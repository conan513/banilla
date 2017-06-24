#include "../../../botpch.h"
#include "../../playerbot.h"
#include "FleeStrategy.h"

using namespace ai;

class FleeStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    FleeStrategyActionNodeFactory()
    {
        creators["flee"] = &flee;
    }
    ~FleeStrategyActionNodeFactory()
    {
        creators.erase("flee");
    }
private:
    static ActionNode* flee(PlayerbotAI* ai)
    {
        return new ActionNode ("flee",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("reposition"), NULL),
            /*C*/ NULL);
    }
};

FleeStrategy::FleeStrategy(PlayerbotAI* ai) : Strategy(ai)
{
    factoryInternal = new FleeStrategyActionNodeFactory();
    actionNodeFactories.Add(factoryInternal);
}

FleeStrategy::~FleeStrategy()
{
    actionNodeFactories.Remove(factoryInternal);
    delete factoryInternal;
}

void FleeStrategy::InitTriggers(list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "panic",
        NextAction::array(0, new NextAction("flee", ACTION_EMERGENCY + 9), NULL)));

    //triggers.push_back(new TriggerNode(
    //   "critical health",
    //   NextAction::array(0, new NextAction("flee", ACTION_MOVE + 9), NULL)));

   triggers.push_back(new TriggerNode(
       "almost no mana",
       NextAction::array(0,  new NextAction("flee", ACTION_MOVE + 9), NULL)));
       }

class FleeFromAddsStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    FleeFromAddsStrategyActionNodeFactory()
    {
        creators["flee"] = &flee;
    }
    ~FleeFromAddsStrategyActionNodeFactory()
    {
        creators.erase("flee");
    }
private:
    static ActionNode* flee(PlayerbotAI* ai)
    {
        return new ActionNode ("flee",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("reposition"), NULL),
            /*C*/ NULL);
    }
};

FleeFromAddsStrategy::FleeFromAddsStrategy(PlayerbotAI* ai) : Strategy(ai)
{
    factoryInternal = new FleeFromAddsStrategyActionNodeFactory();
    actionNodeFactories.Add(factoryInternal);
}

FleeFromAddsStrategy::~FleeFromAddsStrategy()
{
    actionNodeFactories.Remove(factoryInternal);
    delete factoryInternal;
}


void FleeFromAddsStrategy::InitTriggers(list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "has nearest adds",
        NextAction::array(0, new NextAction("flee", 50.0f), NULL)));
}
