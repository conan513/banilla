#include "../pchdef.h"
#include "playerbot.h"
#include "AiFactory.h"
#include "strategy/Engine.h"

#include "strategy/priest/PriestAiObjectContext.h"
#include "strategy/mage/MageAiObjectContext.h"
#include "strategy/warlock/WarlockAiObjectContext.h"
#include "strategy/warrior/WarriorAiObjectContext.h"
#include "strategy/shaman/ShamanAiObjectContext.h"
#include "strategy/paladin/PaladinAiObjectContext.h"
#include "strategy/druid/DruidAiObjectContext.h"
#include "strategy/hunter/HunterAiObjectContext.h"
#include "strategy/rogue/RogueAiObjectContext.h"
#include "../../game/Player.h"
#include "PlayerbotAIConfig.h"
#include "RandomPlayerbotMgr.h"


AiObjectContext* AiFactory::createAiObjectContext(Player* player, PlayerbotAI* ai)
{
    switch (player->getClass())
    {
    case CLASS_PRIEST:
        return new PriestAiObjectContext(ai);
        break;
    case CLASS_MAGE:
        return new MageAiObjectContext(ai);
        break;
    case CLASS_WARLOCK:
        return new WarlockAiObjectContext(ai);
        break;
    case CLASS_WARRIOR:
        return new WarriorAiObjectContext(ai);
        break;
    case CLASS_SHAMAN:
        return new ShamanAiObjectContext(ai);
        break;
    case CLASS_PALADIN:
        return new PaladinAiObjectContext(ai);
        break;
    case CLASS_DRUID:
        return new DruidAiObjectContext(ai);
        break;
    case CLASS_HUNTER:
        return new HunterAiObjectContext(ai);
        break;
    case CLASS_ROGUE:
        return new RogueAiObjectContext(ai);
        break;
    }
    return new AiObjectContext(ai);
}

int AiFactory::GetPlayerSpecTab(Player* bot)
{
	map<uint32, int32> tabs = GetPlayerSpecTabs(bot);

	int tab = -1, max = 0;
	for (uint32 i = 0; i < uint32(3); i++)
	{
		if (tab == -1 || max < tabs[i])
		{
			tab = i;
			max = tabs[i];
		}
	}

	return tab;
}

map<uint32, int32> AiFactory::GetPlayerSpecTabs(Player* bot)
{
	map<uint32, int32> tabs;
	for (uint32 i = 0; i < uint32(3); i++)
		tabs[i] = 0;

	uint32 classMask = bot->getClassMask();
	for (uint32 i = 0; i < sTalentStore.GetNumRows(); ++i)
	{
		TalentEntry const *talentInfo = sTalentStore.LookupEntry(i);
		if (!talentInfo)
			continue;

		TalentTabEntry const *talentTabInfo = sTalentTabStore.LookupEntry(talentInfo->TalentTab);
		if (!talentTabInfo)
			continue;

		if ((classMask & talentTabInfo->ClassMask) == 0)
			continue;

		int maxRank = 0;
		for (int rank = MAX_TALENT_RANK - 1; rank >= 0; --rank)
		{
			if (!talentInfo->RankID[rank])
				continue;

			uint32 spellid = talentInfo->RankID[rank];
			if (spellid && bot->HasSpell(spellid))
				maxRank = rank + 1;

		}
		tabs[talentTabInfo->tabpage] += maxRank;
	}

	return tabs;
}

