/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software licensed under GPL version 2
 * Please see the included DOCS/LICENSE.TXT for more information */

#ifndef SC_CREATURE_H
#define SC_CREATURE_H

#include "CreatureAI.h"
#include "Creature.h"
#include "ScriptMgr.h"

#define CAST_PLR(a)     (dynamic_cast<Player*>(a))
#define CAST_CRE(a)     (dynamic_cast<Creature*>(a))
#define CAST_SUM(a)     (dynamic_cast<TempSummon*>(a))
#define CAST_PET(a)     (dynamic_cast<Pet*>(a))
#define CAST_AI(a,b)    (dynamic_cast<a*>(b))

 // Zerix: Select a random target (used in many scripts) at position 0.
#define SELECT_RANDOM_TARGET_POS_0 me->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0)

#define GET_SPELL(a)    (const_cast<SpellEntry*>(GetSpellStore()->LookupEntry(a)))

class ScriptedInstance;

class SummonList : std::list<uint64>
{
public:
	SummonList(Creature* creature) : m_creature(creature) {}
	void Summon(Creature *summon) { push_back(summon->GetGUID()); }
	void Despawn(Creature *summon);
	void DespawnEntry(uint32 entry);
	void DespawnAll();
	bool isEmpty();
	void AuraOnEntry(uint32 entry, uint32 spellId, bool apply);
	void DoAction(uint32 entry, uint32 info);
	void Cast(uint32 entry, uint32 spell, Unit* target);
private:
	Creature *m_creature;
};

struct PointMovement
{
	uint32 m_uiCreatureEntry;
	uint32 m_uiPointId;
	float m_fX;
	float m_fY;
	float m_fZ;
	uint32 m_uiWaitTime;
};

enum interruptSpell
{
	DONT_INTERRUPT = 0,
	INTERRUPT_AND_CAST = 1,   //cast when CastNextSpellIfAnyAndReady() is called
	INTERRUPT_AND_CAST_INSTANTLY = 2    //cast instantly (CastSpell())
};

enum castTargetMode
{
	CAST_TANK = 0,    //cast on GetVictim() target
	CAST_NULL = 1,    //cast on (Unit*)NULL target
	CAST_RANDOM = 2,    //cast on SelectUnit(SELECT_TARGET_RANDOM) target (needs additionals: range, only player)
	CAST_RANDOM_WITHOUT_TANK = 3,    //same as AUTOCAST_RANDOM but without tank
	CAST_SELF = 4,    //target is m_creature
	CAST_LOWEST_HP_FRIENDLY = 5,    //cast on SelectLowestHpFriendly
	CAST_THREAT_SECOND = 6     //cast on target in second place in threatlist
};

enum movementCheckType
{
	CHECK_TYPE_NONE = 0,
	CHECK_TYPE_CASTER = 1,    // move only when outranged or not in LoS
	CHECK_TYPE_SHOOTER = 2     // chase when in 5yd distance, move when outranged or not in LoS
};

enum SpecialThing
{
	DO_SPEED_UPDATE = 0x01,
	DO_EVADE_CHECK = 0x02,
	DO_PULSE_COMBAT = 0x04,
	DO_COMBAT_N_SPEED = (DO_PULSE_COMBAT | DO_SPEED_UPDATE),
	DO_COMBAT_N_EVADE = (DO_PULSE_COMBAT | DO_EVADE_CHECK),
	DO_EVERYTHING = (DO_COMBAT_N_SPEED | DO_EVADE_CHECK),
};

class SpellToCast
{
public:
	float castDest[3];
	int32 damage[3];
	uint64 targetGUID;
	uint32 spellId;
	bool triggered;
	bool isDestCast;
	bool hasCustomValues;
	bool setAsTarget;
	int32 scriptTextEntry;

	SpellToCast(Unit* target, uint32 spellId, bool triggered, int32 scriptTextEntry, bool visualTarget)
	{

		if (target)
			this->targetGUID = target->GetGUID();
		else
			this->targetGUID = 0;

		this->isDestCast = false;
		this->hasCustomValues = false;
		this->spellId = spellId;
		this->triggered = triggered;
		this->scriptTextEntry = scriptTextEntry;
		this->setAsTarget = visualTarget;
	}

