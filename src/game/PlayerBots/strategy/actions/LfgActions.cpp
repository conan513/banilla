#include "../../../botpch.h"
#include "../../playerbot.h"
#include "LfgActions.h"
#include "BattleGround.h"

using namespace ai;

bool BGJoinAction::Execute(Event event)
{
	if (!sPlayerbotAIConfig.randomBotJoinBG)
		return false;

	if (bot->isDead())
		return false;

	if (bot->getLevel() < 10)
		return false;

	if (!sRandomPlayerbotMgr.IsRandomBot(bot))
		return false;

	if (bot->InBattleGroundQueue())
		return false;

	if (bot->IsBeingTeleported())
		return false;

	Map* map = bot->GetMap();
	if (map && map->Instanceable())
		return false;

	return JoinProposal();
}

int j = 0;

bool BGJoinAction::JoinProposal()
{
//	ai->GetAiObjectContext()->GetValue<uint32>("lfg proposal")->Set(1);

		// warsong only at start
	// nyi: cycle based on time frame through AB and WS
	BattleGroundTypeId bgTypeId = BattleGroundTypeId::BATTLEGROUND_WS;

	// can do this, since it's BattleGround, not arena
	BattleGroundQueueTypeId bgQueueTypeId = BattleGroundMgr::BGQueueTypeId(bgTypeId);

	// ignore if player is already in BG
	if (bot->InBattleGround())
		return false;

	BattleGround* bg = sBattleGroundMgr.GetBattleGroundTemplate(bgTypeId);
	if (!bg)
		return false;

	// expected bracket entry
	//PvPDifficultyEntry const* bracketEntry = GetBattleGroundBracketByLevel(bg->GetMapId(), bot->getLevel());
	//if (!bracketEntry)
	//	return false;

	BattleGroundBracketId bgBracketId = bot->GetBattleGroundBracketIdFromLevel(bgTypeId);

	//GroupJoinBattleGroundResult err;

	// check Deserter debuff
	if (!bot->CanJoinToBattleground())
	{
		return false;
	}

	// check if already in queue
	if (bot->GetBattleGroundQueueIndex(bgQueueTypeId) < PLAYER_MAX_BATTLEGROUND_QUEUES)
		// player is already in this queue
		return false;

	// check if has free queue slots
	if (!bot->HasFreeBattleGroundQueueId())
	{
		return false;
	}

	// check Freeze debuff
	if (bot->HasAura(9454))
		return false;

	/*
	BattleGroundQueue& bgQueue = sBattleGroundMgr.GetBattleGroundQueue(bgQueueTypeId);
	if (bgQueue.m_QueuedPlayers.size()>0)
	{
		GroupQueueInfo* ginfo = bgQueue.AddGroup(bot, NULL, bgTypeId, bracketEntry, false);
		uint32 avgTime = bgQueue.GetAverageQueueWaitTime(ginfo, bracketEntry->GetBracketId());
		// already checked if queueSlot is valid, now just get it
		uint32 queueSlot = bot->AddBattleGroundQueueId(bgQueueTypeId);

		sLog.outError("BattleGround: player joined queue for bg queue type %u bg type %u: GUID %u, NAME %s",
			bgQueueTypeId, bgTypeId, bot->GetGUID(), bot->GetName());
		return true;
	}
	*/
	BattleGroundQueue& bgQueue = sBattleGroundMgr.m_BattleGroundQueues[bgQueueTypeId];
	GroupQueueInfo * ginfo = bgQueue.AddGroup(bot, NULL, bgTypeId, bgBracketId, false);
	uint32 avgTime = bgQueue.GetAverageQueueWaitTime(ginfo, bot->GetBattleGroundBracketIdFromLevel(bgTypeId));
	// already checked if queueSlot is valid, now just get it
	uint32 queueSlot = bot->AddBattleGroundQueueId(bgQueueTypeId);
	// store entry point coords
	bot->SetBattleGroundEntryPoint(bot, false);

	WorldPacket data;
	// send status packet (in queue)
	sBattleGroundMgr.BuildBattleGroundStatusPacket(&data, bg, queueSlot, STATUS_WAIT_QUEUE, avgTime, 0);
	bot->GetSession()->SendPacket(&data);
	
	sBattleGroundMgr.ScheduleQueueUpdate(bgQueueTypeId, bgTypeId, bot->GetBattleGroundBracketIdFromLevel(bgTypeId));

	//sBattleGroundMgr.GetPlayerCount()

	return false;
}

