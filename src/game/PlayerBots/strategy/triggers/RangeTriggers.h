#pragma once
#include "../Trigger.h"
#include "../../PlayerbotAIConfig.h"

namespace ai
{
    class TargetOutOfLOSSpellTrigger : public Trigger {
    public:
        TargetOutOfLOSSpellTrigger(PlayerbotAI* ai) : Trigger(ai, "target out of los") {}
        virtual bool IsActive()
		{
			Unit* target = AI_VALUE(Unit*, "current target");

			if (target && bot->IsWithinLOSInMap(target))
			{
			     return true;
			}
            else return false;
        }
    };

    class EnemyTooCloseForSpellTrigger : public Trigger {
    public:
        EnemyTooCloseForSpellTrigger(PlayerbotAI* ai) : Trigger(ai, "enemy too close for spell") {}
        virtual bool IsActive()
		{
			Unit* target = AI_VALUE(Unit*, "current target");

			if (target && AI_VALUE2(float, "distance", "current target") <= sPlayerbotAIConfig.tooCloseDistance)
			{
			    if (bot->getClass() == CLASS_HUNTER)
                    return true;

				if (AI_VALUE2(bool, "target normal", "current target") && (AI_VALUE(uint8, "melee attacker count") < 2) && (AI_VALUE2(uint8, "health", "self target") > sPlayerbotAIConfig.mediumHealth))
                    return false;
				else if (target->UnderCc())
                    return false;
                else return true;
			}
            else return false;
        }
    };

    class EnemyInMeleeRangeTrigger : public Trigger {
    public:
        EnemyInMeleeRangeTrigger(PlayerbotAI* ai) : Trigger(ai, "enemy in melee range") {}
        virtual bool IsActive()
		{
			Unit* target = AI_VALUE(Unit*, "current target");

			if (target && AI_VALUE2(float, "distance", "current target") <= sPlayerbotAIConfig.meleeDistance)
			{
			    if (target->UnderCc())
                    return false;
                else return true;
			}
            else return false;
        }
    };

	class EnemyTooCloseForShootTrigger : public Trigger {
		public:
			EnemyTooCloseForShootTrigger(PlayerbotAI* ai) : Trigger(ai, "enemy too close for shoot") {}
			virtual bool IsActive()
				{
				Unit* target = AI_VALUE(Unit*, "current target");
				return target && AI_VALUE2(float, "distance", "current target") <= sPlayerbotAIConfig.shootDistance;
				}
			
	};

	class EnemyIsCloseTrigger : public Trigger {
	public:
		EnemyIsCloseTrigger(PlayerbotAI* ai) : Trigger(ai, "enemy is close") {}
		virtual bool IsActive()
		{
			Unit* target = AI_VALUE(Unit*, "current target");
			return target && AI_VALUE2(float, "distance", "current target") <= sPlayerbotAIConfig.tooCloseDistance;
		}
	};

    class EnemyTooCloseForMeleeTrigger : public Trigger {
    public:
        EnemyTooCloseForMeleeTrigger(PlayerbotAI* ai) : Trigger(ai, "enemy too close for melee", 5) {}
        virtual bool IsActive()
		{
			Unit* target = AI_VALUE(Unit*, "current target");
            return target && AI_VALUE2(float, "distance", "current target") <= sPlayerbotAIConfig.contactDistance / 2;
        }
    };

    class OutOfRangeTrigger : public Trigger {
    public:
        OutOfRangeTrigger(PlayerbotAI* ai, string name, float distance) : Trigger(ai, name)
		{
            this->distance = distance;
        }
        virtual bool IsActive()
		{
			Unit* target = AI_VALUE(Unit*, GetTargetName());

			if (target && !bot->IsWithinLOSInMap(target))
			{
			     return true;
			}

			return target && AI_VALUE2(float, "distance", GetTargetName()) > distance;
        }
        virtual string GetTargetName() { return "current target"; }

    protected:
        float distance;
    };

    class EnemyOutOfMeleeTrigger : public OutOfRangeTrigger
	{
    public:
        EnemyOutOfMeleeTrigger(PlayerbotAI* ai) : OutOfRangeTrigger(ai, "enemy out of melee range", sPlayerbotAIConfig.meleeDistance) {}
    };

    class EnemyOutOfSpellRangeTrigger : public OutOfRangeTrigger
	{
    public:
        EnemyOutOfSpellRangeTrigger(PlayerbotAI* ai) : OutOfRangeTrigger(ai, "enemy out of spell range", sPlayerbotAIConfig.spellDistance) {}
    };

    class PartyMemberToHealOutOfSpellRangeTrigger : public OutOfRangeTrigger
	{
    public:
        PartyMemberToHealOutOfSpellRangeTrigger(PlayerbotAI* ai) : OutOfRangeTrigger(ai, "party member to heal out of spell range", sPlayerbotAIConfig.spellDistance) {}
        virtual string GetTargetName() { return "party member to heal"; }
    };

    class FarFromMasterTrigger : public Trigger {
    public:
        FarFromMasterTrigger(PlayerbotAI* ai, string name = "far from master", float distance = 12.0f, int checkInterval = 1) : Trigger(ai, name, checkInterval), distance(distance) {}

        virtual bool IsActive()
        {
            return AI_VALUE2(float, "distance", "master target") > distance;
        }

    private:
        float distance;
    };
	/*
    class OutOfReactRangeTrigger : public FarFromMasterTrigger
    {
    public:
        OutOfReactRangeTrigger(PlayerbotAI* ai) : FarFromMasterTrigger(ai, "out of react range", sPlayerbotAIConfig.reactDistance / 2, 10) {}
    };
	*/
}