	SpellToCast(uint64 target, uint32 spellId, bool triggered, int32 scriptTextEntry, bool visualTarget)
	{
		this->isDestCast = false;
		this->hasCustomValues = false;
		this->targetGUID = target;
		this->spellId = spellId;
		this->triggered = triggered;
		this->scriptTextEntry = scriptTextEntry;
		this->setAsTarget = visualTarget;
	}

	SpellToCast(float x, float y, float z, uint32 spellId, bool triggered, int32 scriptTextEntry, bool visualTarget)
	{
		this->isDestCast = true;
		this->hasCustomValues = false;
		this->castDest[0] = x;
		this->castDest[1] = y;
		this->castDest[2] = z;
		this->spellId = spellId;
		this->triggered = triggered;
		this->scriptTextEntry = scriptTextEntry;
		this->setAsTarget = visualTarget;
	}

	SpellToCast(uint64 target, uint32 spellId, int32 dmg0, int32 dmg1, int32 dmg2, bool triggered, int32 scriptTextEntry, bool visualTarget)
	{
		this->isDestCast = false;
		this->hasCustomValues = true;
		this->damage[0] = dmg0;
		this->damage[1] = dmg1;
		this->damage[2] = dmg2;
		this->targetGUID = target;
		this->spellId = spellId;
		this->triggered = triggered;
		this->scriptTextEntry = scriptTextEntry;
		this->setAsTarget = visualTarget;
	}

	SpellToCast()
	{
		this->targetGUID = 0;
		this->spellId = 0;
		this->triggered = false;
		this->scriptTextEntry = 0;
		this->setAsTarget = false;
		this->isDestCast = false;
		for (uint8 i = 0; i<3; ++i)
		{
			this->castDest[i] = 0;
			this->damage[i] = 0;
		}
	}

	~SpellToCast()
	{
		this->targetGUID = 0;
		this->spellId = 0;
		this->triggered = false;
		this->scriptTextEntry = 0;
		this->setAsTarget = false;
		this->isDestCast = false;
		for (uint8 i = 0; i<3; ++i)
		{
			this->castDest[i] = 0;
			this->damage[i] = 0;
		}
	}
};
enum SCEquip
{
    EQUIP_NO_CHANGE = -1,
    EQUIP_UNEQUIP   = 0
};

struct MANGOS_DLL_DECL ScriptedAI : CreatureAI
{
    explicit ScriptedAI(Creature* pCreature);
    ~ScriptedAI() {}

    //*************
    //CreatureAI Functions
    //*************

    //Called if IsVisible(Unit *who) is true at each *who move
    void MoveInLineOfSight(Unit*) override;

    //Called at each attack of m_creature by any victim
    void AttackStart(Unit*) override;

    // Called for reaction at enter to combat if not in combat yet (enemy can be NULL)
    void EnterCombat(Unit*) override;

    //Called at stoping attack by any attacker
    void EnterEvadeMode() override;

    //Called at any heal cast/item used (call non implemented in mangos)
	void HealedBy(Unit* /*pHealer*/, uint32 /*uiAmountHealed*/) override {}

    // Called at any Damage to any victim (before damage apply)
    void DamageDeal(Unit* /*pDoneTo*/, uint32& /*uiDamage*/) override {}

    // Called at any Damage from any attacker (before damage apply)
    void DamageTaken(Unit* /*pDoneBy*/, uint32& /*uiDamage*/) override {}

    //Called at World update tick
    void UpdateAI(const uint32) override;

    //Called at creature death
    void JustDied(Unit*) override {}

    //Called at creature killing another unit
    void KilledUnit(Unit*) override {}

    // Called when the creature summon successfully other creature
    void JustSummoned(Creature*) override {}

    // Called when a summoned creature is despawned
    void SummonedCreatureDespawn(Creature*) override {}

    // Called when hit by a spell
    void SpellHit(Unit*, const SpellEntry*) override {}

    // Called when creature is spawned or respawned (for reseting variables)
    void JustRespawned() override;

    //Called at waypoint reached or PointMovement end
    void MovementInform(uint32, uint32) override {}

    //*************
    // Variables
    //*************

    //*************
    //Pure virtual functions
    //*************

    //Called at creature reset either by death or evade
    virtual void Reset() = 0;

    // Called at creature death only
    virtual void ResetCreature() {}

    //Called at creature EnterCombat
    virtual void Aggro(Unit*);