bool BGStatusAction::Execute(Event event)
{

	uint32 QueueSlot;
	uint8 arenatype;
	uint8 arenaByte;
	uint32 battleId;
	uint16 x1f90;
	uint8 minlevel;
	uint8 maxlevel;
	uint32 instanceId;
	uint8 isRated;
	uint32 statusid;

	WorldPacket p(event.getPacket());
	statusid = 0;

	//on status 0, the packet has a uint64 as payload only. Took me two suicide tries and a gnomen porn video to find out
	p >> QueueSlot >> arenatype >> arenaByte >> battleId >> x1f90;
	if (x1f90 != 0)
		p >> minlevel >> maxlevel >> instanceId >> isRated >> statusid;

	if (statusid == STATUS_WAIT_LEAVE) //BattleGround is over, bot needs to leave
	{
		sLog.outError("BattleGround: player (bot) %s (%u) is going to leave BattleGround (%u).", bot->GetName(), bot->GetGUID(), battleId);
		bot->LeaveBattleground();
		ai->ResetStrategies();
	}
	if (statusid == STATUS_WAIT_QUEUE) //bot is in queue
	{
		sLog.outError("BattleGround: player (bot) %s (%u) is still in queue (%u).", bot->GetName(), bot->GetGUID(), battleId);
	}
	if (statusid == STATUS_WAIT_JOIN) //bot may join
	{
		if (bot->InBattleGround())
		{
			sLog.outError("BattleGround: player (bot) %s (%u) is in BattleGround already. (%u, %u).", bot->GetName(), bot->GetGUID(), battleId, instanceId);
			return false;
		}

		sLog.outError("BattleGround: player (bot) %s (%u) received a invite to a BattleGround (%u, %u).", bot->GetName(), bot->GetGUID(), battleId, instanceId);

		bot->CombatStop(true);

		sLog.outDebug( "Bot %s is going to join BG %d", bot->GetName(), battleId);

		bot->clearUnitState(UNIT_STAT_ALL_STATE);

		//get GroupQueueInfo from BattleGroundQueue
		BattleGroundTypeId bgTypeId = BattleGroundTypeId(battleId);
		BattleGroundQueueTypeId bgQueueTypeId = BattleGroundMgr::BGQueueTypeId(bgTypeId);
		BattleGroundQueue& bgQueue = sBattleGroundMgr.m_BattleGroundQueues[bgQueueTypeId];
		//we must use temporary variable, because GroupQueueInfo pointer can be deleted in BattleGroundQueue::RemovePlayer() function
		GroupQueueInfo ginfo;
		if (!bgQueue.GetPlayerGroupInfoData(bot->GetGUID(), &ginfo))
		{
			sLog.outDebug( "Bot %s was not in queue to join BG %d", bot->GetName(), battleId);
			return false;
		}
		// if action == 1, then instanceId is required
		if (!ginfo.IsInvitedToBGInstanceGUID)
		{
			sLog.outDebug( "Bot %s had no instanceID to join BG %d", bot->GetName(), battleId);
			return false;
		}

		BattleGround* bg = sBattleGroundMgr.GetBattleGround(ginfo.IsInvitedToBGInstanceGUID, bgTypeId);
		if (!bg)
		{
			bg = sBattleGroundMgr.GetBattleGroundTemplate(bgTypeId);
			if (!bg)
			{
				sLog.outDebug( "Bot %s could find no template for BattleGround %d", bot->GetName(), battleId);
				return false;
			}
		}

		// expected bracket entry
		BattleGroundBracketId bgBracketId = bot->GetBattleGroundBracketIdFromLevel(bgTypeId);
		if (bgBracketId)		
			return false;

		//some checks if player isn't cheating - it is not exactly cheating, but we cannot allow it
		//if (ginfo.ArenaType == 0)
		//{
			//if player is trying to enter BattleGround (not arena!) and he has deserter debuff, we must just remove him from queue
			if (!bot->CanJoinToBattleground())
			{
				sLog.outDebug( "Bot %s cant join BG %d because it has the deserter debuf", bot->GetName(), battleId);
				return false;
			}
			//if player don't match BattleGround max level, then do not allow him to enter! (this might happen when player leveled up during his waiting in queue
			if (bot->getLevel() > bg->GetMaxLevel())
			{
				sLog.outDebug( "Bot %s cant join BG %d because its level does not fit", bot->GetName(), battleId);
				return false;
			}
		//}
		uint32 queueSlot = bot->GetBattleGroundQueueIndex(bgQueueTypeId);
		// check Freeze debuff
		if (bot->HasAura(9454))
		{
			sLog.outDebug( "Bot %s cant join BG %d because it is freezed", bot->GetName(), battleId);
			return false;
		}

		if (!bot->IsInvitedForBattleGroundQueueType(bgQueueTypeId))
		{
			sLog.outDebug( "Bot %s cant join BG %d because it was not invited to join", bot->GetName(), battleId);
			return false;                                 // cheating? No, bots dont cheat. They just try very hard.
		}

		if (!bot->InBattleGround())
			bot->SetBattleGroundEntryPoint();

		// resurrect the player
		if (!bot->isAlive())
		{
			bot->ResurrectPlayer(1.0f);
			bot->SpawnCorpseBones();
		}
		// stop taxi flight at port
		bot->GetMotionMaster()->MovementExpired();
		if (bot->IsFlying())
		{
//			bot->CleanupAfterTaxiFlight();
			return false;
		}

		// remove BattleGround queue status from BGmgr
		bgQueue.RemovePlayer(bot->GetGUID(), false);
		// this is still needed here if BattleGround "jumping" shouldn't add deserter debuff
		// also this is required to prevent stuck at old BattleGround after SetBattleGroundId set to new
		if (BattleGround* currentBg = bot->GetBattleGround())
			currentBg->RemovePlayerAtLeave(bot->GetGUID(), false, true);

		// set the destination instance id
		bot->SetBattleGroundId(bg->GetInstanceID(), bgTypeId);
		// set the destination team
		bot->SetBGTeam(bot->GetTeam());

		// bg->HandleBeforeTeleportToBattleGround(_player);
		sBattleGroundMgr.SendToBattleGround(bot, ginfo.IsInvitedToBGInstanceGUID, bgTypeId);
		ai->ResetStrategies();
		// add only in HandleMoveWorldPortAck()
		// bg->AddPlayer(_player, team);
		sLog.outDebug("bg.BattleGround", "BattleGround: player (bot) %s (%u) joined battle for bg %u, bgtype %u, queue type %u.", bot->GetName(), bot->GetGUID(), bg->GetInstanceID(), bg->GetTypeID(), bgQueueTypeId);
		sLog.outDebug( "Bot %s joined BG %d", bot->GetName(), battleId);
	}
	return true;
}


