#include "../../../botpch.h"
#include "../../playerbot.h"
#include "GenericTriggers.h"
#include "../../LootObjectStack.h"
#include "../../PlayerbotAIConfig.h"

using namespace ai;

bool LowManaTrigger::IsActive()
{
    return AI_VALUE2(bool, "has mana", "self target") && AI_VALUE2(uint8, "mana", "self target") < sPlayerbotAIConfig.lowMana;
}

bool MediumManaTrigger::IsActive()
{
    return AI_VALUE2(bool, "has mana", "self target") && AI_VALUE2(uint8, "mana", "self target") < sPlayerbotAIConfig.mediumMana;
}

bool AlmostFullManaTrigger::IsActive()
{
    return AI_VALUE2(bool, "has mana", "self target") && AI_VALUE2(uint8, "mana", "self target") <= sPlayerbotAIConfig.almostFullMana;
}

bool AlmostNoManaTrigger::IsActive()
{
    return AI_VALUE2(bool, "has mana", "self target") && AI_VALUE2(uint8, "mana", "self target") < sPlayerbotAIConfig.almostNoMana;
}

bool FullManaTrigger::IsActive()
{
    return AI_VALUE2(bool, "has mana", "self target") && AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig.almostFullMana;
}

bool DrinkManaTrigger::IsActive()
{
    return AI_VALUE2(bool, "has mana", "self target") && !AI_VALUE2(bool, "combat", "self target") && AI_VALUE2(uint8, "mana", "self target") < sPlayerbotAIConfig.mediumMana;
}

bool RageAvailable::IsActive()
{
    return AI_VALUE2(uint8, "rage", "self target") >= amount;
}

bool EnergyAvailable::IsActive()
{
	return AI_VALUE2(uint8, "energy", "self target") >= amount;
}

bool ComboPointsAvailableTrigger::IsActive()
{
    return AI_VALUE2(uint8, "combo", "current target") >= amount;
}

bool ComboPointAvailableTrigger::IsActive()
{
    return AI_VALUE2(uint8, "combo", "current target") >= amount;
}

bool LoseAggroTrigger::IsActive()
{
    return !AI_VALUE2(bool, "has aggro", "current target") && AI_VALUE2(bool, "combat", "self target");
}

bool HasAggroTrigger::IsActive()
{
    return AI_VALUE2(bool, "has aggro", "current target") && AI_VALUE2(bool, "combat", "self target");
}

bool PanicTrigger::IsActive()
{
    return AI_VALUE2(uint8, "health", "self target") < sPlayerbotAIConfig.criticalHealth &&
		(!AI_VALUE2(bool, "has mana", "self target") || AI_VALUE2(uint8, "mana", "self target") < sPlayerbotAIConfig.lowMana);
}

bool BuffTrigger::IsActive()
{
    Unit* target = GetTarget();
	return SpellTrigger::IsActive() &&
		!ai->HasAura(spell, target) &&
		(!AI_VALUE2(bool, "has mana", "self target") || AI_VALUE2(uint8, "mana", "self target") >= sPlayerbotAIConfig.lowMana);
}

Value<Unit*>* BuffOnPartyTrigger::GetTargetValue()
{
	return context->GetValue<Unit*>("party member without aura", spell);
}

Value<Unit*>* BuffOnMasterTrigger::GetTargetValue()
{
	return context->GetValue<Unit*>("master without aura", spell);
}

Value<Unit*>* DebuffOnAttackerTrigger::GetTargetValue()
{
	return context->GetValue<Unit*>("attacker without aura", spell);
}

Value<Unit*>* OwnDebuffOnAttackerTrigger::GetTargetValue()
{
	return context->GetValue<Unit*>("attacker without own aura", spell);
}

bool NoAttackersTrigger::IsActive()
{
    return !AI_VALUE(Unit*, "current target") && AI_VALUE(uint8, "attacker count") > 0;
}

bool InvalidTargetTrigger::IsActive()
{
    return AI_VALUE2(bool, "invalid target", "current target");
}

bool NoTargetTrigger::IsActive()
{
	return !AI_VALUE(Unit*, "current target");
}

bool MyAttackerCountTrigger::IsActive()
{
    return AI_VALUE(uint8, "my attacker count") >= amount;
}

bool AoeTrigger::IsActive()
{
	return AI_VALUE(uint8, "attacker count") > 1 && AI_VALUE2(Unit*, "cc target", getName()) &&
		!AI_VALUE2(Unit*, "current cc target", getName());
}

