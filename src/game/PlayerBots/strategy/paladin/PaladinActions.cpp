#include "../../../botpch.h"
#include "../../playerbot.h"
#include "PaladinActions.h"

using namespace ai;

bool CastBlessingOfWisdomOnPartyAction::isUseful()
{
    Unit* player = GetTarget();
    if (player)
    {
    switch (player->getClass())
    {
        case CLASS_WARRIOR:
        case CLASS_ROGUE:
            return false;
        case CLASS_DRUID:
            return !ai->HasAnyAuraOf(player, "bear form", "dire bear form", "cat form", NULL);
    }
    return true;
    }
    return false;
}

bool CastBlessingOfMightOnPartyAction::isUseful()
{
    Unit* player = GetTarget();
    if (player)
    {
        if (ai->HasAura("blessing of might", player))
            return false;

        switch (player->getClass())
        {
        case CLASS_WARRIOR:
        case CLASS_ROGUE:
            return true;
        case CLASS_DRUID:
            return ai->HasAnyAuraOf(player, "bear form", "dire bear form", "cat form", NULL);
        }
        return false;
    }
    else return false;
}

bool CastBeaconOfLightActionOnParty::isUseful()
{
    Unit* player = GetTarget();

    if (player)
    {
        switch (player->getClass())
        {
            case CLASS_WARRIOR:
                return ai->HasAura("defensive stance", player);
            case CLASS_PALADIN:
                return ai->HasAnyAuraOf(player, "blessing of sanctuary", "devotion aura", NULL);
            case CLASS_DRUID:
                return ai->HasAnyAuraOf(player, "bear form", "dire bear form",  NULL);
        }
            return false;
    }
    else return false;
}

bool CastBlessingOfSanctuaryOnPartyAction::isUseful()
{
    Unit* player = GetTarget();
    if (player)
     return !ai->HasAura("blessing of kings", player);
    else return false;
}

bool  CastSealOfCommandAction::isUseful()
{
     return (AI_VALUE(uint8, "melee attacker count") >= 2);
}

bool  CastSealOfWisdomAction::isUseful()
{
      return (AI_VALUE2(uint8, "mana", "self target") <= sPlayerbotAIConfig.lowMana);
}

bool  CastSealOfLightAction::isUseful()
{
    return (AI_VALUE2(uint8, "health", "self target") <= sPlayerbotAIConfig.lowHealth);
}

bool  CastSealOfVengeanceAction::isUseful()
{
     return (AI_VALUE(uint8, "melee attacker count") < 2);
}

bool CastInstantFlashOfLightAction::isUseful()
{
    return ai->HasAura("art of war",bot);
}

bool CastInstantFlashOfLightAction::Execute(Event event)
{
    return ai->CastSpell("flash of light", GetTarget());
}

bool CastInstantExorcismAction::isUseful()
{
    return ai->HasAura("art of war",bot);
}

bool CastInstantExorcismAction::Execute(Event event)
{
    return ai->CastSpell("exorcism", GetTarget());
}

bool CastExorcismHealAction::Execute(Event event)
{
    return ai->CastSpell("exorcism", GetTarget());
}

bool CastInstantFlashOfLightOnPartyAction::isUseful()
{
    return ai->HasAura("art of war",bot);
}

bool CastInstantFlashOfLightOnPartyAction::Execute(Event event)
{
    return ai->CastSpell("flash of light", GetTarget());
}

bool CastInstantFlashOfLightOnMasterAction::isUseful()
{
    return ai->HasAura("art of war",bot);
}

bool CastInstantFlashOfLightOnMasterAction::Execute(Event event)
{
    return ai->CastSpell("flash of light", GetTarget());
}
