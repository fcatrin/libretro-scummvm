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

#include "common/util.h"
#include "common/stack.h"
#include "graphics/primitives.h"

#include "sci/sci.h"
#include "sci/engine/kernel.h"
#include "sci/engine/selector.h"
#include "sci/engine/state.h"
#include "sci/graphics/cache.h"
#include "sci/graphics/compare.h"
#include "sci/graphics/font.h"
#include "sci/graphics/frameout.h"
#include "sci/graphics/screen.h"
#include "sci/graphics/text32.h"

namespace Sci {

int16 GfxText32::_defaultFontId = 0;

GfxText32::GfxText32(SegManager *segMan, GfxCache *fonts, GfxScreen *screen) :
	_segMan(segMan),
	_cache(fonts),
	_screen(screen),
	_scaledWidth(g_sci->_gfxFrameout->getCurrentBuffer().scriptWidth),
	_scaledHeight(g_sci->_gfxFrameout->getCurrentBuffer().scriptHeight),
	// Not a typo, the original engine did not initialise height, only width
	_width(0),
	_text(""),
	_field_20(0),
	_field_2C(2),
	_field_30(0),
	_field_34(0),
	_field_38(0),
	_field_3C(0),
	_bitmap(NULL_REG) {
		_fontId = _defaultFontId;
		_font = _cache->getFont(_defaultFontId);
	}

#define BITMAP_HEADER_SIZE 46
void GfxText32::buildBitmapHeader(byte *bitmap, const int16 width, const int16 height, const uint8 skipColor, const int16 displaceX, const int16 displaceY, const int16 scaledWidth, const int16 scaledHeight, const uint32 hunkPaletteOffset, const bool useRemap) const {

	WRITE_SCI11ENDIAN_UINT16(bitmap + 0, width);
	WRITE_SCI11ENDIAN_UINT16(bitmap + 2, height);
	WRITE_SCI11ENDIAN_UINT16(bitmap + 4, (uint16)displaceX);
	WRITE_SCI11ENDIAN_UINT16(bitmap + 6, (uint16)displaceY);
	bitmap[8] = skipColor;
	bitmap[9] = 0;
	WRITE_SCI11ENDIAN_UINT16(bitmap + 10, 0);

	if (useRemap) {
		bitmap[10] |= 2;
	}

	WRITE_SCI11ENDIAN_UINT32(bitmap + 12, width * height);
	WRITE_SCI11ENDIAN_UINT32(bitmap + 16, 0);

	if (hunkPaletteOffset) {
		WRITE_SCI11ENDIAN_UINT32(bitmap + 20, hunkPaletteOffset + BITMAP_HEADER_SIZE);
	} else {
		WRITE_SCI11ENDIAN_UINT32(bitmap + 20, 0);
	}

	WRITE_SCI11ENDIAN_UINT32(bitmap + 24, BITMAP_HEADER_SIZE);
	WRITE_SCI11ENDIAN_UINT32(bitmap + 28, BITMAP_HEADER_SIZE);
	WRITE_SCI11ENDIAN_UINT32(bitmap + 32, 0);
	WRITE_SCI11ENDIAN_UINT16(bitmap + 36, scaledWidth);
	WRITE_SCI11ENDIAN_UINT16(bitmap + 38, scaledHeight);
}

reg_t GfxText32::createFontBitmap(int16 width, int16 height, const Common::Rect &rect, const Common::String &text, const uint8 foreColor, const uint8 backColor, const uint8 skipColor, const GuiResourceId fontId, const TextAlign alignment, const int16 borderColor, const bool dimmed, const bool doScaling, reg_t *outBitmapObject) {

	_field_22 = 0;
	_borderColor = borderColor;
	_text = text;
	_textRect = rect;
	_width = width;
	_height = height;
	_foreColor = foreColor;
	_backColor = backColor;
	_skipColor = skipColor;
	_alignment = alignment;
	_dimmed = dimmed;

	setFont(fontId);

	if (doScaling) {
		int16 scriptWidth = g_sci->_gfxFrameout->getCurrentBuffer().scriptWidth;
		int16 scriptHeight = g_sci->_gfxFrameout->getCurrentBuffer().scriptHeight;

		Ratio scaleX(_scaledWidth, scriptWidth);
		Ratio scaleY(_scaledHeight, scriptHeight);

		_width = (_width * scaleX).toInt();
		_height = (_height * scaleY).toInt();
		mulinc(_textRect, scaleX, scaleY);
	}

	// _textRect represents where text is drawn inside the
	// bitmap; clipRect is the entire bitmap
	Common::Rect bitmapRect(_width, _height);

	if (_textRect.intersects(bitmapRect)) {
		_textRect.clip(bitmapRect);
	} else {
		_textRect = Common::Rect();
	}

	_bitmap = _segMan->allocateHunkEntry("FontBitmap()", _width * _height + BITMAP_HEADER_SIZE);

	byte *bitmap = _segMan->getHunkPointer(_bitmap);
	buildBitmapHeader(bitmap, _width, _height, _skipColor, 0, 0, _scaledWidth, _scaledHeight, 0, false);

	erase(bitmapRect, false);

	if (_borderColor > -1) {
		drawFrame(bitmapRect, 1, _borderColor, false);
	}

	drawTextBox();

	*outBitmapObject = _bitmap;
	return _bitmap;
}

reg_t GfxText32::createTitledFontBitmap(CelInfo32 &celInfo, Common::Rect &rect, Common::String &text, int16 foreColor, int16 backColor, int font, int16 skipColor, int16 borderColor, bool dimmed, void *unknown1) {
	warning("TODO: createTitledFontBitmap");
	return NULL_REG;
}

void GfxText32::setFont(const GuiResourceId fontId) {
	// NOTE: In SCI engine this calls FontMgr::BuildFontTable and then a font
	// table is built on the FontMgr directly; instead, because we already have
	// font resources, this code just grabs a font out of GfxCache.
	if (fontId != _fontId) {
		_fontId = fontId == -1 ? _defaultFontId : fontId;
		_font = _cache->getFont(_fontId);
	}
}

void GfxText32::drawFrame(const Common::Rect &rect, const int16 size, const uint8 color, const bool doScaling) {
	Common::Rect targetRect = doScaling ? scaleRect(rect) : rect;

	byte *bitmap = _segMan->getHunkPointer(_bitmap);
	byte *pixels = bitmap + READ_SCI11ENDIAN_UINT32(bitmap + 28);

	// NOTE: Not fully disassembled, but this should be right
	// TODO: Implement variable frame size
	assert(size == 1);
	Buffer buffer(_width, _height, pixels);
	buffer.frameRect(targetRect, color);
}

void GfxText32::drawChar(const uint8 charIndex) {
	byte *bitmap = _segMan->getHunkPointer(_bitmap);
	byte *pixels = bitmap + READ_SCI11ENDIAN_UINT32(bitmap + 28);

	_font->drawToBuffer(charIndex, _drawPosition.y, _drawPosition.x, _foreColor, _dimmed, pixels, _width, _height);
	_drawPosition.x += _font->getCharWidth(charIndex);
}

uint16 GfxText32::getCharWidth(const uint8 charIndex, const bool doScaling) const {
	uint16 width = _font->getCharWidth(charIndex);
	if (doScaling) {
		width = scaleUpWidth(width);
	}
	return width;
}

void GfxText32::drawTextBox() {
	if (_text.size() == 0) {
		return;
	}

	const char *text = _text.c_str();
	const char *sourceText = text;
	int16 textRectWidth = _textRect.width();
	_drawPosition.y = _textRect.top;
	uint charIndex = 0;
	if (getLongest(&charIndex, textRectWidth) == 0) {
		error("DrawTextBox GetLongest=0");
	}

	charIndex = 0;
	uint nextCharIndex = 0;
	while (*text != '\0') {
		_drawPosition.x = _textRect.left;

		uint length = getLongest(&nextCharIndex, textRectWidth);
		int16 textWidth = getTextWidth(charIndex, length);

		if (_alignment == kTextAlignCenter) {
			_drawPosition.x += (textRectWidth - textWidth) / 2;
		} else if (_alignment == kTextAlignRight) {
			_drawPosition.x += textRectWidth - textWidth;
		}

		drawText(charIndex, length);
		charIndex = nextCharIndex;
		text = sourceText + charIndex;
		_drawPosition.y += _font->getHeight();
	}
}

void GfxText32::drawText(const uint index, uint length) {
	assert(index + length <= _text.size());

	// NOTE: This draw loop implementation is somewhat different than the
	// implementation in the actual engine, but should be accurate. Primarily
	// the changes revolve around eliminating some extra temporaries and
	// fixing the logic to match.
	const char *text = _text.c_str() + index;
	while (length-- > 0) {
		char currentChar = *text++;

		if (currentChar == '|') {
			const char controlChar = *text++;
			--length;

			if (length == 0) {
				return;
			}

			if (controlChar == 'a' || controlChar == 'c' || controlChar == 'f') {
				uint16 value = 0;

				while (length > 0) {
					const char valueChar = *text;
					if (valueChar < '0' || valueChar > '9') {
						break;
					}

					++text;
					--length;
					value = 10 * value + (valueChar - '0');
				}

				if (length == 0) {
					return;
				}

				if (controlChar == 'a') {
					_alignment = (TextAlign)value;
				} else if (controlChar == 'c') {
					_foreColor = value;
				} else if (controlChar == 'f') {
					setFont(value);
				}
			}

			while (length > 0 && *text != '|') {
				++text;
				--length;
			}
		} else {
			drawChar(currentChar);
		}
	}
}

uint GfxText32::getLongest(uint *charIndex, const int16 width) {
	assert(width > 0);

	uint testLength = 0;
	uint length = 0;

	const uint initialCharIndex = *charIndex;

	// The index of the next word after the last word break
	uint lastWordBreakIndex = *charIndex;

	const char *text = _text.c_str() + *charIndex;

	char currentChar;
	while ((currentChar = *text++) != '\0') {
		// NOTE: In the original engine, the font, color, and alignment were
		// reset here to their initial values

		// The text to render contains a line break; stop at the line break
		if (currentChar == '\r' || currentChar == '\n') {
			// Skip the rest of the line break if it is a Windows-style
			// \r\n or non-standard \n\r
			// NOTE: In the original engine, the `text` pointer had not been
			// advanced yet so the indexes used to access characters were
			// one higher
			if (
				(currentChar == '\r' && text[0] == '\n') ||
				(currentChar == '\n' && text[0] == '\r' && text[1] != '\n')
			) {
				++*charIndex;
			}

			// We are at the end of a line but the last word in the line made
			// it too wide to fit in the text area; return up to the previous
			// word
			if (length && getTextWidth(initialCharIndex, testLength) > width) {
				*charIndex = lastWordBreakIndex;
				return length;
			}

			// Skip the line break and return all text seen up to now
			// NOTE: In original engine, the font, color, and alignment were
			// reset, then getTextWidth was called to use its side-effects to
			// set font, color, and alignment according to the text from
			// `initialCharIndex` to `testLength`
			++*charIndex;
			return testLength;
		} else if (currentChar == ' ') {
			// The last word in the line made it too wide to fit in the text area;
			// return up to the previous word, then collapse the whitespace
			// between that word and its next sibling word into the line break
			if (getTextWidth(initialCharIndex, testLength) > width) {
				*charIndex = lastWordBreakIndex;
				const char *nextChar = _text.c_str() + lastWordBreakIndex;
				while (*nextChar++ == ' ') {
					++*charIndex;
				}

				// NOTE: In original engine, the font, color, and alignment were
				// set here to the values that were seen at the last space character
				return length;
			}

			// NOTE: In the original engine, the values of _fontId, _foreColor,
			// and _alignment were stored for use in the return path mentioned
			// just above here

			// We found a word break that was within the text area, memorise it
			// and continue processing. +1 on the character index because it has
			// not been incremented yet so currently points to the word break
			// and not the word after the break
			length = testLength;
			lastWordBreakIndex = *charIndex + 1;
		}

		// In the middle of a line, keep processing
		++*charIndex;
		++testLength;

		// NOTE: In the original engine, the font, color, and alignment were
		// reset here to their initial values

		// The text to render contained no word breaks yet but is already too
		// wide for the text area; just split the word in half at the point
		// where it overflows
		if (length == 0 && getTextWidth(initialCharIndex, testLength) > width) {
			*charIndex = --testLength + lastWordBreakIndex;
			return testLength;
		}
	}

	// The complete text to render was a single word, or was narrower than
	// the text area, so return the entire line
	if (length == 0 || getTextWidth(initialCharIndex, testLength) <= width) {
		// NOTE: In original engine, the font, color, and alignment were
		// reset, then getTextWidth was called to use its side-effects to
		// set font, color, and alignment according to the text from
		// `initialCharIndex` to `testLength`
		return testLength;
	}

	// The last word in the line made it wider than the text area, so return
	// up to the penultimate word
	*charIndex = lastWordBreakIndex;
	return length;
}

int16 GfxText32::getTextWidth(const uint index, uint length) const {
	int16 width = 0;

	const char *text = _text.c_str() + index;

	GfxFont *font = _font;

	char currentChar = *text++;
	while (length > 0 && currentChar != '\0') {
		// Control codes are in the format `|<code><value>|`
		if (currentChar == '|') {
			// NOTE: Original engine code changed the global state of the
			// FontMgr here upon encountering any color, alignment, or
			// font control code.
			// To avoid requiring all callers to manually restore these
			// values on every call, we ignore control codes other than
			// font change (since alignment and color do not change the
			// width of characters), and simply update the font pointer
			// on stack instead of the member property font.
			currentChar = *text++;
			--length;

			if (length > 0 && currentChar == 'f') {
				GuiResourceId fontId = 0;
				do {
					currentChar = *text++;
					--length;

					fontId = fontId * 10 + currentChar - '0';
				} while (length > 0 && currentChar >= '0' && currentChar <= '9');

				if (length > 0) {
					font = _cache->getFont(fontId);
				}
			}

			// Forward through any more unknown control character data
			while (length > 0 && currentChar != '|') {
				++text;
				--length;
			}
		} else {
			width += font->getCharWidth(currentChar);
		}

		currentChar = *text++;
		--length;
	}

	return width;
}

int16 GfxText32::getTextWidth(const Common::String &text, const uint index, const uint length) {
	_text = text;
	return scaleUpWidth(getTextWidth(index, length));
}

Common::Rect GfxText32::getTextSize(const Common::String &text, int16 maxWidth, bool doScaling) {
	// NOTE: Like most of the text rendering code, this function was pretty
	// weird in the original engine. The initial result rectangle was actually
	// a 1x1 rectangle (0, 0, 0, 0), which was then "fixed" after the main
	// text size loop finished running by subtracting 1 from the right and
	// bottom edges.

	Common::Rect result;

	int16 scriptWidth = g_sci->_gfxFrameout->getCurrentBuffer().scriptWidth;
	int16 scriptHeight = g_sci->_gfxFrameout->getCurrentBuffer().scriptHeight;

	maxWidth = maxWidth * _scaledWidth / scriptWidth;

	_text = text;

	if (maxWidth >= 0) {
		if (maxWidth == 0) {
			// TODO: This was hardcoded to 192, but guessing
			// that it was originally 60% of the scriptWidth
			// before the compiler took over.
			// Verify this by looking at a game that uses a
			// scriptWidth other than 320, like LSL7
			maxWidth = _scaledWidth * (scriptWidth * 0.6) / scriptWidth;
		}

		result.right = maxWidth;

		int16 textWidth = 0;
		if (_text.size() > 0) {
			const char *rawText = _text.c_str();
			const char *sourceText = rawText;
			uint charIndex = 0;
			uint nextCharIndex = 0;
			while (*rawText != '\0') {
				uint length = getLongest(&nextCharIndex, result.width());
				textWidth = MAX(textWidth, getTextWidth(charIndex, length));
				charIndex = nextCharIndex;
				rawText = sourceText + charIndex;
				// TODO: Due to getLongest and getTextWidth not having side
				// effects, it is possible that the currently loaded font's
				// height is wrong for this line if it was changed inline
				result.bottom += _font->getHeight();
			}
		}

		if (textWidth < maxWidth) {
			result.right = textWidth;
		}
	} else {
		result.right = getTextWidth(0, 10000);
		result.bottom = _font->getHeight() + 1;
	}

	if (doScaling) {
		// NOTE: The original code did some more complex stuff for edge
		// rounding. The right edge was designed to always round down,
		// and the bottom edge was designed to always round up. It seems
		// we are able to get away with simpler rounding, but it is
		// possible that there are still some edge cases here.
		mul(result, Ratio(scriptWidth, _scaledWidth), Ratio(scriptHeight, _scaledHeight));
		result.right += 1;
		result.bottom += 1;
	}

	return result;
}

void GfxText32::erase(const Common::Rect &rect, const bool doScaling) {
	Common::Rect targetRect = doScaling ? rect : scaleRect(rect);

	byte *bitmap = _segMan->getHunkPointer(_bitmap);
	byte *pixels = bitmap + READ_SCI11ENDIAN_UINT32(bitmap + 28);

	// NOTE: There is an extra optimisation within the SCI code to
	// do a single memset if the scaledRect is the same size as
	// the bitmap, not implemented here.
	Buffer buffer(_width, _height, pixels);
	buffer.fillRect(targetRect, _backColor);
}

void GfxText32::disposeTextBitmap(reg_t hunkId) {
	_segMan->freeHunkEntry(hunkId);
}

int16 GfxText32::getStringWidth(const Common::String &text) {
	// TODO: The fact that this double-scales the text makes it
	// seem pretty unlikely that this is ever called in real life
	error("Called weirdo getStringWidth (FontMgr::StringWidth)");
	return scaleUpWidth(getTextWidth(text, 0, 10000));
}

} // End of namespace Sci
