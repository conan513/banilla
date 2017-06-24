#include "../../../botpch.h"
#include "../../playerbot.h"
#include "FeralDruidStrategy.h"

using namespace ai;

class FeralDruidStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    FeralDruidStrategyActionNodeFactory()
    {
        creators["survival instincts"] = &survival_instincts;
    }
private:
    static ActionNode* survival_instincts(PlayerbotAI* ai)
    {
        return new ActionNode ("survival instincts",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("barskin"), NULL),
            /*C*/ NULL);
    }

};

FeralDruidStrategy::FeralDruidStrategy(PlayerbotAI* ai) : GenericDruidStrategy(ai)
{
    actionNodeFactories.Add(new FeralDruidStrategyActionNodeFactory());
    actionNodeFactories.Add(new ShapeshiftDruidStrategyActionNodeFactory());
}

void FeralDruidStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericDruidStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "not facing target",
        NextAction::array(0, new NextAction("set facing", ACTION_MOVE + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("reach melee", ACTION_MOVE + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy too close for melee",
        NextAction::array(0, new NextAction("move out of enemy contact", ACTION_MOVE + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("survival instincts", ACTION_EMERGENCY + 1), NULL)));
}

