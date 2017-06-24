#include "../../../botpch.h"
#include "../../playerbot.h"
#include "DruidMultipliers.h"
#include "HealDruidStrategy.h"

using namespace ai;

class HealDruidStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    HealDruidStrategyActionNodeFactory()
    {
        creators["swiftmend"] = &swiftmend;
        creators["swiftmend on party"] = &swiftmend_on_party;
        creators["swiftmend on master"] = &swiftmend_on_master;
        creators["regrowth"] = &regrowth;
        creators["regrowth on party"] = &regrowth_on_party;
        creators["regrowth on master"] = &regrowth_on_master;
        creators["rejuvenation"] = &rejuvenation;
        creators["rejuvenation on party"] = &rejuvenation_on_party;
        creators["rejuvenation on master"] = &rejuvenation_on_master;
        creators["nourish"] = &nourish;
        creators["nourish on party"] = &nourish_on_party;
        creators["nourish on master"] = &nourish_on_master;
        creators["wild growth on master"] = &wild_growth_on_master;
        creators["swiftmend"] = &swiftmend;
        creators["swiftmend on party"] = &swiftmend_on_party;
        creators["swiftmend on master"] = &swiftmend_on_master;
        creators["moonfire heal"] = &moonfire_heal;
        creators["tree form"] = &tree_form;
        creators["healing touch on party"] = &healing_touch_on_party;
        creators["healing on master"] = &healing_touch_on_master;
        creators["wrath heal"] = &wrath_heal;
        creators["nature's grasp"] =natures_grasp;
        creators["nature's swiftness"] = &nature_swiftness;
        creators["nature's swiftness on party"] = &nature_swiftness_on_party;
        creators["nature's swiftness on master"] = &nature_swiftness_on_master;
    }
