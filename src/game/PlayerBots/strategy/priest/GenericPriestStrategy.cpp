#include "../../../botpch.h"
#include "../../playerbot.h"
#include "PriestMultipliers.h"
#include "HealPriestStrategy.h"
#include "GenericPriestStrategyActionNodeFactory.h"

using namespace ai;

GenericPriestStrategy::GenericPriestStrategy(PlayerbotAI* ai) : CombatStrategy(ai)
{
    actionNodeFactories.Add(new GenericPriestStrategyActionNodeFactory());
}

void GenericPriestStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy too close for spell",
        NextAction::array(0, new NextAction("flee", ACTION_MOVE + 8), NULL)));

        triggers.push_back(new TriggerNode(
        "takes periodic damage",
        NextAction::array(0, new NextAction("flee", ACTION_MOVE + 9), NULL)));

    triggers.push_back(new TriggerNode(
        "shadow word: pain on attacker",
        NextAction::array(0, new NextAction("shadow word: pain on attacker", 11.0f), NULL)));

       triggers.push_back(new TriggerNode(
        "enemy out of spell",
        NextAction::array(0, new NextAction("reach spell", ACTION_MOVE + 6), NULL)));

     triggers.push_back(new TriggerNode(
        "enemy too close for spell",
        NextAction::array(0, new NextAction("flee",ACTION_MOVE + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "shackle undead",
        NextAction::array(0, new NextAction("shackle undead",46.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "shackle undead on cc",
        NextAction::array(0, new NextAction("shackle undead",46.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost dead",
        NextAction::array(0, new NextAction("power word: shield on party", 50.0f),  new NextAction("flash heal on party", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("power word: shield", ACTION_CRITICAL_HEAL + 3) , NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("power word: shield on party", ACTION_CRITICAL_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "master low health",
        NextAction::array(0, new NextAction("power word: shield on party", ACTION_CRITICAL_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("shadowfiend", ACTION_EMERGENCY + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "almost dead",
        NextAction::array(0, new NextAction("desperate prayer", 50.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"critical aoe heal",
		NextAction::array(0, new NextAction("inner focus", ACTION_CRITICAL_HEAL + 4), new NextAction("divine hymn", ACTION_CRITICAL_HEAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "runaway",
        NextAction::array(0, new NextAction("psychic scream", ACTION_EMERGENCY + 7), new NextAction("renew", ACTION_EMERGENCY + 7), NULL)));
}

void PriestCureStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		"dispel magic",
		NextAction::array(0, new NextAction("dispel magic", 41.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"dispel magic on party",
		NextAction::array(0, new NextAction("dispel magic on party", 40.0f), NULL)));


	triggers.push_back(new TriggerNode(
		"cure disease",
		NextAction::array(0, new NextAction("abolish disease", 31.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"party member cure disease",
		NextAction::array(0, new NextAction("abolish disease on party", 30.0f), NULL)));
}