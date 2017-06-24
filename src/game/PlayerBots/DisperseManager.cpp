#include "../pchdef.h"
#include "playerbot.h"
#include "DisperseManager.h"
#include "PlayerbotAIConfig.h"
#include "AiFactory.h"
#include "../Groups/Group.h"

using namespace ai;
using namespace std;

bool DisperseManager::calculateDistanceToPlayers(FleePoint *point)
{

    float minDistance = sPlayerbotAIConfig.sightDistance;

	Group* group = bot->GetGroup();
	float d;

	if (!group)
		return true;

	for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next())
    {
		Player* player = gref->GetSource();

		if(player == bot)
			continue;

        if (allPlayers)
        {
            d = player->GetDistance(point->x, point->y, point->z);
            point->toAllPlayers.probe(d);

            if (minDistance > d)
                minDistance = d;
            }
        else
        {
			uint8 spec = AiFactory::GetPlayerSpecTab(bot);

            d = player->GetDistance(point->x, point->y, point->z);
            point->toAllPlayers.probe(d);

            switch (player->getClass()) {
                case CLASS_HUNTER:
                case CLASS_MAGE:
                case CLASS_PRIEST:
                case CLASS_WARLOCK:
                     if (minDistance > d)
                        minDistance = d;
                    break;
                case CLASS_SHAMAN:
                if (spec != 1)
                     if (minDistance > d)
                        minDistance = d;
                break;
                case CLASS_DRUID:
                if (spec != 1)
                     if (minDistance > d)
                        minDistance = d;
                break;
                case CLASS_PALADIN:
			    if (spec == 0 && bot->getLevel() > 55)
                     if (minDistance > d)
                        minDistance = d;
                break;
                case CLASS_ROGUE:
                case CLASS_WARRIOR:
                case CLASS_DEATH_KNIGHT:
				 if (minDistance > d)
                    minDistance = d;
				break;
            }
        }
	}

        return (d >= sPlayerbotAIConfig.disperseDistance);
}

bool DisperseManager::calculateDistanceToCreatures(FleePoint *point)
{
	RangePair &distance = point->toCreatures;
    float d = 0;

	list<ObjectGuid> units = *bot->GetPlayerbotAI()->GetAiObjectContext()->GetValue<list<ObjectGuid> >("possible targets");

	if (units.empty())
        return true;

	for (list<ObjectGuid>::iterator i = units.begin(); i != units.end(); ++i)
    {
		Unit* unit = bot->GetPlayerbotAI()->GetUnit(*i);
		if (!unit)
		    continue;

		d = unit->GetDistance(point->x, point->y, point->z);
		if (d <= sPlayerbotAIConfig.aggroDistance)
		    continue;

		distance.probe(d);
	}

	return (d > sPlayerbotAIConfig.aggroDistance);
}

void DisperseManager::calculateDistanceToDestination(FleePoint *point)
{
    RangePair &distance = point->toDestination;

	float d = bot->GetDistance(point->x, point->y, point->z);
    distance.probe(d);
}

