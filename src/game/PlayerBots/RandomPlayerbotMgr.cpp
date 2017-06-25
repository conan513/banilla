#include "../pchdef.h"
#include "playerbot.h"
#include "PlayerbotAIConfig.h"
#include "PlayerbotFactory.h"
#include "../../shared/Database/DatabaseEnv.h"
#include "PlayerbotAI.h"
#include "Guild.h"
#include "DBCStores.h"
#include "AiFactory.h"
#include "MapManager.h"
#include "PlayerbotCommandServer.h"
#include "GuildTaskMgr.h"
#include <thread>
#include "BattleGround.h"
#include "PlayerbotCommandServer.h"
#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CellImpl.h"
#include "FleeManager.h"

using namespace ai;
using namespace MaNGOS;

INSTANTIATE_SINGLETON_1(RandomPlayerbotMgr);

RandomPlayerbotMgr::RandomPlayerbotMgr() : PlayerbotHolder(), processTicks(0)
{
sPlayerbotCommandServer.Start();
}

RandomPlayerbotMgr::~RandomPlayerbotMgr()
{
}

int RandomPlayerbotMgr::GetMaxAllowedBotCount()
{
	return GetEventValue(0, "bot_count");
	}

void RandomPlayerbotMgr::UpdateAIInternal(uint32 elapsed)
{
    SetNextCheckDelay(sPlayerbotAIConfig.randomBotUpdateInterval * 1000);

    if (!sPlayerbotAIConfig.randomBotAutologin || !sPlayerbotAIConfig.enabled)
        return;

    int maxAllowedBotCount = GetEventValue(0, "bot_count");
    if (!maxAllowedBotCount)
    {
        maxAllowedBotCount = urand(sPlayerbotAIConfig.minRandomBots, sPlayerbotAIConfig.maxRandomBots);
        SetEventValue(0, "bot_count", maxAllowedBotCount,
                urand(sPlayerbotAIConfig.randomBotCountChangeMinInterval, sPlayerbotAIConfig.randomBotCountChangeMaxInterval));
    }

    list<uint32> bots = GetBots();
    int botCount = bots.size();
    int allianceNewBots = 0, hordeNewBots = 0;
    int randomBotsPerInterval = (int)urand(sPlayerbotAIConfig.minRandomBotsPerInterval, sPlayerbotAIConfig.maxRandomBotsPerInterval);
    if (!processTicks)
    {
        if (sPlayerbotAIConfig.randomBotLoginAtStartup)
            randomBotsPerInterval = bots.size();
    }

    while (botCount++ < maxAllowedBotCount)
    {
		if (botCount < maxAllowedBotCount)
			AddRandomBots();
    }

    int botProcessed = 0;
    for (list<uint32>::iterator i = bots.begin(); i != bots.end(); ++i)
    {
        uint32 bot = *i;

        sLog.outString("0:Processing bot %d", bot);

        if (ProcessBot(bot))
            botProcessed++;

        if (botProcessed >= randomBotsPerInterval)
            break;
    }

	ostringstream out; out << "Random bots are now scheduled to be processed in the background. Next re-schedule in " << sPlayerbotAIConfig.randomBotUpdateInterval << " seconds";
	sLog.outString(out.str().c_str());
	sWorld.SendWorldText(3, out.str().c_str());

    if ((processTicks++)%10 == 1)
        PrintStats();
}

uint32 RandomPlayerbotMgr::AddRandomBots()
{
	set<uint32> bots;

	QueryResult* results = CharacterDatabase.PQuery(
		"select `bot` from ai_playerbot_random_bots where event = 'add'");

	if (results)
	{
		do
		{
			Field* fields = results->Fetch();
			uint32 bot = fields[0].GetUInt32();
			bots.insert(bot);
		} while (results->NextRow());
		delete results;
	}

	vector<uint32> guids;
	int maxAllowedBotCount = GetEventValue(0, "bot_count");
	for (list<uint32>::iterator i = sPlayerbotAIConfig.randomBotAccounts.begin(); i != sPlayerbotAIConfig.randomBotAccounts.end(); i++)
	{
		uint32 accountId = *i;
		if (!sAccountMgr.GetCharactersCount(accountId))
			continue;

		QueryResult* result = CharacterDatabase.PQuery("SELECT guid, race FROM characters WHERE account = '%u'", accountId);
		if (!result)
			continue;

		do
		{
			Field* fields = result->Fetch();
			uint32 guid = fields[0].GetUInt32();
			uint8 race = fields[1].GetUInt8();
			bool alliance = guids.size() % 2 == 0;
			if (bots.find(guid) == bots.end() &&
				((alliance && IsAlliance(race)) || ((!alliance && !IsAlliance(race))
					)))
			{
				guids.push_back(guid);
				uint32 bot = guid;
				SetEventValue(bot, "add", 1, urand(sPlayerbotAIConfig.minRandomBotInWorldTime, sPlayerbotAIConfig.maxRandomBotInWorldTime));
				uint32 randomTime = 30 + urand(sPlayerbotAIConfig.randomBotUpdateInterval, sPlayerbotAIConfig.randomBotUpdateInterval * 3);
				ScheduleRandomize(bot, randomTime);
				bots.insert(bot);
				sLog.outString("New random bot %d added", bot);
				if (bots.size() >= maxAllowedBotCount) break;
			}
		} while (result->NextRow());
		delete result;
	}

	return guids.size();
}

