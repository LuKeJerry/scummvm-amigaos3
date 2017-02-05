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
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "audio/decoders/wave.h"
#include "common/memstream.h"
#include "titanic/sound/wave_file.h"
#include "titanic/sound/sound_manager.h"
#include "titanic/support/simple_file.h"

namespace Titanic {

CWaveFile::CWaveFile() : _soundManager(nullptr), _stream(nullptr),
		_soundType(Audio::Mixer::kPlainSoundType) {
	setup();
}

CWaveFile::CWaveFile(QSoundManager *owner) : _soundManager(owner), _stream(nullptr),
		_soundType(Audio::Mixer::kPlainSoundType) {
	setup();
}

void CWaveFile::setup() {
	_loadMode = LOADMODE_SCUMMVM;
	_field4 = 0;
	_field14 = 1;
	_dataSize = 0;
	_audioBuffer = nullptr;
	_disposeAudioBuffer = DisposeAfterUse::NO;
	_channel = -1;
}

CWaveFile::~CWaveFile() {
	if (_stream) {
		_soundManager->soundFreed(_soundHandle);
		delete _stream;
	}

	if (_disposeAudioBuffer == DisposeAfterUse::YES && _audioBuffer)
		delete _audioBuffer;
}

uint CWaveFile::getDurationTicks() const {
	if (!_stream)
		return 0;

	// FIXME: The original uses acmStreamSize to calculate
	// a desired size. Since I have no idea how the system API
	// method works, for now I'm using a simple ratio of a
	// sample output to input value
	uint dataSize = _dataSize - 0x46;
	double newSize = (double)dataSize * (1475712.0 / 199836.0);
	return (uint)(newSize * 1000.0 / _stream->getRate());
}

bool CWaveFile::loadSound(const CString &name) {
	assert(!_stream);

	StdCWadFile file;
	if (!file.open(name))
		return false;

	Common::SeekableReadStream *stream = file.readStream();
	_dataSize = stream->size();
	_stream = Audio::makeWAVStream(stream->readStream(_dataSize), DisposeAfterUse::YES);
	_soundType = Audio::Mixer::kSFXSoundType;

	return true;
}

bool CWaveFile::loadSpeech(CDialogueFile *dialogueFile, int speechIndex) {
	DialogueResource *res = dialogueFile->openWaveEntry(speechIndex);
	if (!res)
		return false;

	byte *data = (byte *)malloc(res->_size);
	dialogueFile->read(res, data, res->_size);

	_dataSize = res->_size;
	_stream = Audio::makeWAVStream(new Common::MemoryReadStream(data, _dataSize, DisposeAfterUse::YES),
		DisposeAfterUse::YES);
	_soundType = Audio::Mixer::kSpeechSoundType;

	return true;
}

bool CWaveFile::loadMusic(const CString &name) {
	assert(!_stream);

	StdCWadFile file;
	if (!file.open(name))
		return false;

	Common::SeekableReadStream *stream = file.readStream();
	_dataSize = stream->size();
	_stream = Audio::makeWAVStream(stream->readStream(_dataSize), DisposeAfterUse::YES);
	_soundType = Audio::Mixer::kMusicSoundType;

	return true;
}

bool CWaveFile::loadMusic(CAudioBuffer *buffer, DisposeAfterUse::Flag disposeAfterUse) {
	_audioBuffer = buffer;
	_disposeAudioBuffer = disposeAfterUse;
	_loadMode = LOADMODE_AUDIO_BUFFER;
	_field14 = 0;

	return true;
}

uint CWaveFile::getFrequency() const {
	return _stream->getRate();
}

void CWaveFile::reset() {
	_stream->rewind();
}

const byte *CWaveFile::lock() {
	switch (_loadMode) {
	case LOADMODE_AUDIO_BUFFER:
		// TODO: At this point, locking returning a pointer to a buffer
		// into a QSound wave mixer, for pushing out
		error("TODO: Handle pushing data to sound");

	default:
		return nullptr;
	}
}

void CWaveFile::unlock(const byte *ptr) {
	// No implementation needed in ScummVM
}

} // End of namespace Titanic z
