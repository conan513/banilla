#pragma once

#include "HealPriestStrategy.h"

namespace ai
{
    class ShadowPriestStrategy : public GenericPriestStrategy
    {
    public:
        ShadowPriestStrategy(PlayerbotAI* ai);

    public:
        virtual NextAction** getDefaultActions();
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "shadow"; }
        virtual int GetType() { return STRATEGY_TYPE_DPS|STRATEGY_TYPE_RANGED; }
    };

    class ShadowPriestDebuffStrategy : public CombatStrategy
    {
    public:
        ShadowPriestDebuffStrategy(PlayerbotAI* ai) : CombatStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "shadow debuff"; }
    };
}
