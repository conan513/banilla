#include "../../../botpch.h"
#include "../../playerbot.h"
#include "../values/LastMovementValue.h"
#include "MovementActions.h"
#include "../../game/MotionMaster.h"
#include "../../game/MovementGenerator.h"
#include "../../FleeManager.h"
#include "../../DisperseManager.h"
#include "../../LootObjectStack.h"
#include "../../PlayerbotAIConfig.h"

using namespace ai;

bool MovementAction::MoveNear(uint32 mapId, float x, float y, float z, float distance)
{
    float angle = GetFollowAngle();
    return MoveTo(mapId, x + cos(angle) * distance, y + sin(angle) * distance, z);
}

bool MovementAction::MoveNear(WorldObject* target, float distance)
{
    if (!target)
        return false;

    distance += target->GetObjectBoundingRadius();
	float followAngle = GetFollowAngle();

	for (float angle = followAngle; angle <= followAngle + 2 * M_PI; angle += M_PI / 4)
	{
		float x = target->GetPositionX() + cos(angle) * distance,
			  y = target->GetPositionY() + sin(angle) * distance,
			  z = target->GetPositionZ();
		if (!bot->IsWithinLOS(x, y, z))
			 continue;
	    bool moved = MoveTo(target->GetMapId(), x, y, z);
		if (moved)
			return true;
		}    
    return false;
}

bool MovementAction::ChaseTo(Unit* obj)
{
	if (bot->IsSitState())
		bot->SetStandState(UNIT_STAND_STATE_STAND);
	
	if (!bot->IsPositiveSpellCasted(true))
	{
		bot->CastStop();
		ai->InterruptSpell();
		}
	
	MotionMaster &mm = *bot->GetMotionMaster();
	mm.Clear();
	
		mm.MoveChase(obj);
	return true;
}

bool MovementAction::MoveTo(uint32 mapId, float x, float y, float z)
{

	if (!bot->IsUnderWater())
		bot->UpdateGroundPositionZ(x, y, z);

    if (!IsMovingAllowed(mapId, x, y, z))
        return false;

    float distance = bot->GetDistance2d(x, y);

	if (distance > sPlayerbotAIConfig.contactDistance)
    {
        WaitForReach(distance);

        if (bot->IsSitState())
            bot->SetStandState(UNIT_STAND_STATE_STAND);

		if (!bot->IsPositiveSpellCasted(true))
        {
            bot->CastStop();
            ai->InterruptSpell();
            ai->TellMaster("Interrupt spell to move");
            ai->DoSpecificAction("instant action");
        }

        //bool generatePath = bot->HasAuraType(SPELL_AURA_MOD_INCREASE_MOUNTED_FLIGHT_SPEED) &&
        //        !bot->IsFlying() && !bot->IsUnderWater();
		bool generatePath = !bot->IsFlying() && !bot->IsUnderWater();

        MotionMaster &mm = *bot->GetMotionMaster();
        mm.Clear();

        float botZ = bot->GetPositionZ();
     
		//if (z - botZ > 0.5f && bot->GetDistance2d(x, y) <= 5.0f)
       // {
       //     float speed = bot->GetSpeed(MOVE_RUN);
       //     mm.MoveJump(x, y, botZ + 0.5f, speed, speed, 1);
       // 
		if (!bot->InBattleGround() && z - botZ > 0.5f && bot->GetDistance2d(x, y) <= 5.0f)
		{
			float speed = bot->GetSpeed(MOVE_RUN);
			mm.MoveJump(x, y, botZ + 0.5f, speed, speed, 1);
			}
		else
            mm.MovePoint(mapId, x, y, z, generatePath);

        AI_VALUE(LastMovement&, "last movement").Set(x, y, z, bot->GetOrientation());
        return true;
    }
	else ai->ResetMovePoint();

    return false;
}

