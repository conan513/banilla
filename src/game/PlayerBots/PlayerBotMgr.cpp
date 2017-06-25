#include "../pchdef.h"
#include "playerbot.h"
#include "PlayerbotAIConfig.h"
#include "PlayerbotDbStore.h"
#include "PlayerbotFactory.h"
#include "RandomPlayerbotMgr.h"

#include "Common.h"
#include "Policies/SingletonImp.h"
#include "PlayerBotMgr.h"
#include "ObjectMgr.h"
#include "World.h"
#include "WorldSession.h"
#include "AccountMgr.h"
#include "Opcodes.h"
#include "Config/Config.h"
#include "Chat.h"
#include "Player.h"
#include "PlayerBotAI.h"
#include "Anticheat.h"


class LoginQueryHolder;
class CharacterHandler;

PlayerbotHolder::PlayerbotHolder() : PlayerbotAIBase()
{
    for (uint32 spellId = 0; spellId < sSpellStore.GetNumRows(); spellId++)
        sSpellStore.LookupEntry(spellId);
}

PlayerbotHolder::~PlayerbotHolder()
{
    LogoutAllBots();
}


void PlayerbotHolder::UpdateAIInternal(uint32 elapsed)
{
}

void PlayerbotHolder::UpdateSessions(uint32 elapsed)
{
    for (PlayerBotMap::const_iterator itr = GetPlayerBotsBegin(); itr != GetPlayerBotsEnd(); ++itr)
    {
        Player* const bot = itr->second;
        if (bot->IsBeingTeleported())
        {
            bot->GetPlayerbotAI()->HandleTeleportAck();
        }
        else if (bot->IsInWorld())
        {
            bot->GetSession()->HandleBotPackets();
        }
    }
}

void PlayerbotHolder::LogoutAllBots()
{
    while (true)
    {
        PlayerBotMap::const_iterator itr = GetPlayerBotsBegin();
        if (itr == GetPlayerBotsEnd()) break;
        Player* bot= itr->second;
        LogoutPlayerBot(bot->GetGUID());
    }
	//debug
	//_CrtDumpMemoryLeaks();
}

void PlayerbotHolder::LogoutPlayerBot(uint64 guid)
{
    Player* bot = GetPlayerBot(guid);
    if (bot)
    {
        bot->GetPlayerbotAI()->TellMaster("Goodbye!");
		sPlayerbotDbStore.Save(bot->GetPlayerbotAI());
        //bot->SaveToDB();

        WorldSession * botWorldSessionPtr = bot->GetSession();
        playerBots.erase(guid);    // deletes bot player ptr inside this WorldSession PlayerBotMap
        botWorldSessionPtr->LogoutPlayer(true); // this will delete the bot Player object and PlayerbotAI object
        delete botWorldSessionPtr;  // finally delete the bot's WorldSession
    }
}

Player* PlayerbotHolder::GetPlayerBot(uint64 playerGuid) const
{
    PlayerBotMap::const_iterator it = playerBots.find(playerGuid);
    return (it == playerBots.end()) ? 0 : it->second;
}

void PlayerbotHolder::OnBotLogin(Player * const bot)
{
	PlayerbotAI* ai = new PlayerbotAI(bot);
	bot->SetPlayerbotAI(ai);
	OnBotLoginInternal(bot);

    playerBots[bot->GetGUID()] = bot;

    Player* master = ai->GetMaster();
    if (master)
    {
        ObjectGuid masterGuid = master->GetGUID();
        if (master->GetGroup() &&
            ! master->GetGroup()->IsLeader(masterGuid))
            master->GetGroup()->ChangeLeader(masterGuid);
    }

    Group *group = bot->GetGroup();
    if (group)
    {
        bool groupValid = false;
        Group::MemberSlotList const& slots = group->GetMemberSlots();
        for (Group::MemberSlotList::const_iterator i = slots.begin(); i != slots.end(); ++i)
        {
            ObjectGuid member = i->guid;
            uint32 account = sObjectMgr.GetPlayerAccountIdByGUID(member);
            if (!sPlayerbotAIConfig.IsInRandomAccountList(account))
            {
                groupValid = true;
                break;
            }
        }

        if (!groupValid)
        {
            WorldPacket p;
            string member = bot->GetName();
            p << uint32(PARTY_OP_LEAVE) << member << uint32(0);
            bot->GetSession()->HandleGroupDisbandOpcode(p);
        }
    }

    ai->ResetStrategies();
    ai->TellMaster("Hello!");

	uint32 account = sObjectMgr.GetPlayerAccountIdByGUID(bot->GetGUID());
	if (sPlayerbotAIConfig.IsInRandomAccountList(account))
	{
		sLog.outString("%d/%d Bot %s logged in", playerBots.size(), sRandomPlayerbotMgr.GetMaxAllowedBotCount(), bot->GetName());
		}
	else sLog.outString("Bot %s logged in", bot->GetName());
}


