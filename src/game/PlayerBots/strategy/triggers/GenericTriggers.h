#pragma once
#include "../Trigger.h"

#include "BattleGround.h"
#include "BattleGroundMgr.h"
#include "BattleGroundWS.h"
#include "../../PlayerbotAIConfig.h"

#define BUFF_TRIGGER(clazz, spell, action) \
    class clazz : public BuffTrigger \
    { \
    public: \
        clazz(PlayerbotAI* ai) : BuffTrigger(ai, spell) {} \
    };

#define BUFF_ON_PARTY_TRIGGER(clazz, spell, action) \
    class clazz : public BuffOnPartyTrigger \
    { \
    public: \
        clazz(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, spell) {}  \
    };

#define DEBUFF_TRIGGER(clazz, spell, action) \
    class clazz : public DebuffTrigger \
    { \
    public: \
        clazz(PlayerbotAI* ai) : DebuffTrigger(ai, spell) {} \
    };

namespace ai
{
	class StatAvailable : public Trigger
	{
	public:
		StatAvailable(PlayerbotAI* ai, int amount, string name = "stat available") : Trigger(ai, name)
		{
			this->amount = amount;
		}

	protected:
		int amount;
	};

	class RageAvailable : public StatAvailable
    {
    public:
        RageAvailable(PlayerbotAI* ai, int amount) : StatAvailable(ai, amount, "rage available") {}
        virtual bool IsActive();
    };

    class LightRageAvailableTrigger : public RageAvailable
    {
    public:
        LightRageAvailableTrigger(PlayerbotAI* ai) : RageAvailable(ai, 20) {}
    };

    class MediumRageAvailableTrigger : public RageAvailable
    {
    public:
        MediumRageAvailableTrigger(PlayerbotAI* ai) : RageAvailable(ai, 40) {}
    };

    class HighRageAvailableTrigger : public RageAvailable
    {
    public:
        HighRageAvailableTrigger(PlayerbotAI* ai) : RageAvailable(ai, 60) {}
    };

	class EnergyAvailable : public StatAvailable
	{
	public:
		EnergyAvailable(PlayerbotAI* ai, int amount) : StatAvailable(ai, amount, "energy available") {}
		virtual bool IsActive();
	};

    class LightEnergyAvailableTrigger : public EnergyAvailable
    {
    public:
        LightEnergyAvailableTrigger(PlayerbotAI* ai) : EnergyAvailable(ai, 20) {}
    };

    class MediumEnergyAvailableTrigger : public EnergyAvailable
    {
    public:
        MediumEnergyAvailableTrigger(PlayerbotAI* ai) : EnergyAvailable(ai, 40) {}
    };

    class HighEnergyAvailableTrigger : public EnergyAvailable
    {
    public:
        HighEnergyAvailableTrigger(PlayerbotAI* ai) : EnergyAvailable(ai, 60) {}
    };

	class ComboPointsAvailableTrigger : public StatAvailable
	{
	public:
	    ComboPointsAvailableTrigger(PlayerbotAI* ai, int amount = 5) : StatAvailable(ai, amount, "combo points available") {}
		virtual bool IsActive();
	};

	class ComboPointAvailableTrigger : public StatAvailable
	{
	public:
	    ComboPointAvailableTrigger(PlayerbotAI* ai, int amount = 2) : StatAvailable(ai, amount, "combo point available") {}
		virtual bool IsActive();
	};

	class LoseAggroTrigger : public Trigger {
	public:
		LoseAggroTrigger(PlayerbotAI* ai) : Trigger(ai, "lose aggro") {}
		virtual bool IsActive();
	};

	class HasAggroTrigger : public Trigger {
	public:
	    HasAggroTrigger(PlayerbotAI* ai) : Trigger(ai, "have aggro") {}
		virtual bool IsActive();
	};

	class SpellTrigger : public Trigger
	{
	public:
		SpellTrigger(PlayerbotAI* ai, string spell, int checkInterval = 1) : Trigger(ai, spell, checkInterval)
		{
			this->spell = spell;
		}

