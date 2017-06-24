#include "../../../botpch.h"
#include "../../playerbot.h"
#include "PaladinMultipliers.h"
#include "TankPaladinStrategy.h"

using namespace ai;

class TankPaladinStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    TankPaladinStrategyActionNodeFactory()
    {
        creators["hammer of the righteous"] = &hammer_of_righteous;
    }
private:
    static ActionNode* hammer_of_righteous(PlayerbotAI* ai)
    {
        return new ActionNode ("hammer of the righteous",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
};

TankPaladinStrategy::TankPaladinStrategy(PlayerbotAI* ai) : GenericPaladinStrategy(ai)
{
    actionNodeFactories.Add(new TankPaladinStrategyActionNodeFactory());
}

NextAction** TankPaladinStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("melee", ACTION_NORMAL), NULL);
}

void TankPaladinStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericPaladinStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "judgement of light",
        NextAction::array(0, new NextAction("judgement of light", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "medium mana",
        NextAction::array(0, new NextAction("judgement of wisdom", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "righteous fury",
        NextAction::array(0, new NextAction("righteous fury", ACTION_HIGH + 8), NULL)));

	triggers.push_back(new TriggerNode(
		"holy shield",
		NextAction::array(0, new NextAction("holy shield", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "no aoe",
        NextAction::array(0, new NextAction("seal of vengeance", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "light aoe",
        NextAction::array(0,  new NextAction("avenger's shield", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe",
        NextAction::array(0, new NextAction("seal of command", ACTION_HIGH + 6), new NextAction("consecration", ACTION_HIGH + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "lose aggro",
        NextAction::array(0, new NextAction("hand of reckoning", ACTION_HIGH + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("divine plea", ACTION_HIGH + 5), NULL)));

	triggers.push_back(new TriggerNode(
		"holy shield",
		NextAction::array(0, new NextAction("holy shield", ACTION_HIGH + 7), NULL)));
}
