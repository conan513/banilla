#pragma once

#include "FleeManager.h"

using namespace std;

class Player;

namespace ai
{
	class DisperseManager
	{
	public:
		DisperseManager(Player* bot, float maxAllowedDistance, float followAngle, Unit* target = NULL, bool allPlayers = false) {
			this->bot = bot;
			this->master = bot->GetPlayerbotAI()->GetMaster();
			this->maxAllowedDistance = maxAllowedDistance;
			this->followAngle = followAngle;
			this->allPlayers = allPlayers;
		}

	public:
		bool CalculateDestination(float* rx, float* ry, float* rz);

	private:
		void calculatePossibleDestinations(list<FleePoint*> &points);
		bool calculateDistanceToPlayers(FleePoint *point);
		bool calculateDistanceToCreatures(FleePoint *point);
		void calculateDistanceToDestination(FleePoint *point);
		void cleanup(list<FleePoint*> &points);
		FleePoint* selectOptimalDestination(list<FleePoint*> &points);
		bool isReasonable(FleePoint* point);
		bool isBetterThan(FleePoint* point, FleePoint* other);

	private:
		Player* bot;
		Player* master;
		float maxAllowedDistance;
		float followAngle;
		bool allPlayers;
	};

};