		virtual string GetTargetName() { return "current target"; }
		virtual string getName() { return spell; }
		virtual bool IsActive();

	protected:
		string spell;
	};

	class SpellCanBeCastTrigger : public SpellTrigger
	{
	public:
		SpellCanBeCastTrigger(PlayerbotAI* ai, string spell) : SpellTrigger(ai, spell) {}
		virtual bool IsActive();
	};

	// TODO: check other targets
    class InterruptSpellTrigger : public SpellTrigger
	{
    public:
        InterruptSpellTrigger(PlayerbotAI* ai, string spell) : SpellTrigger(ai, spell) {}
        virtual bool IsActive();
    };


    class AttackerCountTrigger : public Trigger
    {
    public:
        AttackerCountTrigger(PlayerbotAI* ai, int amount, float distance = sPlayerbotAIConfig.sightDistance) : Trigger(ai)
        {
            this->amount = amount;
            this->distance = distance;
        }
    public:
        virtual bool IsActive()
		{
            return AI_VALUE(uint8, "attacker count") >= amount;
        }
        virtual string getName() { return "attacker count"; }

    protected:
        int amount;
        float distance;
    };

    class AoeAttackerCountTrigger : public Trigger
    {
    public:
        AoeAttackerCountTrigger(PlayerbotAI* ai, int amount, float distance = sPlayerbotAIConfig.sightDistance) : Trigger(ai)
        {
            this->amount = amount;
            this->distance = distance;
        }
    public:
        virtual bool IsActive()
		{
			return (AI_VALUE(uint8, "aoe attacker count") > 0) ? true : false;
        }
        virtual string getName() { return "aoe attacker count"; }

    protected:
        int amount;
        float distance;
    };

    class HasAttackersTrigger : public AttackerCountTrigger
    {
    public:
        HasAttackersTrigger(PlayerbotAI* ai) : AttackerCountTrigger(ai, 1) {}
    };

    class MyAttackerCountTrigger : public AttackerCountTrigger
    {
    public:
        MyAttackerCountTrigger(PlayerbotAI* ai, int amount) : AttackerCountTrigger(ai, amount) {}
    public:
        virtual bool IsActive();
        virtual string getName() { return "my attacker count"; }
    };

    class MediumThreatTrigger : public MyAttackerCountTrigger
    {
    public:
        MediumThreatTrigger(PlayerbotAI* ai) : MyAttackerCountTrigger(ai, 2) {}
    };

    class AoeTrigger : public AoeAttackerCountTrigger
    {
    public:
        AoeTrigger(PlayerbotAI* ai, int amount = 3, float range = 15.0f) : AoeAttackerCountTrigger(ai, amount)
        {
            this->range = range;
        }
    public:
        virtual bool IsActive();
        virtual string getName() { return "aoe"; }

    private:
        float range;
    };

    class MeleeAoeTrigger : public AoeAttackerCountTrigger
    {
    public:
        MeleeAoeTrigger(PlayerbotAI* ai, int amount = 3, float range = 5.0f) : AoeAttackerCountTrigger(ai, amount)
        {
            this->range = range;
        }
    public:
        virtual bool IsActive();
        virtual string getName() { return "melee aoe"; }

    private:
        float range;
    };

    class NoFoodTrigger : public Trigger {
    public:
        NoFoodTrigger(PlayerbotAI* ai) : Trigger(ai, "no food trigger") {}
        virtual bool IsActive() { return AI_VALUE2(list<Item*>, "inventory items", "food").empty(); }
    };

    class NoDrinkTrigger : public Trigger {
    public:
        NoDrinkTrigger(PlayerbotAI* ai) : Trigger(ai, "no drink trigger") {}
        virtual bool IsActive() { return AI_VALUE2(list<Item*>, "inventory items", "drink").empty(); }
    };

    class NoAoeTrigger : public AoeTrigger
    {
    public:
        NoAoeTrigger(PlayerbotAI* ai) : AoeTrigger(ai, 1, 12.0f) {}
    };

    class LightAoeTrigger : public AoeTrigger
    {
    public:
        LightAoeTrigger(PlayerbotAI* ai) : AoeTrigger(ai, 2, 12.0f) {}
    };

