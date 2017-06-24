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

	SpellProto const *SpellProto = sSpellMgr->GetSpellProto(spellid);
	if (!SpellProto)
		return true; // there can be known alternatives

	if (SpellProto->Attributes & SPELL_ATTR0_ON_NEXT_SWING ||
		SpellProto->Attributes & SPELL_ATTR0_ON_NEXT_SWING_2)
	{
		Spell* spell = bot->GetCurrentSpell(CURRENT_MELEE_SPELL);
		if (spell && spell->m_SpellProto->Id == spellid && spell->IsNextMeleeSwingSpell() && bot->HasUnitState(UNIT_STATE_MELEE_ATTACKING))
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

	if (SpellProto->IsAutoRepeatRangedSpell() && bot->GetCurrentSpell(CURRENT_AUTOREPEAT_SPELL) &&
            bot->GetCurrentSpell(CURRENT_AUTOREPEAT_SPELL)->m_SpellProto->Id == spellid)
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