bool MeleeAoeTrigger::IsActive()
{
    return AI_VALUE(uint8, "melee attacker count") >= amount;
}

bool DebuffTrigger::IsActive()
{
    if (SpellTrigger::IsActive() &&
		!ai->HasAura(spell, GetTarget(),BOT_AURA_DAMAGE) &&
		(!AI_VALUE2(bool, "has mana", "self target") || AI_VALUE2(uint8, "mana", "self target") >= sPlayerbotAIConfig.lowMana))
    {
     if (AI_VALUE2(bool, "target normal", "current target"))
        return (AI_VALUE2(uint8, "health", "current target") > 30);
     else if (AI_VALUE2(bool, "target boss", "current target"))
        return (AI_VALUE2(uint8, "health", "current target") > 5);
     else return (AI_VALUE2(uint8, "health", "current target") > 20);
    }
    else return false;

    /*
    if (AI_VALUE2(bool, "target normal", "current target"))
        return BuffTrigger::IsActive() && (AI_VALUE2(uint8, "health", "current target") > 30);
    else if (AI_VALUE2(bool, "target boss", "current target"))
        return BuffTrigger::IsActive() && (AI_VALUE2(uint8, "health", "current target") > 5);
    else return BuffTrigger::IsActive() && (AI_VALUE2(uint8, "health", "current target") > 20);
    */
}

bool OwnDebuffTrigger::IsActive()
{
    if (SpellTrigger::IsActive() &&
		!ai->HasOwnAura(spell, GetTarget(),BOT_AURA_DAMAGE) &&
		(!AI_VALUE2(bool, "has mana", "self target") || AI_VALUE2(uint8, "mana", "self target") >= sPlayerbotAIConfig.lowMana))
    {
     if (AI_VALUE2(bool, "target normal", "current target"))
        return (AI_VALUE2(uint8, "health", "current target") > 30);
     else if (AI_VALUE2(bool, "target boss", "current target"))
        return (AI_VALUE2(uint8, "health", "current target") > 5);
     else return (AI_VALUE2(uint8, "health", "current target") > 20);
    }
    else return false;

    /*
    if (AI_VALUE2(bool, "target normal", "current target"))
        return BuffTrigger::IsActive() && (AI_VALUE2(uint8, "health", "current target") > 30);
    else if (AI_VALUE2(bool, "target boss", "current target"))
        return BuffTrigger::IsActive() && (AI_VALUE2(uint8, "health", "current target") > 5);
    else return BuffTrigger::IsActive() && (AI_VALUE2(uint8, "health", "current target") > 20);
    */
}

bool HotTrigger::IsActive()
{
    Unit* target = GetTarget();
	return SpellTrigger::IsActive() &&
		!ai->HasAura(spell, target,BOT_AURA_HEAL) &&
		(!AI_VALUE2(bool, "has mana", "self target") || AI_VALUE2(uint8, "mana", "self target") >= sPlayerbotAIConfig.lowMana);
}

bool SpellTrigger::IsActive()
{
	return GetTarget() && ai->CanCastSpell(spell,GetTarget());
}

bool SpellCanBeCastTrigger::IsActive()
{
	Unit* target = GetTarget();
	return target && ai->CanCastSpell(spell, target);
}

bool RandomTrigger::IsActive()
{
	if (time(0) - lastCheck < sPlayerbotAIConfig.maxWaitForMove / 1000)
		return false;
	
	lastCheck = time(0);
	int k = (int)(probability / sPlayerbotAIConfig.randomChangeMultiplier);
	if (k < 1) k = 1;
	return (rand() % k) == 0;
}

bool AndTrigger::IsActive()
{
    return ls->IsActive() && rs->IsActive();
}

string AndTrigger::getName()
{
    std::string name(ls->getName());
    name = name + " and ";
    name = name + rs->getName();
    return name;
}

bool BoostTrigger::IsActive()
{
	return BuffTrigger::IsActive() && AI_VALUE(uint8, "balance") <= balance;
}

bool SnareTargetTrigger::IsActive()
{
	Unit* target = GetTarget();
	if (target && (target->IsFleeing() || AI_VALUE2(bool, "has aggro", "current target")))
        return DebuffTrigger::IsActive() && AI_VALUE2(bool, "moving", "current target") && !ai->HasAura(spell, target);
    else return false;
}