//consume healthy, if low on health
bool BGTacticsWS::consumeHealthy(BattleGround *bg)
{

	//alliance healthy
	if (bot->HealthBelowPct(50))
	{
		WorldLocation posH1 = WorldLocation(1111.526733f, 1352.458130f, 316.567047f, 0);
		WorldLocation posA1 = WorldLocation(1320.670288f, 1549.642700f, 313.501404f, 0);


		if (bot->GetDistance(posH1.coord_x, posH1.coord_y, posH1.coord_z)<40)
		{
			return MoveTo(bg->GetMapId(), posH1.coord_x, posH1.coord_y, posH1.coord_z);
		}
		if (bot->GetDistance(posA1.coord_x, posA1.coord_y, posA1.coord_z)<40)
		{
			return MoveTo(bg->GetMapId(), posH1.coord_x, posH1.coord_y, posH1.coord_z);
		}
	}
	return false;

}

//run to enemy flag if not taken yet
bool BGTacticsWS::moveTowardsEnemyFlag(BattleGroundWS *bg)
{
	//If no flag is spawned, do something else
	if (!(bg->GetFlagState(bg->GetOtherTeam(bot->GetTeam())) == BG_WS_FLAG_STATE_ON_BASE ||
		bg->GetFlagState(bg->GetOtherTeam(bot->GetTeam())) == BG_WS_FLAG_STATE_ON_GROUND))
		return false;
	if (bg->GetFlagState(bot->GetTeam()) == BG_WS_FLAG_STATE_WAIT_RESPAWN)
		return false;
	GameObject* target_obj = bg->GetBgMap()->GetGameObject(bg->GetFlagKeeper(bg->GetOtherTeam(bot->GetTeam()) == ALLIANCE ? TEAM_HORDE : TEAM_ALLIANCE));
	if (target_obj == NULL)
	{
		if (bot->GetTeam() == HORDE)
			target_obj = bg->GetBgMap()->GetGameObject(bg->m_BgObjects[BG_WS_OBJECT_A_FLAG]);
		else
			target_obj = bg->GetBgMap()->GetGameObject(bg->m_BgObjects[BG_WS_OBJECT_H_FLAG]);
	}
	//Direct Movement, if we are close
	if (bot->IsWithinDist(target_obj, 40))
	{
		MoveNear(target_obj,1.f);
		return true;
	}
	GameObject* obj = bg->GetBgMap()->GetGameObject(bg->GetFlagKeeper(bot->GetTeam() == ALLIANCE ? TEAM_HORDE : TEAM_ALLIANCE));
	if (obj == NULL)
	{
		if (bot->GetTeamId() == TeamId::TEAM_HORDE)
			obj = bg->GetBgMap()->GetGameObject(bg->m_BgObjects[BG_WS_OBJECT_A_FLAG]);
		else
			obj = bg->GetBgMap()->GetGameObject(bg->m_BgObjects[BG_WS_OBJECT_H_FLAG]);
	}
	return runPathTo(obj, bg);
}

