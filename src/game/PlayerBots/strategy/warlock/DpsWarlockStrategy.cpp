#include "../../../botpch.h"
#include "../../playerbot.h"
#include "WarlockTriggers.h"
#include "WarlockMultipliers.h"
#include "DpsWarlockStrategy.h"
#include "WarlockActions.h"

using namespace ai;

class DpsWarlockStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    DpsWarlockStrategyActionNodeFactory()
    {
        creators["summon felhunter"] = &summon_felhunter;
        creators["shadow bolt"] = &shadow_bolt;
        creators["unstable affliction"] = &unstable_affliction;
        creators["haunt"] = &haunt;
    }
    ~DpsWarlockStrategyActionNodeFactory()
    {
        creators.erase("summon felhunter");
        creators.erase("shadow bolt");
        creators.erase("unstable affliction");
        creators.erase("haunt");
    }
private:
    static ActionNode* shadow_bolt(PlayerbotAI* ai)
    {
        return new ActionNode ("shadow bolt",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("shoot"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* summon_felhunter(PlayerbotAI* ai)
    {
        return new ActionNode ("summon felhunter",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("summon imp"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* unstable_affliction(PlayerbotAI* ai)
    {
        return new ActionNode ("unstable affliction",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("shadow bolt"), NULL),
            /*C*/ NextAction::array(0, new NextAction("corruption"), NULL));
    }
    static ActionNode* haunt(PlayerbotAI* ai)
    {
        return new ActionNode ("haunt",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("shadow bolt"), NULL),
            /*C*/ NULL);
    }
};

DpsWarlockStrategy::DpsWarlockStrategy(PlayerbotAI* ai) : GenericWarlockStrategy(ai)
{
    factoryInternal = new DpsWarlockStrategyActionNodeFactory();
    actionNodeFactories.Add(factoryInternal);
}

DpsWarlockStrategy::~DpsWarlockStrategy()
{
    actionNodeFactories.Remove(factoryInternal);
    delete factoryInternal;
    delete defaultActions;
}

NextAction** DpsWarlockStrategy::getDefaultActions()
{
    defaultActions = NextAction::array(0, new NextAction("life tap", 13.0f),  new NextAction("shadow bolt", 12.0f), NULL);
    return defaultActions;
}

void DpsWarlockStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericWarlockStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("drain life", 40.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"shadow trance",
		NextAction::array(0, new NextAction("shadow bolt", 20.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"backlash",
		NextAction::array(0, new NextAction("shadow bolt", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
		"target critical health",
		NextAction::array(0, new NextAction("drain soul", 30.0f), NULL)));
/*
    triggers.push_back(new TriggerNode(
        "corruption on attacker",
        NextAction::array(0, new NextAction("corruption on attacker", 29.0f),  NULL)));
*/

    triggers.push_back(new TriggerNode(
        "corruption",
        NextAction::array(0, new NextAction("corruption", 29.0f),  NULL)));

    triggers.push_back(new TriggerNode(
        "unstable affliction",
        NextAction::array(0, new NextAction("unstable corruption", 19.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "haunt",
        NextAction::array(0, new NextAction("haunt", 20.0f), NULL)));
}

void DpsAoeWarlockStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "medium aoe",
        NextAction::array(0, new NextAction("shadowfury", 29.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "corruption on attacker",
        NextAction::array(0, new NextAction("corruption on attacker", 15.0f),  NULL)));

    triggers.push_back(new TriggerNode(
        "corruption",
        NextAction::array(0, new NextAction("seed of corruption", 30.0f), NULL)));
}

class WarlockDebuffStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    WarlockDebuffStrategyActionNodeFactory()
    {
        creators["curse of the elements"] = curse_of_the_elements;
    }
    ~WarlockDebuffStrategyActionNodeFactory()
    {
        creators.erase("curse of the elements");
    }
private:
    static ActionNode* curse_of_the_elements(PlayerbotAI* ai)
    {
        return new ActionNode ("curse of the elements",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("curse of weakness"), NULL),
            /*C*/ NULL);
    }

};

WarlockDebuffStrategy::WarlockDebuffStrategy(PlayerbotAI* ai) : CombatStrategy(ai)
{
    factoryInternal = new WarlockDebuffStrategyActionNodeFactory();
    actionNodeFactories.Add(factoryInternal);
}

WarlockDebuffStrategy::~WarlockDebuffStrategy()
{
    actionNodeFactories.Remove(factoryInternal);
    delete factoryInternal;
}

void WarlockDebuffStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{

     triggers.push_back(new TriggerNode(
        "curse on attacker",
        NextAction::array(0, new NextAction("curse of the elements on attacker", 12.0f), NULL)));

     triggers.push_back(new TriggerNode(
        "no curse",
        NextAction::array(0, new NextAction("curse of the elements", 30.0f), NULL)));
}


class DpsWarlockDebuffStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    DpsWarlockDebuffStrategyActionNodeFactory()
    {
        creators["curse of agony on attacker"] = curse_of_agony;
    }
    ~DpsWarlockDebuffStrategyActionNodeFactory()
    {
        creators.erase("curse of agony on attacker");
    }
private:
    static ActionNode* curse_of_agony(PlayerbotAI* ai)
    {
        return new ActionNode ("curse of agony on attacker",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
};

DpsWarlockDebuffStrategy::DpsWarlockDebuffStrategy(PlayerbotAI* ai) : CombatStrategy(ai)
{
    factoryInternal = new DpsWarlockDebuffStrategyActionNodeFactory();
    actionNodeFactories.Add(factoryInternal);
}

DpsWarlockDebuffStrategy::~DpsWarlockDebuffStrategy()
{
    actionNodeFactories.Remove(factoryInternal);
    delete factoryInternal;
}

void DpsWarlockDebuffStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "curse on attacker",
        NextAction::array(0, new NextAction("curse of agony on attacker", 12.0f), NULL)));

  triggers.push_back(new TriggerNode(
        "no curse",
        NextAction::array(0, new NextAction("curse of agony", 25.0f), NULL)));
}


class DpsFireWarlockStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    DpsFireWarlockStrategyActionNodeFactory()
    {
        creators["shadow bolt"] = &shadow_bolt;
        creators["summon imp"] = &summon_imp;
        creators["incinerate"] = &incinerate;
    }
    ~DpsFireWarlockStrategyActionNodeFactory()
    {
        creators.erase("shadow bolt");
        creators.erase("summon imp");
        creators.erase("incinerate");
    }
private:
    static ActionNode* summon_imp(PlayerbotAI* ai)
    {
        return new ActionNode ("summon imp",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("life tap"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* incinerate(PlayerbotAI* ai)
    {
        return new ActionNode ("incinerate",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("shadow bolt"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* shadow_bolt(PlayerbotAI* ai)
    {
        return new ActionNode ("shadow bolt",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("shoot"), NULL),
            /*C*/ NULL);
    }
};

DpsFireWarlockStrategy::DpsFireWarlockStrategy(PlayerbotAI* ai) : GenericWarlockStrategy(ai)
{
    factoryInternal = new DpsWarlockStrategyActionNodeFactory();
    actionNodeFactories.Add(factoryInternal);
}

DpsFireWarlockStrategy::~DpsFireWarlockStrategy()
{
    actionNodeFactories.Remove(factoryInternal);
    delete factoryInternal;
    delete defaultActions;
}

NextAction** DpsFireWarlockStrategy::getDefaultActions()
{
    defaultActions = NextAction::array(0,new NextAction("conflagrate", 20.0f), new NextAction("chaos bolt", 15.0f), new NextAction("life tap", 13.0f),  new NextAction("incinerate", 12.0f), NULL);
    return defaultActions;
}

void DpsFireWarlockStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericWarlockStrategy::InitTriggers(triggers);

	triggers.push_back(new TriggerNode(
		"shadow trance",
		NextAction::array(0, new NextAction("shadow bolt", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
		"shadow mastery",
		NextAction::array(0, new NextAction("shadow bolt", 21.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"backlash",
		NextAction::array(0, new NextAction("incinerate", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "immolate on attacker",
        NextAction::array(0, new NextAction("immolate on attacker", 25.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "immolate",
        NextAction::array(0, new NextAction("immolate", 29.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "molten core",
        NextAction::array(0, new NextAction("incinerate", 18.0f), new NextAction("incinerate", 18.0f), new NextAction("incinerate", 18.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "decimation",
        NextAction::array(0, new NextAction("soul fire", 18.0f), new NextAction("soul fire", 18.0f), NULL)));
}

void DpsFireAoeWarlockStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "high aoe",
        NextAction::array(0, new NextAction("rain of fire", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "light aoe",
        NextAction::array(0, new NextAction("shadowfury", 29.0f), NULL)));
}


