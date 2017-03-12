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

#ifndef MANGOS_CREATUREAI_H
#define MANGOS_CREATUREAI_H

#include "Common.h"
#include "Platform/Define.h"
#include "Policies/Singleton.h"
#include "Dynamic/ObjectRegistry.h"
#include "Dynamic/FactoryHolder.h"
#include "ObjectGuid.h"

class WorldObject;
class GameObject;
class Unit;
class Creature;
class Player;
class SpellEntry;
class ChatHandler;
struct Loot;

#define TIME_INTERVAL_LOOK   5000
#define VISIBILITY_RANGE    10000

enum CanCastResult
{
    CAST_OK                     = 0,
    CAST_FAIL_IS_CASTING        = 1,
    CAST_FAIL_OTHER             = 2,
    CAST_FAIL_TOO_FAR           = 3,
    CAST_FAIL_TOO_CLOSE         = 4,
    CAST_FAIL_POWER             = 5,
    CAST_FAIL_STATE             = 6,
    CAST_FAIL_TARGET_AURA       = 7,
	CAST_FAIL_NOT_IN_LOS		= 8
};

enum CastFlags
{
    CAST_INTERRUPT_PREVIOUS     = 0x01,                     //Interrupt any spell casting
    CAST_TRIGGERED              = 0x02,                     //Triggered (this makes spell cost zero mana and have no cast time)
    CAST_FORCE_CAST             = 0x04,                     //Forces cast even if creature is out of mana or out of range
    CAST_NO_MELEE_IF_OOM        = 0x08,                     //Prevents creature from entering melee if out of mana or out of range
    CAST_FORCE_TARGET_SELF      = 0x10,                     //Forces the target to cast this spell on itself
    CAST_AURA_NOT_PRESENT       = 0x20,                     //Only casts the spell if the target does not have an aura from the spell
	CAST_IGNORE_UNSELECTABLE_TARGET = 0x40,                 // Can target UNIT_FLAG_NOT_SELECTABLE - Needed in some scripts
};

enum AIEventType
{
	// Usable with Event AI
	AI_EVENT_JUST_DIED = 0,                        // Sender = Killed Npc, Invoker = Killer
	AI_EVENT_CRITICAL_HEALTH = 1,                        // Sender = Hurt Npc, Invoker = DamageDealer - Expected to be sent by 10% health
	AI_EVENT_LOST_HEALTH = 2,                        // Sender = Hurt Npc, Invoker = DamageDealer - Expected to be sent by 50% health
	AI_EVENT_LOST_SOME_HEALTH = 3,                        // Sender = Hurt Npc, Invoker = DamageDealer - Expected to be sent by 90% health
	AI_EVENT_GOT_FULL_HEALTH = 4,                        // Sender = Healed Npc, Invoker = Healer
	AI_EVENT_CUSTOM_EVENTAI_A = 5,                        // Sender = Npc that throws custom event, Invoker = TARGET_T_ACTION_INVOKER (if exists)
	AI_EVENT_CUSTOM_EVENTAI_B = 6,                        // Sender = Npc that throws custom event, Invoker = TARGET_T_ACTION_INVOKER (if exists)
	AI_EVENT_GOT_CCED = 7,                        // Sender = CCed Npc, Invoker = Caster that CCed
	AI_EVENT_CUSTOM_EVENTAI_C = 8,                        // Sender = Npc that throws custom event, Invoker = TARGET_T_ACTION_INVOKER (if exists)
	AI_EVENT_CUSTOM_EVENTAI_D = 9,                        // Sender = Npc that throws custom event, Invoker = TARGET_T_ACTION_INVOKER (if exists)
	AI_EVENT_CUSTOM_EVENTAI_E = 10,                       // Sender = Npc that throws custom event, Invoker = TARGET_T_ACTION_INVOKER (if exists)
	AI_EVENT_CUSTOM_EVENTAI_F = 11,                       // Sender = Npc that throws custom event, Invoker = TARGET_T_ACTION_INVOKER (if exists)
	MAXIMAL_AI_EVENT_EVENTAI = 12,

	// Internal Use
	AI_EVENT_CALL_ASSISTANCE = 13,                       // Sender = Attacked Npc, Invoker = Enemy

	// Predefined for SD2
	AI_EVENT_START_ESCORT = 100,                      // Invoker = Escorting Player
	AI_EVENT_START_ESCORT_B = 101,                      // Invoker = Escorting Player
	AI_EVENT_START_EVENT = 102,                      // Invoker = EventStarter
	AI_EVENT_START_EVENT_A = 103,                      // Invoker = EventStarter
	AI_EVENT_START_EVENT_B = 104,                      // Invoker = EventStarter

