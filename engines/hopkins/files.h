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

#ifndef HOPKINS_FILES_H
#define HOPKINS_FILES_H

#include "common/scummsys.h"
#include "common/hash-str.h"
#include "common/str.h"
#include "common/stream.h"

namespace Hopkins {

class HopkinsEngine;

class FileManager {
private:
	bool TEST_REP(const Common::String &folder, const Common::String &file);
public:
	HopkinsEngine *_vm;
public:
	FileManager();
	void setParent(HopkinsEngine *vm);

	void Chage_Inifile(Common::StringMap &iniParams);
	byte *CHARGE_FICHIER(const Common::String &file);
	void CHARGE_FICHIER2(const Common::String &file, byte *a2);
	void DMESS();
	void DMESS1();
	void bload(const Common::String &file, byte *buf);
	int bload_it(Common::ReadStream &stream, void *buf, size_t nbytes);
	void F_Censure();
	int CONSTRUIT_SYSTEM(const Common::String &file);
	
	/**
	 * Construct a filename based on a suggested folder and filename.
	 * @param folder		Folder to use. May be overriden for animations.
	 * @param file			Filename
	 */
	void CONSTRUIT_FICHIER(const Common::String &folder, const Common::String &file);

	byte *LIBERE_FICHIER(byte *ptr);
	byte *RECHERCHE_CAT(const Common::String &file, int a2);
	Common::String CONSTRUIT_LINUX(const Common::String &file);

	/**
	 * Returns the size of a file. Throws an error if the file can't be found
	 */
	uint32 FLONG(const Common::String &filename);
};

} // End of namespace Hopkins

#endif /* HOPKINS_GLOBALS_H */