    class MediumAoeTrigger : public AoeTrigger
    {
    public:
        MediumAoeTrigger(PlayerbotAI* ai) : AoeTrigger(ai, 3, 15.0f) {}
    };

    class HighAoeTrigger : public AoeTrigger
    {
    public:
        HighAoeTrigger(PlayerbotAI* ai) : AoeTrigger(ai, 4, 20.0f) {}
    };

    class MeleeNoAoeTrigger : public MeleeAoeTrigger
    {
    public:
        MeleeNoAoeTrigger(PlayerbotAI* ai) : MeleeAoeTrigger(ai, 1, 8.0f) {}
    };

    class MeleeLightAoeTrigger : public MeleeAoeTrigger
    {
    public:
        MeleeLightAoeTrigger(PlayerbotAI* ai) : MeleeAoeTrigger(ai, 2, 8.0f) {}
    };

    class MeleeMediumAoeTrigger : public MeleeAoeTrigger
    {
    public:
        MeleeMediumAoeTrigger(PlayerbotAI* ai) : MeleeAoeTrigger(ai, 3, 10.0f) {}
    };

    class MeleeHighAoeTrigger : public MeleeAoeTrigger
    {
    public:
        MeleeHighAoeTrigger(PlayerbotAI* ai) : MeleeAoeTrigger(ai, 4, 10.0f) {}
    };

    class BuffTrigger : public SpellTrigger
    {
    public:
		BuffTrigger(PlayerbotAI* ai, string spell, int checkInterval = 5) : SpellTrigger(ai, spell, checkInterval) {}
    public:
		virtual string GetTargetName() { return "self target"; }
        virtual bool IsActive();
    };

    class BuffOnPartyTrigger : public BuffTrigger
    {
    public:
        BuffOnPartyTrigger(PlayerbotAI* ai, string spell) : BuffTrigger(ai, spell) {}
    public:
		virtual Value<Unit*>* GetTargetValue();
    };

    class BuffOnMasterTrigger : public BuffTrigger
    {
    public:
        BuffOnMasterTrigger(PlayerbotAI* ai, string spell) : BuffTrigger(ai, spell) {}
    public:
		virtual Value<Unit*>* GetTargetValue();
    };

    BEGIN_TRIGGER(NoAttackersTrigger, Trigger)
    END_TRIGGER()

    BEGIN_TRIGGER(NoTargetTrigger, Trigger)
    END_TRIGGER()

    BEGIN_TRIGGER(InvalidTargetTrigger, Trigger)
    END_TRIGGER()

    class TargetInSightTrigger : public Trigger {
    public:
        TargetInSightTrigger(PlayerbotAI* ai) : Trigger(ai, "target in sight") {}
        virtual bool IsActive() { return AI_VALUE(Unit*, "grind target")? true:false; }
    };

    class DebuffTrigger : public BuffTrigger
    {
    public:
		DebuffTrigger(PlayerbotAI* ai, string spell, int checkInterval = 5) : BuffTrigger(ai, spell, checkInterval) {
			checkInterval = 1;
		}
    public:
		virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    };

     class OwnDebuffTrigger : public BuffTrigger
    {
    public:
        OwnDebuffTrigger(PlayerbotAI* ai, string spell) : BuffTrigger(ai, spell) {
			checkInterval = 1;
		}
    public:
		virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    };

    class DebuffOnAttackerTrigger : public DebuffTrigger
    {
    public:
        DebuffOnAttackerTrigger(PlayerbotAI* ai, string spell) : DebuffTrigger(ai, spell) {}
    public:
        virtual Value<Unit*>* GetTargetValue();
        virtual string getName() { return spell + " on attacker"; }
    };

    class OwnDebuffOnAttackerTrigger : public OwnDebuffTrigger
    {
    public:
        OwnDebuffOnAttackerTrigger(PlayerbotAI* ai, string spell) : OwnDebuffTrigger(ai, spell) {}
    public:
        virtual Value<Unit*>* GetTargetValue();
        virtual string getName() { return spell + " on attacker"; }
    };

