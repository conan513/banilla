#pragma once

#include "../Action.h"
#include "MovementActions.h"
#include "../../PlayerbotAIConfig.h"

namespace ai
{
    class ReachTargetAction : public MovementAction
    {
    public:
        ReachTargetAction(PlayerbotAI* ai, string name, float distance) : MovementAction(ai, name)
		{
            this->distance = distance;
        }
        virtual bool Execute(Event event)
		{
		    if (distance <= sPlayerbotAIConfig.meleeDistance)
                return MoveToUnit(AI_VALUE(Unit*, "current target"));
            else
                return MoveTo(AI_VALUE(Unit*, "current target"), distance);
        }
        virtual bool IsInstant() {return false;}

        virtual bool isUseful()
		{
            Unit* target = AI_VALUE(Unit*, "current target");

            if (!target)
                return false;

           if (!ai)
               return false;

            bot->GetPlayerbotAI()->LogAction("Decide to attack");

            if (target && target->IsFriendlyTo(bot))
                return AI_VALUE2(float, "distance", "current target") > distance;

            list<ObjectGuid> targets = AI_VALUE(list<ObjectGuid>, "possible targets");
            list<ObjectGuid> attackers = AI_VALUE(list<ObjectGuid>, "attackers");

            if (targets.size() == attackers.size() || ai->IsTank(bot))
	    {
                ai->LogAction("Attack:%s", target->GetName());
                return AI_VALUE2(float, "distance", "current target") > (distance + sPlayerbotAIConfig.contactDistance);
            }
            else
            {
                for (list<ObjectGuid>::iterator i = targets.begin(); i != targets.end(); ++i)
                {
                    Unit* unit = ai->GetUnit(*i);
                    if (!unit)
                        continue;

                    if (target && unit->GetGUID() == target->GetGUID())
                        continue;

                    if (unit->isInCombat())
                        continue;

                    float d = unit->GetDistance(target);
                    if (d <= sPlayerbotAIConfig.aggroDistance)
                    {
                       ai->LogAction("No attack");
                        return false;
                         }
                }
                ai->LogAction("Attack:%s", target->GetName());
                return AI_VALUE2(float, "distance", "current target") > (distance + sPlayerbotAIConfig.contactDistance);
            }


        }
        virtual string GetTargetName() { return "current target"; }

    protected:
        float distance;
    };

    class CastReachTargetSpellAction : public CastSpellAction
    {
    public:
        CastReachTargetSpellAction(PlayerbotAI* ai, string spell, float distance) : CastSpellAction(ai, spell)
		{
            this->distance = distance;
        }
		virtual bool isUseful()
		{
			return AI_VALUE2(float, "distance", "current target") > (distance + sPlayerbotAIConfig.contactDistance);
		}

    protected:
        float distance;
    };

    class ReachMeleeAction : public ReachTargetAction
	{
    public:
        ReachMeleeAction(PlayerbotAI* ai) : ReachTargetAction(ai, "reach melee", sPlayerbotAIConfig.meleeDistance) {}
    };

    class ReachSpellAction : public ReachTargetAction
	{
    public:
        ReachSpellAction(PlayerbotAI* ai, float distance = sPlayerbotAIConfig.spellDistance) : ReachTargetAction(ai, "reach spell", distance) {}
    };
}
