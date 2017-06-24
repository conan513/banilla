#include "../../../botpch.h"
#include "../../playerbot.h"
#include "DruidMultipliers.h"
#include "GenericDruidNonCombatStrategy.h"

using namespace ai;

class GenericDruidNonCombatStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    GenericDruidNonCombatStrategyActionNodeFactory()
    {
        creators["mark of the wild"] = &mark_of_the_wild;
        creators["mark of the wild on party"] = &mark_of_the_wild_on_party;
        creators["innervate"] = &innervate;
        creators["regrowth"] = &regrowth;
        creators["regrowth on party"] = &regrowth_on_party;
        creators["regrowth on master"] = &regrowth_on_master;
        creators["rejuvenation"] = &rejuvenation;
        creators["rejuvenation on party"] = &rejuvenation_on_party;
        creators["rejuvenation on master"] = &rejuvenation_on_master;
    }
private:
    static ActionNode* mark_of_the_wild(PlayerbotAI* ai)
    {
        return new ActionNode ("mark of the wild",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* mark_of_the_wild_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("mark of the wild on party",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* innervate(PlayerbotAI* ai)
    {
        return new ActionNode ("innervate",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("drink"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* regrowth(PlayerbotAI* ai)
    {
        return new ActionNode ("regrowth",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("rejuvenation"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* regrowth_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("regrowth on party",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("rejuvenation on party"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* regrowth_on_master(PlayerbotAI* ai)
    {
        return new ActionNode ("regrowth on master",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("rejuvenation on master"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* rejuvenation(PlayerbotAI* ai)
    {
        return new ActionNode ("rejuvenation",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* rejuvenation_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("rejuvenation on party",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* rejuvenation_on_master(PlayerbotAI* ai)
    {
        return new ActionNode ("rejuvenation on master",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
};

GenericDruidNonCombatStrategy::GenericDruidNonCombatStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai)
{
    actionNodeFactories.Add(new GenericDruidNonCombatStrategyActionNodeFactory());
}

void GenericDruidNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "mark of the wild",
        NextAction::array(0, new NextAction("mark of the wild", 12.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "mark of the wild on party",
        NextAction::array(0, new NextAction("mark of the wild on party", 11.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "thorns on party",
        NextAction::array(0, new NextAction("thorns on party", 13.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "cure poison",
        NextAction::array(0, new NextAction("abolish poison", 21.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure poison",
        NextAction::array(0, new NextAction("abolish poison on party", 20.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"party member dead",
		NextAction::array(0, new NextAction("revive", 22.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0,  new NextAction("rejuvenation", ACTION_LIGHT_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0,  new NextAction("rejuvenation on party", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0,  new NextAction("regrowth on party", ACTION_LIGHT_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0,  new NextAction("regrowth", ACTION_LIGHT_HEAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("drink", ACTION_EMERGENCY + 5), NULL)));
}

class GenericDruidStealthStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    GenericDruidStealthStrategyActionNodeFactory()
    {
        creators["prowl"] = &prowl;
            }
private:
    static ActionNode* prowl(PlayerbotAI* ai)
    {
        return new ActionNode ("prowl",
            /*P*/ NextAction::array(0, new NextAction("cat form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
};

GenericDruidStealthStrategy::GenericDruidStealthStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai)
{
    actionNodeFactories.Add(new GenericDruidStealthStrategyActionNodeFactory());
}

void GenericDruidStealthStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "prowl",
        NextAction::array(0, new NextAction("prowl", 12.0f), NULL)));
}
