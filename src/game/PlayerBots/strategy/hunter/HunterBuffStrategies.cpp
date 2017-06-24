#include "../../../botpch.h"
#include "../../playerbot.h"
#include "HunterMultipliers.h"
#include "HunterBuffStrategies.h"

using namespace ai;

class HunterBuffDpsStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    HunterBuffDpsStrategyActionNodeFactory()
    {
        creators["aspect of the dragonhawk"] = &aspect_of_the_dragonhawk;
        creators["aspect of the hawk"] = &aspect_of_the_hawk;
    }
private:
    static ActionNode* aspect_of_the_dragonhawk(PlayerbotAI* ai)
    {
        return new ActionNode ("aspect of the dragonhawk",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("aspect of the hawk"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* aspect_of_the_hawk(PlayerbotAI* ai)
    {
        return new ActionNode ("aspect of the hawk",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("aspect of the monkey"), NULL),
            /*C*/ NULL);
    }
};

HunterBuffDpsStrategy::HunterBuffDpsStrategy(PlayerbotAI* ai) : NonCombatStrategy(ai)
{
    actionNodeFactories.Add(new HunterBuffDpsStrategyActionNodeFactory());
}

void HunterBuffDpsStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		"aspect of the dragonhawk",
		NextAction::array(0, new NextAction("aspect of the dragonhawk", 90.0f), NULL)));

        triggers.push_back(new TriggerNode(
		"aspect of the hawk",
		NextAction::array(0, new NextAction("aspect of the hawk", 90.0f), NULL)));

        triggers.push_back(new TriggerNode(
		"aspect of the viper",
		NextAction::array(0, new NextAction("aspect of the viper", 90.0f), NULL)));
}

void HunterNatureResistanceStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		"aspect of the wild",
		NextAction::array(0, new NextAction("aspect of the wild", 90.0f), NULL)));
}


void HunterBuffSpeedStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "aspect of the pack",
        NextAction::array(0, new NextAction("aspect of the pack", 10.0f), NULL)));
}

void HunterBuffManaStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
		"aspect of the dragonhawk",
		NextAction::array(0, new NextAction("aspect of the dragonhawk", 90.0f), NULL)));

    triggers.push_back(new TriggerNode(
		"aspect of the hawk",
		NextAction::array(0, new NextAction("aspect of the hawk", 90.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "aspect of the viper",
        NextAction::array(0, new NextAction("aspect of the viper", 10.0f), NULL)));
}
