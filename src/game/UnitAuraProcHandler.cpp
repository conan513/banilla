/*
 * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
 * Copyright (C) 2009-2011 MaNGOSZero <https://github.com/mangos/zero>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "Common.h"
#include "Log.h"
#include "ObjectMgr.h"
#include "SpellMgr.h"
#include "Player.h"
#include "Unit.h"
#include "Spell.h"
#include "SpellAuras.h"
#include "Totem.h"
#include "Creature.h"
#include "Formulas.h"
#include "CreatureAI.h"
#include "ScriptMgr.h"
#include "Util.h"

pAuraProcHandler AuraProcHandler[TOTAL_AURAS] =
{
    &Unit::HandleNULLProc,                                  //  0 SPELL_AURA_NONE
    &Unit::HandleNULLProc,                                  //  1 SPELL_AURA_BIND_SIGHT
    &Unit::HandleNULLProc,                                  //  2 SPELL_AURA_MOD_POSSESS
    &Unit::HandleNULLProc,                                  //  3 SPELL_AURA_PERIODIC_DAMAGE
    &Unit::HandleDummyAuraProc,                             //  4 SPELL_AURA_DUMMY
    &Unit::HandleNULLProc,                                  //  5 SPELL_AURA_MOD_CONFUSE
    &Unit::HandleNULLProc,                                  //  6 SPELL_AURA_MOD_CHARM
    &Unit::HandleNULLProc,                                  //  7 SPELL_AURA_MOD_FEAR
    &Unit::HandleNULLProc,                                  //  8 SPELL_AURA_PERIODIC_HEAL
    &Unit::HandleNULLProc,                                  //  9 SPELL_AURA_MOD_ATTACKSPEED
    &Unit::HandleNULLProc,                                  // 10 SPELL_AURA_MOD_THREAT
    &Unit::HandleNULLProc,                                  // 11 SPELL_AURA_MOD_TAUNT
    &Unit::HandleNULLProc,                                  // 12 SPELL_AURA_MOD_STUN
    &Unit::HandleNULLProc,                                  // 13 SPELL_AURA_MOD_DAMAGE_DONE
    &Unit::HandleNULLProc,                                  // 14 SPELL_AURA_MOD_DAMAGE_TAKEN
    &Unit::HandleNULLProc,                                  // 15 SPELL_AURA_DAMAGE_SHIELD
    &Unit::HandleNULLProc,                                  // 16 SPELL_AURA_MOD_STEALTH
    &Unit::HandleNULLProc,                                  // 17 SPELL_AURA_MOD_STEALTH_DETECT
    &Unit::HandleNULLProc,                                  // 18 SPELL_AURA_MOD_INVISIBILITY
    &Unit::HandleNULLProc,                                  // 19 SPELL_AURA_MOD_INVISIBILITY_DETECTION
    &Unit::HandleNULLProc,                                  // 20 SPELL_AURA_OBS_MOD_HEALTH
    &Unit::HandleNULLProc,                                  // 21 SPELL_AURA_OBS_MOD_MANA
    &Unit::HandleModResistanceAuraProc,                     // 22 SPELL_AURA_MOD_RESISTANCE
    &Unit::HandleNULLProc,                                  // 23 SPELL_AURA_PERIODIC_TRIGGER_SPELL
    &Unit::HandleNULLProc,                                  // 24 SPELL_AURA_PERIODIC_ENERGIZE
    &Unit::HandleNULLProc,                                  // 25 SPELL_AURA_MOD_PACIFY
    &Unit::HandleNULLProc,                                  // 26 SPELL_AURA_MOD_ROOT
    &Unit::HandleNULLProc,                                  // 27 SPELL_AURA_MOD_SILENCE
    &Unit::HandleNULLProc,                                  // 28 SPELL_AURA_REFLECT_SPELLS
    &Unit::HandleNULLProc,                                  // 29 SPELL_AURA_MOD_STAT
    &Unit::HandleNULLProc,                                  // 30 SPELL_AURA_MOD_SKILL
    &Unit::HandleNULLProc,                                  // 31 SPELL_AURA_MOD_INCREASE_SPEED
    &Unit::HandleNULLProc,                                  // 32 SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED
    &Unit::HandleNULLProc,                                  // 33 SPELL_AURA_MOD_DECREASE_SPEED
    &Unit::HandleNULLProc,                                  // 34 SPELL_AURA_MOD_INCREASE_HEALTH
    &Unit::HandleNULLProc,                                  // 35 SPELL_AURA_MOD_INCREASE_ENERGY
    &Unit::HandleNULLProc,                                  // 36 SPELL_AURA_MOD_SHAPESHIFT
    &Unit::HandleNULLProc,                                  // 37 SPELL_AURA_EFFECT_IMMUNITY
    &Unit::HandleNULLProc,                                  // 38 SPELL_AURA_STATE_IMMUNITY
    &Unit::HandleNULLProc,                                  // 39 SPELL_AURA_SCHOOL_IMMUNITY
    &Unit::HandleNULLProc,                                  // 40 SPELL_AURA_DAMAGE_IMMUNITY
    &Unit::HandleNULLProc,                                  // 41 SPELL_AURA_DISPEL_IMMUNITY
    &Unit::HandleProcTriggerSpellAuraProc,                  // 42 SPELL_AURA_PROC_TRIGGER_SPELL
    &Unit::HandleProcTriggerDamageAuraProc,                 // 43 SPELL_AURA_PROC_TRIGGER_DAMAGE
    &Unit::HandleNULLProc,                                  // 44 SPELL_AURA_TRACK_CREATURES
    &Unit::HandleNULLProc,                                  // 45 SPELL_AURA_TRACK_RESOURCES
    &Unit::HandleNULLProc,                                  // 46 SPELL_AURA_46
    &Unit::HandleNULLProc,                                  // 47 SPELL_AURA_MOD_PARRY_PERCENT
    &Unit::HandleNULLProc,                                  // 48 SPELL_AURA_48
    &Unit::HandleNULLProc,                                  // 49 SPELL_AURA_MOD_DODGE_PERCENT
    &Unit::HandleNULLProc,                                  // 50 SPELL_AURA_MOD_BLOCK_SKILL    obsolete?
    &Unit::HandleNULLProc,                                  // 51 SPELL_AURA_MOD_BLOCK_PERCENT
    &Unit::HandleNULLProc,                                  // 52 SPELL_AURA_MOD_CRIT_PERCENT
    &Unit::HandleNULLProc,                                  // 53 SPELL_AURA_PERIODIC_LEECH
    &Unit::HandleNULLProc,                                  // 54 SPELL_AURA_MOD_HIT_CHANCE
    &Unit::HandleNULLProc,                                  // 55 SPELL_AURA_MOD_SPELL_HIT_CHANCE
    &Unit::HandleNULLProc,                                  // 56 SPELL_AURA_TRANSFORM
    &Unit::HandleNULLProc,                                  // 57 SPELL_AURA_MOD_SPELL_CRIT_CHANCE
    &Unit::HandleNULLProc,                                  // 58 SPELL_AURA_MOD_INCREASE_SWIM_SPEED
    &Unit::HandleNULLProc,                                  // 59 SPELL_AURA_MOD_DAMAGE_DONE_CREATURE
    &Unit::HandleNULLProc,                                  // 60 SPELL_AURA_MOD_PACIFY_SILENCE
    &Unit::HandleNULLProc,                                  // 61 SPELL_AURA_MOD_SCALE
    &Unit::HandleNULLProc,                                  // 62 SPELL_AURA_PERIODIC_HEALTH_FUNNEL
    &Unit::HandleNULLProc,                                  // 63 SPELL_AURA_PERIODIC_MANA_FUNNEL obsolete?
    &Unit::HandleNULLProc,                                  // 64 SPELL_AURA_PERIODIC_MANA_LEECH
    &Unit::HandleModCastingSpeedNotStackAuraProc,           // 65 SPELL_AURA_MOD_CASTING_SPEED_NOT_STACK
    &Unit::HandleNULLProc,                                  // 66 SPELL_AURA_FEIGN_DEATH
    &Unit::HandleNULLProc,                                  // 67 SPELL_AURA_MOD_DISARM
    &Unit::HandleNULLProc,                                  // 68 SPELL_AURA_MOD_STALKED
    &Unit::HandleNULLProc,                                  // 69 SPELL_AURA_SCHOOL_ABSORB
    &Unit::HandleNULLProc,                                  // 70 SPELL_AURA_EXTRA_ATTACKS      Useless, used by only one spell that has only visual effect
    &Unit::HandleNULLProc,                                  // 71 SPELL_AURA_MOD_SPELL_CRIT_CHANCE_SCHOOL
    &Unit::HandleModPowerCostSchoolAuraProc,                // 72 SPELL_AURA_MOD_POWER_COST_SCHOOL_PCT
    &Unit::HandleModPowerCostSchoolAuraProc,                // 73 SPELL_AURA_MOD_POWER_COST_SCHOOL
    &Unit::HandleReflectSpellsSchoolAuraProc,               // 74 SPELL_AURA_REFLECT_SPELLS_SCHOOL
    &Unit::HandleNULLProc,                                  // 75 SPELL_AURA_MOD_LANGUAGE
    &Unit::HandleNULLProc,                                  // 76 SPELL_AURA_FAR_SIGHT
    &Unit::HandleMechanicImmuneResistanceAuraProc,          // 77 SPELL_AURA_MECHANIC_IMMUNITY
    &Unit::HandleNULLProc,                                  // 78 SPELL_AURA_MOUNTED
    &Unit::HandleNULLProc,                                  // 79 SPELL_AURA_MOD_DAMAGE_PERCENT_DONE
    &Unit::HandleNULLProc,                                  // 80 SPELL_AURA_MOD_PERCENT_STAT
    &Unit::HandleNULLProc,                                  // 81 SPELL_AURA_SPLIT_DAMAGE_PCT
    &Unit::HandleNULLProc,                                  // 82 SPELL_AURA_WATER_BREATHING
    &Unit::HandleNULLProc,                                  // 83 SPELL_AURA_MOD_BASE_RESISTANCE
    &Unit::HandleNULLProc,                                  // 84 SPELL_AURA_MOD_REGEN
    &Unit::HandleCantTrigger,                               // 85 SPELL_AURA_MOD_POWER_REGEN
    &Unit::HandleNULLProc,                                  // 86 SPELL_AURA_CHANNEL_DEATH_ITEM
    &Unit::HandleNULLProc,                                  // 87 SPELL_AURA_MOD_DAMAGE_PERCENT_TAKEN
    &Unit::HandleNULLProc,                                  // 88 SPELL_AURA_MOD_HEALTH_REGEN_PERCENT
    &Unit::HandleNULLProc,                                  // 89 SPELL_AURA_PERIODIC_DAMAGE_PERCENT
    &Unit::HandleNULLProc,                                  // 90 SPELL_AURA_MOD_RESIST_CHANCE  Useless
    &Unit::HandleNULLProc,                                  // 91 SPELL_AURA_MOD_DETECT_RANGE
    &Unit::HandleNULLProc,                                  // 92 SPELL_AURA_PREVENTS_FLEEING
    &Unit::HandleNULLProc,                                  // 93 SPELL_AURA_MOD_UNATTACKABLE
    &Unit::HandleNULLProc,                                  // 94 SPELL_AURA_INTERRUPT_REGEN
    &Unit::HandleNULLProc,                                  // 95 SPELL_AURA_GHOST
    &Unit::HandleNULLProc,                                  // 96 SPELL_AURA_SPELL_MAGNET
    &Unit::HandleNULLProc,                                  // 97 SPELL_AURA_MANA_SHIELD
    &Unit::HandleNULLProc,                                  // 98 SPELL_AURA_MOD_SKILL_TALENT
    &Unit::HandleNULLProc,                                  // 99 SPELL_AURA_MOD_ATTACK_POWER
    &Unit::HandleNULLProc,                                  //100 SPELL_AURA_AURAS_VISIBLE obsolete? all player can see all auras now
    &Unit::HandleNULLProc,                                  //101 SPELL_AURA_MOD_RESISTANCE_PCT
    &Unit::HandleNULLProc,                                  //102 SPELL_AURA_MOD_MELEE_ATTACK_POWER_VERSUS
    &Unit::HandleNULLProc,                                  //103 SPELL_AURA_MOD_TOTAL_THREAT
    &Unit::HandleNULLProc,                                  //104 SPELL_AURA_WATER_WALK
    &Unit::HandleNULLProc,                                  //105 SPELL_AURA_FEATHER_FALL
    &Unit::HandleNULLProc,                                  //106 SPELL_AURA_HOVER
    &Unit::HandleNULLProc,                                  //107 SPELL_AURA_ADD_FLAT_MODIFIER
    &Unit::HandleNULLProc,                                  //108 SPELL_AURA_ADD_PCT_MODIFIER
    &Unit::HandleAddTargetTriggerAuraProc,                  //109 SPELL_AURA_ADD_TARGET_TRIGGER
    &Unit::HandleNULLProc,                                  //110 SPELL_AURA_MOD_POWER_REGEN_PERCENT
    &Unit::HandleNULLProc,                                  //111 SPELL_AURA_ADD_CASTER_HIT_TRIGGER
    &Unit::HandleOverrideClassScriptAuraProc,               //112 SPELL_AURA_OVERRIDE_CLASS_SCRIPTS
    &Unit::HandleNULLProc,                                  //113 SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN
    &Unit::HandleNULLProc,                                  //114 SPELL_AURA_MOD_RANGED_DAMAGE_TAKEN_PCT
    &Unit::HandleNULLProc,                                  //115 SPELL_AURA_MOD_HEALING
    &Unit::HandleNULLProc,                                  //116 SPELL_AURA_MOD_REGEN_DURING_COMBAT
    &Unit::HandleMechanicImmuneResistanceAuraProc,          //117 SPELL_AURA_MOD_MECHANIC_RESISTANCE
    &Unit::HandleNULLProc,                                  //118 SPELL_AURA_MOD_HEALING_PCT
    &Unit::HandleNULLProc,                                  //119 SPELL_AURA_SHARE_PET_TRACKING useless
    &Unit::HandleNULLProc,                                  //120 SPELL_AURA_UNTRACKABLE
    &Unit::HandleNULLProc,                                  //121 SPELL_AURA_EMPATHY
    &Unit::HandleNULLProc,                                  //122 SPELL_AURA_MOD_OFFHAND_DAMAGE_PCT
    &Unit::HandleNULLProc,                                  //123 SPELL_AURA_MOD_TARGET_RESISTANCE
    &Unit::HandleNULLProc,                                  //124 SPELL_AURA_MOD_RANGED_ATTACK_POWER
    &Unit::HandleNULLProc,                                  //125 SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN
    &Unit::HandleNULLProc,                                  //126 SPELL_AURA_MOD_MELEE_DAMAGE_TAKEN_PCT
    &Unit::HandleNULLProc,                                  //127 SPELL_AURA_RANGED_ATTACK_POWER_ATTACKER_BONUS
    &Unit::HandleNULLProc,                                  //128 SPELL_AURA_MOD_POSSESS_PET
    &Unit::HandleNULLProc,                                  //129 SPELL_AURA_MOD_SPEED_ALWAYS
    &Unit::HandleNULLProc,                                  //130 SPELL_AURA_MOD_MOUNTED_SPEED_ALWAYS
    &Unit::HandleNULLProc,                                  //131 SPELL_AURA_MOD_RANGED_ATTACK_POWER_VERSUS
    &Unit::HandleNULLProc,                                  //132 SPELL_AURA_MOD_INCREASE_ENERGY_PERCENT
    &Unit::HandleNULLProc,                                  //133 SPELL_AURA_MOD_INCREASE_HEALTH_PERCENT
    &Unit::HandleNULLProc,                                  //134 SPELL_AURA_MOD_MANA_REGEN_INTERRUPT
    &Unit::HandleNULLProc,                                  //135 SPELL_AURA_MOD_HEALING_DONE
    &Unit::HandleNULLProc,                                  //136 SPELL_AURA_MOD_HEALING_DONE_PERCENT
    &Unit::HandleNULLProc,                                  //137 SPELL_AURA_MOD_TOTAL_STAT_PERCENTAGE
    &Unit::HandleHasteAuraProc,                             //138 SPELL_AURA_MOD_MELEE_HASTE
    &Unit::HandleNULLProc,                                  //139 SPELL_AURA_FORCE_REACTION
    &Unit::HandleNULLProc,                                  //140 SPELL_AURA_MOD_RANGED_HASTE
    &Unit::HandleNULLProc,                                  //141 SPELL_AURA_MOD_RANGED_AMMO_HASTE
    &Unit::HandleNULLProc,                                  //142 SPELL_AURA_MOD_BASE_RESISTANCE_PCT
    &Unit::HandleNULLProc,                                  //143 SPELL_AURA_MOD_RESISTANCE_EXCLUSIVE
    &Unit::HandleNULLProc,                                  //144 SPELL_AURA_SAFE_FALL
    &Unit::HandleNULLProc,                                  //145 SPELL_AURA_CHARISMA obsolete?
    &Unit::HandleNULLProc,                                  //146 SPELL_AURA_PERSUADED obsolete?
    &Unit::HandleNULLProc,                                  //147 SPELL_AURA_MECHANIC_IMMUNITY_MASK
    &Unit::HandleNULLProc,                                  //148 SPELL_AURA_RETAIN_COMBO_POINTS
    &Unit::HandleCantTrigger,                               //149 SPELL_AURA_RESIST_PUSHBACK
    &Unit::HandleNULLProc,                                  //150 SPELL_AURA_MOD_SHIELD_BLOCKVALUE_PCT
    &Unit::HandleNULLProc,                                  //151 SPELL_AURA_TRACK_STEALTHED
    &Unit::HandleNULLProc,                                  //152 SPELL_AURA_MOD_DETECTED_RANGE
    &Unit::HandleNULLProc,                                  //153 SPELL_AURA_SPLIT_DAMAGE_FLAT
    &Unit::HandleNULLProc,                                  //154 SPELL_AURA_MOD_STEALTH_LEVEL
    &Unit::HandleNULLProc,                                  //155 SPELL_AURA_MOD_WATER_BREATHING
    &Unit::HandleNULLProc,                                  //156 SPELL_AURA_MOD_REPUTATION_GAIN
    &Unit::HandleNULLProc,                                  //157 SPELL_AURA_PET_DAMAGE_MULTI (single test like spell 20782, also single for 214 aura)
    &Unit::HandleNULLProc,                                  //158 SPELL_AURA_MOD_SHIELD_BLOCKVALUE
    &Unit::HandleNULLProc,                                  //159 SPELL_AURA_NO_PVP_CREDIT      only for Honorless Target spell
    &Unit::HandleNULLProc,                                  //160 SPELL_AURA_MOD_AOE_AVOIDANCE
    &Unit::HandleNULLProc,                                  //161 SPELL_AURA_MOD_HEALTH_REGEN_IN_COMBAT
    &Unit::HandleNULLProc,                                  //162 SPELL_AURA_POWER_BURN_MANA
    &Unit::HandleNULLProc,                                  //163 SPELL_AURA_MOD_CRIT_DAMAGE_BONUS
    &Unit::HandleNULLProc,                                  //164 useless, only one test spell
    &Unit::HandleNULLProc,                                  //165 SPELL_AURA_MELEE_ATTACK_POWER_ATTACKER_BONUS
    &Unit::HandleNULLProc,                                  //166 SPELL_AURA_MOD_ATTACK_POWER_PCT
    &Unit::HandleNULLProc,                                  //167 SPELL_AURA_MOD_RANGED_ATTACK_POWER_PCT
    &Unit::HandleNULLProc,                                  //168 SPELL_AURA_MOD_DAMAGE_DONE_VERSUS
    &Unit::HandleNULLProc,                                  //169 SPELL_AURA_MOD_CRIT_PERCENT_VERSUS
    &Unit::HandleNULLProc,                                  //170 SPELL_AURA_DETECT_AMORE       only for Detect Amore spell
    &Unit::HandleNULLProc,                                  //171 SPELL_AURA_MOD_SPEED_NOT_STACK
    &Unit::HandleNULLProc,                                  //172 SPELL_AURA_MOD_MOUNTED_SPEED_NOT_STACK
    &Unit::HandleNULLProc,                                  //173 SPELL_AURA_ALLOW_CHAMPION_SPELLS  only for Proclaim Champion spell
    &Unit::HandleNULLProc,                                  //174 SPELL_AURA_MOD_SPELL_DAMAGE_OF_STAT_PERCENT
    &Unit::HandleNULLProc,                                  //175 SPELL_AURA_MOD_SPELL_HEALING_OF_STAT_PERCENT
    &Unit::HandleNULLProc,                                  //176 SPELL_AURA_SPIRIT_OF_REDEMPTION   only for Spirit of Redemption spell, die at aura end
    &Unit::HandleNULLProc,                                  //177 SPELL_AURA_AOE_CHARM
    &Unit::HandleNULLProc,                                  //178 SPELL_AURA_MOD_DEBUFF_RESISTANCE
    &Unit::HandleNULLProc,                                  //179 SPELL_AURA_MOD_ATTACKER_SPELL_CRIT_CHANCE
    &Unit::HandleNULLProc,                                  //180 SPELL_AURA_MOD_FLAT_SPELL_DAMAGE_VERSUS
    &Unit::HandleNULLProc,                                  //181 SPELL_AURA_MOD_FLAT_SPELL_CRIT_DAMAGE_VERSUS unused
    &Unit::HandleNULLProc,                                  //182 SPELL_AURA_MOD_RESISTANCE_OF_STAT_PERCENT
    &Unit::HandleNULLProc,                                  //183 SPELL_AURA_MOD_CRITICAL_THREAT only used in 28746
    &Unit::HandleNULLProc,                                  //184 SPELL_AURA_MOD_ATTACKER_MELEE_HIT_CHANCE
    &Unit::HandleNULLProc,                                  //185 SPELL_AURA_MOD_ATTACKER_RANGED_HIT_CHANCE
    &Unit::HandleNULLProc,                                  //186 SPELL_AURA_MOD_ATTACKER_SPELL_HIT_CHANCE
    &Unit::HandleNULLProc,                                  //187 SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_CHANCE
    &Unit::HandleNULLProc,                                  //188 SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_CHANCE
	&Unit::HandleNULLProc,                                   //189 SPELL_AURA_MOD_RATING
    &Unit::HandleNULLProc,                                  //190 SPELL_AURA_MOD_FACTION_REPUTATION_GAIN
    &Unit::HandleNULLProc,                                  //191 SPELL_AURA_USE_NORMAL_MOVEMENT_SPEED
		&Unit::HandleNULLProc,                                  //192 SPELL_AURA_HASTE_MELEE
		&Unit::HandleNULLProc,                                  //193 SPELL_AURA_HASTE_ALL (in fact combat (any type attack) speed pct)
		&Unit::HandleNULLProc,                                  //194 SPELL_AURA_MOD_DEPRICATED_1 not used now (old SPELL_AURA_MOD_SPELL_DAMAGE_OF_INTELLECT)
		&Unit::HandleNULLProc,                                  //195 SPELL_AURA_MOD_DEPRICATED_2 not used now (old SPELL_AURA_MOD_SPELL_HEALING_OF_INTELLECT)
		&Unit::HandleNULLProc,                                  //196 SPELL_AURA_MOD_COOLDOWN
		&Unit::HandleNULLProc,                                  //197 SPELL_AURA_MOD_ATTACKER_SPELL_AND_WEAPON_CRIT_CHANCE
		&Unit::HandleNULLProc,                                  //198 SPELL_AURA_MOD_ALL_WEAPON_SKILLS
		&Unit::HandleNULLProc,                                  //199 SPELL_AURA_MOD_INCREASES_SPELL_PCT_TO_HIT
		&Unit::HandleNULLProc,                                  //200 SPELL_AURA_MOD_XP_PCT
		&Unit::HandleNULLProc,                                  //201 SPELL_AURA_FLY                             this aura enable flight mode...
		&Unit::HandleNULLProc,                                  //202 SPELL_AURA_IGNORE_COMBAT_RESULT
		&Unit::HandleNULLProc,                                  //203 SPELL_AURA_MOD_ATTACKER_MELEE_CRIT_DAMAGE
		&Unit::HandleNULLProc,                                  //204 SPELL_AURA_MOD_ATTACKER_RANGED_CRIT_DAMAGE
		&Unit::HandleNULLProc,                                  //205 SPELL_AURA_MOD_ATTACKER_SPELL_CRIT_DAMAGE
		&Unit::HandleNULLProc,                                  //206 SPELL_AURA_MOD_FLIGHT_SPEED
		&Unit::HandleNULLProc,                                  //207 SPELL_AURA_MOD_FLIGHT_SPEED_MOUNTED
		&Unit::HandleNULLProc,                                  //208 SPELL_AURA_MOD_FLIGHT_SPEED_STACKING
		&Unit::HandleNULLProc,                                  //209 SPELL_AURA_MOD_FLIGHT_SPEED_MOUNTED_STACKING
		&Unit::HandleNULLProc,                                  //210 SPELL_AURA_MOD_FLIGHT_SPEED_NOT_STACKING
		&Unit::HandleNULLProc,                                  //211 SPELL_AURA_MOD_FLIGHT_SPEED_MOUNTED_NOT_STACKING
		&Unit::HandleNULLProc,                                  //212 SPELL_AURA_MOD_RANGED_ATTACK_POWER_OF_STAT_PERCENT
		&Unit::HandleNULLProc,                                  //213 SPELL_AURA_MOD_RAGE_FROM_DAMAGE_DEALT implemented in Player::RewardRage
		&Unit::HandleNULLProc,                                  //214 Tamed Pet Passive
		&Unit::HandleNULLProc,                                  //215 SPELL_AURA_ARENA_PREPARATION
		&Unit::HandleNULLProc,                                  //216 SPELL_AURA_HASTE_SPELLS
		&Unit::HandleNULLProc,                                  //217                                   unused
		&Unit::HandleNULLProc,                                  //218 SPELL_AURA_HASTE_RANGED
		&Unit::HandleNULLProc,                                  //219 SPELL_AURA_MOD_MANA_REGEN_FROM_STAT
		&Unit::HandleNULLProc,                                  //220 SPELL_AURA_MOD_RATING_FROM_STAT
		&Unit::HandleNULLProc,                                  //221 ignored
		&Unit::HandleNULLProc,                                  //222 unused
		&Unit::HandleNULLProc,                                  //223 Cold Stare
		&Unit::HandleNULLProc,                                  //224 unused
		&Unit::HandleMendingAuraProc,                           //225 SPELL_AURA_PRAYER_OF_MENDING
		&Unit::HandleNULLProc,                                  //226 SPELL_AURA_PERIODIC_DUMMY
		&Unit::HandleNULLProc,                                  //227 SPELL_AURA_PERIODIC_TRIGGER_SPELL_WITH_VALUE
		&Unit::HandleNULLProc,                                  //228 SPELL_AURA_DETECT_STEALTH
		&Unit::HandleNULLProc,                                  //229 SPELL_AURA_MOD_AOE_DAMAGE_AVOIDANCE
		&Unit::HandleNULLProc,                                  //230 Commanding Shout
		&Unit::HandleProcTriggerSpellAuraProc,                  //231 SPELL_AURA_PROC_TRIGGER_SPELL_WITH_VALUE
		&Unit::HandleNULLProc,                                  //232 SPELL_AURA_MECHANIC_DURATION_MOD
		&Unit::HandleNULLProc,                                  //233 set model id to the one of the creature with id m_modifier.m_miscvalue
		&Unit::HandleNULLProc,                                  //234 SPELL_AURA_MECHANIC_DURATION_MOD_NOT_STACK
		&Unit::HandleNULLProc,                                  //235 SPELL_AURA_MOD_DISPEL_RESIST
		&Unit::HandleNULLProc,                                  //236 unused
		&Unit::HandleNULLProc,                                  //237 SPELL_AURA_MOD_SPELL_DAMAGE_OF_ATTACK_POWER
		&Unit::HandleNULLProc,                                  //238 SPELL_AURA_MOD_SPELL_HEALING_OF_ATTACK_POWER
		&Unit::HandleNULLProc,                                  //239 SPELL_AURA_MOD_SCALE_2 only in Noggenfogger Elixir (16595) before 2.3.0 aura 61
		&Unit::HandleNULLProc,                                  //240 SPELL_AURA_MOD_EXPERTISE
		&Unit::HandleNULLProc,                                  //241 Forces the player to move forward
		&Unit::HandleNULLProc,                                  //242 SPELL_AURA_MOD_SPELL_DAMAGE_FROM_HEALING
		&Unit::HandleNULLProc,                                  //243 used by two test spells
		&Unit::HandleNULLProc,                                  //244 Comprehend language
		&Unit::HandleNULLProc,                                  //245 SPELL_AURA_MOD_DURATION_OF_MAGIC_EFFECTS
		&Unit::HandleNULLProc,                                  //246 unused
		&Unit::HandleNULLProc,                                  //247 unused
		&Unit::HandleNULLProc,                                  //248 SPELL_AURA_MOD_COMBAT_RESULT_CHANCE
		&Unit::HandleNULLProc,                                  //249
		&Unit::HandleNULLProc,                                  //250 SPELL_AURA_MOD_INCREASE_HEALTH_2
		&Unit::HandleNULLProc,                                  //251 SPELL_AURA_MOD_ENEMY_DODGE
		&Unit::HandleNULLProc,                                  //252 unused
		&Unit::HandleNULLProc,                                  //253 unused
		&Unit::HandleNULLProc,                                  //254 unused
		&Unit::HandleNULLProc,                                  //255 unused
		&Unit::HandleNULLProc,                                  //256 unused
		&Unit::HandleNULLProc,                                  //257 unused
		&Unit::HandleNULLProc,                                  //258 unused
		&Unit::HandleNULLProc,                                  //259 unused
		&Unit::HandleNULLProc,                                  //260 unused
		&Unit::HandleNULLProc,                                  //261 SPELL_AURA_261 some phased state (44856 spell)
};

// Fonctions Nostalrius
inline bool SpellCanTrigger(const SpellEntry* spellProto, const SpellEntry* procSpell, uint8 eff_idx = 0)
{
    return (procSpell && procSpell->SpellFamilyName == spellProto->SpellFamilyName && procSpell->SpellFamilyFlags & spellProto->EffectItemType[eff_idx]);
}

bool Unit::IsTriggeredAtSpellProcEvent(Unit *pVictim, SpellAuraHolder* holder, SpellEntry const* procSpell, uint32 procFlag, uint32 procExtra, WeaponAttackType attType, bool isVictim, SpellProcEventEntry const*& spellProcEvent)
{
    SpellEntry const* spellProto = holder->GetSpellProto();
    /*
    if (procSpell)
        sLog.outString("Flag : 0x%x, Extr : 0x%x. ProcSpell %u Aura %u",
            procFlag, procExtra, procSpell->Id, spellProto->Id);
    else
        sLog.outString("Flag : 0x%x, Extr : 0x%x. Aura %u (ICON %u)",
            procFlag, procExtra, spellProto->Id, spellProto->SpellIconID);*/

    // Flurry can't proc on additional windfury attacks (is this right?)
    if (spellProto->Id == 16280 && m_extraAttacks)
        return false;

    // Don't proc weapons on Sap
    if (spellProto->Id == 14076 || spellProto->Id == 14094 || spellProto->Id == 14095)
        return false;