    class HotTrigger : public SpellTrigger
    {
    public:
        HotTrigger(PlayerbotAI* ai, string spell) : SpellTrigger(ai, spell, 5) {}
    public:
		virtual string GetTargetName() { return "self target"; }
        virtual bool IsActive();
    };

	class BoostTrigger : public BuffTrigger
	{
	public:
		BoostTrigger(PlayerbotAI* ai, string spell, float balance = 50) : BuffTrigger(ai, spell, 1)
		{
			this->balance = balance;
		}
	public:
		virtual bool IsActive();

	protected:
		float balance;
	};

    class RandomTrigger : public Trigger
    {
    public:
		RandomTrigger(PlayerbotAI* ai, string name, int probability = 7) : Trigger(ai, name)
        {
            this->probability = probability;
			lastCheck = time(0);
        }
    public:
        virtual bool IsActive();
        virtual string getName() { return "random"; }

    protected:
        int probability;
		time_t lastCheck;
	};

    class AndTrigger : public Trigger
    {
    public:
        AndTrigger(PlayerbotAI* ai, Trigger* ls, Trigger* rs) : Trigger(ai)
        {
            this->ls = ls;
            this->rs = rs;
        }
        virtual ~AndTrigger()
        {
            delete ls;
            delete rs;
        }
    public:
        virtual bool IsActive();
        virtual string getName();

    protected:
        Trigger* ls;
        Trigger* rs;
    };

    class SnareTargetTrigger : public DebuffTrigger
    {
    public:
        SnareTargetTrigger(PlayerbotAI* ai, string aura) : DebuffTrigger(ai, aura) {}
    public:
        virtual bool IsActive();
        virtual string getName() { return "target is moving"; }
    };

	class AlmostNoManaTrigger : public Trigger
	{
	public:
		AlmostNoManaTrigger(PlayerbotAI* ai) : Trigger(ai, "almost no mana") {}

		virtual bool IsActive();
	};

	class LowManaTrigger : public Trigger
	{
	public:
		LowManaTrigger(PlayerbotAI* ai) : Trigger(ai, "low mana") {}

		virtual bool IsActive();
	};

	class MediumManaTrigger : public Trigger
	{
	public:
		MediumManaTrigger(PlayerbotAI* ai) : Trigger(ai, "medium mana") {}

		virtual bool IsActive();
	};

	class AlmostFullManaTrigger : public Trigger
	{
	public:
		AlmostFullManaTrigger(PlayerbotAI* ai) : Trigger(ai, "almost full mana") {}

		virtual bool IsActive();
	};

	class FullManaTrigger : public Trigger
	{
	public:
		FullManaTrigger(PlayerbotAI* ai) : Trigger(ai, "full mana") {}

		virtual bool IsActive();
	};

	class DrinkManaTrigger : public Trigger
	{
	public:
		DrinkManaTrigger(PlayerbotAI* ai) : Trigger(ai, "drink mana") {}

		virtual bool IsActive();
	};

    BEGIN_TRIGGER(PanicTrigger, Trigger)
        virtual string getName() { return "panic"; }
    END_TRIGGER()


	class NoPetTrigger : public Trigger
	{
	public:
		NoPetTrigger(PlayerbotAI* ai) : Trigger(ai, "no pet", 5) {}

		virtual bool IsActive() {
			return !AI_VALUE(Unit*, "pet target") && !AI_VALUE2(bool, "mounted", "self target");
		}
	};

	class ItemCountTrigger : public Trigger {
	public:
		ItemCountTrigger(PlayerbotAI* ai, string item, int count) : Trigger(ai, item, 5) {
			this->item = item;
			this->count = count;
		}
	public:
		virtual bool IsActive();
		virtual string getName() { return "item count"; }

	protected:
		string item;
		int count;
	};


	class HasAuraIdTrigger : public Trigger {
	public:
		HasAuraIdTrigger(PlayerbotAI* ai, string spell, uint32 spellId) : Trigger(ai, spell, 5){
            this->spellId = spellId;
		}