//if we have the flag, run home
bool BGTacticsWS::homerun(BattleGroundWS *bg)
{
	if (!(bg->GetFlagState(bg->GetOtherTeam(bot->GetTeam())) == BG_WS_FLAG_STATE_ON_PLAYER))
		return false;
	if (bot->GetGUID() == bg->GetFlagKeeper(bg->GetOtherTeam(bot->GetTeam()) == ALLIANCE ? TEAM_ALLIANCE : TEAM_HORDE)) //flag-Carrier, bring it home
	{
		GameObject* obj = bg->GetBgMap()->GetGameObject(bg->GetFlagKeeper(bot->GetTeam() == ALLIANCE ? TEAM_ALLIANCE : TEAM_HORDE));
		if (obj == NULL)
		{
			if (bot->GetTeamId() == TeamId::TEAM_HORDE)
				obj = bg->GetBgMap()->GetGameObject(bg->m_BgObjects[BG_WS_OBJECT_H_FLAG]);
			else
				obj = bg->GetBgMap()->GetGameObject(bg->m_BgObjects[BG_WS_OBJECT_A_FLAG]);
		}
		if (bot->IsWithinDistInMap(obj, 10) && (bg->GetFlagState(bot->GetTeam()) == BG_WS_FLAG_STATE_ON_BASE))
		{
			bg->EventPlayerCapturedFlag(bot);
			return true;
		}
		return runPathTo(obj, bg);
	}
	else {
		bool supporter = bot->Preference <5;
		//random choice if defense or offense
		if (supporter || (bg->GetFlagState(bot->GetTeam()) != BG_WS_FLAG_STATE_ON_PLAYER))
		{
			ObjectGuid guid = bg->GetFlagKeeper(bg->GetOtherTeam(bot->GetTeam()) == ALLIANCE ? TEAM_ALLIANCE : TEAM_HORDE);
			Player* ourGuy = ObjectAccessor::FindPlayer(guid);
			if (ourGuy != NULL)
			{
				if (!bot->IsWithinDist(ourGuy, 40))
					return runPathTo(ourGuy, bg);
				return Follow(ourGuy);
			}
		}
		else { //as a none supporter, attack their flag, if they carry it
			ObjectGuid guid = bg->GetFlagKeeper(bot->GetTeam() == ALLIANCE ? TEAM_ALLIANCE : TEAM_HORDE);
			Player* theirGuy = ObjectAccessor::FindPlayer(guid);
			if (theirGuy != NULL)
			{
				return runPathTo(theirGuy, bg);
			}
		}
	}
	return false;
}

//the alliance base entrance is at x=1351.759155 , y=1462.368042, z = 323.673737
//the horde base entrance is at x=1125.778076, y=1452.059937, z =315.698883
//left center of the battlefield is at x=1239.085693,y=1541.408569,z=306.491791
//middle center of the battlefield is at x=1227.446289,y=1476.235718,z=307.484589
//right center of the battlefield is at x=1269.962158,y=1382.655640,z=308.545288
//the alliance flag is at x=1538.387207,y=1480.903198,z=352.576385
//the horde flag is at x=919.161316,x=1433.871338,z=345.902771