void RandomPlayerbotMgr::ScheduleRandomize(uint32 bot, uint32 time)
{

    SetEventValue(bot, "randomize", 1, time);
    SetEventValue(bot, "logout", 1, time + 30 + urand(sPlayerbotAIConfig.randomBotUpdateInterval, sPlayerbotAIConfig.randomBotUpdateInterval * 3));
}

void RandomPlayerbotMgr::ScheduleTeleport(uint32 bot)
{

    SetEventValue(bot, "teleport", 1, 60 + urand(sPlayerbotAIConfig.randomBotUpdateInterval, sPlayerbotAIConfig.randomBotUpdateInterval * 3));
}

bool RandomPlayerbotMgr::ProcessBot(uint32 bot)
{

	uint32 isValid = GetEventValue(bot, "add");
	if (!isValid)
	{
		Player* player = GetPlayerBot(bot);
		if (!player || !player->GetGroup())
		{
			sLog.outString("0:Bot %d expired", bot);
			SetEventValue(bot, "add", 0, 0);
		}
		return true;
	}

	if (!GetPlayerBot(bot))
	{
		sLog.outString("0:Bot %d logged in", bot);
		AddPlayerBot(bot, 0);
		if (!GetEventValue(bot, "online"))
		{
			SetEventValue(bot, "online", 1, sPlayerbotAIConfig.minRandomBotInWorldTime);
		}
		return true;
	}

	Player* player = GetPlayerBot(bot);
	if (!player)
		return false;

	if (player->InBattleGround() && player->isDead())
	{
		BattleGround *bg = player->GetBattleGround();
		const WorldSafeLocsEntry *pos = bg->GetClosestGraveYard(player);
		if (!player->IsWithinDist3d(pos->x, pos->y, pos->z, 3.0))
		{
			// Special handle for BattleGround maps
			sLog.outString("bot %s died in a BattleGround. Try to resurrect.", player->GetName());
			SetEventValue(bot, "dead", 1, 5);
			//this is spirit release confirm?			
			player->RemovePet(PET_SAVE_NOT_IN_SLOT);
			player->BuildPlayerRepop();
			player->SpawnCorpseBones();
			player->RepopAtGraveyard();
		}
		else {
			player->ResurrectPlayer(1.0f);
		}
		return false;
	}

	if (player->InBattleGround())
	{
		return false;
	}

	//sLog.outString("Bot %s added", player->GetName());

	PlayerbotAI* ai = player->GetPlayerbotAI();
	if (!ai)
		return false;

	if (player->GetGroup())
	{
		sLog.outString("0:Skipping bot %d as it is in group", bot);
		return false;
	}

	ai->GetAiObjectContext()->GetValue<bool>("random bot update")->Set(true);
	return true;
}

