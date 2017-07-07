#ifndef _RandomPlayerbotMgr_H
#define _RandomPlayerbotMgr_H

#include "Common.h"
#include "PlayerbotAIBase.h"
#include "PlayerbotMgr.h"

#define MAX_NUMBER_OF_AREAS      32

typedef std::vector<uint32> Vector;

class WorldPacket;
class Player;
class Unit;
class Object;
class Item;

using namespace std;

class RandomPlayerbotMgr : public PlayerbotHolder
{
    public:
        RandomPlayerbotMgr();
        virtual ~RandomPlayerbotMgr();
        static RandomPlayerbotMgr& instance()
        {
            static RandomPlayerbotMgr instance;
            return instance;
        }

        virtual void UpdateAIInternal(uint32 elapsed);

	public:
        static bool HandlePlayerbotConsoleCommand(ChatHandler* handler, char const* args);
        bool IsRandomBot(Player* bot);
        bool IsRandomBot(uint32 bot);
        void Randomize(Player* bot);
        void RandomizeFirst(Player* bot);
        void IncreaseLevel(Player* bot);
		void ScheduleTeleport(uint32 bot, uint32 time = 0);
        void HandleCommand(uint32 type, const string& text, Player& fromPlayer);
        string HandleRemoteCommand(string request);
        void OnPlayerLogout(Player* player);
        void OnPlayerLogin(Player* player);
        Player* GetRandomPlayer();
        void PrintStats();
        double GetBuyMultiplier(Player* bot);
        double GetSellMultiplier(Player* bot);
        uint32 GetLootAmount(Player* bot);
        void SetLootAmount(Player* bot, uint32 value);
        uint32 GetTradeDiscount(Player* bot);
        void Refresh(Player* bot);
        void RandomTeleportForLevel(Player* bot);
		int GetMaxAllowedBotCount();
		bool ProcessBot(Player* player);
		void Revive(Player* player);

	protected:
	    virtual void OnBotLoginInternal(Player * const bot) {}

    private:
        uint32 GetEventValue(uint32 bot, string event);
        uint32 SetEventValue(uint32 bot, string event, uint32 value, uint32 validIn);
        list<uint32> GetBots();
		uint32 AddRandomBots();
        bool ProcessBot(uint32 bot);
        void ScheduleRandomize(uint32 bot, uint32 time);
		void RandomTeleport(Player* bot);
        void RandomTeleport(Player* bot, vector<WorldLocation> &locs);
        uint32 GetZoneLevel(uint16 mapId, float teleX, float teleY, float teleZ);
		uint32 GetMasterLevel();
		void PrepareTeleportCache();
	private:
		int masterLevel = 0;
		map<int, int> mapIdToLevel;
       Vector horde_areas = Vector{14, 55, 85,153,154,155,156,157,158,159,160,161,162,163,164,165,166,167,168,169,170,173, 187, 215,219,220,221,222,223,224,225,226,227,228,231,232,233,236,237,238,239,240,272,276,296,362,363,364,365,366,367,368,369,370,371,372,373,374,375,377,378,379,380,396,397,398,407,460,470,471,472,473,474,475,476,637,638,639,696,697,698,699,700,701,702,810,811,812,813,814,815,816,817,818,819,820,821,1099,1497,1637,1617,1638,1639,1640,1641,2118,2119,2197,2237,3460,3461,3462,3463,3464,3465,3466,3467,3468,3469,3470,3471,3472,3473,3474,3475,3476,3479,3480,3481,3482,3483,3484,3485,3486,3487,3488,3489,3531,3532,3533,3434,3436,3489};
       Vector alliance_areas = Vector{2,9,12,20,23,24,34,38,40,55, 57,59,60,62,63,64,68,69,77,80,86,87,88,99,107,108,109,111,113,115,120,131,132,133,134,135,136,137,138,140,142,144,150,186,188,189,192,271,276,296,298,299,320,415,442,608,800,801,802,803,804,805,806,807,808,809,1657,1658,1659,1660,1661,1662,2101,2102,2103,2104,2257,3524,3525,3526,3527,3528,3529,3530,3531,3532,3524,3538,3557,3558,3559,3560,3564,3567,3568,3569,3570,3571,3572,3573,3574,3575,3576,3577,3578,3579};
       vector<uint32> active_areas;

        vector<Player*> players;

        int processTicks;
        map<uint8, vector<WorldLocation> > locsPerLevelCache;
};

#define sRandomPlayerbotMgr RandomPlayerbotMgr::instance()

#endif
