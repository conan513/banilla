#include "../../../botpch.h"
#include "../../playerbot.h"
#include "PriestMultipliers.h"
#include "ShadowPriestStrategy.h"
#include "ShadowPriestStrategyActionNodeFactory.h"

using namespace ai;

ShadowPriestStrategy::ShadowPriestStrategy(PlayerbotAI* ai) : GenericPriestStrategy(ai)
{
    actionNodeFactories.Add(new ShadowPriestStrategyActionNodeFactory());
}

NextAction** ShadowPriestStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("mind blast", 12.0f), new NextAction("mind flay", 10.0f), NULL);
}

void ShadowPriestStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericPriestStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of spell",
        NextAction::array(0, new NextAction("reach spell", ACTION_NORMAL + 9), NULL)));

    triggers.push_back(new TriggerNode(
        "shadowform",
        NextAction::array(0, new NextAction("shadowform", 15.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("dispersion", ACTION_EMERGENCY + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "almost dead",
        NextAction::array(0, new NextAction("dispersion", ACTION_EMERGENCY + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "vampiric embrace",
        NextAction::array(0, new NextAction("vampiric embrace", 16.0f), NULL)));

     triggers.push_back(new TriggerNode(
        "have aggro",
        NextAction::array(0, new NextAction("psychic scream", 49.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy too close for spell",
        NextAction::array(0, new NextAction("flee", 49.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "silence",
        NextAction::array(0, new NextAction("counterspell", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "silence on enemy healer",
        NextAction::array(0, new NextAction("silence on enemy healer", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
		"target almost dead",
		NextAction::array(0, new NextAction("power word: death", ACTION_HIGH + 8), NULL)));
}

void ShadowPriestDebuffStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "devouring plague",
        NextAction::array(0, new NextAction("devouring plague", 13.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "vampiric touch",
        NextAction::array(0, new NextAction("vampiric touch", 11.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "shadow word: pain",
        NextAction::array(0, new NextAction("shadow word: pain", 12.0f), NULL)));
}