// Shadow Word: Death - can trigger from every kill
   if (holder->GetId() == 32409 || holder->GetId() == 54788 || holder->GetId() == 54789 || holder->GetId() == 54790 || holder->GetId() == 54791)
	return true;


    /// [TODO]
    /// Delete all these spells, and manage it via the DB (spell_proc_event)
    if (procSpell)
    {
        // Redoubt
        if (spellProto->SpellIconID == 28 && spellProto->SpellFamilyName == 0)
        {
            if (procFlag & PROC_FLAG_TAKEN_MELEE_HIT && procExtra & PROC_EX_CRITICAL_HIT)
                return true;
            return false;
        }
        // Eye for an Eye
        if (spellProto->SpellIconID == 1820)
        {
            if (procFlag & PROC_FLAG_TAKEN_NEGATIVE_SPELL_HIT && procExtra & PROC_EX_CRITICAL_HIT)
                return true;
            return false;
        }
        // Improved Lay on Hands
        if (spellProto->SpellIconID == 79 && spellProto->SpellFamilyName == SPELLFAMILY_PALADIN)
        {
            if (procSpell->SpellFamilyName == SPELLFAMILY_PALADIN && procSpell->SpellIconID == 79
                    && procSpell->Category == 56 && !isVictim)
                return true;
            return false;
        }

        // DRUID
        // Omen of Clarity
        if (spellProto->Id == 16864)
        {
            if (!procSpell && (procFlag & (PROC_FLAG_SUCCESSFUL_MELEE_HIT | PROC_FLAG_SUCCESSFUL_MELEE_SPELL_HIT)))
                return urand(0, 99) < 10;
            return false;
        }
        // PRIEST
        // Inspiration
        if (spellProto->SpellIconID == 79 && spellProto->SpellFamilyName == SPELLFAMILY_PRIEST)
        {
            if (procSpell->IsFitToFamily<SPELLFAMILY_PRIEST, CF_PRIEST_PRAYER_OF_HEALING, CF_PRIEST_HEAL,
                CF_PRIEST_FLASH_HEAL, CF_PRIEST_FLASH_HEAL2, CF_PRIEST_GREATER_HEAL>() &&
                procExtra & PROC_EX_CRITICAL_HIT && procFlag & PROC_FLAG_SUCCESSFUL_POSITIVE_SPELL)
                return true;
            return false;
        }
        // SPELL_AURA_ADD_TARGET_PROC
        // Chance of proc calculated after.
        if (spellProto->EffectApplyAuraName[0] == SPELL_AURA_ADD_TARGET_TRIGGER)
        {
            // Tous les sorts qui proc sur la victime
            // Puis les autres
            if (isVictim)
                return false;

            // Wolfshead Helm (Part 1 only, from the pig system that does not count the effects :s)
            if (spellProto->Id == 17768)
                return SpellCanTrigger(spellProto, procSpell);
            // Frosty Zap
            if (spellProto->Id == 24392)
                return SpellCanTrigger(spellProto, procSpell);

            return false;
        }
    }
    // Get proc Event Entry
    spellProcEvent = sSpellMgr.GetSpellProcEvent(spellProto->Id);

    // Get EventProcFlag
    uint32 EventProcFlag;
    if (spellProcEvent && spellProcEvent->procFlags) // if exist get custom spellProcEvent->procFlags
        EventProcFlag = spellProcEvent->procFlags;
    else
        EventProcFlag = spellProto->procFlags;       // else get from spell proto
    // Continue if no trigger exist
    if (!EventProcFlag)
        return false;

    // Check spellProcEvent data requirements
    if (!SpellMgr::IsSpellProcEventCanTriggeredBy(spellProcEvent, EventProcFlag, procSpell, procFlag, procExtra))
        return false;

    // In most cases req get honor or XP from kill
    if (EventProcFlag & PROC_FLAG_KILL && GetTypeId() == TYPEID_PLAYER)
    {
        bool allow = ((Player*)this)->isHonorOrXPTarget(pVictim);
        if (!allow)
            return false;
    }
    // Aura added by spell can`t trigger from self (prevent drop charges/do triggers)
    // But except periodic triggers (can triggered from self)
    if (procSpell && procSpell->Id == spellProto->Id && !(EventProcFlag & PROC_FLAG_ON_TAKE_PERIODIC))
        return false;

    // Check if current equipment allows aura to proc
    if (!isVictim && GetTypeId() == TYPEID_PLAYER)
    {
        if (spellProto->EquippedItemClass == ITEM_CLASS_WEAPON)
        {
            Item *item = NULL;
            if (attType == BASE_ATTACK)
                item = ((Player*)this)->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
            else if (attType == OFF_ATTACK)
                item = ((Player*)this)->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
            else
                item = ((Player*)this)->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_RANGED);

            if (!CanUseEquippedWeapon(attType))
                return false;

            if (!item || item->IsBroken() || item->GetProto()->Class != ITEM_CLASS_WEAPON || !((1 << item->GetProto()->SubClass) & spellProto->EquippedItemSubClassMask))
                return false;
        }
        else if (spellProto->EquippedItemClass == ITEM_CLASS_ARMOR)
        {
            // Check if player is wearing shield
            Item *item = ((Player*)this)->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_OFFHAND);
            if (!item || item->IsBroken() || item->GetProto()->Class != ITEM_CLASS_ARMOR || !((1 << item->GetProto()->SubClass) & spellProto->EquippedItemSubClassMask))
                return false;
        }
    }

	if (procSpell)
	{
		if (!spellProto->HasAttribute(SPELL_ATTR_EX3_CAN_PROC_FROM_TRIGGERED_SPECIAL))
			return false;
	}

    // Get chance from spell
    float chance = (float)spellProto->procChance;
    // If in spellProcEvent exist custom chance, chance = spellProcEvent->customChance;
    if (spellProcEvent && spellProcEvent->customChance)
        chance = spellProcEvent->customChance;
    // If PPM exist calculate chance from PPM
    if (!isVictim && spellProcEvent && spellProcEvent->ppmRate != 0)
    {
        uint32 WeaponSpeed = GetAttackTime(attType);
        chance = GetPPMProcChance(WeaponSpeed, spellProcEvent->ppmRate);
    }
    // Apply chance modifier aura
    if (Player* modOwner = GetSpellModOwner())
    {
        modOwner->ApplySpellMod(spellProto->Id, SPELLMOD_CHANCE_OF_SUCCESS, chance);
        if (modOwner->HasOption(PLAYER_CHEAT_ALWAYS_PROC))
            return true;
    }

    return roll_chance_f(chance);
}