    public:
		virtual string GetTargetName() { return "self target"; }
		virtual bool IsActive();

    protected:
        uint32 spellId;
	};

	class HasAuraTrigger : public Trigger {
	public:
		HasAuraTrigger(PlayerbotAI* ai, string spell) : Trigger(ai, spell, 5) {}

		virtual string GetTargetName() { return "self target"; }
		virtual bool IsActive();

	};

    class TimerTrigger : public Trigger
    {
    public:
		TimerTrigger(PlayerbotAI* ai) : Trigger(ai, "timer")
		{
			lastCheck = 0;
			}

    public:
		virtual bool IsActive()
		{
			if (time(0) != lastCheck)
			{
				lastCheck = time(0);
				return true;
				}
			}
		
	private:
		time_t lastCheck;
    };

	class TankAoeTrigger : public NoAttackersTrigger
	{
	public:
		TankAoeTrigger(PlayerbotAI* ai) : NoAttackersTrigger(ai) {}

	public:
		virtual bool IsActive();

	};

    class IsBehindTargetTrigger : public Trigger
    {
    public:
        IsBehindTargetTrigger(PlayerbotAI* ai) : Trigger(ai) {}

    public:
        virtual bool IsActive();
    };

    class IsFrontTargetTrigger : public Trigger
    {
    public:
        IsFrontTargetTrigger(PlayerbotAI* ai) : Trigger(ai) {}

    public:
        virtual bool IsActive();
    };

    class IsNotFacingTargetTrigger : public Trigger
    {
    public:
        IsNotFacingTargetTrigger(PlayerbotAI* ai) : Trigger(ai) {}

    public:
        virtual bool IsActive();
    };

    class HasCcTargetTrigger : public Trigger
    {
    public:
        HasCcTargetTrigger(PlayerbotAI* ai, string name) : Trigger(ai, name) {}

    public:
        virtual bool IsActive();
    };

    class HasCcTarget2Trigger : public Trigger
    {
    public:
        HasCcTarget2Trigger(PlayerbotAI* ai, string name) : Trigger(ai, name) {}

    public:
        virtual bool IsActive();
    };

    class HasCcTarget3Trigger : public Trigger
    {
    public:
        HasCcTarget3Trigger(PlayerbotAI* ai, string name) : Trigger(ai, name) {}

    public:
        virtual bool IsActive();
    };

    class HasCcTarget4Trigger : public Trigger
    {
    public:
        HasCcTarget4Trigger(PlayerbotAI* ai, string name) : Trigger(ai, name) {}

    public:
        virtual bool IsActive();
    };

    class HasCcTarget5Trigger : public Trigger
    {
    public:
        HasCcTarget5Trigger(PlayerbotAI* ai, string name) : Trigger(ai, name) {}

    public:
        virtual bool IsActive();
    };

    class HasCcTarget6Trigger : public Trigger
    {
    public:
        HasCcTarget6Trigger(PlayerbotAI* ai, string name) : Trigger(ai, name) {}

    public:
        virtual bool IsActive();
    };

	class NoMovementTrigger : public Trigger
	{
	public:
		NoMovementTrigger(PlayerbotAI* ai, string name) : Trigger(ai, name) {}

	public:
		virtual bool IsActive();
	};


    class NoPossibleTargetsTrigger : public Trigger
    {
    public:
        NoPossibleTargetsTrigger(PlayerbotAI* ai) : Trigger(ai, "no possible targets") {}

    public:
        virtual bool IsActive();
    };

    class NotLeastHpTargetActiveTrigger : public Trigger
    {
    public:
        NotLeastHpTargetActiveTrigger(PlayerbotAI* ai) : Trigger(ai, "not least hp target active") {}

    public:
        virtual bool IsActive();
    };

    class EnemyPlayerIsAttacking : public Trigger
    {
    public:
        EnemyPlayerIsAttacking(PlayerbotAI* ai) : Trigger(ai, "enemy player is attacking") {}

    public:
        virtual bool IsActive();
    };

    class IsSwimmingTrigger : public Trigger
    {
    public:
        IsSwimmingTrigger(PlayerbotAI* ai) : Trigger(ai, "swimming") {}