string PlayerbotHolder::ProcessBotCommand(string cmd, ObjectGuid guid, bool admin, uint32 masterAccountId, uint32 masterGuildId)
{
    if (!sPlayerbotAIConfig.enabled || guid.IsEmpty())
        return "bot system is disabled";

    uint32 botAccount = sObjectMgr.GetPlayerAccountIdByGUID(guid);
    bool isRandomBot = sRandomPlayerbotMgr.IsRandomBot(guid);
    bool isRandomAccount = sPlayerbotAIConfig.IsInRandomAccountList(botAccount);
    bool isMasterAccount = (masterAccountId == botAccount);

    if (isRandomAccount && !isRandomBot && !admin)
    {
        Player* bot = sObjectMgr.GetPlayer(guid);
        if (bot->GetGuildId() != masterGuildId)
            return "not in your guild";
    }

    if (!isRandomAccount && !isMasterAccount && !admin)
        return "not in your account";

    if (cmd == "add" || cmd == "login")
    {
        if (sObjectMgr.GetPlayer(guid))
            return "player already logged in";

        AddPlayerBot(guid.GetRawValue(), masterAccountId);
        return "ok";
    }
    else if (cmd == "remove" || cmd == "logout" || cmd == "rm")
    {
        if (!sObjectMgr.GetPlayer(guid))
            return "player is offline";

        if (!GetPlayerBot(guid.GetRawValue()))
            return "not your bot";

        LogoutPlayerBot(guid.GetRawValue());
        return "ok";
    }

    if (admin)
    {
        Player* bot = GetPlayerBot(guid.GetRawValue());
        if (!bot)
            return "bot not found";

        Player* master = bot->GetPlayerbotAI()->GetMaster();
        if (master)
        {
            if (cmd == "init=white" || cmd == "init=common")
            {
                PlayerbotFactory factory(bot, master->getLevel(), ITEM_QUALITY_NORMAL);
                factory.CleanRandomize();
                return "ok";
            }
            else if (cmd == "init=green" || cmd == "init=uncommon")
            {
                PlayerbotFactory factory(bot, master->getLevel(), ITEM_QUALITY_UNCOMMON);
                factory.CleanRandomize();
                return "ok";
            }
            else if (cmd == "init=blue" || cmd == "init=rare")
            {
                PlayerbotFactory factory(bot, master->getLevel(), ITEM_QUALITY_RARE);
                factory.CleanRandomize();
                return "ok";
            }
            else if (cmd == "init=epic" || cmd == "init=purple")
            {
                PlayerbotFactory factory(bot, master->getLevel(), ITEM_QUALITY_EPIC);
                factory.CleanRandomize();
                return "ok";
            }
             else if (cmd == "init=high80")
            {
                PlayerbotFactory factory(bot, 80, ITEM_QUALITY_EPIC);
                factory.CleanBuild();
                return "ok";
            }
        }

        if (cmd == "update")
        {
            PlayerbotFactory factory(bot, bot->getLevel());
            factory.Refresh();
            return "ok";
        }
        else if (cmd == "random")
        {
            sRandomPlayerbotMgr.Randomize(bot);
            return "ok";
        }
        else if (cmd == "distance=none")
        {
            Player* bot = sObjectMgr.GetPlayer(guid);
            bot->SetMinTargetDistance(.0f);
            bot->SetMinMasterDistance(.0f);
            return "ok";
        }
        else if (cmd == "distance=melee")
        {
            Player* bot = sObjectMgr.GetPlayer(guid);
            bot->SetMinTargetDistance(sPlayerbotAIConfig.meleeDistance);
            bot->SetMinMasterDistance(sPlayerbotAIConfig.meleeDistance);
            return "ok";
        }
        else if (cmd == "distance=spell")
        {
            Player* bot = sObjectMgr.GetPlayer(guid);
            bot->SetMinTargetDistance(sPlayerbotAIConfig.spellDistance);
            bot->SetMinMasterDistance(sPlayerbotAIConfig.spellDistance);
            return "ok";
        }
        else if (cmd == "distance=close")
        {
            Player* bot = sObjectMgr.GetPlayer(guid);
            bot->SetMinTargetDistance(sPlayerbotAIConfig.closeDistance);
            bot->SetMinMasterDistance(sPlayerbotAIConfig.closeDistance);
            return "ok";
        }
        else if (cmd == "distance=medium")
        {
            Player* bot = sObjectMgr.GetPlayer(guid);
            bot->SetMinTargetDistance(sPlayerbotAIConfig.mediumDistance);
            bot->SetMinMasterDistance(sPlayerbotAIConfig.mediumDistance);
            return "ok";
        }
        else if (cmd == "distance=far")
        {
            Player* bot = sObjectMgr.GetPlayer(guid);
            bot->SetMinTargetDistance(sPlayerbotAIConfig.farDistance);
            bot->SetMinMasterDistance(sPlayerbotAIConfig.farDistance);
            return "ok";
        }
        else if (cmd == "distance=extreme")
        {
            Player* bot = sObjectMgr.GetPlayer(guid);
            bot->SetMinTargetDistance(sPlayerbotAIConfig.extremeDistance);
            bot->SetMinMasterDistance(sPlayerbotAIConfig.extremeDistance);
            return "ok";
        }
        else if (cmd == "targetdistance=none")
        {
            Player* bot = sObjectMgr.GetPlayer(guid);
            bot->SetMinTargetDistance(.0f);
            return "ok";
        }
        else if (cmd == "targetdistance=melee")
        {
            Player* bot = sObjectMgr.GetPlayer(guid);
            bot->SetMinTargetDistance(sPlayerbotAIConfig.meleeDistance);
            return "ok";
        }
        else if (cmd == "targetdistance=spell")
        {
            Player* bot = sObjectMgr.GetPlayer(guid);
            bot->SetMinTargetDistance(sPlayerbotAIConfig.spellDistance);
            return "ok";
        }
        else if (cmd == "targetdistance=close")
        {
            Player* bot = sObjectMgr.GetPlayer(guid);
            bot->SetMinTargetDistance(sPlayerbotAIConfig.closeDistance);
            return "ok";
        }
        else if (cmd == "targetdistance=medium")
        {
            Player* bot = sObjectMgr.GetPlayer(guid);
            bot->SetMinTargetDistance(sPlayerbotAIConfig.mediumDistance);
            return "ok";
        }
        else if (cmd == "targetdistance=far")
        {
            Player* bot = sObjectMgr.GetPlayer(guid);
            bot->SetMinTargetDistance(sPlayerbotAIConfig.farDistance);
            return "ok";
        }
        else if (cmd == "targetdistance=extreme")
        {
            Player* bot = sObjectMgr.GetPlayer(guid);
            bot->SetMinTargetDistance(sPlayerbotAIConfig.extremeDistance);
            return "ok";
        }
        else if (cmd == "masterdistance=none")
        {
            Player* bot = sObjectMgr.GetPlayer(guid);
            bot->SetMinMasterDistance(.0f);
            return "ok";
        }
        else if (cmd == "masterdistance=melee")
        {
            Player* bot = sObjectMgr.GetPlayer(guid);
            bot->SetMinMasterDistance(sPlayerbotAIConfig.meleeDistance);
            return "ok";
        }
        else if (cmd == "masterdistance=spell")
        {
            Player* bot = sObjectMgr.GetPlayer(guid);
            bot->SetMinMasterDistance(sPlayerbotAIConfig.spellDistance);
            return "ok";
        }
        else if (cmd == "masterdistance=close")
        {
            Player* bot = sObjectMgr.GetPlayer(guid);
            bot->SetMinMasterDistance(sPlayerbotAIConfig.closeDistance);
            return "ok";
        }
        else if (cmd == "masterdistance=medium")
        {
            Player* bot = sObjectMgr.GetPlayer(guid);
            bot->SetMinMasterDistance(sPlayerbotAIConfig.mediumDistance);
            return "ok";
        }
        else if (cmd == "masterdistance=far")
        {
            Player* bot = sObjectMgr.GetPlayer(guid);
            bot->SetMinMasterDistance(sPlayerbotAIConfig.farDistance);
            return "ok";
        }
        else if (cmd == "masterdistance=extreme")
        {
            Player* bot = sObjectMgr.GetPlayer(guid);
            bot->SetMinMasterDistance(sPlayerbotAIConfig.extremeDistance);
            return "ok";
        }
    }

    return "unknown command";
}