//horde healthy is at x=1111.526733,y=1352.458130,z=316.567047
//alliance healthy is at x=1320.670288,y=1549.642700, z=313.501404

//alliance fasty is at x=1449.574219,y=1470.698608, z=342.675476
//horde fasty is at x=1006.590210,y=1450.435059, z=335.721283

//alliance graveyard is at x=1370.087769, y=1539.914551, z=321.451538

//Alliance wants to move towards a lower x value

//get back to alliance base

//cross the BattleGround to get to flags or flag carriers
bool BGTacticsWS::runPathTo(WorldObject *unit, BattleGround *bg)
{
	if (unit == NULL)
		return false;
	if (unit->IsWithinDist(bot, 40))
		return MoveNear(unit,1.f);
	if (unit->GetPositionX() > bot->GetPositionX()) //He's somewhere at the alliance side
	{
		if (bot->Preference < 4) //preference < 4 = move through tunnel
		{
			if (bot->GetPositionX() < 1006) //to the fasty
			{
				MoveTo(bg->GetMapId(), 1006.590210f, 1450.435059f, 335.721283f);
				return  true;
			}
			else if (bot->GetPositionX() < 1125) //to the horde entrance
			{
				if (bot->GetPositionY() < 1400)
					MoveTo(bg->GetMapId(), 1125.778076f, bot->GetPositionY(), 316.567047f);
				else
					MoveTo(bg->GetMapId(), 1125.778076f, 1452.059937f, 315.698883f);
				return  true;
			}
		}
		else if (bot->Preference<7) { // preference < 7 = move through graveyard
			if (bot->GetPositionX() < 985) //to the gate at the upper tunnel
			{
				MoveTo(bg->GetMapId(), 985.940125f, 1423.260254f, 345.418121f);
				return  true;
			}
			else if (bot->GetPositionX() < 1054.5) //to the gate at the upper tunnel
			{
				MoveTo(bg->GetMapId(), 1055.182251f, 1396.967529f, 339.361511f);
				return  true;
			}
			else if (bot->GetPositionX() < 1125) //to the horde entrance
			{
				MoveTo(bg->GetMapId(), 1125.778076f, bot->GetPositionY(), 316.567047f);
				return  true;
			}
		}
		else { //all other preference: run down the ramp 
			if (bot->GetPositionX() < 985) //to the gate at the upper tunnel
			{
				MoveTo(bg->GetMapId(), 985.940125f, 1423.260254f, 345.418121f);
				return  true;
			}
			else if (bot->GetPositionX() < 1031) //to the first step of the ramp from the tunnel
			{
				MoveTo(bg->GetMapId(), 1031.764282f, 1454.516235f, 343.337860f);
				return  true;
			}
			else if (bot->GetPositionX() < 1051 && bot->GetPositionY() < 1494) //to the second step of the ramp from the tunnel
			{
				MoveTo(bg->GetMapId(), 1051.304810f, 1494.917725f, 342.043518f);
				return  true;
			}
			else if (bot->GetPositionX() < 1050 && bot->GetPositionY() < 1538) //down the ramp
			{
				MoveTo(bg->GetMapId(), 1050.089478f, 1538.054443f, 332.460388f);
				return  true;
			}
			else if (bot->GetPositionX() < 1050 && bot->GetPositionY() < 1560) //down the ramp
			{
				MoveTo(bg->GetMapId(), 1050.089478f, 1560.054443f, 332.460388f);
				return  true;
			}
			else if (bot->GetPositionX() < 1098) //at the ground now
			{
				MoveTo(bg->GetMapId(), 1098.716797f, 1535.618652f, 315.727539f);
				return  true;
			}
			else if (bot->GetPositionX() < 1239)
			{
				MoveTo(bg->GetMapId(), 1239.085693f, 1541.408569f + frand(-2, +2), 306.491791f);
				return  true;
			}
		}
		if (bot->GetPositionX() < 1227) //move to a more random location in the middle part
		{
			if (bot->GetPositionY() < 1400)
				MoveTo(bg->GetMapId(), 1269.962158f, 1382.655640f + frand(-2, +2), 308.545288f);
			else
				MoveTo(bg->GetMapId(), 1227.446289f, 1476.235718f + frand(-2, +2), 307.484589f);
			return  true;
		}
		if (bot->Preference < 5) //through the tunnel
		{
			if (bot->GetPositionX() < 1351) //move to the alliance entrance
			{
				MoveTo(bg->GetMapId(), 1351.759155f + frand(0, 2), 1462.368042f + frand(-2, +2), 323.673737f);
				return  true;
			}
			else if (bot->GetPositionX() < 1449) //move to the alliance fasty
			{
				MoveTo(bg->GetMapId(), 1449.574219f, 1470.698608f, 342.675476f);
				return  true;
			}
			else { //move to the flag position
				MoveTo(bg->GetMapId(), 1538.387207f, 1480.903198f, 352.576385f);
				return  true;
			}
		}
		else { //up the ramp
			if (bot->GetPositionX() < 1360) //gate at the ramp
			{
				MoveTo(bg->GetMapId(), 1360.088501f, 1393.451660f + frand(-2, +2), 326.183624f);
				return  true;
			}
			if (bot->GetPositionX() < 1399) //half way up
			{
				MoveTo(bg->GetMapId(), 1399.362061f, 1405.105347f + frand(-2, +2), 341.481476f);
				return  true;
			}
			if (bot->GetPositionX() < 1417) //first halway
			{
				MoveTo(bg->GetMapId(), 1417.096191f, 1459.552368f + frand(-2, +2), 349.591827f);
				return  true;
			}
			if (bot->GetPositionX() < 1505.2) //gate to the flag room
			{
				MoveTo(bg->GetMapId(), 1505.045654f, 1493.787231f, 352.017670f);
				return  true;
			}
			else { //move to the flag position
				MoveTo(bg->GetMapId(), 1538.387207f, 1480.903198f, 352.576385f);
				bot->Preference = urand(0, 9); //reset preference
				return  true;
			}
		}
	}
	else //move towards horde base
	{
		if (bot->Preference < 4) //through the tunnel
		{
			if (bot->GetPositionX() > 1449.7) //to the fasty
			{
				MoveTo(bg->GetMapId(), 1449.574219f, 1470.698608f, 342.675476f);
				return  true;
			}
			else if (bot->GetPositionX() > 1443.9) { // moving from the fasty to the gate directly is bugged.. moving back to the tunnel first
				MoveTo(bg->GetMapId(), 1443.761963f, 1459.581909f, 342.115417f);
			}
			else if (bot->GetPositionX() > 1380.9) { // move into the tunnel
				MoveTo(bg->GetMapId(), 1380.761963f, 1457.581909f, 329.115417f);
			}
			else if (bot->GetPositionX() > 1351.9) //to the alliance entrance
			{
				if (bot->GetPositionY() > 1500)
					MoveTo(bg->GetMapId(), 1125.778076f, bot->GetPositionY(), 315.698883f);
				else
					MoveTo(bg->GetMapId(), 1125.778076f, 1452.059937f, 315.698883f);
				return  true;
			}
			if (bot->GetPositionX() > 1240) //move to a more random location in the middle part
			{
				if (bot->GetPositionY() > 1500)
					MoveTo(bg->GetMapId(), 1239.085693f, 1541.408569f + frand(-2, +2), 306.491791f);
				else
					MoveTo(bg->GetMapId(), 1227.446289f, 1476.235718f + frand(-2, +2), 307.484589f);
				return  true;
			}
		}
		else if (bot->Preference < 7) // through the graveyard
		{
			if (bot->GetPositionX() > 1505.2) //To the first gate
			{
				MoveTo(bg->GetMapId(), 1505.045654f, 1493.787231f, 352.017670f);
				return  true;
			}
			else if (bot->GetPositionX() > 1460) //to the second gate
			{
				MoveTo(bg->GetMapId(), 1459.490234f, 1494.175072f, 351.565155f);
				return  true;
			}
			else if (bot->GetPositionX() > 1424) //to the graveyard
			{
				MoveTo(bg->GetMapId(), 1423.106201f + frand(-2, +2), 1532.851196f, 342.152100f);
				return  true;
			}
			else if (bot->GetPositionX() > 1345) // to the field
			{
				MoveTo(bg->GetMapId(), 1344.334595f + frand(-2, +2), 1514.917236f, 319.081726f);
				return  true;
			}
		}
		else
		{
			if (bot->GetPositionX() > 1505.2) //To the first gate
			{
				MoveTo(bg->GetMapId(), 1505.045654f, 1493.787231f, 352.017670f);
				return  true;
			}
			else if (bot->GetPositionX() > 1460) //to the second gate
			{
				MoveTo(bg->GetMapId(), 1459.490234f, 1494.175072f, 351.565155f);
				return  true;
			}
			else if (bot->GetPositionX() > 1418) //half on the upper ramp
			{
				MoveTo(bg->GetMapId(), 1417.096191f, 1459.552368f, 349.591827f);
				return  true;
			}
			else if (bot->GetPositionX() > 1400) //middle down the ramp
			{
				MoveTo(bg->GetMapId(), 1399.362061f, 1405.105347f, 341.481476f);
				return  true;
			}
			else if (bot->GetPositionX() > 1357) //at the gate
			{
				MoveTo(bg->GetMapId(), 1356.088501f, 1393.451660f, 326.183624f);
				return  true;
			}
			else if (bot->GetPositionX() > 1270) // run the gate side way to the middle field
			{
				MoveTo(bg->GetMapId(), 1269.962158f, 1382.655640f + frand(-2, +2), 308.545288f);
				return true;
			}
		}
		if (bot->Preference < 5) //horde ramp
		{
			if (bot->GetPositionX() > 1099) //move to the horde ramp gate
			{
				MoveTo(bg->GetMapId(), 1096.716797f, 1535.618652f, 315.727539f);
				return  true;
			}
			if (bot->GetPositionX() > 1071) //move the ramp up a piece
			{
				MoveTo(bg->GetMapId(), 1070.089478f, 1538.054443f, 332.460388f);
				return  true;
			}
			if (bot->GetPositionX() > 1050.2) //move the ramp up a piece
			{
				MoveTo(bg->GetMapId(), 1050.089478f, 1538.054443f, 332.460388f);
				return  true;
			}
			if (bot->GetPositionX() > 1032) //up in front of first entrance
			{
				MoveTo(bg->GetMapId(), 1031.764282f, 1454.516235f, 343.337860f);
				return  true;
			}
			if (bot->GetPositionX() > 986) //up in front of first entrance
			{
				MoveTo(bg->GetMapId(), 985.940125f, 1423.260254f, 345.418121f);
				return  true;
			}
			MoveTo(bg->GetMapId(), 919.161316f, 1433.871338f, 345.902771f);
			return  true;
		}
		else { //horde tunnel

			if (bot->GetPositionX() > 1125.9f) //move to the horde entrance
			{
				MoveTo(bg->GetMapId(), 1125.778076f, 1452.059937f, 315.698883f);
				return  true;
			}
			else if (bot->GetPositionX() > 1006.7f) //move to the horde fasty
			{
				MoveTo(bg->GetMapId(), 1006.590210f, 1450.435059f, 335.721283f);
				return  true;
			}
			else { //move to the flag position
				MoveTo(bg->GetMapId(), 919.161316f, 1433.871338f, 345.902771f);
				bot->Preference = urand(0, 9); //reset preference
				return  true;
			}
		}
	}
	return false;
}