    public:
        virtual bool IsActive();
    };

    class HasNearestAddsTrigger : public Trigger
    {
    public:
        HasNearestAddsTrigger(PlayerbotAI* ai) : Trigger(ai, "has nearest adds") {}

    public:
        virtual bool IsActive();
    };

    class HasGroupMemberNearTrigger : public Trigger
    {
    public:
        HasGroupMemberNearTrigger(PlayerbotAI* ai) : Trigger(ai, "group member near") {}

    public:
        virtual bool IsActive();
    };

    class HasItemForSpellTrigger : public Trigger
    {
    public:
        HasItemForSpellTrigger(PlayerbotAI* ai, string spell) : Trigger(ai, spell) {}

    public:
        virtual bool IsActive();
    };

    class MainhandEnhanceTrigger : public Trigger
    {
    public:
        MainhandEnhanceTrigger(PlayerbotAI* ai) : Trigger(ai, "mainhand not enhanced") {}

    public:
        virtual bool IsActive();
    };

    class OffhandEnhanceTrigger : public Trigger
    {
    public:
        OffhandEnhanceTrigger(PlayerbotAI* ai) : Trigger(ai, "offhand not enhanced") {}

    public:
        virtual bool IsActive();
    };

    class TargetChangedTrigger : public Trigger
    {
    public:
        TargetChangedTrigger(PlayerbotAI* ai) : Trigger(ai, "target changed") {}

    public:
        virtual bool IsActive();
    };

    class InterruptEnemyHealerTrigger : public SpellTrigger
    {
    public:
        InterruptEnemyHealerTrigger(PlayerbotAI* ai, string spell) : SpellTrigger(ai, spell) {}
    public:
        virtual Value<Unit*>* GetTargetValue();
        virtual string getName() { return spell + " on enemy healer"; }
    };

    class BleedingTrigger : public Trigger {
    public:
        BleedingTrigger(PlayerbotAI* ai) : Trigger(ai, "bleeding", 5) {}
        virtual string GetTargetName() { return "self target"; }
        virtual bool IsActive();
    };

    class FearedTrigger : public Trigger {
    public:
        FearedTrigger(PlayerbotAI* ai) : Trigger(ai, "feared", 5) {}
        virtual string GetTargetName() { return "self target"; }
        virtual bool IsActive();
    };

    class PolymorphedTrigger : public Trigger {
    public:
        PolymorphedTrigger(PlayerbotAI* ai) : Trigger(ai, "polymorphed", 5) {}
        virtual string GetTargetName() { return "self target"; }
        virtual bool IsActive();
    };

    class TakesPeriodicDamageTrigger : public Trigger {
    public:
        TakesPeriodicDamageTrigger(PlayerbotAI* ai) : Trigger(ai, "periodic damage", 5) {}
        virtual string GetTargetName() { return "self target"; }
        virtual bool IsActive();
    };

    class PossessedTrigger : public Trigger {
    public:
        PossessedTrigger(PlayerbotAI* ai) : Trigger(ai, "possessed", 5) {}
        virtual string GetTargetName() { return "self target"; }
        virtual bool IsActive();
    };

    class CharmedTrigger : public Trigger {
    public:
        CharmedTrigger(PlayerbotAI* ai) : Trigger(ai, "charmed", 5) {}
        virtual string GetTargetName() { return "self target"; }
        virtual bool IsActive();
    };

    class DisorientedTrigger : public Trigger {
    public:
        DisorientedTrigger(PlayerbotAI* ai) : Trigger(ai, "disoriented", 5) {}
        virtual string GetTargetName() { return "self target"; }
        virtual bool IsActive();
    };

    class SnaredTrigger : public Trigger {
    public:
        SnaredTrigger(PlayerbotAI* ai) : Trigger(ai, "snared", 5) {}
        virtual string GetTargetName() { return "self target"; }
        virtual bool IsActive();
    };

    class RootedTrigger : public Trigger {
    public:
        RootedTrigger(PlayerbotAI* ai) : Trigger(ai, "rooted", 5) {}
        virtual string GetTargetName() { return "self target"; }
        virtual bool IsActive();
    };

