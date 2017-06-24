#include "../../../botpch.h"
#include "../../playerbot.h"
#include "PaladinTriggers.h"
#include "PaladinActions.h"
#include "../../PlayerbotAIConfig.h"

using namespace ai;

bool SealTrigger::IsActive()
{
	Unit* target = GetTarget();
	return !ai->HasAura("seal of justice", target) &&
        	!ai->HasAura("seal of command", target) &&
        	!ai->HasAura("seal of vengeance", target) &&
		!ai->HasAura("seal of wisdom", target) &&
		!ai->HasAura("seal of righteousness", target) &&
		AI_VALUE2(uint8, "mana", "self target") >= sPlayerbotAIConfig.lowMana;
}

bool SealManaLowTrigger::IsActive()
{
	Unit* target = GetTarget();
	return !ai->HasAura("seal of wisdom", target) && AI_VALUE2(uint8, "mana", "self target") < sPlayerbotAIConfig.lowMana;
}

bool SealLowTrigger::IsActive()
{
	Unit* target = GetTarget();
	return !ai->HasAura("seal of light", target) &&
		AI_VALUE2(uint8, "health", "self target") < sPlayerbotAIConfig.criticalHealth;
}

bool CrusaderAuraTrigger::IsActive()
{
	Unit* target = GetTarget();
	return AI_VALUE2(bool, "mounted", "self target") && !ai->HasAura("crusader aura", target);
}

bool  RighteousFuryTrigger::IsActive()
{
    return ai->IsTank(ai->GetBot());
}