private:
    static ActionNode* swiftmend(PlayerbotAI* ai)
    {
        return new ActionNode ("swiftmend",
            /*P*/ NextAction::array(0, new NextAction("tree form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("nature's swiftness"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* swiftmend_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("swiftmend on party",
            /*P*/ NextAction::array(0, new NextAction("tree form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("nature's swiftness"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* swiftmend_on_master(PlayerbotAI* ai)
    {
        return new ActionNode ("swiftmend on master",
            /*P*/ NextAction::array(0, new NextAction("tree form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("nature's swiftness"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* regrowth(PlayerbotAI* ai)
    {
        return new ActionNode ("regrowth",
            /*P*/ NextAction::array(0, new NextAction("tree form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("nourish"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* regrowth_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("regrowth on party",
            /*P*/ NextAction::array(0, new NextAction("tree form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("nourish on party"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* regrowth_on_master(PlayerbotAI* ai)
    {
        return new ActionNode ("regrowth on master",
            /*P*/ NextAction::array(0, new NextAction("tree form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("nourish on master"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* nourish(PlayerbotAI* ai)
    {
        return new ActionNode ("nourish",
            /*P*/ NextAction::array(0, new NextAction("tree form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("healing touch"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* nourish_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("nourish on party",
            /*P*/ NextAction::array(0, new NextAction("tree form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("healing touch on party"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* nourish_on_master(PlayerbotAI* ai)
    {
        return new ActionNode ("nourish on master",
            /*P*/ NextAction::array(0, new NextAction("tree form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("healing touch on master"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* rejuvenation(PlayerbotAI* ai)
    {
        return new ActionNode ("rejuvenation",
            /*P*/ NextAction::array(0, new NextAction("tree form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("lifebloom"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* rejuvenation_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("rejuvenation on party",
            /*P*/ NextAction::array(0, new NextAction("tree form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("lifebloom on party"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* rejuvenation_on_master(PlayerbotAI* ai)
    {
        return new ActionNode ("rejuvenation on master",
            /*P*/ NextAction::array(0, new NextAction("tree form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("lifebloom on master"), NULL),
            /*C*/ NULL);
    }

    static ActionNode* wild_growth_on_master(PlayerbotAI* ai)
    {
        return new ActionNode ("wild growth on master",
            /*P*/ NextAction::array(0, new NextAction("tree form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("lifebloom on master"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* nature_swiftness(PlayerbotAI* ai)
    {
        return new ActionNode ("nature's swiftness",
            /*P*/ NextAction::array(0, new NextAction("tree form"), NULL),
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("healing touch"), NULL));
    }
    static ActionNode* nature_swiftness_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("nature's swiftness on party",
            /*P*/ NextAction::array(0, new NextAction("tree form"), NULL),
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("healing touch on party"), NULL));
    }
    static ActionNode* nature_swiftness_on_master(PlayerbotAI* ai)
    {
        return new ActionNode ("nature's swiftness on master",
            /*P*/ NextAction::array(0, new NextAction("tree form"), NULL),
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("healing touch on master"), NULL));
    }
   static ActionNode* moonfire_heal(PlayerbotAI* ai)
    {
        return new ActionNode ("moonfire heal",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* wrath_heal(PlayerbotAI* ai)
    {
        return new ActionNode ("wrath heal",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("reach spell"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* tree_form(PlayerbotAI* ai)
    {
        return new ActionNode ("tree form",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*C*/ NULL);
    }
   static ActionNode* natures_grasp(PlayerbotAI* ai)
    {
        return new ActionNode ("nature's grasp",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/NULL);
    }
    static ActionNode* healing_touch_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("healing touch on party",
            /*P*/ NextAction::array(0, new NextAction("tree form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("reach spell"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* healing_touch_on_master(PlayerbotAI* ai)
    {
        return new ActionNode ("healing touch on master",
            /*P*/ NextAction::array(0, new NextAction("tree form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("reach spell"), NULL),
            /*C*/ NULL);
    }

};

HealDruidStrategy::HealDruidStrategy(PlayerbotAI* ai) : GenericDruidStrategy(ai)
{
    actionNodeFactories.Add(new HealDruidStrategyActionNodeFactory());
}

NextAction** HealDruidStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("moonfire heal", ACTION_NORMAL + 1), new NextAction("wrath heal", ACTION_NORMAL),NULL);
}

void HealDruidStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericDruidStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of spell",
        NextAction::array(0, new NextAction("reach spell", ACTION_MOVE + 9), NULL)));

    triggers.push_back(new TriggerNode(
        "not facing target",
        NextAction::array(0, new NextAction("set facing", ACTION_MOVE + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "tree form",
        NextAction::array(0, new NextAction("tree form", ACTION_HIGH + 1), NULL)));

 	triggers.push_back(new TriggerNode(
        "enemy too close for spell",
		NextAction::array(0, new NextAction("nature's grasp", ACTION_MOVE + 9), new NextAction("flee", ACTION_MOVE + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("regrowth", ACTION_MEDIUM_HEAL + 2),NULL)));

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("swiftmend", ACTION_CRITICAL_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("regrowth on party", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "master medium health",
        NextAction::array(0, new NextAction("regrowth on master", ACTION_CRITICAL_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("nourish", ACTION_MEDIUM_HEAL + 9), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("nourish on party", ACTION_MEDIUM_HEAL + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "master low health",
        NextAction::array(0, new NextAction("nourish on master", ACTION_MEDIUM_HEAL + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("healing touch on party", ACTION_CRITICAL_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "master critical health",
        NextAction::array(0, new NextAction("healing touch on master", ACTION_EMERGENCY + 1), NULL)));

 	triggers.push_back(new TriggerNode(
        "party member almost dead",
        NextAction::array(0, new NextAction("swiftmend on party", ACTION_EMERGENCY), NULL)));

	triggers.push_back(new TriggerNode(
        "almost dead",
        NextAction::array(0, new NextAction("swiftmend", ACTION_EMERGENCY + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "master almost dead",
        NextAction::array(0, new NextAction("swiftmend on master", ACTION_EMERGENCY + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("rejuvenation", ACTION_LIGHT_HEAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "master almost full health",
        NextAction::array(0, new NextAction("wild growth on master", ACTION_LIGHT_HEAL + 6), new NextAction("rejuvenation on master", ACTION_LIGHT_HEAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("rejuvenation on party", ACTION_LIGHT_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full aoe heal",
        NextAction::array(0, new NextAction("wild growth on master", ACTION_MEDIUM_HEAL + 3), NULL)));

	triggers.push_back(new TriggerNode(
        "have aggro",
        NextAction::array(0, new NextAction("barkskin", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "entangling roots",
        NextAction::array(0, new NextAction("entangling roots on cc", ACTION_HIGH + 1), NULL)));
}
