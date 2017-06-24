#pragma once

//#include "FeralDruidStrategy.h"
#include "../generic/CombatStrategy.h"
#include "../generic/MeleeCombatStrategy.h"

namespace ai
{
    class CatDpsDruidStrategy : public MeleeCombatStrategy
    {
    public:
        CatDpsDruidStrategy(PlayerbotAI* ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "cat"; }
        virtual NextAction** getDefaultActions();
        virtual int GetType() { return STRATEGY_TYPE_COMBAT | STRATEGY_TYPE_MELEE; }
    };
}