bool RandomPlayerbotMgr::ProcessBot(Player* player)
{
	player->GetPlayerbotAI()->GetAiObjectContext()->GetValue<bool>("random bot update")->Set(false);
	
	uint32 bot = player->GetGUIDLow();
    if (player->isDead())
    {
        if (!GetEventValue(bot, "dead"))
        {
            sLog.outString("0:Setting dead flag for bot %d", bot);
            uint32 randomTime = urand(sPlayerbotAIConfig.minRandomBotReviveTime, sPlayerbotAIConfig.maxRandomBotReviveTime);
            SetEventValue(bot, "dead", 1, randomTime);
            SetEventValue(bot, "revive", 1, randomTime - 60);
            return false;
        }

        if (!GetEventValue(bot, "revive"))
        {
			Revive(player);
            return true;
        }

        return false;
    }

	if (player->GetGuildId())
	{
		Guild* guild = sGuildMgr.GetGuildById(player->GetGuildId());
		if (guild->GetLeaderGuid().GetRawValue() == player->GetGUID()) {
			for (vector<Player*>::iterator i = players.begin(); i != players.end(); ++i)
				sGuildTaskMgr.Update(*i, player);
		}
	}

	bool takePlayerLevel = sPlayerbotAIConfig.randomBotBracketPlayer;
	if (takePlayerLevel)
	{
		uint32 maxLevel = sPlayerbotAIConfig.randomBotMaxLevel;
		uint32 minLevel = sPlayerbotAIConfig.randomBotMinLevel;
		uint32 level = 0;
		if (maxLevel > sWorld.getConfig(CONFIG_UINT32_MAX_PLAYER_LEVEL))
			 maxLevel = sWorld.getConfig(CONFIG_UINT32_MAX_PLAYER_LEVEL);
		if (minLevel < 1)
			 minLevel = 1;
		if (takePlayerLevel)
		{
			level = GetMasterLevel();
			if (level == 0)
			{
				level = urand(minLevel, maxLevel);
			}
			minLevel = level - level % 10;
			maxLevel = level - (level % 10) + 9;
			level = urand(minLevel, maxLevel);
		}
		if (player->getLevel() < minLevel)
		{
			int oldlevel = player->getLevel();
			player->SetLevel(level - 1);
			IncreaseLevel(player);
			sLog.outString("Bot %d was leveled from %d to %d", bot, oldlevel, player->getLevel());
			}
		}

    uint32 randomize = GetEventValue(bot, "randomize");
    if (!randomize)
    {
        sLog.outString("0:Randomizing bot %d", bot);
        Randomize(player);
        //std::thread randomize(&RandomPlayerbotMgr::Randomize,this,player);
        //randomize.detach();
        uint32 randomTime = urand(sPlayerbotAIConfig.minRandomBotRandomizeTime, sPlayerbotAIConfig.maxRandomBotRandomizeTime);
        ScheduleRandomize(bot, randomTime);
        return true;
    }

    uint32 logout = GetEventValue(bot, "logout");
    if (!logout)
    {
        sLog.outString("0:Logging out bot %d", bot);
        LogoutPlayerBot(bot);
        SetEventValue(bot, "logout", 1, sPlayerbotAIConfig.maxRandomBotInWorldTime);
        return true;
    }

    uint32 teleport = GetEventValue(bot, "teleport");
    if (!teleport)
    {
        sLog.outString("0:Random teleporting bot %d", bot);
		RandomTeleportForLevel(player);
        //std::thread random_tele_level(&RandomPlayerbotMgr::RandomTeleportForLevel,this,ai->GetBot());
        //random_tele_level.detach();
        SetEventValue(bot, "teleport", 1, sPlayerbotAIConfig.maxRandomBotInWorldTime);
        return true;
    }

    return false;
}

void RandomPlayerbotMgr::Revive(Player* player)
{
	uint32 bot = player->GetGUIDLow();
	sLog.outString("Reviving dead bot %d", bot);
	SetEventValue(bot, "dead", 0, 0);
	SetEventValue(bot, "revive", 0, 0);
	RandomTeleport(player);
}

void RandomPlayerbotMgr::RandomTeleport(Player* bot, vector<WorldLocation> &locs)
{
	if (bot->InBattleGround())
		return;

    if (bot->IsBeingTeleported())
        return;

    if (locs.empty())
    {
         sLog.outError("0:Cannot teleport bot %s - no locations available", bot->GetName());
        return;
    }

    for (int attemtps = 0; attemtps < locs.size()*2; ++attemtps)
    {
		int index = urand(0, locs.size() - 1);
		WorldLocation loc = locs[index];
		float x = loc.coord_x + (attemtps > 0 ? urand(0, sPlayerbotAIConfig.grindDistance) - sPlayerbotAIConfig.grindDistance / 2 : 0);
		float y = loc.coord_y + (attemtps > 0 ? urand(0, sPlayerbotAIConfig.grindDistance) - sPlayerbotAIConfig.grindDistance / 2 : 0);
		float z = loc.coord_z;
		float z = loc.coord_z;

		Map* map = sMapMgr.FindMap(loc.mapid, 0);
		if (!map)
			continue;

		if (map->IsBattleGround() || map->IsDungeon() || map->IsRaid())
			continue;

		const TerrainInfo * terrain = map->GetTerrain();
		if (!terrain)
			continue;

		if (!terrain->IsOutdoors(x, y, z) ||
			terrain->IsUnderWater(x, y, z) ||
			terrain->IsInWater(x, y, z))
			continue;


		float ground = map->GetHeight(x, y, z + 0.5f);
		if (ground <= INVALID_HEIGHT)
			continue;

		uint32 areaId = terrain->GetAreaId(x, y, z);

		if (!areaId)
			continue;

		AreaTableEntry const* area = GetAreaEntryByAreaID(areaId);
		if (!area)
			continue;

    //Some exceptions:
        if (IsAlliance(bot->getRace()))
        {
            vector<uint32>::iterator i = find(horde_areas.begin(), horde_areas.end(), areaId);

            if (i != horde_areas.end())
                continue;
        }
        else //horde
        {
            vector<uint32>::iterator i = find(alliance_areas.begin(), alliance_areas.end(), areaId);

            if (i != alliance_areas.end())
                continue;
        }

		if (strstr(area->area_name[0], "UNUSED"))
			continue;

        float ground = map->GetHeight(x, y, z + 0.5f);
        if (ground <= INVALID_HEIGHT)
            continue;

        vector<uint32>::iterator a = find(active_areas.begin(), active_areas.end(), areaId);
        if (a == active_areas.end())
        {
            if (active_areas.size() < MAX_NUMBER_OF_AREAS)
                active_areas.insert(a,areaId);
            else continue;
        }

        z = 0.05f + ground;
		sLog.outString("Random teleporting bot %s to %s %f,%f,%f (%u/%u locations)",
			bot->GetName(), area->area_name[0], x, y, z, attemtps, locs.size());

        bot->GetMotionMaster()->Clear();
        bot->TeleportTo(loc.mapid, x, y, z, 0);
        return;
    }

     sLog.outError("0:Cannot teleport bot %s - no locations available", bot->GetName());
}

