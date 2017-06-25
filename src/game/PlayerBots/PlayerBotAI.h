#pragma once

#include "../botpch.h"
#include "PlayerbotMgr.h"
#include "PlayerbotAIBase.h"
#include "strategy/AiObjectContext.h"
#include "strategy/Engine.h"
#include "strategy/ExternalEventHelper.h"
#include "ChatFilter.h"
#include "PlayerbotSecurity.h"
#include <stack>

#include "PlayerAI.h"
#include "WorldSession.h"

class Player;
class PlayerbotMgr;
class ChatHandler;

using namespace std;
using namespace ai;

bool IsAlliance(uint8 race);

class PlayerbotChatHandler: protected ChatHandler
{
public:
    explicit PlayerbotChatHandler(Player* pMasterPlayer) : ChatHandler(pMasterPlayer->GetSession()) {}
    void sysmessage(string str) { SendSysMessage(str.c_str()); }
    uint32 extractQuestId(string str);
    uint32 extractSpellId(string str)
    {
        char* source = (char*)str.c_str();
        return ExtractSpellIdFromLink(&source);
    }
};

namespace ai
{
	class MinValueCalculator {
	public:
		MinValueCalculator(float def = 0.0f) {
			param = NULL;
			minValue = def;
		}

	public:
		void probe(float value, void* p) {
			if (!param || minValue >= value) {
				minValue = value;
				param = p;
			}
		}

	public:
		void* param;
		float minValue;
	};
};

enum BotState
{
    BOT_STATE_COMBAT = 0,
    BOT_STATE_NON_COMBAT = 1,
    BOT_STATE_DEAD = 2
};

#define BOT_STATE_MAX 3

enum BotAuraType
{
    BOT_AURA_NORMAL = 0,
    BOT_AURA_DAMAGE = 1,
    BOT_AURA_HEAL = 2
};

#define BOT_AURA_TYPE_MAX 3

class PacketHandlingHelper
{
public:
    void AddHandler(uint16 opcode, string handler);
    void Handle(ExternalEventHelper &helper);
    void AddPacket(const WorldPacket& packet);

private:
    map<uint16, string> handlers;
    stack<WorldPacket> queue;
};

class ChatCommandHolder
{
public:
    ChatCommandHolder(string command, Player* owner = NULL, uint32 type = CHAT_MSG_WHISPER) : command(command), owner(owner), type(type) {}
    ChatCommandHolder(ChatCommandHolder const& other)
    {
        this->command = other.command;
        this->owner = other.owner;
        this->type = other.type;
    }

public:
    string GetCommand() { return command; }
    Player* GetOwner() { return owner; }
    uint32 GetType() { return type; }

private:
    string command;
    Player* owner;
    uint32 type;
};

class PlayerbotAI : public PlayerbotAIBase
{
public:
	PlayerbotAI();
	PlayerbotAI(Player* bot);
	virtual ~PlayerbotAI();

public:
	virtual void UpdateAI(uint32 elapsed);
	virtual void UpdateAIInternal(uint32 elapsed);
	string HandleRemoteCommand(string command);
    void HandleCommand(uint32 type, const string& text, Player& fromPlayer);
	void HandleBotOutgoingPacket(const WorldPacket& packet);
    void HandleMasterIncomingPacket(const WorldPacket& packet);
    void HandleMasterOutgoingPacket(const WorldPacket& packet);
	void HandleTeleportAck();
    void ChangeEngine(BotState type);
	void DoNextAction(int depth = 0, bool instantonly = false, bool noflee = false);
    void DoSpecificAction(string name);
    bool DoMovingAction(Player* player, Unit* target);
    void ChangeStrategy(string name, BotState type);
	void ClearStrategies(BotState type);
	list<string> GetStrategies(BotState type);
    bool ContainsStrategy(StrategyType type);
    bool HasStrategy(string name, BotState type);
    void ResetStrategies();
    void ReInitCurrentEngine();
    void Reset();
    bool IsTank(Player* player);
    bool IsHeal(Player* player);
    bool IsSpellcaster(Player* player);
    bool IsRanged(Player* player);
    bool CanHeal(Player* player);
    Creature* GetCreature(ObjectGuid guid);
    Unit* GetUnit(ObjectGuid guid);
    GameObject* GetGameObject(ObjectGuid guid);
    bool TellMaster(ostringstream &stream, PlayerbotSecurityLevel securityLevel = PLAYERBOT_SECURITY_ALLOW_ALL) { return TellMaster(stream.str(), securityLevel); }
    bool TellMaster(string text, PlayerbotSecurityLevel securityLevel = PLAYERBOT_SECURITY_ALLOW_ALL);
    bool TellMasterNoFacing(string text, PlayerbotSecurityLevel securityLevel = PLAYERBOT_SECURITY_ALLOW_ALL);
    void SpellInterrupted(uint32 spellid);
    int32 CalculateGlobalCooldown(uint32 spellid);
    void InterruptSpell();
    void RemoveAura(string name);
    void RemoveShapeshift();
    void WaitForSpellCast(Spell *spell);
    bool PlaySound(uint32 emote);

