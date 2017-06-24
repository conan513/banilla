#include "../../../botpch.h"
#include "../../playerbot.h"
#include "MageMultipliers.h"
#include "FrostMageStrategy.h"

using namespace ai;

class FrostMageStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    FrostMageStrategyActionNodeFactory()
    {
        creators["ice veins"] = &ice_veins;
        creators["frostbolt"] = &frostbolt;
        creators["summon water elemental"] = &summon_water_elemental;
        creators["deep freeze"] = &deep_freeze;
        creators["ice barrier"] = &ice_barrier;
        creators["cold snap"] = &cold_snap;
    }
private:
    static ActionNode* ice_veins(PlayerbotAI* ai)
    {
        return new ActionNode ("ice veins",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("cold snap"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* frostbolt(PlayerbotAI* ai)
    {
        return new ActionNode ("frostbolt",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("ice lance"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* ice_block(PlayerbotAI* ai)
    {
        return new ActionNode ("ice block",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("cold snap"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* summon_water_elemental(PlayerbotAI* ai)
    {
        return new ActionNode ("summon water elemental",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* deep_freeze(PlayerbotAI* ai)
    {
        return new ActionNode ("deep_freeze",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("frostbolt"), NULL),
            /*C*/ NextAction::array(0, new NextAction("ice lance"), NULL));
    }

     static ActionNode* ice_barrier(PlayerbotAI* ai)
    {
        return new ActionNode ("ice barrier",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("mana shield"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* cold_snap(PlayerbotAI* ai)
    {
        return new ActionNode ("cold snap",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
};

FrostMageStrategy::FrostMageStrategy(PlayerbotAI* ai) : GenericMageStrategy(ai)
{
    actionNodeFactories.Add(new FrostMageStrategyActionNodeFactory());
}

NextAction** FrostMageStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("deep freeze", 8.0f), new NextAction("frostbolt", 7.0f), NULL);
}

void FrostMageStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericMageStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "icy veins",
        NextAction::array(0, new NextAction("icy veins", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "fingers of cold",
        NextAction::array(0, new NextAction("deep freeze", 50.0f), new NextAction("frostbolt", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "brain freeze",
        NextAction::array(0, new NextAction("frostfire bolt", 50.0f),NULL)));

    triggers.push_back(new TriggerNode(
        "target frozen",
        NextAction::array(0, new NextAction("frostbolt", 60.0f), new NextAction("ice lance", 50.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "summon water elemental",
        NextAction::array(0, new NextAction("summon water elemental", 60.0f),NULL)));

    triggers.push_back(new TriggerNode(
		"critical health",
		NextAction::array(0, new NextAction("ice block", 80.0f), NULL)));

    triggers.push_back(new TriggerNode(
		"medium health",
		NextAction::array(0, new NextAction("ice barrier", 71.0f), NULL)));
}

void FrostMageAoeStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		"high aoe",
		NextAction::array(0, new NextAction("blizzard", 40.0f), NULL)));

        triggers.push_back(new TriggerNode(
        "melee light aoe",
        NextAction::array(0, new NextAction("cone of cold", ACTION_HIGH + 3), NULL)));

		triggers.push_back(new TriggerNode(
        "enemy too close for spell",
        NextAction::array(0, new NextAction("cone of cold", 70.0f), NULL)));
}