void RandomPlayerbotMgr::RandomTeleportForLevel(Player* bot)
{
	if (bot->InBattleGround())
		return;

 sLog.outString("0:Preparing location to random teleporting bot %s for level %u", bot->GetName(), bot->getLevel());

     if (locsPerLevelCache[bot->getLevel()].empty()) {
         QueryResult* results = WorldDatabase.PQuery("select map, position_x, position_y, position_z "
             "from (select map, position_x, position_y, position_z, avg(t.maxlevel), avg(t.minlevel), "
             "%u - (avg(t.maxlevel) + avg(t.minlevel)) / 2 delta "
             "from creature c inner join creature_template t on c.id = t.entry group by t.entry) q "
             "where delta >= 0 and delta <= %u and map in (%s) and not exists ( "
             "select map, position_x, position_y, position_z from "
             "("
             "select map, c.position_x, c.position_y, c.position_z, avg(t.maxlevel), avg(t.minlevel), "
             "%u - (avg(t.maxlevel) + avg(t.minlevel)) / 2 delta "
             "from creature c "
             "inner join creature_template t on c.id = t.entry group by t.entry "
             ") q1 "
             "where delta > %u and q1.map = q.map "
             "and sqrt("
             "(q1.position_x - q.position_x)*(q1.position_x - q.position_x) +"
             "(q1.position_y - q.position_y)*(q1.position_y - q.position_y) +"
             "(q1.position_z - q.position_z)*(q1.position_z - q.position_z)"
             ") < %u) ORDER BY RAND()",
             bot->getLevel(),
             sPlayerbotAIConfig.randomBotTeleLevel,
             sPlayerbotAIConfig.randomBotMapsAsString.c_str(),
             bot->getLevel(),
             sPlayerbotAIConfig.randomBotTeleLevel,
             (uint32)sPlayerbotAIConfig.sightDistance);
    if (results)
    {
            do
             {
                 Field* fields = results->Fetch();
                 uint16 mapId = fields[0].GetUInt16();
                 float x = fields[1].GetFloat();
                 float y = fields[2].GetFloat();
                 float z = fields[3].GetFloat();
                 WorldLocation loc(mapId, x, y, z, 0);
                 locsPerLevelCache[bot->getLevel()].push_back(loc);
             } while (results->NextRow());
         }
    }
    sLog.outString("Found...");
    RandomTeleport(bot, locsPerLevelCache[bot->getLevel()]);
}

void RandomPlayerbotMgr::RandomTeleport(Player* bot)
{
	if (bot->InBattleGround())
		return;

	vector<WorldLocation> locs;

	FleeManager manager(bot, sPlayerbotAIConfig.randomBotTeleportDistance, 0);
	float rx, ry, rz;
	if (manager.CalculateDestination(&rx, &ry, &rz))
	{
		WorldLocation loc(bot->GetMapId(), rx, ry, rz);
		locs.push_back(loc);
		return;
	}

	list<Unit*> targets;
	float range = sPlayerbotAIConfig.randomBotTeleportDistance;
	MaNGOS::AnyUnitInObjectRangeCheck u_check(bot, range);
	MaNGOS::UnitListSearcher<MaNGOS::AnyUnitInObjectRangeCheck> searcher(targets, u_check);
	Cell::VisitAllObjects(bot, searcher, range);

	for (list<Unit *>::iterator i = targets.begin(); i != targets.end(); ++i)
	{
		Unit* unit = *i;
		WorldLocation loc;
		unit->GetPosition(loc);
		locs.push_back(loc);
	}

	RandomTeleport(bot, locs);
	Refresh(bot);
}

void RandomPlayerbotMgr::Randomize(Player* bot)
{
	if (!bot->CanProcess())
		return;

	bot->StartProcessing();

	if (bot->getLevel() == 1)
	{
		//std::thread RandomizingFirst(&RandomPlayerbotMgr::RandomizeFirst, this, bot);
		//RandomizingFirst.detach();
		RandomizeFirst(bot);
	}
	else
	{
		//std::thread IncreasingLevel(&RandomPlayerbotMgr::IncreaseLevel, this, bot);
		//IncreasingLevel.detach();
		IncreaseLevel(bot);
	}
        
	 bot->StopProcessing();
}