    class FrozenTrigger : public Trigger {
    public:
        FrozenTrigger(PlayerbotAI* ai) : Trigger(ai, "frozen", 5) {}
        virtual string GetTargetName() { return "self target"; }
        virtual bool IsActive();
    };

    class SilencedTrigger : public Trigger {
    public:
        SilencedTrigger(PlayerbotAI* ai) : Trigger(ai, "silenced", 5) {}
        virtual string GetTargetName() { return "self target"; }
        virtual bool IsActive();
    };

    class StunnedTrigger : public Trigger {
    public:
        StunnedTrigger(PlayerbotAI* ai) : Trigger(ai, "stunned", 5) {}
        virtual string GetTargetName() { return "self target"; }
        virtual bool IsActive();
    };

    class TargetPossessedTrigger : public Trigger {
    public:
        TargetPossessedTrigger(PlayerbotAI* ai) : Trigger(ai, "target possessed", 5) {}
        virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    };

    class TargetCharmedTrigger : public Trigger {
    public:
        TargetCharmedTrigger(PlayerbotAI* ai) : Trigger(ai, "target charmed", 5) {}
        virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    };

    class TargetDisorientedTrigger : public Trigger {
    public:
        TargetDisorientedTrigger(PlayerbotAI* ai) : Trigger(ai, "target disoriented", 5) {}
        virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    };

    class TargetSnaredTrigger : public Trigger {
    public:
        TargetSnaredTrigger(PlayerbotAI* ai) : Trigger(ai, "target snared", 5) {}
        virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    };

    class TargetRootedTrigger : public Trigger {
    public:
        TargetRootedTrigger(PlayerbotAI* ai) : Trigger(ai, "target rooted", 5) {}
        virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    };

    class TargetBleedingTrigger : public Trigger {
    public:
        TargetBleedingTrigger(PlayerbotAI* ai) : Trigger(ai, "target bleeding", 5) {}
        virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    };

    class TargetPolymorphedTrigger : public Trigger {
    public:
        TargetPolymorphedTrigger(PlayerbotAI* ai) : Trigger(ai, "target polymorphed", 5) {}
        virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    };

    class TargetSilencedTrigger : public Trigger {
    public:
        TargetSilencedTrigger(PlayerbotAI* ai) : Trigger(ai, "target silenced", 5) {}
        virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    };

    class TargetFrozenTrigger : public Trigger {
    public:
        TargetFrozenTrigger(PlayerbotAI* ai) : Trigger(ai, "target frozen", 5) {}
        virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    };

    class TargetFearedTrigger : public Trigger {
    public:
        TargetFearedTrigger(PlayerbotAI* ai) : Trigger(ai, "target feared", 5) {}
        virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    };

    class TargetFleeingTrigger : public Trigger {
    public:
        TargetFleeingTrigger(PlayerbotAI* ai) : Trigger(ai, "target fleeing", 5) {}
        virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    };

    class TargetStunnedTrigger : public Trigger {
    public:
        TargetStunnedTrigger(PlayerbotAI* ai) : Trigger(ai, "target stunned", 5) {}
        virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    };

    class TargetNotSnaredTrigger : public Trigger {
    public:
        TargetNotSnaredTrigger(PlayerbotAI* ai) : Trigger(ai, "target not snared", 5) {}
        virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    };

    class TargetNotRootedTrigger : public Trigger {
    public:
        TargetNotRootedTrigger(PlayerbotAI* ai) : Trigger(ai, "target not rooted", 5) {}
        virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    };

    class TargetNotFrozenTrigger : public Trigger {
    public:
        TargetNotFrozenTrigger(PlayerbotAI* ai) : Trigger(ai, "target not frozen", 5) {}
        virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    };

    class TargetNotStunnedTrigger : public Trigger {
    public:
        TargetNotStunnedTrigger(PlayerbotAI* ai) : Trigger(ai, "target not stunned", 5) {}
        virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    };

