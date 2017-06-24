#pragma once

#include "GenericDruidStrategy.h"
#include "DruidAiObjectContext.h"

namespace ai
{
    class ShapeshiftDruidStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
    {
    public:
        ShapeshiftDruidStrategyActionNodeFactory()
        {
        creators["thorns"] = &thorns;
        creators["cure poison"] = &cure_poison;
        creators["cure poison on party"] = &cure_poison_on_party;
        creators["abolish poison"] = &abolish_poison;
        creators["abolish poison on party"] = &abolish_poison_on_party;
        }

    private:

    static ActionNode* thorns(PlayerbotAI* ai)
    {
        return new ActionNode ("thorns",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* cure_poison(PlayerbotAI* ai)
    {
        return new ActionNode ("cure poison",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* cure_poison_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("cure poison on party",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* abolish_poison(PlayerbotAI* ai)
    {
        return new ActionNode ("abolish poison",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* abolish_poison_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("abolish poison on party",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    };

    class FeralDruidStrategy : public GenericDruidStrategy
    {
    protected:
        FeralDruidStrategy(PlayerbotAI* ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual int GetType() { return STRATEGY_TYPE_COMBAT | STRATEGY_TYPE_MELEE; }
    };

}
