#include "../../../botpch.h"
#include "../../playerbot.h"
#include "PriestTriggers.h"
#include "PriestActions.h"

using namespace ai;

bool DivineSpiritTrigger:: IsActive()
{
    return (BuffTrigger::IsActive() && bot->getLevel() > 39);
    };

bool DivineSpiritOnPartyTrigger:: IsActive()
{
    return (BuffOnPartyTrigger::IsActive() && bot->getLevel() > 39);
    };

bool PrayerOfShadowProtectionTrigger:: IsActive()
{
    return (BuffTrigger::IsActive() && bot->getLevel() > 39);
    };

bool PrayerOfShadowProtectionOnPartyTrigger:: IsActive()
{
    return (BuffOnPartyTrigger::IsActive() && bot->getLevel() > 39);
    };