SpellAuraProcResult Unit::HandleHasteAuraProc(Unit *pVictim, uint32 damage, Aura* triggeredByAura, SpellEntry const * /*procSpell*/, uint32 /*procFlag*/, uint32 /*procEx*/, uint32 cooldown)
{
    return SPELL_AURA_PROC_OK;
}

SpellAuraProcResult Unit::HandleDummyAuraProc(Unit *pVictim, uint32 damage, Aura* triggeredByAura, SpellEntry const * procSpell, uint32 procFlag, uint32 procEx, uint32 cooldown)
{
    SpellEntry const *dummySpell = triggeredByAura->GetSpellProto();
	SpellEffectIndex effIndex = triggeredByAura->GetEffIndex();
    int32  triggerAmount = triggeredByAura->GetModifier()->m_amount;

    Item* castItem = triggeredByAura->GetCastItemGuid() && GetTypeId() == TYPEID_PLAYER
                     ? ((Player*)this)->GetItemByGuid(triggeredByAura->GetCastItemGuid()) : NULL;

    uint32 triggered_spell_id = 0;
    Unit* target = pVictim;
    int32  basepoints[MAX_EFFECT_INDEX] = {0, 0, 0};


    switch (dummySpell->SpellFamilyName)
    {
        case SPELLFAMILY_GENERIC:
        {
            switch (dummySpell->Id)
            {
                // Eye for an Eye
                case 9799:
                case 25988:
                {
                    // prevent damage back from weapon special attacks
                    if (!procSpell || procSpell->DmgClass != SPELL_DAMAGE_CLASS_MAGIC)
                        return SPELL_AURA_PROC_FAILED;

                    // return damage % to attacker but < 50% own total health
                    basepoints[0] = triggerAmount * int32(damage) / 100;
                    if (basepoints[0] > (int32)GetMaxHealth() / 2)
                        basepoints[0] = (int32)GetMaxHealth() / 2;

                    triggered_spell_id = 25997;
                    break;
                }
				// Sweeping Strikes
				case 12292:
				case 18765:
				{
					// Prevent chain of triggered spell from same triggered spell
					if (procSpell && procSpell->Id == 26654)
						return SPELL_AURA_PROC_FAILED;

					if (procSpell && procSpell->Id == 12723)
						return SPELL_AURA_PROC_FAILED;

					target = SelectRandomUnfriendlyTarget(pVictim);
					if (!target)
						return SPELL_AURA_PROC_FAILED;

					// Case for Execute. This will only run when procced by Execute
					if (procSpell && procSpell->Id == 20647)
					{

						if (pVictim->GetHealthPercent() < 20.0f && target->GetHealthPercent() < 20.0f)  // If Both Target A and target B is sub 20% do full damage
						{
							basepoints[0] = damage * 100 / CalcArmorReducedDamage(pVictim, 100);
							triggered_spell_id = 12723; //Note this SS id deals 1 damage by itself (Cannot crit)
						}
						else if (pVictim->GetHealthPercent() < 20.0f)	// If only Target A is sub 20% and target B is over 20% do Basic attack damage
						{
							triggered_spell_id = 26654;	// This SS deals damage equal to AA also this spell ID can crit ?? Maybe this explains the rumor of SS criting since it only scales with spell crit ? = 5% crit.
						}
						else // Full damage on anything else (Shouldn't really ever be used) since execute can only be used sub 20% anyway.                                             
						{
							basepoints[0] = damage * 100 / CalcArmorReducedDamage(pVictim, 100);
							triggered_spell_id = 12723;	//Note this SS id deals 1 damage by itself (Cannot crit)
						}
					}
					else // Full damage on anything else 
					{
						basepoints[0] = damage * 100 / CalcArmorReducedDamage(pVictim, 100);
						triggered_spell_id = 12723;	//Note this SS id deals 1 damage by itself (Cannot crit)
					}

					break;
				}
                // Retaliation
                case 20230:
                {
                    // check attack comes not from behind
                    if (!HasInArc(M_PI_F, pVictim))
                        return SPELL_AURA_PROC_FAILED;

                    triggered_spell_id = 22858;
                    break;
                }
                // Twisted Reflection (boss spell)
                case 21063:
                    triggered_spell_id = 21064;
                    break;
                // Unstable Power
                case 24658:
                {
                    // Need remove one 24659 aura
                    RemoveAuraHolderFromStack(24659);
                    return SPELL_AURA_PROC_OK;
                }
                // Restless Strength
                case 24661:
                {
                    // Need remove one 24662 aura
                    RemoveAuraHolderFromStack(24662);
                    return SPELL_AURA_PROC_OK;
                }
                // Viscidus Frost Weakness
                case 25926:
                {
                    if (!procSpell)
                        return SPELL_AURA_PROC_FAILED;

                    if (GetSchoolMask(procSpell->School) == SPELL_SCHOOL_MASK_FROST)
                    {
                        ++triggeredByAura->GetModifier()->m_amount;
                        triggerAmount = triggeredByAura->GetModifier()->m_amount;

                        if (triggerAmount == 100)
                            triggered_spell_id = 26034; // Slowed
                        else if (triggerAmount == 150)
                            triggered_spell_id = 26036; // Slowed more
                        else if (triggerAmount == 200)
                            triggered_spell_id = 25937; // Freeze
                    }

                    break;
                }
                // Viscidus Freeze
                case 25937:
                {
                    if (procSpell)
                    {
                        if (GetSchoolMask(procSpell->School) != SPELL_SCHOOL_MASK_NORMAL)
                            return SPELL_AURA_PROC_FAILED;
                    }
                    else
                        return SPELL_AURA_PROC_FAILED;

                    ++triggeredByAura->GetModifier()->m_amount;
                    triggerAmount = triggeredByAura->GetModifier()->m_amount;

                    if (triggerAmount == 25)
                        MonsterTextEmote(-1531044, NULL); // Cracks
                    else if (triggerAmount == 50)
                        MonsterTextEmote(-1531045, NULL); // Shatter
                    else if (triggerAmount == 75)
                    {
                        RemoveAurasDueToSpell(25937);
                        triggered_spell_id = 25938; // Explode
                    }

                    break;
                }
                // Adaptive Warding (Frostfire Regalia set)
                case 28764:
                {
                    if (!procSpell)
                        return SPELL_AURA_PROC_FAILED;

                    // find Mage Armor
                    bool found = false;
                    AuraList const& mRegenInterupt = GetAurasByType(SPELL_AURA_MOD_MANA_REGEN_INTERRUPT);
                    for (AuraList::const_iterator iter = mRegenInterupt.begin(); iter != mRegenInterupt.end(); ++iter)
                    {
                        if (SpellEntry const* iterSpellProto = (*iter)->GetSpellProto())
                        {
                            if (iterSpellProto->IsFitToFamily<SPELLFAMILY_MAGE, CF_MAGE_MAGE_ARMOR>())
                            {
                                found = true;
                                break;
                            }
                        }
                    }
                    if (!found)
                        return SPELL_AURA_PROC_FAILED;

                    switch (GetFirstSchoolInMask(GetSpellSchoolMask(procSpell)))
                    {
                        case SPELL_SCHOOL_NORMAL:
                        case SPELL_SCHOOL_HOLY:
                            return SPELL_AURA_PROC_FAILED;                   // ignored
                        case SPELL_SCHOOL_FIRE:
                            triggered_spell_id = 28765;
                            break;
                        case SPELL_SCHOOL_NATURE:
                            triggered_spell_id = 28768;
                            break;
                        case SPELL_SCHOOL_FROST:
                            triggered_spell_id = 28766;
                            break;
                        case SPELL_SCHOOL_SHADOW:
                            triggered_spell_id = 28769;
                            break;
                        case SPELL_SCHOOL_ARCANE:
                            triggered_spell_id = 28770;
                            break;
                        default:
                            return SPELL_AURA_PROC_FAILED;
                    }

                    target = this;
                    break;
                }
                // Obsidian Armor (Justice Bearer`s Pauldrons shoulder)
                case 27539:
                {
                    if (!procSpell)
                        return SPELL_AURA_PROC_FAILED;

                    switch (GetFirstSchoolInMask(GetSpellSchoolMask(procSpell)))
                    {
                        case SPELL_SCHOOL_NORMAL:
                            return SPELL_AURA_PROC_FAILED;                   // ignore
                        case SPELL_SCHOOL_HOLY:
                            triggered_spell_id = 27536;
                            break;
                        case SPELL_SCHOOL_FIRE:
                            triggered_spell_id = 27533;
                            break;
                        case SPELL_SCHOOL_NATURE:
                            triggered_spell_id = 27538;
                            break;
                        case SPELL_SCHOOL_FROST:
                            triggered_spell_id = 27534;
                            break;
                        case SPELL_SCHOOL_SHADOW:
                            triggered_spell_id = 27535;
                            break;
                        case SPELL_SCHOOL_ARCANE:
                            triggered_spell_id = 27540;
                            break;
                        default:
                            return SPELL_AURA_PROC_FAILED;
                    }

                    target = this;
                    break;
                }
            }
            break;
        }
        case SPELLFAMILY_MAGE:
        {
            // Magic Absorption
            if (dummySpell->SpellIconID == 459)             // only this spell have SpellIconID == 459 and dummy aura
            {
                if (getPowerType() != POWER_MANA)
                    return SPELL_AURA_PROC_FAILED;

                // mana reward
                basepoints[0] = (triggerAmount * GetMaxPower(POWER_MANA) / 100);
                target = this;
                triggered_spell_id = 29442;
                break;
            }
            // Master of Elements
            if (dummySpell->SpellIconID == 1920)
            {
                if (!procSpell)
                    return SPELL_AURA_PROC_FAILED;

                // mana cost save
                int32 cost = procSpell->manaCost + procSpell->ManaCostPercentage * GetCreateMana() / 100;
                basepoints[0] = cost * triggerAmount / 100;
                if (basepoints[0] <= 0)
                    return SPELL_AURA_PROC_FAILED;

                target = this;
                triggered_spell_id = 29077;
                break;
            }
            switch (dummySpell->Id)
            {
                // Ignite
                case 11119:
                case 11120:
                case 12846:
                case 12847:
                case 12848:
                {
		    
                    switch (dummySpell->Id)
                    {
                        case 11119:
                            basepoints[0] = int32(0.04f * damage);
                            break;
                        case 11120:
                            basepoints[0] = int32(0.08f * damage);
                            break;
                        case 12846:
                            basepoints[0] = int32(0.12f * damage);
                            break;
                        case 12847:
                            basepoints[0] = int32(0.16f * damage);
                            break;
                        case 12848:
                            basepoints[0] = int32(0.20f * damage);
                            break;
                        default:
                            sLog.outError("Unit::HandleDummyAuraProc: non handled spell id: %u (IG)", dummySpell->Id);
                            return SPELL_AURA_PROC_FAILED;
                    }

		    // Get current Ignite Aura if exist
		    Aura *igniteAura = target->GetAura(12654, EFFECT_INDEX_0);

		    if (igniteAura)
		    {
			Modifier *igniteModifier = igniteAura->GetModifier();
			SpellAuraHolder* igniteHolder = igniteAura->GetHolder();

			int32 tickDamage = igniteModifier->m_amount;

			bool notAtMaxStack = igniteAura->GetStackAmount() < 5;

			// If 1 of 2 ticks of ignite have been applied (2s),
			// Halve damage to apply correct remaining damage on 4s refresh
			if (1 == igniteAura->GetAuraTicks() && notAtMaxStack)
			    tickDamage = tickDamage / 2 + 1;

			bool reapplyIgnite = igniteAura->GetAuraTicks() >= igniteAura->GetAuraMaxTicks();

			if (!reapplyIgnite)
			{

		    	    if (notAtMaxStack)
		    	    {
			        tickDamage += basepoints[0];

				igniteHolder->ModStackAmount(1);

			        // Update DOT damage
			        igniteModifier->m_amount = tickDamage;
			        igniteAura->ApplyModifier(true, true, false);
		            } 
			    else
			        igniteHolder->SetStackAmount(5);

			    // Refresh Ignite Stack
			    igniteHolder->Refresh(igniteAura->GetCaster(), target, igniteHolder );

			    return SPELL_AURA_PROC_OK;
			}
			// All damage done, remove and continue to reapply
			target->RemoveAurasDueToSpell(12654);	
		    }
				
		    // No Ignite found, apply Ignite Aura
                    triggered_spell_id = 12654;
                    break;
                }
                // Combustion
                case 11129:
                {
                    //last charge and crit
                    if (triggeredByAura->GetHolder()->GetAuraCharges() <= 1 && (procEx & PROC_EX_CRITICAL_HIT))
                    {
                        RemoveAurasDueToSpell(28682);       //-> remove Combustion auras
                        return SPELL_AURA_PROC_OK;                        // charge counting (will removed)
                    }

                    CastSpell(this, 28682, true, castItem, triggeredByAura);
                    return (procEx & PROC_EX_CRITICAL_HIT) ? SPELL_AURA_PROC_OK : SPELL_AURA_PROC_FAILED; // charge update only at crit hits, no hidden cooldowns
                }
            }
            break;
        }
        case SPELLFAMILY_WARRIOR:
        {
            // Attaques circulaires
            if (dummySpell->Id == 12292)
            {
                target = SelectRandomUnfriendlyTarget();
                if (!target)
                    return SPELL_AURA_PROC_FAILED;
                triggered_spell_id = 26654;
            }
            // Retaliation
            if (dummySpell->IsFitToFamilyMask<CF_WARRIOR_RETALIATION>())
            {
                // check attack comes not from behind
                if (!HasInArc(M_PI_F, pVictim))
                    return SPELL_AURA_PROC_FAILED;

                triggered_spell_id = 22858;
                break;
            }
// Second Wind
			if (dummySpell->SpellIconID == 1697)
			{
				// only for spells and hit/crit (trigger start always) and not start from self casted spells (5530 Mace Stun Effect for example)
				if (!procSpell || !(procEx & (PROC_EX_NORMAL_HIT | PROC_EX_CRITICAL_HIT)) || this == pVictim)
					return SPELL_AURA_PROC_FAILED;
				// Need stun or root mechanic
				if (!(GetAllSpellMechanicMask(procSpell) & IMMUNE_TO_ROOT_AND_STUN_MASK))
					return SPELL_AURA_PROC_FAILED;

				switch (dummySpell->Id)
				{
				case 29838: triggered_spell_id = 29842; break;
				case 29834: triggered_spell_id = 29841; break;
				default:
					sLog.outError("Unit::HandleDummyAuraProc: non handled spell id: %u (SW)", dummySpell->Id);
					return SPELL_AURA_PROC_FAILED;
				}

				target = this;
				break;
			}			
            break;

			// Battle Hardened
			if (dummySpell->SpellIconID == 2781)
			{
				// only for spells and hit/crit (trigger start always) and not start from self casted spells (5530 Mace Stun Effect for example)
				if (!procSpell || !(procEx & (PROC_EX_PERIODIC_POSITIVE)) || this == pVictim)
					return SPELL_AURA_PROC_FAILED;				

				if (!(GetAllSpellMechanicMask(procSpell) & IMMUNE_TO_ROOT_AND_STUN_MASK))
					return SPELL_AURA_PROC_FAILED;

				switch (dummySpell->Id)
				{
				case 54100: triggered_spell_id = 29841; break;
				case 54101: triggered_spell_id = 29842; break;
				case 54102: triggered_spell_id = 29843; break;
				default:
					sLog.outError("Unit::HandleDummyAuraProc: non handled spell id: %u (SW)", dummySpell->Id);
					return SPELL_AURA_PROC_FAILED;
				}
					
				target = this;
				break;
			}
            break;
        }
        case SPELLFAMILY_WARLOCK:
		{
        // Seed of Corruption
			if (dummySpell->SpellFamilyFlags && dummySpell->SpellIconID == 1932)
			{
				Modifier* mod = triggeredByAura->GetModifier();
				// if damage is more than need or target die from damage deal finish spell
				if (mod->m_amount <= (int32)damage || GetHealth() <= damage)
				{
					// remember guid before aura delete
					ObjectGuid casterGuid = triggeredByAura->GetCasterGuid();

					// Remove aura (before cast for prevent infinite loop handlers)
					RemoveAurasDueToSpell(triggeredByAura->GetId());

					// Cast finish spell (triggeredByAura already not exist!)
					switch (dummySpell->Id)
					{ 
					case 54731: 
						CastSpell(this, 54739, true, castItem, nullptr, casterGuid);
						break;
					case 54732: 
						CastSpell(this, 54740, true, castItem, nullptr, casterGuid);
						break;
					case 54733:
						CastSpell(this, 54741, true, castItem, nullptr, casterGuid);
						break;
					case 54734:
						CastSpell(this, 54742, true, castItem, nullptr, casterGuid);
						break;
					case 54735:
						CastSpell(this, 54743, true, castItem, nullptr, casterGuid);
						break;
					}
				//	CastSpell(this, 27285, true, castItem, nullptr, casterGuid);
					return SPELL_AURA_PROC_OK;              // no hidden cooldown
				}

				// Damage counting
				mod->m_amount -= damage;
				return SPELL_AURA_PROC_OK;
			}
			// Seed of Corruption (Mobs cast) - no die req
			if (!dummySpell->SpellFamilyFlags && dummySpell->SpellIconID == 1932)
			{
				Modifier* mod = triggeredByAura->GetModifier();
				// if damage is more than need deal finish spell
				if (mod->m_amount <= (int32)damage)
				{
					// remember guid before aura delete
					ObjectGuid casterGuid = triggeredByAura->GetCasterGuid();

					// Remove aura (before cast for prevent infinite loop handlers)
					RemoveAurasDueToSpell(triggeredByAura->GetId());

					// Cast finish spell (triggeredByAura already not exist!)
					CastSpell(this, 32865, true, castItem, nullptr, casterGuid);
					return SPELL_AURA_PROC_OK;              // no hidden cooldown
				}
				// Damage counting
				mod->m_amount -= damage;
				return SPELL_AURA_PROC_OK;
			}
				// Nightfall
			case 18094:
			case 18095:
			case 54266:
			case 54267:
			case 54268:
			{
				target = this;
				triggered_spell_id = 17941;
				break;
			}
			// Soul Leech
			case 30293:
			case 30295:
			case 30296:
			{
				// health
				basepoints[0] = int32(damage * triggerAmount / 100);
				target = this;
				triggered_spell_id = 30294;
				break;
			}
			// Shadowflame (Voidheart Raiment set bonus)
			case 37377:
			{
				triggered_spell_id = 37379;
				break;
			}
			// Pet Healing (Corruptor Raiment or Rift Stalker Armor)
			case 37381:
			{
				target = GetPet();
				if (!target)
					return SPELL_AURA_PROC_FAILED;

				// heal amount
				basepoints[0] = damage * triggerAmount / 100;
				triggered_spell_id = 37382;
				break;
			}
			// Pet Healing 
			case 54323:
			case 54324:
			case 54325:
			case 54326:
			case 54327:
			{
				target = GetPet();
				if (!target)
					return SPELL_AURA_PROC_FAILED;

				// heal amount
				//basepoints[0] = damage * triggerAmount / 100;
				basepoints[0] = (GetHealth() + target->GetHealth())/ 25;
				basepoints[1] = (GetHealth() + target->GetHealth()) / 25;
				triggered_spell_id = 54756;
				break;
			}
			// Shadowflame Hellfire (Voidheart Raiment set bonus)
			case 39437:
			{
				triggered_spell_id = 37378;
				break;
			}
			case 547777:
			{
				triggered_spell_id = 37378;
				break;
			}
			break;
		}
        case SPELLFAMILY_PRIEST:
        {
            switch (dummySpell->Id)
            {
		// Vampiric Touch
		if (dummySpell->SpellFamilyFlags & uint64(0x0000040000000000))
		{
			if (!pVictim || !pVictim->isAlive())
				return SPELL_AURA_PROC_FAILED;

			// pVictim is caster of aura
			if (triggeredByAura->GetCasterGuid() != pVictim->GetObjectGuid())
				return SPELL_AURA_PROC_FAILED;

			// energize amount
			basepoints[0] = triggerAmount * damage / 100;
			pVictim->CastCustomSpell(pVictim, 34919, &basepoints[0], nullptr, nullptr, true, castItem, triggeredByAura);
			return SPELL_AURA_PROC_OK;                  // no hidden cooldown
		}

                // Vampiric Embrace
                case 15286:
                {
                    if (!pVictim || !pVictim->isAlive())
                        return SPELL_AURA_PROC_FAILED;

                    // pVictim is caster of aura
                    if (triggeredByAura->GetCasterGuid() != pVictim->GetObjectGuid())
                        return SPELL_AURA_PROC_FAILED;

                    // heal amount
                    basepoints[0] = triggerAmount * damage / 100;
                    pVictim->CastCustomSpell(pVictim, 15290, &basepoints[0], NULL, NULL, true, castItem, triggeredByAura);
                    return SPELL_AURA_PROC_OK;                                // no hidden cooldown
                }
                // Oracle Healing Bonus ("Garments of the Oracle" set)
                case 26169:
                {
                    // heal amount
                    basepoints[0] = int32(damage * 10 / 100);
                    target = this;
                    triggered_spell_id = 26170;
                    break;
                }
	// Frozen Shadoweave (Shadow's Embrace set) warning! its not only priest set
				case 39372:
				{
					if (!procSpell || (GetSpellSchoolMask(procSpell) & (SPELL_SCHOOL_MASK_FROST | SPELL_SCHOOL_MASK_SHADOW)) == 0)
						return SPELL_AURA_PROC_FAILED;

					// heal amount
					basepoints[0] = damage * triggerAmount / 100;
					target = this;
					triggered_spell_id = 39373;
					break;
				}
                // Greater Heal (Vestments of Faith (Priest Tier 3) - 4 pieces bonus)
                case 28809:
                {
                    triggered_spell_id = 28810;
                    break;
                }
            }
            break;
        }
        case SPELLFAMILY_DRUID:
        {
            switch (dummySpell->Id)
            {
                // Healing Touch (Dreamwalker Raiment set)
                case 28719:
                {
                    // mana back
                    basepoints[0] = int32(procSpell->manaCost * 30 / 100);
                    target = this;
                    triggered_spell_id = 28742;
                    break;
                }
                // Healing Touch Refund (Idol of Longevity trinket)
                case 28847:
                {
                    target = this;
                    triggered_spell_id = 28848;
                    break;
                }
		// Natural Perfection
				case 54418:
				case 54419:
				case 54420:
				{
					switch (dummySpell->Id)
					{
					case 54418: basepoints[0] = int32(0.1f * damage); break;
					case 54419: basepoints[0] = int32(0.2f * damage); break;
					case 54420: basepoints[0] = int32(0.3f * damage); break;
					default:
						sLog.outError("Unit::HandleDummyAuraProc: non handled spell id: %u (IG)", dummySpell->Id);
						return SPELL_AURA_PROC_FAILED;
					}

					triggered_spell_id = 54417;
					break;
				}
				// Maim Interrupt
				case 44835:
				{
					// Deadly Interrupt Effect
					triggered_spell_id = 32747;
					break;
				}
            }
            break;
        }
        case SPELLFAMILY_ROGUE:
        {
            switch (dummySpell->Id)
            {
                // Clean Escape
                case 23582:
                    // triggered spell have same masks and etc with main Vanish spell
                    if (!procSpell || procSpell->Effect[EFFECT_INDEX_0] == SPELL_EFFECT_NONE)
                        return SPELL_AURA_PROC_FAILED;
                    triggered_spell_id = 23583;
                    break;
             	// Deadly Throw Interrupt
		case 32748:
		{
			// Prevent cast Deadly Throw Interrupt on self from last effect (apply dummy) of Deadly Throw
			if (this == pVictim)
				return SPELL_AURA_PROC_FAILED;

			triggered_spell_id = 32747;
			break;
		}
                // Blade Flurry
                case 13877:
                {
                    // prevent chain of triggered spell from same triggered spell
                    if (procSpell && procSpell->Id == 22482)
                        return SPELL_AURA_PROC_FAILED;

                    target = SelectRandomUnfriendlyTarget(pVictim);

                    if (!target)
                        return SPELL_AURA_PROC_FAILED;

                     // Reconstitute damage before armor reduction
                    basepoints[0] = damage * 100 / CalcArmorReducedDamage(pVictim, 100);

                    triggered_spell_id = 22482;
                    break;
                }
            }
            break;
        }
        case SPELLFAMILY_HUNTER:
            break;
        case SPELLFAMILY_PALADIN:
        {
            // Seal of Righteousness - melee proc dummy
            if ((dummySpell->IsFitToFamilyMask<CF_PALADIN_SEALS>()) && triggeredByAura->GetEffIndex() == EFFECT_INDEX_0)
            {
                if (GetTypeId() != TYPEID_PLAYER)
                    return SPELL_AURA_PROC_FAILED;

                uint32 spellId;
                switch (triggeredByAura->GetId())
                {
                    case 20154:
                    case 21084:
                        spellId = 25742;
                        break;     // Rank 1
                    case 20287:
                        spellId = 25740;
                        break;     // Rank 2
                    case 20288:
                        spellId = 25739;
                        break;     // Rank 3
                    case 20289:
                        spellId = 25738;
                        break;     // Rank 4
                    case 20290:
                        spellId = 25737;
                        break;     // Rank 5
                    case 20291:
                        spellId = 25736;
                        break;     // Rank 6
                    case 20292:
                        spellId = 25735;
                        break;     // Rank 7
                    case 20293:
                        spellId = 25713;
                        break;     // Rank 8
                    default:
                        sLog.outError("Unit::HandleDummyAuraProc: non handled possibly SoR (Id = %u)", triggeredByAura->GetId());
                        return SPELL_AURA_PROC_FAILED;
                }
                float MAX_WSP = 4.0f;
                float MIN_WSP = 1.5f;

                Item *item = ((Player*)this)->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);
                float speed = (item ? item->GetProto()->Delay : BASE_ATTACK_TIME) / 1000.0f;

                float minDmg = triggerAmount / 87.0f;
                float maxDmg = triggerAmount / 25.0f;

                float damageBasePoints = (maxDmg - minDmg) * ((speed - MIN_WSP) / (MAX_WSP - MIN_WSP)) + minDmg;

                int32 damagePoint = urand(0, 1) ? floor(damageBasePoints) : ceil(damageBasePoints);

                // apply damage bonuses manually
                if (damagePoint >= 0)
                {
                    damagePoint = SpellDamageBonusDone(pVictim, dummySpell, damagePoint, SPELL_DIRECT_DAMAGE);
                    damagePoint = pVictim->SpellDamageBonusTaken(this, dummySpell, damagePoint, SPELL_DIRECT_DAMAGE);
                }

                CastCustomSpell(pVictim, spellId, &damagePoint, NULL, NULL, true, NULL, triggeredByAura);
                // Seal of Righteousness can proc weapon enchants. mechanic removed in 2.1.0
                ((Player*)this)->CastItemCombatSpell(pVictim, BASE_ATTACK);
                return SPELL_AURA_PROC_OK;                                // no hidden cooldown
            }

            switch (dummySpell->Id)
            {
                // Holy Power (Redemption Armor set)
                case 28789:
                {
                    if (!pVictim)
                        return SPELL_AURA_PROC_FAILED;

                    // Set class defined buff
                    switch (pVictim->getClass())
                    {
                        case CLASS_PALADIN:
                        case CLASS_PRIEST:
                        case CLASS_SHAMAN:
                        case CLASS_DRUID:
                            triggered_spell_id = 28795;     // Increases the friendly target's mana regeneration by $s1 per 5 sec. for $d.
                            break;
                        case CLASS_MAGE:
                        case CLASS_WARLOCK:
                            triggered_spell_id = 28793;     // Increases the friendly target's spell damage and healing by up to $s1 for $d.
                            break;
                        case CLASS_HUNTER:
                        case CLASS_ROGUE:
                            triggered_spell_id = 28791;     // Increases the friendly target's attack power by $s1 for $d.
                            break;
                        case CLASS_WARRIOR:
                            triggered_spell_id = 28790;     // Increases the friendly target's armor
                            break;
                        default:
                            return SPELL_AURA_PROC_FAILED;
                    }
                    break;
                }

// Spiritual Attunement
				case 31785:
				case 33776:
				{
					// if healed by another unit (pVictim)
					if (this == pVictim)
						return SPELL_AURA_PROC_FAILED;

					// dont count overhealing
					uint32 diff = GetMaxHealth() - GetHealth();
					if (!diff)
						return SPELL_AURA_PROC_FAILED;
					basepoints[0] = triggerAmount * (damage > diff ? diff : damage) / 100;
					target = this;
					triggered_spell_id = 31786;
					break;
				}
				// Seal of Vengeance (damage calc on apply aura)
				case 31801:
				{
					if (effIndex != EFFECT_INDEX_0)         // effect 1,2 used by seal unleashing code
						return SPELL_AURA_PROC_FAILED;

					triggered_spell_id = 31803;

					// Since Patch 2.2.0 Seal of Vengeance does additional damage against fully stacked targets
					// Add 5-stack effect from Holy Vengeance
					const SpellAuraHolder* existing = target->GetSpellAuraHolder(31803, GetObjectGuid());
					if (existing && existing->GetStackAmount() >= 5)
						CastSpell(target, 42463, true, nullptr, triggeredByAura);
					break;
				}
				case 54647:
				{
					if (effIndex != EFFECT_INDEX_0)         // effect 1,2 used by seal unleashing code
						return SPELL_AURA_PROC_FAILED;

					triggered_spell_id = 54648;

					// Since Patch 2.2.0 Seal of Vengeance does additional damage against fully stacked targets
					// Add 5-stack effect from Holy Vengeance
					const SpellAuraHolder* existing = target->GetSpellAuraHolder(54648, GetObjectGuid());
					if (existing && existing->GetStackAmount() >= 5)
						CastSpell(target, 54650, true, nullptr, triggeredByAura);
					break;
				}
				// Light's Grace
				case 54438:
				case 54439:
				case 54440:
				case 54441:
				{
					switch (dummySpell->Id)
					{
					case 54438: basepoints[0] = int32(0.05f * damage); break;
					case 54439: basepoints[0] = int32(0.1f * damage); break;
					case 54440: basepoints[0] = int32(0.15f * damage); break;
					case 54441: basepoints[0] = int32(0.2f * damage); break;
					default:
						sLog.outError("Unit::HandleDummyAuraProc: non handled spell id: %u (IG)", dummySpell->Id);
						return SPELL_AURA_PROC_FAILED;
					}

					triggered_spell_id = 54442;
					break;
				}
            }
            break;
        }
        case SPELLFAMILY_SHAMAN:
        {
            switch (dummySpell->Id)
            {
                // Totemic Power (The Earthshatterer set)
                case 28823:
                {
                    if (!pVictim)
                        return SPELL_AURA_PROC_FAILED;

                    // Set class defined buff
                    switch (pVictim->getClass())
                    {
                        case CLASS_PALADIN:
                        case CLASS_PRIEST:
                        case CLASS_SHAMAN:
                        case CLASS_DRUID:
                            triggered_spell_id = 28824;     // Increases the friendly target's mana regeneration by $s1 per 5 sec. for $d.
                            break;
                        case CLASS_MAGE:
                        case CLASS_WARLOCK:
                            triggered_spell_id = 28825;     // Increases the friendly target's spell damage and healing by up to $s1 for $d.
                            break;
                        case CLASS_HUNTER:
                        case CLASS_ROGUE:
                            triggered_spell_id = 28826;     // Increases the friendly target's attack power by $s1 for $d.
                            break;
                        case CLASS_WARRIOR:
                            triggered_spell_id = 28827;     // Increases the friendly target's armor
                            break;
                        default:
                            return SPELL_AURA_PROC_FAILED;
                    }
                    break;
                }
                // Lesser Healing Wave (Totem of Flowing Water Relic)
                case 28849:
                {
                    target = this;
                    triggered_spell_id = 28850;
                    break;
                }
		// Earth Shield
				case 974:                                  // Earth Shield				
				case 32593:
				case 32594:
				{
					if (GetTypeId() != TYPEID_PLAYER)
						return SPELL_AURA_PROC_FAILED;

					// heal
					basepoints[0] = triggerAmount;
					target = this;
					triggered_spell_id = 371;
					break;
				}
				// Lightning Overload
				case 30675:                                 				
				case 30678:
				case 30679:
				case 30680:
				case 30681:
				{
					if (!procSpell || GetTypeId() != TYPEID_PLAYER || !pVictim)
						return SPELL_AURA_PROC_FAILED;

					// custom cooldown processing case
					if (cooldown && GetTypeId() == TYPEID_PLAYER && ((Player*)this)->HasSpellCooldown(dummySpell->Id))
						return SPELL_AURA_PROC_FAILED;

					uint32 spellId;
					// Every Lightning Bolt and Chain Lightning spell have duplicate vs half damage and zero cost
					switch (procSpell->Id)
					{
						// Lightning Bolt
					case   403: spellId = 45284; break;     // Rank  1
					case   529: spellId = 45286; break;     // Rank  2
					case   548: spellId = 45287; break;     // Rank  3
					case   915: spellId = 45288; break;     // Rank  4
					case   943: spellId = 45289; break;     // Rank  5
					case  6041: spellId = 45290; break;     // Rank  6
					case 10391: spellId = 45291; break;     // Rank  7
					case 10392: spellId = 45292; break;     // Rank  8
					case 15207: spellId = 45293; break;     // Rank  9
					case 15208: spellId = 45294; break;     // Rank 10
					case 25448: spellId = 45295; break;     // Rank 11
					case 25449: spellId = 45296; break;     // Rank 12
															// Chain Lightning
					case   421: spellId = 45297; break;     // Rank  1
					case   930: spellId = 45298; break;     // Rank  2
					case  2860: spellId = 45299; break;     // Rank  3
					case 10605: spellId = 45300; break;     // Rank  4
					case 25439: spellId = 45301; break;     // Rank  5
					case 25442: spellId = 45302; break;     // Rank  6
					default:
						sLog.outError("Unit::HandleDummyAuraProc: non handled spell id: %u (LO)", procSpell->Id);
						return SPELL_AURA_PROC_FAILED;
					}

					// Remove cooldown (Chain Lightning - have Category Recovery time)
					if (procSpell->SpellFamilyFlags & uint64(0x0000000000000002))
						((Player*)this)->RemoveSpellCooldown(spellId);

					CastSpell(pVictim, spellId, true, castItem, triggeredByAura);

					if (cooldown && GetTypeId() == TYPEID_PLAYER)
						((Player*)this)->AddSpellCooldown(dummySpell->Id, 0, time(nullptr) + cooldown);

					return SPELL_AURA_PROC_OK;
				}
				// Tidal Force
				case 54906:
				{
					// last charge and crit
					if (triggeredByAura->GetHolder()->GetAuraCharges() <= 1 && (procEx & PROC_EX_CRITICAL_HIT))
					{
						RemoveAurasDueToSpell(54907);       //-> remove Combustion auras
						return SPELL_AURA_PROC_OK;          // charge counting (will removed)
					}

					CastSpell(this, 54907, true, castItem, triggeredByAura);
					return (procEx & PROC_EX_CRITICAL_HIT) ? SPELL_AURA_PROC_OK : SPELL_AURA_PROC_FAILED; // charge update only at crit hits, no hidden cooldowns
				}

				// Telluric Waves
				case 54908:
				case 54909:
				case 54910:
				{
					if (procEx & PROC_EX_CRITICAL_HIT)
					{
					
						int32 critical_chance = int32(pVictim->GetUnitCriticalChance(procSpell, GetSchoolMask(SPELL_SCHOOL_NATURE)));

						pVictim->CastCustomSpell(pVictim, 54911, &critical_chance, nullptr, nullptr, true, castItem, triggeredByAura);
						
					}

					
					return SPELL_AURA_PROC_OK;
				}

            }
            break;
        }
        default:
            break;
    }

    // processed charge only counting case
    if (!triggered_spell_id)
        return SPELL_AURA_PROC_OK;

    SpellEntry const* triggerEntry = sSpellMgr.GetSpellEntry(triggered_spell_id);

    if (!triggerEntry)
    {
        sLog.outError("Unit::HandleDummyAuraProc: Spell %u have not existed triggered spell %u", dummySpell->Id, triggered_spell_id);
        return SPELL_AURA_PROC_FAILED;
    }

    // default case
    if (!target || target != this && !target->isAlive())
        return SPELL_AURA_PROC_FAILED;

    if (cooldown && GetTypeId() == TYPEID_PLAYER && ((Player*)this)->HasSpellCooldown(triggered_spell_id))
        return SPELL_AURA_PROC_FAILED;

    if (basepoints[EFFECT_INDEX_0] || basepoints[EFFECT_INDEX_1] || basepoints[EFFECT_INDEX_2])
        CastCustomSpell(target, triggered_spell_id,
                        basepoints[EFFECT_INDEX_0] ? &basepoints[EFFECT_INDEX_0] : NULL,
                        basepoints[EFFECT_INDEX_1] ? &basepoints[EFFECT_INDEX_1] : NULL,
                        basepoints[EFFECT_INDEX_2] ? &basepoints[EFFECT_INDEX_2] : NULL,
                        true, castItem, triggeredByAura);
    else
        CastSpell(target, triggered_spell_id, true, castItem, triggeredByAura);

    if (cooldown && GetTypeId() == TYPEID_PLAYER)
        ((Player*)this)->AddSpellCooldown(triggered_spell_id, 0, time(NULL) + cooldown);

    return SPELL_AURA_PROC_OK;
}

