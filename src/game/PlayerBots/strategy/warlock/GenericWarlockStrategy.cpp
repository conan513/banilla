#include "../../../botpch.h"
#include "../../playerbot.h"
#include "WarlockMultipliers.h"
#include "GenericWarlockStrategy.h"

using namespace ai;

class GenericWarlockStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    GenericWarlockStrategyActionNodeFactory()
    {
        creators["banish"] = &banish;
        creators["soul shatter"] = &soul_shatter;
        creators["death coil"] = &death_coil;
        creators["healthstone"] = &healthstone;
    }
private:
    static ActionNode* banish(PlayerbotAI* ai)
    {
        return new ActionNode ("banish",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("fear"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* healthstone(PlayerbotAI* ai)
    {
        return new ActionNode ("healthstone",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("healing potion"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* soul_shatter(PlayerbotAI* ai)
    {
        return new ActionNode ("soul shatter",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("death coil"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* death_coil(PlayerbotAI* ai)
    {
        return new ActionNode ("death coil",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("howl of terror"), NULL),
            /*C*/ NextAction::array(0, new NextAction("fear"), NULL));
    }
};

GenericWarlockStrategy::GenericWarlockStrategy(PlayerbotAI* ai) : CombatStrategy(ai)
{
    actionNodeFactories.Add(new GenericWarlockStrategyActionNodeFactory());
}

NextAction** GenericWarlockStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("shadow bolt", 10.0f), NULL);
}

void GenericWarlockStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

    //triggers.push_back(new TriggerNode(
    //    "curse of agony",
    //    NextAction::array(0, new NextAction("curse of agony", 11.0f), NULL)));

   triggers.push_back(new TriggerNode(
        "enemy too close for spell",
        NextAction::array(0, new NextAction("flee", ACTION_MOVE + 8), NULL)));

      triggers.push_back(new TriggerNode(
        "takes periodic damage",
        NextAction::array(0, new NextAction("flee", ACTION_MOVE + 9), NULL)));

     triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("fel domination", ACTION_EMERGENCY), NULL)));

     triggers.push_back(new TriggerNode(
        "enemy out of spell",
        NextAction::array(0, new NextAction("reach spell", ACTION_MOVE + 7), NULL)));

     triggers.push_back(new TriggerNode(
        "not facing target",
        NextAction::array(0, new NextAction("set facing", ACTION_MOVE + 6), NULL)));

     triggers.push_back(new TriggerNode(
        "medium threat",
        NextAction::array(0, new NextAction("soul shatter", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("healthstone", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium mana",
        NextAction::array(0, new NextAction("life tap", ACTION_NORMAL + 2), NULL)));

      triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("life tap", ACTION_NORMAL + 3), NULL)));

	triggers.push_back(new TriggerNode(
		"target almost dead",
		NextAction::array(0, new NextAction("drain soul", 30.0f), NULL)));

     triggers.push_back(new TriggerNode(
        "target fleeing",
        NextAction::array(0, new NextAction("curse of exhaustion", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "banish",
        NextAction::array(0, new NextAction("banish", 21.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "fear",
        NextAction::array(0, new NextAction("fear on cc", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "almost dead",
        NextAction::array(0, new NextAction("bandage", ACTION_EMERGENCY), NULL)));

}