bool MovementAction::FleeTo(Unit* target, uint32 mapId, float x, float y, float z)
{

    bot->UpdateAllowedPositionZ(x, y, z);
    z = z + 0.05f;

    if (!IsMovingAllowed(mapId, x, y, z))
        return false;

    if (!target)
        return false;

    float distance = bot->GetDistance(x, y, z);
	float targetDistance = bot->GetDistance2d(target->GetPositionX(), target->GetPositionY());

	if (targetDistance > sPlayerbotAIConfig.tooCloseDistance + 2.0f)
	{
		ai->ResetMovePoint();
		//ai->Reset();
		return true;
	}

    if (distance > sPlayerbotAIConfig.contactDistance)
    {
		WaitForReach(distance);

        if (bot->IsSitState())
            bot->SetStandState(UNIT_STAND_STATE_STAND);

		if (!bot->IsPositiveSpellCasted(true))
		{
			bot->CastStop();
			ai->InterruptSpell();
			ai->TellMaster("Interrupt spell to flee");
		}

        bool generatePath = !bot->IsUnderWater();
        MotionMaster &mm = *bot->GetMotionMaster();
        mm.Clear();

        float botZ = bot->GetPositionZ();
        if (z - botZ > 0.5f && bot->GetDistance2d(x, y) <= 5.0f)
        {
            float speed = bot->GetSpeed(MOVE_RUN);
            mm.MoveJump(x, y, botZ + 0.5f, speed, speed, 1);
        }
        else
            mm.MovePoint(mapId, x, y, z, generatePath);
    }
	else ai->ResetMovePoint();

    AI_VALUE(LastMovement&, "last movement").Set(x, y, z, bot->GetOrientation());
    return true;
}

bool MovementAction::MoveTo(Unit* target, float distance)
{
    if (!IsMovingAllowed(target))
        return false;

    float bx = bot->GetPositionX();
    float by = bot->GetPositionY();
    float bz = bot->GetPositionZ();

    float tx = target->GetPositionX();
    float ty = target->GetPositionY();
    float tz = target->GetPositionZ();

    float distanceToTarget = bot->GetDistance2d(target);
    float angle = bot->GetAngle(target);
    float needToGo;

    if (target && target == GetMaster() && bot->GetMinMasterDistance() > 0)
    {
        needToGo = distanceToTarget + bot->GetMinMasterDistance() - distance;
        }
    else if (target  && bot->GetMinTargetDistance() > 0)
    {
        needToGo = distanceToTarget + bot->GetMinTargetDistance() - distance;
        }
    else
         needToGo = distanceToTarget - distance;

    float maxDistance = sPlayerbotAIConfig.spellDistance;
    if (needToGo > 0 && needToGo > maxDistance)
        needToGo = maxDistance;
    else if (needToGo < 0 && needToGo < -maxDistance)
        needToGo = -maxDistance;

    float dx = cos(angle) * needToGo + bx;
    float dy = sin(angle) * needToGo + by;

    return MoveTo(target->GetMapId(), dx, dy, tz);
}

bool MovementAction::MoveToUnit(Unit* target)
{
    if (!IsMovingAllowed(target))
        return false;

    bot->GetMotionMaster()->Clear();
    bot->GetMotionMaster()->MoveChase(target);

   // ai->DoNextAction(1,true);
	return true;
}

float MovementAction::GetFollowAngle()
{
    Player* master = GetMaster();
    Group* group = master ? master->GetGroup() : bot->GetGroup();
    if (!group)
        return 0.0f;

    int index = 1;
    for (GroupReference *ref = group->GetFirstMember(); ref; ref = ref->next())
    {
        if( ref->getSource() == master)
            continue;

        if( ref->getSource() == bot)
            return 2 * M_PI / (group->GetMembersCount() -1) * index;

        index++;
    }
    return 0;
}

bool MovementAction::IsMovingAllowed(Unit* target)
{
    if (!target)
        return false;

    if (bot->GetMapId() != target->GetMapId())
        return false;

    float distance = bot->GetDistance(target);
	if (!bot->InBattleGround() &&  distance > sPlayerbotAIConfig.reactDistance)
        return false;

    return IsMovingAllowed();
}

