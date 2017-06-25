#include "../pchdef.h"
#include "playerbot.h"
#include "FleeManager.h"
#include "PlayerbotAIConfig.h"
#include "Group.h"
#include "AiFactory.h"
#include "strategy/values/LastMovementValue.h"

using namespace ai;
using namespace std;

void FleeManager::calculateDistanceToPlayers(FleePoint *point)
{
	Group* group = bot->GetGroup();
	if (!group)
		return;

	for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next())
    {
		Player* player = gref->getSource();
		if(player == bot)
			continue;

        uint8 spec = AiFactory::GetPlayerSpecTab(bot);

		float d = player->GetDistance2d(point->x, point->y);
		point->toAllPlayers.probe(d);
		switch (player->getClass()) {
			case CLASS_HUNTER:
			case CLASS_MAGE:
			case CLASS_PRIEST:
			case CLASS_WARLOCK:
				point->toRangedPlayers.probe(d);
				break;
            case CLASS_SHAMAN:
                if (spec == 1)
                    point->toMeleePlayers.probe(d);
                else
                    point->toRangedPlayers.probe(d);
                break;
            case CLASS_DRUID:
                if (spec == 1)
                    point->toMeleePlayers.probe(d);
                else
                    point->toRangedPlayers.probe(d);
                break;
			case CLASS_PALADIN:
			    if (spec == 0)
                    point->toRangedPlayers.probe(d);
                else
                    point->toMeleePlayers.probe(d);
                break;
			case CLASS_ROGUE:
			case CLASS_WARRIOR:
				point->toMeleePlayers.probe(d);
				break;
		}
	}
}

bool FleeManager::calculateDistanceToCreatures(FleePoint *point)
{
	RangePair &distance = point->toCreatures;
    float d = 0;

	list<ObjectGuid> units = *bot->GetPlayerbotAI()->GetAiObjectContext()->GetValue<list<ObjectGuid> >("possible targets");
	for (list<ObjectGuid>::iterator i = units.begin(); i != units.end(); ++i)
    {
		Unit* unit = bot->GetPlayerbotAI()->GetUnit(*i);
		if (!unit)
		    continue;

		float d = unit->GetDistance2d(point->x, point->y);
		if (d <= sPlayerbotAIConfig.aggroDistance)
		    continue;

		distance.probe(d);
	}

	return (d > sPlayerbotAIConfig.aggroDistance);
}

void FleeManager::calculateDistanceToDestination(FleePoint *point)
{
    RangePair &distance = point->toDestination;

	float d = bot->GetDistance(point->x, point->y, point->z);
    distance.probe(d);
}