bool PlayerbotMgr::HandlePlayerbotMgrCommand(ChatHandler* handler, char const* args)
{
	if (!sPlayerbotAIConfig.enabled)
	{
		handler->PSendSysMessage("|cffff0000Playerbot system is currently disabled!");
        return false;
	}

    WorldSession *m_session = handler->GetSession();

    if (!m_session)
    {
        handler->PSendSysMessage("You may only add bots from an active session");
        return false;
    }

    Player* player = m_session->GetPlayer();
    PlayerbotMgr* mgr = player->GetPlayerbotMgr();
    if (!mgr)
    {
        handler->PSendSysMessage("you cannot control bots yet");
        return false;
    }

    list<string> messages = mgr->HandlePlayerbotCommand(args, player);
    if (messages.empty())
        return true;

    for (list<string>::iterator i = messages.begin(); i != messages.end(); ++i)
    {
        handler->PSendSysMessage(i->c_str());
    }

    return false;
}

list<string> PlayerbotHolder::HandlePlayerbotCommand(char const* args, Player* master)
{
    list<string> messages;


	if (!*args)
	{
		messages.push_back("usage: list or add/init/remove PLAYERNAME");
		messages.push_back("  (OR) .bot lookup [CLASS] (without to see list of classes)");
		return messages;
	}

	char *cmd = strtok((char*)args, " ");
	char *charname = strtok(NULL, " ");

	//thesawolf - display lookup legend
	if ((cmd) && (!charname))
	{
		std::string cmdStr = cmd;
		if (cmdStr == "lookup" || cmdStr == "LOOKUP")
		{
			messages.push_back("Classes Available:");
			messages.push_back("|TInterface\\icons\\INV_Sword_27.png:25:25:0:-1|t Warrior");
			messages.push_back("|TInterface\\icons\\INV_Hammer_01.png:25:25:0:-1|t Paladin");
			messages.push_back("|TInterface\\icons\\INV_Weapon_Bow_07.png:25:25:0:-1|t Hunter");
			messages.push_back("|TInterface\\icons\\INV_ThrowingKnife_04.png:25:25:0:-1|t Rogue");
			messages.push_back("|TInterface\\icons\\INV_Staff_30.png:25:25:0:-1|t Priest");
			messages.push_back("|TInterface\\icons\\inv_jewelry_talisman_04.png:25:25:0:-1|t Shaman");
			messages.push_back("|TInterface\\icons\\INV_staff_30.png:25:25:0:-1|t Mage");
			messages.push_back("|TInterface\\icons\\INV_staff_30.png:25:25:0:-1|t Warlock");
			messages.push_back("|TInterface\\icons\\Ability_Druid_Maul.png:25:25:0:-1|t Druid");
			messages.push_back("(Usage: .bot lookup CLASS)");
			return messages;
		}
	}
	else if (!cmd)
	{
		messages.push_back("usage: list or add/init/remove PLAYERNAME");
		return messages;
		
	}
	
		if (!strcmp(cmd, "list"))
		{
			messages.push_back(ListBots(master));
			return messages;
		}
	
		if (!charname)
		{
			messages.push_back("usage: list or add/init/remove PLAYERNAME");
		return messages;
	}

    std::string cmdStr = cmd;
    std::string charnameStr = charname;


	//thesawolf - lookup routine.. you know ANY of those RANDOM names?
	if (cmdStr == "lookup" || cmdStr == "LOOKUP")
	{
		string bsearch1 = "Looking for bots of class: " + charnameStr + "...";
		messages.push_back(bsearch1);

		uint8 claz = 0;
		string icon = " ";
		if (charnameStr == "warrior" || charnameStr == "Warrior" || charnameStr == "WARRIOR")
		{
			claz = 1;
			icon = "|TInterface\\icons\\INV_Sword_27.png:25:25:0:-1|t ";
		}
		else if (charnameStr == "paladin" || charnameStr == "Paladin" || charnameStr == "PALADIN")
		{
			claz = 2;
			icon = "|TInterface\\icons\\INV_Hammer_01.png:25:25:0:-1|t ";
		}
		else if (charnameStr == "hunter" || charnameStr == "Hunter" || charnameStr == "HUNTER")
		{
			claz = 3;
			icon = "|TInterface\\icons\\INV_Weapon_Bow_07.png:25:25:0:-1|t ";
		}
		else if (charnameStr == "rogue" || charnameStr == "Rogue" || charnameStr == "ROGUE" || charnameStr == "rouge" || charnameStr == "Rouge" || charnameStr == "ROUGE") // for my friends that cannot spell
		{
			claz = 4;
			icon = "|TInterface\\icons\\INV_ThrowingKnife_04.png:25:25:0:-1|t ";
		}
		else if (charnameStr == "priest" || charnameStr == "Priest" || charnameStr == "PRIEST")
		{
			claz = 5;
			icon = "|TInterface\\icons\\INV_Staff_30.png:25:25:0:-1|t ";
		}
		else if (charnameStr == "shaman" || charnameStr == "Shaman" || charnameStr == "SHAMAN")
		{
			claz = 7;
			icon = "|TInterface\\icons\\inv_jewelry_talisman_04.png:25:25:0:-1|t ";
		}
		else if (charnameStr == "mage" || charnameStr == "Mage" || charnameStr == "MAGE")
		{
			claz = 8;
			icon = "|TInterface\\icons\\INV_staff_30.png:25:25:0:-1|t ";
		}
		else if (charnameStr == "warlock" || charnameStr == "Warlock" || charnameStr == "WARLOCK")
		{
			claz = 9;
			icon = "|TInterface\\icons\\INV_staff_30.png:25:25:0:-1|t ";
		}
		else if (charnameStr == "druid" || charnameStr == "Druid" || charnameStr == "DRUID")
		{
			claz = 11;
			icon = "|TInterface\\icons\\Ability_Druid_Maul.png:25:25:0:-1|t ";
		}
		else
		{
			messages.push_back("Error: Invalid Class. Try again.");
			return messages;
		}

		QueryResult* lresults = CharacterDatabase.PQuery("SELECT * FROM characters WHERE class = '%u'", claz);
		if (lresults)
		{
			do
			{
				Field* fields = lresults->Fetch();
				string bName = fields[2].GetString();
				uint8 bRace = fields[3].GetUInt8();
				string cRace = " ";
				switch (bRace)
				{
				case 1: cRace = "Human";	break;
				case 2: cRace = "Orc";		break;
				case 3: cRace = "Dwarf";	break;
				case 4: cRace = "Nightelf";	break;
				case 5: cRace = "Undead";	break;
				case 6: cRace = "Tauren";	break;
				case 7: cRace = "Gnome";	break;
				case 8: cRace = "Troll";	break;
				case 10: cRace = "Bloodelf";	break;
				case 11: cRace = "Draenei";	break;
				}
				bool bGender = fields[5].GetBool();
				string cGender = "";
				if (bGender == 0)
					cGender = "Male";
				else
					cGender = "Female";
				bool bOnline = fields[25].GetBool();
				string cOnline = "";
				if (bOnline == 0)
					cOnline = "|cff00ff00Available|r";
				else
					cOnline = "|cffff0000Not Available|r";
				string bList = icon + "|TInterface\\icons\\Achievement_Character_" + cRace + "_" + cGender + ".png:25:25:0:-1|t " + bName + " - " + cRace + " " + cGender + " [" + cOnline + "]";
				messages.push_back(bList);

			} while (lresults->NextRow());
		}
		else
		{
			messages.push_back("Error: Listing class bots. Try again.");
			messages.push_back("Usage: .bot lookup (to see list of classes)");
			return messages;
		}
		messages.push_back("(Usage: .bot add PLAYERNAME)");
		return messages;
	}

    set<string> bots;
    if (charnameStr == "*" && master)
    {
        Group* group = master->GetGroup();
        if (!group)
        {
            messages.push_back("you must be in group");
            return messages;
        }

        Group::MemberSlotList slots = group->GetMemberSlots();
        for (Group::member_citerator i = slots.begin(); i != slots.end(); i++)
        {
			ObjectGuid member = i->guid;

			if (member.GetRawValue() == master->GetGUID())
				continue;

			string bot;
			if (sObjectMgr.GetPlayerNameByGUID(member, bot))
			    bots.insert(bot);
        }
    }

    if (charnameStr == "!" && master && master->GetSession()->GetSecurity() > SEC_GAMEMASTER)
    {
        for (PlayerBotMap::const_iterator i = GetPlayerBotsBegin(); i != GetPlayerBotsEnd(); ++i)
        {
            Player* bot = i->second;
            if (bot && bot->IsInWorld())
                bots.insert(bot->GetName());
        }
    }

    vector<string> chars = split(charnameStr, ',');
    for (vector<string>::iterator i = chars.begin(); i != chars.end(); i++)
    {
        string s = *i;

        uint32 accountId = GetAccountId(s);
        if (!accountId)
        {
            bots.insert(s);
            continue;
        }

        QueryResult* results = CharacterDatabase.PQuery(
            "SELECT name FROM characters WHERE account = '%u'",
            accountId);
        if (results)
        {
            do
            {
                Field* fields = results->Fetch();
                string charName = fields[0].GetString();
                bots.insert(charName);
            } while (results->NextRow());
        }
	}

    for (set<string>::iterator i = bots.begin(); i != bots.end(); ++i)
    {
        string bot = *i;
        ostringstream out;
        out << cmdStr << ": " << bot << " - ";

        ObjectGuid member = sObjectMgr.GetPlayerGuidByName(bot);
        if (!member)
        {
            out << "character not found";
        }
        else if (master && member.GetRawValue() != master->GetGUID())
        {
            out << ProcessBotCommand(cmdStr, member,
                    master->GetSession()->GetSecurity() >= SEC_GAMEMASTER,
                    master->GetSession()->GetAccountId(),
                    master->GetGuildId());
        }
        else if (!master)
        {
            out << ProcessBotCommand(cmdStr, member, true, -1, -1);
        }

        messages.push_back(out.str());
    }

    return messages;
}

