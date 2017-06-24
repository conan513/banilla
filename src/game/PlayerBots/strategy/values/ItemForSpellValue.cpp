#include "../../../botpch.h"
#include "../../playerbot.h"
#include "ItemForSpellValue.h"

using namespace ai;

#ifndef WIN32
inline int strcmpi(const char* s1, const char* s2)
{
    for (; *s1 && *s2 && (toupper(*s1) == toupper(*s2)); ++s1, ++s2);
    return *s1 - *s2;
}
#endif

Item* ItemForSpellValue::Calculate()
{
    uint32 spellid = atoi(qualifier.c_str());
    if (!spellid)
        return NULL;

    SpellProto const *SpellProto = sSpellMgr->GetSpellProto(spellid);
    if (!SpellProto)
        return NULL;

    Item* itemForSpell = NULL;
    Player* trader = bot->GetTrader();
    if (trader)
    {
        itemForSpell = trader->GetTradeData()->GetItem(TRADE_SLOT_NONTRADED);
        if (itemForSpell && itemForSpell->IsFitToSpellRequirements(SpellProto))
            return itemForSpell;
    }

    // Workaround as some spells have no item mask (e.g. shaman weapon enhancements)
    if (!strcmpi(SpellProto->SpellName[0], "rockbiter weapon") ||
            !strcmpi(SpellProto->SpellName[0], "flametongue weapon") ||
            !strcmpi(SpellProto->SpellName[0], "earthliving weapon") ||
            !strcmpi(SpellProto->SpellName[0], "frostbrand weapon") ||
            !strcmpi(SpellProto->SpellName[0], "windfury weapon"))
    {
        itemForSpell = GetItemFitsToSpellRequirements(EQUIPMENT_SLOT_MAINHAND, SpellProto);
        if (itemForSpell && itemForSpell->GetProto()->Class == ITEM_CLASS_WEAPON)
            return itemForSpell;

        itemForSpell = GetItemFitsToSpellRequirements(EQUIPMENT_SLOT_OFFHAND, SpellProto);
        if (itemForSpell && itemForSpell->GetProto()->Class == ITEM_CLASS_WEAPON)
            return itemForSpell;

        return NULL;
    }

    for( uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++ ) {
        itemForSpell = GetItemFitsToSpellRequirements(slot, SpellProto);
        if (itemForSpell)
            return itemForSpell;
    }
    return NULL;
}

Item* ItemForSpellValue::GetItemFitsToSpellRequirements(uint8 slot, SpellProto const *SpellProto)
{
    Item* const itemForSpell = bot->GetItemByPos( INVENTORY_SLOT_BAG_0, slot );
    if (!itemForSpell || itemForSpell->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT))
        return NULL;

    if (itemForSpell->IsFitToSpellRequirements(SpellProto))
        return itemForSpell;

    return NULL;
}