bool ItemCountTrigger::IsActive()
{
	return AI_VALUE2(uint8, "item count", item) < count;
}

bool InterruptSpellTrigger::IsActive()
{
	return SpellTrigger::IsActive() && ai->IsInterruptableSpellCasting(GetTarget(), getName());
}

bool HasAuraTrigger::IsActive()
{
	return ai->HasAura(getName(), GetTarget());
}

bool HasAuraIdTrigger::IsActive()
{
	return ai->HasAura(spellId, GetTarget());
}

bool TankAoeTrigger::IsActive()
{
	if (!AI_VALUE(uint8, "attacker count"))
		return false;

	Unit* currentTarget = AI_VALUE(Unit*, "current target");
	if (!currentTarget)
		return true;

	Unit* tankTarget = AI_VALUE(Unit*, "tank target");
	if (!tankTarget || currentTarget == tankTarget)
		return false;

	return currentTarget->getVictim() == AI_VALUE(Unit*, "self target");
}

bool IsBehindTargetTrigger::IsActive()
{
    Unit* target = AI_VALUE(Unit*, "current target");
    return target && AI_VALUE2(bool, "behind", "current target");
}

bool IsFrontTargetTrigger::IsActive()
{
    Unit* target = AI_VALUE(Unit*, "current target");
    return target && !AI_VALUE2(bool, "behind", "current target");
}

bool IsNotFacingTargetTrigger::IsActive()
{
    return !AI_VALUE2(bool, "facing", "current target");
}

bool HasCcTargetTrigger::IsActive()
{
    return AI_VALUE(uint8, "attacker count") > 1 && AI_VALUE2(Unit*, "cc target", getName()) &&
        !AI_VALUE2(Unit*, "current cc target", getName());
}

bool HasCcTarget2Trigger::IsActive()
{
    return AI_VALUE(uint8, "attacker count") > 1 && AI_VALUE2(Unit*, "cc target2", getName()) &&
        !AI_VALUE2(Unit*, "current cc target", getName());
}

bool HasCcTarget3Trigger::IsActive()
{
    return AI_VALUE(uint8, "attacker count") > 1 && AI_VALUE2(Unit*, "cc target3", getName()) &&
        !AI_VALUE2(Unit*, "current cc target", getName());
}

bool HasCcTarget4Trigger::IsActive()
{
    return AI_VALUE(uint8, "attacker count") > 1 && AI_VALUE2(Unit*, "cc target4", getName()) &&
        !AI_VALUE2(Unit*, "current cc target", getName());
}

bool HasCcTarget5Trigger::IsActive()
{
    return AI_VALUE(uint8, "attacker count") > 1 && AI_VALUE2(Unit*, "cc target5", getName()) &&
        !AI_VALUE2(Unit*, "current cc target", getName());
}

bool HasCcTarget6Trigger::IsActive()
{
    return AI_VALUE(uint8, "attacker count") > 1 && AI_VALUE2(Unit*, "cc target6", getName()) &&
        !AI_VALUE2(Unit*, "current cc target", getName());
}

bool NoMovementTrigger::IsActive()
{
	return !AI_VALUE2(bool, "moving", "self target");
}

bool NoPossibleTargetsTrigger::IsActive()
{
    list<ObjectGuid> targets = AI_VALUE(list<ObjectGuid>, "possible targets");
    return !targets.size();
}

bool NotLeastHpTargetActiveTrigger::IsActive()
{
    Unit* leastHp = AI_VALUE(Unit*, "least hp target");
    Unit* target = AI_VALUE(Unit*, "current target");
    return leastHp && target != leastHp;
}

bool EnemyPlayerIsAttacking::IsActive()
{
    Unit* enemyPlayer = AI_VALUE(Unit*, "enemy player target");
    Unit* target = AI_VALUE(Unit*, "current target");
    return enemyPlayer && target != enemyPlayer;
}

bool IsSwimmingTrigger::IsActive()
{
    return AI_VALUE2(bool, "swimming", "self target");
}

bool HasNearestAddsTrigger::IsActive()
{
    list<ObjectGuid> targets = AI_VALUE(list<ObjectGuid>, "nearest adds");
    return targets.size();
}

bool  HasGroupMemberNearTrigger::IsActive()
{
    list<ObjectGuid> targets = AI_VALUE(list<ObjectGuid>, "party members near");
    return targets.size();
}