uint32 PlayerbotHolder::GetAccountId(string name)
{
    uint32 accountId = 0;

    QueryResult* results = LoginDatabase.PQuery("SELECT id FROM account WHERE username = '%s'", name.c_str());
    if(results)
    {
        Field* fields = results->Fetch();
        accountId = fields[0].GetUInt32();
    }

    return accountId;
}

string PlayerbotHolder::ListBots(Player* master)
{
	set<string> bots;
	map<uint8, string> classNames;
	classNames[CLASS_DRUID] = "Druid";
	classNames[CLASS_HUNTER] = "Hunter";
	classNames[CLASS_MAGE] = "Mage";
	classNames[CLASS_PALADIN] = "Paladin";
	classNames[CLASS_PRIEST] = "Priest";
	classNames[CLASS_ROGUE] = "Rogue";
	classNames[CLASS_SHAMAN] = "Shaman";
	classNames[CLASS_WARLOCK] = "Warlock";
	classNames[CLASS_WARRIOR] = "Warrior";

	map<string, string> online;
	list<string> names;
	map<string, string> classes;

	for (PlayerBotMap::const_iterator it = GetPlayerBotsBegin(); it != GetPlayerBotsEnd(); ++it)
	{
		Player* const bot = it->second;
		string name = bot->GetName();
		bots.insert(name);

		names.push_back(name);
		online[name] = "+";
		classes[name] = classNames[bot->getClass()];
	}

	if (master)
	{
		QueryResult* results = CharacterDatabase.PQuery("SELECT class,name FROM characters where account = '%u'",
			master->GetSession()->GetAccountId());
		if (results != NULL)
		{
			do
			{
				Field* fields = results->Fetch();
				uint8 cls = fields[0].GetUInt8();
				string name = fields[1].GetString();
				if (bots.find(name) == bots.end() && name != master->GetSession()->GetPlayerName())
				{
					names.push_back(name);
					online[name] = "-";
					classes[name] = classNames[cls];
				}
			} while (results->NextRow());
			delete results;
		}
	}

	names.sort();

	ostringstream out;
	bool first = true;
	out << "Bot roster: ";
	for (list<string>::iterator i = names.begin(); i != names.end(); ++i)
	{
		if (first) first = false; else out << ", ";
		string name = *i;
		out << online[name] << name << " " << classes[name];
	}

	return out.str();
}

