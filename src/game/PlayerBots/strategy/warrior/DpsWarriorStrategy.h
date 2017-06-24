#pragma once

#include "GenericWarriorStrategy.h"

namespace ai
{
    class DpsWarriorStrategy : public GenericWarriorStrategy
    {
    public:
        DpsWarriorStrategy(PlayerbotAI* ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "dps"; }
        virtual NextAction** getDefaultActions();
        virtual int GetType() { return STRATEGY_TYPE_COMBAT | STRATEGY_TYPE_DPS | STRATEGY_TYPE_MELEE; }
    };

    class DpsArmsWarriorStrategy : public GenericWarriorStrategy
    {
    public:
        DpsArmsWarriorStrategy(PlayerbotAI* ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "arms"; }
        virtual NextAction** getDefaultActions();
        virtual int GetType() { return STRATEGY_TYPE_COMBAT | STRATEGY_TYPE_DPS | STRATEGY_TYPE_MELEE; }
    };

    class DpsFuryWarriorStrategy : public GenericWarriorStrategy
    {
    public:
        DpsFuryWarriorStrategy(PlayerbotAI* ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "fury"; }
        virtual NextAction** getDefaultActions();
        virtual int GetType() { return STRATEGY_TYPE_COMBAT | STRATEGY_TYPE_DPS | STRATEGY_TYPE_MELEE; }
    };

    class DpsWarriorAoeStrategy : public CombatStrategy
    {
    public:
        DpsWarriorAoeStrategy(PlayerbotAI* ai) : CombatStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual NextAction** getDefaultActions();
        virtual string getName() { return "aoe"; }
    };
}
