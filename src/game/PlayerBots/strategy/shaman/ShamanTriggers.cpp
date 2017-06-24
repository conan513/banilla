#include "../../../botpch.h"
#include "../../playerbot.h"
#include "ShamanTriggers.h"
#include "ShamanActions.h"

using namespace ai;

list<string> ShamanWeaponTrigger::spells;

bool ShamanWeaponTrigger::IsActive()
{
/*
    if (spells.empty())
    {
        spells.push_back("frostbrand weapon");
        spells.push_back("rockbiter weapon");
        spells.push_back("flametongue weapon");
        spells.push_back("earthliving weapon");
        spells.push_back("windfury weapon");
    }

    for (list<string>::iterator i = spells.begin(); i != spells.end(); ++i)
    {
        uint32 spellId = AI_VALUE2(uint32, "spell id", spell);
        if (!spellId)
            continue;

        if (AI_VALUE2(Item*, "item for spell", spellId))
        {
            if (AI_VALUE2(bool, "mainhand enhanced", "self target") &&  AI_VALUE2(bool, "offhand enhanced", "self target"))
                return true;
        }
    }

    return false;

   // return SpellTrigger::IsActive()
   //         && !ai->HasAnyAuraOf(GetTarget(), "frostbrand weapon", "rockbiter weapon", "flametongue weapon", "earthliving weapon", "windfury weapon", NULL);


    return // && !ai->HasAnyAuraOf(GetTarget(), "frostbrand weapon", "rockbiter weapon", "flametongue weapon", "earthliving weapon", "windfury weapon", NULL);
    */

    return !(AI_VALUE2(bool, "mainhand enhanced", "self target") && AI_VALUE2(bool, "offhand enhanced", "self target"));
}

bool ShockTrigger::IsActive()
{
    return SpellTrigger::IsActive()
            && !ai->HasAnyAuraOf(GetTarget(), "frost shock", "earth shock", "flame shock", NULL);
}
