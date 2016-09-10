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

/* VLC code
 *
 * Original copyright note: * Intel Indeo 4 (IV41, IV42, etc.) video decoder for ffmpeg
 * written, produced, and directed by Alan Smithee
 */

#include "image/codecs/indeo/mem.h"

namespace Image {
namespace Indeo {

const uint8 ffReverse[256] = {
	0x00, 0x80, 0x40, 0xC0, 0x20, 0xA0, 0x60, 0xE0, 0x10, 0x90, 0x50, 0xD0, 0x30, 0xB0, 0x70, 0xF0, 
	0x08, 0x88, 0x48, 0xC8, 0x28, 0xA8, 0x68, 0xE8, 0x18, 0x98, 0x58, 0xD8, 0x38, 0xB8, 0x78, 0xF8, 
	0x04, 0x84, 0x44, 0xC4, 0x24, 0xA4, 0x64, 0xE4, 0x14, 0x94, 0x54, 0xD4, 0x34, 0xB4, 0x74, 0xF4, 
	0x0C, 0x8C, 0x4C, 0xCC, 0x2C, 0xAC, 0x6C, 0xEC, 0x1C, 0x9C, 0x5C, 0xDC, 0x3C, 0xBC, 0x7C, 0xFC, 
	0x02, 0x82, 0x42, 0xC2, 0x22, 0xA2, 0x62, 0xE2, 0x12, 0x92, 0x52, 0xD2, 0x32, 0xB2, 0x72, 0xF2, 
	0x0A, 0x8A, 0x4A, 0xCA, 0x2A, 0xAA, 0x6A, 0xEA, 0x1A, 0x9A, 0x5A, 0xDA, 0x3A, 0xBA, 0x7A, 0xFA, 
	0x06, 0x86, 0x46, 0xC6, 0x26, 0xA6, 0x66, 0xE6, 0x16, 0x96, 0x56, 0xD6, 0x36, 0xB6, 0x76, 0xF6, 
	0x0E, 0x8E, 0x4E, 0xCE, 0x2E, 0xAE, 0x6E, 0xEE, 0x1E, 0x9E, 0x5E, 0xDE, 0x3E, 0xBE, 0x7E, 0xFE, 
	0x01, 0x81, 0x41, 0xC1, 0x21, 0xA1, 0x61, 0xE1, 0x11, 0x91, 0x51, 0xD1, 0x31, 0xB1, 0x71, 0xF1, 
	0x09, 0x89, 0x49, 0xC9, 0x29, 0xA9, 0x69, 0xE9, 0x19, 0x99, 0x59, 0xD9, 0x39, 0xB9, 0x79, 0xF9, 
	0x05, 0x85, 0x45, 0xC5, 0x25, 0xA5, 0x65, 0xE5, 0x15, 0x95, 0x55, 0xD5, 0x35, 0xB5, 0x75, 0xF5, 
	0x0D, 0x8D, 0x4D, 0xCD, 0x2D, 0xAD, 0x6D, 0xED, 0x1D, 0x9D, 0x5D, 0xDD, 0x3D, 0xBD, 0x7D, 0xFD, 
	0x03, 0x83, 0x43, 0xC3, 0x23, 0xA3, 0x63, 0xE3, 0x13, 0x93, 0x53, 0xD3, 0x33, 0xB3, 0x73, 0xF3, 
	0x0B, 0x8B, 0x4B, 0xCB, 0x2B, 0xAB, 0x6B, 0xEB, 0x1B, 0x9B, 0x5B, 0xDB, 0x3B, 0xBB, 0x7B, 0xFB, 
	0x07, 0x87, 0x47, 0xC7, 0x27, 0xA7, 0x67, 0xE7, 0x17, 0x97, 0x57, 0xD7, 0x37, 0xB7, 0x77, 0xF7, 
	0x0F, 0x8F, 0x4F, 0xCF, 0x2F, 0xAF, 0x6F, 0xEF, 0x1F, 0x9F, 0x5F, 0xDF, 0x3F, 0xBF, 0x7F, 0xFF, 
};

const uint8 ffZigZagDirect[64] = {
	0,   1,  8, 16,  9,  2,  3, 10,
	17, 24, 32, 25, 18, 11,  4,  5,
	12, 19, 26, 33, 40, 48, 41, 34,
	27, 20, 13,  6,  7, 14, 21, 28,
	35, 42, 49, 56, 57, 50, 43, 36,
	29, 22, 15, 23, 30, 37, 44, 51,
	58, 59, 52, 45, 38, 31, 39, 46,
	53, 60, 61, 54, 47, 55, 62, 63
};

/*------------------------------------------------------------------------*/

/**
 * Multiply two `size_t` values checking for overflow.
 *
 * @param[in]  a,b Operands of multiplication
 * @param[out] r   Pointer to the result of the operation
 * @return 0 on success, AVERROR(EINVAL) on overflow
 */
static inline int avSizeMult(size_t a, size_t b, size_t *r) {
    size_t t = a * b;

    // Hack inspired from glibc: don't try the division if nelem and elsize
    // are both less than sqrt(SIZE_MAX).
    if ((a | b) >= ((size_t)1 << (sizeof(size_t) * 4)) && a && t / a != b)
        return -1;
    *r = t;
    return 0;
}

/*------------------------------------------------------------------------*/

void *avMalloc(size_t size) {
	return malloc(size);
}

void *avMallocZ(size_t size) {
	void *ptr = avMalloc(size);
	if (ptr)
		memset(ptr, 0, size);

	return ptr;
}

void *avMallocArray(size_t nmemb, size_t size) {
    if (!size || nmemb >= MAX_INTEGER / size)
        return nullptr;
    return malloc(nmemb * size);
}

void *avMallocZArray(size_t nmemb, size_t size) {
	if (!size || nmemb >= MAX_INTEGER / size)
		return NULL;

	return avMallocZ(nmemb * size);
}

void avFree(void *ptr) {
	free(ptr);
}

void avFreeP(void *arg) {
	void **ptr = (void **)arg;
	free(*ptr);
	*ptr = nullptr;
}

static void *avRealloc(void *ptr, size_t size) {
	return realloc(ptr, size + !size);
}

void *avReallocF(void *ptr, size_t nelem, size_t elsize) {
	size_t size;
	void *r;

	if (avSizeMult(elsize, nelem, &size)) {
		avFree(ptr);
		return nullptr;
	}
	r = avRealloc(ptr, size);
	if (!r)
		avFree(ptr);

	return r;
}


/**
 * Swap the order of the bytes in the passed value
 */
uint32 bitswap32(uint32 x) {
	return (uint32)ffReverse[x & 0xFF] << 24 |
		(uint32)ffReverse[(x >> 8) & 0xFF] << 16 |
		(uint32)ffReverse[(x >> 16) & 0xFF] << 8 |
		(uint32)ffReverse[x >> 24];
}

/**
 * Reverse "nbits" bits of the value "val" and return the result
 * in the least significant bits.
 */
uint16 invertBits(uint16 val, int nbits) {
	uint16 res;

	if (nbits <= 8) {
		res = ffReverse[val] >> (8 - nbits);
	} else {
		res = ((ffReverse[val & 0xFF] << 8) +
			(ffReverse[val >> 8])) >> (16 - nbits);
	}

	return res;
}

uint8 avClipUint8(int a) {
	if (a&(~0xFF)) return (-a) >> 31;
	else           return a;
}

unsigned avClipUintp2(int a, int p) {
	if (a & ~((1 << p) - 1)) return -a >> 31 & ((1 << p) - 1);
	else                   return  a;
}

} // End of namespace Indeo
} // End of namespace Image