//is being called, when flag "+warsong" is set
bool BGTacticsWS::Execute(Event event)
{
	if (!bot->InBattleGround())
		return false;
	if (bot->isDead())
	{
		bot->GetMotionMaster()->MovementExpired();
	}
	//Check for Warsong.
	if (bot->GetBattleGround()->GetTypeID() == BattleGroundTypeId::BATTLEGROUND_WS)
	{
		ai->SetMaster(NULL);
		if (bot->HasAuraType(SPELL_AURA_SPIRIT_OF_REDEMPTION))
			bot->RemoveSpellsCausingAura(SPELL_AURA_SPIRIT_OF_REDEMPTION);
		if (bot->isInCombat())
		{
			if (!wasInCombat)
				bot->GetMotionMaster()->MovementExpired();
		}
		wasInCombat = bot->isInCombat();
		//In Warsong, the bots run to the other flag and take it, try to get back and protect each other.
		//If our flag was taken, pures will try to get it back
		BattleGroundWS* bg = (BattleGroundWS *)bot->GetBattleGround();
		if (bg != NULL && !bot->isDead())
		{
			//If flag is close, always click it.
			bool alreadyHasFlag = bg->GetFlagState(bg->GetOtherTeam(bot->GetTeam())) == BG_WS_FLAG_STATE_ON_PLAYER;
			if (!alreadyHasFlag)
			{
				GameObject* target_obj = bg->GetBgMap()->GetGameObject(bg->GetFlagKeeper(bg->GetOtherTeam(bot->GetTeam()) == ALLIANCE ? TEAM_HORDE : TEAM_ALLIANCE));
				if (target_obj == NULL)
				{
					if (bot->GetTeam() == HORDE)
					{
						target_obj = bg->GetBgMap()->GetGameObject(bg->m_BgObjects[BG_WS_OBJECT_A_FLAG]);
					}
					else
					{
						target_obj = bg->GetBgMap()->GetGameObject(bg->m_BgObjects[BG_WS_OBJECT_H_FLAG]);
					}
				}
				if (bot->IsWithinDistInMap(target_obj, 10))
				{
					bg->EventPlayerClickedOnFlag(bot, target_obj);
					return true;
				}
			}
			// startup phase
			if (bg->GetStartDelayTime()>0)
			{
				if (bot->GetTeam() == ALLIANCE) //you.. may... NOT.. PASS!
				{
					if (bot->GetPositionX() <1507)
					{
						bot->GetMotionMaster()->MovementExpired();
						MoveTo(bg->GetMapId(), 1510, bot->GetPositionY(), bot->GetPositionZ());
						return false;
					}
				}
				else {
					if (bot->GetPositionX() > 947)
					{
						bot->GetMotionMaster()->MovementExpired();
						MoveTo(bg->GetMapId(), 950, bot->GetPositionY(), bot->GetPositionZ());
						return false;
					}
				}
				if (!bot->isInCombat())
				{
					//= bg->GetTeamStartPosition(BattleGround::GetTeamIndexByTeamId(bot->GetTeam()));
					for (std::map<ObjectGuid, BattleGroundPlayer>::const_iterator itr = bg->GetPlayers().begin(); itr != bg->GetPlayers().end(); ++itr)
					{
						if (urand(0, 100) < 2)
						{
							if (bot->GetTeam() == ALLIANCE)
								return MoveNear(bg->GetMapId(), 1523.811, 1481.757, 352.008, frand(1.0, 5.0));
							else
								return MoveNear(bg->GetMapId(), 933.331, 1433.724, 345.536, frand(1.0, 5.0));
						}
					}
				}
				return true;
			}
			//check if we are moving or in combat
			if (!IsMovingAllowed() || bot->IsMoving())
				return false;
			bool moving = false;
			//Only go for directive, if not in combat
			if (!bot->isInCombat())
			{
				moving = consumeHealthy(bg);
				if (!moving)
					moving = moveTowardsEnemyFlag(bg);
				if (!moving)
					moving = homerun(bg);
			}
			if (!moving)
			{
				if (bg->GetBgMap()->GetGameObject(bg->m_BgObjects[BG_WS_OBJECT_A_FLAG]) == NULL &&
					bg->GetBgMap()->GetGameObject(bg->m_BgObjects[BG_WS_OBJECT_H_FLAG]) == NULL)
				{
					float distance = sPlayerbotAIConfig.tooCloseDistance + sPlayerbotAIConfig.grindDistance * urand(3, 10) / 10.0f;

					Map* map = bot->GetMap();

					for (int i = 0; i < 10; ++i)
					{
						float x = bot->GetPositionX();
						float y = bot->GetPositionY();
						float z = bot->GetPositionZ();
						x += urand(0, distance) - distance / 2;
						y += urand(0, distance) - distance / 2;
						bot->UpdateGroundPositionZ(x, y, z);

						//if (map->IsInWater(x, y, z))
						//	continue;

						bool moved = MoveNear(bot->GetMapId(), x, y, z);
						if (moved)
							break;
					}
				}
				else
				{
					AttackAnythingAction* action = new AttackAnythingAction(ai);
					action->Execute(event);
				}
			}
		}
	}
	return true;
}
