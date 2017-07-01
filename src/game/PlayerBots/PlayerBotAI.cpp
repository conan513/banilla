#include "../pchdef.h"
#include "PlayerbotMgr.h"
#include "playerbot.h"

#include "AiFactory.h"

#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CellImpl.h"
#include "strategy/values/LastMovementValue.h"
#include "strategy/actions/LogLevelAction.h"
#include "strategy/values/LastSpellCastValue.h"
#include "LootObjectStack.h"
#include "PlayerbotAIConfig.h"
#include "PlayerbotAI.h"
#include "PlayerbotFactory.h"
#include "PlayerbotSecurity.h"
#include "Group.h"
//#include "../Spells/SpellHistory.h"
#include "Pet.h"
#include "SpellAuraDefines.h"
#include "GuildTaskMgr.h"
#include "PlayerbotDbStore.h"

#include "PlayerBotAI.h"
#include "Player.h"
#include "DBCStructure.h"
#include "Log.h"
#include "SocialMgr.h"
#include "MotionMaster.h"
#include "ObjectMgr.h"
#include "MoveSpline.h"
#include "PlayerBotMgr.h"


using namespace ai;
using namespace std;

vector<string>& split(const string &s, char delim, vector<string> &elems);
vector<string> split(const string &s, char delim);
uint64 extractGuid(WorldPacket& packet);
std::string &trim(std::string &s);

uint32 PlayerbotChatHandler::extractQuestId(string str)
{
	char* source = (char*)str.c_str();
	char* cId = ExtractKeyFromLink(&source, "Hquest");
	return cId ? atol(cId) : 0;
}

void PacketHandlingHelper::AddHandler(uint16 opcode, string handler)
{
    handlers[opcode] = handler;
}

void PacketHandlingHelper::Handle(ExternalEventHelper &helper)
{
    while (!queue.empty())
    {
        helper.HandlePacket(handlers, queue.top());
        queue.pop();
    }
}

void PacketHandlingHelper::AddPacket(const WorldPacket& packet)
{
	if (handlers.find(packet.GetOpcode()) != handlers.end())
        queue.push(WorldPacket(packet));
}


PlayerbotAI::PlayerbotAI() : PlayerbotAIBase(), bot(NULL), aiObjectContext(NULL),
    currentEngine(NULL), chatHelper(this), chatFilter(this), accountId(0), security(NULL), master(NULL)
{
    for (int i = 0 ; i < BOT_STATE_MAX; i++)
        engines[i] = NULL;
}

PlayerbotAI::PlayerbotAI(Player* bot) :
    PlayerbotAIBase(), chatHelper(this), chatFilter(this), security(bot), master(NULL)
{
	this->bot = bot;

	accountId = sObjectMgr.GetPlayerAccountIdByGUID(bot->GetGUID());

    aiObjectContext = AiFactory::createAiObjectContext(bot, this);

    engines[BOT_STATE_COMBAT] = AiFactory::createCombatEngine(bot, this, aiObjectContext);
    engines[BOT_STATE_NON_COMBAT] = AiFactory::createNonCombatEngine(bot, this, aiObjectContext);
    engines[BOT_STATE_DEAD] = AiFactory::createDeadEngine(bot, this, aiObjectContext);
    currentEngine = engines[BOT_STATE_NON_COMBAT];
    currentState = BOT_STATE_NON_COMBAT;

	masterIncomingPacketHandlers.AddHandler(CMSG_GAMEOBJ_USE, "use game object");
    masterIncomingPacketHandlers.AddHandler(CMSG_AREATRIGGER, "area trigger");
    masterIncomingPacketHandlers.AddHandler(CMSG_GAMEOBJ_USE, "use game object");
    masterIncomingPacketHandlers.AddHandler(CMSG_LOOT_ROLL, "loot roll");
    masterIncomingPacketHandlers.AddHandler(CMSG_GOSSIP_HELLO, "gossip hello");
    masterIncomingPacketHandlers.AddHandler(CMSG_QUESTGIVER_HELLO, "gossip hello");
    masterIncomingPacketHandlers.AddHandler(CMSG_QUESTGIVER_COMPLETE_QUEST, "complete quest");
    masterIncomingPacketHandlers.AddHandler(CMSG_QUESTGIVER_ACCEPT_QUEST, "accept quest");
    masterIncomingPacketHandlers.AddHandler(CMSG_ACTIVATETAXI, "activate taxi");
    masterIncomingPacketHandlers.AddHandler(CMSG_ACTIVATETAXIEXPRESS, "activate taxi");
    masterIncomingPacketHandlers.AddHandler(CMSG_MOVE_SPLINE_DONE, "taxi done");
    masterIncomingPacketHandlers.AddHandler(CMSG_GROUP_UNINVITE_GUID, "uninvite");
    masterIncomingPacketHandlers.AddHandler(CMSG_PUSHQUESTTOPARTY, "quest share");
    masterIncomingPacketHandlers.AddHandler(CMSG_GUILD_INVITE, "guild invite");

    botOutgoingPacketHandlers.AddHandler(SMSG_GROUP_INVITE, "group invite");
    botOutgoingPacketHandlers.AddHandler(BUY_ERR_NOT_ENOUGHT_MONEY, "not enough money");
    botOutgoingPacketHandlers.AddHandler(BUY_ERR_REPUTATION_REQUIRE, "not enough reputation");
    botOutgoingPacketHandlers.AddHandler(SMSG_GROUP_SET_LEADER, "group set leader");
    botOutgoingPacketHandlers.AddHandler(SMSG_FORCE_RUN_SPEED_CHANGE, "check mount state");
    botOutgoingPacketHandlers.AddHandler(SMSG_RESURRECT_REQUEST, "resurrect request");
    botOutgoingPacketHandlers.AddHandler(SMSG_INVENTORY_CHANGE_FAILURE, "cannot equip");
    botOutgoingPacketHandlers.AddHandler(SMSG_TRADE_STATUS, "trade status");
    botOutgoingPacketHandlers.AddHandler(SMSG_LOOT_RESPONSE, "loot response");
    botOutgoingPacketHandlers.AddHandler(SMSG_QUESTUPDATE_ADD_KILL, "quest objective completed");
    botOutgoingPacketHandlers.AddHandler(SMSG_ITEM_PUSH_RESULT, "item push result");
    botOutgoingPacketHandlers.AddHandler(SMSG_PARTY_COMMAND_RESULT, "party command");
    botOutgoingPacketHandlers.AddHandler(SMSG_CAST_FAILED, "cast failed");
    botOutgoingPacketHandlers.AddHandler(SMSG_DUEL_REQUESTED, "duel requested");
	botOutgoingPacketHandlers.AddHandler(SMSG_BATTLEFIELD_STATUS, "bg status");

    masterOutgoingPacketHandlers.AddHandler(SMSG_PARTY_COMMAND_RESULT, "party command");
    masterOutgoingPacketHandlers.AddHandler(MSG_RAID_READY_CHECK, "ready check");
    masterOutgoingPacketHandlers.AddHandler(MSG_RAID_READY_CHECK_FINISHED, "ready check finished");
}

PlayerbotAI::~PlayerbotAI()
{
    for (int i = 0 ; i < BOT_STATE_MAX; i++)
    {
        if (engines[i])
            delete engines[i];
    }

    if (aiObjectContext)
        delete aiObjectContext;
}

void PlayerbotAI::UpdateAI(uint32 elapsed)
{
    if (bot->IsBeingTeleported())
        return;

	//DEBUG
	/*	engines[BOT_STATE_COMBAT]->testMode = bot->InBattleGround();
	 	engines[BOT_STATE_NON_COMBAT]->testMode = bot->InBattleGround();
	 	engines[BOT_STATE_COMBAT]->testPrefix = bot->GetName();
	 	engines[BOT_STATE_NON_COMBAT]->testPrefix = bot->GetName();*/
	 
	 	//EOD

  //  if (nextAICheckDelay > sPlayerbotAIConfig.globalCoolDown &&
    if (bot->IsNonMeleeSpellCasted(true, true, false) &&
        *GetAiObjectContext()->GetValue<bool>("invalid target", "current target"))
    {
        Spell* spell = bot->GetCurrentSpell(CURRENT_GENERIC_SPELL);
        if (spell && !IsPositiveSpell(spell->m_spellInfo))
        {
            InterruptSpell();
            TellMaster("Interrupted spell for update");
        }

        Spell* channel_spell = bot->GetCurrentSpell(CURRENT_CHANNELED_SPELL);
        if (channel_spell && !IsPositiveSpell(channel_spell->m_spellInfo))
        {
            InterruptSpell();
            TellMaster("Interrupted channel spell for update");
        }
    }

    Pet* pet = bot->GetPet();
	if (pet && pet->getPetType() == HUNTER_PET && pet->GetHappinessState() != HAPPY)
    {
         pet->SetPower(POWER_HAPPINESS, HAPPINESS_LEVEL_SIZE * 2);
    }


    PlayerbotAIBase::UpdateAI(elapsed);
}

void PlayerbotAI::UpdateAIInternal(uint32 elapsed)
{
    ExternalEventHelper helper(aiObjectContext);
    while (!chatCommands.empty())
    {
        ChatCommandHolder holder = chatCommands.front();
        string command = holder.GetCommand();
        Player* owner = holder.GetOwner();
        if (!helper.ParseChatCommand(command, owner) && holder.GetType() == CHAT_MSG_WHISPER)
        {
            ostringstream out; out << "Unknown command " << command;
            TellMaster(out);
            helper.ParseChatCommand("help");
        }
        chatCommands.pop();
    }

    botOutgoingPacketHandlers.Handle(helper);
    masterIncomingPacketHandlers.Handle(helper);
    masterOutgoingPacketHandlers.Handle(helper);

	DoNextAction();
}

