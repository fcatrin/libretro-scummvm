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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 * $URL$
 * $Id$
 *
 */

#ifndef TSAGE_RINGWORLD_SCENES5_H
#define TSAGE_RINGWORLD_SCENES5_H

#include "common/scummsys.h"
#include "tsage/core.h"
#include "tsage/converse.h"
#include "tsage/ringworld_logic.h"

namespace tSage {

class Scene4000: public Scene {
	/* Actions */
	class Action1: public Action {
	public:
		virtual void signal();
	};
	class Action2: public Action {
	public:
		virtual void signal();
	};
	class Action3: public Action {
	public:
		virtual void signal();
	};
	class Action4: public Action {
	public:
		virtual void signal();
	};
	class Action5: public Action {
	public:
		virtual void signal();
	};
	class Action6: public Action {
	public:
		virtual void signal();
	};
	class Action7: public Action {
	public:
		virtual void signal();
	};
	class Action8: public Action {
	public:
		virtual void signal();
	};
	class Action9: public Action {
	public:
		virtual void signal();
	};
	class Action10: public Action {
	public:
		virtual void signal();
	};
	class Action11: public Action {
	public:
		virtual void signal();
	};
	class Action12: public Action {
	public:
		virtual void signal();
	};
	class Action13: public Action {
	public:
		virtual void signal();
	};

	/* Hotspots */
	class Hotspot7: public SceneObject {
	public:
		virtual void doAction(int action);
	};
	class Hotspot8: public SceneObject {
	private:
		int _ctr;
	public:
		virtual void synchronise(Serialiser &s) {
			SceneObject::synchronise(s);
			s.syncAsUint16LE(_ctr);
		}
		virtual void doAction(int action);
	};
	class Hotspot9: public SceneObject {
	public:
		virtual void doAction(int action);
	};
	class Hotspot10: public SceneObject {
	public:
		virtual void doAction(int action);
	};
	class Hotspot12: public SceneObject {
	public:
		virtual void doAction(int action);
	};
	class Hotspot13: public SceneObject {
	public:
		virtual void doAction(int action);
	};
	class Hotspot: public SceneObject {
	public:
		virtual void doAction(int action);
	};
	class Hotspot17: public SceneObject {
	public:
		virtual void doAction(int action);
	};
	class Hotspot18: public SceneObject {
	public:
		virtual void doAction(int action);
	};
	class Hotspot23: public SceneObject {
	public:
		virtual void doAction(int action);
	};
public:
	SequenceManager _sequenceManager1, _sequenceManager2, _sequenceManager3;
	SoundHandler _soundHandler1, _soundHandler2;
	SpeakerQR _speakerQR;
	SpeakerML _speakerML;
	SpeakerMR _speakerMR;
	SpeakerSR _speakerSR;
	SpeakerCHFL _speakerCHFL;
	SpeakerPL _speakerPL;
	SpeakerPText _speakerPText;
	SpeakerQText _speakerQText;
	SpeakerSText _speakerSText;
	SpeakerMText _speakerMText;
	SpeakerCHFR _speakerCHFR;
	SpeakerQL _speakerQL;
	SpeakerCHFText _speakerCHFText;
	SceneObject _hotspot1, _hotspot2, _hotspot3, _hotspot4, _hotspot5, _hotspot6;
	Hotspot7 _hotspot7;
	Hotspot8 _hotspot8;
	Hotspot9 _hotspot9;
	Hotspot10 _hotspot10;
	DisplayHotspot _hotspot11;
	Hotspot12 _hotspot12;
	Hotspot13 _hotspot13;
	Hotspot _hotspot14, _hotspot15, _hotspot16;
	Hotspot17 _hotspot17;
	Hotspot18 _hotspot18;
	DisplayHotspot _hotspot19, _hotspot20, _hotspot21, _hotspot22;
	Hotspot23 _hotspot23;
	DisplayHotspot _hotspot24, _hotspot25, _hotspot26;
	SceneObject _hotspot27;
	Action1 _action1;
	Action2 _action2;
	Action3 _action3;
	Action4 _action4;
	Action5 _action5;
	Action6 _action6;
	Action7 _action7;
	Action8 _action8;
	Action9 _action9;
	Action10 _action10;
	Action11 _action11;
	Action12 _action12;
	Action13 _action13;

	Scene4000();
	virtual void postInit(SceneObjectList *OwnerList = NULL);
	virtual void signal();
	virtual void dispatch();
};

class Scene4010: public Scene {
public:
	SequenceManager _sequenceManager;
	SpeakerQText _speakerQText;
	SpeakerSText _speakerSText;
	SpeakerMText _speakerMText;
	SceneObject _hotspot1, _hotspot2;

	virtual void postInit(SceneObjectList *OwnerList = NULL);	
	virtual void signal();
};

class Scene4025: public Scene {
	/* Custom classes */
	class Peg;

	class Hole: public SceneObject {
	public:
		Peg *_pegPtr;
		int _armStrip;
		Common::Point _newPosition;

		virtual void synchronise(Serialiser &s);
		virtual void doAction(int action);
	};
	class Peg: public SceneObject {
	public:
		int _field88;
		int _armStrip;

		Peg(): SceneObject() { _field88 = 0; _armStrip = 3; }
		virtual void synchronise(Serialiser &s);
		virtual void doAction(int action);
	};

	/* Actions */
	class Action1: public Action {
	public:
		virtual void signal();
	};
	class Action2: public Action {
	public:
		virtual void signal();
	};
	class Action3: public Action {
	public:
		virtual void signal();
	};
public:
	SequenceManager _sequenceManager;
	GfxButton _gfxButton;
	SceneObject _armHotspot;
	Hole _hole1, _hole2, _hole3, _hole4, _hole5;
	Peg _peg1, _peg2, _peg3, _peg4, _peg5;
	Action1 _action1;
	Action2 _action2;
	Action3 _action3;
	Peg *_pegPtr, *_pegPtr2;
	Hole *_holePtr;

	Scene4025();
	virtual void postInit(SceneObjectList *OwnerList = NULL);
	virtual void synchronise(Serialiser &s);
	virtual void remove();
	virtual void signal();
	virtual void process(Event &event);
	virtual void dispatch();
};

} // End of namespace tSage

#endif
