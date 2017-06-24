#include "../../../botpch.h"
#include "../../playerbot.h"
#include "MageMultipliers.h"
#include "ArcaneMageStrategy.h"

using namespace ai;

class ArcaneMageStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    ArcaneMageStrategyActionNodeFactory()
    {
        creators["arcane blast"] = &arcane_blast;
        creators["arcane barrage"] = &arcane_barrage;
        creators["arcane missiles"] = &arcane_missiles;
        creators["boost"] = &arcane_power;
    }
private:
    static ActionNode* arcane_blast(PlayerbotAI* ai)
    {
        return new ActionNode ("arcane blast",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("arcane missiles"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* arcane_barrage(PlayerbotAI* ai)
    {
        return new ActionNode ("arcane barrage",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("arcane missiles"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* arcane_missiles(PlayerbotAI* ai)
    {
        return new ActionNode ("arcane missiles",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("shoot"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* arcane_power(PlayerbotAI* ai)
    {
        return new ActionNode ("arcane power",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("presence of mind"), NULL),
            /*C*/ NULL);
    }
};

ArcaneMageStrategy::ArcaneMageStrategy(PlayerbotAI* ai) : GenericMageStrategy(ai)
{
    actionNodeFactories.Add(new ArcaneMageStrategyActionNodeFactory());
}

NextAction** ArcaneMageStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("arcane barrage", 10.0f), NULL);
}

void ArcaneMageStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericMageStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "arcane blast",
        NextAction::array(0, new NextAction("arcane blast", 15.0f), NULL)));

     triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("mana shield", 15.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "missile barrage",
        NextAction::array(0, new NextAction("arcane missiles", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "boost",
        NextAction::array(0, new NextAction("arcane power", 40.0f), new NextAction("icy veins", 40.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "burst",
        NextAction::array(0, new NextAction("presence of mind", 40.0f), new NextAction("pyroblast", 40.0f),NULL)));

    triggers.push_back(new TriggerNode(
        "slow",
        NextAction::array(0, new NextAction("slow", 30.0f), NULL)));
}

void ArcaneMageAoeStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "enemy too close for spell",
        NextAction::array(0, new NextAction("mana shield", 60.0f), new NextAction("cone of cold", 60.0f), NULL)));

        triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("cone of cold", ACTION_HIGH + 3), NULL)));

        triggers.push_back(new TriggerNode(
		"high aoe",
		NextAction::array(0, new NextAction("arcane explosion", 30.0f), NULL)));
}