PlayerbotMgr::PlayerbotMgr(Player* const master) : PlayerbotHolder(),  master(master)
{
}

PlayerbotMgr::~PlayerbotMgr()
{
}

void PlayerbotMgr::UpdateAIInternal(uint32 elapsed)
{
    SetNextCheckDelay(sPlayerbotAIConfig.reactDelay);
}

void PlayerbotMgr::HandleCommand(uint32 type, const string& text)
{
    Player *master = GetMaster();
    if (!master)
        return;

    for (PlayerBotMap::const_iterator it = GetPlayerBotsBegin(); it != GetPlayerBotsEnd(); ++it)
    {
        Player* const bot = it->second;
        bot->GetPlayerbotAI()->HandleCommand(type, text, *master);
    }

    for (PlayerBotMap::const_iterator it = sRandomPlayerbotMgr.GetPlayerBotsBegin(); it != sRandomPlayerbotMgr.GetPlayerBotsEnd(); ++it)
    {
        Player* const bot = it->second;
        if (bot->GetPlayerbotAI()->GetMaster() == master)
            bot->GetPlayerbotAI()->HandleCommand(type, text, *master);
    }
}

void PlayerbotMgr::HandleMasterIncomingPacket(const WorldPacket& packet)
{
    for (PlayerBotMap::const_iterator it = GetPlayerBotsBegin(); it != GetPlayerBotsEnd(); ++it)
    {
        Player* const bot = it->second;
        bot->GetPlayerbotAI()->HandleMasterIncomingPacket(packet);
    }

    for (PlayerBotMap::const_iterator it = sRandomPlayerbotMgr.GetPlayerBotsBegin(); it != sRandomPlayerbotMgr.GetPlayerBotsEnd(); ++it)
    {
        Player* const bot = it->second;
        if (bot->GetPlayerbotAI()->GetMaster() == GetMaster())
            bot->GetPlayerbotAI()->HandleMasterIncomingPacket(packet);
    }

    switch (packet.GetOpcode())
    {
        // if master is logging out, log out all bots
        case CMSG_LOGOUT_REQUEST:
        {
            LogoutAllBots();
            return;
        }
    }
}
void PlayerbotMgr::HandleMasterOutgoingPacket(const WorldPacket& packet)
{
    for (PlayerBotMap::const_iterator it = GetPlayerBotsBegin(); it != GetPlayerBotsEnd(); ++it)
    {
        Player* const bot = it->second;
        bot->GetPlayerbotAI()->HandleMasterOutgoingPacket(packet);
    }

    for (PlayerBotMap::const_iterator it = sRandomPlayerbotMgr.GetPlayerBotsBegin(); it != sRandomPlayerbotMgr.GetPlayerBotsEnd(); ++it)
    {
        Player* const bot = it->second;
        if (bot->GetPlayerbotAI()->GetMaster() == GetMaster())
            bot->GetPlayerbotAI()->HandleMasterOutgoingPacket(packet);
    }
}

void PlayerbotMgr::SaveToDB()
{
    for (PlayerBotMap::const_iterator it = GetPlayerBotsBegin(); it != GetPlayerBotsEnd(); ++it)
    {
        Player* const bot = it->second;
        bot->SaveToDB();
    }
    for (PlayerBotMap::const_iterator it = sRandomPlayerbotMgr.GetPlayerBotsBegin(); it != sRandomPlayerbotMgr.GetPlayerBotsEnd(); ++it)
    {
        Player* const bot = it->second;
        if (bot->GetPlayerbotAI()->GetMaster() == GetMaster())
            bot->SaveToDB();
    }
}

