#pragma once

#include "../generic/NonCombatStrategy.h"

namespace ai
{
    class GenericDruidNonCombatStrategy : public NonCombatStrategy
    {
    public:
        GenericDruidNonCombatStrategy(PlayerbotAI* ai);
        virtual string getName() { return "nc"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

    class GenericDruidStealthStrategy : public NonCombatStrategy
    {
    public:
        GenericDruidStealthStrategy(PlayerbotAI* ai);
        virtual string getName() { return "stealth"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };
}
