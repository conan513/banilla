#ifndef _PLAYERBOTMGR_H
#define _PLAYERBOTMGR_H

#include "Common.h"
#include "PlayerbotAIBase.h"
#include "../botpch.h"

#include "Policies/Singleton.h"
#include "Database/DatabaseEnv.h"

#include <vector>

class WorldPacket;
class Player;
class Unit;
class Object;
class Item;

typedef map<uint64, Player*> PlayerBotMap;

class PlayerbotHolder : public PlayerbotAIBase
{
public:
    PlayerbotHolder();
    virtual ~PlayerbotHolder();

	void AddPlayerBot(uint64 guid, uint32 masterAccountId);
	void HandlePlayerBotLoginCallback(QueryResult * dummy, SqlQueryHolder * holder);

	void LogoutPlayerBot(uint64 guid);
	Player* GetPlayerBot(uint64 guid) const;

    PlayerBotMap::const_iterator GetPlayerBotsBegin() const { return playerBots.begin(); }
    PlayerBotMap::const_iterator GetPlayerBotsEnd()   const { return playerBots.end();   }

    virtual void UpdateAIInternal(uint32 elapsed);
    void UpdateSessions(uint32 elapsed);

    void LogoutAllBots();
    void OnBotLogin(Player * const bot);

    list<string> HandlePlayerbotCommand(char const* args, Player* master = NULL);
    string ProcessBotCommand(string cmd, ObjectGuid guid, bool admin, uint32 masterAccountId, uint32 masterGuildId);
    uint32 GetAccountId(string name);
	string ListBots(Player* master);

protected:
    virtual void OnBotLoginInternal(Player * const bot) = 0;

protected:
    PlayerBotMap playerBots;
};

class PlayerbotMgr : public PlayerbotHolder
{
public:
    PlayerbotMgr(Player* const master);
    virtual ~PlayerbotMgr();

    static bool HandlePlayerbotMgrCommand(ChatHandler* handler, char const* args);
    void HandleMasterIncomingPacket(const WorldPacket& packet);
    void HandleMasterOutgoingPacket(const WorldPacket& packet);
    void HandleCommand(uint32 type, const string& text);
	void OnPlayerLogin(Player* player);

    virtual void UpdateAIInternal(uint32 elapsed);

    Player* GetMaster() const { return master; };

    void SaveToDB();

protected:
    virtual void OnBotLoginInternal(Player * const bot);

private:
    Player* const master;
};

class EventBotAI;
class WorldSession;

enum PlayerBotState
{
    PB_STATE_OFFLINE,
    PB_STATE_LOADING,
    PB_STATE_ONLINE
};

struct EventBotEntry
{
    uint64 playerGUID;
    std::string name;
    uint32 accountId;

    uint32 chance;
    uint8 state; //Online, in queue or offline
    bool isChatBot; // bot des joueurs en discussion via le site.
    bool customBot; // Enabled even if PlayerBot system disabled (AutoTesting system for example)
    EventBotAI* ai;

    EventBotEntry(uint64 guid, uint32 account, uint32 _chance): playerGUID(guid), accountId(account), chance(_chance), state(PB_STATE_OFFLINE), isChatBot(false), ai(NULL), customBot(false)
    {}
    EventBotEntry(): state(PB_STATE_OFFLINE), isChatBot(false), ai(NULL), accountId(0), playerGUID(0), chance(100.0f), customBot(false)
    {}
};

struct EventBotStats
{
    /* Stats */
    uint32 onlineCount;
    uint32 loadingCount;
    uint32 totalBots;
    uint32 onlineChat;

    /* Config */
    uint32 confMaxOnline;
    uint32 confMinOnline;
    uint32 confBotsRefresh;
    uint32 confUpdateDiff;

	EventBotStats()
    : onlineCount(0), loadingCount(0), totalBots(0), onlineChat(0),
    confMaxOnline(0), confMinOnline(0), confBotsRefresh(0), confUpdateDiff(0) {}
};


class EventBotMgr
{
    public:
        EventBotMgr();
        ~EventBotMgr();

        void LoadConfig();
        void load();

        void update(uint32 diff);
        bool addOrRemoveBot();

        bool addBot(EventBotAI* ai);
        bool addBot(uint32 playerGuid, bool chatBot=false);
        bool deleteBot(uint32 playerGuid);

        bool addRandomBot();
        bool deleteRandomBot();

        void deleteAll();
        void addAllBots();

        void OnBotLogout(EventBotEntry *e);
        void OnBotLogin(EventBotEntry *e);
        void OnPlayerInWorld(Player* pPlayer);
        void AddTempBot(uint32 account, uint32 time);
        void RefreshTempBot(uint32 account);

        bool ForceAccountConnection(WorldSession* sess);
        bool IsPermanentBot(uint32 playerGuid);
        bool IsChatBot(uint32 playerGuid);
        bool ForceLogoutDelay() const { return forceLogoutDelay; }

        uint32 GenBotAccountId() { return ++_maxAccountId; }
		EventBotStats& GetStats(){ return m_stats; }
        void Start() { enable = true; }
    protected:
        /* Combien de temps depuis la derniere MaJ ?*/
        uint32 m_elapsedTime;
        uint32 m_lastBotsRefresh;
        uint32 m_lastUpdate;
        uint32 totalChance;
        uint32 _maxAccountId;

        std::map<uint32 /*pl guid*/, EventBotEntry*> m_bots;
        std::map<uint32 /*account*/, uint32> m_tempBots;
		EventBotStats m_stats;

        uint32 confMinBots;
        uint32 confMaxBots;
        uint32 confBotsRefresh;
        uint32 confUpdateDiff;
        bool confDebug;
        bool forceLogoutDelay;

        bool enable;
};

#define sEventBotMgr MaNGOS::Singleton<EventBotMgr>::Instance()
#endif
