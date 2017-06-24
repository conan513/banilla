#pragma once
#include "../triggers/GenericTriggers.h"

namespace ai
{

    class StealthTrigger : public BuffTrigger
	{
	public:
		StealthTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "stealth") {}
        virtual bool IsActive() { return BuffTrigger::IsActive() && !AI_VALUE2(bool, "combat", "self target"); }
    };

    BUFF_TRIGGER(RiposteTrigger, "riposte","riposte");
    BUFF_TRIGGER(SliceAndDiceTrigger, "slice and dice","slice and dice");

    class RuptureTrigger : public DebuffTrigger
	{
	public:
		RuptureTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "rupture") {}
		virtual bool IsActive() { return DebuffTrigger::IsActive() && ai->HasAura("slice and dice", bot);}
	};

    BUFF_TRIGGER(PremeditationTrigger, "premeditation","premeditation");
    DEBUFF_TRIGGER(HungerForBloodTrigger, "hunger for blood","hunger for blood");

    class KickInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        KickInterruptSpellTrigger(PlayerbotAI* ai) : InterruptSpellTrigger(ai, "kick") {}
    };

    class GougeInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        GougeInterruptSpellTrigger(PlayerbotAI* ai) : InterruptSpellTrigger(ai, "gauge") {}
    };

    class ExposeArmorTrigger : public DebuffTrigger
    {
    public:
        ExposeArmorTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "expose armor") {}
	virtual bool IsActive() { return DebuffTrigger::IsActive() && !ai->HasAura("sunder armor", bot) && (AI_VALUE2(bool, "target boss", "current target"));}
    };

    class GarroteTrigger : public OwnDebuffTrigger
    {
    public:
        GarroteTrigger(PlayerbotAI* ai) : OwnDebuffTrigger(ai, "garrote") {}
        virtual bool IsActive() { return OwnDebuffTrigger::IsActive() && ai->HasAura("stealth", bot);}
    };

    class AmbushTrigger : public IsBehindTargetTrigger
    {
    public:
        AmbushTrigger(PlayerbotAI* ai) : IsBehindTargetTrigger(ai) {}
        virtual bool IsActive()
        {
            Unit* target = AI_VALUE(Unit*, "current target");

			if (target && AI_VALUE2(float, "distance", "current target") <= sPlayerbotAIConfig.meleeDistance)
			{
			    if (target->UnderCc())
                    return false;
                else return IsBehindTargetTrigger::IsActive() && ai->HasAura("stealth", bot);
			}
            else return false;
        }
    };

    class KickInterruptEnemyHealerSpellTrigger : public InterruptEnemyHealerTrigger
    {
    public:
        KickInterruptEnemyHealerSpellTrigger(PlayerbotAI* ai) : InterruptEnemyHealerTrigger(ai, "kick") {}
    };

    class SapTrigger : public HasCcTarget4Trigger
    {
    public:
        SapTrigger(PlayerbotAI* ai) : HasCcTarget4Trigger(ai, "sap") {}
    };
}