void AiFactory::AddDefaultCombatStrategies(Player* player, PlayerbotAI* const facade, Engine* engine)
{
    int tab = GetPlayerSpecTab(player);

	if (player->InBattleGround() && player->GetBattleGroundTypeId() == BATTLEGROUND_WS)
	{
		engine->addStrategies("grind", "warsong", "tank", "dps", "heal", "racials", "chat", "default", "aoe", "potions", "cast time", "conserve mana", "duel", "pvp", NULL);
		}
	else {
		if (player->getClass() == CLASS_WARRIOR || player->getClass() == CLASS_ROGUE)
			engine->addStrategies("attack weak", "racials", "chat", "default", "aoe", "potions", "cast time", "duel", "pvp", NULL);
		else
			engine->addStrategies("attack weak", "racials", "chat", "default", "aoe", "potions", "cast time", "conserve mana", "duel", "pvp", NULL);

//		engine->addStrategies("tank", "dps", "heal", "racials", "chat", "default", "aoe", "potions", "cast time", "conserve mana", "duel", "pvp", NULL);
		
	}
	
	
    switch (player->getClass())
    {
        case CLASS_PRIEST:
            if (tab == 2)
            {
                engine->addStrategies("dps", "threat", NULL);
                if (player->getLevel() > 19)
                    engine->addStrategy("dps debuff");
            }
            else if (tab == 1)
                engine->addStrategies("holy","holy dps",NULL);
            else
                engine->addStrategy("heal");

            engine->addStrategies("flee", "cure", NULL);
            break;
        case CLASS_MAGE:
            if (tab == 0)
                engine->addStrategies("arcane", "arcane aoe", "threat", "bmana", NULL);
            else if (tab == 1)
                engine->addStrategies("fire", "fire aoe", "threat", "bdps", NULL);
            else
                engine->addStrategies("frost", "frost aoe", "threat", "bdps", NULL);

			engine->addStrategies("flee", "cure", NULL);
            break;
        case CLASS_WARRIOR:
            if (tab == 2)
                engine->addStrategies("tank", "tank aoe", NULL);
            else if (tab == 1)
                engine->addStrategies("fury", "dps", "threat", NULL);
            else
                engine->addStrategies("arms", "dps", "threat", NULL);
            break;
        case CLASS_SHAMAN:
            if (tab == 0)
                engine->addStrategies("caster", "caster aoe", "bmana", "totems", "threat", "flee", "cure", NULL);
            else if (tab == 2)
                engine->addStrategies("heal", "bmana", "flee", "totems", "cure", NULL);
            else
                engine->addStrategies("dps", "melee aoe", "bdps", "threat", "totems", "cure", NULL);
            break;
        case CLASS_PALADIN:
            if (tab == 0)
                if (player->getLevel() > 59)
                    engine->addStrategies("heal", "bmana", "threat", "flee", "cure", NULL);
                else
                    engine->addStrategies("melee heal", "bmana", "cure", "threat", NULL);
            else if (tab == 1)
                engine->addStrategies("tank", "tank aoe", "barmor", "cure", "bthreat", NULL);
            else
                engine->addStrategies("dps", "bdps", "cure", "threat", NULL);
            break;
        case CLASS_DRUID:
            if (tab == 0)
            {
                engine->addStrategies("caster", "caster aoe", "threat", "flee", "cure", NULL);
                if (player->getLevel() > 19)
                    engine->addStrategy("caster debuff");
            }
            else if (tab == 2)
                engine->addStrategies("heal", "flee", "cure", NULL);
            else
                engine->addStrategies("bear", "tank aoe", NULL);
            break;
        case CLASS_HUNTER:
            engine->addStrategies("dps", "bdps", "threat", "flee", NULL);
            if (player->getLevel() > 19)
                engine->addStrategy("dps debuff");
            break;
        case CLASS_ROGUE:
            if (tab == 1)
                engine->addStrategies("dps", "sword", "threat", NULL);
            else
                engine->addStrategies("dps", "dagger", "threat", NULL);
            break;
        case CLASS_WARLOCK:
            if (tab == 0)
            {
                engine->addStrategies("dps", "threat", "dps debuff", NULL);
            }
            else if (tab == 1)
                engine->addStrategies("tank", "threat", "dps debuff", NULL);
            else
            {
                engine->addStrategies("fire", "threat", "debuff", NULL);
            }

            engine->addStrategy("flee");
            break;
    }

	if (sRandomPlayerbotMgr.IsRandomBot(player))
	{
		if (!player->GetGroup())
		{
			engine->ChangeStrategy(sPlayerbotAIConfig.randomBotCombatStrategies);
			if (player->getClass() == CLASS_DRUID && player->getLevel() < 20)
			{
				engine->addStrategies("bear", NULL);
			}
		}
	}
	else
	{
		engine->ChangeStrategy(sPlayerbotAIConfig.combatStrategies);
	}
}

Engine* AiFactory::createCombatEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext) {
	Engine* engine = new Engine(facade, AiObjectContext);
    AddDefaultCombatStrategies(player, facade, engine);
    return engine;
}

Engine* AiFactory::createMobileEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext) {
	Engine* engine = new Engine(facade, AiObjectContext);
    AddDefaultMobileStrategies(player, facade, engine);
    return engine;
}

