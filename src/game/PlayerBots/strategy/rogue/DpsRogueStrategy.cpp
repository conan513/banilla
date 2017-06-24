#include "../../../botpch.h"
#include "../../playerbot.h"
#include "RogueMultipliers.h"
#include "DpsRogueStrategy.h"

using namespace ai;

class DpsRogueStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    DpsRogueStrategyActionNodeFactory()
    {
        creators["backstab"] = &backstab;
        creators["hemorrhage"] = &hemorrhage;
        creators["kick"] = &kick;
        creators["gouge"] = &gouge;
        creators["kidney shot"] = &kidney_shot;
        creators["evasion"] = &evasion;
        creators["dismantle"] = &dismantle;
        creators["move behind"] = &move_behind;
        creators["sap"] = &sap;
        creators["sap on cc"] = &sap_on_cc;
        creators["melee"] = &melee;
        creators["reach melee"] = &reach_melee;
        creators["vanish"] = &vanish;
        creators["sunder armor"] = &sunder_armor;
    }
    ~DpsRogueStrategyActionNodeFactory()
    {
        creators.erase("backstab");
        creators.erase("hemorrhage");
        creators.erase("kick");
        creators.erase("gouge");
        creators.erase("kidney shot");
        creators.erase("evasion");
        creators.erase("dismantle");
        creators.erase("move behind");
        creators.erase("sap");
        creators.erase("sap on cc");
        creators.erase("melee");
        creators.erase("reach melee");
        creators.erase("vanish");
        creators.erase("sunder armor");
    }