void PlayerbotAI::HandleTeleportAck()
{
	bot->GetMotionMaster()->Clear(true);
	if (bot->IsBeingTeleportedNear())
	{
		WorldPacket p = WorldPacket(MSG_MOVE_TELEPORT_ACK, 8 + 4 + 4);
		p.appendPackGUID(bot->GetGUID());
		p << (uint32)0; // supposed to be flags? not used currently
		p << (uint32)time(0); // time - not currently used
		bot->GetSession()->HandleMoveTeleportAckOpcode(p);
	}
	else if (bot->IsBeingTeleportedFar())
	{
	    WorldPacket p;
		bot->GetSession()->HandleMoveWorldportAckOpcode(p);
		SetNextCheckDelay(sPlayerbotAIConfig.globalCoolDown);
	}
}

void PlayerbotAI::Reset()
{
    if (bot->IsFlying())
        return;

    currentEngine = engines[BOT_STATE_NON_COMBAT];
    nextAICheckDelay = 0;

	whispers.clear();

    aiObjectContext->GetValue<Unit*>("old target")->Set(NULL);
    aiObjectContext->GetValue<Unit*>("current target")->Set(NULL);
    aiObjectContext->GetValue<LootObject>("loot target")->Set(LootObject());
    aiObjectContext->GetValue<uint32>("lfg proposal")->Set(0);

    LastSpellCast & lastSpell = aiObjectContext->GetValue<LastSpellCast& >("last spell cast")->Get();
    lastSpell.Reset();

    LastMovement & lastMovement = aiObjectContext->GetValue<LastMovement& >("last movement")->Get();
    lastMovement.Set(NULL);

    bot->GetMotionMaster()->Clear();
    bot->m_taxi.ClearTaxiDestinations();

    Spell* spell = bot->GetCurrentSpell(CURRENT_GENERIC_SPELL);
        if (spell && !IsPositiveSpell(spell->m_spellInfo))
        {
            InterruptSpell();
            TellMaster("Interrupted spell for reset");
        }

        Spell* channel_spell = bot->GetCurrentSpell(CURRENT_CHANNELED_SPELL);
        if (channel_spell && !IsPositiveSpell(channel_spell->m_spellInfo))
        {
            InterruptSpell();
            TellMaster("Interrupted channel spell for reset");
        }
    //InterruptSpell();

    for (int i = 0 ; i < BOT_STATE_MAX; i++)
    {
        engines[i]->Init();
    }
}

void PlayerbotAI::HandleCommand(uint32 type, const string& text, Player& fromPlayer)
{
    if (!GetSecurity()->CheckLevelFor(PLAYERBOT_SECURITY_INVITE, type != CHAT_MSG_WHISPER, &fromPlayer))
        return;

    if (type == CHAT_MSG_ADDON)
        return;

    string filtered = text;
    if (!sPlayerbotAIConfig.commandPrefix.empty())
    {
        if (filtered.find(sPlayerbotAIConfig.commandPrefix) != 0)
            return;

        filtered = filtered.substr(sPlayerbotAIConfig.commandPrefix.size());
    }

    filtered = chatFilter.Filter(trim((string&)filtered));
    if (filtered.empty())
        return;

    if (filtered.find("who") != 0 && !GetSecurity()->CheckLevelFor(PLAYERBOT_SECURITY_ALLOW_ALL, type != CHAT_MSG_WHISPER, &fromPlayer))
        return;

    if (type == CHAT_MSG_RAID_WARNING && filtered.find(bot->GetName()) != string::npos && filtered.find("award") == string::npos)
    {
        ChatCommandHolder cmd("warning", &fromPlayer, type);
        chatCommands.push(cmd);
        return;
    }

    if (filtered.size() > 2 && filtered.substr(0, 2) == "d " || filtered.size() > 3 && filtered.substr(0, 3) == "do ")
    {
        std::string action = filtered.substr(filtered.find(" ") + 1);
        DoSpecificAction(action);
    }
    else if (filtered == "reset")
    {
        Reset();
    }
    else
    {
        ChatCommandHolder cmd(filtered, &fromPlayer, type);
        chatCommands.push(cmd);
    }
}

void PlayerbotAI::HandleBotOutgoingPacket(const WorldPacket& packet)
{
    switch (packet.GetOpcode())
    {
    case SMSG_SPELL_FAILURE:
        {
            WorldPacket p(packet);
            p.rpos(0);
			ObjectGuid casterGuid;
			p >> casterGuid.ReadAsPacked();
            if (casterGuid != bot->GetObjectGuid())
                return;

            uint8 castCount;
            uint32 spellId;
            p >> castCount;
            p >> spellId;
            SpellInterrupted(spellId);
            return;
        }
    case SMSG_SPELL_DELAYED:
        {
            WorldPacket p(packet);
            p.rpos(0);
			ObjectGuid casterGuid;
			p >> casterGuid.ReadAsPacked();

            if (casterGuid != bot->GetObjectGuid())
                return;

            uint32 delaytime;
            p >> delaytime;
            if (delaytime <= 1000)
                IncreaseNextCheckDelay(delaytime);
            return;
        }
    default:
        botOutgoingPacketHandlers.AddPacket(packet);
    }
}

void PlayerbotAI::SpellInterrupted(uint32 spellid)
{
    LastSpellCast& lastSpell = aiObjectContext->GetValue<LastSpellCast&>("last spell cast")->Get();
	if (!spellid || lastSpell.id != spellid)
        return;

    lastSpell.Reset();

    time_t now = time(0);
    if (now <= lastSpell.time)
        return;

    uint32 castTimeSpent = 1000 * (now - lastSpell.time);

    int32 globalCooldown = CalculateGlobalCooldown(lastSpell.id);
    if (castTimeSpent < globalCooldown)
        SetNextCheckDelay(globalCooldown - castTimeSpent);
    else
		SetNextCheckDelay(sPlayerbotAIConfig.reactDelay);

    lastSpell.id = 0;
}

int32 PlayerbotAI::CalculateGlobalCooldown(uint32 spellid)
{
    if (!spellid)
        return 0;

    if (bot->HasSpellCooldown(spellid))
        return sPlayerbotAIConfig.globalCoolDown;

    return sPlayerbotAIConfig.reactDelay;
}

void PlayerbotAI::HandleMasterIncomingPacket(const WorldPacket& packet)
{
    masterIncomingPacketHandlers.AddPacket(packet);
}

void PlayerbotAI::HandleMasterOutgoingPacket(const WorldPacket& packet)
{
    masterOutgoingPacketHandlers.AddPacket(packet);
}

void PlayerbotAI::ChangeEngine(BotState type)
{
    Engine* engine = engines[type];

    if (currentEngine != engine)
    {
        currentEngine = engine;
        currentState = type;
        ReInitCurrentEngine();

        switch (type)
        {
        case BOT_STATE_COMBAT:
            sLog.outDebug( "=== %s COMBAT ===", bot->GetName());
            break;
        case BOT_STATE_NON_COMBAT:
            sLog.outDebug( "=== %s NON-COMBAT ===", bot->GetName());
            break;
        case BOT_STATE_DEAD:
            sLog.outDebug( "=== %s DEAD ===", bot->GetName());
            break;
        }
    }
}

void PlayerbotAI::DoNextAction(int depth, bool instantonly, bool noflee)
{
    if (bot->IsBeingTeleported() || (GetMaster() && GetMaster()->IsBeingTeleported()))
        return;

    currentEngine->DoNextAction(NULL,depth,instantonly,noflee);

    if (currentEngine != engines[BOT_STATE_DEAD] && !bot->isAlive())
        ChangeEngine(BOT_STATE_DEAD);

    if (currentEngine == engines[BOT_STATE_DEAD] && bot->isAlive())
        ChangeEngine(BOT_STATE_NON_COMBAT);

    Group *group = bot->GetGroup();
	if (!master && group &&!bot->InBattleGround())
		 {
			for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next())
			 {
				Player* member = gref->getSource();
				PlayerbotAI* ai = bot->GetPlayerbotAI();
				if (member && member->IsInWorld() && !member->GetPlayerbotAI() && (!master || master->GetPlayerbotAI()))
				 {
					ai->SetMaster(member);
					ai->ResetStrategies();
					ai->TellMaster("Hello");
					break;
				}
			}
		}
}

void PlayerbotAI::ReInitCurrentEngine()
{
    InterruptSpell();
    currentEngine->Init();
}

void PlayerbotAI::ChangeStrategy(string names, BotState type)
{
    Engine* e = engines[type];
    if (!e)
        return;

    e->ChangeStrategy(names);
}

void PlayerbotAI::ClearStrategies(BotState type)
{
	Engine* e = engines[type];
	if (!e)
		return;

	e->removeAllStrategies();
}

list<string> PlayerbotAI::GetStrategies(BotState type)
{
	Engine* e = engines[type];
	if (!e)
		return list<string>();

	return e->GetStrategies();
}

void PlayerbotAI::DoSpecificAction(string name)
{
    for (int i = 0 ; i < BOT_STATE_MAX; i++)
    {
        ostringstream out;
        ActionResult res = engines[i]->ExecuteAction(name);
        switch (res)
        {
        case ACTION_RESULT_UNKNOWN:
            continue;
        case ACTION_RESULT_OK:
            out << name << ": done";
            TellMaster(out);
            PlaySound(TEXTEMOTE_NOD);
            return;
        case ACTION_RESULT_IMPOSSIBLE:
            out << name << ": impossible";
            TellMaster(out);
            PlaySound(TEXTEMOTE_NO);
            return;
        case ACTION_RESULT_USELESS:
            out << name << ": useless";
            TellMaster(out);
            PlaySound(TEXTEMOTE_NO);
            return;
        case ACTION_RESULT_FAILED:
            out << name << ": failed";
            TellMaster(out);
            return;
        }
    }
    ostringstream out;
    out << name << ": unknown action";
    TellMaster(out);
}

bool PlayerbotAI::PlaySound(uint32 emote)
{
	if (EmotesTextSoundEntry const* soundEntry = FindTextSoundEmoteFor(emote, bot->getRace(), bot->getGender()))
	{
		bot->PlayDistanceSound(soundEntry->SoundId);
		return true;
	}

	return false;
}

