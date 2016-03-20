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

#ifndef SHERLOCK_SURFACE_H
#define SHERLOCK_SURFACE_H

#include "common/rect.h"
#include "common/platform.h"
#include "graphics/managed_surface.h"
#include "sherlock/fonts.h"
#include "sherlock/image_file.h"

namespace Sherlock {

#define SCALE_THRESHOLD 0x100
#define TRANSPARENCY 255

/**
 * Implements a descendent surface that combines both a managed surface and the font
 * drawing code. It also introduces a series of drawing method stubs that the 3DO
 * Serrated Scalpel screen overrides to implement sprite doubling
 */
class Surface: virtual public Graphics::ManagedSurface, public Fonts {
public:
	/**
	 * Constructor
	 */
	Surface();
	
	/**
	 * Constructor
	 */
	Surface(int width, int height);

	/**
	 * Set the surface details
	 */
	void setPixels(byte *pixelsPtr, int sizeX, int sizeY, const Graphics::PixelFormat &pixFormat);

	/**
	 * Draws a surface on this surface
	 */
	virtual void SHblitFrom(const Graphics::Surface &src) {
		Graphics::ManagedSurface::blitFrom(src);
	}

	/**
	 * Draws a surface at a given position within this surface
	 */
	virtual void SHblitFrom(const Graphics::Surface &src, const Common::Point &destPos) {
		Graphics::ManagedSurface::blitFrom(src, destPos);
	}

	/**
	 * Draws a sub-section of a surface at a given position within this surface
	 */
	virtual void SHblitFrom(const Graphics::Surface &src, const Common::Point &destPos, const Common::Rect &srcBounds) {
		Graphics::ManagedSurface::blitFrom(src, srcBounds, destPos);
	}

	/**
	 * Draws an image frame at a given position within this surface with transparency
	 */
	void SHtransBlitFrom(const ImageFrame &src, const Common::Point &pt,
		bool flipped = false, int overrideColor = 0, int scaleVal = SCALE_THRESHOLD);

	/**
	 * Draws an image frame at a given position within this surface with transparency
	 */
	void SHtransBlitFrom(const Graphics::Surface &src, const Common::Point &pt,
		bool flipped = false, int overrideColor = 0, int scaleVal = SCALE_THRESHOLD);

	/**
	 * Fill a given area of the surface with a given color
	 */
	virtual void SHfillRect(const Common::Rect &r, uint color) {
		Graphics::ManagedSurface::fillRect(r, color);
	}

	/**
	 * Return the width of the surface
	 */
	virtual uint16 width() const { return this->w; }
	
	/**
	 * Return the height of the surface
	 */
	virtual uint16 height() const { return this->h; }

	/**
	 * Draws the given string into the back buffer using the images stored in _font
	 */
	void writeString(const Common::String &str, const Common::Point &pt, uint overrideColor);
	
	/**
	 * Draws a fancy version of the given string at the given position
	 */
	void writeFancyString(const Common::String &str, const Common::Point &pt, uint overrideColor1, uint overrideColor2);
};

} // End of namespace Sherlock

#endif