void RandomPlayerbotMgr::IncreaseLevel(Player* bot)
{
     if (!IsRandomBot(bot))
        return;

    uint32 maxLevel = sWorld.getConfig(CONFIG_UINT32_MAX_PLAYER_LEVEL);
    uint32 level = min((uint32)(bot->getLevel() + 1), maxLevel);
    PlayerbotFactory factory(bot, level);
    if (bot->GetGuildId())
        factory.Refresh();
    else
        factory.Randomize();
    RandomTeleportForLevel(bot);
}

void RandomPlayerbotMgr::RandomizeFirst(Player* bot)
{
	bool takePlayerLevel = sPlayerbotAIConfig.randomBotBracketPlayer;
	uint32 maxLevel = sPlayerbotAIConfig.randomBotMaxLevel;
	uint32 minLevel = sPlayerbotAIConfig.randomBotMinLevel;
	uint32 level = 0;
	if (maxLevel > sWorld.getConfig(CONFIG_UINT32_MAX_PLAYER_LEVEL))
		maxLevel = sWorld.getConfig(CONFIG_UINT32_MAX_PLAYER_LEVEL);
	if (minLevel < 1)
		minLevel = 1;
	if (takePlayerLevel)
	{
		level = GetMasterLevel();
		if (level == 0)
		{
			level = urand(minLevel, maxLevel);
		}
		minLevel = level - level % 10;
		maxLevel = level - (level % 10) + 9;
	}
	for (int attempt = 0; attempt < 10; ++attempt)
	{
		vector<GameTele const*> locs;
		int index = urand(0, sPlayerbotAIConfig.randomBotMaps.size() - 1);

		uint16 mapId = sPlayerbotAIConfig.randomBotMaps[index];

		vector<GameTele const*> locs;
		GameTeleMap const & teleMap = sObjectMgr.GetGameTeleMap();
		for (GameTeleMap::const_iterator itr = teleMap.begin(); itr != teleMap.end(); ++itr)
		{
			GameTele const* tele = &itr->second;
			if (tele->mapId == mapId)
				locs.push_back(tele);
		}


		index = urand(0, locs.size() - 1);
		if (index >= locs.size())
			return;

		GameTele const* tele = locs[index];
		//caching.. if not, it will create excessive database load
		if (mapIdToLevel.find(tele->mapId) == mapIdToLevel.end())
		{
			level = GetZoneLevel(tele->mapId, tele->position_x, tele->position_y, tele->position_z);
			mapIdToLevel.emplace(tele->mapId, level);
		}
		else {
			level = mapIdToLevel[tele->mapId];
		}
		if (level > maxLevel || level < minLevel)
			continue;

		if (level <= 0) level = 1;
		if (!takePlayerLevel)
		{
			if (urand(0, 100) < 100 * sPlayerbotAIConfig.randomBotMaxLevelChance)
				level = maxLevel;
		}

		PlayerbotFactory factory(bot, level);
		factory.CleanRandomize();
		RandomTeleportForLevel(bot);
		break;
	}
}

uint32 RandomPlayerbotMgr::GetMasterLevel()
{
	if (masterLevel == 0)
	{
		QueryResult* results = CharacterDatabase.PQuery("select level from characters where cinematic = 1 order by online desc limit 1");
		if (results)
		{
			Field* fields = results->Fetch();
			masterLevel = fields[0].GetUInt8();
		}
	}
	return masterLevel;
}



uint32 RandomPlayerbotMgr::GetZoneLevel(uint16 mapId, float teleX, float teleY, float teleZ)
{
    uint32 maxLevel = sWorld.getConfig(CONFIG_UINT32_MAX_PLAYER_LEVEL);

	uint32 level;
    QueryResult* results = WorldDatabase.PQuery("select avg(t.minlevel) minlevel, avg(t.maxlevel) maxlevel from creature c "
            "inner join creature_template t on c.id = t.entry "
            "where map = '%u' and minlevel > 1 and abs(position_x - '%f') < '%u' and abs(position_y - '%f') < '%u'",
            mapId, teleX, sPlayerbotAIConfig.randomBotTeleportDistance / 2, teleY, sPlayerbotAIConfig.randomBotTeleportDistance / 2);

    if (results)
    {
        Field* fields = results->Fetch();
        uint8 minLevel = fields[0].GetUInt8();
        uint8 maxLevel = fields[1].GetUInt8();
        level = urand(minLevel, maxLevel);
        if (level > maxLevel)
            level = maxLevel;
    }
    else
    {
        level = urand(1, maxLevel);
    }

    return level;
}