//thesawolf - emotion responses
void PlayerbotAI::ReceiveEmote(Player* player, uint32 emote)
{
	// thesawolf - lets clear any running emotes first
	bot->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
	switch (emote)
	{
	case TEXTEMOTE_BONK:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_CRY);
		break;
	case TEXTEMOTE_SALUTE:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
		break;
	case TEXTEMOTE_BECKON:
		//SetBotCommandState(COMMAND_FOLLOW, true);
		bot->Say("Wherever you go, I'll follow..", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_WAVE:
	case TEXTEMOTE_GREET:
	case TEXTEMOTE_HAIL:
	case TEXTEMOTE_HELLO:
	case TEXTEMOTE_WELCOME:
	case TEXTEMOTE_INTRODUCE:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_WAVE);
		bot->Say("Hey there!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_DANCE:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_DANCE);
		bot->Say("Shake what your mama gave you!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_FLIRT:
	case TEXTEMOTE_KISS:
	case TEXTEMOTE_HUG:
	case TEXTEMOTE_BLUSH:
	case TEXTEMOTE_SMILE:
	case TEXTEMOTE_LOVE:
	case TEXTEMOTE_FLEX:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_APPLAUD);
		bot->Say("Hercules! Hercules!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_ANGRY:
	case TEXTEMOTE_GLARE:
	case TEXTEMOTE_BLAME:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_QUESTION);
		bot->Say("Did I do thaaaaat?", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_FART:
	case TEXTEMOTE_BURP:
	case TEXTEMOTE_GASP:
	case TEXTEMOTE_NOSEPICK:
	case TEXTEMOTE_SNIFF:
	case TEXTEMOTE_STINK:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
		bot->Say("Wasn't me! Just sayin'..", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_JOKE:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_LAUGH);
		bot->Say("Oh.. was I not supposed to laugh so soon?", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_CHICKEN:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_RUDE);
		bot->Say("We'll see who's chicken soon enough!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_APOLOGIZE:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
		bot->Say("You damn right you're sorry!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_APPLAUD:
	case TEXTEMOTE_CLAP:
	case TEXTEMOTE_CONGRATULATE:
	case TEXTEMOTE_HAPPY:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_BOW);
		bot->Say("Thank you.. Thank you.. I'm here all week.", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_BEG:
	case TEXTEMOTE_GROVEL:
	case TEXTEMOTE_PLEAD:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_NO);
		bot->Say("Beg all you want.. I have nothing for you.", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_BITE:
	case TEXTEMOTE_POKE:
	case TEXTEMOTE_SCRATCH:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
		bot->Yell("OUCH! Dammit, that hurt!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_BORED:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_NO);
		bot->Say("My job description doesn't include entertaining you..", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_BOW:
	case TEXTEMOTE_CURTSEY:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_BOW);
		break;
	case TEXTEMOTE_BRB:
	case TEXTEMOTE_SIT:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_EAT);
		bot->Say("Looks like time for an AFK break..", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_AGREE:
	case TEXTEMOTE_NOD:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
		bot->Say("At least SOMEONE agrees with me!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_AMAZE:
	case TEXTEMOTE_COWER:
	case TEXTEMOTE_CRINGE:
	case TEXTEMOTE_EYE:
	case TEXTEMOTE_KNEEL:
	case TEXTEMOTE_PEER:
	case TEXTEMOTE_SURRENDER:
	case TEXTEMOTE_PRAISE:
	case TEXTEMOTE_SCARED:
	case TEXTEMOTE_COMMEND:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_FLEX);
		bot->Say("Yes, Yes. I know I'm amazing..", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_BLEED:
	case TEXTEMOTE_MOURN:
	case TEXTEMOTE_FLOP:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_KNEEL);
		bot->Yell("MEDIC! Stat!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_BLINK:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_KICK);
		bot->Say("What? You got something in your eye?", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_BOUNCE:
	case TEXTEMOTE_BARK:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
		bot->Say("Who's a good doggy? You're a good doggy!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_BYE:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_WAVE);
		bot->Say("Umm.... wait! Where are you going?!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_CACKLE:
	case TEXTEMOTE_LAUGH:
	case TEXTEMOTE_CHUCKLE:
	case TEXTEMOTE_GIGGLE:
	case TEXTEMOTE_GUFFAW:
	case TEXTEMOTE_ROFL:
	case TEXTEMOTE_SNICKER:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_LAUGH);
		bot->Say("Wait... what are we laughing at again?", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_CONFUSED:
	case TEXTEMOTE_CURIOUS:
	case TEXTEMOTE_FIDGET:
	case TEXTEMOTE_FROWN:
	case TEXTEMOTE_SHRUG:
	case TEXTEMOTE_SIGH:
	case TEXTEMOTE_STARE:
	case TEXTEMOTE_TAP:
	case TEXTEMOTE_SURPRISED:
	case TEXTEMOTE_WHINE:
	case TEXTEMOTE_BOGGLE:
	case TEXTEMOTE_LOST:
	case TEXTEMOTE_PONDER:
	case TEXTEMOTE_SNUB:
	case TEXTEMOTE_SERIOUS:
	case TEXTEMOTE_EYEBROW:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_QUESTION);
		bot->Say("Don't look at  me.. I just work here", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_COUGH:
	case TEXTEMOTE_DROOL:
	case TEXTEMOTE_SPIT:
	case TEXTEMOTE_LICK:
	case TEXTEMOTE_BREATH:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
		bot->Say("Ewww! Keep your nasty germs over there!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_CRY:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_CRY);
		bot->Say("Don't you start crying or it'll make me start crying!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_CRACK:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
		bot->Say("It's clobbering time!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_EAT:
	case TEXTEMOTE_DRINK:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_EAT);
		bot->Say("I hope you brought enough for the whole class...", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_GLOAT:
	case TEXTEMOTE_MOCK:
	case TEXTEMOTE_TEASE:
	case TEXTEMOTE_EMBARRASS:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_CRY);
		bot->Say("Doesn't mean you need to be an ass about it..", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_HUNGRY:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_EAT);
		bot->Say("What? You want some of this?", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_LAYDOWN:
	case TEXTEMOTE_TIRED:
	case TEXTEMOTE_YAWN:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_KNEEL);
		bot->Say("Is it break time already?", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_MOAN:
	case TEXTEMOTE_MOON:
	case TEXTEMOTE_SEXY:
	case TEXTEMOTE_SHAKE:
	case TEXTEMOTE_WHISTLE:
	case TEXTEMOTE_CUDDLE:
	case TEXTEMOTE_PURR:
	case TEXTEMOTE_SHIMMY:
	case TEXTEMOTE_SMIRK:
	case TEXTEMOTE_WINK:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_NO);
		bot->Say("Keep it in your pants, boss..", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_NO:
	case TEXTEMOTE_VETO:
	case TEXTEMOTE_DISAGREE:
	case TEXTEMOTE_DOUBT:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_QUESTION);
		bot->Say("Aww.... why not?!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_PANIC:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_EXCLAMATION);
		bot->Say("Now is NOT the time to panic!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_POINT:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
		bot->Say("What?! I can do that TOO!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_RUDE:
	case TEXTEMOTE_RASP:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_RUDE);
		bot->Say("Right back at you, bub!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_ROAR:
	case TEXTEMOTE_THREATEN:
	case TEXTEMOTE_CALM:
	case TEXTEMOTE_DUCK:
	case TEXTEMOTE_TAUNT:
	case TEXTEMOTE_PITY:
	case TEXTEMOTE_GROWL:
	case TEXTEMOTE_OPENFIRE:
	case TEXTEMOTE_ENCOURAGE:
	case TEXTEMOTE_ENEMY:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_ROAR);
		bot->Yell("RAWR!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_TALK:
	case TEXTEMOTE_TALKEX:
	case TEXTEMOTE_TALKQ:
	case TEXTEMOTE_LISTEN:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
		bot->Say("Blah Blah Blah Yakety Smackety..", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_THANK:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_BOW);
		bot->Say("You are quite welcome!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_VICTORY:
	case TEXTEMOTE_CHEER:
	case TEXTEMOTE_TOAST:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);
		bot->Say("Yay!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_COLD:
	case TEXTEMOTE_SHIVER:
	case TEXTEMOTE_THIRSTY:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_QUESTION);
		bot->Say("And what exactly am I supposed to do about that?", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_COMFORT:
	case TEXTEMOTE_SOOTHE:
	case TEXTEMOTE_PAT:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_CRY);
		bot->Say("Thanks...", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_INSULT:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_CRY);
		bot->Say("You hurt my feelings..", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_JK:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
		bot->Say("You.....", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_RAISE:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
		bot->Say("Yes.. you.. at the back of the class..", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_READY:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_SALUTE);
		bot->Say("Ready here, too!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_SHOO:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_KICK);
		bot->Say("Shoo yourself!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_SLAP:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_CRY);
		bot->Say("What did I do to deserve that?", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_STAND:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_NONE);
		bot->Say("What? Break time's over? Fine..", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_TICKLE:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_LAUGH);
		bot->Say("Hey! Stop that!", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_VIOLIN:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
		bot->Say("Har Har.. very funny..", LANG_UNIVERSAL);
		break;
	case TEXTEMOTE_GOODLUCK:
	case TEXTEMOTE_BRANDISH:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_BEG);
		bot->Say("Please don't kill me!", LANG_UNIVERSAL);
		break;
	default:
		bot->HandleEmoteCommand(EMOTE_ONESHOT_QUESTION);
		bot->Say("Mmmmmkaaaaaay...", LANG_UNIVERSAL);
		break;
	}
	return;
}

bool PlayerbotAI::ContainsStrategy(StrategyType type)
{
    for (int i = 0 ; i < BOT_STATE_MAX; i++)
    {
        if (engines[i]->ContainsStrategy(type))
            return true;
    }
    return false;
}

bool PlayerbotAI::HasStrategy(string name, BotState type)
{
    return engines[type]->HasStrategy(name);
}

void PlayerbotAI::ResetStrategies()
{
    for (int i = 0 ; i < BOT_STATE_MAX; i++)
        engines[i]->removeAllStrategies();

    AiFactory::AddDefaultCombatStrategies(bot, this, engines[BOT_STATE_COMBAT]);
    AiFactory::AddDefaultNonCombatStrategies(bot, this, engines[BOT_STATE_NON_COMBAT]);
    AiFactory::AddDefaultDeadStrategies(bot, this, engines[BOT_STATE_DEAD]);

	sPlayerbotDbStore.Load(this);
}

bool PlayerbotAI::IsRanged(Player* player)
{
    PlayerbotAI* botAi = player->GetPlayerbotAI();

    if (botAi && botAi->ContainsStrategy(STRATEGY_TYPE_RANGED))
        return true;

    switch (player->getClass())
    {
    case CLASS_PALADIN:
    case CLASS_WARRIOR:
    case CLASS_ROGUE:
        return false;
    case CLASS_SHAMAN:
        return HasAnyAuraOf(player, "water shield", NULL);
    case CLASS_DRUID:
        return !HasAnyAuraOf(player, "cat form", "bear form", "dire bear form", NULL);
    }
    return true;
}

bool PlayerbotAI::CanHeal(Player* player)
{
    PlayerbotAI* botAi = player->GetPlayerbotAI();

    if (botAi && botAi->ContainsStrategy(STRATEGY_TYPE_HEAL))
        return true;

    switch (player->getClass())
    {
    case CLASS_WARRIOR:
    case CLASS_ROGUE:
    case CLASS_HUNTER:
    case CLASS_MAGE:
    case CLASS_WARLOCK:
        return false;
    }
    return true;
}

bool PlayerbotAI::IsSpellcaster(Player* player)
{
    switch (player->getClass())
    {
    case CLASS_WARRIOR:
    case CLASS_ROGUE:
        return false;
    case CLASS_DRUID:
        return HasAnyAuraOf(player, "moonkin form", "caster form", NULL);
    case CLASS_SHAMAN:
        return HasAnyAuraOf(player, "water shield", NULL);
    }
    return true;
}

bool PlayerbotAI::DoMovingAction(Player* player, Unit* target)
{
    if (!target || !player)
        return true;

    PlayerbotAI* ai = player->GetPlayerbotAI();

    if (!ai)
        return true;

    if (ai->IsHeal(player))
    {
        Group *group = player->GetGroup();
        if (!master && group)
        {
            float health = player->GetHealthPercent();

            for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next())
            {
                Player* member = gref->getSource();
                if (member && member->IsInWorld() && member->GetDistance(player) < sPlayerbotAIConfig.spellDistance)
                {
                    if (member->GetHealthPercent() < health)
                        health = member->GetHealthPercent();
                }
            }

            if (health > sPlayerbotAIConfig.almostFullHealth)
                return true;
            else if (health > sPlayerbotAIConfig.lowHealth)
            {
                switch (player->getClass())
                {
                case CLASS_PRIEST:
                    if (health == player->GetHealthPercent())
                        ai->DoSpecificAction("renew");
                    else
                        ai->DoSpecificAction("renew on party");
                    return true;
                case CLASS_DRUID:
                    if (health == player->GetHealthPercent())
                        ai->DoSpecificAction("rejuvenation");
                    else
                        ai->DoSpecificAction("rejuvenation on party");
                    return true;
                case CLASS_SHAMAN:
                    if (health == player->GetHealthPercent())
                        ai->DoSpecificAction("riptide");
                    else
                        ai->DoSpecificAction("riptide on party");
                    return true;
                case CLASS_PALADIN:
                    if (health == player->GetHealthPercent())
                        ai->DoSpecificAction("holy shock");
                    else
                        ai->DoSpecificAction("holy shock on party");
                    return true;
                }
            }
            else return false; //stop moving someone is dying!
        }
    }

//damage dealers
    if (!target->IsHostileTo(player))
        return true;

	if (!GetMaster())
		return true;

    if (!ai->IsTank(bot) && !ai->GetMaster()->isInCombat())
        return true;

    switch (player->getClass())
    {
    case CLASS_HUNTER:
        ai->DoSpecificAction("explosive shot");
        ai->DoSpecificAction("chimera shot");
        ai->DoSpecificAction("arcane shot");
        return true;
    case CLASS_MAGE:
        if (player->getLevel() >= 66)
            ai->DoSpecificAction("ice lance");
        else ai->DoSpecificAction("fire blast");

        return true;
    case CLASS_DRUID:
        if (HasAnyAuraOf(player, "moonkin form",NULL))
            ai->DoSpecificAction("moonfire");
        return true;
    case CLASS_WARLOCK:
        ai->DoSpecificAction("corruption");
        return true;
    case CLASS_PRIEST:
         if (HasAnyAuraOf(player, "shadow form", NULL))
            ai->DoSpecificAction("shadow word:pain");
        return true;
    case CLASS_SHAMAN:
            ai->DoSpecificAction("flame shock");
            return true;
    }
    return true;
}


bool PlayerbotAI::IsTank(Player* player)
{
    PlayerbotAI* botAi = player->GetPlayerbotAI();

    if (botAi && botAi->ContainsStrategy(STRATEGY_TYPE_TANK))
        return true;

    switch (player->getClass())
    {
    case CLASS_PALADIN:
    case CLASS_WARRIOR:
        return true;
    case CLASS_DRUID:
        return HasAnyAuraOf(player, "bear form", "dire bear form", NULL);
    }
    return false;
}

bool PlayerbotAI::IsHeal(Player* player)
{
    PlayerbotAI* botAi = player->GetPlayerbotAI();
    if (botAi && botAi->ContainsStrategy(STRATEGY_TYPE_HEAL))
        return true;

    switch (player->getClass())
    {
    case CLASS_PRIEST:
        return !HasAnyAuraOf(player, "shadow form", NULL);
    case CLASS_SHAMAN:
        return HasAnyAuraOf(player, "water shield", NULL);
    case CLASS_PALADIN:
        return HasAnyAuraOf(player, "seal of wisdom", NULL);
    case CLASS_DRUID:
        return HasAnyAuraOf(player, "tree of life form", "caster form", NULL);
    }
    return false;
}



namespace MaNGOS
{

    class UnitByGuidInRangeCheck
    {
    public:
        UnitByGuidInRangeCheck(WorldObject const* obj, ObjectGuid guid, float range) : i_obj(obj), i_range(range), i_guid(guid) {}
        WorldObject const& GetFocusObject() const { return *i_obj; }
        bool operator()(Unit* u)
        {
            return u->GetGUID() == i_guid && i_obj->IsWithinDistInMap(u, i_range);
        }
    private:
        WorldObject const* i_obj;
        float i_range;
        ObjectGuid i_guid;
    };

    class GameObjectByGuidInRangeCheck
    {
    public:
        GameObjectByGuidInRangeCheck(WorldObject const* obj, ObjectGuid guid, float range) : i_obj(obj), i_range(range), i_guid(guid) {}
        WorldObject const& GetFocusObject() const { return *i_obj; }
        bool operator()(GameObject* u)
        {
            if (u && i_obj->IsWithinDistInMap(u, i_range) && u->isSpawned() && u->GetGOInfo() && u->GetGUID() == i_guid)
                return true;

            return false;
        }
    private:
        WorldObject const* i_obj;
        float i_range;
        ObjectGuid i_guid;
    };

};


Unit* PlayerbotAI::GetUnit(ObjectGuid guid)
{
    if (!guid)
        return NULL;

    Map* map = bot->GetMap();
    if (!map)
        return NULL;

    if (guid.IsPlayer())
        return ObjectAccessor::GetUnit(*bot,guid);

    if (guid.IsPet())
        return map->GetPet(guid);

    return map->GetCreature(guid);

//    return ObjectAccessor::GetObjectInMap(guid, map, (Unit*)NULL);
}


Creature* PlayerbotAI::GetCreature(ObjectGuid guid)
{
    if (!guid)
        return NULL;

    Map* map = bot->GetMap();
    if (!map)
        return NULL;

    return map->GetCreature(guid);
}

GameObject* PlayerbotAI::GetGameObject(ObjectGuid guid)
{
    if (!guid)
        return NULL;

    Map* map = bot->GetMap();
    if (!map)
        return NULL;

    return map->GetGameObject(guid);
}

bool PlayerbotAI::TellMasterNoFacing(string text, PlayerbotSecurityLevel securityLevel)
{
    Player* master = GetMaster();
	if (!master || master->IsBeingTeleported())
        return false;

    if (!GetSecurity()->CheckLevelFor(securityLevel, true, master))
        return false;

    if (sPlayerbotAIConfig.whisperDistance && !bot->GetGroup() && sRandomPlayerbotMgr.IsRandomBot(bot) &&
            master->GetSession()->GetSecurity() < SEC_GAMEMASTER &&
            (bot->GetMapId() != master->GetMapId() || bot->GetDistance(master) > sPlayerbotAIConfig.whisperDistance))
        return false;

	time_t lastSaid = whispers[text];
	if (!lastSaid || (time(0) - lastSaid) >= sPlayerbotAIConfig.maxWaitForMove / 1000)
		{
		  whispers[text] = time(0);
		  bot->Whisper(text, LANG_UNIVERSAL, master->GetGUID());
		}
    return true;
}

bool PlayerbotAI::TellMaster(string text, PlayerbotSecurityLevel securityLevel)
{
    if (!TellMasterNoFacing(text, securityLevel))
        return false;

    if (!bot->IsMoving() && !bot->isInCombat() && bot->GetMapId() == master->GetMapId())
    {
        if (!bot->isInFront(master, M_PI / 2))
            bot->SetFacingTo(bot->GetAngle(master));

        bot->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
    }

    return true;
}

bool IsRealAura(Player* bot, Aura const* aura, Unit* unit, BotAuraType auratype)
{
    if (!aura)
        return false;
//Debug
//    if (aura->GetSpellProto()->Is

//  if (!unit->IsHostileTo(bot))
//      return true;

    if (auratype == BOT_AURA_NORMAL)
    {
        if (!unit->IsHostileTo(bot))
            return true;
    }

    uint32 stacks = aura->GetStackAmount();
    if (aura->GetSpellProto()->StackAmount > 0 && stacks >= aura->GetSpellProto()->StackAmount)
        return true;

    if (aura->GetCaster() == bot || IsPositiveSpell(aura->GetSpellProto()) || aura->IsAreaAura())
        return true;

    if (aura->GetAuraMaxDuration() > 1500 && aura->GetAuraDuration() > 0 && (aura->GetAuraMaxDuration() - aura->GetAuraDuration() < 1500))
        return false;
  
  /*  if  (aura->GetSpellProto()->IsStackableOnOneSlotWithDifferentCasters())
    {
        if (aura->GetCaster())
            return (aura->GetCaster()->GetGUID() == bot->GetGUID());
    }
    else return false;
	*/

	return false;
}

bool IsRealOwnAura(Player* bot, Aura const* aura, Unit* unit, BotAuraType auratype)
{
   if (!aura)
        return false;
    //Debug

    if (!unit->IsHostileTo(bot))
        return true;

    uint32 stacks = aura->GetStackAmount();

    if (stacks >= aura->GetSpellProto()->StackAmount)
        return true;

	if (aura->GetCaster() == bot || IsPositiveSpell(aura->GetSpellProto()) || aura->IsAreaAura())
        return true;

    return false;
}


bool PlayerbotAI::HasAura(string name, Unit* unit, BotAuraType auratype)
{
    if (!unit)
        return false;

    wstring wnamepart;
    if (!Utf8toWStr(name, wnamepart))
        return 0;

    wstrToLower(wnamepart);

  for (uint32 auraType = SPELL_AURA_BIND_SIGHT; auraType < TOTAL_AURAS; auraType++)
	{
		Unit::AuraList const& auras = unit->GetAurasByType((AuraType)auraType);
		for (Unit::AuraList::const_iterator i = auras.begin(); i != auras.end(); i++)
		{
			Aura* aura = *i;
			if (!aura)
				continue;

			const string auraName = aura->GetSpellProto()->SpellName[0];
			if (auraName.empty() || auraName.length() != wnamepart.length() || !Utf8FitTo(auraName, wnamepart))
				continue;

			if (IsRealAura(bot, aura, unit, auratype))
				return true;
		}
    }
}

bool PlayerbotAI::HasOwnAura(string name, Unit* unit, BotAuraType auratype)
{
    if (!unit)
        return false;

    uint32 spellId = aiObjectContext->GetValue<uint32>("spell id", name)->Get();
    if (spellId)
        return HasOwnAura(spellId, unit);

    wstring wnamepart;
    if (!Utf8toWStr(name, wnamepart))
        return 0;

    wstrToLower(wnamepart);

	for (uint32 auraType = SPELL_AURA_BIND_SIGHT; auraType < TOTAL_AURAS; auraType++)
	{
		Unit::AuraList const& auras = unit->GetAurasByType((AuraType)auraType);
		for (Unit::AuraList::const_iterator i = auras.begin(); i != auras.end(); i++)
		{
			Aura* aura = *i;
			if (!aura)
				continue;

			const string auraName = aura->GetSpellProto()->SpellName[0];
			if (auraName.empty() || auraName.length() != wnamepart.length() || !Utf8FitTo(auraName, wnamepart))
				continue;

			if (IsRealOwnAura(bot, aura, unit, auratype))
				return true;
		}
	}

    return false;
}

bool PlayerbotAI::HasAura(uint32 spellId, const Unit* unit, BotAuraType auratype)
{
    if (!spellId || !unit)
        return false;

	for (uint32 effect = EFFECT_INDEX_0; effect <= EFFECT_INDEX_2; effect++)
	{
		Aura* aura = ((Unit*)unit)->GetAura(spellId, (SpellEffectIndex)effect);
		
        if (IsRealAura(bot, aura, (Unit*)unit,auratype))
            return true;
    }

    return false;
}

bool PlayerbotAI::HasOwnAura(uint32 spellId, const Unit* unit, BotAuraType auratype)
{
    if (!spellId || !unit)
        return false;

	for (uint32 effect = EFFECT_INDEX_0; effect <= EFFECT_INDEX_2; effect++)
	{
		Aura* aura = ((Unit*)unit)->GetAura(spellId, (SpellEffectIndex)effect);

		if (IsRealOwnAura(bot, aura, (Unit*)unit,auratype))
            return true;
    }

    return false;
}

bool PlayerbotAI::HasAnyAuraOf(Unit* player, ...)
{
    if (!player)
        return false;

    va_list vl;
    va_start(vl, player);

    const char* cur;
    do {
        cur = va_arg(vl, const char*);
        if (cur && HasAura(cur, player)) {
            va_end(vl);
            return true;
        }
    }
    while (cur);

    va_end(vl);
    return false;
}

bool PlayerbotAI::CanCastSpell(string name, Unit* target, bool interruptcasting)
{
    return CanCastSpell(aiObjectContext->GetValue<uint32>("spell id", name)->Get(), target,true,interruptcasting);
}

bool PlayerbotAI::CanCastSpell(uint32 spellid, Unit* target, bool checkHasSpell, bool interruptcasting)
{
    if (!spellid)
        return false;

    if (!target)

        target = bot;

    if (checkHasSpell && !bot->HasSpell(spellid))
        return false;
//?
    if (bot->HasSpellCooldown(spellid))
       return false;

	SpellEntry const *spellInfo = sSpellMgr.GetSpellEntry(spellid);
	if (!spellInfo)
		return false;

    bool positiveSpell = IsPositiveSpell(spellInfo);
    if (positiveSpell && bot->IsHostileTo(target))
        return false;

    if (!positiveSpell && bot->IsFriendlyTo(target))
        return false;

	if (target->IsImmuneToSpell(spellInfo, false))
        return false;

  //  if (target->IsImmunedToDamage(SpellProto->GetSchoolMask()))
  //      return false;

    if (bot != target && bot->GetDistance(target) > sPlayerbotAIConfig.sightDistance)
        return false;
/*
    if (positiveSpell)
    {
        Spell* castingSpell = bot->GetCurrentSpell(CURRENT_GENERIC_SPELL);
        if (castingSpell && castingSpell->GetSpellProto()->IsPositive())
            return false;

        Spell* channelSpell = bot->GetCurrentSpell(CURRENT_CHANNELED_SPELL);
        if (channelSpell && channelSpell->GetSpellProto()->IsPositive())
            return false;
        }
*/

   if (!interruptcasting)
   {
	if (bot->IsNonMeleeSpellCasted(true))
	    return false;

        Spell* castingSpell = bot->GetCurrentSpell(CURRENT_GENERIC_SPELL);
        if (castingSpell)
            return false;

        Spell* channelSpell = bot->GetCurrentSpell(CURRENT_CHANNELED_SPELL);
        if (channelSpell)
            return false;
	}

   ObjectGuid oldSel = bot->GetSelectionGuid();
   bot->SetSelectionGuid(target->GetObjectGuid());
   Spell *spell = new Spell(bot, spellInfo, false);

	spell->m_targets.setUnitTarget(target);
	spell->m_CastItem = aiObjectContext->GetValue<Item*>("item for spell", spellid)->Get();
	spell->m_targets.setItemTarget(spell->m_CastItem);
	SpellCastResult result = spell->CheckCast(false);
    delete spell;
	if (oldSel)
		bot->SetSelectionGuid(oldSel);

    switch (result)
    {
    case SPELL_FAILED_NOT_INFRONT:
    {
        TellMaster("Cast failed: Not in front");
        return true;
        }
    case SPELL_FAILED_NOT_STANDING:
    {
        TellMaster("Cast failed: Not standing");
        return true;
    }
    case SPELL_FAILED_UNIT_NOT_INFRONT:
    {
        TellMaster("Cast failed: Not in front");
        return true;
        }
    case SPELL_FAILED_MOVING:
     {
        TellMaster("Cast failed: Moving");
        return true;
        }
    case SPELL_FAILED_TRY_AGAIN:
    {
        TellMaster("Cast failed: Try again");
        return true;
        }
       case SPELL_FAILED_BAD_IMPLICIT_TARGETS:
    case SPELL_FAILED_BAD_TARGETS:
    {
        TellMaster("Cast failed: Bad target");
        return true;
        }
    case SPELL_CAST_OK:
        return true;
    default:
        return false;
    }
}


bool PlayerbotAI::CastSpell(string name, Unit* target)
{
    bool result = CastSpell(aiObjectContext->GetValue<uint32>("spell id", name)->Get(), target);
    if (result)
    {
        aiObjectContext->GetValue<time_t>("last spell cast time", name)->Set(time(0));
    }

    return result;
}

bool PlayerbotAI::CastSpell(uint32 spellId, Unit* target)
{
    if (!spellId)
        return false;

    if (!target)
        target = bot;

    Pet* pet = bot->GetPet();
	SpellEntry const *pSpellInfo = sSpellMgr.GetSpellEntry(spellId);
	if (pet && pet->HasSpell(spellId))
	{
		pet->ToggleAutocast(spellId, true);
		TellMaster("My pet will auto-cast this spell");
		return true;
	}

    aiObjectContext->GetValue<LastSpellCast&>("last spell cast")->Get().Set(spellId, target->GetGUID(), time(0));
    aiObjectContext->GetValue<LastMovement&>("last movement")->Get().Set(NULL);

    MotionMaster &mm = *bot->GetMotionMaster();

    if (bot->IsFlying())
        return false;

	bot->clearUnitState(UNIT_STAT_CHASE);
	bot->clearUnitState(UNIT_STAT_FOLLOW);

	ObjectGuid oldSel = bot->GetSelectionGuid();
	bot->SetSelectionGuid(target->GetGUID());

	Spell *spell = new Spell(bot, pSpellInfo, false);
	if (bot->IsMoving() && spell->GetCastTime())
	{
		spell->cancel();
		delete spell;		
		return false;
	}

	SpellCastTargets targets;
	WorldObject* faceTo = target;

	if (pSpellInfo->Targets & TARGET_FLAG_ITEM)
	{
		spell->m_CastItem = aiObjectContext->GetValue<Item*>("item for spell", spellId)->Get();
		targets.setItemTarget(spell->m_CastItem);
	}
	else if (pSpellInfo->Targets & TARGET_FLAG_DEST_LOCATION)
	{
		WorldLocation aoe = aiObjectContext->GetValue<WorldLocation>("aoe position")->Get();
		targets.setDestination(aoe.coord_x, aoe.coord_y, aoe.coord_z);
	}
	else if (pSpellInfo->Targets & TARGET_FLAG_SOURCE_LOCATION)
	{
		targets.setDestination(bot->GetPositionX(), bot->GetPositionY(), bot->GetPositionZ());
	}
	else
	{
		targets.setUnitTarget(target);
	}

	if (pSpellInfo->Effect[0] == SPELL_EFFECT_OPEN_LOCK ||
		pSpellInfo->Effect[0] == SPELL_EFFECT_SKINNING)
	{
		LootObject loot = *aiObjectContext->GetValue<LootObject>("loot target");
		if (!loot.IsLootPossible(bot))
		{
			spell->cancel();
			delete spell;			
			return false;
		}

		GameObject* go = GetGameObject(loot.guid);
		if (go && go->isSpawned())
		{
			WorldPacket* packetgouse = new WorldPacket(CMSG_GAMEOBJ_USE, 8);
			*packetgouse << loot.guid;
			bot->GetSession()->QueuePacket(std::move(packetgouse));
			targets.setGOTarget(go);
			faceTo = go;
		}
		else
		{
			Unit* creature = GetUnit(loot.guid);
			if (creature)
			{
				targets.setUnitTarget(creature);
				faceTo = creature;
			}
		}
    }


	if (!bot->isInFront(faceTo, sPlayerbotAIConfig.sightDistance, M_PI / 2))
	{
		bot->SetFacingTo(bot->GetAngle(faceTo));
		spell->cancel();
		delete spell;
		SetNextCheckDelay(sPlayerbotAIConfig.globalCoolDown);
		return false;
	}

	spell->prepare(targets);
	WaitForSpellCast(spell);
	aiObjectContext->GetValue<LastSpellCast&>("last spell cast")->Get().Set(spellId, target->GetGUID(), time(0));

	if (oldSel)
		bot->SetSelectionGuid(oldSel);
	
	return true;
}

void PlayerbotAI::WaitForSpellCast(Spell *spell)
{
	const SpellEntry* const pSpellInfo = spell->m_spellInfo;

    float castTime = spell->GetCastTime();
	if (IsChanneledSpell(pSpellInfo))
    {
        int32 duration = GetSpellDuration(pSpellInfo);
        if (duration > 0)
            castTime += duration;
    }

    castTime = ceil(castTime);

    uint32 globalCooldown = CalculateGlobalCooldown(pSpellInfo->Id);
    if (castTime < globalCooldown)
        castTime = globalCooldown;

    SetNextCheckDelay(castTime + sPlayerbotAIConfig.reactDelay);
}

void PlayerbotAI::InterruptSpell()
{
    if (bot->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
        return;

    TellMaster("Interrupting...");
    LastSpellCast& lastSpell = aiObjectContext->GetValue<LastSpellCast&>("last spell cast")->Get();

    for (int type = CURRENT_MELEE_SPELL; type < CURRENT_CHANNELED_SPELL; type++)
    {
        Spell* spell = bot->GetCurrentSpell((CurrentSpellTypes)type);
        if (!spell)
            continue;

		if (IsPositiveSpell(spell->m_spellInfo))
			continue;

        bot->InterruptSpell((CurrentSpellTypes)type);

        WorldPacket data(SMSG_SPELL_FAILURE, 8 + 1 + 4 + 1);
        data.appendPackGUID(bot->GetGUID());
        data << uint8(1);
        data << uint32(spell->m_spellInfo->Id);
        data << uint8(0);
        bot->SendMessageToSet(&data, true);

        data.Initialize(SMSG_SPELL_FAILED_OTHER, 8 + 1 + 4 + 1);
        data.appendPackGUID(bot->GetGUID());
        data << uint8(1);
        data << uint32(spell->m_spellInfo->Id);
        data << uint8(0);
        bot->SendMessageToSet(&data, true);

        SpellInterrupted(spell->m_spellInfo->Id);
    }

    SpellInterrupted(lastSpell.id);
}


void PlayerbotAI::RemoveAura(string name)
{
    uint32 spellid = aiObjectContext->GetValue<uint32>("spell id", name)->Get();
    if (spellid && HasAura(spellid, bot))
        bot->RemoveAurasDueToSpell(spellid);
}

bool PlayerbotAI::IsInterruptableSpellCasting(Unit* target, string spell)
{
    uint32 spellid = aiObjectContext->GetValue<uint32>("spell id", spell)->Get();
    if (!spellid || !target->IsNonMeleeSpellCasted(true))
        return false;

	SpellEntry const *spellInfo = sSpellMgr.GetSpellEntry(spellid);
	if (!spellInfo)
		return false;

	if (target->IsImmuneToSpell(spellInfo, false))
        return false;

	for (int32 i = EFFECT_INDEX_0; i <= EFFECT_INDEX_2; i++)
	{
		if ((spellInfo->InterruptFlags & SPELL_INTERRUPT_FLAG_INTERRUPT) && spellInfo->PreventionType == SPELL_PREVENTION_TYPE_SILENCE)
			return true;

		if ((spellInfo->Effect[i] == SPELL_EFFECT_INTERRUPT_CAST) &&
			!target->IsImmuneToSpellEffect(spellInfo, (SpellEffectIndex)i, true))
			return true;
	}

    return false;
}

bool PlayerbotAI::HasAuraToDispel(Unit* target, uint32 dispelType)
{

	for (uint32 type = SPELL_AURA_NONE; type < TOTAL_AURAS; ++type)
	{
		Unit::AuraList const& auras = target->GetAurasByType((AuraType)type);
		for (Unit::AuraList::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
		{
			const Aura* aura = *itr;
			const SpellEntry* entry = aura->GetSpellProto();
			uint32 spellId = entry->Id;

			bool isPositiveSpell = IsPositiveSpell(spellId);
			if (isPositiveSpell && bot->IsFriendlyTo(target))
				continue;

			if (!isPositiveSpell && bot->IsHostileTo(target))
				continue;

			if (canDispel(entry, dispelType))
				return true;
		}
	}
	return false;
}


#ifndef WIN32
inline int strcmpi(const char* s1, const char* s2)
{
    for (; *s1 && *s2 && (toupper(*s1) == toupper(*s2)); ++s1, ++s2);
    return *s1 - *s2;
}
#endif

bool PlayerbotAI::canDispel(const SpellEntry* entry, uint32 dispelType)
{
    if (entry->Dispel != dispelType)
        return false;

    return !entry->SpellName[0] ||
        (strcmpi((const char*)entry->SpellName[0], "demon skin") &&
        strcmpi((const char*)entry->SpellName[0], "mage armor") &&
        strcmpi((const char*)entry->SpellName[0], "frost armor") &&
        strcmpi((const char*)entry->SpellName[0], "wavering will") &&
        strcmpi((const char*)entry->SpellName[0], "chilled") &&
        strcmpi((const char*)entry->SpellName[0], "ice armor"));
}

bool IsAlliance(uint8 race)
{
    return race == RACE_HUMAN || race == RACE_DWARF || race == RACE_NIGHTELF ||
            race == RACE_GNOME || race == RACE_DRAENEI;
}

bool PlayerbotAI::IsOpposing(Player* player)
{
    return IsOpposing(player->getRace(), bot->getRace());
}

bool PlayerbotAI::IsOpposing(uint8 race1, uint8 race2)
{
    return (IsAlliance(race1) && !IsAlliance(race2)) || (!IsAlliance(race1) && IsAlliance(race2));
}

void PlayerbotAI::RemoveShapeshift()
{
    RemoveAura("bear form");
    RemoveAura("dire bear form");
    RemoveAura("moonkin form");
    RemoveAura("travel form");
    RemoveAura("cat form");
    RemoveAura("flight form");
    RemoveAura("swift flight form");
    RemoveAura("aquatic form");
    RemoveAura("ghost wolf");
    RemoveAura("tree of life");
}

uint32 PlayerbotAI::GetEquipGearScore(Player* player, bool withBags, bool withBank)
{
    std::vector<uint32> gearScore(EQUIPMENT_SLOT_END);
    uint32 twoHandScore = 0;

    for (uint8 i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
    {
        if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            _fillGearScoreData(player, item, &gearScore, twoHandScore);
    }

    if (withBags)
    {
        // check inventory
        for (int i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; ++i)
        {
            if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
                _fillGearScoreData(player, item, &gearScore, twoHandScore);
        }

        // check bags
        for (int i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
        {
            if (Bag* pBag = (Bag*)player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            {
                for (uint32 j = 0; j < pBag->GetBagSize(); ++j)
                {
                    if (Item* item2 = pBag->GetItemByPos(j))
                        _fillGearScoreData(player, item2, &gearScore, twoHandScore);
                }
            }
        }
    }

    if (withBank)
    {
        for (uint8 i = BANK_SLOT_ITEM_START; i < BANK_SLOT_ITEM_END; ++i)
        {
            if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
                _fillGearScoreData(player, item, &gearScore, twoHandScore);
        }

        for (uint8 i = BANK_SLOT_BAG_START; i < BANK_SLOT_BAG_END; ++i)
        {
            if (Item* item = player->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            {
                if (item->IsBag())
                {
                    Bag* bag = (Bag*)item;
                    for (uint8 j = 0; j < bag->GetBagSize(); ++j)
                    {
                        if (Item* item2 = bag->GetItemByPos(j))
                            _fillGearScoreData(player, item2, &gearScore, twoHandScore);
                    }
                }
            }
        }
    }

    uint8 count = EQUIPMENT_SLOT_END - 2;   // ignore body and tabard slots
    uint32 sum = 0;

    // check if 2h hand is higher level than main hand + off hand
    if (gearScore[EQUIPMENT_SLOT_MAINHAND] + gearScore[EQUIPMENT_SLOT_OFFHAND] < twoHandScore * 2)
    {
        gearScore[EQUIPMENT_SLOT_OFFHAND] = 0;  // off hand is ignored in calculations if 2h weapon has higher score
        --count;
        gearScore[EQUIPMENT_SLOT_MAINHAND] = twoHandScore;
    }

    for (uint8 i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
    {
       sum += gearScore[i];
    }

    if (count)
    {
        uint32 res = uint32(sum / count);
        return res;
    }
    else
        return 0;
}

void PlayerbotAI::_fillGearScoreData(Player *player, Item* item, std::vector<uint32>* gearScore, uint32& twoHandScore)
{
    if (!item)
        return;

    if (player->CanUseItem(item->GetProto()) != EQUIP_ERR_OK)
        return;

    uint8 type   = item->GetProto()->InventoryType;
    uint32 level = item->GetProto()->ItemLevel;

    switch (type)
    {
        case INVTYPE_2HWEAPON:
            twoHandScore = std::max(twoHandScore, level);
            break;
        case INVTYPE_WEAPON:
        case INVTYPE_WEAPONMAINHAND:
            (*gearScore)[SLOT_MAIN_HAND] = std::max((*gearScore)[SLOT_MAIN_HAND], level);
            break;
        case INVTYPE_SHIELD:
        case INVTYPE_WEAPONOFFHAND:
            (*gearScore)[EQUIPMENT_SLOT_OFFHAND] = std::max((*gearScore)[EQUIPMENT_SLOT_OFFHAND], level);
            break;
        case INVTYPE_THROWN:
        case INVTYPE_RANGEDRIGHT:
        case INVTYPE_RANGED:
        case INVTYPE_QUIVER:
        case INVTYPE_RELIC:
            (*gearScore)[EQUIPMENT_SLOT_RANGED] = std::max((*gearScore)[EQUIPMENT_SLOT_RANGED], level);
            break;
        case INVTYPE_HEAD:
            (*gearScore)[EQUIPMENT_SLOT_HEAD] = std::max((*gearScore)[EQUIPMENT_SLOT_HEAD], level);
            break;
        case INVTYPE_NECK:
            (*gearScore)[EQUIPMENT_SLOT_NECK] = std::max((*gearScore)[EQUIPMENT_SLOT_NECK], level);
            break;
        case INVTYPE_SHOULDERS:
            (*gearScore)[EQUIPMENT_SLOT_SHOULDERS] = std::max((*gearScore)[EQUIPMENT_SLOT_SHOULDERS], level);
            break;
        case INVTYPE_BODY:
            (*gearScore)[EQUIPMENT_SLOT_BODY] = std::max((*gearScore)[EQUIPMENT_SLOT_BODY], level);
            break;
        case INVTYPE_CHEST:
            (*gearScore)[EQUIPMENT_SLOT_CHEST] = std::max((*gearScore)[EQUIPMENT_SLOT_CHEST], level);
            break;
        case INVTYPE_WAIST:
            (*gearScore)[EQUIPMENT_SLOT_WAIST] = std::max((*gearScore)[EQUIPMENT_SLOT_WAIST], level);
            break;
        case INVTYPE_LEGS:
            (*gearScore)[EQUIPMENT_SLOT_LEGS] = std::max((*gearScore)[EQUIPMENT_SLOT_LEGS], level);
            break;
        case INVTYPE_FEET:
            (*gearScore)[EQUIPMENT_SLOT_FEET] = std::max((*gearScore)[EQUIPMENT_SLOT_FEET], level);
            break;
        case INVTYPE_WRISTS:
            (*gearScore)[EQUIPMENT_SLOT_WRISTS] = std::max((*gearScore)[EQUIPMENT_SLOT_WRISTS], level);
            break;
        case INVTYPE_HANDS:
            (*gearScore)[EQUIPMENT_SLOT_HEAD] = std::max((*gearScore)[EQUIPMENT_SLOT_HEAD], level);
            break;
        // equipped gear score check uses both rings and trinkets for calculation, assume that for bags/banks it is the same
        // with keeping second highest score at second slot
        case INVTYPE_FINGER:
        {
            if ((*gearScore)[EQUIPMENT_SLOT_FINGER1] < level)
            {
                (*gearScore)[EQUIPMENT_SLOT_FINGER2] = (*gearScore)[EQUIPMENT_SLOT_FINGER1];
                (*gearScore)[EQUIPMENT_SLOT_FINGER1] = level;
            }
            else if ((*gearScore)[EQUIPMENT_SLOT_FINGER2] < level)
                (*gearScore)[EQUIPMENT_SLOT_FINGER2] = level;
            break;
        }
        case INVTYPE_TRINKET:
        {
            if ((*gearScore)[EQUIPMENT_SLOT_TRINKET1] < level)
            {
                (*gearScore)[EQUIPMENT_SLOT_TRINKET2] = (*gearScore)[EQUIPMENT_SLOT_TRINKET1];
                (*gearScore)[EQUIPMENT_SLOT_TRINKET1] = level;
            }
            else if ((*gearScore)[EQUIPMENT_SLOT_TRINKET2] < level)
                (*gearScore)[EQUIPMENT_SLOT_TRINKET2] = level;
            break;
        }
        case INVTYPE_CLOAK:
            (*gearScore)[EQUIPMENT_SLOT_BACK] = std::max((*gearScore)[EQUIPMENT_SLOT_BACK], level);
            break;
        default:
            break;
    }
}

string PlayerbotAI::HandleRemoteCommand(string command)
{
    if (command == "state")
    {
        switch (currentState)
        {
        case BOT_STATE_COMBAT:
            return "combat";
        case BOT_STATE_DEAD:
            return "dead";
        case BOT_STATE_NON_COMBAT:
            return "non-combat";
        default:
            return "unknown";
        }
    }
    else if (command == "position")
    {
        ostringstream out; out << bot->GetPositionX() << " " << bot->GetPositionY() << " " << bot->GetPositionZ() << " " << bot->GetMapId() << " " << bot->GetOrientation();
        return out.str();
    }
    else if (command == "tpos")
    {
        Unit* target = *GetAiObjectContext()->GetValue<Unit*>("current target");
        if (!target) {
            return "";
        }

        ostringstream out; out << target->GetPositionX() << " " << target->GetPositionY() << " " << target->GetPositionZ() << " " << target->GetMapId() << " " << target->GetOrientation();
        return out.str();
    }
    else if (command == "movement")
    {
        LastMovement& data = *GetAiObjectContext()->GetValue<LastMovement&>("last movement");
        ostringstream out; out << data.lastMoveToX << " " << data.lastMoveToY << " " << data.lastMoveToZ << " " << bot->GetMapId() << " " << data.lastMoveToOri;
        return out.str();
    }
	else if (command == "tpos")
		 {
		Unit* target = *GetAiObjectContext()->GetValue<Unit*>("current target");
		if (!target) {
			return "";

		}

		ostringstream out; out << target->GetPositionX() << " " << target->GetPositionY() << " " << target->GetPositionZ() << " " << target->GetMapId() << " " << target->GetOrientation();
		return out.str();
		}
    else if (command == "target")
    {
        Unit* target = *GetAiObjectContext()->GetValue<Unit*>("current target");
        if (!target) {
            return "";
        }

        return target->GetName();
    }
     else if (command == "movement")
    {
        LastMovement& data = *GetAiObjectContext()->GetValue<LastMovement&>("last movement");
        ostringstream out; out << data.lastMoveToX << " " << data.lastMoveToY << " " << data.lastMoveToZ << " " << bot->GetMapId() << " " << data.lastMoveToOri;
        return out.str();
    }
    else if (command == "hp")
    {
        int pct = (int)((static_cast<float> (bot->GetHealth()) / bot->GetMaxHealth()) * 100);
        ostringstream out; out << pct << "%";

        Unit* target = *GetAiObjectContext()->GetValue<Unit*>("current target");
        if (!target) {
            return out.str();
        }

        pct = (int)((static_cast<float> (target->GetHealth()) / target->GetMaxHealth()) * 100);
        out << " / " << pct << "%";
        return out.str();
    }
    else if (command == "strategy")
    {
        return currentEngine->ListStrategies();
    }
    else if (command == "action")
    {
        return currentEngine->GetLastAction();
    }
    else if (command == "values")
    {
        return GetAiObjectContext()->FormatValues();
    }

    ostringstream out; out << "invalid command: " << command;
    return out.str();
}

void PlayerbotAI::LogAction(const char* format, ...)
{
    char buf[1024];

    va_list ap;
    va_start(ap, format);
    vsprintf(buf, format, ap);
    va_end(ap);

    Player* bot = GetBot();
    if (sPlayerbotAIConfig.logInGroupOnly && !bot->GetGroup())
        return;

    sLog.outDebug( "%s %s", bot->GetName(), buf);
}

bool EventBotAI::OnSessionLoaded(EventBotEntry* entry, WorldSession* sess)
{
    sess->LoginPlayer(entry->playerGUID);
    return true;
}

void EventBotAI::UpdateAI(const uint32 diff)
{
    if (me->IsBeingTeleportedNear())
    {
        WorldPacket data(MSG_MOVE_TELEPORT_ACK, 10);
        data << me->GetObjectGuid();
        data << uint32(0) << uint32(0);
        me->GetSession()->HandleMoveTeleportAckOpcode(data);
    }
    if (me->IsBeingTeleportedFar())
        me->GetSession()->HandleMoveWorldportAckOpcode();
}

void EventBotAI::Remove()
{
    me->setAI(NULL);
    me = NULL;
}

void EventBotFleeingAI::OnPlayerLogin()
{
    me->GetMotionMaster()->MoveFleeing(me);
    me->SetGodMode(true);
}

/// MageOrgrimmarAttackerAI event
enum
{
    SPELL_FROST_NOVA = 122,
    SPELL_FIREBOLT = 133,
    AURA_REGEN_MANA = 430,
};


bool EventBotAI::SpawnNewPlayer(WorldSession* sess, uint8 class_, uint32 race_, uint32 mapId, uint32 instanceId, float x, float y, float z, float o)
{
    ASSERT(botEntry);
    std::string name = sObjectMgr.GeneratePetName(1863); // Succubus name
    normalizePlayerName(name);
    uint8 gender = urand(0, 1);
    uint8 skin = urand(0, 5);
    uint8 face = urand(0, 5);
    uint8 hairStyle = urand(0, 5);
    uint8 hairColor = urand(0, 5);
    uint8 facialHair = urand(0, 5);
    uint8 outfitId = urand(0, 10);
    Player *newChar = new Player(sess);
    uint32 guid = botEntry->playerGUID;
    if (!newChar->Create(guid, name, race_, class_, gender, skin, face, hairStyle, hairColor, facialHair, outfitId))
    {
        sLog.outError("EventBotAI::SpawnNewPlayer: Unable to create a player!");
        delete newChar;
        return false;
    }
    newChar->SetLocationMapId(mapId);
    newChar->SetLocationInstanceId(instanceId);
    newChar->SetAutoInstanceSwitch(false);
    newChar->GetMotionMaster()->Initialize();
    newChar->setCinematic(1);
    // Set instance
    if (instanceId && mapId > 1) // Not a continent
    {
        DungeonPersistentState *state = (DungeonPersistentState*)sMapPersistentStateMgr
                .AddPersistentState(sMapStorage.LookupEntry<MapEntry>(mapId), instanceId, time(nullptr) + 3600, false, true);
        newChar->BindToInstance(state, true, true);
    }
    // Generate position
    Map* map = sMapMgr.FindMap(mapId, instanceId);
    if (!map)
    {
        sLog.outError("EventBotAI::SpawnNewPlayer: Map (%u, %u) not found!", mapId, instanceId);
        delete newChar;
        return false;
    }
    newChar->Relocate(x, y, z, o);
    sObjectMgr.InsertPlayerInCache(newChar);
    newChar->SetMap(map);
    newChar->CreatePacketBroadcaster();
    MasterPlayer* mPlayer = new MasterPlayer(sess);
    mPlayer->LoadPlayer(newChar);
    mPlayer->SetSocial(sSocialMgr.LoadFromDB(NULL, newChar->GetObjectGuid()));
    if (!newChar->GetMap()->Add(newChar))
    {
        sLog.outError("EventBotAI::SpawnNewPlayer: Unable to add player to map!");
        delete newChar;
        return false;
    }
    sess->SetPlayer(newChar);
    sess->SetMasterPlayer(mPlayer);
    sObjectAccessor.AddObject(newChar);
    return true;
}
bool MageOrgrimmarAttackerAI::OnSessionLoaded(EventBotEntry* entry, WorldSession* sess)
{
    return SpawnNewPlayer(sess, CLASS_MAGE, RACE_GNOME, 1, 0, 1017.0f, -4450, 12, 0.65f);
}

void MageOrgrimmarAttackerAI::UpdateAI(const uint32 diff)
{
    EventBotAI::UpdateAI(diff);
    if (me->getLevel() != 60)
        me->GiveLevel(60);
    /// DEATH
    if (!me->isAlive())
    {
        sEventBotMgr.deleteBot(me->GetGUIDLow());
        /*
        if (me->getDeathState() < CORPSE)
            return;
        if (me->getDeathState() == CORPSE && me->GetDeathTimer() && me->GetDeathTimer() < (6 * MINUTE * IN_MILLISECONDS - 30000))
        {
            me->SetHealth(1);
            me->RepopAtGraveyard();
        }
        else if (me->getDeathState() == CORPSE && !me->GetDeathTimer())
        {
            me->ResurrectPlayer(0.5f);
            me->SpawnCorpseBones();
        }
        */
        return;
    }
    /// COMBAT AI
    if (me->IsNonMeleeSpellCasted(false) || (me->HasAura(AURA_REGEN_MANA) && me->GetPower(POWER_MANA) != me->GetMaxPower(POWER_MANA)))
        return;
    float range = me->isInCombat() ? 30.0f : frand(15, 30);
    Unit* target = me->SelectNearestTarget(range);
    if (target && !me->IsWithinLOSInMap(target))
        target = NULL;
    // OOM ?
    if (me->GetPower(POWER_MANA) < 40 && target && me->isInCombat())
    {
        if (me->Attack(target, true))
            me->GetMotionMaster()->MoveChase(target);
        return;
    }
    // Stop chase if has mana
    if (me->GetMotionMaster()->GetCurrentMovementGeneratorType() == CHASE_MOTION_TYPE)
        me->GetMotionMaster()->MovementExpired();
    bool nearTarget = target && target->IsWithinMeleeRange(me);
    if (!me->HasSpellCooldown(SPELL_FROST_NOVA) && me->GetPower(POWER_MANA) > 50)
        if (nearTarget)
            me->CastSpell(me, SPELL_FROST_NOVA, false);
    if (nearTarget && target->hasUnitState(UNIT_STAT_CAN_NOT_MOVE))
    {
        // already runing
        if (!me->movespline->Finalized())
            return;
        // Try to kit
        float x, y, z;
        me->GetPosition(x, y, z);
        float d = me->GetDistance(target);
        d += me->GetObjectBoundingRadius();
        d += target->GetObjectBoundingRadius();
        x += (x - target->GetPositionX()) * 5.0f / d;
        y += (y - target->GetPositionY()) * 5.0f / d;
        me->UpdateGroundPositionZ(x, y, z);
        me->GetMotionMaster()->MovePoint(0, x, y, z, MOVE_PATHFINDING);
        return;
    }

    if (target && me->GetPower(POWER_MANA) > 50)
    {
        uint32 spellId = SPELL_FIREBOLT;
        me->SetFacingToObject(target);
        if (!me->movespline->Finalized())
            me->StopMoving();

        /*float z = me->GetPositionZ();
        me->UpdateGroundPositionZ(me->GetPositionX(), me->GetPositionY(), z);
        me->Relocate(me->GetPositionX(), me->GetPositionY(), z);
        me->m_movementInfo.moveFlags = 0;
        me->SendHeartBeat();*/

        me->CastSpell(target, spellId, false);
        return;
    }
    /// OUT OF COMBAT REGEN
    if (!me->isInCombat() && me->GetPower(POWER_MANA) < 150)
    {
        if (!me->movespline->Finalized())
            me->StopMoving();
        me->CastSpell(target, AURA_REGEN_MANA, false);
        return;
    }
    /// MOVEMENT AI
    float x, y, z = 0; // Where to go
    float r = 10;
    if (me->movespline->Finalized())
    {
        if (me->GetPositionX() < 1000.0f)
        {
            x = 1176;
            y = -4404;
        }
        else if (me->GetPositionX() + 10 < 1176.0f)
        {
            x = 1176;
            y = -4404;
        }
        else if (me->GetPositionX() + 10 < 1357.0f)
        {
            switch (urand(0, 1))
            {
                case 0:
                    x = 1357;
                    y = -4376;
                    break;
                case 1:
                    x = 1354;
                    y = -4412;
                    break;
                case 2:
                    x = 1346;
                    y = -4339;
                    break;
            }
        }
        else if (me->GetPositionX() + 10 < 1421.0f)
        {
            // Porte orgri
            x = 1427;
            y = -4362;
            z = 25.0f;
            r = 4;
        }
        else
        {
            switch (urand(0, 2))
            {
                case 0:
                    x = 1516;
                    y = -4410;
                    z = 17.0f;
                    r = 4;
                    break;
                case 1:
                    x = 1538;
                    y = -4347;
                    z = 18;
                    r = 3;
                    break;
                case 2:
                    x = 1617;
                    y = -4426;
                    z = 12;
                    r = 4;
                    break;
            }
        }
        if (!z)
        {
            z = me->GetPositionZ();
            me->UpdateGroundPositionZ(x, y, z);
        }
        r = 20;
        if (!me->GetMap()->GetWalkRandomPosition(NULL, x, y, z, r))
            return;
    }
    else
    {
        return;
        if (urand(0, 20) == 0) // random move
        {
            me->GetPosition(x, y, z);
            r = frand(0, 2);
            float angle = me->GetOrientation() + frand(-M_PI_F / 2, M_PI_F / 2);
            x += r * cos(angle);
            y += r * sin(angle);
            if (!me->GetMap()->GetWalkHitPosition(NULL, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), x, y, z))
                return;
        }
        else
            return;
    }
    me->GetMotionMaster()->MovePoint(0, x, y, z, MOVE_PATHFINDING);
}

void PopulateAreaBotAI::BeforeAddToMap(Player* player)
{
    if (player->GetInstanceId() || player->GetTeam() != _team)
        return;
    if (player->GetMapId() != _map || !player->IsWithinDist3d(_x, _y, _z, _radius * 2))
    {
        float x = _x;
        float y = _y;
        float z = _z;
        Map* map = sMapMgr.CreateMap(_map, player);
        while (!map->GetWalkRandomPosition(NULL, x, y, z, _radius));
        player->Relocate(x, y, z);
        player->SetLocationMapId(_map);
    }
}

void PopulateAreaBotAI::OnPlayerLogin()
{
    if (urand(0, 1))
        me->GetMotionMaster()->MoveConfused();
}

EventBotAI* CreateEventBotAI(std::string ainame)
{
    if (ainame == "MageOrgrimmarAttackerAI")
        return new MageOrgrimmarAttackerAI();
    if (ainame == "IronforgePopulationAI")
        return new PopulateAreaBotAI(0, -4928.5f, -946.6f, 501.6f, ALLIANCE, 100.0f);
    if (ainame == "StormwindPopulationAI")
        return new PopulateAreaBotAI(0, -8829.5f, 625.6f, 93.9f, ALLIANCE, 50.0f);
    if (ainame == "OrgrimmarPopulationAI")
        return new PopulateAreaBotAI(1, 1568, -4405.87f, 8.13f, HORDE, 150.0f);
    if (ainame == "EventBotFleeingAI")
        return new EventBotFleeingAI();
    return new EventBotAI();
}
