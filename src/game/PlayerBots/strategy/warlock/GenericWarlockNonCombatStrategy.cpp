#include "../../../botpch.h"
#include "../../playerbot.h"
#include "WarlockMultipliers.h"
#include "GenericWarlockNonCombatStrategy.h"

using namespace ai;

class GenericWarlockNonCombatStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    GenericWarlockNonCombatStrategyActionNodeFactory()
    {
        creators["fel armor"] = &fel_armor;
        creators["demon armor"] = &demon_armor;
    }
private:
    static ActionNode* fel_armor(PlayerbotAI* ai)
    {
        return new ActionNode ("fel armor",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("demon armor"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* demon_armor(PlayerbotAI* ai)
    {
        return new ActionNode ("demon armor",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("demon skin"), NULL),
            /*C*/ NULL);
    }
};

GenericWarlockNonCombatStrategy::GenericWarlockNonCombatStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai)
{
    actionNodeFactories.Add(new GenericWarlockNonCombatStrategyActionNodeFactory());
}

void GenericWarlockNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "demon armor",
        NextAction::array(0, new NextAction("fel armor", 21.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"no healthstone",
		NextAction::array(0, new NextAction("create healthstone", 15.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"no firestone",
		NextAction::array(0, new NextAction("create firestone", 14.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"no spellstone",
		NextAction::array(0, new NextAction("create spellstone", 13.0f), NULL)));

    triggers.push_back(new TriggerNode(
		"no soulstone",
		NextAction::array(0, new NextAction("create soulstone", 13.0f), NULL)));

    triggers.push_back(new TriggerNode(
		"no soulstone on master",
		NextAction::array(0, new NextAction("soulstone on master", 13.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"in battleground without flag",
		NextAction::array(0, new NextAction("mount", 1.0f), NULL)));
}

class WarlockImpStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    WarlockImpStrategyActionNodeFactory()
    {
        creators["summon imp"] = &summon_imp;
        }
private:
    static ActionNode* summon_imp(PlayerbotAI* ai)
    {
        return new ActionNode ("summon imp",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("drink"), NULL),
            /*C*/ NULL);
    }
};

WarlockImpStrategy::WarlockImpStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai)
{
    actionNodeFactories.Add(new WarlockImpStrategyActionNodeFactory());
}

void WarlockImpStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
        triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon imp", 60.0f), NULL)));

        triggers.push_back(new TriggerNode(
        "mainhand not enhanced",
        NextAction::array(0, new NextAction("firestone", 50.0f), NULL)));
}

class WarlockVoidwalkerActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    WarlockVoidwalkerActionNodeFactory()
    {
        creators["summon voidwalker"] = &summon_voidwalker;
        }
private:
    static ActionNode* summon_voidwalker(PlayerbotAI* ai)
    {
        return new ActionNode ("summon voidwalker",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("drink"), NULL),
            /*C*/ NULL);
    }
};

WarlockVoidwalkerStrategy::WarlockVoidwalkerStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai)
{
    actionNodeFactories.Add(new WarlockVoidwalkerActionNodeFactory());
}


void WarlockVoidwalkerStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
        triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon voidwalker", 60.0f), NULL)));

        triggers.push_back(new TriggerNode(
        "mainhand not enhanced",
        NextAction::array(0, new NextAction("spellstone", 50.0f), NULL)));
}

class WarlockSuccubusActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    WarlockSuccubusActionNodeFactory()
    {
        creators["summon succubus"] = &summon_succubus;
        }
private:
    static ActionNode* summon_succubus(PlayerbotAI* ai)
    {
        return new ActionNode ("summon succubus",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("drink"), NULL),
            /*C*/ NULL);
    }
};

WarlockSuccubusStrategy::WarlockSuccubusStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai)
{
    actionNodeFactories.Add(new WarlockSuccubusActionNodeFactory());
}


void WarlockSuccubusStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
        triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon succubus", 60.0f), NULL)));

        triggers.push_back(new TriggerNode(
        "mainhand not enhanced",
        NextAction::array(0, new NextAction("spellstone", 50.0f), NULL)));
}

class WarlockFelhunterActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    WarlockFelhunterActionNodeFactory()
    {
        creators["summon felhunter"] = &summon_felhunter;
        }
private:
    static ActionNode* summon_felhunter(PlayerbotAI* ai)
    {
        return new ActionNode ("summon felhunter",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("drink"), NULL),
            /*C*/ NULL);
    }
};

WarlockFelhunterStrategy::WarlockFelhunterStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai)
{
    actionNodeFactories.Add(new WarlockFelhunterActionNodeFactory());
}

void WarlockFelhunterStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
        triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon felhunter", 60.0f), NULL)));

        triggers.push_back(new TriggerNode(
        "mainhand not enhanced",
        NextAction::array(0, new NextAction("spellstone", 50.0f), NULL)));
}

class WarlockFelguardStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    WarlockFelguardStrategyActionNodeFactory()
    {
        creators["summon felguard"] = &summon_felguard;
        creators["summon voidwalker"] = &summon_void_walker;
        }
private:
    static ActionNode* summon_felguard(PlayerbotAI* ai)
    {
        return new ActionNode ("summon felguard",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("summon voidwalker"), NULL),
            /*C*/ NULL);
    }

    static ActionNode* summon_void_walker(PlayerbotAI* ai)
    {
        return new ActionNode ("summon voidwalker",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("drink"), NULL),
            /*C*/ NULL);
    }
};

WarlockFelguardStrategy::WarlockFelguardStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai)
{
    actionNodeFactories.Add(new WarlockFelguardStrategyActionNodeFactory());
}

void WarlockFelguardStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
        triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon felguard", 60.0f), NULL)));

        triggers.push_back(new TriggerNode(
        "mainhand not enhanced",
        NextAction::array(0, new NextAction("firestone", 50.0f), NULL)));
}