void RandomPlayerbotMgr::Refresh(Player* bot)
{
	if (bot->InBattleGround())
		return;
	sLog.outString("Refreshing bot %s", bot->GetName());
	if (bot->isDead())
	{
		bot->ResurrectPlayer(1.0f);
		bot->SpawnCorpseBones();
		bot->GetPlayerbotAI()->ResetStrategies();
	}

	bot->GetPlayerbotAI()->Reset();

	HostileReference *ref = bot->getHostileRefManager().getFirst();
	while (ref)
	{
		ThreatManager *threatManager = ref->getSource();
		Unit *unit = threatManager->getOwner();
		float threat = ref->getThreat();

		unit->RemoveAllAttackers();
		unit->ClearInCombat();

		ref = ref->next();
	}

	bot->RemoveAllAttackers();
	bot->ClearInCombat();

	bot->DurabilityRepairAll(false, 1.0f);
//	bot->SetFullHealth();
	bot->SetPvP(true);

	if (bot->GetMaxPower(POWER_MANA) > 0)
		bot->SetPower(POWER_MANA, bot->GetMaxPower(POWER_MANA));

	if (bot->GetMaxPower(POWER_ENERGY) > 0)
		bot->SetPower(POWER_ENERGY, bot->GetMaxPower(POWER_ENERGY));
}


bool RandomPlayerbotMgr::IsRandomBot(Player* bot)
{
     return IsRandomBot(bot->GetGUID());
}

bool RandomPlayerbotMgr::IsRandomBot(uint32 bot)
{
    return GetEventValue(bot, "add");
}

list<uint32> RandomPlayerbotMgr::GetBots()
{
    list<uint32> bots;

    QueryResult* results = CharacterDatabase.Query(
            "select bot from ai_playerbot_random_bots where owner = 0 and event = 'add'");

    if (results)
    {
        do
        {
            Field* fields = results->Fetch();
            uint32 bot = fields[0].GetUInt32();

        } while (results->NextRow());
    }

    return bots;
}

uint32 RandomPlayerbotMgr::GetEventValue(uint32 bot, string event)
{

    uint32 value = 0;

    QueryResult* results = CharacterDatabase.PQuery(
            "select `value`, `time`, validIn from ai_playerbot_random_bots where owner = 0 and bot = '%u' and event = '%s'",
            bot, event.c_str());

    if (results)
    {
        Field* fields = results->Fetch();
        value = fields[0].GetUInt32();
        uint32 lastChangeTime = fields[1].GetUInt32();
        uint32 validIn = fields[2].GetUInt32();
        if ((time(0) - lastChangeTime) >= validIn)
            value = 0;
    }

    return value;
}

uint32 RandomPlayerbotMgr::SetEventValue(uint32 bot, string event, uint32 value, uint32 validIn)
{
    CharacterDatabase.PExecute("delete from ai_playerbot_random_bots where owner = 0 and bot = '%u' and event = '%s'",
            bot, event.c_str());
    if (value)
    {
        CharacterDatabase.PExecute(
                "insert into ai_playerbot_random_bots (owner, bot, `time`, validIn, event, `value`) values ('%u', '%u', '%u', '%u', '%s', '%u')",
                0, bot, (uint32)time(0), validIn, event.c_str(), value);
    }

    return value;
}

bool RandomPlayerbotMgr::HandlePlayerbotConsoleCommand(ChatHandler* handler, char const* args)
{
    if (!sPlayerbotAIConfig.enabled)
    {
         sLog.outError("Playerbot system is currently disabled!");
        return false;
    }

    if (!args || !*args)
    {
         sLog.outError("Usage: rndbot stats/update/reset/init/refresh/add/remove");
        return false;
    }

    string cmd = args;

    if (cmd == "reset")
    {
        CharacterDatabase.PExecute("delete from ai_playerbot_random_bots");
        sLog.outString("0:Random bots were reset for all players");
        return true;
    }
    else if (cmd == "stats")
    {
        sRandomPlayerbotMgr.PrintStats();
        return true;
    }
    else if (cmd == "update")
    {
        sRandomPlayerbotMgr.UpdateAIInternal(0);
        return true;
    }
	else if (cmd == "init" || cmd == "refresh" || cmd == "teleport" || cmd == "revive")
    {
		sLog.outString("1:Randomizing bots for %d accounts", sPlayerbotAIConfig.randomBotAccounts.size());
		list<uint32> botIds;
        for (list<uint32>::iterator i = sPlayerbotAIConfig.randomBotAccounts.begin(); i != sPlayerbotAIConfig.randomBotAccounts.end(); ++i)
        {
            uint32 account = *i;
            if (QueryResult* results = CharacterDatabase.PQuery("SELECT guid FROM characters where account = '%u'", account))
            {
                do
                {
                    
					Field* fields = results->Fetch();

					uint32 botId = fields[0].GetUInt32();
					ObjectGuid guid = ObjectGuid(HIGHGUID_PLAYER, botId);
					Player* bot = sObjectMgr.GetPlayer(guid);
					if (!bot)
						continue;

					botIds.push_back(botId);

                    if (!bot)
                        continue;
                } while (results->NextRow());
            }
        }

        int processed = 0;
		for (list<uint32>::iterator i = botIds.begin(); i != botIds.end(); ++i)
        {
			ObjectGuid guid = ObjectGuid(HIGHGUID_PLAYER, *i);
			Player* bot = sObjectMgr.GetPlayer(guid);
            if (!bot)
                continue;

            sLog.outString("[%u/%u] Processing command '%s' for bot '%s'",
                    processed++, botIds.size(), cmd.c_str(), bot->GetName());

            if (cmd == "init")
            {
                sRandomPlayerbotMgr.RandomizeFirst(bot);
            }
            else if (cmd == "teleport")
            {
                sRandomPlayerbotMgr.RandomTeleportForLevel(bot);
            }
			else if (cmd == "revive")
			{
				sRandomPlayerbotMgr.Revive(bot);
			}
            else
            {
                bot->SetLevel(bot->getLevel() - 1);
                sRandomPlayerbotMgr.IncreaseLevel(bot);
            }
            uint32 randomTime = urand(sPlayerbotAIConfig.minRandomBotRandomizeTime, sPlayerbotAIConfig.maxRandomBotRandomizeTime);
            CharacterDatabase.PExecute("update ai_playerbot_random_bots set validIn = '%u' where event = 'randomize' and bot = '%u'",
                    randomTime, bot->GetGUID());
            CharacterDatabase.PExecute("update ai_playerbot_random_bots set validIn = '%u' where event = 'logout' and bot = '%u'",
                    sPlayerbotAIConfig.maxRandomBotInWorldTime, bot->GetGUID());
        }
        return true;
    }
    else
    {
        list<string> messages = sRandomPlayerbotMgr.HandlePlayerbotCommand(args, NULL);
        for (list<string>::iterator i = messages.begin(); i != messages.end(); ++i)
        {
			sLog.outString(i->c_str());
        }

        return true;
    }

    return false;
}

