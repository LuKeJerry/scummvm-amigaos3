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

#include "fullpipe/fullpipe.h"

#include "fullpipe/objects.h"
#include "fullpipe/gfx.h"
#include "fullpipe/statics.h"
#include "fullpipe/scene.h"

#include "common/memstream.h"

namespace Fullpipe {

void Bitmap::load(Common::ReadStream *s) {
	debug(5, "Bitmap::load()");

	_x = s->readUint32LE();
	_y = s->readUint32LE();
	_width = s->readUint32LE();
	_height = s->readUint32LE();
	s->readUint32LE(); // pixels
	_type = s->readUint32LE();
	_field_18 = s->readUint32LE();
	_flags = s->readUint32LE();

	debug(8, "Bitmap: x: %d y: %d w: %d h: %d field_18: 0x%x", _x, _y, _width, _height, _field_18);
	debug(8, "Bitmap: type: %s (0x%04x) flags: 0x%x", Common::tag2string(_type).c_str(), _type, _flags);
}

Background::Background() {
	_x = 0;
	_y = 0;
	_messageQueueId = 0;
	_bigPictureArray1Count = 0;
	_bigPictureArray2Count = 0;
	_bigPictureArray = 0;
	_bgname = 0;
	_palette = 0;
}

bool Background::load(MfcArchive &file) {
	debug(5, "Background::load()");
	_bgname = file.readPascalString();

	int count = file.readUint16LE();

	for (int i = 0; i < count; i++) {
		PictureObject *pct = new PictureObject();

		pct->load(file, i == 0);
		addPictureObject(pct);
	}

	assert(g_fullpipe->_gameProjectVersion >= 4);

	_bigPictureArray1Count = file.readUint32LE();

	assert(g_fullpipe->_gameProjectVersion >= 5);

	_bigPictureArray2Count = file.readUint32LE();

	_bigPictureArray = (BigPicture ***)calloc(_bigPictureArray1Count, sizeof(BigPicture **));

	debug(6, "bigPictureArray[%d][%d]", _bigPictureArray1Count, _bigPictureArray2Count);

	for (int i = 0; i < _bigPictureArray1Count; i++) {
		_bigPictureArray[i] = (BigPicture **)calloc(_bigPictureArray2Count, sizeof(BigPicture *));
		for (int j = 0; j < _bigPictureArray2Count; j++) {
			_bigPictureArray[i][j] = new BigPicture();

			_bigPictureArray[i][j]->load(file);
		}
	}

	return true;
}

void Background::addPictureObject(PictureObject *pct) {
	if (pct->_field_4)
		pct->renumPictures(&_picObjList);

	bool inserted = false;
	for (uint i = 0; i < _picObjList.size(); i++) {
		if (((PictureObject *)_picObjList[i])->_priority == pct->_priority) {
			_picObjList.insert_at(i, pct);
			inserted = true;
			break;
		}
	}

	if (!inserted) {
		_picObjList.push_back(pct);
	}
}

PictureObject::PictureObject() {
	_ox = 0;
	_oy = 0;
	_picture = 0;
}

PictureObject::PictureObject(PictureObject *src) : GameObject(src) {
	_picture = src->_picture;
	_ox2 = _ox;
	_oy2 = _oy;
	_pictureObject2List = src->_pictureObject2List;
}

bool PictureObject::load(MfcArchive &file, bool bigPicture) {
	debug(5, "PictureObject::load()");
	GameObject::load(file);

	if (bigPicture)
		_picture = new BigPicture();
	else
		_picture = new Picture();

	_picture->load(file);

	_pictureObject2List = new CPtrList();

	int count = file.readUint16LE();

	if (count > 0) {
		GameObject *o = new GameObject();
		
		o->load(file);
		_pictureObject2List->push_back(o);
	}

	_ox2 = _ox;
	_oy2 = _oy;

#if 0
	_picture->displayPicture();
#endif

	return true;
}

Common::Point *PictureObject::getDimensions(Common::Point *p) {
	_picture->getDimensions(p);

	return p;
}

void PictureObject::draw() {
	if (_flags & 1)
		_picture->draw(_ox, _oy, 2, 0);
	else
		_picture->draw(_ox, _oy, 0, 0);
}

bool PictureObject::setPicAniInfo(PicAniInfo *picAniInfo) {
	if (!(picAniInfo->type & 2) || (picAniInfo->type & 1)) {
		error("Picture::setPicAniInfo(): Wrong type: %d", picAniInfo->type);

		return false;
	}

	if (picAniInfo->type & 2) {
		setOXY(picAniInfo->ox, picAniInfo->oy);
		_priority = picAniInfo->priority;
		_field_4 = picAniInfo->field_8;
		setFlags(picAniInfo->flags);
		_field_8 = picAniInfo->field_24;

		return true;
	}

	return false;
}

GameObject::GameObject() {
	_field_4 = 0;
	_flags = 0;
	_id = 0;
	_ox = 0;
	_oy = 0;
	_priority = 0;
	_field_20 = 0;
	_field_8 = 0;
}

GameObject::GameObject(GameObject *src) {
	_field_4 = 1;
	_flags = 0;
	_id = src->_id;

	_objectName = (char *)calloc(strlen(src->_objectName) + 1, 1);
	strncpy(_objectName, src->_objectName, strlen(src->_objectName));

	_ox = src->_ox;
	_oy = src->_oy;
	_priority = src->_priority;
	_field_20 = 1;
	_field_8 = src->_field_8;
}

bool GameObject::load(MfcArchive &file) {
	debug(5, "GameObject::load()");
	_field_4 = 0;
	_flags = 0;
	_field_20 = 0;
	
	_id = file.readUint16LE();
	
	_objectName = file.readPascalString();
	_ox = file.readUint32LE();
	_oy = file.readUint32LE();
	_priority = file.readUint16LE();

	if (g_fullpipe->_gameProjectVersion >= 11) {
		_field_8 = file.readUint32LE();
	}

	return true;
}

void GameObject::setOXY(int x, int y) {
	_ox = x;
	_oy = y;
}

void GameObject::renumPictures(CPtrList *lst) {
	int *buf = (int *)calloc(lst->size() + 2, sizeof(int));

	for (uint i = 0; i < lst->size(); i++) {
		if (_id == ((PictureObject *)((*lst)[i]))->_id)
			buf[((PictureObject *)((*lst)[i]))->_field_4] = 1;
	}

	if (buf[_field_4]) {
		uint count;
		for (count = 1; buf[count] && count < lst->size() + 2; count++)
			;
		_field_4 = count;
	}

	free(buf);
}

Picture::Picture() {
	_x = 0;
	_y = 0;
	_field_44 = 0;
	_field_54 = 0;
	_bitmap = 0;
	_alpha = -1;
	_paletteData = 0;
	_convertedBitmap = 0;
}

Picture::~Picture() {
	freePicture();

	_bitmap = 0;

	if (_memoryObject2)
		delete _memoryObject2;

	if (_paletteData)
		free(_paletteData);

	if (_convertedBitmap) {
		delete _convertedBitmap;
		_convertedBitmap = 0;
	}
}

void Picture::freePicture() {
	if (_bitmap) {
		if (testFlags() && !_field_54) {
			freeData();
			delete _bitmap;
			_bitmap = 0;
		}
	}

	if (_bitmap) {
		_bitmap = 0;
		_data = 0;
	}

	if (_convertedBitmap) {
		free(_convertedBitmap->_pixels);
		delete _convertedBitmap;
		_convertedBitmap = 0;
	}
}

bool Picture::load(MfcArchive &file) {
	debug(5, "Picture::load()");
	MemoryObject::load(file);

	_x = file.readUint32LE();
	_y = file.readUint32LE();
	_field_44 = file.readUint16LE();
	
	assert(g_fullpipe->_gameProjectVersion >= 2);

	_width = file.readUint32LE();
	_height = file.readUint32LE();

	_flags |= 1;

	_memoryObject2 = new MemoryObject2;
	_memoryObject2->load(file);

	if (_memoryObject2->_data) {
		setAOIDs();
	}

	assert (g_fullpipe->_gameProjectVersion >= 12);

	_alpha = file.readUint32LE();

	int havePal = file.readUint32LE();

	if (havePal > 0) {
		_paletteData = (byte *)calloc(1024, 1);
		file.read(_paletteData, 1024);
	}

	getData();

	debug(5, "Picture::load: <%s>", _memfilename);

	return true;
}

void Picture::setAOIDs() {
	int w = (g_fullpipe->_pictureScale + _width - 1) / g_fullpipe->_pictureScale;
	int h = (g_fullpipe->_pictureScale + _height - 1) / g_fullpipe->_pictureScale;

	_memoryObject2->_rows = (byte **)malloc(w * sizeof(int *));

	int pitch = 2 * h;
	byte *ptr = _memoryObject2->getData();
	for (int i = 0; i < w; i++) {
		_memoryObject2->_rows[i] = ptr;
		ptr += pitch;
	}
}

void Picture::init() {
	_bitmap = new Bitmap();

	getDibInfo();

	_bitmap->_flags |= 0x1000000;
}

Common::Point *Picture::getDimensions(Common::Point *p) {
	p->x = _width;
	p->y = _height;

	return p;
}

void Picture::getDibInfo() {
	int off = _dataSize & ~0xf;

	debug(0, "Picture::getDibInfo: _dataSize: %d", _dataSize);

	if (!_dataSize) {
		warning("Picture::getDibInfo(): Empty data size");
		return;
	}

	if (_dataSize != off) {
		warning("Uneven data size: 0x%x", _dataSize);
	}

	Common::MemoryReadStream *s = new Common::MemoryReadStream(_data + off - 32, 32);

	_bitmap->load(s);
	_bitmap->_pixels = _data;
}

Bitmap *Picture::getPixelData() {
	if (!_bitmap)
		init();

	return _bitmap;
}

void Picture::draw(int x, int y, int style, int angle) {
	int x1 = x;
	int y1 = y;

	debug(0, "Picture::draw(%d, %d, %d, %d)", x, y, style, angle);

	if (x != -1)
		x1 = x;

	if (y != -1)
		y1 = y;

	if (!_bitmap)
		init();

	if (!_bitmap)
		return;

	if (_alpha < 0xff) {
		warning("Picture:draw: alpha = %0x", _alpha);
	}

	switch (style) {
	case 1:
		//flip
		warning("STUB: Picture::draw: style 1");
		break;
	case 2:
		error("STUB: Picture::draw: style 2");
		break;
	default:
		if (angle)
			drawRotated(x1, y1, angle);
		else
			_bitmap->putDib(x1, y1, (int32 *)_paletteData);
	}
}

void Picture::drawRotated(int x, int y, int angle) {
	warning("STUB: Picture::drawRotated(%d, %d, %d)", x, y, angle);
}

void Picture::displayPicture() {
	if (!g_fullpipe->_gameContinue)
		return;

	getData();
	init();

	if (!_dataSize)
		return;

	g_fullpipe->_backgroundSurface.fillRect(Common::Rect(0, 0, 799, 599), 0);
	g_fullpipe->_system->copyRectToScreen(g_fullpipe->_backgroundSurface.getBasePtr(0, 0), g_fullpipe->_backgroundSurface.pitch, 0, 0, 799, 599);

	draw(0, 0, 0, 0);

	g_fullpipe->updateEvents();
	g_fullpipe->_system->delayMillis(10);
	g_fullpipe->_system->updateScreen();

	while (g_fullpipe->_gameContinue) {
		g_fullpipe->updateEvents();
		g_fullpipe->_system->delayMillis(10);
		g_fullpipe->_system->updateScreen();

		if (g_fullpipe->_keyState == ' ') {
			g_fullpipe->_keyState = Common::KEYCODE_INVALID;
			break;
		}
	}
}

void Picture::setPaletteData(byte *pal) {
	if (_paletteData)
		free(_paletteData);

	if (pal) {
		_paletteData = (byte *)malloc(1024);
		memcpy(_paletteData, pal, 1024);
	}
}

void Picture::copyMemoryObject2(Picture *src) {
	if (_width == src->_width && _height == src->_height) {
		if (src->_memoryObject2 && src->_memoryObject2->_rows && _memoryObject2) {
			byte *data = loadData();
			_memoryObject2->copyData(data, _dataSize);
			setAOIDs();
		}
	}
}

void Bitmap::putDib(int x, int y, int32 *palette) {
	debug(0, "Bitmap::putDib(%d, %d)", x, y);

	_x = x - g_fullpipe->_sceneRect.left;
	_y = y - g_fullpipe->_sceneRect.top;

	if (_type == MKTAG('R', 'B', '\0', '\0'))
		putDibRB(palette);
	else
		putDibCB(palette);
}

void Bitmap::putDibRB(int32 *palette) {
	uint16 *curDestPtr;
	int endy;
	int x;
	int start1;
	int fillLen;
	uint16 pixel;
	int endx;
	int y;
	uint16 *srcPtr2;
	uint16 *srcPtr;

	debug(0, "Bitmap::putDibRB()");

	endx = _width + _x - 1;
	endy = _height + _y - 1;

	if (_x > 799 || endx < 0 || _y > 599 || endy < 0)
		return;

	if (endy > 599)
		endy = 599;

	if (endx > 799)
		endx = 799;

	int startx = _x;
	if (startx < 0)
		startx = 0;

	int starty = _y;
	if (starty < 0)
		starty = 0;

	y = endy;
	srcPtr = (uint16 *)_pixels;

	bool breakup = false;
	for (y = endy; y >= starty && !breakup; y--) {
		x = startx;

		while ((pixel = *srcPtr++) != 0) {
			if (pixel == 0x100) {
				breakup = true;
				break;
			}

			while (pixel == 0x200 && y >= starty) {
				uint16 value = *srcPtr++;

				x += (byte)(value & 0xff);
				y -= (byte)((value >> 8) & 0xff);

				pixel = *srcPtr++;
			}

			if (y < starty || pixel == 0)
				break;

			start1 = x;
			fillLen = (byte)(pixel & 0xff);

			if (fillLen) {
				x += fillLen;

				if (start1 < 0) {
					fillLen += start1;

					if (fillLen > 0)
						start1 = 0;
				}

				if (fillLen > 0 || start1 >= 0) {
					if (x <= 799 + 1 || (fillLen += 799 - x + 1, fillLen > 0)) {
						if (y <= endy) {
							curDestPtr = (uint16 *)g_fullpipe->_backgroundSurface.getBasePtr(start1, y);
							int bgcolor = palette[(pixel >> 8) & 0xff];
							colorFill(curDestPtr, fillLen, bgcolor);
						}
					}
				}
			} else {
				fillLen = (pixel >> 8) & 0xff;
				srcPtr2 = srcPtr;
				x += fillLen;
				srcPtr += (fillLen + 1) >> 1;

				if (start1 < 0) {
					fillLen += start1;
					if (fillLen > 0) {
						srcPtr2 = (uint16 *)((byte *)srcPtr2 - start1);
						start1 = 0;
					}
				}

				if (x > 799 + 1) {
					fillLen += 799 - x + 1;
					if (fillLen <= 0)
						continue;
				}

				if (y <= endy) {
					curDestPtr = (uint16 *)g_fullpipe->_backgroundSurface.getBasePtr(start1, y);
					paletteFill(curDestPtr, (byte *)srcPtr2, fillLen, (int32 *)palette);
				}
			}
		}
	}

	g_fullpipe->_system->copyRectToScreen(g_fullpipe->_backgroundSurface.getBasePtr(startx, starty), g_fullpipe->_backgroundSurface.pitch, startx, starty, endx + 1 - startx, endy + 1 - starty);
}

void Bitmap::putDibCB(int32 *palette) {
	uint16 *curDestPtr;
	int endx;
	int endy;
	int bpp;
	uint pitch;
	bool cb05_format;

	endx = _width + _x - 1;
	endy = _height + _y - 1;

	debug(0, "Bitmap::putDibCB(): %d, %d, %d, %d [%d, %d]", _x, _y, endx, endy, _width, _height);

	if (_x > 799 || endx < 0 || _y > 599 || endy < 0)
		return;

	if (endy > 599)
		endy = 599;

	if (endx > 799)
		endx = 799;

	cb05_format = (_type == MKTAG('C', 'B', '\05', 'e'));

	bpp = cb05_format ? 2 : 1;
	pitch = (bpp * _width + 3) & 0xFFFFFFFC;

	byte *srcPtr = &_pixels[pitch * (endy - _y)];

	int startx = _x;
	if (startx < 0) {
		srcPtr += bpp * -_x;
		startx = 0;
	}

	int starty = _y;
	if (starty < 0)
		starty = 0;

	if (_flags & 0x1000000) {
		for (int y = starty; y < endy; srcPtr -= pitch, y++) {
			curDestPtr = (uint16 *)g_fullpipe->_backgroundSurface.getBasePtr(startx, y);
			copierKeyColor(curDestPtr, srcPtr, endx - startx + 1, _flags & 0xff, (int32 *)palette, cb05_format);
		}
	} else {
		for (int y = starty; y <= endy; srcPtr -= pitch, y++) {
			curDestPtr = (uint16 *)g_fullpipe->_backgroundSurface.getBasePtr(startx, y);
			copier(curDestPtr, srcPtr, endx - startx + 1, (int32 *)palette, cb05_format);
		}
	}

	g_fullpipe->_system->copyRectToScreen(g_fullpipe->_backgroundSurface.getBasePtr(startx, starty), g_fullpipe->_backgroundSurface.pitch, startx, starty, endx + 1 - startx, endy + 1 - starty);
}

void Bitmap::colorFill(uint16 *dest, int len, int32 color) {
#if 0
	if (blendMode) {
		if (blendMode != 1)
			error("vrtPutDib : RLE Fill : Invalid alpha blend mode");

		colorFill = ptralphaFillColor16bit;
	} else {
		colorFill = ptrfillColor16bit;
	}
#endif

	for (int i = 0; i < len; i++)
		*dest++ = (int16)(color & 0xffff);
}

void Bitmap::paletteFill(uint16 *dest, byte *src, int len, int32 *palette) {
#if 0
	if (blendMode) {
		if (blendMode != 1)
			error("vrtPutDib : RLE Fill : Invalid alpha blend mode");

		paletteFill = ptrcopierWithPaletteAlpha;
	} else {
		paletteFill = ptrcopierWithPalette;
	}
#endif

	for (int i = 0; i < len; i++)
		*dest++ = READ_LE_UINT32(&palette[*src++]) & 0xffff;
}

void Bitmap::copierKeyColor(uint16 *dest, byte *src, int len, int keyColor, int32 *palette, bool cb05_format) {
#if 0
	if (blendMode) {
		if (blendMode == 1) {
			if (cb05_format)
				copierKeyColor = ptrcopier16bitKeycolorAlpha;
			else
				copierKeyColor = ptrcopierKeycolorAlpha;
		} else {
			copier = 0;
		}
	} else if (cb05_format) {
		copierKeyColor = ptrcopier16bitKeycolor;
	} else {
		copierKeyColor = ptrkeyColor16bit;
	}
#endif

	if (!cb05_format) {
		for (int i = 0; i < len; i++) {
			if (*src != keyColor)
				*dest = READ_LE_UINT32(&palette[*src]) & 0xffff;

			dest++;
			src++;
		}
	} else {
		int16 *src16 = (int16 *)src;

		for (int i = 0; i < len; i++) {
			if (*src16 != 0)
				*dest = *src16;

			dest++;
			src16++;
		}
	}
}

void Bitmap::copier(uint16 *dest, byte *src, int len, int32 *palette, bool cb05_format) {
#if 0
	if (blendMode) {
		if (blendMode == 1) {
			if (cb05_format)
				copier = ptrcopier16bitAlpha;
			else
				copier = ptrcopierWithPaletteAlpha;
		} else {
			copier = 0;
		}
	} else if (cb05_format) {
		copier = ptrcopier16bit;
	} else {
		copier = ptrcopierWithPalette;
	}
#endif

	if (!cb05_format) {
		for (int i = 0; i < len; i++)
			*dest++ = READ_LE_UINT32(&palette[*src++]) & 0xffff;
	} else {
		int16 *src16 = (int16 *)src;

		for (int i = 0; i < len; i++)
			*dest++ = *src16++;
	}
}

Bitmap *Bitmap::reverseImage() {
	warning("STUB: Bitmap::reverseImage()");

	return this;
}

bool BigPicture::load(MfcArchive &file) {
	debug(5, "BigPicture::load()");
	Picture::load(file);

	return true;
}

Shadows::Shadows() {
	_staticAniObjectId = 0;
	_movementId = 0;
	_sceneId = 0;
}

bool Shadows::load(MfcArchive &file) {
	debug(5, "Shadows::load()");
	_sceneId = file.readUint32LE();
	_staticAniObjectId = file.readUint32LE();
	_movementId = file.readUint32LE();

	return true;
}

void Shadows::init() {
	Scene *scene = g_fullpipe->accessScene(_sceneId);

	StaticANIObject *st;
	Movement *mov;

	if (scene && (st = scene->getStaticANIObject1ById(_staticAniObjectId, -1)) != 0
		&& ((mov = st->getMovementById(_movementId)) != 0))
		initMovement(mov);
}

void Shadows::initMovement(Movement *mov) {
	warning("STUB: Shadows::initMovement()");
}

DynamicPhase *Shadows::findSize(int width, int height) {
	int idx = 0;
	int min = 1000;

	for (uint i = 0; i < _items.size(); i++) {
		int w = abs(width - _items[i].width);
		if (w < min) {
			min = w;
			idx = i;
		}
	}
	return _items[idx].dynPhase;
}

} // End of namespace Fullpipe