bool MovementAction::IsMovingAllowed(uint32 mapId, float x, float y, float z)
{
    float distance = bot->GetDistance(x, y, z);
	if (!bot->InBattleGround() && distance > sPlayerbotAIConfig.reactDistance)
        return false;

    return IsMovingAllowed();
}

bool MovementAction::IsMovingAllowed()
{
    if (bot->isFrozen() || bot->IsPolymorphed() ||
			(bot->isDead() && !bot->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST)) ||
            bot->IsBeingTeleported() ||
            bot->isInRoots() ||
            bot->HasAuraType(SPELL_AURA_MOD_CONFUSE) || bot->IsCharmed() ||
            bot->HasAuraType(SPELL_AURA_MOD_STUN) || bot->IsFlying())
        return false;

    MotionMaster &mm = *bot->GetMotionMaster();
    return mm.GetCurrentMovementGeneratorType() != FLIGHT_MOTION_TYPE;
}

bool MovementAction::Follow(Unit* target, float distance)
{
    return Follow(target, distance, GetFollowAngle());
}

bool MovementAction::GetBehind(Unit* target, float distance)
{
    return GetBehind(target, distance, GetFollowAngle());
}

bool MovementAction::Follow(Unit* target, float distance, float angle)
{
    MotionMaster &mm = *bot->GetMotionMaster();

    if (!target)
        return false;

	if (!bot->InBattleGround() && bot->GetDistance2d(target) <= sPlayerbotAIConfig.sightDistance &&
            abs(bot->GetPositionZ() - target->GetPositionZ()) >= sPlayerbotAIConfig.tooCloseDistance)
    {
        mm.Clear();
        float x = target->GetPositionX(), y = target->GetPositionY(), z = target->GetPositionZ();

        bot->UpdateAllowedPositionZ(x, y, z);
        z = z + 0.05f;

        if (target->GetMapId() && bot->GetMapId() != target->GetMapId())
        {
            bot->TeleportTo(target->GetMapId(), x, y, z, bot->GetOrientation());
        }
        else
        {
            bot->Relocate(x, y, z, bot->GetOrientation());
        }
        AI_VALUE(LastMovement&, "last movement").Set(target);
        return true;
    }

    if (!IsMovingAllowed(target))
        return false;

	if (target->GetTypeId() == TYPEID_PLAYER)
	{
		if (((Unit *)target)->IsFriendlyTo(bot) && bot->IsMounted() && AI_VALUE(list<ObjectGuid>, "possible targets").empty())
			distance += angle;
	}

   // if (target->IsFriendlyTo(bot) && bot->IsMounted() && AI_VALUE(list<ObjectGuid>, "possible targets").empty())
   //     distance += angle;

	if (!bot->InBattleGround() && bot->GetDistance2d(target) <= sPlayerbotAIConfig.followDistance)
        return false;

    if (bot->IsSitState())
        bot->SetStandState(UNIT_STAND_STATE_STAND);

	if (!bot->IsPositiveSpellCasted(true))
    {
        bot->CastStop();
        ai->InterruptSpell();
        ai->TellMaster("Interrupt spell to follow");
    }

	mm.MoveFollow(target, distance, angle);

    AI_VALUE(LastMovement&, "last movement").Set(target);
    return true;
}

bool MovementAction::GetBehind(Unit* target, float distance, float angle)
{
    MotionMaster &mm = *bot->GetMotionMaster();

    if (!target)
        return false;

	if (!bot->InBattleGround() && bot->GetDistance2d(target) <= sPlayerbotAIConfig.sightDistance &&
            abs(bot->GetPositionZ() - target->GetPositionZ()) >= sPlayerbotAIConfig.tooCloseDistance)
    {
        mm.Clear();
        float x = target->GetPositionX(), y = target->GetPositionY(), z = target->GetPositionZ();
        bot->UpdateAllowedPositionZ(x, y, z);
        z = z + 0.05f;

        if (target->GetMapId() && bot->GetMapId() != target->GetMapId())
        {
           return false;
        }
        else
        {
            bot->Relocate(x, y, z, bot->GetOrientation());
        }
        AI_VALUE(LastMovement&, "last movement").Set(target);
        return true;
    }

    if (!IsMovingAllowed(target))
        return false;

    if (bot->IsSitState())
        bot->SetStandState(UNIT_STAND_STATE_STAND);

	if (!bot->IsPositiveSpellCasted(true))
    {
        bot->CastStop();
        ai->InterruptSpell();
        ai->TellMaster("Interrupt spell to move behind");
    }

	mm.MoveFollow(target, distance, angle);

    AI_VALUE(LastMovement&, "last movement").Set(target);
    return true;
}

