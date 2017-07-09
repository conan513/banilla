#include "../../../botpch.h"
#include "../../playerbot.h"
#include "AttackAction.h"
#include "MovementGenerator.h"
#include "AI/CreatureAI.h"
#include "Pet.h"
#include "../../LootObjectStack.h"

using namespace ai;

bool AttackAction::Execute(Event event)
{
    Unit* target = GetTarget();

    if (!target)
        return false;

    return Attack(target);
}

bool AttackMyTargetAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    Unit* target = master->getSelectedUnit();
    if (!target)
    {
        if (verbose) ai->TellMaster("You have no target");
        return false;
    }

    return Attack(target);
}

bool AttackAction::Attack(Unit* target)
{
    MotionMaster &mm = *bot->GetMotionMaster();
    if (bot->IsFlying())
    {
        if (verbose) ai->TellMaster("I cannot attack in flight");
        return false;
    }

    if (!target)
    {
        if (verbose) ai->TellMaster("I have no target");
        return false;
    }

	if (target->isDead())
	{
		if (verbose) ai->TellMaster("Target is dead");
		return false;
	}

    Player* master = GetMaster();
    if (AI_VALUE(uint8, "balance") < 75 && (master && master->isDead() && !bot->isInCombat()))
    {
        if (verbose) ai->TellMaster("target too strong!");
        return false;
    }

    if (AI_VALUE(uint8, "balance") < 75 && !(master || bot->GetGroup()))
    {
        if (verbose) ai->TellMaster("target too strong!");
        return false;
    }

    ostringstream msg;
    msg << target->GetName();
    if (bot->IsFriendlyTo(target))
    {
        msg << " is friendly to me";
        if (verbose) ai->TellMaster(msg.str());
        return false;
    }
	if( !bot->InBattleGround() && !bot->IsWithinLOSInMap(target))
    {
        msg << " is not on my sight";
        if (verbose) ai->TellMaster(msg.str());
        return false;
    }

	if (target && (target->UnderCc() || target->IsStunned() || target->isFrozen()))
	{
		float minHealth = 0;

		if (AI_VALUE(uint8, "my attacker count") >= 2)
		{
			list<ObjectGuid> attackers = AI_VALUE(list<ObjectGuid>, "attackers");
			for (list<ObjectGuid>::iterator i = attackers.begin(); i != attackers.end(); ++i)
			{
				Unit* unit = ai->GetUnit(*i);

				if (!unit || (unit == target) || unit->UnderCc())
					continue;

				float health = unit->GetHealth();

				if (minHealth == 0 || minHealth > health)
				{
					minHealth = health;
					target = unit;
					msg << "new target due to cc";
				}
			}
		}
		else if (!bot->GetGroup())
		{
			if (ai->CanHeal(bot) && bot->GetHealthPercent() < 60)
			{
				ai->DoSpecificAction("urgent heal");
				return false;
			}
			else if (ai->IsRanged(bot) && AI_VALUE2(float, "distance", "current target") <= sPlayerbotAIConfig.tooCloseDistance)
			{
				ai->DoSpecificAction("flee");
				return false;
			}
			else if (bot->GetHealthPercent() < 50)
			{
				ai->DoSpecificAction("bandage");
				return false;
			}
		}
	}

	if (bot->IsMounted() && bot->IsWithinLOSInMap(target))

    if (bot->IsMounted())
    {
        WorldPacket emptyPacket;
        bot->GetSession()->HandleCancelMountAuraOpcode(emptyPacket);
    }

    ObjectGuid guid = target->GetGUID();
    bot->SetSelectionGuid(target->GetGUID());

    Unit* oldTarget = context->GetValue<Unit*>("current target")->Get();
    context->GetValue<Unit*>("old target")->Set(oldTarget);

    context->GetValue<Unit*>("current target")->Set(target);
    context->GetValue<LootObjectStack*>("available loot")->Get()->Add(guid);

	Pet* pet = bot->GetPet();
	if (pet)
	{
		CreatureAI* creatureAI = ((Creature*)pet)->AI();
		if (creatureAI)
			creatureAI->AttackStart(target);
	}


    if (!((bot->getLevel() > 19 && ai->HasAura("stealth",bot)) || (bot->getLevel() > 31 && ai->HasAura("prowl",bot))))
        bot->Attack(target, true);
    //else bot->Attack(target, false);

    ai->ChangeEngine(BOT_STATE_COMBAT);
    return true;
}

bool AttackDuelOpponentAction::isUseful()
{
    return AI_VALUE(Unit*, "duel target");
}

bool AttackDuelOpponentAction::Execute(Event event)
{
    return Attack(AI_VALUE(Unit*, "duel target"));
}
