#include "../../../botpch.h"
#include "../../playerbot.h"
#include "SpellCastUsefulValue.h"
#include "LastSpellCastValue.h"

using namespace ai;

bool SpellCastUsefulValue::Calculate()
{
    uint32 spellid = AI_VALUE2(uint32, "spell id", qualifier);
	if (!spellid)
		return true; // there can be known alternatives

	SpellEntry const *SpellProto = sSpellMgr.GetSpellEntry(spellid);
	if (!SpellProto)
		return true; // there can be known alternatives

	if (SpellProto->Attributes & SPELL_ATTR_ON_NEXT_SWING_1 ||
		SpellProto->Attributes & SPELL_ATTR_ON_NEXT_SWING_2)
	{
		Spell* spell = bot->GetCurrentSpell(CURRENT_MELEE_SPELL);
		if (spell && spell->m_spellInfo->Id == spellid && spell->IsNextMeleeSwingSpell() && bot->hasUnitState(UNIT_STAT_MELEE_ATTACKING))
			return false;
	}
	else
	{
        uint32 lastSpellId = AI_VALUE(LastSpellCast&, "last spell cast").id;
        if (spellid == lastSpellId)
        {
            Spell* const pSpell = bot->FindCurrentSpellBySpellId(lastSpellId);
            if (pSpell)
                return false;
        }
	}

	if (IsAutoRepeatRangedSpell(SpellProto) && bot->GetCurrentSpell(CURRENT_AUTOREPEAT_SPELL) &&
		bot->GetCurrentSpell(CURRENT_AUTOREPEAT_SPELL)->m_spellInfo->Id == spellid)
    {
        return false;
    }

    // TODO: workaround
    if (qualifier == "windfury weapon" || qualifier == "flametongue weapon" || qualifier == "frostbrand weapon" ||
            qualifier == "rockbiter weapon" || qualifier == "earthliving weapon" || qualifier == "spellstone" || qualifier == "firestone"
            || qualifier == "instant poison" || qualifier == "deadly poison" || qualifier == "mind-numbing poison" || qualifier == "crippling poison")
    {
        Item *item = AI_VALUE2(Item*, "item for spell", spellid);
        if (item && item->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT))
            return false;
    }

	return true;
}
