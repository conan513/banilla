#include "../../../botpch.h"
#include "../../playerbot.h"
#include "RogueTriggers.h"
#include "RogueMultipliers.h"
#include "GenericRogueNonCombatStrategy.h"
#include "RogueActions.h"

using namespace ai;


class GenericRogueNonCombatStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    GenericRogueNonCombatStrategyActionNodeFactory()
    {
        creators["sprint"] = &sprint;
        creators["deadly poison offhand"] = &deadly_poison;
    }
private:
    static ActionNode* sprint(PlayerbotAI* ai)
    {
        return new ActionNode ("sprint",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* deadly_poison(PlayerbotAI* ai)
    {
        return new ActionNode ("deadly poison offhand",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("instant poison offhand"), NULL),
            /*C*/ NULL);
    }
};

GenericRogueNonCombatStrategy::GenericRogueNonCombatStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai)
{
    actionNodeFactories.Add(new GenericRogueNonCombatStrategyActionNodeFactory());
}

void GenericRogueNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "mainhand not enhanced",
        NextAction::array(0, new NextAction("instant poison mainhand", 21.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "offhand not enhanced",
        NextAction::array(0, new NextAction("deadly poison offhand", 21.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "runaway",
        NextAction::array(0, new NextAction("sprint", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("bandage", 20.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"in battleground without flag",
		NextAction::array(0, new NextAction("stealth", 1.0f), NULL)));
}

class GenericRogueNonCombatStealthStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    GenericRogueNonCombatStealthStrategyActionNodeFactory()
    {
        creators["stealth"] = &stealth;
        creators["wound poison offhand"] = &wound_poison;
        creators["garrote"] = &garrote;
        creators["ambush"] = &ambush;
        creators["cheap shot"] = &cheap_shot;
    }
private:
    static ActionNode* stealth(PlayerbotAI* ai)
    {
        return new ActionNode ("stealth",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* wound_poison(PlayerbotAI* ai)
    {
        return new ActionNode ("wound poison offhand",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("instant poison offhand"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* garrote(PlayerbotAI* ai)
    {
        return new ActionNode ("garrote",
            /*P*/ NextAction::array(0, new NextAction("stealth"), NULL),
            /*A*/ NextAction::array(0, new NextAction("ambush"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* ambush(PlayerbotAI* ai)
    {
        return new ActionNode ("ambush",
            /*P*/ NextAction::array(0, new NextAction("stealth"), NULL),
            /*A*/ NextAction::array(0, new NextAction("cheap shot"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* cheap_shot(PlayerbotAI* ai)
    {
        return new ActionNode ("cheap shot",
            /*P*/ NextAction::array(0, new NextAction("stealth"), NULL),
            /*A*/ NextAction::array(0, new NextAction("garrote sword"), NULL),
            /*C*/ NULL);
    }
};

GenericRogueNonCombatStealthStrategy::GenericRogueNonCombatStealthStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai)
{
    actionNodeFactories.Add(new GenericRogueNonCombatStealthStrategyActionNodeFactory());
}

void GenericRogueNonCombatStealthStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "stealth",
        NextAction::array(0, new NextAction("stealth", 21.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "mainhand not enhanced",
        NextAction::array(0, new NextAction("instant poison mainhand", 21.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "offhand not enhanced",
        NextAction::array(0, new NextAction("wound poison offhand", 21.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "garrote",
        NextAction::array(0, new NextAction("garrote", ACTION_EMERGENCY + 8), NULL)));

}

