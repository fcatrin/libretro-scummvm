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

#include "sherlock/people.h"
#include "sherlock/sherlock.h"
#include "sherlock/scalpel/scalpel_people.h"
#include "sherlock/tattoo/tattoo_people.h"

namespace Sherlock {

// Walk speeds
#define MWALK_SPEED 2
#define XWALK_SPEED 4
#define YWALK_SPEED 1

// Characer animation sequences
static const uint8 CHARACTER_SEQUENCES[MAX_HOLMES_SEQUENCE][MAX_FRAME] = {
	{ 29, 1, 2, 3, 4, 5, 6, 7, 0 },		// Walk Right
	{ 22, 1, 2, 3, 4, 5, 6, 7, 0 },		// Walk Down
	{ 29, 1, 2, 3, 4, 5, 6, 7, 0 },		// Walk Left
	{ 15, 1, 2, 3, 4, 5, 6, 7, 0 },		// Walk Up
	{ 42, 1, 2, 3, 4, 5, 0 },			// Goto Stand Right
	{ 47, 1, 2, 3, 4, 5, 0 },			// Goto Stand Down
	{ 42, 1, 2, 3, 4, 5, 0 },			// Goto Stand Left
	{ 36, 1, 0 },						// Goto Stand Up
	{ 8, 1, 2, 3, 4, 5, 6, 7, 0 },		// Walk Up Right
	{ 1, 1, 2, 3, 4, 5, 6, 7, 0 },		// Walk Down Right
	{ 8, 1, 2, 3, 4, 5, 6, 7, 0 },		// Walk Up Left
	{ 1, 1, 2, 3, 4, 5, 6, 7, 0 },		// Walk Down Left
	{ 37, 1, 2, 3, 4, 5, 0 },			// Goto Stand Up Right
	{ 37, 1, 2, 3, 4, 5, 0 },			// Goto Stand Up Left
	{ 52, 1, 2, 3, 4, 0 },				// Goto Stand Down Right
	{ 52, 1, 2, 3, 4, 0 }				// Goto Stand Down Left
};

// Rose Tattoo walk image libraries
// Walk resources within WALK.LIB
const char *const WALK_LIB_NAMES[NUM_IN_WALK_LIB] = {
	"SVGAWALK.VGS",
	"COATWALK.VGS",
	"WATSON.VGS",
	"NOHAT.VGS",
	"TUPRIGHT.VGS",
	"TRIGHT.VGS",
	"TDOWNRG.VGS",
	"TWUPRIGH.VGS",
	"TWRIGHT.VGS",
	"TWDOWNRG.VGS"
};

/*----------------------------------------------------------------*/

Person::Person() : Sprite(), _walkLoaded(false), _npcIndex(0), _npcStack(0), _npcPause(false)  {
	Common::fill(&_npcPath[0], &_npcPath[MAX_NPC_PATH], 0);
	_tempX = _tempScaleVal = 0;
	_updateNPCPath = false;
	_npcIndex = 0;
	_npcStack = 0;
	_savedNpcSequence = 0;
	_savedNpcFrame = 0;
	_updateNPCPath = false;
	_npcPause = false;
}

void Person::clearNPC() {
	Common::fill(&_npcPath[0], &_npcPath[MAX_NPC_PATH], 0);
	_npcIndex = _npcStack = 0;
	_npcName = "";
}

void Person::updateNPC() {
	// TODO
}

/*----------------------------------------------------------------*/

People *People::init(SherlockEngine *vm) {
	if (vm->getGameID() == GType_SerratedScalpel)
		return new Scalpel::ScalpelPeople(vm);
	else
		return new Tattoo::TattooPeople(vm);
}

People::People(SherlockEngine *vm) : _vm(vm), _player(_data[0]) {
	_holmesOn = true;
	_oldWalkSequence = -1;
	_allowWalkAbort = false;
	_portraitLoaded = false;
	_portraitsOn = true;
	_clearingThePortrait = false;
	_srcZone = _destZone = 0;
	_talkPics = nullptr;
	_portraitSide = 0;
	_speakerFlip = false;
	_holmesFlip = false;
	_holmesQuotient = 0;
	_hSavedPos = Point32(-1, -1);
	_hSavedFacing = -1;
	_forceWalkReload = false;
	_useWalkLib = false;
	_walkControl = 0;

	_portrait._sequences = new byte[32];
}

People::~People() {
	for (int idx = 0; idx < MAX_CHARACTERS; ++idx) {
		if (_data[idx]._walkLoaded)
			delete _data[PLAYER]._images;
	}

	delete _talkPics;
	delete[] _portrait._sequences;
}

void People::reset() {
	_data[0]._description = "Sherlock Holmes!";

	// Note: Serrated Scalpel only uses a single Person slot for Sherlock.. Watson is handled by scene sprites
	int count = IS_SERRATED_SCALPEL ? 1 : MAX_CHARACTERS;
	for (int idx = 0; idx < count; ++idx) {
		Sprite &p = _data[idx];

		p._type = (idx == 0) ? CHARACTER : INVALID;
		if (IS_SERRATED_SCALPEL)
			p._position = Point32(100 * FIXED_INT_MULTIPLIER, 110 * FIXED_INT_MULTIPLIER);
		else
			p._position = Point32(36 * FIXED_INT_MULTIPLIER, 29 * FIXED_INT_MULTIPLIER);

		p._sequenceNumber = Scalpel::STOP_DOWNRIGHT;
		p._imageFrame = nullptr;
		p._frameNumber = 1;
		p._delta = Point32(0, 0);
		p._oldPosition = Common::Point(0, 0);
		p._oldSize = Common::Point(0, 0);
		p._misc = 0;
		p._walkCount = 0;
		p._pickUp = "";
		p._allow = 0;
		p._noShapeSize = Common::Point(0, 0);
		p._goto = Common::Point(0, 0);
		p._status = 0;
		p._seqTo = 0;
		p._seqCounter = p._seqCounter2 = 0;
		p._seqStack = 0;
		p._gotoSeq = p._talkSeq = 0;
		p._restoreSlot = 0;
		p._startSeq = 0;
		p._altImages = nullptr;
		p._altSeq = 0;
		p._centerWalk = true;
		p._adjust = Common::Point(0, 0);

		// Load the default walk sequences
		p._oldWalkSequence = -1;
		p._walkSequences.clear();
		if (IS_SERRATED_SCALPEL) {
			p._walkSequences.resize(MAX_HOLMES_SEQUENCE);
			for (int seqIdx = 0; seqIdx < MAX_HOLMES_SEQUENCE; ++seqIdx) {
				p._walkSequences[seqIdx]._sequences.clear();

				const byte *pSrc = &CHARACTER_SEQUENCES[seqIdx][0];
				do {
					p._walkSequences[seqIdx]._sequences.push_back(*pSrc);
				} while (*pSrc++);
			}
		}
	}

	// Reset any walk path in progress when Sherlock leaves scenes
	_walkTo.clear();
}

bool People::loadWalk() {
	Resources &res = *_vm->_res;
	bool result = false;

	if (IS_SERRATED_SCALPEL) {
		if (_data[PLAYER]._walkLoaded) {
			return false;
		} else {
			_data[PLAYER]._images = new ImageFile("walk.vgs");
			_data[PLAYER].setImageFrame();
			_data[PLAYER]._walkLoaded = true;

			result = true;
		}
	} else {
		for (int idx = 0; idx < MAX_CHARACTERS; ++idx) {
			if (!_data[idx]._walkLoaded && (_data[idx]._type == CHARACTER || _data[idx]._type == HIDDEN_CHARACTER)) {
				if (_data[idx]._type == HIDDEN_CHARACTER)
					_data[idx]._type = INVALID;

				// See if this is one of the more used Walk Graphics stored in WALK.LIB
				for (int libNum = 0; libNum < NUM_IN_WALK_LIB; ++libNum) {
					if (!_data[0]._walkVGSName.compareToIgnoreCase(WALK_LIB_NAMES[libNum])) {
						_useWalkLib = true;
						break;
					}
				}

				// Load the images for the character
				_data[idx]._images = new ImageFile(_data[idx]._walkVGSName, false);
				_data[idx]._numFrames = _data[idx]._images->size();

				// Load walk sequence data
				Common::String fname = Common::String(_data[idx]._walkVGSName.c_str(), strchr(_data[idx]._walkVGSName.c_str(), '.'));
				fname += ".SEQ";

				// Load the walk sequence data
				Common::SeekableReadStream *stream = res.load(fname, _useWalkLib ? "walk.lib" : "vgs.lib");
				
				_data[idx]._walkSequences.resize(stream->readByte());

				for (uint seqNum = 0; seqNum < _data[idx]._walkSequences.size(); ++seqNum)
					_data[idx]._walkSequences[seqNum].load(*stream);

				// Close the sequences resource
				delete stream;
				_useWalkLib = false;

				_data[idx]._frameNumber = 0;
				_data[idx].setImageFrame();

				// Set the stop Frames pointers
				for (int dirNum = 0; dirNum < 8; ++dirNum) {
					int count = 0;
					while (_data[idx]._walkSequences[dirNum + 8][count] != 0)
						++count;
					count += 2;
					count = _data[idx]._walkSequences[dirNum + 8][count] - 1;
					_data[idx]._stopFrames[dirNum] = &(*_data[idx]._images)[count];
				}

				result = true;
				_data[idx]._walkLoaded = true;
			} else if (_data[idx]._type != CHARACTER) {
				_data[idx]._walkLoaded = false;
			}
		}
	}

	_forceWalkReload = false;
	return result;
}

bool People::freeWalk() {
	bool result = false;

	for (int idx = 0; idx < MAX_CHARACTERS; ++idx) {
		if (_data[idx]._walkLoaded) {
			delete _data[idx]._images;
			_data[idx]._images = nullptr;
			
			_data[idx]._walkLoaded = false;
			result = true;
		}
	}

	return result;
}

void People::setWalking() {
	Map &map = *_vm->_map;
	Scene &scene = *_vm->_scene;
	int oldDirection, oldFrame;
	Common::Point speed, delta;

	// Flag that player has now walked in the scene
	scene._walkedInScene = true;

	// Stop any previous walking, since a new dest is being set
	_player._walkCount = 0;
	oldDirection = _player._sequenceNumber;
	oldFrame = _player._frameNumber;

	// Set speed to use horizontal and vertical movement
	if (map._active) {
		speed = Common::Point(MWALK_SPEED, MWALK_SPEED);
	} else {
		speed = Common::Point(XWALK_SPEED, YWALK_SPEED);
	}

	// If the player is already close to the given destination that no
	// walking is needed, move to the next straight line segment in the
	// overall walking route, if there is one
	for (;;) {
		// Since we want the player to be centered on the destination they
		// clicked, but characters draw positions start at their left, move
		// the destination half the character width to draw him centered
		int temp;
		if (_walkDest.x >= (temp = _player._imageFrame->_frame.w / 2))
			_walkDest.x -= temp;

		delta = Common::Point(
			ABS(_player._position.x / FIXED_INT_MULTIPLIER - _walkDest.x),
			ABS(_player._position.y / FIXED_INT_MULTIPLIER - _walkDest.y)
		);

		// If we're ready to move a sufficient distance, that's it. Otherwise,
		// move onto the next portion of the walk path, if there is one
		if ((delta.x > 3 || delta.y > 0) || _walkTo.empty())
			break;

		// Pop next walk segment off the walk route stack
		_walkDest = _walkTo.pop();
	}

	// If a sufficient move is being done, then start the move
	if (delta.x > 3 || delta.y) {
		// See whether the major movement is horizontal or vertical
		if (delta.x >= delta.y) {
			// Set the initial frame sequence for the left and right, as well
			// as setting the delta x depending on direction
			if (_walkDest.x < (_player._position.x / FIXED_INT_MULTIPLIER)) {
				_player._sequenceNumber = (map._active ? (int)MAP_LEFT : (int)Scalpel::WALK_LEFT);
				_player._delta.x = speed.x * -FIXED_INT_MULTIPLIER;
			} else {
				_player._sequenceNumber = (map._active ? (int)MAP_RIGHT : (int)Scalpel::WALK_RIGHT);
				_player._delta.x = speed.x * FIXED_INT_MULTIPLIER;
			}

			// See if the x delta is too small to be divided by the speed, since
			// this would cause a divide by zero error
			if (delta.x >= speed.x) {
				// Det the delta y
				_player._delta.y = (delta.y * FIXED_INT_MULTIPLIER) / (delta.x / speed.x);
				if (_walkDest.y < (_player._position.y / FIXED_INT_MULTIPLIER))
					_player._delta.y = -_player._delta.y;

				// Set how many times we should add the delta to the player's position
				_player._walkCount = delta.x / speed.x;
			} else {
				// The delta x was less than the speed (ie. we're really close to
				// the destination). So set delta to 0 so the player won't move
				_player._delta = Point32(0, 0);
				_player._position = Point32(_walkDest.x * FIXED_INT_MULTIPLIER, _walkDest.y * FIXED_INT_MULTIPLIER);
assert(_player._position.y >= 10000);/***DEBUG****/
				_player._walkCount = 1;
			}

			// See if the sequence needs to be changed for diagonal walking
			if (_player._delta.y > 150) {
				if (!map._active) {
					switch (_player._sequenceNumber) {
					case Scalpel::WALK_LEFT:
						_player._sequenceNumber = Scalpel::WALK_DOWNLEFT;
						break;
					case Scalpel::WALK_RIGHT:
						_player._sequenceNumber = Scalpel::WALK_DOWNRIGHT;
						break;
					}
				}
			} else if (_player._delta.y < -150) {
				if (!map._active) {
					switch (_player._sequenceNumber) {
					case Scalpel::WALK_LEFT:
						_player._sequenceNumber = Scalpel::WALK_UPLEFT;
						break;
					case Scalpel::WALK_RIGHT:
						_player._sequenceNumber = Scalpel::WALK_UPRIGHT;
						break;
					}
				}
			}
		} else {
			// Major movement is vertical, so set the sequence for up and down,
			// and set the delta Y depending on the direction
			if (_walkDest.y < (_player._position.y / FIXED_INT_MULTIPLIER)) {
				_player._sequenceNumber = Scalpel::WALK_UP;
				_player._delta.y = speed.y * -FIXED_INT_MULTIPLIER;
			} else {
				_player._sequenceNumber = Scalpel::WALK_DOWN;
				_player._delta.y = speed.y * FIXED_INT_MULTIPLIER;
			}

			// If we're on the overhead map, set the sequence so we keep moving
			// in the same direction
			if (map._active)
				_player._sequenceNumber = (oldDirection == -1) ? MAP_RIGHT : oldDirection;

			// Set the delta x
			_player._delta.x = (delta.x * FIXED_INT_MULTIPLIER) / (delta.y / speed.y);
			if (_walkDest.x < (_player._position.x / FIXED_INT_MULTIPLIER))
				_player._delta.x = -_player._delta.x;

			_player._walkCount = delta.y / speed.y;
		}
	}

	// See if the new walk sequence is the same as the old. If it's a new one,
	// we need to reset the frame number to zero so it's animation starts at
	// it's beginning. Otherwise, if it's the same sequence, we can leave it
	// as is, so it keeps the animation going at wherever it was up to
	if (_player._sequenceNumber != _oldWalkSequence)
		_player._frameNumber = 0;
	_oldWalkSequence = _player._sequenceNumber;

	if (!_player._walkCount)
		gotoStand(_player);

	// If the sequence is the same as when we started, then Holmes was
	// standing still and we're trying to re-stand him, so reset Holmes'
	// rame to the old frame number from before it was reset to 0
	if (_player._sequenceNumber == oldDirection)
		_player._frameNumber = oldFrame;
}

void People::gotoStand(Sprite &sprite) {
	Map &map = *_vm->_map;
	_walkTo.clear();
	sprite._walkCount = 0;

	switch (sprite._sequenceNumber) {
	case Scalpel::WALK_UP:
		sprite._sequenceNumber = Scalpel::STOP_UP;
		break;
	case Scalpel::WALK_DOWN:
		sprite._sequenceNumber = Scalpel::STOP_DOWN;
		break;
	case Scalpel::TALK_LEFT:
	case Scalpel::WALK_LEFT:
		sprite._sequenceNumber = Scalpel::STOP_LEFT;
		break;
	case Scalpel::TALK_RIGHT:
	case Scalpel::WALK_RIGHT:
		sprite._sequenceNumber = Scalpel::STOP_RIGHT;
		break;
	case Scalpel::WALK_UPRIGHT:
		sprite._sequenceNumber = Scalpel::STOP_UPRIGHT;
		break;
	case Scalpel::WALK_UPLEFT:
		sprite._sequenceNumber = Scalpel::STOP_UPLEFT;
		break;
	case Scalpel::WALK_DOWNRIGHT:
		sprite._sequenceNumber = Scalpel::STOP_DOWNRIGHT;
		break;
	case Scalpel::WALK_DOWNLEFT:
		sprite._sequenceNumber = Scalpel::STOP_DOWNLEFT;
		break;
	default:
		break;
	}

	// Only restart frame at 0 if the sequence number has changed
	if (_oldWalkSequence != -1 || sprite._sequenceNumber == Scalpel::STOP_UP)
		sprite._frameNumber = 0;

	if (map._active) {
		sprite._sequenceNumber = 0;
		_player._position.x = (map[map._charPoint].x - 6) * FIXED_INT_MULTIPLIER;
		_player._position.y = (map[map._charPoint].y + 10) * FIXED_INT_MULTIPLIER;
	}

	_oldWalkSequence = -1;
	_allowWalkAbort = true;
}

void People::walkToCoords(const Point32 &destPos, int destDir) {
	Events &events = *_vm->_events;
	Scene &scene = *_vm->_scene;
	Talk &talk = *_vm->_talk;

	CursorId oldCursor = events.getCursor();
	events.setCursor(WAIT);

	_walkDest = Common::Point(destPos.x / FIXED_INT_MULTIPLIER + 10, destPos.y / FIXED_INT_MULTIPLIER);
	_allowWalkAbort = true;
	goAllTheWay();

	// Keep calling doBgAnim until the walk is done
	do {
		events.pollEventsAndWait();
		scene.doBgAnim();
	} while (!_vm->shouldQuit() && _player._walkCount);

	if (!talk._talkToAbort) {
		// Put player exactly on destination position, and set direction
		_player._position = destPos;
assert(_player._position.y >= 10000);/***DEBUG****/

		_player._sequenceNumber = destDir;
		gotoStand(_player);

		// Draw Holmes facing the new direction
		scene.doBgAnim();

		if (!talk._talkToAbort)
			events.setCursor(oldCursor);
	}
}

void People::goAllTheWay() {
	Scene &scene = *_vm->_scene;
	Common::Point srcPt(_player._position.x / FIXED_INT_MULTIPLIER + _player.frameWidth() / 2,
		_player._position.y / FIXED_INT_MULTIPLIER);

	// Get the zone the player is currently in
	_srcZone = scene.whichZone(srcPt);
	if (_srcZone == -1)
		_srcZone = scene.closestZone(srcPt);

	// Get the zone of the destination
	_destZone = scene.whichZone(_walkDest);
	if (_destZone == -1) {
		_destZone = scene.closestZone(_walkDest);

		// The destination isn't in a zone
		if (_walkDest.x >= (SHERLOCK_SCREEN_WIDTH - 1))
			_walkDest.x = SHERLOCK_SCREEN_WIDTH - 2;

		// Trace a line between the centroid of the found closest zone to
		// the destination, to find the point at which the zone will be left
		const Common::Rect &destRect = scene._zones[_destZone];
		const Common::Point destCenter((destRect.left + destRect.right) / 2,
			(destRect.top + destRect.bottom) / 2);
		const Common::Point delta = _walkDest - destCenter;
		Point32 pt(destCenter.x * FIXED_INT_MULTIPLIER, destCenter.y * FIXED_INT_MULTIPLIER);

		// Move along the line until the zone is left
		do {
			pt += delta;
		} while (destRect.contains(pt.x / FIXED_INT_MULTIPLIER, pt.y / FIXED_INT_MULTIPLIER));

		// Set the new walk destination to the last point that was in the
		// zone just before it was left
		_walkDest = Common::Point((pt.x - delta.x * 2) / FIXED_INT_MULTIPLIER,
			(pt.y - delta.y * 2) / FIXED_INT_MULTIPLIER);
	}

	// Only do a walk if both zones are acceptable
	if (_srcZone == -2 || _destZone == -2)
		return;

	// If the start and dest zones are the same, walk directly to the dest point
	if (_srcZone == _destZone) {
		setWalking();
	} else {
		// Otherwise a path needs to be formed from the path information
		int i = scene._walkDirectory[_srcZone][_destZone];

		// See if we need to use a reverse path
		if (i == -1)
			i = scene._walkDirectory[_destZone][_srcZone];

		int count = scene._walkData[i];
		++i;

		// See how many points there are between the src and dest zones
		if (!count || count == -1) {
			// There are none, so just walk to the new zone
			setWalking();
		} else {
			// There are points, so set up a multi-step path between points
			// to reach the given destination
			_walkTo.clear();

			if (scene._walkDirectory[_srcZone][_destZone] != -1) {
				i += 3 * (count - 1);
				for (int idx = 0; idx < count; ++idx, i -= 3) {
					_walkTo.push(Common::Point(READ_LE_UINT16(&scene._walkData[i]),
						scene._walkData[i + 2]));
				}
			} else {
				for (int idx = 0; idx < count; ++idx, i += 3) {
					_walkTo.push(Common::Point(READ_LE_UINT16(&scene._walkData[i]), scene._walkData[i + 2]));
				}
			}

			// Final position
			_walkTo.push(_walkDest);

			// Start walking
			_walkDest = _walkTo.pop();
			setWalking();
		}
	}
}

int People::findSpeaker(int speaker) {
	Scene &scene = *_vm->_scene;
	const char *portrait = _characters[speaker]._portrait;

	for (int idx = 0; idx < (int)scene._bgShapes.size(); ++idx) {
		Object &obj = scene._bgShapes[idx];

		if (obj._type == ACTIVE_BG_SHAPE) {
			Common::String name(obj._name.c_str(), obj._name.c_str() + 4);

			if (name.equalsIgnoreCase(portrait)
				&& obj._name[4] >= '0' && obj._name[4] <= '9')
				return idx;
		}
	}

	// Fallback in Rose Tattoo
	if (IS_ROSE_TATTOO) {
		bool flag = _vm->readFlags(76);
		
		if (_data[0]._type == CHARACTER && ((speaker == 0 && flag) || (speaker == 1 && !flag)))
			return -1;

		for (uint idx = 1; idx < MAX_CHARACTERS; ++idx) {
			if (_data[idx]._type == CHARACTER) {
				Common::String name(_data[idx]._name.c_str(), _data[idx]._name.c_str() + 4);

				if (name.equalsIgnoreCase(portrait) && _data[idx]._npcName[4] >= '0' && _data[idx]._npcName[4] <= '9')
					return idx + 256;
			}
		}
	}

	return -1;
}

void People::clearTalking() {
	Scene &scene = *_vm->_scene;
	Screen &screen = *_vm->_screen;
	Talk &talk = *_vm->_talk;

	if (_portraitsOn) {
		Common::Point pt = _portrait._position;
		int width, height;
		_portrait._imageFrame = _talkPics ? &(*_talkPics)[0] : (ImageFrame *)nullptr;

		// Flag portrait for removal, and save the size of the frame to use erasing it
		_portrait._type = REMOVE;
		_portrait._delta.x = width = _portrait.frameWidth();
		_portrait._delta.y = height = _portrait.frameHeight();

		delete _talkPics;
		_talkPics = nullptr;

		// Flag to let the talk code know not to interrupt on the next doBgAnim
		_clearingThePortrait = true;
		scene.doBgAnim();
		_clearingThePortrait = false;

		screen.slamArea(pt.x, pt.y, width, height);

		if (!talk._talkToAbort)
			_portraitLoaded = false;
	}
}

void People::synchronize(Common::Serializer &s) {
	s.syncAsByte(_holmesOn);

	if (IS_SERRATED_SCALPEL) {
		s.syncAsSint16LE(_player._position.x);
		s.syncAsSint16LE(_player._position.y);
		s.syncAsSint16LE(_player._sequenceNumber);
	} else {
		for (int idx = 0; idx < MAX_CHARACTERS; ++idx) {
			Person &p = _data[idx];
			s.syncAsSint16LE(p._position.x);
			s.syncAsSint16LE(p._position.y);
			s.syncAsSint16LE(p._sequenceNumber);
			s.syncAsSint16LE(p._type);
			s.syncString(p._walkVGSName);
			s.syncString(p._description);
			s.syncString(p._examine);
		}
	}

	s.syncAsSint16LE(_holmesQuotient);

	if (s.isLoading()) {
		_hSavedPos = _player._position;
		_hSavedFacing = _player._sequenceNumber;
	}
}

} // End of namespace Sherlock