void PlayerbotMgr::OnBotLoginInternal(Player * const bot)
{
    bot->GetPlayerbotAI()->SetMaster(master);
    bot->GetPlayerbotAI()->ResetStrategies();
}

INSTANTIATE_SINGLETON_1(EventBotMgr);


EventBotMgr::EventBotMgr()
{
    totalChance = 0;
    _maxAccountId = 0;

    /* Config */
    confMinBots         = 4;
    confMaxBots         = 8;
    confBotsRefresh     = 30000;
    confUpdateDiff      = 10000;
    enable              = false;
    confDebug           = false;
    forceLogoutDelay    = true;

    /* Time */
    m_elapsedTime = 0;
    m_lastBotsRefresh = 0;
    m_lastUpdate = 0;
}

EventBotMgr::~EventBotMgr()
{

}

void EventBotMgr::LoadConfig()
{
    enable              = sConfig.GetBoolDefault("PlayerBot.Enable", false);
    confMinBots         = sConfig.GetIntDefault("PlayerBot.MinBots", 3);
    confMaxBots         = sConfig.GetIntDefault("PlayerBot.MaxBots", 10);
    confBotsRefresh     = sConfig.GetIntDefault("PlayerBot.Refresh", 60000);
    confDebug           = sConfig.GetBoolDefault("PlayerBot.Debug", false);
    confUpdateDiff      = sConfig.GetIntDefault("PlayerBot.UpdateMs", 10000);
    forceLogoutDelay    = sConfig.GetBoolDefault("PlayerBot.ForceLogoutDelay", true);
    if (!forceLogoutDelay)
        m_tempBots.clear();
}

void EventBotMgr::load()
{
    // 1- clean
    deleteAll();
    m_bots.clear();
    m_tempBots.clear();
    totalChance = 0;

    // 2- Configuration
    LoadConfig();

    // 3- Load usable account ID
    QueryResult *result = LoginDatabase.PQuery(
                              "SELECT MAX(id)"
                              " FROM account");
    if (!result)
    {
        sLog.outError("Playerbot: unable to load max account id.");
        return;
    }
    Field *fields = result->Fetch();
    _maxAccountId = fields[0].GetUInt32() + 10000;
    delete result;

    // 4- LoadFromDB
    sLog.outString(">> [PlayerBotMgr] Loading Bots ...");
    result = CharacterDatabase.PQuery(
                 "SELECT char_guid, chance, ai"
                 " FROM playerbot");
    if (!result)
        sLog.outString("DB playerbot vide.");
    else
    {
        do
        {
            fields = result->Fetch();
            uint32 guid = fields[0].GetUInt32();
            uint32 acc = GenBotAccountId();
            uint32 chance = fields[1].GetUInt32();

            EventBotEntry* entry = new EventBotEntry(guid,
                    acc, chance);
            entry->ai = CreateEventBotAI(fields[2].GetCppString());
            entry->ai->botEntry = entry;
            if (!sObjectMgr.GetPlayerNameByGUID(guid, entry->name))
                entry->name = "<Unknown>";
            entry->ai->OnBotEntryLoad(entry);
            m_bots[entry->playerGUID] = entry;
            totalChance += chance;
        }
        while (result->NextRow());
        delete result;
        sLog.outString("%u bots charges", m_bots.size());
    }

    // 5- Check config/DB
    if (confMinBots >= m_bots.size() && m_bots.size() != 0)
        confMinBots = m_bots.size() - 1;
    if (confMaxBots > m_bots.size())
        confMaxBots = m_bots.size();
    if (confMaxBots <= confMinBots)
        confMaxBots = confMinBots + 1;

    // 6- Start initial bots
    if (enable)
    {
        for (uint32 i = 0; i < confMinBots; i++)
            addRandomBot();
    }

    //7 - Remplir les stats
    m_stats.confMaxOnline = confMaxBots;
    m_stats.confMinOnline = confMinBots;
    m_stats.totalBots = m_bots.size();
    m_stats.confBotsRefresh = confBotsRefresh;
    m_stats.confUpdateDiff = confUpdateDiff;

    //8- Afficher les stats si débug
    if (confDebug)
    {
        sLog.outString("[PlayerBotMgr] Between %u and %u bots online", confMinBots, confMaxBots);
        sLog.outString("[PlayerBotMgr] %u now loading", m_stats.loadingCount);
    }
}

void EventBotMgr::deleteAll()
{
    m_stats.onlineCount = 0;
    m_stats.loadingCount = 0;

    std::map<uint32, EventBotEntry*>::iterator i;
    for (i = m_bots.begin(); i != m_bots.end(); i++)
    {
        if (i->second->state != PB_STATE_OFFLINE)
        {
            OnBotLogout(i->second);
            totalChance += i->second->chance;
        }
    }
    m_tempBots.clear();

    if (confDebug)
        sLog.outString("[PlayerBotMgr] Deleting all bots [OK]");
}

void EventBotMgr::OnBotLogin(EventBotEntry *e)
{
    e->state = PB_STATE_ONLINE;
    if (confDebug)
        sLog.outString("[PlayerBot][Login]  '%s' GUID:%u Acc:%u", e->name.c_str(), e->playerGUID, e->accountId);
}
void EventBotMgr::OnBotLogout(EventBotEntry *e)
{
    e->state = PB_STATE_OFFLINE;
    if (confDebug)
        sLog.outString("[PlayerBot][Logout] '%s' GUID:%u Acc:%u", e->name.c_str(), e->playerGUID, e->accountId);
}

void EventBotMgr::OnPlayerInWorld(Player* player)
{
    if (EventBotEntry* e = player->GetSession()->GetBot())
    {
        player->setAI(e->ai);
        e->ai->SetPlayer(player);
        e->ai->OnPlayerLogin();
    }
}

