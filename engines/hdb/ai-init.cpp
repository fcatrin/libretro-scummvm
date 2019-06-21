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

#include "hdb/hdb.h"

namespace HDB {

/*
	Comment from Original:
	these arrays list each of the game's actor's possible states and
	which graphics to load for them.
*/

AIStateDef none[] = {
	{ STATE_ENDSTATES, "" }
};

AIStateDef guy[] = {
	{ STATE_BLINK,		"ent_guy_blink" },
	{ STATE_STANDDOWN,	"ent_guy_standdown" },
	{ STATE_STANDUP,	"ent_guy_standup" },
	{ STATE_STANDLEFT,	"ent_guy_standleft" },
	{ STATE_STANDRIGHT,	"ent_guy_standright" },
	{ STATE_MOVEDOWN,	"ent_guy_walkdown" },
	{ STATE_MOVEUP,		"ent_guy_walkup" },
	{ STATE_MOVELEFT,	"ent_guy_walkleft" },
	{ STATE_MOVERIGHT,	"ent_guy_walkright" },
	{ STATE_PUSHDOWN,	"ent_guy_pushdown" },
	{ STATE_PUSHUP,		"ent_guy_pushup" },
	{ STATE_PUSHLEFT,	"ent_guy_pushleft" },
	{ STATE_PUSHRIGHT,	"ent_guy_pushright" },
	{ STATE_GRABDOWN,	"ent_guy_getdown" },
	{ STATE_GRABUP,		"ent_guy_getup" },
	{ STATE_GRABLEFT,	"ent_guy_getleft" },
	{ STATE_GRABRIGHT,	"ent_guy_getright" },
	{ STATE_PLUMMET,		"ent_guy_plummet" },
	{ STATE_ATK_STUN_DOWN,	"ent_guy_stundown" },
	{ STATE_ATK_STUN_UP,	"ent_guy_stunup" },
	{ STATE_ATK_STUN_LEFT,	"ent_guy_stunleft" },
	{ STATE_ATK_STUN_RIGHT,	"ent_guy_stunright" },
	{ STATE_ATK_SLUG_DOWN,	"ent_guy_slingdown" },
	{ STATE_ATK_SLUG_UP,	"ent_guy_slingup" },
	{ STATE_ATK_SLUG_LEFT,	"ent_guy_slingleft" },
	{ STATE_ATK_SLUG_RIGHT,	"ent_guy_slingright" },
	{ STATE_DYING,		"ent_guy_die" },
	{ STATE_HORRIBLE1,	"ent_guy_horrible1" },
	{ STATE_HORRIBLE2,	"ent_guy_horrible2" },
	{ STATE_HORRIBLE3,	"ent_guy_horrible3" },
	{ STATE_HORRIBLE4,	"ent_guy_horrible4" },
	{ STATE_GOODJOB,	"ent_guy_goodjob" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef gemAttack[] = {
	{ STATE_MOVEDOWN, "ent_gem_white_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef slugAttack[] = {
	{ STATE_ENDSTATES, "" }
};

AIStateDef dolly[] = {
	{ STATE_MOVEDOWN,	"ent_sergeant_walkdown" },
	{ STATE_MOVEUP,		"ent_sergeant_walkup" },
	{ STATE_MOVELEFT,	"ent_sergeant_walkleft" },
	{ STATE_MOVERIGHT,	"ent_sergeant_walkright" },
	{ STATE_DOLLYUSERIGHT, "ent_sergeant_userright" },
	{ STATE_KISSRIGHT,	"ent_sergeant_kissright" },
	{ STATE_KISSLEFT,	"ent_sergeant_kissleft" },
	{ STATE_ANGRY,		"ent_sergeant_angry"},
	{ STATE_LAUGH,		"ent_sergeant_laugh" },
	{ STATE_PANIC,		"ent_sergeant_panic" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef sergeant[] = {
	{ STATE_STANDDOWN,	"ent_sergeant_standdown" },
	{ STATE_STANDUP,	"ent_sergeant_standup" },
	{ STATE_STANDLEFT,	"ent_sergeant_standleft" },
	{ STATE_STANDRIGHT,	"ent_sergeant_standright" },
	{ STATE_YELL,		"ent_sergeant_yell" },
	{ STATE_MOVEDOWN,	"ent_sergeant_walkdown" },
	{ STATE_MOVEUP,		"ent_sergeant_walkup" },
	{ STATE_MOVELEFT,	"ent_sergeant_walkleft" },
	{ STATE_MOVERIGHT,	"ent_sergeant_walkright" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef spacedude[] = {
	{ STATE_MOVEDOWN,	"ent_spacedude_walkdown" },
	{ STATE_MOVEUP,		"ent_spacedude_walkup" },
	{ STATE_MOVELEFT,	"ent_spacedude_walkleft" },
	{ STATE_MOVERIGHT,	"ent_spacedude_walkright" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef chicken[] = {
	{ STATE_STANDDOWN,	"ent_chicken_standdown" },
	{ STATE_STANDUP,		"ent_chicken_standup" },
	{ STATE_STANDLEFT,	"ent_chicken_standleft" },
	{ STATE_STANDRIGHT,	"ent_chicken_standright" },
	{ STATE_MOVEDOWN,	"ent_chicken_walkdown" },
	{ STATE_MOVEUP,		"ent_chicken_walkup" },
	{ STATE_MOVELEFT,	"ent_chicken_walkleft" },
	{ STATE_MOVERIGHT,	"ent_chicken_walkright" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef vortexian[] = {
	{ STATE_STANDDOWN, "ent_vortexian_standdown" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef maintBot[] = {
	{ STATE_STANDDOWN,	"ent_maintbot_standdown" },
	{ STATE_STANDUP,	"ent_maintbot_standup" },
	{ STATE_STANDLEFT,	"ent_maintbot_standleft" },
	{ STATE_STANDRIGHT,	"ent_maintbot_standright" },
	{ STATE_MOVEDOWN,	"ent_maintbot_walkdown" },
	{ STATE_MOVEUP,		"ent_maintbot_walkup" },
	{ STATE_MOVELEFT,	"ent_maintbot_walkleft" },
	{ STATE_MOVERIGHT,	"ent_maintbot_walkright" },
	{ STATE_USEDOWN,	"ent_maintbot_usedown" },
	{ STATE_USEUP,		"ent_maintbot_useup" },
	{ STATE_USELEFT,	"ent_maintbot_useleft" },
	{ STATE_USERIGHT,	"ent_maintbot_useright" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef scientist[] = {
	{ STATE_BLINK,		"ent_scientist_blink" },
	{ STATE_STANDDOWN,	"ent_scientist_standdown" },
	{ STATE_STANDUP,	"ent_scientist_standup" },
	{ STATE_STANDLEFT,	"ent_scientist_standleft" },
	{ STATE_STANDRIGHT,	"ent_scientist_standright" },
	{ STATE_MOVEDOWN,	"ent_scientist_walkdown" },
	{ STATE_MOVEUP,		"ent_scientist_walkup" },
	{ STATE_MOVELEFT,	"ent_scientist_walkleft" },
	{ STATE_MOVERIGHT,	"ent_scientist_walkright" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef worker[] = {
	{ STATE_BLINK,		"ent_worker_blink" },
	{ STATE_STANDDOWN,	"ent_worker_standdown" },
	{ STATE_STANDUP,	"ent_worker_standup" },
	{ STATE_STANDLEFT,	"ent_worker_standleft" },
	{ STATE_STANDRIGHT,	"ent_worker_standright" },
	{ STATE_MOVEDOWN,	"ent_worker_walkdown" },
	{ STATE_MOVEUP,		"ent_worker_walkup" },
	{ STATE_MOVELEFT,	"ent_worker_walkleft" },
	{ STATE_MOVERIGHT,	"ent_worker_walkright" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef deadWorker[] = {
	{ STATE_STANDDOWN, "ent_dead_worker_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef accountant[] = {
	{ STATE_STANDDOWN,	"ent_accountant_standdown" },
	{ STATE_STANDUP,	"ent_accountant_standup" },
	{ STATE_STANDLEFT,	"ent_accountant_standleft" },
	{ STATE_STANDRIGHT,	"ent_accountant_standright" },
	{ STATE_ENDSTATES, "" }
};

// Enemies

AIStateDef pushBot[] = {
	{ STATE_MOVEDOWN,	"ent_pushbot_walkdown" },
	{ STATE_MOVEUP,		"ent_pushbot_walkup" },
	{ STATE_MOVELEFT,	"ent_pushbot_walkleft" },
	{ STATE_MOVERIGHT,	"ent_pushbot_walkright" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef rightBot[] = {
	{ STATE_MOVEDOWN,	"ent_rightbot_walkdown" },
	{ STATE_MOVEUP,		"ent_rightbot_walkup" },
	{ STATE_MOVELEFT,	"ent_rightbot_walkleft" },
	{ STATE_MOVERIGHT,	"ent_rightbot_walkright" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef omniBot[] = {
	{ STATE_MOVEDOWN,	"ent_omnibot_walkdown" },
	{ STATE_MOVEUP,		"ent_omnibot_walkup" },
	{ STATE_MOVELEFT,	"ent_omnibot_walkleft" },
	{ STATE_MOVERIGHT,	"ent_omnibot_walkright" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef laser[] = {
	{ STATE_STANDDOWN,	"ent_laser_down" },
	{ STATE_STANDUP,	"ent_laser_up" },
	{ STATE_STANDLEFT,	"ent_laser_left" },
	{ STATE_STANDRIGHT,	"ent_laser_right" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef diverter[] = {
	{ STATE_DIVERTER_BL,	"ent_deflectorbl_sit" },
	{ STATE_DIVERTER_BR,	"ent_deflectorbr_sit" },
	{ STATE_DIVERTER_TL,	"ent_deflectortl_sit" },
	{ STATE_DIVERTER_TR,	"ent_deflectortr_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef turnBot[] = {
	{ STATE_MOVEDOWN,	"ent_turnbot_walkdown" },
	{ STATE_MOVEUP,		"ent_turnbot_walkup" },
	{ STATE_MOVELEFT,	"ent_turnbot_walkleft" },
	{ STATE_MOVERIGHT,	"ent_turnbot_walkright" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef deadEye[] = {
	{ STATE_MOVEDOWN,	"ent_deadeye_walkdown" },
	{ STATE_MOVEUP,		"ent_deadeye_walkup" },
	{ STATE_MOVELEFT,	"ent_deadeye_walkleft" },
	{ STATE_MOVERIGHT,	"ent_deadeye_walkright" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef meerkat[] = {
	{ STATE_MEER_MOVE,		"ent_meerkat_dirtmove" },
	{ STATE_MEER_APPEAR,	"ent_meerkat_appear" },
	{ STATE_MEER_BITE,		"ent_meerkat_bite" },
	{ STATE_MEER_DISAPPEAR, "ent_meerkat_disappear" },
	{ STATE_MEER_LOOK,		"ent_meerkat_look" },
};

AIStateDef goodFairy[] = {
	{ STATE_MOVEDOWN,	"ent_goodfairy_walkdown" },
	{ STATE_MOVEUP,		"ent_goodfairy_walkup" },
	{ STATE_MOVELEFT,	"ent_goodfairy_walkleft" },
	{ STATE_MOVERIGHT,	"ent_goodfairy_walkright" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef badFairy[] = {
	{ STATE_MOVEDOWN,	"ent_badfairy_walkdown" },
	{ STATE_MOVEUP,		"ent_badfairy_walkup" },
	{ STATE_MOVELEFT,	"ent_badfairy_walkleft" },
	{ STATE_MOVERIGHT,	"ent_badfairy_walkright" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef gatePuddle[] = {
	{ STATE_MOVEDOWN, "ent_gatepuddle_standdown"},
	{ STATE_ENDSTATES, "" }
};

AIStateDef icePuff[] = {
	{ STATE_ICEP_PEEK,			"ent_icepuff_peek" },
	{ STATE_ICEP_APPEAR,		"ent_icepuff_appear" },
	{ STATE_ICEP_THROWDOWN,		"ent_icepuff_throwdown" },
	{ STATE_ICEP_THROWRIGHT,	"ent_icepuff_throwright" },
	{ STATE_ICEP_THROWLEFT,		"ent_icepuff_throwleft" },
	{ STATE_ICEP_DISAPPEAR,		"ent_icepuff_disappear" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef buzzfly[] = {
	{ STATE_MOVEDOWN,	"ent_buzzfly_walkdown" },
	{ STATE_MOVEUP,		"ent_buzzfly_walkup" },
	{ STATE_MOVELEFT,	"ent_buzzfly_walkleft" },
	{ STATE_MOVERIGHT,	"ent_buzzfly_walkright" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef fatFrog[] = {
	{ STATE_STANDDOWN,	"ent_fatfrog_standdown" },
	{ STATE_STANDLEFT,	"ent_fatfrog_standleft" },
	{ STATE_STANDRIGHT,	"ent_fatfrog_standright" },
	{ STATE_LICKDOWN,	"ent_fatfrog_lickdown" },
	{ STATE_LICKLEFT,	"ent_fatfrog_lickleft" },
	{ STATE_LICKRIGHT,	"ent_fatfrog_lickright" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef dragon[] = {
	{ STATE_ENDSTATES, "" }
};

AIStateDef omniBotMissile[] = {
	{ STATE_MOVEDOWN, "ent_omnibot_missile"},
	{ STATE_ENDSTATES, "" }
};

AIStateDef fourFirer[] = {
	{ STATE_STANDDOWN,	"ent_four_laser_down" },
	{ STATE_STANDUP,	"ent_four_laser_up" },
	{ STATE_STANDLEFT,	"ent_four_laser_left" },
	{ STATE_STANDRIGHT,	"ent_four_laser_right" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef railRider[] = {
	{ STATE_STANDDOWN,	"ent_railrider_standdown" },
	{ STATE_STANDUP,	"ent_railrider_standup" },
	{ STATE_MOVEDOWN,	"ent_railrider_walkdown" },
	{ STATE_MOVEUP,		"ent_railrider_walkup" },
	{ STATE_MOVELEFT,	"ent_railrider_walkleft" },
	{ STATE_MOVERIGHT,	"ent_railrider_walkright" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef shockBot[] = {
	{ STATE_MOVEDOWN, "ent_shockbot_walk" },
	{ STATE_SHOCKING, "ent_shock_spark_sit" },
	{ STATE_ENDSTATES, "" }
};

// Pushables

AIStateDef crate[] = {
	{ STATE_STANDDOWN,	"ent_crate_sit" },
	{ STATE_FLOATING,	"ent_crate_float" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef barrelLight[] = {
	{ STATE_STANDDOWN,	"ent_barrel_light_sit" },
	{ STATE_FLOATING,	"ent_barrel_light_float" },
	{ STATE_MELTED,		"ent_barrel_light_melt" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef barrelHeavy[] = {
	{ STATE_STANDDOWN,	"ent_barrel_heavy_sit" },
	{ STATE_FLOATING,	"ent_barrel_heavy_float" },
	{ STATE_MELTED,		"ent_barrel_heavy_melt" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef barrelExplode[] = {
	{ STATE_STANDDOWN,	"ent_barrel_explode_sit" },
	{ STATE_EXPLODING,	"explosion_boom_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef frogStatue[] = {
	{ STATE_STANDDOWN,	"ent_frogstatue_sit" },
	{ STATE_ENDSTATES, "" }
};

// Weapons

AIStateDef club[] = {
	{ STATE_STANDDOWN,	"ent_club_sit" },
	{ STATE_ENDSTATES, "" }
};
AIStateDef roboStunner[] = {
	{ STATE_STANDDOWN,	"ent_robostunner_sit" },
	{ STATE_ENDSTATES, "" }
};
AIStateDef slugSlinger[] = {
	{ STATE_STANDDOWN,	"ent_slugslinger_sit" },
	{ STATE_ENDSTATES, "" }
};

// Items

AIStateDef itemChicken[] = {
	{ STATE_STANDDOWN, "ent_chicken_standdown" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef envelopeWhite[] = {
	{ STATE_STANDDOWN, "ent_envelope_white_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef envelopeBlue[] = {
	{ STATE_STANDDOWN, "ent_envelope_blue_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef envelopeRed[] = {
	{ STATE_STANDDOWN, "ent_envelope_red_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef envelopeGreen[] = {
	{ STATE_STANDDOWN, "ent_envelope_green_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef transceiver[] = {
	{ STATE_STANDDOWN, "ent_transceiver_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef cell[] = {
	{ STATE_STANDDOWN, "ent_cell_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef gooCup[] = {
	{ STATE_STANDDOWN, "ent_goo_cup_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef gemWhite[] = {
	{ STATE_STANDDOWN, "ent_gem_white_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef gemBlue[] = {
	{ STATE_STANDDOWN, "ent_gem_blue_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef gemRed[] = {
	{ STATE_STANDDOWN, "ent_gem_red_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef gemGreen[] = {
	{ STATE_STANDDOWN, "ent_gem_green_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef cabKey[] = {
	{ STATE_STANDDOWN, "ent_cabkey_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef teaCup[] = {
	{ STATE_STANDDOWN, "ent_teacup_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef cookie[] = {
	{ STATE_STANDDOWN, "ent_cookie_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef burger[] = {
	{ STATE_STANDDOWN, "ent_burger_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef pda[] = {
	{ STATE_STANDDOWN, "ent_pda_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef book[] = {
	{ STATE_STANDDOWN, "ent_book_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef clipboard[] = {
	{ STATE_STANDDOWN, "ent_clipboard_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef note[] = {
	{ STATE_STANDDOWN, "ent_note_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef keycardWhite[] = {
	{ STATE_STANDDOWN, "ent_keycard_white_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef keycardBlue[] = {
	{ STATE_STANDDOWN, "ent_keycard_blue_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef keycardRed[] = {
	{ STATE_STANDDOWN, "ent_keycard_red_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef keycardGreen[] = {
	{ STATE_STANDDOWN, "ent_keycard_green_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef keycardPurple[] = {
	{ STATE_STANDDOWN, "ent_keycard_purple_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef keycardBlack[] = {
	{ STATE_STANDDOWN, "ent_keycard_black_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef magicEgg[] = {
	{ STATE_STANDDOWN, "ent_magic_egg_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef iceBlock[] = {
	{ STATE_STANDDOWN, "ent_ice_block_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef dollyTool1[] = {
	{ STATE_STANDDOWN, "ent_dolly_tool1_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef dollyTool2[] = {
	{ STATE_STANDDOWN, "ent_dolly_tool2_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef dollyTool3[] = {
	{ STATE_STANDDOWN, "ent_dolly_tool3_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef dollyTool4[] = {
	{ STATE_STANDDOWN, "ent_dolly_tool4_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef seed[] = {
	{ STATE_STANDDOWN, "ent_seed_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef soda[] = {
	{ STATE_STANDDOWN, "ent_soda_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef router[] = {
	{ STATE_STANDDOWN, "ent_router_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef slicer[] = {
	{ STATE_STANDDOWN, "ent_slicer_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef package[] = {
	{ STATE_STANDDOWN, "ent_package_sit" },
	{ STATE_ENDSTATES, "" }
};

AIStateDef monkeystone[] = {
	{ STATE_STANDDOWN, "ent_monkeystone_sit" },
	{ STATE_ENDSTATES, "" }
};

AIEntTypeInfo aiEntList[] = {
	// AI.H enum name		lua name				list of gfx for states	name of init function
	//--------------------------------------------------------------------------------------------
	{ AI_NONE,				"AI_NONE",				&none[0],				aiNoneInit,				NULL  },
	{ AI_GUY,				"AI_GUY",				&guy[0],				aiPlayerInit,			aiPlayerInit2  },
	{ AI_DOLLY,				"AI_DOLLY",				&dolly[0],				aiDollyInit,			aiDollyInit2  },
	{ AI_SERGEANT,			"AI_SERGEANT",			&sergeant[0],			aiSergeantInit,			aiSergeantInit2  },
	{ AI_SPACEDUDE,			"AI_SPACEDUDE",			&spacedude[0],			aiSpacedudeInit,		aiSpacedudeInit2  },
	{ AI_CHICKEN,			"AI_CHICKEN",			&chicken[0],			aiChickenInit,			aiChickenInit2  },
	{ AI_VORTEXIAN,			"AI_VORTEXIAN",			&vortexian[0],			aiVortexianInit,		aiVortexianInit2  },
	{ AI_MAINTBOT,			"AI_MAINTBOT",			&maintBot[0],			aiMaintBotInit,			aiMaintBotInit2  },
	{ AI_SCIENTIST,			"AI_SCIENTIST",			&scientist[0],			aiScientistInit,		aiScientistInit2  },
	{ AI_RAILRIDER,			"AI_RAILRIDER",			&railRider[0],			aiRailRiderInit,		aiRailRiderInit2  },
	{ AI_RAILRIDER_ON,		"AI_RAILRIDER",			&railRider[0],			aiRailRiderInit,		aiRailRiderInit2  },
	{ AI_SHOCKBOT,			"AI_SHOCKBOT",			&shockBot[0],			aiShockBotInit,			aiShockBotInit2  },
	{ AI_FOURFIRER,			"AI_FOURFIRER",			&fourFirer[0],			aiFourFirerInit,		aiFourFirerInit2  },
	{ AI_OMNIBOT_MISSILE,	"AI_OMNIBOT_MISSILE",	&omniBotMissile[0],		aiOmniBotMissileInit,	aiOmniBotMissileInit2  },
	{ AI_GEM_ATTACK,		"AI_GEM_ATTACK",		&gemAttack[0],			aiGemAttackInit,		NULL  },
	{ AI_WORKER,			"AI_WORKER",			&worker[0],				aiWorkerInit,			aiWorkerInit2  },
	{ AI_ACCOUNTANT,		"AI_ACCOUNTANT",		&accountant[0],			aiAccountantInit,		aiAccountantInit2  },
	{ AI_SLUG_ATTACK,		"AI_SLUG_ATTACK",		&slugAttack[0],			aiSlugAttackInit,		aiSlugAttackInit2  },
	{ AI_DEADWORKER,		"AI_DEADWORKER",		&deadWorker[0],			aiDeadWorkerInit,		aiDeadWorkerInit2  },

	{ AI_LASER,				"AI_LASER",				&laser[0],				aiLaserInit,			aiLaserInit2  },
	{ AI_DIVERTER,			"AI_DIVERTER",			&diverter[0],			aiDiverterInit,			aiDiverterInit2  },
	{ AI_OMNIBOT,			"AI_OMNIBOT",			&omniBot[0],			aiOmniBotInit,			aiOmniBotInit2  },
	{ AI_TURNBOT,			"AI_TURNBOT",			&turnBot[0],			aiTurnBotInit,			aiTurnBotInit2  },
	{ AI_RIGHTBOT,			"AI_RIGHTBOT",			&rightBot[0],			aiRightBotInit,			aiRightBotInit2  },
	{ AI_PUSHBOT,			"AI_PUSHBOT",			&pushBot[0],			aiPushBotInit,			aiPushBotInit2  },
	{ AI_DEADEYE,			"AI_DEADEYE",			&deadEye[0],			aiDeadEyeInit,			aiDeadEyeInit2  },
	{ AI_MEERKAT,			"AI_MEERKAT",			&meerkat[0],			aiMeerkatInit,			aiMeerkatInit2  },
	{ AI_FATFROG,			"AI_FATFROG",			&fatFrog[0],			aiFatFrogInit,			aiFatFrogInit2  },
	{ AI_GOODFAIRY,			"AI_GOODFAIRY",			&goodFairy[0],			aiGoodFairyInit,		aiGoodFairyInit2  },
	{ AI_BADFAIRY,			"AI_BADFAIRY",			&badFairy[0],			aiBadFairyInit,			aiBadFairyInit2  },
	{ AI_GATEPUDDLE,		"AI_GATEPUDDLE",		&gatePuddle[0],			aiGatePuddleInit,		aiGatePuddleInit2  },
	{ AI_ICEPUFF,			"AI_ICEPUFF",			&icePuff[0],			aiIcePuffInit,			aiIcePuffInit2  },
	{ AI_DRAGON,			"AI_DRAGON",			&dragon[0],				aiDragonInit,			aiDragonInit2  },
	{ AI_BUZZFLY,			"AI_BUZZFLY",			&buzzfly[0],			aiBuzzflyInit,			aiBuzzflyInit2  },
	{ AI_BOOMBARREL,		"AI_BOOMBARREL",		&barrelExplode[0],		aiBarrelExplodeInit,	aiBarrelExplodeInit2  },
	{ AI_FROGSTATUE,		"AI_FROGSTATUE",		&frogStatue[0],			aiFrogStatueInit,		aiFrogStatueInit2  },

	{ AI_MAGIC_EGG,			"AI_MAGIC_EGG",			&magicEgg[0],			aiMagicEggInit,		aiMagicEggInit2  },
	{ AI_ICE_BLOCK,			"AI_ICE_BLOCK",			&iceBlock[0],			aiIceBlockInit,		aiIceBlockInit2  },

	{ AI_CRATE,				"AI_CRATE",				&crate[0],				aiCrateInit,			aiCrateInit2  },
	{ AI_LIGHTBARREL,		"AI_LIGHTBARREL",		&barrelLight[0],		aiBarrelLightInit,		aiBarrelLightInit2  },
	{ AI_HEAVYBARREL,		"AI_HEAVYBARREL",		&barrelHeavy[0],		aiBarrelHeavyInit,		aiBarrelHeavyInit2  },

	{ ITEM_CELL,			"ITEM_CELL",			&cell[0],				aiCellInit,				aiCellInit2  },
	{ ITEM_ENV_WHITE,		"ITEM_ENV_WHITE",		&envelopeWhite[0],		aiEnvelopeWhiteInit,	aiEnvelopeWhiteInit2  },
	{ ITEM_TRANSCEIVER,		"ITEM_TRANSCEIVER",		&transceiver[0],		aiTransceiverInit,		aiTransceiverInit2  },
	{ ITEM_MONKEYSTONE,		"ITEM_MONKEYSTONE",		&monkeystone[0],		aiMonkeystoneInit,		aiMonkeystoneInit2  },
	{ ITEM_GEM_WHITE,		"ITEM_GEM_WHITE",		&gemWhite[0],			aiGemWhiteInit,			aiGemWhiteInit2  },
	{ ITEM_CHICKEN,			"ITEM_CHICKEN",			&itemChicken[0],		aiItemChickenInit,		aiItemChickenInit2  },
	{ ITEM_GOO_CUP,			"ITEM_GOO_CUP",			&gooCup[0],				aiGooCupInit,			aiGooCupInit2  },
	{ ITEM_CABKEY,			"ITEM_CABKEY",			&cabKey[0],				aiCabKeyInit,			aiCabKeyInit2  },
	{ ITEM_ENV_BLUE,		"ITEM_ENV_BLUE",		&envelopeBlue[0],		aiEnvelopeBlueInit,		aiEnvelopeBlueInit2  },
	{ ITEM_ENV_RED,			"ITEM_ENV_RED",			&envelopeRed[0],		aiEnvelopeRedInit,		aiEnvelopeRedInit2  },
	{ ITEM_CLUB,			"ITEM_CLUB",			&club[0],				aiClubInit,				aiClubInit2  },
	{ ITEM_ROBOSTUNNER,		"ITEM_ROBOSTUNNER",		&roboStunner[0],		aiRoboStunnerInit,		aiRoboStunnerInit2  },
	{ ITEM_SLUGSLINGER,		"ITEM_SLUGSLINGER",		&slugSlinger[0],		aiSlugSlingerInit,		aiSlugSlingerInit2  },

	{ ITEM_ENV_GREEN,		"ITEM_ENV_GREEN",		&envelopeGreen[0],		aiEnvelopeGreenInit,	aiEnvelopeGreenInit2  },
	{ ITEM_GEM_BLUE,		"ITEM_GEM_BLUE",		&gemBlue[0],			aiGemBlueInit,			aiGemBlueInit2  },
	{ ITEM_GEM_RED,			"ITEM_GEM_RED",			&gemRed[0],				aiGemRedInit,			aiGemRedInit2  },
	{ ITEM_GEM_GREEN,		"ITEM_GEM_GREEN",		&gemGreen[0],			aiGemGreenInit,			aiGemGreenInit2  },
	{ ITEM_TEACUP,			"ITEM_TEACUP",			&teaCup[0],				aiTeaCupInit,			aiTeaCupInit2  },
	{ ITEM_COOKIE,			"ITEM_COOKIE",			&cookie[0],				aiCookieInit,			aiCookieInit2  },
	{ ITEM_BURGER,			"ITEM_BURGER",			&burger[0],				aiBurgerInit,			aiBurgerInit2  },
	{ ITEM_PDA,				"ITEM_PDA",				&pda[0],				aiPdaInit,				aiPdaInit2  },
	{ ITEM_BOOK,			"ITEM_BOOK",			&book[0],				aiBookInit,				aiBookInit2  },
	{ ITEM_CLIPBOARD,		"ITEM_CLIPBOARD",		&clipboard[0],			aiClipboardInit,		aiClipboardInit2  },
	{ ITEM_NOTE,			"ITEM_NOTE",			&note[0],				aiNoteInit,				aiNoteInit2  },
	{ ITEM_KEYCARD_WHITE,	"ITEM_KEYCARD_WHITE",	&keycardWhite[0],		aiKeycardWhiteInit,		aiKeycardWhiteInit2  },
	{ ITEM_KEYCARD_BLUE,	"ITEM_KEYCARD_BLUE",	&keycardBlue[0],		aiKeycardBlueInit,		aiKeycardBlueInit2  },
	{ ITEM_KEYCARD_RED,		"ITEM_KEYCARD_RED",		&keycardRed[0],			aiKeycardRedInit,		aiKeycardRedInit2  },
	{ ITEM_KEYCARD_GREEN,	"ITEM_KEYCARD_GREEN",	&keycardGreen[0],		aiKeycardGreenInit,	aiKeycardGreenInit2  },
	{ ITEM_KEYCARD_PURPLE,	"ITEM_KEYCARD_PURPLE",	&keycardPurple[0],		aiKeycardPurpleInit,	aiKeycardPurpleInit2  },
	{ ITEM_KEYCARD_BLACK,	"ITEM_KEYCARD_BLACK",	&keycardBlack[0],		aiKeycardBlackInit,	aiKeycardBlackInit2  },
	{ ITEM_DOLLYTOOL1,		"ITEM_DOLLYTOOL1",		&dollyTool1[0],			aiDollyTool1Init,		aiDollyTool1Init2  },
	{ ITEM_DOLLYTOOL2,		"ITEM_DOLLYTOOL2",		&dollyTool2[0],			aiDollyTool2Init,		aiDollyTool2Init2  },
	{ ITEM_DOLLYTOOL3,		"ITEM_DOLLYTOOL3",		&dollyTool3[0],			aiDollyTool3Init,		aiDollyTool3Init2  },
	{ ITEM_DOLLYTOOL4,		"ITEM_DOLLYTOOL4",		&dollyTool4[0],			aiDollyTool4Init,		aiDollyTool4Init2  },
	{ ITEM_SEED,			"ITEM_SEED",			&seed[0],				aiSeedInit,				aiSeedInit2  },
	{ ITEM_SODA,			"ITEM_SODA",			&soda[0],				aiSodaInit,				aiSodaInit2  },
	{ ITEM_ROUTER,			"ITEM_ROUTER",			&router[0],				aiRouterInit,			aiRouterInit2  },
	{ ITEM_SLICER,			"ITEM_SLICER",			&slicer[0],				aiSlicerInit,			aiSlicerInit2  },
	{ ITEM_PACKAGE,			"ITEM_PACKAGE",			&package[0],			aiPackageInit,			aiPackageInit2  },

	{ END_AI_TYPES,			NULL,					NULL,					NULL,					NULL }
};

AI::AI() {
	_ents = new Common::Array<AIEntity *>;
	_floats = new Common::Array<AIEntity *>;

	for (int i = 0; i < kMaxLevel2Ents;i++) {
		_entsLevel2[i] = new AIEntLevel2;
	}

	// REMOVE: Remove for final. Used here due to lack of a MENU
	_numGems = _numGooCups = _numMonkeystones = _numInventory = 0;
}

AI::~AI() {
	delete _ents;
	delete _floats;
	for (int i = 0; i < kMaxLevel2Ents;i++) {
		delete _entsLevel2[i];
	}
}

bool AI::init() {
	warning("STUB: AI::init incomplete");

	// Clear Waypoint list and load Waypoint graphics
	_numWaypoints = 0;
	_waypointGfx[0] = new Tile;
	_waypointGfx[0]->load(g_hdb->_fileMan->findFirstData("icon_waypoint_select1", TYPE_ICON32));
	_waypointGfx[1] = new Tile;
	_waypointGfx[1]->load(g_hdb->_fileMan->findFirstData("icon_waypoint_select2", TYPE_ICON32));
	_waypointGfx[2] = new Tile;
	_waypointGfx[2]->load(g_hdb->_fileMan->findFirstData("icon_waypoint_select3", TYPE_ICON32));
	_waypointGfx[3] = new Tile;
	_waypointGfx[3]->load(g_hdb->_fileMan->findFirstData("icon_waypoint_select4", TYPE_ICON32));

	_playerRunning = false;

	restartSystem();
	return true;
}

void AI::clearPersistent() {
	_numGems = _numGooCups = _numMonkeystones = 0;
}

void AI::restartSystem() {
	warning("STUB: AI::restartSystem incomplete");

	// Clear Player
	_player = NULL;
	_playerDead = false;
	_playerInvisible = false;
	_playerOnIce = false;
	_playerEmerging = false;

	// Clean up Player Graphics Storage
	memset(_horrible1Gfx, NULL, kMaxDeathFrames * sizeof(Tile *));
	memset(_horrible2Gfx, NULL, kMaxDeathFrames * sizeof(Tile *));
	memset(_horrible3Gfx, NULL, kMaxDeathFrames * sizeof(Tile *));
	memset(_horrible4Gfx, NULL, kMaxDeathFrames * sizeof(Tile *));
	memset(_plummetGfx, NULL, kMaxDeathFrames * sizeof(Tile *));
	memset(_dyingGfx, NULL, kMaxDeathFrames * sizeof(Tile *));

	memset(_pushdownGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_pushupGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_pushleftGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_pushrightGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_stunDownGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_stunUpGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_stunLeftGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_stunRightGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_slugDownGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_slugUpGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_slugLeftGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_slugRightGfx, NULL, kMaxAnimFrames * sizeof(Tile *));

	if (_clubDownFrames) {
		_clubDownFrames = 3;
		_clubUpFrames = 3;
		_clubLeftFrames = 3;
		_clubRightFrames = 3;
	}

	memset(_clubDownGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_clubUpGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_clubLeftGfx, NULL, kMaxAnimFrames * sizeof(Tile *));
	memset(_clubRightGfx, NULL, kMaxAnimFrames * sizeof(Tile *));

	// Clear the Entity List
	_ents->clear();

	// Clear Cinematic System
	_cineActive = _cameraLock = _playerLock = _cineAborted = false;

	// Clear waypoints
	memset(&_waypoints[0], 0, sizeof(_waypoints));
	_numWaypoints = 0;
}
} // End of Namespace
