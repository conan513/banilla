#include "../../../botpch.h"
#include "../../playerbot.h"
#include "MageMultipliers.h"
#include "GenericMageStrategy.h"

using namespace ai;

class GenericMageStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    GenericMageStrategyActionNodeFactory()
    {
        creators["frostbolt"] = &frostbolt;
        creators["fireball"] = &fireball;
        creators["pyroblast"] = &pyroblast;
        creators["frost nova"] = &frost_nova;
        creators["blink"] = &blink;
        creators["evocation"] = &evocation;
        creators["frostfire bolt"] = &frostfire_bolt;
        creators["ice block"] = &ice_block;
        creators["ice lance"] = &ice_lance;
        creators["cone of cold"] = &cone_of_cold;
		creators["remove curse"] = &remove_curse;
		creators["remove curse on party"] = &remove_curse_on_party;
    }
private:
    static ActionNode* frostbolt(PlayerbotAI* ai)
    {
        return new ActionNode ("frostbolt",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("shoot"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* pyroblast(PlayerbotAI* ai)
    {
        return new ActionNode ("pyroblast",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("fireball"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* fireball(PlayerbotAI* ai)
    {
        return new ActionNode ("fireball",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("frostbolt"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* frost_nova(PlayerbotAI* ai)
    {
        return new ActionNode ("frost nova",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("cone of cold",70), NULL),
            /*C*/ NextAction::array(0, new NextAction("relocate",ACTION_MOVE + 5), NULL));
    }
    static ActionNode* cone_of_cold(PlayerbotAI* ai)
    {
        return new ActionNode ("cone of cold",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("blink",ACTION_MOVE + 5), NULL),
            /*C*/ NextAction::array(0, new NextAction("relocate",ACTION_MOVE + 5), NULL));
    }
    static ActionNode* blink(PlayerbotAI* ai)
    {
        return new ActionNode ("blink",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("flee",ACTION_MOVE + 5), NULL),
            /*C*/ NULL);
    }
    static ActionNode* evocation(PlayerbotAI* ai)
    {
        return new ActionNode ("evocation",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("mana potion"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* frostfire_bolt(PlayerbotAI* ai)
    {
        return new ActionNode ("frostfire bolt",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("fireball"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* ice_block(PlayerbotAI* ai)
    {
        return new ActionNode ("ice block",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("cold snap"), NULL),
            /*C*/ NextAction::array(0, new NextAction("ice block"), NULL));
    }
    static ActionNode* ice_lance(PlayerbotAI* ai)
    {
        return new ActionNode ("ice block",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("fire blast"), NULL),
            /*C*/ NULL);
    }
	static ActionNode* remove_curse(PlayerbotAI* ai)
	{
		return new ActionNode("remove curse",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("remove lesser curse"), NULL),
			/*C*/ NULL);
	}
	static ActionNode* remove_curse_on_party(PlayerbotAI* ai)
	{
		return new ActionNode("remove curse on party",
			/*P*/ NULL,
			/*A*/ NextAction::array(0, new NextAction("remove lesser curse on party"), NULL),
			/*C*/ NULL);
	}
};

GenericMageStrategy::GenericMageStrategy(PlayerbotAI* ai) : CombatStrategy(ai)
{
    actionNodeFactories.Add(new GenericMageStrategyActionNodeFactory());
}

void GenericMageStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "takes periodic damage",
        NextAction::array(0, new NextAction("blink", ACTION_MOVE + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy too close for spell",
        NextAction::array(0, new NextAction("flee", 49.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"enemy is close",
		NextAction::array(0, new NextAction("frost nova", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy out of spell",
        NextAction::array(0, new NextAction("reach spell", ACTION_MOVE + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "have aggro",
        NextAction::array(0, new NextAction("frost nova",ACTION_MOVE + 9), new NextAction("flee",ACTION_MOVE + 8), NULL)));

   triggers.push_back(new TriggerNode(
        "runaway",
        NextAction::array(0, new NextAction("frost nova", ACTION_EMERGENCY + 7), new NextAction("blink", ACTION_EMERGENCY + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "remove curse",
        NextAction::array(0, new NextAction("remove curse", 41.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "remove curse on party",
        NextAction::array(0, new NextAction("remove curse on party", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "counterspell",
        NextAction::array(0, new NextAction("counterspell", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "counterspell on enemy healer",
        NextAction::array(0, new NextAction("counterspell on enemy healer", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"critical health",
		NextAction::array(0, new NextAction("ice block", 80.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "polymorph",
        NextAction::array(0, new NextAction("polymorph", 50.0f), NULL)));

     triggers.push_back(new TriggerNode(
        "polymorph on cc",
        NextAction::array(0, new NextAction("polymorph", 50.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"spellsteal",
		NextAction::array(0, new NextAction("spellsteal", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
		"stunned",
		NextAction::array(0, new NextAction("blink", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
		"rooted",
		NextAction::array(0, new NextAction("blink", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium threat",
        NextAction::array(0, new NextAction("invisibility", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("evocation", ACTION_EMERGENCY + 5), NULL)));

     triggers.push_back(new TriggerNode(
        "boost",
        NextAction::array(0, new NextAction("icy veins", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "almost dead",
        NextAction::array(0, new NextAction("bandage", ACTION_CRITICAL_HEAL), NULL)));
}

void MageCureStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		"remove curse",
		NextAction::array(0, new NextAction("remove curse", 41.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"remove curse on party",
		NextAction::array(0, new NextAction("remove curse on party", 40.0f), NULL)));

}