void DisperseManager::calculatePossibleDestinations(list<FleePoint*> &points)
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

    if (allPlayers)
    {
        minDistance = sPlayerbotAIConfig.disperseDistance;
    }
    else
    {
        switch (bot->getClass()) {
			case CLASS_HUNTER:
			case CLASS_MAGE:
			case CLASS_PRIEST:
			case CLASS_WARLOCK:
				maxDistance = maxAllowedDistance;
				minDistance = sPlayerbotAIConfig.disperseDistance;

				if (maxDistance < minDistance  + 5.0f)
                    maxDistance = minDistance  + 5.0f;

				distanceStep = 5.0f;
				break;
			case CLASS_ROGUE:
			case CLASS_WARRIOR:
            case CLASS_DEATH_KNIGHT:
				maxDistance = sPlayerbotAIConfig.meleeDistance;
				minDistance = sPlayerbotAIConfig.contactDistance;
				distanceStep = 2.0f;

                if (bot->GetPlayerbotAI()->IsTank(bot))
                    frontonly = 1;
                else backonly = 1;

				break;
            case CLASS_SHAMAN:
                if (spec == 1)
                {
                    maxDistance = sPlayerbotAIConfig.meleeDistance;
                    minDistance = sPlayerbotAIConfig.contactDistance;
                    distanceStep = 2.0f;
                    backonly = 1;
                }
                else
                {
                    maxDistance = maxAllowedDistance;
                    minDistance = sPlayerbotAIConfig.disperseDistance;

                    if (maxDistance < minDistance  + 5.0f)
                        maxDistance = minDistance  + 5.0f;

                    distanceStep = 5.0f;
                }
                break;
			case CLASS_DRUID:
			    if (spec == 1)
                {
                    maxDistance = sPlayerbotAIConfig.meleeDistance;
                    minDistance = sPlayerbotAIConfig.contactDistance;
                    distanceStep = 2.0f;
                    if (bot->GetPlayerbotAI()->IsTank(bot))
                        frontonly = 1;
                    else backonly = 1;
                }
                else
                {
                    maxDistance = maxAllowedDistance;
                    minDistance = sPlayerbotAIConfig.disperseDistance;

                    if (maxDistance < minDistance  + 5.0f)
                        maxDistance = minDistance  + 5.0f;

                    distanceStep = 5.0f;
                }
                break;
            case CLASS_PALADIN:
				if (spec == 0 && bot->getLevel() > 55)
                {
                    maxDistance = maxAllowedDistance;
                    minDistance = sPlayerbotAIConfig.disperseDistance;

                    if (maxDistance < minDistance  + 5.0f)
                        maxDistance = minDistance  + 5.0f;

                    distanceStep = 5.0f;
                }
                else
                {
                    maxDistance = sPlayerbotAIConfig.meleeDistance;
                    minDistance = sPlayerbotAIConfig.contactDistance;
                    distanceStep = 2.0f;

                    if (bot->GetPlayerbotAI()->IsTank(bot))
                        frontonly = 1;
                    else backonly = 1;
                }
                break;
        }
    }

	for (float distance = maxDistance; distance >= minDistance; distance -= distanceStep)
	{
        for (float angle = -M_PI + followAngle; angle < M_PI + followAngle; angle += M_PI / 16)
        {

            float x = botPosX + cos(angle) * distance;
            float y = botPosY + sin(angle) * distance;
            float z = botPosZ;

            bot->UpdateAllowedPositionZ(x, y, z);
            //need to investigate
            if (abs(z - botPosZ) > 10.0f)
                continue;

            if (!bot->IsWithinLOS(x, y, z))
                continue;

			if (master && !master->IsWithinLOS(x, y, z))
				continue;

            if (master && master->GetDistance(x, y, z) > sPlayerbotAIConfig.sightDistance)
                continue;

            if (master && master->GetDistance(x,y,z) < bot->GetMinMasterDistance())
                continue;

         //   if (master && master->GetDistance(x, y, z) > sPlayerbotAIConfig.sightDistance)
         //       continue;

          //  if (backonly && bot->isInFront(target, M_PI / 3.0f))
          //      continue;

           // if (frontonly && !bot->isInFront(target, M_PI / 3.0f))
           //     continue;
		//	if (movePoint && abs(bot->GetDistance(x, y, z) - bot->GetDistance(oldPosX, oldPosY, oldPosX)) < 1.0f)
		//		continue;

            FleePoint *point = new FleePoint(x, y, z);
            if (calculateDistanceToPlayers(point) && calculateDistanceToCreatures(point));
                points.push_back(point);
        }
	}
}

void DisperseManager::cleanup(list<FleePoint*> &points)
{
	for (list<FleePoint*>::iterator i = points.begin(); i != points.end(); i++)
    {
		FleePoint* point = *i;
		delete point;
	}
	points.clear();
}

FleePoint* DisperseManager::selectOptimalDestination(list<FleePoint*> &points)
{
	FleePoint* byCreatures = NULL;
	for (list<FleePoint*>::iterator i = points.begin(); i != points.end(); i++)
    {
		FleePoint* point = *i;
		if (point->isReasonable() && (!byCreatures || point->isBetterByCreatures(byCreatures)))
			byCreatures = point;
	}

	FleePoint* byAll = NULL;
	for (list<FleePoint*>::iterator i = points.begin(); i != points.end(); i++)
    {
		FleePoint* point = *i;
		if (point->isReasonable() && (!byAll || point->isBetterByAll(byAll)))
		    byAll = point;
	}

	FleePoint* byDistance = NULL;

	for (list<FleePoint*>::iterator i = points.begin(); i != points.end(); i++)
    {
		FleePoint* point = *i;
		if (point->isReasonable() && (!byDistance || point->isBetterByDistance(byDistance)))
		    byDistance = point;
	}

	if (byAll && byCreatures)
	{
	    if (byAll->isBetterByDistance(byCreatures))
	        return byAll;
        else return byCreatures;
	}
    else
        return byDistance;
}

bool DisperseManager::CalculateDestination(float* rx, float* ry, float* rz)
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
	*rz = bot->GetPositionZ();

    cleanup(points);
	return true;
}
