#include "../../pchdef.h"
#include "../playerbot.h"
#include "Strategy.h"
#include "NamedObjectContext.h"

using namespace ai;
using namespace std;


class ActionNodeFactoryInternal : public NamedObjectFactory<ActionNode>
{
public:
    ActionNodeFactoryInternal()
    {
        creators["melee"] = &melee;
        creators["healthstone"] = &healthstone;
        creators["be near"] = &follow_master_random;
        creators["attack anything"] = &attack_anything;
        creators["move random"] = &move_random;
        creators["move to loot"] = &move_to_loot;
        creators["food"] = &food;
        creators["drink"] = &drink;
        creators["bandage"] = &bandage;
        creators["mana potion"] = &mana_potion;
        creators["healing potion"] = &healing_potion;
        creators["bomb"] = &bomb;
        creators["flee"] = &flee;
		creators["reposition"] = &reposition;
		creators["move to guestgiver"] = &move_questgiver;
		creators["move to guestender"] = &move_questender;
		creators["move to quest"] = &move_quest;
    }

private:
    static ActionNode* melee(PlayerbotAI* ai)
    {
        return new ActionNode ("melee",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* healthstone(PlayerbotAI* ai)
    {
        return new ActionNode ("healthstone",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("healing potion"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* follow_master_random(PlayerbotAI* ai)
    {
        return new ActionNode ("be near",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("follow"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* attack_anything(PlayerbotAI* ai)
    {
        return new ActionNode ("attack anything",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* move_random(PlayerbotAI* ai)
    {
        return new ActionNode ("move random",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("stay line"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* move_to_loot(PlayerbotAI* ai)
    {
        return new ActionNode ("move to loot",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* food(PlayerbotAI* ai)
    {
        return new ActionNode ("food",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* drink(PlayerbotAI* ai)
    {
        return new ActionNode ("drink",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* bandage(PlayerbotAI* ai)
    {
        return new ActionNode ("bandage",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* mana_potion(PlayerbotAI* ai)
    {
        return new ActionNode ("mana potion",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("drink"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* healing_potion(PlayerbotAI* ai)
    {
        return new ActionNode ("healing potion",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("food"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* flee(PlayerbotAI* ai)
    {
        return new ActionNode ("flee",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* bomb(PlayerbotAI* ai)
    {
        return new ActionNode ("bomb",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
	static ActionNode* reposition(PlayerbotAI* ai)
	{
		return new ActionNode("reposition",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
	static ActionNode* move_questgiver(PlayerbotAI* ai)
	{
		return new ActionNode("move to guestgiver",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
	static ActionNode* move_questender(PlayerbotAI* ai)
	{
		return new ActionNode("move to guestender",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}
	static ActionNode* move_quest(PlayerbotAI* ai)
	{
		return new ActionNode("move to quest",
			/*P*/ NULL,
			/*A*/ NULL,
			/*C*/ NULL);
	}

    ~ActionNodeFactoryInternal()
    {
        creators.erase("melee");
        creators.erase("healthstone");
        creators.erase("be near");
        creators.erase("attack anything");
        creators.erase("move random");
        creators.erase("move to loot");
        creators.erase("food");
        creators.erase("drink");
        creators.erase("bandage");
        creators.erase("mana potion");
        creators.erase("healing potion");
        creators.erase("bomb");
        creators.erase("flee");
		creators.erase("reposition");
		creators.erase("move to guestgiver");
		creators.erase("move to guestender");
		creators.erase("move to quest");
    }
};

Strategy::Strategy(PlayerbotAI* ai) : PlayerbotAIAware(ai)
{
    factoryInternal = new ActionNodeFactoryInternal();
    actionNodeFactories.Add(factoryInternal);
}

Strategy::~Strategy()
{
    actionNodeFactories.Remove(factoryInternal);
    delete factoryInternal;
}

ActionNode* Strategy::GetAction(string name)
{
    return actionNodeFactories.GetObject(name, ai);
}

