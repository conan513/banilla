#include "../../../botpch.h"
#include "../../playerbot.h"
#include "PaladinMultipliers.h"
#include "HealPaladinStrategy.h"
#include "GenericPaladinStrategyActionNodeFactory.h"

using namespace ai;

class MeleeHealPaladinStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    MeleeHealPaladinStrategyActionNodeFactory()
    {
        creators["seal of righteousness"] = &seal_of_righteousness;
        creators["seal of wisdom"] = &seal_of_wisdom;
        creators["holy shock on party"] = &holy_shock_on_party;
    }

private:
    static ActionNode* seal_of_righteousness(PlayerbotAI* ai)
    {
        return new ActionNode ("seal_of_righteousness",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("seal of wisdom"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* seal_of_wisdom(PlayerbotAI* ai)
    {
        return new ActionNode ("seal of wisdom",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("seal of light"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* holy_shock_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("holy shock on party",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("holy shock on attacker"), NULL),
            /*C*/ NULL);
    }
};

MeleeHealPaladinStrategy::MeleeHealPaladinStrategy(PlayerbotAI* ai) : GenericPaladinStrategy(ai)
{
    actionNodeFactories.Add(new MeleeHealPaladinStrategyActionNodeFactory());
}

NextAction** MeleeHealPaladinStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("judgement of wisdom", ACTION_NORMAL + 3), new NextAction("holy shock on party", ACTION_NORMAL + 2), NULL);
}

void MeleeHealPaladinStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericPaladinStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("move behind", ACTION_MOVE), NULL)));

    triggers.push_back(new TriggerNode(
        "beacon of light on master",
        NextAction::array(0, new NextAction("beacon of light on master",  ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("holy light", ACTION_MEDIUM_HEAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "medium mana",
        NextAction::array(0, new NextAction("seal of wisdom", ACTION_MEDIUM_HEAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "full mana",
        NextAction::array(0, new NextAction("seal of righteousness", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "seal",
        NextAction::array(0, new NextAction("seal of righteousness", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "seal mana",
        NextAction::array(0, new NextAction("seal of wisdom", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("holy shock on party", ACTION_LIGHT_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "master almost full health",
        NextAction::array(0, new NextAction("holy shock on master", ACTION_LIGHT_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("holy light on party", ACTION_MEDIUM_HEAL + 1), NULL)));

     triggers.push_back(new TriggerNode(
        "master medium health",
        NextAction::array(0, new NextAction("holy light on master", ACTION_MEDIUM_HEAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("flash of light", ACTION_CRITICAL_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("flash of light on party", ACTION_CRITICAL_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "master low health",
        NextAction::array(0, new NextAction("flash of light on master", ACTION_CRITICAL_HEAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
		"party member critical health",
		NextAction::array(0, new NextAction("holy shock on party", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
		"master critical health",
		NextAction::array(0, new NextAction("holy shock on master", ACTION_EMERGENCY + 1), NULL)));

    triggers.push_back(new TriggerNode(
		"critical health",
		NextAction::array(0, new NextAction("holy shock", ACTION_EMERGENCY + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "judgement of wisdom",
        NextAction::array(0, new NextAction("judgement of wisdom", ACTION_NORMAL + 2), NULL)));

     triggers.push_back(new TriggerNode(
        "not facing target",
        NextAction::array(0, new NextAction("set facing", ACTION_MOVE + 7), NULL)));

     triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("divine illumination", ACTION_HIGH + 5), NULL)));
}


class HealPaladinStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    HealPaladinStrategyActionNodeFactory()
    {
        creators["seal of wisdom"] = &seal_of_wisdom;
        creators["seal of light"] = &seal_of_light;
    }

private:
    static ActionNode* seal_of_wisdom(PlayerbotAI* ai)
    {
        return new ActionNode ("seal of wisdom",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("seal of light"), NULL),
            /*C*/ NULL);
    }
     static ActionNode* seal_of_light(PlayerbotAI* ai)
    {
        return new ActionNode ("seal of light",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("seal of righteousness"), NULL),
            /*C*/ NULL);
    }
};

HealPaladinStrategy::HealPaladinStrategy(PlayerbotAI* ai) : RangedCombatStrategy(ai)
{
    actionNodeFactories.Add(new GenericPaladinStrategyActionNodeFactory());
    actionNodeFactories.Add(new HealPaladinStrategyActionNodeFactory());
}

NextAction** HealPaladinStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("ranged judgement of wisdom", ACTION_NORMAL + 2), new NextAction("exorcism heal", ACTION_NORMAL), NULL);
}

void HealPaladinStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    RangedCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "almost dead",
        NextAction::array(0, new NextAction("divine shield", ACTION_EMERGENCY + 7), new NextAction("holy light", ACTION_EMERGENCY + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy out of spell",
        NextAction::array(0, new NextAction("reach spell", ACTION_NORMAL + 9), NULL)));

     triggers.push_back(new TriggerNode(
        "enemy too close for spell",
        NextAction::array(0, new NextAction("flee",40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "beacon of light on master",
        NextAction::array(0, new NextAction("beacon of light on master",  ACTION_HIGH), NULL)));

      triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("flash of light", ACTION_CRITICAL_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("flash of light on party", ACTION_CRITICAL_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "master low health",
        NextAction::array(0, new NextAction("flash of light on master", ACTION_CRITICAL_HEAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("holy light", ACTION_MEDIUM_HEAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("holy light on party", ACTION_MEDIUM_HEAL + 1), NULL)));

     triggers.push_back(new TriggerNode(
        "master medium health",
        NextAction::array(0, new NextAction("holy light on master", ACTION_MEDIUM_HEAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
		"party member critical health",
		NextAction::array(0, new NextAction("holy shock on party", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
		"master critical health",
		NextAction::array(0, new NextAction("holy shock on master", ACTION_EMERGENCY + 1), NULL)));

    triggers.push_back(new TriggerNode(
		"critical health",
		NextAction::array(0, new NextAction("holy shock", ACTION_EMERGENCY + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "judgement of wisdom",
        NextAction::array(0, new NextAction("ranged judgement of wisdom", ACTION_NORMAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "blessing",
        NextAction::array(0, new NextAction("blessing of kings", ACTION_HIGH + 8), NULL)));

     triggers.push_back(new TriggerNode(
        "not facing target",
        NextAction::array(0, new NextAction("set facing", ACTION_MOVE + 7), NULL)));

     triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("divine illumination", ACTION_HIGH + 5), NULL)));

	triggers.push_back(new TriggerNode(
		"hammer of justice interrupt",
		NextAction::array(0, new NextAction("hammer of justice", ACTION_INTERRUPT), NULL)));

	triggers.push_back(new TriggerNode(
		"hammer of justice on enemy healer",
		NextAction::array(0, new NextAction("hammer of justice on enemy healer", ACTION_INTERRUPT), NULL)));

	triggers.push_back(new TriggerNode(
		"almost dead",
		NextAction::array(0, new NextAction("divine shield", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
		"stunned",
		NextAction::array(0, new NextAction("blessing of freedom", ACTION_EMERGENCY), NULL)));

	triggers.push_back(new TriggerNode(
		"party member almost dead",
		NextAction::array(0, new NextAction("lay on hands on party", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "party member polymorphed",
        NextAction::array(0, new NextAction("cleanse magic on party", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "party member rooted",
        NextAction::array(0, new NextAction("blessing of freedom on party", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "party member snared",
        NextAction::array(0, new NextAction("blessing of freedom on party", ACTION_EMERGENCY), NULL)));

	triggers.push_back(new TriggerNode(
		"target critical health",
		NextAction::array(0, new NextAction("hammer of wrath", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure disease",
        NextAction::array(0, new NextAction("cleanse disease", ACTION_DISPEL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure disease",
        NextAction::array(0, new NextAction("cleanse disease on party", ACTION_DISPEL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse cure poison",
        NextAction::array(0, new NextAction("cleanse poison", ACTION_DISPEL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse party member cure poison",
        NextAction::array(0, new NextAction("cleanse poison on party", ACTION_DISPEL + 1), NULL)));

	triggers.push_back(new TriggerNode(
		"cleanse cure magic",
		NextAction::array(0, new NextAction("cleanse magic", ACTION_DISPEL + 2), NULL)));

	triggers.push_back(new TriggerNode(
		"cleanse party member cure magic",
		NextAction::array(0, new NextAction("cleanse magic on party", ACTION_DISPEL + 1), NULL)));

     triggers.push_back(new TriggerNode(
        "boost",
        NextAction::array(0, new NextAction("avenging wrath", ACTION_HIGH + 7), NULL)));
}