void RandomPlayerbotMgr::HandleCommand(uint32 type, const string& text, Player& fromPlayer)
{
    for (PlayerBotMap::const_iterator it = GetPlayerBotsBegin(); it != GetPlayerBotsEnd(); ++it)
    {
        Player* const bot = it->second;
        bot->GetPlayerbotAI()->HandleCommand(type, text, fromPlayer);
    }
}

void RandomPlayerbotMgr::OnPlayerLogout(Player* player)
{
    for (PlayerBotMap::const_iterator it = GetPlayerBotsBegin(); it != GetPlayerBotsEnd(); ++it)
    {
        Player* const bot = it->second;

         PlayerbotAI* ai = bot->GetPlayerbotAI();
        if (player == ai->GetMaster())
        {
			ai->SetMaster(NULL);
			if (!bot->InBattleGround())
				ai->ResetStrategies();
        }
    }

    if (!player->GetPlayerbotAI())
    {
        vector<Player*>::iterator i = find(players.begin(), players.end(), player);
        if (i != players.end())
            players.erase(i);
    }
}

void RandomPlayerbotMgr::OnPlayerLogin(Player* player)
{
    for (PlayerBotMap::const_iterator it = GetPlayerBotsBegin(); it != GetPlayerBotsEnd(); ++it)
    {
        Player* const bot = it->second;

        if (player == bot || player->GetPlayerbotAI())
            continue;

        Group* group = bot->GetGroup();
        if (!group)
            continue;

        for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next())
        {
            Player* member = gref->getSource();
            PlayerbotAI* ai = bot->GetPlayerbotAI();
            if (member == player && (!ai->GetMaster() || ai->GetMaster()->GetPlayerbotAI()))
            {
				if (!bot->InBattleGround())
				{
					ai->SetMaster(player);
					ai->ResetStrategies();
					ai->TellMaster("Hello");
				}
                break;
            }
        }
    }

    if (player->GetPlayerbotAI())
        return;

    players.push_back(player);
}

Player* RandomPlayerbotMgr::GetRandomPlayer()
{
    if (players.empty())
        return NULL;

    uint32 index = urand(0, players.size() - 1);
    return players[index];
}