void AiFactory::AddDefaultNonCombatStrategies(Player* player, PlayerbotAI* const facade, Engine* nonCombatEngine)
{
    int tab = GetPlayerSpecTab(player);

    switch (player->getClass()){       
        case CLASS_PALADIN:
			if (tab == 1)
				nonCombatEngine->addStrategy("bthreat");
			else
				nonCombatEngine->addStrategy("bdps");
			break;
        case CLASS_HUNTER:
			nonCombatEngine->addStrategy("bdps");
			break;
        case CLASS_SHAMAN:
			if (tab == 0 || tab == 2)
				 nonCombatEngine->addStrategy("bmana");
			else
				 nonCombatEngine->addStrategy("bdps");
        case CLASS_ROGUE:
            nonCombatEngine->addStrategy("stealth");
            break;
        case CLASS_MAGE:
            if (tab > 1)
                nonCombatEngine->addStrategy("bdps");
            else
                nonCombatEngine->addStrategy("bmana");
            break;
        case CLASS_WARLOCK:
            if (tab == 0)
            {
                if (player->getLevel() > 30)
                    nonCombatEngine->addStrategies("felhunter", NULL);
                else
                    nonCombatEngine->addStrategies("imp", NULL);
            }
            if (tab == 1)
            {
             if (player->getLevel() >= 50)
                    nonCombatEngine->addStrategies("felguard", NULL);
                else nonCombatEngine->addStrategies("voidwalker", NULL);
            }
            else
            {
                nonCombatEngine->addStrategies("imp", NULL);
            }
    }

	if (player->InBattleGround())
	{
		nonCombatEngine->addStrategies("grind", "warsong", "attack weak", "cure", "nc", "food", "stay", "follow", "chat","default", "quest", "loot", "gather", "duel", "emote", "lfg", "bg", "bhealth", "bmana", NULL);
		
			}
	else {
		nonCombatEngine->addStrategies("attack weak", "nc", "food", "stay", "cure", "follow", "chat","default", "quest", "loot", "gather", "duel", "emote", "lfg", "bg", "bhealth", "bmana", NULL);
	}

    //nonCombatEngine->addStrategies("nc", "attack weak", "food", "stay", "chat",
    //        "default", "quest", "loot", "gather", "duel", "emote", NULL);


    if (sRandomPlayerbotMgr.IsRandomBot(player) && !player->GetGroup())
    {
        //nonCombatEngine->ChangeStrategy(sPlayerbotAIConfig.randomBotNonCombatStrategies);
        //debug only
        nonCombatEngine->addStrategies("move random", "grind", "food", NULL);
		nonCombatEngine->ChangeStrategy(sPlayerbotAIConfig.randomBotNonCombatStrategies);
    }
	else if (sRandomPlayerbotMgr.IsRandomBot(player))
		{
			if (!player->GetGroup())
			{
				nonCombatEngine->ChangeStrategy(sPlayerbotAIConfig.randomBotNonCombatStrategies);
			}
		}
		else
		{
			nonCombatEngine->ChangeStrategy(sPlayerbotAIConfig.nonCombatStrategies);
		}

}

Engine* AiFactory::createNonCombatEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext) {
	Engine* nonCombatEngine = new Engine(facade, AiObjectContext);

    AddDefaultNonCombatStrategies(player, facade, nonCombatEngine);
	return nonCombatEngine;
}

void AiFactory::AddDefaultDeadStrategies(Player* player, PlayerbotAI* const facade, Engine* deadEngine)
{
    deadEngine->addStrategies("dead", "stay", "chat", "default", "follow", NULL);
    if (sRandomPlayerbotMgr.IsRandomBot(player) && !player->GetGroup())
    {
        deadEngine->removeStrategy("follow");
    }
}

void AiFactory::AddDefaultMobileStrategies(Player* player, PlayerbotAI* const facade, Engine* mobileEngine)
{
    mobileEngine->addStrategies("mobile", "stay", "chat", "default", "follow", NULL);
}


Engine* AiFactory::createDeadEngine(Player* player, PlayerbotAI* const facade, AiObjectContext* AiObjectContext) {
    Engine* deadEngine = new Engine(facade, AiObjectContext);
    AddDefaultDeadStrategies(player, facade, deadEngine);
    return deadEngine;
}
