#include "../../../botpch.h"
#include "../../playerbot.h"
#include "WarriorMultipliers.h"
#include "GenericWarriorNonCombatStrategy.h"

using namespace ai;

void GenericWarriorNonCombatStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    NonCombatStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "battle stance",
        NextAction::array(0, new NextAction("battle stance", 11.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "vigilance",
        NextAction::array(0, new NextAction("vigilance on master", 21.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"in battleground without flag",
		NextAction::array(0, new NextAction("mount", 1.0f), NULL)));
}