	// Some IDs for special cases in SD2
	AI_EVENT_CUSTOM_A = 1000,
	AI_EVENT_CUSTOM_B = 1001,
	AI_EVENT_CUSTOM_C = 1002,
	AI_EVENT_CUSTOM_D = 1003,
	AI_EVENT_CUSTOM_E = 1004,
	AI_EVENT_CUSTOM_F = 1005,
};

class MANGOS_DLL_SPEC CreatureAI
{
    public:
        explicit CreatureAI(Creature* creature) : m_creature(creature), m_bUseAiAtControl(false), m_uLastAlertTime(0) {}

        virtual ~CreatureAI();
        virtual void OnRemoveFromWorld() {}

        virtual uint32 GetData(uint32 /*type*/) { return 0; }

        virtual void InformGuid(const ObjectGuid /*guid*/, uint32 /*type*/=0) {}
        virtual void DoAction(const uint32 /*type*/=0) {}
        virtual void DoAction(Unit* /*pUnit*/, uint32 /*type*/) {}

        ///== Information about AI ========================
        virtual void GetAIInformation(ChatHandler& /*reader*/) {}

        ///== Reactions At =================================

        // Called if IsVisible(Unit *who) is true at each *who move, reaction at visibility zone enter
        virtual void MoveInLineOfSight(Unit *) {}

        // Called for reaction at enter to combat if not in combat yet (enemy can be NULL)
        virtual void EnterCombat(Unit* /*enemy*/) {}

        // Called for reaction at stopping attack at no attackers or targets
        virtual void EnterEvadeMode();

        // Called at reaching home after evade
        virtual void JustReachedHome() {}

        // Called at any heal cast/item used (call non implemented)
        virtual void HealBy(Unit * /*healer*/, uint32 /*amount_healed*/) {}

        // Helper functions for cast spell
        virtual CanCastResult CanCastSpell(Unit* pTarget, const SpellEntry *pSpell, bool isTriggered);

        // Called at any Damage to any victim (before damage apply)
        virtual void DamageDeal(Unit * /*done_to*/, uint32 & /*damage*/) {}

        // Called at any Damage from any attacker (before damage apply)
        // Note: it for recalculation damage or special reaction at damage
        // for attack reaction use AttackedBy called for not DOT damage in Unit::DealDamage also
        virtual void DamageTaken(Unit * /*done_by*/, uint32 & /*damage*/) {}

        // Called when the creature is killed
        virtual void JustDied(Unit *) {}

        // Called when the creature summon is killed
        virtual void SummonedCreatureJustDied(Creature* /*unit*/) {}

        // Called when the creature kills a unit
        virtual void KilledUnit(Unit *) {}

        // Called when owner of m_creature (if m_creature is PROTECTOR_PET) kills a unit
        virtual void OwnerKilledUnit(Unit *) {}

        // Called when the creature summon successfully other creature
        virtual void JustSummoned(Creature* ) {}

        // Called when the creature summon successfully a gameobject
        virtual void JustSummoned(GameObject* ) {}

        // Called when the creature summon despawn
        virtual void SummonedCreatureDespawn(Creature* /*unit*/) {}

        // Called when hit by a spell
        virtual void SpellHit(Unit*, const SpellEntry*) {}

        // Called when spell hits creature's target
        virtual void SpellHitTarget(Unit*, const SpellEntry*) {}

        // Called when the creature is target of hostile action: swing, hostile spell landed, fear/etc)
        virtual void AttackedBy(Unit* attacker);

        // Called when creature is spawned or respawned (for reseting variables)
        virtual void JustRespawned() { }

        // Called at waypoint reached or point movement finished
        virtual void MovementInform(uint32 /*MovementType*/, uint32 /*Data*/) {}

        // Called if a temporary summoned of m_creature reach a move point
        virtual void SummonedMovementInform(Creature* /*summoned*/, uint32 /*motion_type*/, uint32 /*point_id*/) {}

        // Called at text emote receive from player
        virtual void ReceiveEmote(Player* /*pPlayer*/, uint32 /*text_emote*/) {}

        virtual void OwnerAttackedBy(Unit* /*attacker*/) {}
        virtual void OwnerAttacked(Unit* /*target*/) {}

        ///== Triggered Actions Requested ==================

        // Called when creature attack expected (if creature can and no have current victim)
        // Note: for reaction at hostile action must be called AttackedBy function.
        virtual void AttackStart(Unit *) {}

        // Called at World update tick
        virtual void UpdateAI(const uint32 /*diff*/) {}

        // Comme UpdateAI, mais pour quand le mob est sous forme de corps.
        virtual void UpdateAI_corpse(const uint32 /*uiDiff*/) {}

        ///== State checks =================================

        // called when the corpse of this creature gets removed
        virtual void CorpseRemoved(uint32 & /*respawnDelay*/) {}

