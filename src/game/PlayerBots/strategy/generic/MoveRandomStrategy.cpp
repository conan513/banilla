#include "../../../botpch.h"
#include "../../playerbot.h"
#include "MoveRandomStrategy.h"

using namespace ai;

void MoveRandomStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "very often",
        NextAction::array(0, new NextAction("move random", 2.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"very often",
		NextAction::array(0, new NextAction("move to guestgiver", 3.f), NULL)));

	triggers.push_back(new TriggerNode(
		"often",
		NextAction::array(0, new NextAction("move to guestender", 4.f), NULL)));

	triggers.push_back(new TriggerNode(
		"often",
		NextAction::array(0, new NextAction("move to quest", 5.f), NULL)));
}