void MovementAction::WaitForReach(float distance)
{
    float delay = 1000.0f * distance / bot->GetSpeed(MOVE_RUN) + sPlayerbotAIConfig.reactDelay;

    if (delay > sPlayerbotAIConfig.maxWaitForMove)
        delay = sPlayerbotAIConfig.maxWaitForMove;

    Unit* target = *ai->GetAiObjectContext()->GetValue<Unit*>("current target");
    Unit* player = *ai->GetAiObjectContext()->GetValue<Unit*>("enemy player target");
    if ((player || target) && delay > sPlayerbotAIConfig.globalCoolDown)
        delay = sPlayerbotAIConfig.globalCoolDown;

    if (ai->DoMovingAction(bot,GetTarget()))
        ai->SetNextCheckDelay((uint32)delay);
}

bool MovementAction::Flee(Unit *target)
{
    Player* master = GetMaster();
    if (!target)
        target = master;

    if (!target)
        return false;

    if (!sPlayerbotAIConfig.fleeingEnabled)
        return false;

    if (!IsMovingAllowed())
        return false;

    if (ai->IsMoving())
        return false;

    uint32 mapId = target->GetMapId();

    float rx, ry, rz;

    if (ai->GetMovePoint(mapId,rx,ry,rz))
    {
            return FleeTo(target,target->GetMapId(), rx, ry, rz);
      }
    else
    {
       FleeManager manager(bot, sPlayerbotAIConfig.fleeDistance, bot->GetAngle(target) + M_PI);

       if (!manager.CalculateDestination(&rx, &ry, &rz))
         return false;

       ai->SetMovePoint(mapId,rx, ry, rz);
       return FleeTo(target,target->GetMapId(), rx, ry, rz);
     }
}

bool MovementAction::Disperse(Unit *target)
{
    Player* master = GetMaster();

    if (!target)
        target = bot;

    if (!IsMovingAllowed())
        return false;

    if (ai->IsMoving())
        return false;

    uint32 mapId = target->GetMapId();

    float rx, ry, rz;

    if (ai->GetMovePoint(mapId,rx,ry,rz))
    {
            return FleeTo(target,target->GetMapId(), rx, ry, rz);
      }
    else
    {
       DisperseManager manager(bot, sPlayerbotAIConfig.fleeDistance, GetFollowAngle());

       if (!manager.CalculateDestination(&rx, &ry, &rz))
         return false;

       ai->SetMovePoint(mapId,rx, ry, rz);
       return FleeTo(target,target->GetMapId(), rx, ry, rz);
     }
}

bool MovementAction::Reposition(Unit *target)
{
    Player* master = GetMaster();
    if (!target)
        target = master;

    if (!target)
        return false;

    if (!IsMovingAllowed())
        return false;

    uint32 mapId = target->GetMapId();

    float rx, ry, rz;

    if (ai->GetMovePoint(mapId,rx,ry,rz) && (bot->GetDistance(rx, ry, rz) > (sPlayerbotAIConfig.tooCloseDistance)/2 ))
    {
            return FleeTo(target,target->GetMapId(), rx, ry, rz);
      }
    else
    {
       FleeManager manager(bot, sPlayerbotAIConfig.fleeDistance, bot->GetAngle(target) + M_PI);

       if (!manager.CalculateDestination(&rx, &ry, &rz))
         return false;

       ai->SetMovePoint(mapId,rx, ry, rz);
       return FleeTo(target,target->GetMapId(), rx, ry, rz);
     }

}

