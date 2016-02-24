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
 */

namespace Wage {

#define ADGF_DEFAULT (ADGF_DROPLANGUAGE|ADGF_DROPPLATFORM)
#define ADGF_GENERIC (ADGF_DROPLANGUAGE|ADGF_DROPPLATFORM|ADGF_USEEXTRAASTITLE)

#define FANGAME(n,f,m,s) { "wage",n,AD_ENTRY1s(f,m,s),Common::EN_ANY,Common::kPlatformMacintosh,ADGF_GENERIC,GUIO0()}
#define BIGGAME(t,v,f,m,s) { t,v,AD_ENTRY1s(f,m,s),Common::EN_ANY,Common::kPlatformMacintosh,ADGF_DEFAULT,GUIO0()}

static const ADGameDescription gameDescriptions[] = {
	FANGAME("3rd Floor", "3rd Floor", "a107d7a177970b2259e32681bd8b47c9", 285056),
	BIGGAME("afm", "v1.8", "Another Fine Mess 1.8", "8e5aa915f3253efb2aab52435647b25e", 1456000),
	BIGGAME("amot", "v1.8", "A Mess O' Trouble 1.8", "b3ef53afed282671b704e45df829350c", 1895552),
	// Off-screen rendering in second screen
	FANGAME("Bug Hunt", "Bug Hunt", "2ebd3515a87941063ad66c3cf93c5e78", 200064),
	// Problems with letter rendering
	FANGAME("Canal District", "Canal District", "8856bc699a20fc5b7fc67accee12cac7", 658176),
	BIGGAME("cantitoe", "", "Camp Cantitoe", "098aa5c11c58e1ef274a30a9e01b4755", 621440),
	FANGAME("Deep Angst", "Deep Angst", "635f62bbc569e72b03cab9107927d03d", 335232),
	FANGAME("Dungeon World II", "DungeonWorld2", "e10c5e3cc17879c298b1551f33571b15", 234880),
	// Polygons with ignored byte 1
	FANGAME("Double Trouble", "Double Trouble", "5e9ee13d09ac54918ed111fa9727ac1c", 557184),
	FANGAME("Escape from School!", "Escape from School!", "a854be48d4af20126d18a9cad93a969b", 51840),
	FANGAME("Magic Rings", "Magic Rings", "6e0d1dd561d3dad8f9a7a20ed1f09b16", 112000),
	FANGAME("Midnight Snack", "Midnight Snack", "346982a32fc701f53bb19771d72063d0", 69504),
	FANGAME("Queen Quest", "Queen Quest", "730605d312efedb5e3ff108522fcac18", 59776),
	BIGGAME("scepters", "", "Scepters", "b80bff315897776dda7689cdf829fab4", 360832),
	FANGAME("Time Bomb", "Time Bomb", "2df84b636237686b624e736a698a16c4", 66432),
	FANGAME("ZikTuria", "ZikTuria", "e793155bed1a70fa2074a3fcd696b751", 54784),
	FANGAME("Zoony", "Zoony", "e6cc8a914a4215dafbcce6315dd12cf5", 160256),

	AD_TABLE_END_MARKER
};

} // End of namespace Wage