void EventBotMgr::update(uint32 diff)
{
    // Bots temporaires
    std::map<uint32, uint32>::iterator it;
    for (it = m_tempBots.begin(); it != m_tempBots.end(); ++it)
    {
        if (it->second < diff)
            it->second = 0;
        else
            it->second -= diff;
    }
    it = m_tempBots.begin();
    while (it != m_tempBots.end())
    {
        if (!it->second)
        {
            // Update des "chatBot" aussi.
            for (std::map<uint32, EventBotEntry*>::iterator iter = m_bots.begin(); iter != m_bots.end(); ++iter)
                if (iter->second->accountId == it->first)
                {
                    iter->second->state = PB_STATE_OFFLINE; // Will get logged out at next WorldSession::Update call
                    m_bots.erase(iter);
                    break;
                }
            m_tempBots.erase(it);
            it = m_tempBots.begin();
        }
        else
            ++it;
    }

    m_elapsedTime += diff;
    if (!((m_elapsedTime - m_lastUpdate) > confUpdateDiff))
        return; //Pas besoin d'update
    m_lastUpdate = m_elapsedTime;

    /* Connection des bots en attente */
    std::map<uint32, EventBotEntry*>::iterator iter;
    for (iter = m_bots.begin(); iter != m_bots.end(); ++iter)
    {
        if (!enable && !iter->second->customBot)
            continue;
        if (iter->second->state != PB_STATE_LOADING)
            continue;

        WorldSession* sess = sWorld.FindSession(iter->second->accountId);

        if (!sess)
        {
            // This may happen : just wait for the World to add the session.
            //sLog.outString("/!\\ PlayerBot in queue but Session not in World ... Account : %u, GUID : %u", iter->second->accountId, iter->second->playerGUID);
            continue;
        }
        if (iter->second->ai->OnSessionLoaded(iter->second, sess))
        {
            OnBotLogin(iter->second);
            m_stats.loadingCount--;

            if (iter->second->isChatBot)
                m_stats.onlineChat++;
            else
                m_stats.onlineCount++;
        }
        else
            sLog.outError("PLAYERBOT: Unable to load session id %u", iter->second->accountId);
    }
    if (!enable)
        return;
    uint32 updatesCount = (m_elapsedTime - m_lastBotsRefresh) / confBotsRefresh;
    for (uint32 i = 0; i < updatesCount; ++i)
    {
        addOrRemoveBot();
        m_lastBotsRefresh += confBotsRefresh;
    }
}

/*
Toutes les X minutes, ajoute ou enleve un bot.
*/
bool EventBotMgr::addOrRemoveBot()
{
    uint32 alea = urand(confMinBots, confMaxBots);
    /*
    10 --- --- --- --- --- --- --- --- --- --- 20 bots
                NumActuel
    [alea ici : remove    ][    ici, add    ]
    */
    if (alea > m_stats.onlineCount)
        return addRandomBot();
    else
        return deleteRandomBot();

}

bool EventBotMgr::addBot(EventBotAI* ai)
{
    // Find a correct accountid ?
	EventBotEntry* e = new EventBotEntry();
    e->ai = ai;
    e->accountId = GenBotAccountId();
    e->playerGUID = sObjectMgr.GeneratePlayerLowGuid();
    e->customBot = true;
    ai->botEntry = e;
    m_bots[e->playerGUID] = e;
    addBot(e->playerGUID, false);
    return true;
}

bool EventBotMgr::addBot(uint32 playerGUID, bool chatBot)
{
    uint32 accountId = 0;
	EventBotEntry *e = NULL;
    std::map<uint32, EventBotEntry*>::iterator iter = m_bots.find(playerGUID);
    if (iter == m_bots.end())
        accountId = sObjectMgr.GetPlayerAccountIdByGUID(playerGUID);
    else
        accountId = iter->second->accountId;
    if (!accountId)
    {
        DETAIL_LOG("Compte du joueur %u introuvable ...", playerGUID);
        return false;
    }

    if (iter != m_bots.end())
        e = iter->second;
    else
    {
        DETAIL_LOG("Adding temporary PlayerBot.");
        e = new EventBotEntry();
        e->state        = PB_STATE_LOADING;
        e->playerGUID   = playerGUID;
        e->chance       = 10;
        e->accountId    = accountId;
        e->isChatBot    = chatBot;
        e->ai           = new EventBotAI(NULL);
        m_bots[playerGUID] = e;
    }

    e->state = PB_STATE_LOADING;
    WorldSession *session = new WorldSession(accountId, NULL, sAccountMgr.GetSecurity(accountId), 0, LOCALE_enUS);
    session->SetBot(e);
    // "It's not because you are a bot that you are allowed cheat!"
    sAnticheatLib->SessionAdded(session);
    sWorld.AddSession(session);
    m_stats.loadingCount++;
    if (chatBot)
        AddTempBot(accountId, 20000);
    return true;
}

bool EventBotMgr::addRandomBot()
{
    uint32 alea = urand(0, totalChance);
    std::map<uint32, EventBotEntry*>::iterator it;
    bool done = false;
    for (it = m_bots.begin(); it != m_bots.end() && !done; it++)
    {
        if (it->second->state != PB_STATE_OFFLINE)
            continue;
        if (it->second->customBot)
            continue;
        uint32 chance = it->second->chance;

        if (chance >= alea)
        {
            addBot(it->first);
            done = true;
        }
        alea -= chance;
    }
    return done;
}

void EventBotMgr::AddTempBot(uint32 account, uint32 time)
{
    m_tempBots[account] = time;
}

void EventBotMgr::RefreshTempBot(uint32 account)
{
    if (m_tempBots.find(account) != m_tempBots.end())
    {
        uint32& delay = m_tempBots[account];
        if (delay < 1000)
            delay = 1000;
    }
}