bool RepositionAction::Execute(Event event)
{
    return Reposition(AI_VALUE(Unit*, "current target"));
}

bool RepositionAction::isUseful()
{
    return AI_VALUE(uint8, "attacker count") > 0;
}

bool MoveOrderAction::Execute(Event event)
{
    Player* player = GetMaster();

    float rx, ry, rz;

    uint32 mapId = bot->GetMapId();
    if (player->GetMovePoint(mapId,rx,ry,rz))
    {
        float distance = bot->GetDistance(rx,ry,rz);

        if (distance <= sPlayerbotAIConfig.sightDistance)
            return FleeTo(bot,mapId, rx, ry, rz);
         else player->ResetMovePoint();
      }
    else return false;
}

bool MoveOrderAction::isUseful()
{
    return true;
}


bool FleeAction::Execute(Event event)
{
    return Flee(AI_VALUE(Unit*, "current target"));
}

bool FleeAction::isUseful()
{
    return AI_VALUE(uint8, "attacker count") > 0 &&
		   AI_VALUE2(float, "distance", "current target") <= sPlayerbotAIConfig.shootDistance;
}

bool DisperseAction::Execute(Event event)
{
    return Disperse(AI_VALUE(Unit*, "self target"));
}

bool RunAwayAction::Execute(Event event)
{
    return Flee(AI_VALUE(Unit*, "master target"));
}

bool MoveRandomAction::Execute(Event event)
{
	vector<WorldLocation> locs;
	list<ObjectGuid> npcs = AI_VALUE(list<ObjectGuid>, "nearest npcs");
	for (list<ObjectGuid>::iterator i = npcs.begin(); i != npcs.end(); i++)
    {
		WorldObject* target = ai->GetUnit(*i);
		if (target && bot->GetDistance(target) > sPlayerbotAIConfig.tooCloseDistance)
        {
			WorldLocation loc;
			target->GetPosition(loc);
			locs.push_back(loc);
        }
    }

	list<ObjectGuid> players = AI_VALUE(list<ObjectGuid>, "nearest friendly players");
	for (list<ObjectGuid>::iterator i = players.begin(); i != players.end(); i++)
    {
		WorldObject* target = ai->GetUnit(*i);
		if (target && bot->GetDistance(target) > sPlayerbotAIConfig.tooCloseDistance)
		{
			WorldLocation loc;
			target->GetPosition(loc);
			locs.push_back(loc);
		}
    }

	list<ObjectGuid> gos = AI_VALUE(list<ObjectGuid>, "nearest game objects");
	for (list<ObjectGuid>::iterator i = gos.begin(); i != gos.end(); i++)
	{
		WorldObject* target = ai->GetGameObject(*i);

		if (target && bot->GetDistance(target) > sPlayerbotAIConfig.tooCloseDistance)
		{
			WorldLocation loc;
			target->GetPosition(loc);
			locs.push_back(loc);
		}
	}

	float distance = sPlayerbotAIConfig.grindDistance;
	Map* map = bot->GetMap();

    for (int i = 0; i < 10; ++i)
    {
        float x = bot->GetPositionX();
        float y = bot->GetPositionY();
        float z = bot->GetPositionZ();
        x += urand(0, distance) - distance / 2;
        y += urand(0, distance) - distance / 2;
        bot->UpdateAllowedPositionZ(x, y, z);

		const TerrainInfo* terrain = map->GetTerrain();
		if (terrain->IsUnderWater(x, y, z) ||
			terrain->IsInWater(x, y, z))
			continue;

		float ground = map->GetHeight(x, y, z + 0.5f);
		if (ground <= INVALID_HEIGHT)
			continue;
		
			z = 0.05f + ground;
		WorldLocation loc(bot->GetMapId(), x, y, z);
		locs.push_back(loc);
    }

	if (locs.empty())
		return false;
	
		WorldLocation target = locs[urand(0, locs.size() - 1)];
	return MoveNear(target.mapid, target.coord_x, target.coord_y, target.coord_z);
}

