#pragma once

#include "GenericPaladinStrategy.h"
#include "../generic/RangedCombatStrategy.h"

namespace ai
{
    class HealPaladinStrategy : public RangedCombatStrategy
    {
    public:
        HealPaladinStrategy(PlayerbotAI* ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "heal"; }
        virtual NextAction** getDefaultActions();
        virtual int GetType() { return STRATEGY_TYPE_HEAL; }
    };


    class MeleeHealPaladinStrategy : public GenericPaladinStrategy
    {
    public:
        MeleeHealPaladinStrategy(PlayerbotAI* ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "melee heal"; }
        virtual NextAction** getDefaultActions();
        virtual int GetType() { return STRATEGY_TYPE_HEAL; }
    };
}