bool EventBotMgr::deleteBot(uint32 playerGUID)
{
    std::map<uint32, EventBotEntry*>::iterator iter = m_bots.find(playerGUID);
    if (iter == m_bots.end())
        return false;
    uint32 accountId = iter->second->accountId;

    if (iter->second->state == PB_STATE_LOADING)
        m_stats.loadingCount--;
    else if (iter->second->state == PB_STATE_ONLINE)
        m_stats.onlineCount--;

    OnBotLogout(iter->second);
    return true;
}

bool EventBotMgr::deleteRandomBot()
{
    if (m_stats.onlineCount < 1)
        return false;
    uint32 idDelete = urand(0, m_stats.onlineCount);
    uint32 onlinePassed = 0;
    std::map<uint32, EventBotEntry*>::iterator iter;
    for (iter = m_bots.begin(); iter != m_bots.end(); iter++)
    {
        if (!iter->second->customBot && !iter->second->isChatBot && iter->second->state == PB_STATE_ONLINE)
        {
            onlinePassed++;
            if (onlinePassed == idDelete)
            {
                OnBotLogout(iter->second);
                m_stats.onlineCount--;
                return true;
            }
        }
    }
    return false;
}

bool EventBotMgr::ForceAccountConnection(WorldSession* sess)
{
    if (sess->GetBot())
        return sess->GetBot()->state != PB_STATE_OFFLINE;

    // Bots temporaires
    if (m_tempBots.find(sess->GetAccountId()) != m_tempBots.end())
        return true;

    return false;
}

bool EventBotMgr::IsPermanentBot(uint32 playerGUID)
{
    std::map<uint32, EventBotEntry*>::iterator iter = m_bots.find(playerGUID);
    if (iter != m_bots.end())
        return true;
    return false;
}

bool EventBotMgr::IsChatBot(uint32 playerGuid)
{
    std::map<uint32, EventBotEntry*>::iterator iter = m_bots.find(playerGuid);
    if (iter != m_bots.end() && iter->second->isChatBot)
        return true;
    return false;
}

void EventBotMgr::addAllBots()
{
    std::map<uint32, EventBotEntry*>::iterator it;
    for (it = m_bots.begin(); it != m_bots.end(); it++)
    {
        if (!it->second->isChatBot && it->second->state == PB_STATE_OFFLINE)
            addBot(it->first);
    }
}

bool ChatHandler::HandleBotReloadCommand(char * args)
{
    sEventBotMgr.load();
    SendSysMessage("PlayerBot recharge");
    return true;
}

bool ChatHandler::HandleBotAddRandomCommand(char * args)
{
    uint32 count = 1;
    char* sCount = strtok((char*)args, " ");
    if (sCount)
        count = uint32(atoi(sCount));
    for (uint32 i = 0; i < count; ++i)
        sEventBotMgr.addRandomBot();
    PSendSysMessage("%u bots added", count);
    return true;
}

bool ChatHandler::HandleBotStopCommand(char * args)
{
    sEventBotMgr.deleteAll();
    SendSysMessage("Tous les bots ont ete decharges.");
    return true;
}

bool ChatHandler::HandleBotAddAllCommand(char * args)
{
    sEventBotMgr.addAllBots();
    SendSysMessage("Tous les bots ont ete connecte");
    return true;
}

bool ChatHandler::HandleBotAddCommand(char* args)
{
    uint32 guid = 0;
    char *charname = NULL;
    if (*args)
    {
        charname = strtok((char*)args, " ");
        if (charname && strcmp(charname, "") == 0)
            return false;

        guid = sObjectMgr.GetPlayerGuidByName(charname).GetCounter();
        if (!guid)
        {
            PSendSysMessage("Player not found : '%s'", charname);
            SetSentErrorMessage(true);
            return false;
        }
    }
    if (!guid || !sEventBotMgr.addBot(guid))
    {
        SendSysMessage("[PlayerBotMgr] Unable to load bot.");
        return true;
    }
    PSendSysMessage("[PlayerBotMgr] Bot added : '%s', GUID=%u", charname ? charname : "NULL", guid);
    return true;
}

bool ChatHandler::HandleBotDeleteCommand(char * args)
{
    char *charname = strtok((char*)args, " ");

    if (!charname || strcmp(charname, "") == 0)
    {
        SendSysMessage("Syntaxe : $nomDuJoueur");
        SetSentErrorMessage(true);
        return false;
    }
    uint32 lowGuid = sObjectMgr.GetPlayerGuidByName(charname).GetCounter();
    if (!lowGuid)
    {
        PSendSysMessage("Unable to find player: '%s'", charname);
        SetSentErrorMessage(true);
        return false;
    }
    if (sEventBotMgr.deleteBot(lowGuid))
    {
        PSendSysMessage("Bot %s (GUID:%u) disconnected.", charname, lowGuid);
        return true;
    }
    else
    {
        PSendSysMessage("Bot %s (GUID:%u) : unable to disconnect.", charname, lowGuid);
        SetSentErrorMessage(true);
        return false;
    }
}

bool ChatHandler::HandleBotInfoCommand(char * args)
{
    uint32 online = sWorld.GetActiveSessionCount();

    PlayerBotStats stats = sEventBotMgr.GetStats();
    SendSysMessage("-- PlayerBot stats --");
    PSendSysMessage("Min:%u Max:%u Total:%u", stats.confMinOnline, stats.confMaxOnline, stats.totalBots);
    PSendSysMessage("Loading : %u, Online : %u, Chat : %u", stats.loadingCount, stats.onlineCount, stats.onlineChat);
    PSendSysMessage("%up + %ub = %u",
                    (online - stats.onlineCount), stats.onlineCount, online);
    return true;
}

bool ChatHandler::HandleBotStartCommand(char * args)
{
    sEventBotMgr.Start();
    return true;
}