bool MoveToLootAction::Execute(Event event)
{
    LootObject loot = AI_VALUE(LootObject, "loot target");
    if (!loot.IsLootPossible(bot))
        return false;

    return MoveNear(loot.GetWorldObject(bot));
}

bool MoveOutOfEnemyContactAction::Execute(Event event)
{
    Unit* target = AI_VALUE(Unit*, "current target");
    if (!target)
        return false;

    return MoveNear(target, sPlayerbotAIConfig.meleeDistance);
}

bool MoveOutOfEnemyContactAction::isUseful()
{
    return AI_VALUE2(float, "distance", "current target") < (sPlayerbotAIConfig.meleeDistance + sPlayerbotAIConfig.contactDistance);
}

bool SetFacingTargetAction::Execute(Event event)
{
    Unit* target = AI_VALUE(Unit*, "current target");
    if (!target)
        return false;

    bot->SetFacingTo(bot->GetAngle(target));
    ai->SetNextCheckDelay(sPlayerbotAIConfig.globalCoolDown);
    return true;
}

bool SetFacingTargetAction::isUseful()
{
    return !AI_VALUE2(bool, "facing", "current target");
}

bool MoveQuestGiverAction::Execute(Event event)
{	
	uint32 mapId;
	uint32 areaId;
	uint32 zoneId;
	float go_x, go_y, go_z;
	uint32 questId = 0;

	WorldObject* QuestStarter;

	QuestStarter = bot->MoveToQuestStarter(mapId, areaId, zoneId, go_x, go_y, go_z, questId);

	if (!QuestStarter)
		return false;

	AreaTableEntry const* area = GetAreaEntryByAreaID(areaId);

	if (area)
		sLog.outString("Teleporting bot %s to queststarter for quest to %s %f,%f,%f", bot->GetName(), area->area_name[0], go_x, go_y, go_z);

	MoveNear(QuestStarter);

	return true;
}

bool MoveQuestEnderAction::isUseful()
{
	return !bot->GetGroup();
}

bool MoveQuestEnderAction::Execute(Event event)
{
	uint32 mapId;
	uint32 areaId;
	uint32 zoneId;
	float go_x, go_y, go_z;
	uint32 questId = 0;

	WorldObject* QuestEnder;

	QuestEnder = bot->MoveToQuestEnder(mapId, areaId, zoneId, go_x, go_y, go_z, questId);

	if (!QuestEnder)
		return false;

	AreaTableEntry const* area = GetAreaEntryByAreaID(areaId);

	if (area)
		sLog.outString("Teleporting bot %s to questender for quest to %s %f,%f,%f", bot->GetName(), area->area_name[0], go_x, go_y, go_z);

	MoveNear(QuestEnder);

	return true;
}

bool MoveQuestGiverAction::isUseful()
{
	return !bot->GetGroup();
}

bool MoveQuestPositionAction::Execute(Event event)
{
	uint32 mapId;
	uint32 areaId;
	uint32 zoneId;
	float go_x, go_y, go_z;
	uint32 questId = 0;
	
	WorldObject* QuestTarget;

	QuestTarget = bot->MoveToQuestPosition(mapId, areaId, zoneId, go_x, go_y, go_z, questId);

	if (!QuestTarget)
		return false;

	AreaTableEntry const* area = GetAreaEntryByAreaID(areaId);

	if (area)
		sLog.outString("Teleporting bot %s to queststarter for quest to %s %f,%f,%f", bot->GetName(), area->area_name[0], go_x, go_y, go_z);

	if ((bot->GetMapId() != mapId) || (bot->GetDistance2d(QuestTarget) < 200.f))
	{
		MotionMaster &mm = *bot->GetMotionMaster();
		mm.Clear();
		bot->TeleportTo(mapId, go_x, go_y, go_z, 0);
	}

	MoveNear(QuestTarget);

	return true;
}

bool MoveQuestPositionAction::isUseful()
{
	return !bot->GetGroup();
}
