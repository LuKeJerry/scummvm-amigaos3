/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#include <stdio.h>

#include "base/main.h"
#include "common/scummsys.h"

#include "backends/platform/amigaos3/amigaos3-aga.h"

#include <proto/icon.h>
#include <proto/timer.h>
#include <workbench/startup.h>

#define DEFAULT_AUDIO_THREAD_PRIORITY 1

static int wbClosed = 0;

struct CxBase* CxBase = NULL;
extern struct Library* CyberGfxBase = NULL;
struct GfxBase* GfxBase = NULL;
struct Library* IconBase = NULL;
struct IntuitionBase* IntuitionBase = NULL;
struct KeymapBase* KeymapBase = NULL;
struct RealTimeBase  *RealTimeBase = NULL;

//extern struct Device* TimerBase = NULL;
struct MsgPort* TimerMP = NULL;
struct Device* TimerBase = NULL;
struct timerequest *TimerIOReq = NULL;
ULONG eclocks_per_ms; /* EClock frequency in 1000Hz */

static void unload_libraries(void) {
	if (CxBase != NULL) {
		CloseLibrary((struct Library*)CxBase);
		CxBase = NULL;
	}

	//    if (CyberGfxBase != NULL) {
	//        CloseLibrary((struct Library*) CyberGfxBase);
	//        CyberGfxBase = NULL;
	//    }

	if (GfxBase != NULL) {
		CloseLibrary((struct Library*)GfxBase);
		GfxBase = NULL;
	}

	if (IconBase != NULL) {
		CloseLibrary((struct Library*)IconBase);
		IconBase = NULL;
	}

	if (IntuitionBase != NULL) {
		CloseLibrary((struct Library*)IntuitionBase);
		IntuitionBase = NULL;
	}

	if (KeymapBase != NULL) {
		CloseLibrary((struct Library*)KeymapBase);
		KeymapBase = NULL;
	}


	if (RealTimeBase != NULL) {
		CloseLibrary((struct Library*)RealTimeBase);
		RealTimeBase = NULL;
	}

	if (TimerBase != NULL) {
		CloseDevice(&TimerIOReq->tr_node);
		TimerBase = NULL;
	}

	if (TimerIOReq != NULL) {
		DeleteIORequest(TimerIOReq);
		TimerIOReq = NULL;
	}

	if (TimerMP != NULL) {
		DeleteMsgPort(TimerMP);
		TimerMP = NULL;
	}
}

static void load_libraries(void) {
	atexit(unload_libraries);

	CxBase = (struct CxBase*)OpenLibrary("commodities.library", 0);
	if (CxBase == NULL) {
		fprintf(stderr, "Unable to load commodities.library!\n");
		exit(EXIT_FAILURE);
	}

	//    CyberGfxBase = (struct Library*) OpenLibrary("cybergraphics.library", 0);
	//    if (CyberGfxBase == NULL) {
	//        fprintf(stderr, "Unable to load cybergraphics.library!\n");
	//        exit(EXIT_FAILURE);
	//    }

	GfxBase = (struct GfxBase*)OpenLibrary("graphics.library", 0);
	if (GfxBase == NULL) {
		fprintf(stderr, "Unable to load graphics.library!\n");
		exit(EXIT_FAILURE);
	}

	IconBase = (struct Library*)OpenLibrary("icon.library", 0);
	if (IconBase == NULL) {
		fprintf(stderr, "Unable to load icon.library!\n");
		exit(EXIT_FAILURE);
	}

	IntuitionBase = (struct IntuitionBase*)OpenLibrary("intuition.library", 0);
	if (IntuitionBase == NULL) {
		fprintf(stderr, "Unable to load intuition.library!\n");
		exit(EXIT_FAILURE);
	}

	KeymapBase = (struct KeymapBase*)OpenLibrary("keymap.library", 0);
	if (KeymapBase == NULL) {
		fprintf(stderr, "Unable to load keymap.library!\n");
		exit(EXIT_FAILURE);
	}

	RealTimeBase = (struct RealTimeBase*)OpenLibrary("realtime.library", 0);
	if (RealTimeBase == NULL)	 {
		fprintf(stderr, "Unable to load realtime.library!\n");
		exit(EXIT_FAILURE);
	}

	// Load timer.device so that GetSysTime is
	// available.
	if ((TimerMP = CreateMsgPort()) == NULL) {
		exit(EXIT_FAILURE);
	}
	if ((TimerIOReq = (timerequest*)CreateIORequest(TimerMP, sizeof(struct timerequest))) == NULL) {
		exit(EXIT_FAILURE);
	}
	BYTE err = OpenDevice("timer.device", UNIT_MICROHZ, &TimerIOReq->tr_node, 37);
	if (err || TimerIOReq->tr_node.io_Device == NULL) {
		fprintf(stderr, "Unable to load timer.device!");
		exit(EXIT_FAILURE);
	}
	TimerBase = TimerIOReq->tr_node.io_Device;

	{
		extern ULONG eclocks_per_ms;
		struct EClockVal time;
		eclocks_per_ms = ReadEClock(&time) / 1000;
	}
}

__stdargs int main(int argcWb, char const * argvWb[]) {
	load_libraries();

	char const * const argvDefault[] = {"ScummVM", NULL};

	char const * const *argv = argvDefault;
	int argc = sizeof(argvDefault) / sizeof(argvDefault[0]) - 1;

	int audioThreadPriority = DEFAULT_AUDIO_THREAD_PRIORITY;
	int closeWb = 0;

	struct Task * task = FindTask(NULL);
	ptrdiff_t ss = (char*)task->tc_SPUpper - (char*)task->tc_SPLower;

	printf("Process stack size is %d bytes.\n", ss);
	if (ss < 100000) {
		printf("Process stack size is smaller than 100000. Exiting.\n");
		exit(EXIT_FAILURE);
	}

	if (argcWb == 0) {
		struct WBStartup* wbStartup = (struct WBStartup*)argvWb;

		// Process Tooltypes.
		struct DiskObject* diskObject = GetDiskObject((char*)wbStartup->sm_ArgList[0].wa_Name);

		if (diskObject != NULL) {
			char* toolType = (char*)FindToolType((char* const*)diskObject->do_ToolTypes, "AUDIO_THREAD_PRIORITY");
			if (toolType != NULL) {
				sscanf(toolType, "%d", &audioThreadPriority);
			}

			toolType = (char*)FindToolType((char* const*)diskObject->do_ToolTypes, "CLOSE_WB");
			if (toolType != NULL) {
				closeWb = 1;
			}

			FreeDiskObject(diskObject);
		}

	} else {
		argc = argcWb;
		argv = argvWb;
	}

	// Create our OSystem instance
	OSystem_AmigaOS3 *amigaOsSystem = new OSystem_AmigaOS3();
	g_system = amigaOsSystem;
	assert(g_system);

	// Pre initialize the backend
	amigaOsSystem->init(audioThreadPriority);

	if (closeWb) {
		wbClosed = CloseWorkBench();
	}

	// Invoke the actual ScummVM main entry point:
	int res = scummvm_main(argc, argv);

	// Delete OSystem
	if (g_system) {
		delete amigaOsSystem;
	}

	if (wbClosed) {
		OpenWorkBench();
	}

	return res;
}