private:

    static ActionNode* move_behind(PlayerbotAI* ai)
    {
        return new ActionNode ("move behind",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("garrote"), NULL));
    }
    static ActionNode* melee(PlayerbotAI* ai)
    {
        return new ActionNode ("melee",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("move behind"), NULL),
            /*C*/  NULL);
    }
    static ActionNode* reach_melee(PlayerbotAI* ai)
    {
        return new ActionNode ("reach melee",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* backstab(PlayerbotAI* ai)
    {
        return new ActionNode ("backstab",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("hemorrhage"), NULL),
            /*C*/ NextAction::array(0, new NextAction("move behind"), NULL));
    }
    static ActionNode* hemorrhage(PlayerbotAI* ai)
    {
        return new ActionNode ("hemorrhage",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("move behind"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* kick(PlayerbotAI* ai)
    {
        return new ActionNode ("kick",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("gouge"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* gouge(PlayerbotAI* ai)
    {
        return new ActionNode ("gouge",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("kidney shot"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* kidney_shot(PlayerbotAI* ai)
    {
        return new ActionNode ("kidney shot",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("blind"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* vanish(PlayerbotAI* ai)
    {
        return new ActionNode ("vanish",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("preparation"), NULL),
            /*C*/ NextAction::array(0, new NextAction("flee"), NULL));
    }
    static ActionNode* evasion(PlayerbotAI* ai)
    {
        return new ActionNode ("evasion",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("vanish"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* sap(PlayerbotAI* ai)
    {
        return new ActionNode ("sap",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("garrote"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* sap_on_cc(PlayerbotAI* ai)
    {
        return new ActionNode ("sap on cc",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("garrote"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* dismantle(PlayerbotAI* ai)
    {
        return new ActionNode ("dismantle",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("blind"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* sunder_armor(PlayerbotAI* ai)
    {
        return new ActionNode ("sunder armor",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("rupture"), NULL),
            /*C*/ NULL);
    }
};

DpsRogueStrategy::DpsRogueStrategy(PlayerbotAI* ai) : MeleeCombatStrategy(ai)
{
    factoryInternal = new DpsRogueStrategyActionNodeFactory();
    actionNodeFactories.Add(factoryInternal);
}

DpsRogueStrategy::~DpsRogueStrategy()
{
    actionNodeFactories.Remove(factoryInternal);
    delete factoryInternal;
    delete defaultActions;
}

NextAction** DpsRogueStrategy::getDefaultActions()
{
    defaultActions = NextAction::array(0, new NextAction("garrote", ACTION_HIGH + 8), new NextAction("backstab", ACTION_NORMAL), NULL);
    return defaultActions;
}

void DpsRogueStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    MeleeCombatStrategy::InitTriggers(triggers);

	triggers.push_back(new TriggerNode(
        "stealth",
        NextAction::array(0, new NextAction("stealth", ACTION_MOVE + 9), NULL)));

	triggers.push_back(new TriggerNode(
        "takes periodic damage",
        NextAction::array(0, new NextAction("cloak of shadows", ACTION_EMERGENCY), NULL)));

    //triggers.push_back(new TriggerNode(
    //    "sap on cc",
    //    NextAction::array(0, new NextAction("sap", ACTION_HIGH + 9), NULL)));

    //triggers.push_back(new TriggerNode(
    //    "sap",
    //    NextAction::array(0, new NextAction("sap", ACTION_HIGH + 10), NULL)));

//	triggers.push_back(new TriggerNode(
//        "combo points available",
//        NextAction::array(0, new NextAction("sunder armor", ACTION_HIGH + 8), NULL)));

	triggers.push_back(new TriggerNode(
        "target fleeing",
        NextAction::array(0, new NextAction("kidney shot", ACTION_HIGH), NULL)));

	triggers.push_back(new TriggerNode(
        "combo point available",
        NextAction::array(0, new NextAction("slice and dice", ACTION_HIGH + 9), NULL)));

	triggers.push_back(new TriggerNode(
        "riposte",
        NextAction::array(0, new NextAction("riposte", ACTION_HIGH + 3), NULL)));

	triggers.push_back(new TriggerNode(
        "rupture",
        NextAction::array(0, new NextAction("rupture", ACTION_HIGH + 5), NULL)));

	triggers.push_back(new TriggerNode(
        "slice and dice",
        NextAction::array(0, new NextAction("slice and dice", ACTION_HIGH + 9), NULL)));

	triggers.push_back(new TriggerNode(
        "rooted",
        NextAction::array(0, new NextAction("vanish", ACTION_HIGH + 5), NULL)));

 	triggers.push_back(new TriggerNode(
        "snared",
        NextAction::array(0, new NextAction("sprint", ACTION_HIGH + 4), NULL)));

 	triggers.push_back(new TriggerNode(
        "enemy too close for melee",
        NextAction::array(0, new NextAction("move out of enemy contact", ACTION_MOVE + 8), NULL)));

	triggers.push_back(new TriggerNode(
	"medium threat",
	NextAction::array(0, new NextAction("feint", ACTION_HIGH), NULL)));

	triggers.push_back(new TriggerNode(
	"critical health",
	NextAction::array(0, new NextAction("vanish", ACTION_EMERGENCY + 8), NULL)));

	triggers.push_back(new TriggerNode(
	"party member critical health",
	NextAction::array(0, new NextAction("dismantle", ACTION_HIGH + 7), NULL)));

	triggers.push_back(new TriggerNode(
	"kick",
	NextAction::array(0, new NextAction("kick", ACTION_INTERRUPT + 2), NULL)));

	triggers.push_back(new TriggerNode(
	"kick on enemy healer",
	NextAction::array(0, new NextAction("kick on enemy healer", ACTION_INTERRUPT + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "not facing target",
        NextAction::array(0, new NextAction("set facing", ACTION_MOVE + 7), NULL)));

     triggers.push_back(new TriggerNode(
        "have aggro",
        NextAction::array(0, new NextAction("evasion", ACTION_EMERGENCY + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "almost dead",
        NextAction::array(0, new NextAction("bandage", ACTION_EMERGENCY + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "garrote",
        NextAction::array(0, new NextAction("garrote", ACTION_EMERGENCY + 2), NULL)));

     triggers.push_back(new TriggerNode(
        "runaway",
        NextAction::array(0, new NextAction("blind", ACTION_EMERGENCY + 7), new NextAction("sprint", ACTION_EMERGENCY + 6), new NextAction("stealth", ACTION_EMERGENCY + 5),NULL)));
}

class DpsSwordRogueStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    DpsSwordRogueStrategyActionNodeFactory()
    {
        creators["riposte"] = &riposte;
        creators["sinister strike"] = &sinister_strike;
        creators["adrenaline rush"] = &adrenaline_rush;
        creators["boost"] = &adrenaline_rush;
        creators["garrote"] = &garrote;
        creators["cheap shot"] = &cheap_shot;
    }
    ~DpsSwordRogueStrategyActionNodeFactory()
    {
        creators.erase("riposte");
        creators.erase("sinister strike");
        creators.erase("adrenaline rush");
        creators.erase("boost");
        creators.erase("garrote");
        creators.erase("cheap shot");
    }
private:
    static ActionNode* riposte(PlayerbotAI* ai)
    {
        return new ActionNode ("riposte",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("sinister strike"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* sinister_strike(PlayerbotAI* ai)
    {
        return new ActionNode ("sinister strike",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* adrenaline_rush(PlayerbotAI* ai)
    {
        return new ActionNode ("adrenaline rush",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* garrote(PlayerbotAI* ai)
    {
        return new ActionNode ("garrote sword",
            /*P*/ NextAction::array(0, new NextAction("stealth"), NULL),
            /*A*/ NextAction::array(0, new NextAction("cheap shot"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* cheap_shot(PlayerbotAI* ai)
    {
        return new ActionNode ("cheap shot",
            /*P*/ NextAction::array(0, new NextAction("stealth"), NULL),
            /*A*/ NextAction::array(0, new NextAction("sinister strike"), NULL),
            /*C*/ NULL);
    }
};

DpsSwordRogueStrategy::DpsSwordRogueStrategy(PlayerbotAI* ai) :  DpsRogueStrategy(ai)
{
    factoryInternal = new DpsSwordRogueStrategyActionNodeFactory();
    actionNodeFactories.Add(factoryInternal);
}

DpsSwordRogueStrategy::~DpsSwordRogueStrategy()
{
    actionNodeFactories.Remove(factoryInternal);
    delete factoryInternal;
    delete defaultActions;
}

NextAction** DpsSwordRogueStrategy::getDefaultActions()
{
    defaultActions = NextAction::array(0, new NextAction("riposte", ACTION_NORMAL + 2), new NextAction("sinister strike", ACTION_NORMAL), NULL);
    return defaultActions;
}

void DpsSwordRogueStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    DpsRogueStrategy::InitTriggers(triggers);

	triggers.push_back(new TriggerNode(
        "garrote",
        NextAction::array(0, new NextAction("garrote sword", ACTION_EMERGENCY + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("reach melee", ACTION_MOVE + 8), new NextAction("garrote sword", ACTION_MOVE + 7), NULL)));

    triggers.push_back(new TriggerNode(
	"high energy available",
	NextAction::array(0, new NextAction("sinister strike", ACTION_NORMAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "combo points available",
        NextAction::array(0, new NextAction("eviscerate", ACTION_HIGH), NULL)));

    triggers.push_back(new TriggerNode(
        "riposte",
        NextAction::array(0, new NextAction("riposte", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "rupture",
        NextAction::array(0, new NextAction("rupture", ACTION_HIGH + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "not facing target",
        NextAction::array(0, new NextAction("set facing", ACTION_EMERGENCY), NULL)));

     triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("blade flurry", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "melee high aoe",
        NextAction::array(0, new NextAction("fan of knives", ACTION_HIGH + 1), NULL)));

     triggers.push_back(new TriggerNode(
        "boost",
        NextAction::array(0, new NextAction("adrenaline rush", ACTION_NORMAL + 5),  new NextAction("blade flurry", ACTION_NORMAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
	"target almost dead",
	NextAction::array(0, new NextAction("eviscerate", ACTION_HIGH + 9), NULL)));
}

class DpsDaggerRogueStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    DpsDaggerRogueStrategyActionNodeFactory()
    {
        creators["premeditation"] = &premeditation;
        creators["melee"] = &melee;
        creators["ghostly strike"] = &ghostly_strike;
        creators["gouge"] = &gouge;
        creators["shadowstep"] = &shadowstep;
        creators["mutilate"] = &mutilate;
        creators["vanish"] = &vanish;
        creators["backstab"] = &backstab;
        creators["cold blood"] = &cold_blood;
        creators["envenom"] = &envenom;
        creators["boost"] = &shadow_dance;
        creators["garrote"] = &garrote;
        creators["ambush"] = &ambush;
        creators["cheap shot"] = &cheap_shot;
    }
    ~DpsDaggerRogueStrategyActionNodeFactory()
    {
        creators.erase("premeditation");
        creators.erase("melee");
        creators.erase("ghostly strike");
        creators.erase("gouge");
        creators.erase("shadowstep");
        creators.erase("mutilate");
        creators.erase("vanish");
        creators.erase("backstab");
        creators.erase("cold blood");
        creators.erase("envenom");
        creators.erase("boost");
        creators.erase("garrote");
        creators.erase("ambush");
        creators.erase("cheap shot");
    }
private:
    static ActionNode* premeditation(PlayerbotAI* ai)
    {
        return new ActionNode ("premeditation",
            /*P*/ NextAction::array(0, new NextAction("stealth"), NULL),
            /*A*/  NextAction::array(0, new NextAction("garrote"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* rupture(PlayerbotAI* ai)
    {
        return new ActionNode ("rupture",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("envenom"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* melee(PlayerbotAI* ai)
    {
        return new ActionNode ("melee",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("shadowstep"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* shadowstep(PlayerbotAI* ai)
    {
        return new ActionNode ("shadowstep",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("reach melee"), NULL),
            /*C*/ NextAction::array(0, new NextAction("premeditation"), NULL));
    }
    static ActionNode* mutilate(PlayerbotAI* ai)
    {
        return new ActionNode ("mutilate",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("backstab"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* vanish(PlayerbotAI* ai)
    {
        return new ActionNode ("vanish",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("preparation"), NULL),
            /*C*/  NextAction::array(0, new NextAction("garrote"), NULL));
    }
    static ActionNode* backstab(PlayerbotAI* ai)
    {
        return new ActionNode ("backstab",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("hemorrhage"), NULL),
            /*C*/ NextAction::array(0, new NextAction("move behind"), NULL));
    }
    static ActionNode* ghostly_strike(PlayerbotAI* ai)
    {
        return new ActionNode ("ghostly strike",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("dismantle"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* gouge(PlayerbotAI* ai)
    {
        return new ActionNode ("gouge",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("hemorrhage"), NULL),
            /*C*/ NextAction::array(0, new NextAction("move behind"), NULL));
    }
    static ActionNode* envenom(PlayerbotAI* ai)
    {
        return new ActionNode ("envenom",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("eviscerate"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* shadow_dance(PlayerbotAI* ai)
    {
        return new ActionNode ("shadow dance",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("cold blood"), NULL),
            /*C*/ NextAction::array(0, new NextAction("ambush"), NULL));
    }

    static ActionNode* cold_blood(PlayerbotAI* ai)
    {
        return new ActionNode ("cold blood",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("mutilate"),NULL));
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
            /*A*/ NextAction::array(0, new NextAction("garrote"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* cheap_shot(PlayerbotAI* ai)
    {
        return new ActionNode ("cheap shot",
            /*P*/ NextAction::array(0, new NextAction("stealth"), NULL),
            /*A*/ NextAction::array(0, new NextAction("garrote"), NULL),
            /*C*/ NULL);
    }

};

DpsDaggerRogueStrategy::DpsDaggerRogueStrategy(PlayerbotAI* ai) :  DpsRogueStrategy(ai)
{
    factoryInternal = new DpsDaggerRogueStrategyActionNodeFactory();
    actionNodeFactories.Add(factoryInternal);
}

DpsDaggerRogueStrategy::~DpsDaggerRogueStrategy()
{
    actionNodeFactories.Remove(factoryInternal);
    delete factoryInternal;
    delete defaultActions;
}

NextAction** DpsDaggerRogueStrategy::getDefaultActions()
{
    defaultActions = NextAction::array(0, new NextAction("garrote", ACTION_HIGH + 9), new NextAction("ambush", ACTION_HIGH), new NextAction("mutilate", ACTION_NORMAL + 5), new NextAction("backstab", ACTION_NORMAL), NULL);
    return defaultActions;
}

void DpsDaggerRogueStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    DpsRogueStrategy::InitTriggers(triggers);

//	triggers.push_back(new TriggerNode(
//        "garrote",
//        NextAction::array(0, new NextAction("garrote", ACTION_EMERGENCY + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "ambush",
        NextAction::array(0, new NextAction("ambush", ACTION_EMERGENCY + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("shadowstep", ACTION_MOVE + 9), new NextAction("garrote", ACTION_HIGH + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "combo points available",
        NextAction::array(0, new NextAction("cold blood", ACTION_HIGH + 2), new NextAction("envenom", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "front target",
        NextAction::array(0, new NextAction("move behind", ACTION_MOVE + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "high energy available",
        NextAction::array(0, new NextAction("backstab", ACTION_HIGH), NULL)));

     triggers.push_back(new TriggerNode(
        "rupture",
        NextAction::array(0, new NextAction("rupture", ACTION_HIGH + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "premeditation",
        NextAction::array(0, new NextAction("premeditation", ACTION_HIGH + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "have aggro",
        NextAction::array(0, new NextAction("ghostly strike", ACTION_HIGH + 4), NULL)));

	triggers.push_back(new TriggerNode(
        "medium threat",
        NextAction::array(0, new NextAction("feint", ACTION_HIGH), NULL)));

	triggers.push_back(new TriggerNode(
        "almost dead",
        NextAction::array(0, new NextAction("vanish", ACTION_EMERGENCY), NULL)));

	triggers.push_back(new TriggerNode(
        "kick",
        NextAction::array(0, new NextAction("kick", ACTION_INTERRUPT + 2), NULL)));

	triggers.push_back(new TriggerNode(
        "kick on enemy healer",
        NextAction::array(0, new NextAction("kick on enemy healer", ACTION_INTERRUPT + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "behind target",
        NextAction::array(0, new NextAction("backstab", ACTION_NORMAL + 6), NULL)));

     triggers.push_back(new TriggerNode(
        "boost",
        NextAction::array(0, new NextAction("shadow dance", ACTION_NORMAL + 5), new NextAction("garrote", ACTION_NORMAL + 5), new NextAction("ambush", ACTION_NORMAL + 5), new NextAction("ambush", ACTION_NORMAL + 5),NULL)));

     triggers.push_back(new TriggerNode(
        "melee high aoe",
        NextAction::array(0, new NextAction("fan of knives", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "target almost dead",
        NextAction::array(0, new NextAction("envenom", ACTION_HIGH + 9), NULL)));
}
