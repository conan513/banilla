#include "../../../botpch.h"
#include "../../playerbot.h"
#include "PaladinMultipliers.h"
#include "DpsPaladinStrategy.h"

using namespace ai;

class DpsPaladinStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    DpsPaladinStrategyActionNodeFactory()
    {
        creators["crusader strike"] = &crusader_strike;
        creators["instant flash of light on master"] = &instant_exorcism;
        creators["instant exorcism"] = &instant_flash_of_light;
    }

private:   
    static ActionNode* crusader_strike(PlayerbotAI* ai)
    {
        return new ActionNode ("crusader strike",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* instant_exorcism(PlayerbotAI* ai)
    {
        return new ActionNode ("instant exorcism",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("instant flash of light on master"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* instant_flash_of_light(PlayerbotAI* ai)
    {
        return new ActionNode ("instant flash of light on master",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("instant flash of light on party"), NULL),
            /*C*/ NULL);
    }
};

DpsPaladinStrategy::DpsPaladinStrategy(PlayerbotAI* ai) : GenericPaladinStrategy(ai)
{
    actionNodeFactories.Add(new DpsPaladinStrategyActionNodeFactory());
}

NextAction** DpsPaladinStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("instant exorcism", ACTION_NORMAL + 2), new NextAction("crusader strike", ACTION_NORMAL + 1), NULL);
}

void DpsPaladinStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericPaladinStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("move behind", ACTION_MOVE + 9), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("instant flash of light on party", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "master medium health",
        NextAction::array(0, new NextAction("instant flash of light on master", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("instant flash of light", ACTION_MEDIUM_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("instant flash of light", ACTION_MEDIUM_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "judgement of wisdom",
        NextAction::array(0, new NextAction("judgement of wisdom", ACTION_NORMAL + 2), NULL)));
    
	triggers.push_back(new TriggerNode(
		"melee medium aoe",
		NextAction::array(0, new NextAction("seal of command", ACTION_HIGH + 2), new NextAction("divine storm", ACTION_HIGH + 1), new NextAction("consecration", ACTION_HIGH + 1), NULL)));

	triggers.push_back(new TriggerNode(
		"art of war",
		NextAction::array(0, new NextAction("exorcism", ACTION_HIGH + 2), NULL)));

     triggers.push_back(new TriggerNode(
        "not facing target",
        NextAction::array(0, new NextAction("set facing", ACTION_MOVE + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "medium threat",
        NextAction::array(0, new NextAction("hand of salvation", ACTION_HIGH + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "no melee aoe",
        NextAction::array(0, new NextAction("seal of vengeance", ACTION_HIGH + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "light melee aoe",
        NextAction::array(0, new NextAction("seal of command", ACTION_HIGH + 6), new NextAction("divine storm", ACTION_HIGH + 5), NULL)));
}