    class TargetNotBleedingTrigger : public Trigger {
    public:
        TargetNotBleedingTrigger(PlayerbotAI* ai) : Trigger(ai, "target not bleeding", 5) {}
        virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    };

    class TargetNotPolymorphedTrigger : public Trigger {
    public:
        TargetNotPolymorphedTrigger(PlayerbotAI* ai) : Trigger(ai, "target not polymorphed", 5) {}
        virtual string GetTargetName() { return "current target"; }
        virtual bool IsActive();
    };

    class PartyMemberRootedTrigger : public Trigger {
	public:
		PartyMemberRootedTrigger(PlayerbotAI* ai) : Trigger(ai, "party member rooted", 5) {}
        virtual Value<Unit*>* GetTargetValue();
		virtual bool IsActive();
	};

	class PartyMemberSnaredTrigger : public Trigger {
	public:
		PartyMemberSnaredTrigger(PlayerbotAI* ai) : Trigger(ai, "party member snared", 5) {}
        virtual Value<Unit*>* GetTargetValue();
		virtual bool IsActive();
	};

	class PartyMemberPolymorphedTrigger : public Trigger {
	public:
		PartyMemberPolymorphedTrigger(PlayerbotAI* ai) : Trigger(ai, "party member polymorphed", 5) {}
        virtual Value<Unit*>* GetTargetValue();
		virtual bool IsActive();
	};

	class PartyMemberFrozenTrigger : public Trigger {
	public:
		PartyMemberFrozenTrigger(PlayerbotAI* ai) : Trigger(ai, "party member frozen", 5) {}
        virtual Value<Unit*>* GetTargetValue();
		virtual bool IsActive();
	};

	class PartyMemberPossessedTrigger : public Trigger {
	public:
		PartyMemberPossessedTrigger(PlayerbotAI* ai) : Trigger(ai, "party member possessed", 5) {}
        virtual Value<Unit*>* GetTargetValue();
		virtual bool IsActive();
	};

	class PartyMemberCharmedTrigger : public Trigger {
	public:
		PartyMemberCharmedTrigger(PlayerbotAI* ai) : Trigger(ai, "party member charmed", 5) {}
        virtual Value<Unit*>* GetTargetValue();
		virtual bool IsActive();
	};

    class PartyMemberFearedTrigger : public Trigger {
	public:
		PartyMemberFearedTrigger(PlayerbotAI* ai) : Trigger(ai, "party member feared", 5) {}
        virtual Value<Unit*>* GetTargetValue();
		virtual bool IsActive();
	};

	class PlayerHasNoFlag : public Trigger
	{
	public:
		PlayerHasNoFlag(PlayerbotAI* ai) : Trigger(ai, "player has no flag") {}

	public:
		virtual bool IsActive();
	};

	class PlayerIsInBattleGround : public Trigger
	{
	public:
		PlayerIsInBattleGround(PlayerbotAI* ai) : Trigger(ai, "in BattleGround") {}

	public:
		virtual bool IsActive();
	};

	class PlayerIsInBattleGroundWithoutFlag : public Trigger
	{
	public:
		PlayerIsInBattleGroundWithoutFlag(PlayerbotAI* ai) : Trigger(ai, "in BattleGround without flag") {}

	public:
		virtual bool IsActive();
	};
}

class RandomBotUpdateTrigger : public RandomTrigger
{
	public:
		RandomBotUpdateTrigger(PlayerbotAI* ai) : RandomTrigger(ai, "random bot update", 30) {}
		
	public:
		virtual bool IsActive()
		{
			return RandomTrigger::IsActive() && AI_VALUE(bool, "random bot update");
			}
};

class NoNonBotPlayersAroundTrigger : public Trigger
{
	public:
		NoNonBotPlayersAroundTrigger(PlayerbotAI* ai) : Trigger(ai, "no non bot players around", 5) {}
		
			public:
				virtual bool IsActive()
				{
					return AI_VALUE(list<ObjectGuid>, "nearest non bot players").empty();
					}
};

#include "RangeTriggers.h"
#include "HealthTriggers.h"
#include "CureTriggers.h"