bool MainhandEnhanceTrigger::IsActive()
{
    return !AI_VALUE2(bool, "mainhand enhanced", "self target") && !AI_VALUE2(bool, "mounted", "self target");
}

bool OffhandEnhanceTrigger::IsActive()
{
    return !AI_VALUE2(bool, "offhand enhanced", "self target") && !AI_VALUE2(bool, "mounted", "self target");
}

bool HasItemForSpellTrigger::IsActive()
{
	string spell = getName();
    uint32 spellId = AI_VALUE2(uint32, "spell id", spell);
    return spellId && AI_VALUE2(Item*, "item for spell", spellId);
}


bool TargetChangedTrigger::IsActive()
{
    Unit* oldTarget = context->GetValue<Unit*>("old target")->Get();
    Unit* target = context->GetValue<Unit*>("current target")->Get();
    return target && oldTarget != target;
}

Value<Unit*>* InterruptEnemyHealerTrigger::GetTargetValue()
{
    return context->GetValue<Unit*>("enemy healer target", spell);
}

bool CharmedTrigger::IsActive()
{
    return AI_VALUE2(bool, "charmed", GetTargetName());
}

bool SilencedTrigger::IsActive()
{
    return AI_VALUE2(bool, "silenced", GetTargetName());
}

bool FearedTrigger::IsActive()
{
    return AI_VALUE2(bool, "feared", GetTargetName());
}

bool BleedingTrigger::IsActive()
{
    return AI_VALUE2(bool, "bleeding", GetTargetName());
}

bool PossessedTrigger::IsActive()
{
    return AI_VALUE2(bool, "possessed", GetTargetName());
}

bool DisorientedTrigger::IsActive()
{
    return AI_VALUE2(bool, "disoriented", GetTargetName());
}

bool TakesPeriodicDamageTrigger::IsActive()
{
    return AI_VALUE2(bool, "periodic damage", GetTargetName());
}

bool PolymorphedTrigger::IsActive()
{
    return AI_VALUE2(bool, "polymorphed", GetTargetName());
}

bool SnaredTrigger::IsActive()
{
    return AI_VALUE2(bool, "snared", GetTargetName());
}

bool FrozenTrigger::IsActive()
{
    return AI_VALUE2(bool, "frozen", GetTargetName());
}

bool RootedTrigger::IsActive()
{
    return AI_VALUE2(bool, "rooted", GetTargetName());
}

bool StunnedTrigger::IsActive()
{
    return AI_VALUE2(bool, "stunned", GetTargetName());
}

bool TargetPossessedTrigger::IsActive()
{
    return AI_VALUE2(bool, "possessed", GetTargetName());
}

bool TargetCharmedTrigger::IsActive()
{
    return AI_VALUE2(bool, "charmed", GetTargetName());
}

bool TargetDisorientedTrigger::IsActive()
{
    return AI_VALUE2(bool, "disoriented", GetTargetName());
}

bool TargetBleedingTrigger::IsActive()
{
    return AI_VALUE2(bool, "bleeding", GetTargetName());
}

bool TargetPolymorphedTrigger::IsActive()
{
    return AI_VALUE2(bool, "polymorphed", GetTargetName());
}

bool TargetSnaredTrigger::IsActive()
{
    return AI_VALUE2(bool, "snared", GetTargetName());
}

bool TargetFrozenTrigger::IsActive()
{
    return AI_VALUE2(bool, "frozen", GetTargetName());
}

bool TargetSilencedTrigger::IsActive()
{
    return AI_VALUE2(bool, "silenced", GetTargetName());
}

bool TargetFearedTrigger::IsActive()
{
    return AI_VALUE2(bool, "feared", GetTargetName());
}

bool TargetRootedTrigger::IsActive()
{
    return AI_VALUE2(bool, "rooted", GetTargetName());
}

bool TargetFleeingTrigger::IsActive()
{
    return AI_VALUE2(bool, "fleeing", GetTargetName());
}

bool TargetStunnedTrigger::IsActive()
{
    return AI_VALUE2(bool, "stunned", GetTargetName());
}

bool TargetNotSnaredTrigger::IsActive()
{
    return !AI_VALUE2(bool, "snared", GetTargetName());
}

bool TargetNotFrozenTrigger::IsActive()
{
    return !AI_VALUE2(bool, "frozen", GetTargetName());
}