	//thesawolf - emote reactions
	void ReceiveEmote(Player* player, uint32 emote);

    virtual bool CanCastSpell(string name, Unit* target, bool interruptcasting = false);
    virtual bool CastSpell(string name, Unit* target);
    virtual bool HasAura(string spellName, Unit* player, BotAuraType auratype = BOT_AURA_NORMAL);
    virtual bool HasOwnAura(string spellName, Unit* player, BotAuraType auratype = BOT_AURA_NORMAL);
    virtual bool HasAnyAuraOf(Unit* player, ...);

    virtual bool IsInterruptableSpellCasting(Unit* player, string spell);
    virtual bool HasAuraToDispel(Unit* player, uint32 dispelType);
    bool CanCastSpell(uint32 spellid, Unit* target, bool checkHasSpell = true, bool interruptcasting = false);

    bool HasAura(uint32 spellId, const Unit* player, BotAuraType auratype = BOT_AURA_NORMAL);
    bool HasOwnAura(uint32 spellId, const Unit* player, BotAuraType auratype = BOT_AURA_NORMAL);
    bool CastSpell(uint32 spellId, Unit* target);
    bool canDispel(const SpellEntry* entry, uint32 dispelType);

    uint32 GetEquipGearScore(Player* player, bool withBags, bool withBank);

private:
    void _fillGearScoreData(Player *player, Item* item, std::vector<uint32>* gearScore, uint32& twoHandScore);

public:
	Player* GetBot() { return bot; }
    Player* GetMaster() { return master; }
    void SetMaster(Player* master) { this->master = master; }
    AiObjectContext* GetAiObjectContext() { return aiObjectContext; }
    ChatHelper* GetChatHelper() { return &chatHelper; }
    bool IsOpposing(Player* player);
    static bool IsOpposing(uint8 race1, uint8 race2);
    PlayerbotSecurity* GetSecurity() { return &security; }
	map<string, time_t> whispers;

    void SetMovePoint (uint32 mapId, float x, float y, float z) {go_point= true; go_mapId = mapId; go_x = x; go_y = y;go_z = z;}
	void ResetMovePoint() {go_point = false;}
	bool IsMoving() { return go_point; }
	bool GetMovePoint( uint32 mapId, float& x, float& y, float& z)
    {
        if (mapId != go_mapId)
            return false;

        if (go_point)
        {
            x = go_x;
            y = go_y;
            z = go_z;
            return true;
        }
        else return false;
    }

    void VisitObject(ObjectGuid Id)
    {
        if (objectVisited.size() > 9)
            objectVisited.empty();

        objectVisited.push_back(Id);
    }

    bool ObjectNotVisited(ObjectGuid Id)
    {
        vector<ObjectGuid>::iterator i = find(objectVisited.begin(), objectVisited.end(), Id);
        return (i == objectVisited.end());
    }

