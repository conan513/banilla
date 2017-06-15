/*
 * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
 * Copyright (C) 2009-2011 MaNGOSZero <https://github.com/mangos/zero>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "InstanceData.h"
#include "Database/DatabaseEnv.h"
#include "Map.h"
#include "Player.h"
#include "ScriptedInstance.h"

void InstanceData::SaveToDB()
{
    // no reason to save BGs/Arenas
    if (instance->IsBattleGround())
        return;

    if (!Save())
        return;

    std::string data = Save();
    CharacterDatabase.escape_string(data);

	std::stringstream ss(data);
	int bossState;
	bool instanceComplete = true;
	int count = 1;

	while (ss >> bossState)
	{
		if ((bossState != DONE) && (bossState != SPECIAL))
		{
			instanceComplete = false;
			break;
		}
		count = count + 1;
	}


	if (instanceComplete)
	{
		CharacterDatabase.PExecute("UPDATE `instance_times` SET `end_time` =  NOW() WHERE `instance_id` = %i", instance->GetInstanceId());
		}

    if (instance->Instanceable())
        CharacterDatabase.PExecute("UPDATE instance SET data = '%s' WHERE id = '%u'", data.c_str(), instance->GetInstanceId());
    else
        CharacterDatabase.PExecute("UPDATE world SET data = '%s' WHERE map = '%u'", data.c_str(), instance->GetId());
}

bool InstanceData::CheckConditionCriteriaMeet(Player const* /*player*/, uint32 map_id, WorldObject const* source, uint32 instance_condition_id) const
{
    sLog.outError("Condition system call InstanceData::CheckConditionCriteriaMeet but instance script for map %u not have implementation for player condition criteria with internal id %u for map %u",
                  instance->GetId(), instance_condition_id, map_id);
    return false;
}

void InstanceData::OnPlayerEnter(Player *player)
{
	if (player->isGameMaster())
	{
		return;
	}

	QueryResult* resultPlayerIds = resultPlayerIds = CharacterDatabase.PQuery("SELECT `player_ids` FROM `instance_times` WHERE `instance_id` = %i", instance->GetInstanceId());
	if (resultPlayerIds)
	{
		Field* fields = resultPlayerIds->Fetch();
		std::string playerIds = fields[0].GetString();
		std::istringstream ss(playerIds);
		int playerId;

		while (ss >> playerId)
		{
			if (playerId == player->GetGUIDLow())
			{
				return;
			}
		}
	}

	CharacterDatabase.PExecute("INSERT INTO `instance_times` (`instance_id`, `map`, `difficulty`, `player_ids`) VALUES (%i, %i, %i, %i) ON DUPLICATE KEY UPDATE `player_ids` = CONCAT(player_ids, ' %i')", instance->GetInstanceId(), instance->GetId(), false, player->GetGUIDLow(), player->GetGUIDLow());
}

void InstanceData::OnPlayerDeath(Player *player)
{
	CharacterDatabase.PExecute("UPDATE `instance_times` SET `deaths` = `deaths`+1 WHERE instance_id = %i", instance->GetInstanceId());
}
