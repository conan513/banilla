#include "../../../botpch.h"
#include "../../playerbot.h"
#include "UseFoodStrategy.h"

using namespace ai;

class UseFoodStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    UseFoodStrategyActionNodeFactory()
    {
        creators["food"] = &food;
    }

private:
    static ActionNode* food(PlayerbotAI* ai)
    {
        return new ActionNode ("food",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("bandage"), NULL),
            /*C*/ NULL);
    }
};

UseFoodStrategy::UseFoodStrategy(PlayerbotAI* ai) : Strategy(ai)
{
    actionNodeFactories.Add(new UseFoodStrategyActionNodeFactory());
}

void UseFoodStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    Strategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("food", 2.0f), NULL)));

   triggers.push_back(new TriggerNode(
        "almost dead",
        NextAction::array(0, new NextAction("bandage", 12.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "drink mana",
        NextAction::array(0, new NextAction("drink", 2.0f), NULL)));
}
