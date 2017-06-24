#include "../../../botpch.h"
#include "../../playerbot.h"
#include "WarlockMultipliers.h"
#include "TankWarlockStrategy.h"

using namespace ai;

class GenericWarlockStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    GenericWarlockStrategyActionNodeFactory()
    {
        creators["summon voidwalker"] = &summon_voidwalker;
        creators["summon felguard"] = &summon_felguard;
        creators["boost"] = &demonic_empowerment;
    }
private:
    static ActionNode* summon_voidwalker(PlayerbotAI* ai)
    {
        return new ActionNode ("summon voidwalker",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("drain soul"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* summon_felguard(PlayerbotAI* ai)
    {
        return new ActionNode ("summon felguard",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("summon voidwalker"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* demonic_empowerment(PlayerbotAI* ai)
    {
        return new ActionNode ("demonic empowerment",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
};

TankWarlockStrategy::TankWarlockStrategy(PlayerbotAI* ai) : GenericWarlockStrategy(ai)
{
    actionNodeFactories.Add(new GenericWarlockStrategyActionNodeFactory());
}

NextAction** TankWarlockStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("shadow bolt", 10.0f), NULL);
}

void TankWarlockStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericWarlockStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "no pet",
        NextAction::array(0, new NextAction("summon felguard", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "demon dead",
        NextAction::array(0, new NextAction("fel domination", 50.0f),  new NextAction("summon felguard", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium threat",
        NextAction::array(0, new NextAction("demonic empowerment", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "corruption on attacker",
        NextAction::array(0, new NextAction("corruption on attacker", 25.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "corruption",
        NextAction::array(0, new NextAction("corruption", 15.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "immolate",
        NextAction::array(0, new NextAction("immolate", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "molten core",
        NextAction::array(0, new NextAction("incinerate", 18.0f), new NextAction("incinerate", 18.0f), new NextAction("incinerate", 18.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "decimation",
        NextAction::array(0, new NextAction("soul fire", 18.0f), new NextAction("soul fire", 18.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "no curse",
        NextAction::array(0, new NextAction("curse of weakness", 18.0f), NULL)));
}
