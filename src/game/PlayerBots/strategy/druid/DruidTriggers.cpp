#include "../../../botpch.h"
#include "../../playerbot.h"
#include "DruidTriggers.h"
#include "DruidActions.h"

using namespace ai;

bool ThornsOnPartyTrigger::IsActive()
{
	Unit* player = GetTarget();
    if (player)
    {
        switch (player->getClass())
        {
            case CLASS_DEATH_KNIGHT:
                return ai->HasAura("frost presence", player);
            case CLASS_WARRIOR:
                return ai->HasAura("defensive stance", player);
            case CLASS_PALADIN:
                return ai->HasAnyAuraOf(player, "blessing of sanctuary", "devotion aura", NULL);
            case CLASS_DRUID:
                return ai->HasAnyAuraOf(player, "bear form", "dire bear form", "moonkin form", NULL);
        }
            return false;
    }
    else return false;
}