SpellAuraProcResult Unit::HandleProcTriggerSpellAuraProc(Unit *pVictim, uint32 damage, Aura* triggeredByAura, SpellEntry const *procSpell, uint32 procFlags, uint32 procEx, uint32 cooldown)
{
    // Get triggered aura spell info
    SpellEntry const* auraSpellInfo = triggeredByAura->GetSpellProto();

    // Basepoints of trigger aura
    int32 triggerAmount = triggeredByAura->GetModifier()->m_amount;

    // Set trigger spell id, target, custom basepoints
    uint32 trigger_spell_id = auraSpellInfo->EffectTriggerSpell[triggeredByAura->GetEffIndex()];
    Unit*  target = NULL;
    int32  basepoints[MAX_EFFECT_INDEX] = {0, 0, 0};

    Item* castItem = triggeredByAura->GetCastItemGuid() && GetTypeId() == TYPEID_PLAYER
                     ? ((Player*)this)->GetItemByGuid(triggeredByAura->GetCastItemGuid()) : NULL;

    // Try handle unknown trigger spells
    // Custom requirements (not listed in procEx) Warning! damage dealing after this
    // Custom triggered spells
    switch (auraSpellInfo->SpellFamilyName)
    {
        case SPELLFAMILY_GENERIC:
            switch (auraSpellInfo->Id)
            {
                //case 5301:  break;                        // Defensive State (DND)
                //case 7137:  break;                        // Shadow Charge (Rank 1)
                //case 7377:  break;                        // Take Immune Periodic Damage <Not Working>
                //case 13358: break;                        // Defensive State (DND)
                //case 16092: break;                        // Defensive State (DND)
                //case 18943: break;                        // Double Attack
                //case 19194: break;                        // Double Attack
                //case 19817: break;                        // Double Attack
                //case 19818: break;                        // Double Attack
                //case 22835: break;                        // Drunken Rage
                //    trigger_spell_id = 14822; break;
                case 23780:                                 // Aegis of Preservation (Aegis of Preservation trinket)
                    trigger_spell_id = 23781;
                    break;
                //case 24949: break;                        // Defensive State 2 (DND)
				case 24905:                                 // Moonkin Form (Passive)
				{
					// Elune's Touch (instead non-existed triggered spell) 30% from AP
					trigger_spell_id = 33926;
					basepoints[0] = GetTotalAttackPowerValue(BASE_ATTACK) * 30 / 100;
					target = this;
					break;
				}

                case 27522:                                 // Mana Drain Trigger
                {
                    // On successful melee or ranged attack gain $29471s1 mana and if possible drain $27526s1 mana from the target.
                    if (isAlive())
                        CastSpell(this, 29471, true, castItem, triggeredByAura);
                    if (pVictim && pVictim->isAlive())
                        CastSpell(pVictim, 27526, true, castItem, triggeredByAura);
                    return SPELL_AURA_PROC_OK;
                }
                case 31255:                                 // Deadly Swiftness (Rank 1)
                {
                    // whenever you deal damage to a target who is below 20% health.
                    if (pVictim->GetHealth() > pVictim->GetMaxHealth() / 5)
                        return SPELL_AURA_PROC_FAILED;

                    target = this;
                    trigger_spell_id = 22588;
                    break;
                }
                // Nostalrius
                case 28200:
                {
                    if (procFlags & (PROC_FLAG_SUCCESSFUL_POSITIVE_AOE_HIT | PROC_FLAG_SUCCESSFUL_AOE_SPELL_HIT))
                    {
                        if (procFlags != PROC_FLAG_SUCCESSFUL_POSITIVE_AOE_HIT &&
                                procFlags != PROC_FLAG_SUCCESSFUL_AOE_SPELL_HIT)
                            return SPELL_AURA_PROC_FAILED;
                    }
                    break;
                }
	case 33896:                                 // Desperate Defense (Stonescythe Whelp, Stonescythe Alpha, Stonescythe Ambusher)
					trigger_spell_id = 33898;
					break;      
					// case 34082: break;                   // Advantaged State (DND)
					// case 34783: break:                   // Spell Reflection
					// case 35205: break:                   // Vanish
					// case 35321: break;                   // Gushing Wound
				case 36096:                             // Spell Reflection
					return SPELL_AURA_PROC_OK;          // Missing Trigger spell with no evidence to tell what to trigger, need to return to trigger consumption
														// case 36207: break:                   // Steal Weapon
														// case 36576: break:                   // Shaleskin (Shaleskin Flayer, Shaleskin Ripper) 30023 trigger
														// case 37030: break;                   // Chaotic Temperament
														// case 38363: break;                   // Gushing Wound
														// case 39215: break;                   // Gushing Wound
														// case 40250: break;                   // Improved Duration
														// case 40329: break;                   // Demo Shout Sensor
														// case 40364: break;                   // Entangling Roots Sensor
														// case 41054: break;                   // Copy Weapon
														//    trigger_spell_id = 41055; break;
														// case 41248: break;                   // Consuming Strikes
														//    trigger_spell_id = 41249; break;
														// case 43453: break:                   // Rune Ward
														// case 43504: break;                   // Alterac Valley OnKill Proc Aura

            }
            break;
        case SPELLFAMILY_MAGE:
		if (auraSpellInfo->SpellIconID == 2127)         // Blazing Speed
			{
				switch (auraSpellInfo->Id)
				{
				case 31641:  // Rank 1
				case 31642:  // Rank 2
					trigger_spell_id = 31643;
					break;
				default:
					sLog.outError("Unit::HandleProcTriggerSpellAuraProc: Spell %u miss possibly Blazing Speed", auraSpellInfo->Id);
					return SPELL_AURA_PROC_FAILED;
				}
			}
            if (auraSpellInfo->Id == 26467)                 // Persistent Shield (Scarab Brooch trinket)
            {
                // This spell originally trigger 13567 - Dummy Trigger (vs dummy effect)
                basepoints[0] = damage * 15 / 100;
                target = pVictim;
                trigger_spell_id = 26470;
            }
            break;
        case SPELLFAMILY_WARRIOR:
		// Rampage
			if (auraSpellInfo->SpellIconID == 2006 && auraSpellInfo->IsFitToFamilyMask(uint64(0x0000000000100000)))
			{
				switch (auraSpellInfo->Id)
				{
				case 29801: trigger_spell_id = 30029; break;       // Rank 1
				case 30030: trigger_spell_id = 30031; break;       // Rank 2
				case 30033: trigger_spell_id = 30032; break;       // Rank 3
				default:
					sLog.outError("Unit::HandleProcTriggerSpellAuraProc: Spell %u not handled in Rampage", auraSpellInfo->Id);
					return SPELL_AURA_PROC_FAILED;
				}
				break;
		case SPELLFAMILY_WARLOCK:
		{
			// Pyroclasm
			if (auraSpellInfo->SpellIconID == 1137)
			{
				if (!pVictim || !pVictim->isAlive() || pVictim == this || procSpell == NULL)
					return SPELL_AURA_PROC_FAILED;
				// Calculate spell tick count for spells
				uint32 tick = 1; // Default tick = 1

				if (procSpell->SpellIconID == 184 && procSpell->SpellVisual == 2253)
					tick = 1; // Feu de l'ame
				// Hellfire have 15 tick
				else if (procSpell->IsFitToFamilyMask<CF_WARLOCK_HELLFIRE>())
					tick = 15;
				// Rain of Fire have 4 tick
				else if (procSpell->IsFitToFamilyMask<CF_WARLOCK_RAIN_OF_FIRE>())
					tick = 4;
				else
					return SPELL_AURA_PROC_FAILED;

				// Calculate chance = baseChance / tick
				float chance = 0;
				switch (auraSpellInfo->Id)
				{
				case 18096: // Rank 1
					chance = 13.0f / tick;
					break;
				case 18073: // Rank 2
					chance = 26.0f / tick;
					break;
				}

				// Roll chance
				if (!roll_chance_f(chance))
					return SPELL_AURA_PROC_FAILED;

				trigger_spell_id = 18093;
			}
			// Cheat Death
			else if (auraSpellInfo->Id == 28845)
			{
				// When your health drops below 20% ....
				int32 health20 = int32(GetMaxHealth()) / 5;
				if (int32(GetHealth()) - int32(damage) >= health20 || int32(GetHealth()) < health20)
					return SPELL_AURA_PROC_FAILED;
			}
			// Consequences ne proc pas sur soi-meme (Flammes infernales)
			else if (auraSpellInfo->SpellIconID == 11)
			{
				if (pVictim == this)
					return SPELL_AURA_PROC_FAILED;
			}
			break;
		}
		case SPELLFAMILY_PRIEST:
		{
			// Shadowguard
			if (auraSpellInfo->SpellIconID == 19)
			{
				switch (auraSpellInfo->Id)
				{
				case 18137:
					trigger_spell_id = 28377;
					break;   // Rank 1
				case 19308:
					trigger_spell_id = 28378;
					break;   // Rank 2
				case 19309:
					trigger_spell_id = 28379;
					break;   // Rank 3
				case 19310:
					trigger_spell_id = 28380;
					break;   // Rank 4
				case 19311:
					trigger_spell_id = 28381;
					break;   // Rank 5
				case 19312:
					trigger_spell_id = 28382;
					break;   // Rank 6
				default:
					sLog.outError("Unit::HandleProcTriggerSpell: Spell %u not handled in SG", auraSpellInfo->Id);
					return SPELL_AURA_PROC_FAILED;
				}
			}
			// Blessed Recovery
			else if (auraSpellInfo->SpellIconID == 1875)
			{
				switch (auraSpellInfo->Id)
				{
				case 27811:
					trigger_spell_id = 27813;
					break;
				case 27815:
					trigger_spell_id = 27817;
					break;
				case 27816:
					trigger_spell_id = 27818;
					break;
				default:
					sLog.outError("Unit::HandleProcTriggerSpell: Spell %u not handled in BR", auraSpellInfo->Id);
					return SPELL_AURA_PROC_FAILED;
				}
				basepoints[0] = damage * triggerAmount / 100 / 3;
				target = this;
			}
			break;
		}
		case SPELLFAMILY_DRUID:

			// Druid Forms Trinket
			if (auraSpellInfo->Id == 37336)
			{
				switch (GetShapeshiftForm())
				{
				case FORM_NONE:     trigger_spell_id = 37344; break;
				case FORM_CAT:      trigger_spell_id = 37341; break;
				case FORM_BEAR:
				case FORM_DIREBEAR: trigger_spell_id = 37340; break;
				case FORM_TREE:     trigger_spell_id = 37342; break;
				case FORM_MOONKIN:  trigger_spell_id = 37343; break;
				default:
					return SPELL_AURA_PROC_FAILED;
				}
			}
			// Deep Wounds (replace triggered spells to directly apply DoT), dot spell have familyflags
			switch (auraSpellInfo->Id)
			{
				// Primal Tenacity
			case 54042:
			case 54043:
				float weaponDamage;
				// DW should benefit of attack power, damage percent mods etc.
				// TODO: check if using offhand damage is correct and if it should be divided by 2
				if (haveOffhandWeapon() && getAttackTimer(BASE_ATTACK) > getAttackTimer(OFF_ATTACK))
					weaponDamage = (GetFloatValue(UNIT_FIELD_MINOFFHANDDAMAGE) + GetFloatValue(UNIT_FIELD_MAXOFFHANDDAMAGE)) / 2;
				else
					weaponDamage = (GetFloatValue(UNIT_FIELD_MINDAMAGE) + GetFloatValue(UNIT_FIELD_MAXDAMAGE)) / 2;

				switch (auraSpellInfo->Id)
				{
				case 54042: basepoints[0] = int32(weaponDamage * 0.2f); break;
				case 54043: basepoints[0] = int32(weaponDamage * 0.4f); break;
					// Impossible case
				default:
					sLog.outError("Unit::HandleProcTriggerSpellAuraProc: DW unknown spell rank %u", auraSpellInfo->Id);
					return SPELL_AURA_PROC_FAILED;
				}

				// 1 tick/sec * 6 sec = 6 ticks
				basepoints[0] /= 6;

				trigger_spell_id = 12721;
				break;
				// Feral Tenacity
			case 58423:
			case 58424:
			case 58425:
				if (HasAuraWithMiscValue(SPELL_AURA_MOD_DAMAGE_DONE, 8508))
					trigger_spell_id = 58422;
				break;
			}
			break;
		case SPELLFAMILY_HUNTER:
			switch (auraSpellInfo->Id)
			{
				// Patch 1.9: Aspect of the Pack and Aspect of the Cheetah - Periodic damage will no longer trigger the Dazed effect.
			case 5118:  // Aspect of the Cheetah
			case 13159: // Aspect of the Pack
				if (procFlags & (PROC_FLAG_ON_DO_PERIODIC | PROC_FLAG_ON_TAKE_PERIODIC))
					return SPELL_AURA_PROC_FAILED;
			}
			break;
		case SPELLFAMILY_ROGUE:
		{
			if (auraSpellInfo->SpellIconID == 2260)         // Combat Potency
			{
				if (!(procFlags & PROC_FLAG_SUCCESSFUL_OFFHAND_HIT))
					return SPELL_AURA_PROC_FAILED;
			}
			else if (auraSpellInfo->SpellIconID == 1477)         // Blade Twisting
			{
				// accumulated chance to finish the cooldown of Power Infusion
				if (GetTypeId() == TYPEID_PLAYER)
				{
					const SpellCooldowns& cm = ((Player*)this)->GetSpellCooldownMap();
					for (SpellCooldowns::const_iterator itr = cm.begin(); itr != cm.end();)
					{
						SpellEntry const* spellInfo = sSpellMgr.GetSpellEntry(itr->first);

						if (spellInfo->SpellFamilyName == SPELLFAMILY_ROGUE && (spellInfo->Id == 13877) && GetSpellRecoveryTime(spellInfo) > 0)
						{
							if (((Player*)this)->RollAccumChance())
								((Player*)this)->RemoveSpellCooldown((itr++)->first, true);
						}
						else
						{
							((Player*)this)->AddAccumChance(4);
							++itr;
						}
					}

					trigger_spell_id = 31125;
					break;
				}
				if (auraSpellInfo->SpellIconID == 1939)         // Shadow Strikes
				{
					if (!(procFlags & PROC_FLAG_SUCCESSFUL_OFFHAND_HIT))
						return SPELL_AURA_PROC_FAILED;

					if (pVictim)
					{

						bool found = false;
						// fast check
						if (pVictim->HasAuraState(AURA_STATE_DEADLY_POISON))
							found = true;
						// full aura scan
						else
						{
							Unit::SpellAuraHolderMap const& auras = pVictim->GetSpellAuraHolderMap();
							for (Unit::SpellAuraHolderMap::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
							{
								if (itr->second->GetSpellProto()->Dispel == DISPEL_POISON)
								{
									found = true;
									break;
								}
							}


							if (!found)
							{
								// check dazed affect
								Unit::AuraList const& decSpeedList = pVictim->GetAurasByType(SPELL_AURA_MOD_DECREASE_SPEED);
								for (Unit::AuraList::const_iterator iter = decSpeedList.begin(); iter != decSpeedList.end(); ++iter)
								{
									if ((*iter)->GetSpellProto()->SpellIconID == 15 && (*iter)->GetSpellProto()->Dispel == 0)
									{
										found = true;
										break;
									}
								}
							}

							if (!found)
							{
								return SPELL_AURA_PROC_FAILED;
							}
						}
						trigger_spell_id = 31139;
						break;
					}
				}
				break;
			}
			// Cheat Death
			else if (auraSpellInfo->Id == 28845)
			{
				// When your health drops below 20% ....
				int32 health20 = int32(GetMaxHealth()) / 5;
				if (int32(GetHealth()) - int32(damage) >= health20 || int32(GetHealth()) < health20)
					return SPELL_AURA_PROC_FAILED;
			}

			break;
		}
		case SPELLFAMILY_PALADIN:
		{
			// Judgement of Light and Judgement of Wisdom
			if (auraSpellInfo->IsFitToFamilyMask<CF_PALADIN_JUDGEMENT_OF_WISDOM_LIGHT>())
			{
				switch (auraSpellInfo->Id)
				{
					// Judgement of Light
				case 20185:
					trigger_spell_id = 20267;
					break; // Rank 1
				case 20344:
					trigger_spell_id = 20341;
					break; // Rank 2
				case 20345:
					trigger_spell_id = 20342;
					break; // Rank 3
				case 20346:
					trigger_spell_id = 20343;
					break; // Rank 4
				// Judgement of Wisdom
				case 20186:
					trigger_spell_id = 20268;
					break; // Rank 1
				case 20354:
					trigger_spell_id = 20352;
					break; // Rank 2
				case 20355:
					trigger_spell_id = 20353;
					break; // Rank 3
				default:
					sLog.outError("Unit::HandleProcTriggerSpell: Spell %u miss posibly Judgement of Light/Wisdom", auraSpellInfo->Id);
					return SPELL_AURA_PROC_FAILED;
				}
				pVictim->CastSpell(pVictim, trigger_spell_id, true, castItem, triggeredByAura);
				return SPELL_AURA_PROC_OK;                        // no hidden cooldown
			}
			// Illumination
			else if (auraSpellInfo->SpellIconID == 241)
			{
				if (!procSpell)
					return SPELL_AURA_PROC_FAILED;

				// procspell is triggered spell but we need mana cost of original casted spell

				//[Nostalrius] : Stocke autremenent
				//Le sort caste est dans une varible : Unit::m_castingSpell. Sinon, impossible de trouver le sort qui a provoque le proc

				SpellEntry const *originalSpell = sSpellMgr.GetSpellEntry(m_castingSpell);
				//SpellEntry const *originalSpell = sSpellMgr.GetSpellEntry(originalSpellId);
				if (!originalSpell)
				{
					sLog.outError("Unit::HandleProcTriggerSpell: Spell %u unknown but selected as original in Illu", m_castingSpell);
					return SPELL_AURA_PROC_FAILED;
				}
				// Histoire de pas reproc une autre fois ... :S
				m_castingSpell = 0;
				basepoints[0] = originalSpell->manaCost;
				trigger_spell_id = 20272;
				target = this;
				break;
			}

			//Purifing Power
			else if (auraSpellInfo->SpellIconID == 3019)
			{
				if (!procSpell)
					return SPELL_AURA_PROC_FAILED;
				// procspell is triggered spell but we need damage of original casted spell
				uint32 originalSpellId = procSpell->Id;

				SpellEntry const* originalSpell = sSpellMgr.GetSpellEntry(originalSpellId);
				if (!originalSpell)
				{
					sLog.outError("Unit::HandleProcTriggerSpellAuraProc: Spell %u unknown but selected as original in Illu", originalSpellId);
					return SPELL_AURA_PROC_FAILED;
				}

				switch (auraSpellInfo->Id)
				{
				case 54305: basepoints[0] = int32(originalSpell->EffectBasePoints[0] * 0.33f);
				case 54306: basepoints[0] = int32(originalSpell->EffectBasePoints[0] * 0.66f);
				case 54307: basepoints[0] = int32(originalSpell->EffectBasePoints[0]);
				default:
					sLog.outError("Unit::HandleProcTriggerSpellAuraProc: Spell %u not handled correctly", procSpell->Id);
					return SPELL_AURA_PROC_FAILED;
				}

				trigger_spell_id = 54877;
				target = this;
			}
			//Blessed Life
			else if (auraSpellInfo->SpellIconID == 2137)
			{
				if (!procSpell)
					return SPELL_AURA_PROC_FAILED;
				// procspell is triggered spell but we need base heal of original casted spell
				uint32 originalSpellId = procSpell->Id;

				SpellEntry const* originalSpell = sSpellMgr.GetSpellEntry(originalSpellId);
				if (!originalSpell)
				{
					sLog.outError("Unit::HandleProcTriggerSpellAuraProc: Spell %u unknown but selected as original in Illu", originalSpellId);
					return SPELL_AURA_PROC_FAILED;
				}

				switch (auraSpellInfo->Id)
				{
				case 54878: basepoints[0] = int32(originalSpell->EffectBasePoints[0] * 0.05f);
				case 54879: basepoints[0] = int32(originalSpell->EffectBasePoints[0] * 0.1f);
				case 54880: basepoints[0] = int32(originalSpell->EffectBasePoints[0] * 0.15f);
				case 54881: basepoints[0] = int32(originalSpell->EffectBasePoints[0] * 0.2f);
				case 54882: basepoints[0] = int32(originalSpell->EffectBasePoints[0] * 0.25f);
				default:
					sLog.outError("Unit::HandleProcTriggerSpellAuraProc: Spell %u not handled correctly", procSpell->Id);
					return SPELL_AURA_PROC_FAILED;
				}

				trigger_spell_id = 54883;
				target = this;
			}
			// Lightning Capacitor
			else if (auraSpellInfo->Id == 37657)
			{
				if (!pVictim || !pVictim->isAlive())
					return SPELL_AURA_PROC_FAILED;
				// stacking
				CastSpell(this, 37658, true, nullptr, triggeredByAura);

				Aura* dummy = GetDummyAura(37658);
				// release at 3 aura in stack (cont contain in basepoint of trigger aura)
				if (!dummy || dummy->GetStackAmount() < uint32(triggerAmount))
					return SPELL_AURA_PROC_FAILED;

				RemoveAurasDueToSpell(37658);
				trigger_spell_id = 37661;
				target = pVictim;
			}
			// Bonus Healing (Crystal Spire of Karabor mace)
			else if (auraSpellInfo->Id == 40971)
			{
				// If your target is below $s1% health
				if (pVictim->GetHealth() > pVictim->GetMaxHealth() * triggerAmount / 100)
					return SPELL_AURA_PROC_FAILED;
			}

			break;
		}
		case SPELLFAMILY_SHAMAN:
		{
			// Lightning Shield (overwrite non existing triggered spell call in spell.dbc
			if (auraSpellInfo->IsFitToFamilyMask<CF_SHAMAN_LIGHTNING_SHIELD>() && auraSpellInfo->SpellVisual == 37)
			{
				switch (auraSpellInfo->Id)
				{
				case 324:                               // Rank 1
					trigger_spell_id = 26364;
					break;
				case 325:                               // Rank 2
					trigger_spell_id = 26365;
					break;
				case 905:                               // Rank 3
					trigger_spell_id = 26366;
					break;
				case 945:                               // Rank 4
					trigger_spell_id = 26367;
					break;
				case 8134:                              // Rank 5
					trigger_spell_id = 26369;
					break;
				case 10431:                             // Rank 6
					trigger_spell_id = 26370;
					break;
				case 10432:                             // Rank 7
					trigger_spell_id = 26363;
					break;
				default:
					sLog.outError("Unit::HandleProcTriggerSpell: Spell %u not handled in LShield", auraSpellInfo->Id);
					return SPELL_AURA_PROC_FAILED;
				}
			}
			// Lightning Shield (The Ten Storms set)
			else if (auraSpellInfo->Id == 23551)
			{
				trigger_spell_id = 23552;
				target = pVictim;
			}
			// Damage from Lightning Shield (The Ten Storms set)
			else if (auraSpellInfo->Id == 23552)
				trigger_spell_id = 27635;
			// Mana Surge (The Earthfury set)
			else if (auraSpellInfo->Id == 23572)
			{
				if (!procSpell)
					return SPELL_AURA_PROC_FAILED;
				basepoints[0] = procSpell->manaCost * 35 / 100;
				trigger_spell_id = 23571;
				target = this;
			}
			else if (auraSpellInfo->SpellIconID == 2013)
			{
				// Check health condition - should drop to less 40% (trigger at any attack with result health less 40%, independent original health state)
				int32 health40 = int32(GetMaxHealth()) * 4 / 10;
				if (int32(GetHealth()) - int32(damage) >= health40)
					return SPELL_AURA_PROC_FAILED;

				if (pVictim && pVictim->isAlive())
					pVictim->getThreatManager().modifyThreatPercent(this, 10);

				basepoints[0] = triggerAmount * GetMaxHealth() / 100;
				trigger_spell_id = 31616;
				target = this;
			}
			else if (auraSpellInfo->Id == 54943)
				// Earthquake					
			{
				if (!pVictim || !pVictim->isAlive() || pVictim == this || procSpell == nullptr)
					return SPELL_AURA_PROC_FAILED;

				float chance = 10;

				// Roll chance
				if (!roll_chance_f(chance))
					return SPELL_AURA_PROC_FAILED;

				trigger_spell_id = 54944;
				break;
			}
			break;
		}
		default:
			break;
		}
    }

    // All ok. Check current trigger spell
    SpellEntry const* triggerEntry = sSpellMgr.GetSpellEntry(trigger_spell_id);
    if (!triggerEntry)
    {
        // Not cast unknown spell
        sLog.outError("Unit::HandleProcTriggerSpell: Spell %u have %u in EffectTriggered[%d], not handled custom case?", auraSpellInfo->Id, trigger_spell_id, triggeredByAura->GetEffIndex());
        return SPELL_AURA_PROC_FAILED;
    }

    // not allow proc extra attack spell at extra attack
    if (m_extraAttacks && IsSpellHaveEffect(triggerEntry, SPELL_EFFECT_ADD_EXTRA_ATTACKS) && triggerEntry->Id != 20178)
        return SPELL_AURA_PROC_FAILED;

    // Custom basepoints/target for exist spell
    // dummy basepoints or other customs
    switch (trigger_spell_id)
    {
        // Cast positive spell on enemy target
        case 7099:  // Curse of Mending
        case 29494: // Temptation
        case 39647: // Curse of Mending
        case 20233: // Improved Lay on Hands (cast on target)
        {
            target = pVictim;
            break;
        }
        // Combo points add triggers (need add combopoint only for main target, and after possible combopoints reset)
        case 15250: // Rogue Setup
        {
            if (!pVictim || pVictim != getVictim())  // applied only for main target
                return SPELL_AURA_PROC_FAILED;
            break;                                   // continue normal case
        }
        // Finishing moves that add combo points
        case 14189: // Seal Fate (Netherblade set)
        case 14157: // Ruthlessness
        {
            // Need add combopoint AFTER finishing move (or they get dropped in finish phase)
            if (Spell* spell = GetCurrentSpell(CURRENT_GENERIC_SPELL))
            {
                spell->AddTriggeredSpell(trigger_spell_id);
                return SPELL_AURA_PROC_OK;
            }
            return SPELL_AURA_PROC_FAILED;
        }
// Shamanistic Rage triggered spell
		case 30824:
		{
			basepoints[0] = int32(GetTotalAttackPowerValue(BASE_ATTACK) * triggerAmount / 100);
			break;
		}
		// Enlightenment (trigger only from mana cost spells)
		case 35095:
		{
			if (!procSpell || procSpell->powerType != POWER_MANA || (procSpell->manaCost == 0 && procSpell->ManaCostPercentage == 0 && procSpell->manaCostPerlevel == 0))
				return SPELL_AURA_PROC_FAILED;
			break;
		}
    }

    if (cooldown && GetTypeId() == TYPEID_PLAYER && ((Player*)this)->HasSpellCooldown(trigger_spell_id))
        return SPELL_AURA_PROC_FAILED;

    // try detect target manually if not set
    if (target == NULL)
        target = !(procFlags & PROC_FLAG_SUCCESSFUL_POSITIVE_SPELL) && IsPositiveSpell(trigger_spell_id) ? this : pVictim;

    // default case
    if (!target || target != this && !target->isAlive())
        return SPELL_AURA_PROC_FAILED;

    if (basepoints[EFFECT_INDEX_0] || basepoints[EFFECT_INDEX_1] || basepoints[EFFECT_INDEX_2])
        CastCustomSpell(target, trigger_spell_id,
                        basepoints[EFFECT_INDEX_0] ? &basepoints[EFFECT_INDEX_0] : NULL,
                        basepoints[EFFECT_INDEX_1] ? &basepoints[EFFECT_INDEX_1] : NULL,
                        basepoints[EFFECT_INDEX_2] ? &basepoints[EFFECT_INDEX_2] : NULL,
                        true, castItem, triggeredByAura);
    else
        CastSpell(target, trigger_spell_id, true, castItem, triggeredByAura);

    if (cooldown && GetTypeId() == TYPEID_PLAYER)
        ((Player*)this)->AddSpellCooldown(trigger_spell_id, 0, time(NULL) + cooldown);

    return SPELL_AURA_PROC_OK;
}

SpellAuraProcResult Unit::HandleProcTriggerDamageAuraProc(Unit *pVictim, uint32 damage, Aura* triggeredByAura, SpellEntry const *procSpell, uint32 procFlags, uint32 procEx, uint32 cooldown)
{
    SpellEntry const *spellInfo = triggeredByAura->GetSpellProto();
    DEBUG_FILTER_LOG(LOG_FILTER_SPELL_CAST, "ProcDamageAndSpell: doing %u damage from spell id %u (triggered by auratype %u of spell %u)",
                     triggeredByAura->GetModifier()->m_amount, spellInfo->Id, triggeredByAura->GetModifier()->m_auraname, triggeredByAura->GetId());
    SpellNonMeleeDamage damageInfo(this, pVictim, spellInfo->Id, SpellSchools(spellInfo->School));
    CalculateSpellDamage(&damageInfo, triggeredByAura->GetModifier()->m_amount, spellInfo);
    damageInfo.target->CalculateAbsorbResistBlock(this, &damageInfo, spellInfo);
    DealDamageMods(damageInfo.target, damageInfo.damage, &damageInfo.absorb);
    SendSpellNonMeleeDamageLog(&damageInfo);
    DealSpellDamage(&damageInfo, true);
    return SPELL_AURA_PROC_OK;
}

SpellAuraProcResult Unit::HandleOverrideClassScriptAuraProc(Unit *pVictim, uint32 /*damage*/, Aura *triggeredByAura, SpellEntry const *procSpell, uint32 /*procFlag*/, uint32 /*procEx*/ , uint32 cooldown)
{
    int32 scriptId = triggeredByAura->GetModifier()->m_miscvalue;

    if (!pVictim || !pVictim->isAlive())
        return SPELL_AURA_PROC_FAILED;

    Item* castItem = triggeredByAura->GetCastItemGuid() && GetTypeId() == TYPEID_PLAYER
                     ? ((Player*)this)->GetItemByGuid(triggeredByAura->GetCastItemGuid()) : NULL;

    // Basepoints of trigger aura
    int32 triggerAmount = triggeredByAura->GetModifier()->m_amount;

    uint32 triggered_spell_id = 0;

    switch (scriptId)
    {       
        case 836:                                           // Improved Blizzard (Rank 1)
        {
            if (!procSpell || procSpell->SpellVisual != 259)
                return SPELL_AURA_PROC_FAILED;
            triggered_spell_id = 12484;
            break;
        }
        case 988:                                           // Improved Blizzard (Rank 2)
        {
            if (!procSpell || procSpell->SpellVisual != 259)
                return SPELL_AURA_PROC_FAILED;
            triggered_spell_id = 12485;
            break;
        }
        case 989:                                           // Improved Blizzard (Rank 3)
        {
            if (!procSpell || procSpell->SpellVisual != 259)
                return SPELL_AURA_PROC_FAILED;
            triggered_spell_id = 12486;
            break;
        }
        case 4086:                                          // Improved Mend Pet (Rank 1)
        case 4087:                                          // Improved Mend Pet (Rank 2)
        {
            if (!roll_chance_i(triggerAmount))
                return SPELL_AURA_PROC_FAILED;

            triggered_spell_id = 24406;

// accumulated chance to finish the cooldown for Bestial Wrath
			if (GetTypeId() == TYPEID_PLAYER)
			{
				const SpellCooldowns& cm = ((Player*)this)->GetSpellCooldownMap();
				for (SpellCooldowns::const_iterator itr = cm.begin(); itr != cm.end();)
				{
					SpellEntry const* spellInfo = sSpellMgr.GetSpellEntry(itr->first);

					if (spellInfo->SpellFamilyName == SPELLFAMILY_HUNTER && (spellInfo->Id == 19574) && GetSpellRecoveryTime(spellInfo) > 0)
					{
						if (((Player*)this)->RollAccumChance())
							((Player*)this)->RemoveSpellCooldown((itr++)->first, true);
					}
					else
					{
						((Player*)this)->AddAccumChance(2);
						++itr;
					}
				}
			}

            break;
        }
		 case 4309: 
        {													
		triggered_spell_id = 17941;                     // Shadow Trance (Warlock Nightfall)
 // accumulated chance to finish the cooldown for Amplify Curse
		if (GetTypeId() == TYPEID_PLAYER)
		{
			const SpellCooldowns& cm = ((Player*)this)->GetSpellCooldownMap();
			for (SpellCooldowns::const_iterator itr = cm.begin(); itr != cm.end();)
			{
				SpellEntry const* spellInfo = sSpellMgr.GetSpellEntry(itr->first);

				if (spellInfo->SpellFamilyName == SPELLFAMILY_WARLOCK && (spellInfo->Id == 18288) && GetSpellRecoveryTime(spellInfo) > 0)
				{
					if (((Player*)this)->RollAccumChance())
						((Player*)this)->RemoveSpellCooldown((itr++)->first, true);
				}
				else
				{
					((Player*)this)->AddAccumChance(4);
					++itr;
				}
			}
		}
            break;
        }

		case 5001:
		{													//Custom
			triggered_spell_id = 54269;                     // Lunar Eclipse (Druid)
			break;
		}
		case 5002:
		{
			triggered_spell_id = 54271;                     // Solar Eclipse (Druid)
			break;
		}
		case 5003:
		{
		    triggered_spell_id = 54273;                     // Overload (Shaman)
 // accumulated chance to finish the cooldown for Elemental Mastery
			if (GetTypeId() == TYPEID_PLAYER)
			{
				const SpellCooldowns& cm = ((Player*)this)->GetSpellCooldownMap();
				for (SpellCooldowns::const_iterator itr = cm.begin(); itr != cm.end();)
				{
					SpellEntry const* spellInfo = sSpellMgr.GetSpellEntry(itr->first);

					if (spellInfo->SpellFamilyName == SPELLFAMILY_SHAMAN && spellInfo->Id == 16166 && GetSpellRecoveryTime(spellInfo) > 0)
					{
						if (((Player*)this)->RollAccumChance())
							((Player*)this)->RemoveSpellCooldown((itr++)->first, true);
					}
					else
					{
						((Player*)this)->AddAccumChance(5);
						++itr;
					}
				}
			}
			break;
		}
		case 5010:
		{
			triggered_spell_id = 15271;                     // Pain and Gain
			break;
		}
		case 5011:
		{
			triggered_spell_id = 54316;                     // Pain and Suffering (Warlock)
			break;
		}		
		case 5012:
		{
			triggered_spell_id = 54517;                     // Art of War (Paladin)
			break;
		}
		case 5013:
		{
			triggered_spell_id = 54533;                     // Cunningness (Hunter)
			break;
		}
		case 5014:
		{
			triggered_spell_id = 54536;                     // Cobra reflexes (Hunter)
			break;
		}
		case 5015:
		{
			triggered_spell_id = 54540;                     // Marksman (Hunter)
			break;
		}
		case 5016:
		{
			triggered_spell_id = 54582;                     // Fire and Frost (Mage)
		// accumulated chance to finish the cooldown of Combustion and Cold Snap
			if (GetTypeId() == TYPEID_PLAYER)
			{
				const SpellCooldowns& cm = ((Player*)this)->GetSpellCooldownMap();
				for (SpellCooldowns::const_iterator itr = cm.begin(); itr != cm.end();)
				{
					SpellEntry const* spellInfo = sSpellMgr.GetSpellEntry(itr->first);

					if (spellInfo->SpellFamilyName == SPELLFAMILY_MAGE && (spellInfo->Id == 11129 || spellInfo->Id == 12472) && GetSpellRecoveryTime(spellInfo) > 0)
					{
						if (((Player*)this)->RollAccumChance())
							((Player*)this)->RemoveSpellCooldown((itr++)->first, true);
					}
					else
					{
						((Player*)this)->AddAccumChance(4);
						++itr;
					}
				}
			}
			break;
		}
		case 5017:
		{
			triggered_spell_id = 54095;                     // Enlightment (Priest)
// accumulated chance to finish the cooldown of Power Infusion
			if (GetTypeId() == TYPEID_PLAYER)
			{
				const SpellCooldowns& cm = ((Player*)this)->GetSpellCooldownMap();
				for (SpellCooldowns::const_iterator itr = cm.begin(); itr != cm.end();)
				{
					SpellEntry const* spellInfo = sSpellMgr.GetSpellEntry(itr->first);

					if (spellInfo->SpellFamilyName == SPELLFAMILY_PRIEST && (spellInfo->Id == 10060) && GetSpellRecoveryTime(spellInfo) > 0)
					{
						if (((Player*)this)->RollAccumChance())
							((Player*)this)->RemoveSpellCooldown((itr++)->first, true);
					}
					else
					{
						((Player*)this)->AddAccumChance(8);
						++itr;
					}
				}
			}
			break;
		}
		case 5018:
		{
			if (HasAura(18788))
				triggered_spell_id = 54395;                     // Decimation (Warlock)
			break;
		}
		case 5019:											//Payback (Hunter)
		{
			triggered_spell_id = 1491;
			break;
		}
		case 5020:                                          // Hit or Miss
		{
			triggered_spell_id = 54554; break;			
			break;
		}
		case 5021:
		{
			triggered_spell_id = 54461;                     // Ice veins (Mage)
			break;
		}
		case 5022:
		{
			triggered_spell_id = 54643;                     // Ice veins (Mage)
			break;
		}
		case 5023:
		{
			triggered_spell_id = 54457;                     // Pyromaniac
			break;
		}
		case 5024:                                          //Overheat
		{
			if (HasAura(54778))
				RemoveAurasDueToSpell(54778);

			triggered_spell_id = 54777;

			break;
		}
		case 5025:
		{
			if (HasAura(54777))
				RemoveAurasDueToSpell(54777);

			triggered_spell_id = 54778;                     // Hypothermia
			break;
		}
        case 4533:                                          // Dreamwalker Raiment 2 pieces bonus
        {
            // Chance 50%
            if (!roll_chance_i(50))
                return SPELL_AURA_PROC_FAILED;

            switch (pVictim->getPowerType())
            {
                case POWER_MANA:   triggered_spell_id = 28722; break;
                case POWER_RAGE:   triggered_spell_id = 28723; break;
                case POWER_ENERGY: triggered_spell_id = 28724; break;
                default:
                    return SPELL_AURA_PROC_FAILED;
            }
            break;
        }
        case 4537:                                          // Dreamwalker Raiment 6 pieces bonus
            triggered_spell_id = 28750;                     // Blessing of the Claw
            break;
    }

    // not processed
    if (!triggered_spell_id)
        return SPELL_AURA_PROC_OK;

    // standard non-dummy case
    SpellEntry const* triggerEntry = sSpellMgr.GetSpellEntry(triggered_spell_id);

    if (!triggerEntry || triggered_spell_id == 18350)
    {
        sLog.outError("Unit::HandleOverrideClassScriptAuraProc: Spell %u triggering for class script id %u", triggered_spell_id, scriptId);
        return SPELL_AURA_PROC_FAILED;
    }

    if (cooldown && GetTypeId() == TYPEID_PLAYER && ((Player*)this)->HasSpellCooldown(triggered_spell_id))
        return SPELL_AURA_PROC_FAILED;

    CastSpell(pVictim, triggered_spell_id, true, castItem, triggeredByAura);

    if (cooldown && GetTypeId() == TYPEID_PLAYER)
        ((Player*)this)->AddSpellCooldown(triggered_spell_id, 0, time(NULL) + cooldown);

    return SPELL_AURA_PROC_OK;
}

SpellAuraProcResult Unit::HandleModCastingSpeedNotStackAuraProc(Unit* /*pVictim*/, uint32 /*damage*/, Aura* /*triggeredByAura*/, SpellEntry const* procSpell, uint32 /*procFlag*/, uint32 /*procEx*/, uint32 /*cooldown*/)
{
    // Skip melee hits or instant cast spells
    return !(procSpell == NULL || GetSpellCastTime(procSpell) == 0) ? SPELL_AURA_PROC_OK : SPELL_AURA_PROC_FAILED;
}

SpellAuraProcResult Unit::HandleReflectSpellsSchoolAuraProc(Unit* /*pVictim*/, uint32 /*damage*/, Aura* triggeredByAura, SpellEntry const* procSpell, uint32 /*procFlag*/, uint32 /*procEx*/, uint32 /*cooldown*/)
{
    // Skip Melee hits and spells ws wrong school
    return !(procSpell == NULL || (triggeredByAura->GetModifier()->m_miscvalue & GetSchoolMask(procSpell->School)) == 0) ? SPELL_AURA_PROC_OK : SPELL_AURA_PROC_FAILED;
}

SpellAuraProcResult Unit::HandleModPowerCostSchoolAuraProc(Unit* /*pVictim*/, uint32 /*damage*/, Aura* triggeredByAura, SpellEntry const* procSpell, uint32 /*procFlag*/, uint32 /*procEx*/, uint32 /*cooldown*/)
{
    // Skip melee hits and spells ws wrong school or zero cost
    return !(procSpell == NULL ||
             (procSpell->manaCost == 0 && procSpell->ManaCostPercentage == 0) ||           // Cost check
             (triggeredByAura->GetModifier()->m_miscvalue & GetSchoolMask(procSpell->School)) == 0) ? SPELL_AURA_PROC_OK : SPELL_AURA_PROC_FAILED;  // School check
}

SpellAuraProcResult Unit::HandleMechanicImmuneResistanceAuraProc(Unit* /*pVictim*/, uint32 /*damage*/, Aura* triggeredByAura, SpellEntry const* procSpell, uint32 /*procFlag*/, uint32 /*procEx*/, uint32 /*cooldown*/)
{
    // Compare mechanic
    return !(procSpell == NULL || procSpell->Mechanic != triggeredByAura->GetModifier()->m_miscvalue)
           ? SPELL_AURA_PROC_OK : SPELL_AURA_PROC_FAILED;
}

// Nostalrius
SpellAuraProcResult Unit::HandleAddTargetTriggerAuraProc(Unit *pVictim, uint32 /*damage*/, Aura *triggeredByAura, SpellEntry const *procSpell, uint32 /*procFlag*/, uint32 /*procEx*/ , uint32 cooldown)
{
    const SpellEntry* aurEntry = triggeredByAura->GetSpellProto();
    uint32 trigger_spell_id = aurEntry->EffectTriggerSpell[0];
    float chance = 0.0f;

    if (aurEntry->EffectBasePoints[0] != -1)
        chance = aurEntry->EffectBasePoints[0];
    else
    {
        switch (aurEntry->Id)
        {
            // Frappes implacables
            case 14179: // Rang 1 : 4%
            {
                if (GetTypeId() == TYPEID_PLAYER)
                {
                    chance = 20.0f * m_castingSpell;
                    m_castingSpell = 0;
                }
                break;
            }
            default:
            {
                sLog.outError("Spell %u has chance = -1 but not handled in core ...", aurEntry->Id);
                break;
            }
        }
    }
    // Si il y a plusieurs ticks ...
    // Blizzard - 8 ticks (fix procs abuses de morsure de givre)
    if (aurEntry->IsFitToFamily<SPELLFAMILY_MAGE, CF_MAGE_BLIZZARD>())
        chance /= 8;

    // Chance = -1 -> A calculer manuellement
    if (!roll_chance_f(chance))
        return SPELL_AURA_PROC_FAILED;

    if (trigger_spell_id)
    {
        bool bTarget = true;
        switch (aurEntry->Id)
        {
            case 17768: // Casque tete de loup
            case 24392: // Gelee soudaine
            case 14179: // Frappes implacables
                bTarget = false;
                break;
        }

        if (bTarget)
        {
            // Cone de glace
            if (pVictim->GetGUID() == GetGUID())
                return SPELL_AURA_PROC_FAILED;
            pVictim->CastSpell(pVictim, trigger_spell_id, true, NULL, triggeredByAura);
        }
        else
            CastSpell(this, trigger_spell_id, true, NULL, triggeredByAura);
    }
    return SPELL_AURA_PROC_OK;
}

SpellAuraProcResult Unit::HandleModResistanceAuraProc(Unit* /*pVictim*/, uint32 damage, Aura* triggeredByAura, SpellEntry const* /*procSpell*/, uint32 /*procFlag*/, uint32 /*procEx*/, uint32 /*cooldown*/)
{
    SpellEntry const *spellInfo = triggeredByAura->GetSpellProto();

    // Inner Fire
    if (spellInfo->IsFitToFamily<SPELLFAMILY_PRIEST, CF_PRIEST_INNER_FIRE>())
    {
        // only at real damage
        if (!damage)
            return SPELL_AURA_PROC_FAILED;
    }

    return SPELL_AURA_PROC_OK;
}

SpellAuraProcResult Unit::HandleMendingAuraProc(Unit* /*pVictim*/, uint32 /*damage*/, Aura* triggeredByAura, SpellEntry const* /*procSpell*/, uint32 /*procFlag*/, uint32 /*procEx*/, uint32 /*cooldown*/)
{
	// aura can be deleted at casts
	SpellEntry const* spellProto = triggeredByAura->GetSpellProto();
	SpellEffectIndex effIdx = triggeredByAura->GetEffIndex();
	int32 heal = triggeredByAura->GetModifier()->m_amount;
	ObjectGuid caster_guid = triggeredByAura->GetCasterGuid();

	// jumps
	int32 jumps = triggeredByAura->GetHolder()->GetAuraCharges() - 1;

	// current aura expire
	triggeredByAura->GetHolder()->SetAuraCharges(1);        // will removed at next charges decrease

															// next target selection
	if (jumps > 0 && GetTypeId() == TYPEID_PLAYER && caster_guid.IsPlayer())
	{
		float radius;
		if (spellProto->EffectRadiusIndex[effIdx])
			radius = GetSpellRadius(sSpellRadiusStore.LookupEntry(spellProto->EffectRadiusIndex[effIdx]));
		else
			radius = GetSpellMaxRange(sSpellRangeStore.LookupEntry(spellProto->rangeIndex));

		if (Player* caster = ((Player*)triggeredByAura->GetCaster()))
		{
			caster->ApplySpellMod(spellProto->Id, SPELLMOD_RADIUS, radius, nullptr);

			if (Player* target = ((Player*)this)->GetNextRaidMemberWithLowestLifePercentage(radius, SPELL_AURA_PRAYER_OF_MENDING))
			{
				// aura will applied from caster, but spell casted from current aura holder
				SpellModifier* mod = new SpellModifier(SPELLMOD_CHARGES, SPELLMOD_FLAT, jumps - 5, spellProto->Id, spellProto->SpellFamilyFlags);

				// remove before apply next (locked against deleted)
				triggeredByAura->SetInUse(true);
				RemoveAurasByCasterSpell(spellProto->Id, caster->GetObjectGuid());

				((Player*)this)->AddSpellMod(mod, true);
				CastCustomSpell(target, spellProto->Id, &heal, nullptr, nullptr, true, nullptr, triggeredByAura, caster->GetObjectGuid());
				((Player*)this)->AddSpellMod(mod, false);
				triggeredByAura->SetInUse(false);
			}
		}
	}

	// heal
	CastCustomSpell(this, 33110, &heal, nullptr, nullptr, true, nullptr, nullptr, caster_guid);
	return SPELL_AURA_PROC_OK;
}

