#include "../../../botpch.h"
#include "../../playerbot.h"

#include "HunterMultipliers.h"
#include "DpsHunterStrategy.h"

using namespace ai;

class DpsHunterStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    DpsHunterStrategyActionNodeFactory()
    {
        creators["aimed shot"] = &aimed_shot;
        creators["multi-shot"] = &multi_shot;
        creators["arcane shot"] = &arcane_shot;
        creators["chimera shot"] = &chimera_shot;
        creators["black arrow"] = &black_arrow;
        creators["immolation trap"] = &immolation_trap;
        creators["explosive trap"] = &explosive_trap;
        creators["explosive shot"] = &explosive_shot;
        creators["steady shot"] = &steady_shot;
        creators["viper sting"] = &viper_sting;
    }
    ~DpsHunterStrategyActionNodeFactory()
    {
        creators.erase("aimed shot");
        creators.erase("multi-shot");
        creators.erase("arcane shot");
        creators.erase("chimera shot");
        creators.erase("black arrow");
        creators.erase("immolation trap");
        creators.erase("explosive trap");
        creators.erase("explosive shot");
        creators.erase("steady shot");
        creators.erase("viper sting");
    }
private:
    static ActionNode* viper_sting(PlayerbotAI* ai)
    {
        return new ActionNode ("viper sting",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("mana potion"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* aimed_shot(PlayerbotAI* ai)
    {
        return new ActionNode ("aimed shot",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("arcane shot"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* chimera_shot(PlayerbotAI* ai)
    {
        return new ActionNode ("chimera shot",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("arcane shot"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* explosive_shot(PlayerbotAI* ai)
    {
        return new ActionNode ("explosive shot",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("chimera shot"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* black_arrow(PlayerbotAI* ai)
    {
        return new ActionNode ("black arrow",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("immolation trap"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* immolation_trap(PlayerbotAI* ai)
    {
        return new ActionNode ("immolation trap",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("explosive trap"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* explosive_trap(PlayerbotAI* ai)
    {
        return new ActionNode ("explosive trap",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("freezing trap"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* steady_shot(PlayerbotAI* ai)
    {
        return new ActionNode ("steady shot",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("arcane shot"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* arcane_shot(PlayerbotAI* ai)
    {
        return new ActionNode ("arcane shot",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("multi-shot"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* multi_shot(PlayerbotAI* ai)
    {
        return new ActionNode ("multi-shot",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("auto shot"), NULL),
            /*C*/ NULL);
    }
};

NextAction** DpsHunterStrategy::getDefaultActions()
{
    defaultActions = NextAction::array(0, new NextAction("explosive shot", 18.0f), new NextAction("kill command", 15.0f), new NextAction("aimed shot", 15.0f), new NextAction("steady shot", 12.0f), new NextAction("auto shot", 10.0f), NULL);
    return defaultActions;
}

DpsHunterStrategy::DpsHunterStrategy(PlayerbotAI* ai) : GenericHunterStrategy(ai)
{
    factoryInternal = new DpsHunterStrategyActionNodeFactory();
    actionNodeFactories.Add(factoryInternal);
}

DpsHunterStrategy::~DpsHunterStrategy()
{
    actionNodeFactories.Remove(factoryInternal);
    delete factoryInternal;
    delete defaultActions;
}

void DpsHunterStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericHunterStrategy::InitTriggers(triggers);

	triggers.push_back(new TriggerNode(
		"enemy in melee range",
		NextAction::array(0, new NextAction("freezing trap", ACTION_HIGH + 7), NULL)));

	triggers.push_back(new TriggerNode(
		"enemy too close for spell",
		NextAction::array(0, new NextAction("wing clip", ACTION_HIGH + 6), new NextAction("flee", ACTION_HIGH + 5), new NextAction("concussive shot", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "black arrow",
        NextAction::array(0, new NextAction("black arrow", ACTION_NORMAL + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("viper sting", ACTION_HIGH + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("call pet", ACTION_HIGH + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "hunters pet low health",
        NextAction::array(0, new NextAction("mend pet", ACTION_HIGH + 1), NULL)));
    
    triggers.push_back(new TriggerNode(
        "hunter's mark",
        NextAction::array(0, new NextAction("hunter's mark", ACTION_HIGH + 9), NULL)));

    triggers.push_back(new TriggerNode(
        "kill command",
        NextAction::array(0, new NextAction("kill command", ACTION_NORMAL + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "medium threat",
        NextAction::array(0, new NextAction("intimidation", ACTION_HIGH + 2), NULL)));

     triggers.push_back(new TriggerNode(
        "target critical health",
        NextAction::array(0, new NextAction("kill shot", ACTION_NORMAL + 8), NULL)));
}

class DpsAoeHunterStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    DpsAoeHunterStrategyActionNodeFactory()
    {
        creators["explosive trap"] = &explosive_trap;
    }
    ~DpsAoeHunterStrategyActionNodeFactory()
    {
        creators.erase("explosive trap");
    }
private:
    static ActionNode* explosive_trap(PlayerbotAI* ai)
    {
        return new ActionNode ("explosive trap",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("volley", 20.0f), NULL),
            /*C*/ NULL);
    }
};

DpsAoeHunterStrategy::DpsAoeHunterStrategy(PlayerbotAI* ai) : CombatStrategy(ai)
{
    factoryInternal = new DpsAoeHunterStrategyActionNodeFactory();
    actionNodeFactories.Add(factoryInternal);
}

DpsAoeHunterStrategy::~DpsAoeHunterStrategy()
{
    actionNodeFactories.Remove(factoryInternal);
    delete factoryInternal;
}

void DpsAoeHunterStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "light aoe",
        NextAction::array(0, new NextAction("multi-shot", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
		"melee high aoe",
		NextAction::array(0, new NextAction("explosive trap", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
		"melee light aoe",
		NextAction::array(0, new NextAction("freezing trap", 20.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"high aoe",
		NextAction::array(0, new NextAction("volley", 20.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"serpent sting on attacker",
		NextAction::array(0, new NextAction("serpent sting on attacker", 49.0f), NULL)));
}

void DpsHunterDebuffStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "no stings",
        NextAction::array(0, new NextAction("serpent sting", 50.0f), NULL)));
}