void RandomPlayerbotMgr::PrintStats()
{
	sLog.outString("%d Random Bots online", playerBots.size());

    map<uint32, int> alliance, horde;
    for (uint32 i = 0; i < 10; ++i)
    {
        alliance[i] = 0;
        horde[i] = 0;
    }

    map<uint8, int> perRace, perClass, spec1, spec2, spec3;
    for (uint8 race = RACE_HUMAN; race < MAX_RACES; ++race)
    {
        perRace[race] = 0;
    }
    for (uint8 cls = CLASS_WARRIOR; cls < MAX_CLASSES; ++cls)
    {
        perClass[cls] = 0;
        spec1[cls] = 0;
        spec2[cls] = 0;
        spec3[cls] = 0;
    }

    int dps = 0, heal = 0, tank = 0, active = 0;
    for (PlayerBotMap::iterator i = playerBots.begin(); i != playerBots.end(); ++i)
    {
        Player* bot = i->second;
        if (IsAlliance(bot->getRace()))
            alliance[bot->getLevel() / 10]++;
        else
            horde[bot->getLevel() / 10]++;

        perRace[bot->getRace()]++;
        perClass[bot->getClass()]++;

		if (bot->GetPlayerbotAI()->IsActive())
			active++;

        int spec = AiFactory::GetPlayerSpecTab(bot);

        if (spec == 0)
            spec1[bot->getClass()]++;
        else if (spec == 1)
            spec2[bot->getClass()]++;
        else if (spec == 2)
            spec3[bot->getClass()]++;

        switch (bot->getClass())
        {
        case CLASS_DRUID:
            if (spec == 2)
                heal++;
            else
                dps++;
            break;
        case CLASS_PALADIN:
            if (spec == 1)
                tank++;
            else if (spec == 0)
                heal++;
            else
                dps++;
            break;
        case CLASS_PRIEST:
            if (spec != 2)
                heal++;
            else
                dps++;
            break;
        case CLASS_SHAMAN:
            if (spec == 2)
                heal++;
            else
                dps++;
            break;
        case CLASS_WARRIOR:
            if (spec == 2)
                tank++;
            else
                dps++;
            break;
        default:
            dps++;
            break;
        }
    }

    sLog.outString("Per level:");
    uint32 maxLevel = sWorld.getConfig(CONFIG_UINT32_MAX_PLAYER_LEVEL);
    for (uint32 i = 0; i < 10; ++i)
    {
        if (!alliance[i] && !horde[i])
            continue;

        uint32 from = i*10;
        uint32 to = min(from + 9, maxLevel);
        if (!from) from = 1;
        sLog.outString("    %d..%d: %d alliance, %d horde", from, to, alliance[i], horde[i]);
    }
    sLog.outString("Per race:");
    for (uint8 race = RACE_HUMAN; race < MAX_RACES; ++race)
    {
        if (perRace[race])
            sLog.outString("    %s: %d", ChatHelper::formatRace(race).c_str(), perRace[race]);
    }
    sLog.outString("Per class:");
    for (uint8 cls = CLASS_WARRIOR; cls < MAX_CLASSES; ++cls)
    {
        if (perClass[cls])
            sLog.outString("    %s: %d (%d/%d/%d)", ChatHelper::formatClass(cls).c_str(), perClass[cls],spec1[cls],spec2[cls],spec3[cls]);
    }
    sLog.outString("Per role:");
    sLog.outString("    tank: %d", tank);
    sLog.outString("    heal: %d", heal);
    sLog.outString("    dps: %d", dps);

	sLog.outString("Active bots: %d", active);
}

double RandomPlayerbotMgr::GetBuyMultiplier(Player* bot)
{
    uint32 id = bot->GetGUID();
    uint32 value = GetEventValue(id, "buymultiplier");
    if (!value)
    {
        value = urand(1, 120);
        uint32 validIn = urand(sPlayerbotAIConfig.minRandomBotsPriceChangeInterval, sPlayerbotAIConfig.maxRandomBotsPriceChangeInterval);
        SetEventValue(id, "buymultiplier", value, validIn);
    }

    return (double)value / 100.0;
}

double RandomPlayerbotMgr::GetSellMultiplier(Player* bot)
{
    uint32 id = bot->GetGUID();
    uint32 value = GetEventValue(id, "sellmultiplier");
    if (!value)
    {
        value = urand(80, 250);
        uint32 validIn = urand(sPlayerbotAIConfig.minRandomBotsPriceChangeInterval, sPlayerbotAIConfig.maxRandomBotsPriceChangeInterval);
        SetEventValue(id, "sellmultiplier", value, validIn);
    }

    return (double)value / 100.0;
}

uint32 RandomPlayerbotMgr::GetLootAmount(Player* bot)
{
    uint32 id = bot->GetGUID();
    return GetEventValue(id, "lootamount");
}

void RandomPlayerbotMgr::SetLootAmount(Player* bot, uint32 value)
{
    uint32 id = bot->GetGUID();
    SetEventValue(id, "lootamount", value, 24 * 3600);
}

uint32 RandomPlayerbotMgr::GetTradeDiscount(Player* bot)
{
    Group* group = bot->GetGroup();
    return GetLootAmount(bot) / (group ? group->GetMembersCount() : 10);
}

string RandomPlayerbotMgr::HandleRemoteCommand(string request)
{
    string::iterator pos = find(request.begin(), request.end(), ',');
    if (pos == request.end())
    {
        ostringstream out; out << "invalid request: " << request;
        return out.str();
    }

    string command = string(request.begin(), pos);
    uint64 guid = atoi(string(pos + 1, request.end()).c_str());
    Player* bot = GetPlayerBot(guid);
    if (!bot)
        return "invalid guid";

    PlayerbotAI *ai = bot->GetPlayerbotAI();
    if (!ai)
        return "invalid guid";

    return ai->HandleRemoteCommand(command);
}

