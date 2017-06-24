#include "../../../botpch.h"
#include "../../playerbot.h"
#include "HunterTriggers.h"
#include "HunterActions.h"

using namespace ai;

bool HunterNoStingsActiveTrigger::IsActive()
{
	Unit* target = AI_VALUE(Unit*, "current target");
    return target && AI_VALUE2(uint8, "health", "current target") > 10 &&
        !ai->HasAura("serpent sting", target) &&
        !ai->HasAura("scorpid sting", target) &&
        !ai->HasAura("viper sting", target);
}

bool HuntersPetDeadTrigger::IsActive()
{
    Unit* pet = AI_VALUE(Unit*, "pet target");
	return AI_VALUE(bool, "pet dead") && !AI_VALUE2(bool, "mounted", "self target");
}


bool HuntersPetLowHealthTrigger::IsActive()
{
    Unit* pet = AI_VALUE(Unit*, "pet target");
    return pet && AI_VALUE2(uint8, "health", "pet target") < 40 &&
        !AI_VALUE2(bool, "dead", "pet target") && !AI_VALUE2(bool, "mounted", "self target");
}

bool HunterAspectOfTheDragonHawkTrigger::IsActive()
{
    Unit* target = GetTarget();
    return !ai->HasAura("aspect of the dragonhawk", target) &&
        (AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig.lowMana) && BuffTrigger::IsActive();
}

bool HunterAspectOfTheHawkTrigger::IsActive()
{
    Unit* target = GetTarget();
    return !ai->HasAura("aspect of the dragonhawk", target) &&
        !ai->HasAura("aspect of the hawk", target) &&
        (AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig.lowMana);
}