bool TargetNotBleedingTrigger::IsActive()
{
    return !AI_VALUE2(bool, "bleeding", GetTargetName());
}

bool TargetNotPolymorphedTrigger::IsActive()
{
    return !AI_VALUE2(bool, "polymorphed", GetTargetName());
}

bool TargetNotRootedTrigger::IsActive()
{
    return !AI_VALUE2(bool, "rooted", GetTargetName());
}

bool TargetNotStunnedTrigger::IsActive()
{
    return !AI_VALUE2(bool, "stunned", GetTargetName());
}

Value<Unit*>*  PartyMemberPossessedTrigger::GetTargetValue()
{
	return context->GetValue<Unit*>("party member dispel possess");
}

bool PartyMemberPossessedTrigger::IsActive()
{
	return !AI_VALUE2(bool, "possessed", GetTargetName());
}

Value<Unit*>*  PartyMemberCharmedTrigger::GetTargetValue()
{
	return context->GetValue<Unit*>("party member dispel charm");
}

bool PartyMemberCharmedTrigger::IsActive()
{
	return !AI_VALUE2(bool, "charmed", GetTargetName());
}

Value<Unit*>*  PartyMemberFearedTrigger::GetTargetValue()
{
	return context->GetValue<Unit*>("party member dispel fear");
}

bool PartyMemberFearedTrigger::IsActive()
{
	return !AI_VALUE2(bool, "feared", GetTargetName());
}

Value<Unit*>*  PartyMemberRootedTrigger::GetTargetValue()
{
	return context->GetValue<Unit*>("party member dispel root");
}

bool PartyMemberRootedTrigger::IsActive()
{
	return !AI_VALUE2(bool, "rooted", GetTargetName());
}

Value<Unit*>*  PartyMemberSnaredTrigger::GetTargetValue()
{
	return context->GetValue<Unit*>("party member dispel snare");
}

bool PartyMemberSnaredTrigger::IsActive()
{
	return !AI_VALUE2(bool, "snared", GetTargetName());
}

Value<Unit*>*  PartyMemberPolymorphedTrigger::GetTargetValue()
{
	return context->GetValue<Unit*>("party member dispel polymorph");
}

bool PartyMemberPolymorphedTrigger::IsActive()
{
	return !AI_VALUE2(bool, "polymorphed", GetTargetName());
}

Value<Unit*>*  PartyMemberFrozenTrigger::GetTargetValue()
{
	return context->GetValue<Unit*>("party member dispel frozen");
}

bool PartyMemberFrozenTrigger::IsActive()
{
	return !AI_VALUE2(bool, "frozen", GetTargetName());
}

bool PlayerHasNoFlag::IsActive()
{
	if (ai->GetBot()->InBattleGround())
		{
		if (ai->GetBot()->GetBattleGroundTypeId() == BattleGroundTypeId::BATTLEGROUND_WS)
			{
			BattleGroundWS *bg = (BattleGroundWS*)ai->GetBot()->GetBattleGround();
			if (!(bg->GetFlagState(bg->GetOtherTeam(bot->GetTeam())) == BG_WS_FLAG_STATE_ON_PLAYER))
				 return false;
			if (bot->GetGUID() == bg->GetFlagKeeper(bg->GetOtherTeam(bot->GetTeam()) == ALLIANCE ? TEAM_ALLIANCE : TEAM_HORDE)) //flag-Carrier, bring it home
				{
				return false;
				}
			}
		}
	return true;
	}

bool PlayerIsInBattleGround::IsActive()
{
	return ai->GetBot()->InBattleGround();
	}

bool PlayerIsInBattleGroundWithoutFlag::IsActive()
 {
	if (ai->GetBot()->InBattleGround())
		{
		if (ai->GetBot()->GetBattleGroundTypeId() == BattleGroundTypeId::BATTLEGROUND_WS)
			{
			BattleGroundWS *bg = (BattleGroundWS*)ai->GetBot()->GetBattleGround();
			if (!(bg->GetFlagState(bg->GetOtherTeam(bot->GetTeam())) == BG_WS_FLAG_STATE_ON_PLAYER))
				return true;
			if (bot->GetGUID() == bg->GetFlagKeeper(bg->GetOtherTeam(bot->GetTeam()) == ALLIANCE ? TEAM_ALLIANCE : TEAM_HORDE)) //flag-Carrier, bring it home
			{
				return false;
				}
			}
		return true;
		}
	return true;
}