    void LogAction(const char* format, ...);

protected:
	Player* bot;
	Player* master;
	uint32 accountId;
    AiObjectContext* aiObjectContext;
    Engine* currentEngine;
    Engine* engines[BOT_STATE_MAX];
    BotState currentState;
    ChatHelper chatHelper;
	queue<ChatCommandHolder> chatCommands;
    PacketHandlingHelper botOutgoingPacketHandlers;
    PacketHandlingHelper masterIncomingPacketHandlers;
    PacketHandlingHelper masterOutgoingPacketHandlers;
    CompositeChatFilter chatFilter;
    PlayerbotSecurity security;
    float go_x;
    float go_y;
    float go_z;
    bool go_point;

    uint32 go_mapId;

    vector<ObjectGuid> objectVisited;

};

struct EventBotEntry;
class WorldSession;
class EventBotAI;

EventBotAI* CreateEventBotAI(std::string ainame);

class EventBotAI: public PlayerAI
{
    public:
        explicit EventBotAI(Player* pPlayer = NULL) : PlayerAI(pPlayer), botEntry(NULL) {}
        virtual ~EventBotAI() {}
        virtual void Remove();

        virtual bool OnSessionLoaded(EventBotEntry* entry, WorldSession* sess);
        virtual void OnBotEntryLoad(EventBotEntry* entry) {}
        virtual void UpdateAI(const uint32 /*diff*/); // Handle delayed teleports
        virtual void OnPlayerLogin() {}
        virtual void BeforeAddToMap(Player* player) {} // me=NULL at call
        // Helpers
        bool SpawnNewPlayer(WorldSession* sess, uint8 _class, uint32 _race, uint32 mapId, uint32 instanceId, float dx, float dy, float dz, float o);
        EventBotEntry* botEntry;
};

class PlayerCreatorAI: public EventBotAI
{
    public:
        explicit PlayerCreatorAI(Player* pPlayer, uint8 _race_, uint8 _class_, uint32 mapId, uint32 instanceId, float x, float y, float z, float o) :
            EventBotAI(pPlayer), _race(_race_), _class(_class_), _mapId(mapId), _instanceId(instanceId), _x(x), _y(y), _z(z), _o(o)
        {
        }
        virtual ~PlayerCreatorAI() {}
        virtual bool OnSessionLoaded(EventBotEntry* entry, WorldSession* sess)
        {
            return SpawnNewPlayer(sess, _class, _race, _mapId, _instanceId, _x, _y, _z, _o);
        }
    protected:
        uint8 _race;
        uint8 _class;
        uint32 _mapId;
        uint32 _instanceId;
        float _x;
        float _y;
        float _z;
        float _o;
};

class EventBotFleeingAI : public EventBotAI
{
    public:
        EventBotFleeingAI() : EventBotAI() {}
        virtual void OnPlayerLogin();
};

class MageOrgrimmarAttackerAI: public EventBotAI
{
    public:
        explicit MageOrgrimmarAttackerAI(Player* pPlayer = NULL) : EventBotAI(pPlayer) {}
        virtual ~MageOrgrimmarAttackerAI() {}
        virtual bool OnSessionLoaded(EventBotEntry* entry, WorldSession* sess);
        virtual void UpdateAI(const uint32 /*diff*/);
};

class PopulateAreaBotAI: public EventBotAI
{
    public:
        explicit PopulateAreaBotAI(uint32 map, float x, float y, float z, uint32 team, float radius, Player* pPlayer = NULL) : EventBotAI(pPlayer), _map(map), _x(x), _y(y), _z(z), _team(team), _radius(radius) {}
        virtual ~PopulateAreaBotAI() {}
        virtual void BeforeAddToMap(Player* player); // me=NULL at call
        virtual void OnPlayerLogin();
    protected:
        uint32 _map;
        float _x, _y, _z;
        float _radius;
        uint32 _team;
};