    //*************
    //AI Helper Functions
    //*************

    //Start movement toward victim
    void DoStartMovement(Unit* pVictim, float fDistance = 0, float fAngle = 0);

    //Start no movement on victim
    void DoStartNoMovement(Unit* pVictim);

    //Stop attack of current victim
    void DoStopAttack();

    //Cast spell by spell info
    void DoCastSpell(Unit* pwho, SpellEntry const* pSpellInfo, bool bTriggered = false);

    //Plays a sound to all nearby players
    void DoPlaySoundToSet(WorldObject* pSource, uint32 uiSoundId);

    void SendMonsterMoveWithSpeed(float x, float y, float z, uint32 MovementFlags, uint32 transitTime = 0, Player* player = nullptr);
    //Drops all threat to 0%. Does not remove players from the threat list
    void DoResetThreat();

    //Teleports a player without dropping threat (only teleports to same map)
    void DoTeleportPlayer(Unit* pUnit, float fX, float fY, float fZ, float fO);

    //Returns friendly unit with the most amount of hp missing from max hp
    Unit* DoSelectLowestHpFriendly(float fRange, uint32 uiMinHPDiff = 1, bool bPercent = false) const;

    //Returns a list of friendly CC'd units within range
    std::list<Creature*> DoFindFriendlyCC(float fRange);

    //Returns a list of all friendly units missing a specific buff within range
    std::list<Creature*> DoFindFriendlyMissingBuff(float fRange, uint32 uiSpellId);

    //Return a player with at least minimumRange from m_creature
    Player* GetPlayerAtMinimumRange(float fMinimumRange);

    //Spawns a creature relative to m_creature
    Creature* DoSpawnCreature(uint32 uiId, float fX, float fY, float fZ, float fAngle, uint32 uiType, uint32 uiDespawntime);

    //Spawns a creature at a random position around m_creature
    Creature* DoSpawnCreature(uint32 id, float dist, uint32 type, uint32 despawntime);

    //Returns spells that meet the specified criteria from the creatures spell list
    SpellEntry const* SelectSpell(Unit* pTarget, int32 uiSchool, int32 uiMechanic, SelectTarget selectTargets, uint32 uiPowerCostMin, uint32 uiPowerCostMax, float fRangeMin, float fRangeMax, SelectEffect selectEffect);

    //Checks if you can cast the specified spell
    bool CanCast(Unit* pTarget, SpellEntry const* pSpell, bool bTriggered = false);

    void SetEquipmentSlots(bool bLoadDefault, int32 uiMainHand = EQUIP_NO_CHANGE, int32 uiOffHand = EQUIP_NO_CHANGE, int32 uiRanged = EQUIP_NO_CHANGE);

    //Generally used to control if MoveChase() is to be used or not in AttackStart(). Some creatures does not chase victims
    void SetCombatMovement(bool bCombatMove);
    bool IsCombatMovement() const { return m_bCombatMovement; }

    bool EnterEvadeIfOutOfCombatArea(const uint32 uiDiff);
    void EnterEvadeIfOutOfHomeArea();

    void DoGoHome();
	//custom
	uint32 Randomize(uint32 interval, float multiplier = 0);
	uint32 RandomizeUp(uint32 interval, float multiplier = 0);
	void ServerFirst(Unit *killer);

    float DoGetThreat(Unit* pUnit);
    void DoModifyThreatPercent(Unit* pUnit, int32 pct);
    void DoTeleportTo(float fX, float fY, float fZ, uint32 uiTime);
    void DoTeleportTo(const float fPos[4]);
    void DoTeleportAll(float fX, float fY, float fZ, float fO);
    Creature* me;
	void SetAttackDistance(float distance) { m_attackDistance = distance; }

    private:
        bool   m_bCombatMovement;
        uint32 m_uiEvadeCheckCooldown;

		/// How should an enemy be chased
		float m_attackDistance;
		float m_attackAngle;

        bool m_bEvadeOutOfHomeArea;
        uint32 m_uiHomeArea;
};

struct MANGOS_DLL_DECL Scripted_NoMovementAI : ScriptedAI
{
    explicit Scripted_NoMovementAI(Creature* pCreature) : ScriptedAI(pCreature) {}

    //Called at each attack of m_creature by any victim
    void AttackStart(Unit*) override;
};

#endif
