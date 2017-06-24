#include "../../../botpch.h"
#include "../../playerbot.h"
#include "MoveBehindAction.h"
#include "../../PlayerbotAIConfig.h"
#include "../values/Formations.h"

using namespace ai;

bool MoveBehindAction::Execute(Event event)
{
     Unit* target = GetTarget();

    if (!target)
        return false;
    else
        return GetBehind(target);
}

bool MoveBehindAction::isUseful()
{
     Unit* target = GetTarget();

    if (!target)
        return false;
    else
        return AI_VALUE2(bool, "behind", "current target");
}