void FleeManager::calculatePossibleDestinations(list<FleePoint*> &points)
{
	float botPosX = bot->GetPositionX();
	float botPosY = bot->GetPositionY();
	float botPosZ = bot->GetPositionZ();
	float oldPosX;
	float oldPosY;

	float maxDistance;
	float minDistance;
	float distanceStep;

	bool frontonly = 0;
	bool backonly = 0;

	uint32 mapId = bot->GetMapId();
	bool movePoint = false;

	if (bot)
		movePoint = bot->GetPlayerbotAI()->GetMovePoint(mapId, oldPosX, oldPosY, oldPosX);

    uint8 spec = AiFactory::GetPlayerSpecTab(bot);

    switch (bot->getClass()) {
			case CLASS_HUNTER:
			case CLASS_MAGE:
			case CLASS_PRIEST:
			case CLASS_WARLOCK:
				maxDistance = maxAllowedDistance;
				minDistance = sPlayerbotAIConfig.tooCloseDistance + 4.0f;

				if (maxDistance < minDistance  + 5.0f)
                    maxDistance = minDistance  + 5.0f;

				distanceStep = 1.0f;
				break;
			case CLASS_ROGUE:
			case CLASS_WARRIOR:
				maxDistance = sPlayerbotAIConfig.meleeDistance + 5.0f;
				minDistance = sPlayerbotAIConfig.tooCloseDistance + 1.0f;
				distanceStep = 1.0f;

                if (bot->GetPlayerbotAI()->IsTank(bot))
                    frontonly = 1;
                else backonly = 1;

				break;
            case CLASS_SHAMAN:
                if (spec == 1)
                {
                    maxDistance = sPlayerbotAIConfig.meleeDistance + 5.0f;
                    minDistance = sPlayerbotAIConfig.tooCloseDistance + 1.0f;
                    distanceStep = 1.0f;
                    backonly = 1;
                }
                else
                {
                    maxDistance = sPlayerbotAIConfig.meleeDistance + 10.0f;
                    minDistance = sPlayerbotAIConfig.tooCloseDistance + 4.0f;
                    distanceStep = 1.0f;

                    if (maxDistance < minDistance  + 5.0f)
                        maxDistance = minDistance  + 5.0f;

                    distanceStep = 1.0f;
                }
                break;
			case CLASS_DRUID:
			    if (spec == 1)
                {
                    maxDistance = sPlayerbotAIConfig.meleeDistance + 5.0f;
                    minDistance = sPlayerbotAIConfig.tooCloseDistance + 1.0f;
                    distanceStep = 1.0f;

                    if (bot->GetPlayerbotAI()->IsTank(bot))
                        frontonly = 1;
                    else backonly = 1;
                }
                else
                {
                    maxDistance = maxAllowedDistance;
                    minDistance = sPlayerbotAIConfig.tooCloseDistance + 5.0f;

                    if (maxDistance < minDistance  + 5.0f)
                        maxDistance = minDistance  + 5.0f;

                    distanceStep = 1.0f;
                }
                break;
            case CLASS_PALADIN:
				if (spec == 0 && bot->getLevel() > 55)
                {
                    maxDistance = maxAllowedDistance;
                    minDistance = sPlayerbotAIConfig.tooCloseDistance + 5.0f;

                    if (maxDistance < minDistance  + 5.0f)
                        maxDistance = minDistance  + 5.0f;

                    distanceStep = 1.0f;
                }
                else
                {
                    maxDistance = sPlayerbotAIConfig.meleeDistance + 5.0f;
                    minDistance = sPlayerbotAIConfig.tooCloseDistance + 1.0f;
                    distanceStep = 1.0f;

                    if (bot->GetPlayerbotAI()->IsTank(bot))
                        frontonly = 1;
                    else backonly = 1;
                }
                break;
    }

	for (float distance = maxDistance; distance >= minDistance; distance -= distanceStep)
	{
		for (float angle = followAngle; angle < followAngle + 2 * M_PI; angle += M_PI / 8)
        {

            float x = botPosX + cos(angle) * distance;
            float y = botPosY + sin(angle) * distance;
            float z = botPosZ;

			bot->UpdateGroundPositionZ(x, y, z);
            //bot->UpdateAllowedPositionZ(x, y, z);
            //need to investigate
            if (abs(z - botPosZ) > 10.0f)
                continue;

            if (!bot->IsWithinLOS(x, y, z))
                continue;

			if (master && !master->IsWithinLOS(x, y, z))
				continue;

			Map* map = bot->GetMap();
			const TerrainInfo* terrain = map->GetTerrain();
			if (terrain && terrain->IsInWater(x, y, z))
				continue;

            if (master && master->GetDistance(x, y, z) > sPlayerbotAIConfig.sightDistance)
                continue;

            if (master && master->GetDistance(x,y,z) < bot->GetMinMasterDistance())
                continue;

            if (target && target->GetDistance(x,y,z) < bot->GetMinTargetDistance())
                continue;

          //  if (backonly && bot->isInFront(target, M_PI / 3.0f))
          //      continue;

           // if (frontonly && !bot->isInFront(target, M_PI / 3.0f))
           //     continue;
		//	if (movePoint && abs(bot->GetDistance(x, y, z) - bot->GetDistance(oldPosX, oldPosY, oldPosX)) < 1.0f)
		//		continue;

            FleePoint *point = new FleePoint(x, y, z);
            calculateDistanceToPlayers(point);
            calculateDistanceToDestination(point);

			if (point->isReasonable())
                points.push_back(point);
			else
				delete point;
        }
	}
}

void FleeManager::cleanup(list<FleePoint*> &points)
{
	for (list<FleePoint*>::iterator i = points.begin(); i != points.end(); i++)
    {
		FleePoint* point = *i;
		delete point;
	}
	points.clear();
}

bool FleePoint::isReasonable()
{
	return toCreatures.min >= 0 && toCreatures.max >= 0 &&
		toAllPlayers.min >= 0 && toAllPlayers.max >= 0 &&
		toAllPlayers.min <= sPlayerbotAIConfig.spellDistance &&
		toAllPlayers.max <= sPlayerbotAIConfig.sightDistance &&
		toCreatures.min >= sPlayerbotAIConfig.aggroDistance &&
		toCreatures.max >= sPlayerbotAIConfig.shootDistance;
}
	
FleePoint* FleeManager::selectOptimalDestination(list<FleePoint*> &points)
{
	FleePoint* best = NULL;
	for (list<FleePoint*>::iterator i = points.begin(); i != points.end(); i++)
	{
		FleePoint* point = *i;
		if (!best || (point->toCreatures.min - best->toCreatures.min) >= 0.5f)
		{
			best = point;
		}
		else if ((point->toCreatures.min - best->toCreatures.min) >= 0)
		{
			if (point->toRangedPlayers.max >= 0 && best->toRangedPlayers.max >= 0 &&
				(point->toRangedPlayers.max - best->toRangedPlayers.max) <= 0.5f)
			{
				best = point;
			}
			else if (point->toMeleePlayers.max >= 0 && best->toMeleePlayers.max >= 0 &&
				(point->toMeleePlayers.min - best->toMeleePlayers.min) >= 0.5f)
			{
				best = point;
			}
		}
	}

	return best;
}

bool FleeManager::CalculateDestination(float* rx, float* ry, float* rz)
{
	list<FleePoint*> points;
	calculatePossibleDestinations(points);

	FleePoint* point = selectOptimalDestination(points);
	if (!point)
	{
		cleanup(points);
		return false;
	}

	*rx = point->x;
	*ry = point->y;
	*rz = point->z;

	cleanup(points);
	return true;
}
