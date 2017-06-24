#pragma once

#include "../triggers/GenericTriggers.h"

namespace ai
{
    BEGIN_TRIGGER(HunterNoStingsActiveTrigger, Trigger)
    END_TRIGGER()

    BUFF_ON_PARTY_TRIGGER(MisdirectionOnPartyTrigger, "misdirection", "misdirection on party")

    class HunterAspectOfTheHawkTrigger : public BuffTrigger
    {
    public:
        HunterAspectOfTheHawkTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "aspect of the hawk") {
			checkInterval = 1;
		}
		virtual bool IsActive();
    };

    class HunterAspectOfTheDragonHawkTrigger : public BuffTrigger
    {
    public:
        HunterAspectOfTheDragonHawkTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "aspect of the dragonhawk") {
			checkInterval = 1;
        }
        virtual bool IsActive();
    };

	class HunterAspectOfTheWildTrigger : public BuffTrigger
	{
	public:
		HunterAspectOfTheWildTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "aspect of the wild") {
			checkInterval = 1;
		}
	};

    class HunterAspectOfTheViperTrigger : public BuffTrigger
    {
    public:
        HunterAspectOfTheViperTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "aspect of the viper") {}
        virtual bool IsActive()
        {
            return BuffTrigger::IsActive() &&  (AI_VALUE2(uint8, "mana", "self target") <= sPlayerbotAIConfig.lowMana);
        }
    };

    class HunterAspectOfThePackTrigger : public BuffTrigger
    {
    public:
        HunterAspectOfThePackTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "aspect of the pack") {}
        virtual bool IsActive() {
			return (BuffTrigger::IsActive() && bot->GetGroup() && !AI_VALUE2(bool, "mounted", "self target"));
        };
    };

    BEGIN_TRIGGER(HuntersPetDeadTrigger, Trigger)
    END_TRIGGER()

    BEGIN_TRIGGER(HuntersPetLowHealthTrigger, Trigger)
    END_TRIGGER()

    DEBUFF_TRIGGER(BlackArrowTrigger, "black arrow", "black arrow")
    DEBUFF_TRIGGER(HuntersMarkTrigger, "hunter's mark", "hunter's mark")

    class ConcussiveShotSnareTrigger : public SnareTargetTrigger {
    public:
        ConcussiveShotSnareTrigger(PlayerbotAI* ai) : SnareTargetTrigger(ai, "concussive shot snare") {}
    };

    class FreezingTrapTrigger : public HasCcTargetTrigger
    {
    public:
        FreezingTrapTrigger(PlayerbotAI* ai) : HasCcTargetTrigger(ai, "freezing trap") {}
    };

    class RapidFireTrigger : public BoostTrigger
    {
    public:
        RapidFireTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "rapid fire") {}
    };

    class KillCommandTrigger : public BoostTrigger
    {
    public:
        KillCommandTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "kill command") {}
    };

    class KillShotTrigger : public BoostTrigger
    {
    public:
        KillShotTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "kill shot") {}
    };

    class CounterstrikeTrigger : public BuffTrigger
    {
    public:
        CounterstrikeTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "counterstrike") {}
    };

    class TrueshotAuraTrigger : public BuffTrigger
    {
    public:
        TrueshotAuraTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "trueshot aura") {}

        bool IsActive()
        {
            return (BuffTrigger::IsActive() && bot->getLevel() > 39);
            };
    };

    class SerpentStingOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        SerpentStingOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "serpent sting") {}
    };

    class ArcaneShotOnAttackerTrigger : public TargetAuraDispelTrigger
    {
    public:
        ArcaneShotOnAttackerTrigger(PlayerbotAI* ai) : TargetAuraDispelTrigger(ai, "arcane shot", DISPEL_MAGIC) {}
    };

    class SilencingShotInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        SilencingShotInterruptSpellTrigger(PlayerbotAI* ai) : InterruptSpellTrigger(ai, "silencing shot") {}
    };

    class SilencingShotEnemyHealerTrigger : public InterruptEnemyHealerTrigger
    {
    public:
        SilencingShotEnemyHealerTrigger(PlayerbotAI* ai) : InterruptEnemyHealerTrigger(ai, "silencing shot") {}
    };

    class WyvernStingTrigger : public HasCcTarget4Trigger
    {
    public:
        WyvernStingTrigger(PlayerbotAI* ai) : HasCcTarget4Trigger(ai, "wyvern sting") {}
    };
}