        // Called when victim entered water and creature can not enter water
        virtual bool canReachByRangeAttack(Unit*) { return false; }

        // Is corpse looting allowed ?
        virtual bool CanBeLooted() const { return true; }

        // Called when filling loot table
        virtual bool FillLoot(Loot* loot, Player* looter) const { return false; }

		/**
		* Check if unit is visible for MoveInLineOfSight
		* Note: This check is by default only the state-depending (visibility, range), NOT LineOfSight
		* @param pWho Unit* who is checked if it is visible for the creature
		*/
        virtual bool IsVisible(Unit* /* pWho */) const { return false; }
        virtual bool IsVisibleFor(Unit const* /* pWho */, bool & /* isVisible */) const { return false; }

        /**
         * @brief Triggers an alert when a Unit moves near stealth detection range
         * @param who
         */
        virtual void TriggerAlert(Unit const* who);
		///== Event Handling ===============================

		/**
		* Send an AI Event to nearby Creatures around
		* @param uiType number to specify the event, default cases listed in enum AIEventType
		* @param pInvoker Unit that triggered this event (like an attacker)
		* @param uiDelay  delay time until the Event will be triggered
		* @param fRadius  range in which for receiver is searched
		*/
		void SendAIEventAround(AIEventType eventType, Unit* pInvoker, uint32 uiDelay, float fRadius, uint32 miscValue = 0) const;

		/**
		* Send an AI Event to a Creature
		* @param eventType to specify the event, default cases listed in enum AIEventType
		* @param pInvoker Unit that triggered this event (like an attacker)
		* @param pReceiver Creature to receive this event
		*/
		void SendAIEvent(AIEventType eventType, Unit* pInvoker, Creature* pReceiver, uint32 miscValue = 0) const;

		/**
		* Called when an AI Event is received
		* @param eventType to specify the event, default cases listed in enum AIEventType
		* @param pSender Creature that sent this event
		* @param pInvoker Unit that triggered this event (like an attacker)
		*/
		virtual void ReceiveAIEvent(AIEventType /*eventType*/, Creature* /*pSender*/, Unit* /*pInvoker*/, uint32 /*miscValue*/) {}

        // TrinityCore
        void DoCast(Unit* victim, uint32 spellId, bool triggered = false);
        void DoCastVictim(uint32 spellId, bool triggered = false);
        void DoCastAOE(uint32 spellId, bool triggered = false);
        bool UpdateVictim();
        bool UpdateCombatState();
        bool UpdateVictimWithGaze();
        void SetGazeOn(Unit *target);

        ///== Helper functions =============================
        bool DoMeleeAttackIfReady();
        CanCastResult DoCastSpellIfCan(Unit* pTarget, uint32 uiSpell, uint32 uiCastFlags = 0, ObjectGuid uiOriginalCasterGUID = ObjectGuid());
        void ClearTargetIcon();
        ///== Fields =======================================

		/// Set combat movement (on/off), also sets UNIT_STAT_NO_COMBAT_MOVEMENT
		void SetCombatMovement(bool enable, bool stopOrStartMovement = false);
		bool IsCombatMovement() const { return m_isCombatMovement; }

        // Pointer to controlled by AI creature
        Creature* const m_creature;
        bool SwitchAiAtControl() const { return !m_bUseAiAtControl; }
        void SetUseAiAtControl(bool v) { m_bUseAiAtControl = v; }
		/// Combat movement currently enabled
		bool m_isCombatMovement;
    protected:
        bool m_bUseAiAtControl;
        uint32 m_uLastAlertTime;
		bool m_dismountOnAggro;
};

struct SelectableAI : FactoryHolder<CreatureAI>, Permissible<Creature>
{
    explicit SelectableAI(const char *id) : FactoryHolder<CreatureAI>(id) {}
};

template<class REAL_AI>
struct CreatureAIFactory : SelectableAI
{
    explicit CreatureAIFactory(const char *name) : SelectableAI(name) {}

    CreatureAI* Create(void *) const override;

    int Permit(const Creature *c) const override { return REAL_AI::Permissible(c); }
};

enum Permitions
{
    PERMIT_BASE_NO                 = -1,
    PERMIT_BASE_IDLE               = 1,
    PERMIT_BASE_REACTIVE           = 100,
    PERMIT_BASE_PROACTIVE          = 200,
    PERMIT_BASE_FACTION_SPECIFIC   = 400,
    PERMIT_BASE_SPECIAL            = 800
};

typedef FactoryHolder<CreatureAI> CreatureAICreator;
typedef FactoryHolder<CreatureAI>::FactoryHolderRegistry CreatureAIRegistry;
typedef FactoryHolder<CreatureAI>::FactoryHolderRepository CreatureAIRepository;
#endif
