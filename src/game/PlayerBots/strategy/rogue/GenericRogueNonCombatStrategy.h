#pragma once

#include "../generic/NonCombatStrategy.h"

namespace ai
{
    class GenericRogueNonCombatStrategy : public NonCombatStrategy
    {
    public:
        GenericRogueNonCombatStrategy(PlayerbotAI* ai);
        virtual string getName() { return "nc"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

    class GenericRogueNonCombatStealthStrategy : public NonCombatStrategy
    {
    public:
        GenericRogueNonCombatStealthStrategy(PlayerbotAI* ai);
        virtual string getName() { return "stealth"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };
}
