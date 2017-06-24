#include "../../../botpch.h"
#include "../../playerbot.h"
#include "ShamanActions.h"

using namespace ai;

bool CastEarthShieldOnPartyAction::isUseful()
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
                return ai->HasAura("blessing of sanctuary", player);
            case CLASS_DRUID:
                return ai->HasAnyAuraOf(player, "bear form", "dire bear form",  NULL);
        }
            return false;
    }
    else return false;
}

