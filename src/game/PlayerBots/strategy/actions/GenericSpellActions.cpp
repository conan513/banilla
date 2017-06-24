#include "../../../botpch.h"
#include "../../playerbot.h"
#include "GenericActions.h"

using namespace ai;

bool CastSpellAction::Execute(Event event)
{
	if (spell == "mount")
	{
		if (bot->InBattleGround() && !bot->isInCombat())
		{
			if (!bot->IsMounted())
			{
				//Mounts
				if (bot->getLevel() > 39 && bot->GetTeam() != ALLIANCE)
				{
					return ai->CastSpell(23240, bot);
				}
				if (bot->getLevel() > 39 && bot->GetTeam() != HORDE)
				{
					return ai->CastSpell(23242, bot);
				}
				if (bot->getLevel() > 19 && bot->GetTeam() != ALLIANCE)
				{
					return ai->CastSpell(6899, bot);
				}
				if (bot->getLevel() > 19 && bot->GetTeam() != HORDE)
				{
					return ai->CastSpell(8395, bot);
				}
			}
		}
		return false;
	}
	return ai->CastSpell(spell, GetTarget());
}

bool CastSpellAction::isPossible()
{
    //if (AI_VALUE2(float, "distance", GetTargetName()) > range)
    //    return false;

	//if (ai->IsMoving() && !isInstant())
	//	return false;
	if (spell == "mount" && !bot->IsMounted() && !bot->isInCombat())
		return true;

	if (spell == "mount" && bot->isInCombat())
	{
		bot->Unmount();
		return false;
	}

	Unit* target = GetTarget();

	if (!target)
    {
        target = bot;
        return  ai->CanCastSpell(spell, GetTarget());
    }

	if (!bot->IsWithinLOSInMap(target))
		return false;

	if (!bot->IsFriendlyTo(target) && target->UnderCc() && !target->IsStunned())
	{
		if (target->isFrozen() && bot->getClass() == CLASS_MAGE)
			return  ai->CanCastSpell(spell, GetTarget());
		else return false;
	}

	return ai->CanCastSpell(spell, GetTarget());
}

bool CastSpellAction::isUseful()
{
	if (spell == "mount" && !bot->IsMounted() && !bot->isInCombat())
		return true;

	if (spell == "mount" && bot->isInCombat())
	{
		bot->Unmount();
		return false;
	}

	return GetTarget() && AI_VALUE2(bool, "spell cast useful", spell);
}

bool CastAuraSpellAction::isUseful()
{
	return CastSpellAction::isUseful() && !ai->HasAura(spell, GetTarget());
}

bool CastDebuffSpellAction::isUseful()
{
    if (AI_VALUE(uint8, "balance") > 50)
    {
	if (AI_VALUE2(uint8, "health", "current target") > sPlayerbotAIConfig.almostDead && ((AI_VALUE2(bool, "target normal", "current target") || AI_VALUE2(bool, "target player", "current target"))))
        	return CastSpellAction::isUseful() && !ai->HasAura(spell, GetTarget(), BOT_AURA_DAMAGE);
	}
    else if (AI_VALUE2(uint8, "health", "current target") > sPlayerbotAIConfig.almostDead/2 && AI_VALUE2(bool, "target elite", "current target"))
    {
        	return CastSpellAction::isUseful() && !ai->HasAura(spell, GetTarget(), BOT_AURA_DAMAGE);
	}
    else if (AI_VALUE2(uint8, "health", "current target") > sPlayerbotAIConfig.almostDead/3 && AI_VALUE2(bool, "target boss", "current target"))
    {
    	return CastSpellAction::isUseful() && !ai->HasAura(spell, GetTarget(), BOT_AURA_DAMAGE);
	}
    else return false;
}

bool CastOwnDebuffSpellAction::isUseful()
{
	return CastSpellAction::isUseful() && !ai->HasOwnAura(spell, GetTarget(), BOT_AURA_DAMAGE);
}

bool CastHotSpellAction::isUseful()
{
	return CastSpellAction::isUseful() && !ai->HasAura(spell, GetTarget(), BOT_AURA_HEAL);
}

bool CastEnchantItemAction::isPossible()
{
    if (!CastSpellAction::isPossible())
        return false;

    uint32 spellId = AI_VALUE2(uint32, "spell id", spell);
    return spellId && AI_VALUE2(Item*, "item for spell", spellId);
}

bool CastHealingSpellAction::isUseful()
{
	return CastHotSpellAction::isUseful() && AI_VALUE2(uint8, "health", GetTargetName()) < (100 - estAmount);
}

bool CastAoeHealSpellAction::isUseful()
{
	return CastSpellAction::isUseful() && AI_VALUE2(uint8, "aoe heal", "medium") > 0;
}


Value<Unit*>* CurePartyMemberAction::GetTargetValue()
{
    return context->GetValue<Unit*>("party member to dispel", dispelType);
}

Value<Unit*>* DispelFrozenPartyMemberAction::GetTargetValue()
{
    return context->GetValue<Unit*>("party member dispel frozen");
}

Value<Unit*>* DispelRootPartyMemberAction::GetTargetValue()
{
    return context->GetValue<Unit*>("party member dispel root");
}

Value<Unit*>* DispelSnarePartyMemberAction::GetTargetValue()
{
    return context->GetValue<Unit*>("party member dispel snare");
}

Value<Unit*>* DispelCharmPartyMemberAction::GetTargetValue()
{
    return context->GetValue<Unit*>("party member dispel charm");
}

Value<Unit*>* DispelPossessPartyMemberAction::GetTargetValue()
{
    return context->GetValue<Unit*>("party member dispel possess");
}

Value<Unit*>* DispelPolymorphPartyMemberAction::GetTargetValue()
{
    return context->GetValue<Unit*>("party member dispel polymorph");
}

Value<Unit*>* DispelFearPartyMemberAction::GetTargetValue()
{
    return context->GetValue<Unit*>("party member dispel fear");
}

Value<Unit*>* BuffOnPartyAction::GetTargetValue()
{
    return context->GetValue<Unit*>("party member without aura", spell);
}
