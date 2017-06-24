#include "../../../botpch.h"
#include "../../playerbot.h"
#include "DisperseStrategy.h"

using namespace ai;

void DisperseStrategy::InitTriggers(list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "group member near",
        NextAction::array(0, new NextAction("disperse", 50.0f), NULL)));
}
