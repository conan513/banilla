/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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

/* ScriptData
SDName: GO_Scripts
SD%Complete: 100
SDComment: Quest support: 4285,4287,4288(crystal pylons), 4296, 5088, 6481, 10990, 10991, 10992. Field_Repair_Bot->Teaches spell 22704. Barov_journal->Teaches spell 26089
SDCategory: Game Objects
EndScriptData */

/* ContentData
go_cat_figurine (the "trap" version of GO, two different exist)
go_northern_crystal_pylon
go_eastern_crystal_pylon
go_western_crystal_pylon
go_barov_journal
go_field_repair_bot_74A
go_orb_of_command
go_resonite_cask
go_sacred_fire_of_life
go_tablet_of_madness
go_tablet_of_the_seven
EndContentData */

#include "scriptPCH.h"

/*######
## go_cat_figurine
######*/

enum
{
    SPELL_SUMMON_GHOST_SABER    = 5968,
};

bool GOHello_go_cat_figurine(Player* pPlayer, GameObject* pGo)
{
    pPlayer->CastSpell(pPlayer, SPELL_SUMMON_GHOST_SABER, true);
    return false;
}

/*######
## go_crystal_pylons (3x)
######*/


bool GOHello_go_eastern_crystal_pylon(Player* pPlayer, GameObject* pGo)
{
    if (pGo->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER)
    {
        pPlayer->PrepareQuestMenu(pGo->GetGUID());
        pPlayer->SendPreparedQuest(pGo->GetGUID());
    }

    if (pPlayer->GetQuestStatus(4287) == QUEST_STATUS_INCOMPLETE)
        pPlayer->AreaExploredOrEventHappens(4287);

    return true;
}

bool GOHello_go_western_crystal_pylon(Player* pPlayer, GameObject* pGo)
{
    if (pGo->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER)
    {
        pPlayer->PrepareQuestMenu(pGo->GetGUID());
        pPlayer->SendPreparedQuest(pGo->GetGUID());
    }

    if (pPlayer->GetQuestStatus(4288) == QUEST_STATUS_INCOMPLETE)
        pPlayer->AreaExploredOrEventHappens(4288);

    return true;
}

bool GOHello_go_northern_crystal_pylon(Player* pPlayer, GameObject* pGo)
{
    if (pGo->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER)
    {
        pPlayer->PrepareQuestMenu(pGo->GetGUID());
        pPlayer->SendPreparedQuest(pGo->GetGUID());
    }

    if (pPlayer->GetQuestStatus(4285) == QUEST_STATUS_INCOMPLETE)
        pPlayer->AreaExploredOrEventHappens(4285);

    return true;
}


/*######
## go_barov_journal
######*/

bool GOHello_go_barov_journal(Player* pPlayer, GameObject* pGo)
{
    if (sWorld.GetWowPatch() > WOW_PATCH_108)
    {
        if (pPlayer->HasSkill(SKILL_TAILORING) && pPlayer->GetBaseSkillValue(SKILL_TAILORING) >= 285)
        {
            if (!pPlayer->HasSpell(26086))
            {
                pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Learn recipe Felcloth Bag", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);
                pPlayer->SEND_GOSSIP_MENU(8121, pGo->GetObjectGuid());
            }
            else
                pPlayer->SEND_GOSSIP_MENU(8122, pGo->GetObjectGuid());
        }
        else
            pPlayer->SEND_GOSSIP_MENU(8120, pGo->GetObjectGuid());
        return true;
    }

    return false;
}

bool GossipSelect_go_barov_journal(Player* pPlayer, GameObject* pGo, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF)
    {
        pPlayer->CastSpell(pPlayer, 26095, false);
        pPlayer->CLOSE_GOSSIP_MENU();
    }
    return true;
}

/*######
## go_greater_moonlight
######*/

bool GOHello_go_greater_moonlight(Player* pPlayer, GameObject* pGo) {
    auto zone = pPlayer->GetZoneId();

    if (zone == 493) // Moonglade
    {
        sLog.outError("Zone %d Team %d GO %d", zone, pPlayer->GetTeamId(), pGo->GetGUIDLow());
        if (pPlayer->GetTeamId() == TEAM_ALLIANCE)
        {
            switch (pGo->GetGUIDLow())
            {
                case 3998422: // Darnassus
                    pPlayer->TeleportTo(WorldLocation(1, 10150.45f, 2602.12f, 1330.82f, 5.03f));
                    break;
                case 3998424: // Stormwind
                    pPlayer->TeleportTo(WorldLocation(0, -8748.27f, 1074.27f, 90.52f, 4.17f));
                    break;
                case 3998425: // Ironforge
                    pPlayer->TeleportTo(WorldLocation(0, -4663.39f, -956.23f, 500.37f, 5.73f));
                    break;
                default:
                    return false;
            }
        }
        else
        {
            switch(pGo->GetGUID())
            {
                case 3998423: // Thunderbluff
                    pPlayer->TeleportTo(WorldLocation(1, -1031.73f, -230.42f, 160.18f, 3.12f));
                    break;
                case 3998426: // Undercity
                    pPlayer->TeleportTo(WorldLocation(0, 1642.41f, 239.9f, 62.59f, 3.01f));
                    break;
                case 3998427: // Orgrimmar
                    pPlayer->TeleportTo(WorldLocation(1, 1971.18f, -4259.45f, 32.21f, 4.0f));
                    break;
                default:
                    return false;
            }
        }
    
    } else {
        pPlayer->TeleportTo(WorldLocation(1, 7577.0f, -2188.9f, 475.3f, 5.03f));
    }

    return true;
}

/*######
## go_field_repair_bot_74A
######*/

bool GOHello_go_field_repair_bot_74A(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->HasSkill(SKILL_ENGINEERING) && pPlayer->GetBaseSkillValue(SKILL_ENGINEERING) >= 300 && !pPlayer->HasSpell(22704))
        pPlayer->CastSpell(pPlayer, 22864, false);
    return true;
}

/*######
## go_gilded_brazier
######*/

enum
{
    NPC_STILLBLADE  = 17716,
};

bool GOHello_go_gilded_brazier(Player* pPlayer, GameObject* pGO)
{
    if (pGO->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
    {
        if (Creature* pCreature = pPlayer->SummonCreature(NPC_STILLBLADE, 8087.632f, -7542.740f, 151.568f, 0.122f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000))
            pCreature->AI()->AttackStart(pPlayer);
    }

    return true;
}


/*######
## go_orb_of_command
######*/

bool GOHello_go_orb_of_command(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->GetQuestRewardStatus(7761))
        pPlayer->TeleportTo(469, -7664.76f, -1100.87f, 399.679f, 0.561981f);

    return true;
}

/*######
## go_resonite_cask
######*/

enum
{
    NPC_GOGGEROC    = 11920
};

bool GOHello_go_resonite_cask(Player* pPlayer, GameObject* pGO)
{
    if (pGO->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
        pGO->SummonCreature(NPC_GOGGEROC, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000);

    return false;
}

/*######
## go_sacred_fire_of_life
######*/

enum
{
    NPC_ARIKARA     = 10882,
};

bool GOHello_go_sacred_fire_of_life(Player* pPlayer, GameObject* pGO)
{
    if (pGO->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
        pPlayer->SummonCreature(NPC_ARIKARA, -5008.338f, -2118.894f, 83.657f, 0.874f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);

    return true;
}

/*######
## go_tablet_of_madness
######*/

bool GOHello_go_tablet_of_madness(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->HasSkill(SKILL_ALCHEMY) && pPlayer->GetSkillValue(SKILL_ALCHEMY) >= 300 && !pPlayer->HasSpell(24266))
        pPlayer->CastSpell(pPlayer, 24267, false);
    return true;
}

/*######
## go_tablet_of_the_seven
######*/

//TODO: use gossip option ("Transcript the Tablet") instead, if Mangos adds support.
bool GOHello_go_tablet_of_the_seven(Player* pPlayer, GameObject* pGo)
{
    if (pGo->GetGoType() != GAMEOBJECT_TYPE_QUESTGIVER)
        return true;

    if (pPlayer->GetQuestStatus(4296) == QUEST_STATUS_INCOMPLETE)
        pPlayer->CastSpell(pPlayer, 15065, false);

    return true;
}

// go_silithyste
bool GOHello_go_silithyste(Player* pPlayer, GameObject* pGo)
{
    // Histoire de pas recaster, car dans ce cas ca annule l'ancien buff, et ca spawn un autre monticule ...
    if (pPlayer->HasAura(29519, EFFECT_INDEX_0))
        return true;

    pPlayer->CastSpell(pPlayer, 29519, true);

    sLog.out(LOG_BG, "%s [%u:%u:'%s'] reprend une Silithyst d'un monticule",
             pPlayer->GetName(),
             pPlayer->GetGUIDLow(), pPlayer->GetSession()->GetAccountId(), pPlayer->GetSession()->GetRemoteAddress().c_str());


    // On despawn seulement ceux qui sont la temporairement (Blizzlike ?)
    if (pGo->GetEntry() == 181597)
    {
        pGo->SetLootState(GO_JUST_DEACTIVATED);
        pGo->AddObjectToRemoveList();
    }
    else
        pGo->SetLootState(GO_JUST_DEACTIVATED);
    return true;
}

/*######
## go_restes_sha_ni
######
SQL :
UPDATE quest_template SET QuestFlags = QuestFlags | 2, SpecialFlags = SpecialFlags | 2 WHERE entry = 3821;
UPDATE gameobject_template SET ScriptName="go_restes_sha_ni" WHERE entry=160445;
UPDATE creature_template SET npcflag = 0 WHERE entry=9136;
*/

bool GOHello_go_restes_sha_ni(Player* pPlayer, GameObject* pGo)
{
    // Completion de la quete
    if (pPlayer->GetQuestStatus(3821) == QUEST_STATUS_INCOMPLETE)
        pPlayer->AreaExploredOrEventHappens(3821);
    // Invoquer (ou non) l'esprit.
    if (!pGo->FindNearestCreature(9136, 10.0f, true))
    {
        if (pPlayer->GetQuestStatus(3821) == QUEST_STATUS_INCOMPLETE || pPlayer->GetQuestStatus(3821) == QUEST_STATUS_COMPLETE)
        {
            pGo->SummonCreature(9136, -7919.9f, -2603.8f, 223.345f, 5.13f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
            return true;
        }
    }
    return true;
}

/*######
## go_Hive_Regal_Glyphed_Crystal
## go_Hive_Ashi_Glyphed_Crystal
## go_Hive_Zora_Glyphed_Crystal
######*/

enum
{
    QUEST_GLYPH_CHASING                 = 8309,
    ITEM_GEOLOGIST_TRANSCRIPTION_KIT    = 20453,
    ITEM_HIVE_ZORA_RUBBING              = 20454,
    ITEM_HIVE_ASHI_RUBBING              = 20455,
    ITEM_HIVE_REGAL_RUBBING             = 20456,
};

// gossip menu 20000 : Le cristal est couvert de glyphes et de runes compliqu�s. Vous n'y comprenez rien.
template <int REWARD_ITEM>
bool GOHello_go_Hive_Glyphed_Crystal(Player* pPlayer, GameObject* pGo)
{
    pPlayer->PlayerTalkClass->CloseGossip();
    pPlayer->PlayerTalkClass->ClearMenus();

    if (pPlayer->GetQuestStatus(QUEST_GLYPH_CHASING) == QUEST_STATUS_INCOMPLETE &&
        pPlayer->HasItemCount(ITEM_GEOLOGIST_TRANSCRIPTION_KIT, 1) &&
        !pPlayer->HasItemCount(REWARD_ITEM, 1))
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "<Use the transcription device to gather a rubbing.>", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

    pPlayer->SEND_GOSSIP_MENU(20000, pGo->GetGUID());
    return true;
}

template <int REWARD_ITEM>
bool GOSelect_go_Hive_Glyphed_Crystal(Player* pPlayer, GameObject* pGo, uint32 sender, uint32 action)
{
    pPlayer->PlayerTalkClass->CloseGossip();
    pPlayer->PlayerTalkClass->ClearMenus();

    if (pPlayer->GetQuestStatus(QUEST_GLYPH_CHASING) == QUEST_STATUS_INCOMPLETE &&
        pPlayer->HasItemCount(ITEM_GEOLOGIST_TRANSCRIPTION_KIT, 1) &&
        !pPlayer->HasItemCount(REWARD_ITEM, 1))
        pPlayer->AddItem(REWARD_ITEM, 1);

    return true;
}

/*#####
# item_arcane_charges
#####*/

enum
{
	SPELL_ARCANE_CHARGES = 45072
};

bool ItemUse_item_arcane_charges(Player* pPlayer, Item* pItem, const SpellCastTargets& /*pTargets*/)
{
	if (pPlayer->IsTaxiFlying())
		return false;

	pPlayer->SendEquipError(EQUIP_ERR_NONE, pItem, nullptr);

	if (const SpellEntry* pSpellInfo = sSpellMgr.GetSpellEntry(SPELL_ARCANE_CHARGES))
		Spell::SendCastResult(pPlayer, pSpellInfo, SPELL_FAILED_ERROR);

	return true;
}

/*#####
# item_flying_machine
#####*/

bool ItemUse_item_flying_machine(Player* pPlayer, Item* pItem, const SpellCastTargets& /*pTargets*/)
{
	uint32 itemId = pItem->GetEntry();

	if (itemId == 34060)
		if (pPlayer->GetBaseSkillValue(SKILL_RIDING) >= 225)
			return false;

	if (itemId == 34061)
		if (pPlayer->GetBaseSkillValue(SKILL_RIDING) == 300)
			return false;

	//debug_log("SD2: Player attempt to use item %u, but did not meet riding requirement", itemId);
	pPlayer->SendEquipError(EQUIP_ERR_CANT_EQUIP_SKILL, pItem, nullptr);
	return true;
}

/*#####
# item_gor_dreks_ointment
#####*/

enum
{
	NPC_TH_DIRE_WOLF = 20748,
	SPELL_GORDREKS_OINTMENT = 32578
};

bool ItemUse_item_gor_dreks_ointment(Player* pPlayer, Item* pItem, const SpellCastTargets& pTargets)
{
	if (pTargets.getUnitTarget() && pTargets.getUnitTarget()->GetTypeId() == TYPEID_UNIT && pTargets.getUnitTarget()->HasAura(SPELL_GORDREKS_OINTMENT))
	{
		pPlayer->SendEquipError(EQUIP_ERR_NONE, pItem, nullptr);

		if (const SpellEntry* pSpellInfo = sSpellMgr.GetSpellEntry(SPELL_GORDREKS_OINTMENT))
			Spell::SendCastResult(pPlayer, pSpellInfo, SPELL_FAILED_TARGET_AURASTATE);

		return true;
	}

	return false;
}

/*######
## matrix_punchograph
######*/

enum eMatrixPunchograph
{
	ITEM_WHITE_PUNCH_CARD = 9279,
	ITEM_YELLOW_PUNCH_CARD = 9280,
	ITEM_BLUE_PUNCH_CARD = 9282,
	ITEM_RED_PUNCH_CARD = 9281,
	ITEM_PRISMATIC_PUNCH_CARD = 9316,
	SPELL_YELLOW_PUNCH_CARD = 11512,
	SPELL_BLUE_PUNCH_CARD = 11525,
	SPELL_RED_PUNCH_CARD = 11528,
	SPELL_PRISMATIC_PUNCH_CARD = 11545,
	MATRIX_PUNCHOGRAPH_3005_A = 142345,
	MATRIX_PUNCHOGRAPH_3005_B = 142475,
	MATRIX_PUNCHOGRAPH_3005_C = 142476,
	MATRIX_PUNCHOGRAPH_3005_D = 142696,
};

bool GOUse_go_matrix_punchograph(Player *pPlayer, GameObject *pGO)
{
	switch (pGO->GetEntry())
	{
	case MATRIX_PUNCHOGRAPH_3005_A:
		if (pPlayer->HasItemCount(ITEM_WHITE_PUNCH_CARD, 1))
		{
			pPlayer->CastSpell(pPlayer, SPELL_YELLOW_PUNCH_CARD, true);
			pPlayer->DestroyItemCount(ITEM_WHITE_PUNCH_CARD, 1, true);
		}
		break;
	case MATRIX_PUNCHOGRAPH_3005_B:
		if (pPlayer->HasItemCount(ITEM_YELLOW_PUNCH_CARD, 1))
		{
			pPlayer->CastSpell(pPlayer, SPELL_BLUE_PUNCH_CARD, true);
			pPlayer->DestroyItemCount(ITEM_YELLOW_PUNCH_CARD, 1, true);
		}
		break;
	case MATRIX_PUNCHOGRAPH_3005_C:
		if (pPlayer->HasItemCount(ITEM_BLUE_PUNCH_CARD, 1))
		{
			pPlayer->CastSpell(pPlayer, SPELL_RED_PUNCH_CARD, true);
			pPlayer->DestroyItemCount(ITEM_BLUE_PUNCH_CARD, 1, true);
		}
		break;
	case MATRIX_PUNCHOGRAPH_3005_D:
		if (pPlayer->HasItemCount(ITEM_RED_PUNCH_CARD, 1))
		{
			pPlayer->CastSpell(pPlayer, SPELL_PRISMATIC_PUNCH_CARD, true);
			pPlayer->DestroyItemCount(ITEM_RED_PUNCH_CARD, 1, true);
		}
		break;
	default:
		break;
	}
	return false;
}

const char* ImpInABottleQuotes[] =
{
	"Hey! You try telling the future when someone's shaking up your house!",
	"I don't think so, boss.",
	"The answer's yes in here, don't see why it'd be different out there!",
	"I suppose.",
	"It's as sure as the warts on my backside",
	"Yes, unless I have anything to do with it",
	"Jump three times and dance for ten minutes and it will definitely happen!",
	"My sources say \"no\". Before the torture, that is.",
	"Definitely.",
	"I can't see why not, although, I can't see a lot of things right now.",
	"Yes, it will rain. That's not what you asked? Too bad!",
	"My fortune telling powers are immeasureable - your chances are though: NO CHANCE",
	"The odds are 32.33 [repeating of course] percent change of success.",
	"Didn't you already ask that once? Yes already!",
	"Avoid taking unnecessary gambles. Your lucky numbers are two, two and a half, and eleven-teen.",
	"When Blackrock Freezes over",
	"Survey says: BZZZZT!",
	"Imp in a ball is ignoring you.",
	"Hey! You try arranging furniture with some jerk shaking your house",
	"Yes, but if anyone else asks... it wasn't me who told you",
	"Hahahahahah, you're kidding right?",
	"Sure but you're not going to like it.",
	"I don't have to be a fortune-telling imp to know the answer to that one - No!",
	"Yes, now stop pestering me",
	"Yes! I mean no! I mean... which answer will get me out of here?",
	"When dwarves fly. Oh they do? Then yes.",
	"Want to trade places?",
	"You remember that time you tried to drill that hole in your head?",
	"What happens in the twisting nether, stays in the twisting nether.",
	"Yes, yes, a thousand times, yes already!",
	"Not unless you're some kind of super-person. And don't kid yourself, you're not.",
	"NO - and don't try shaking me again for a better answer!",
	"Yes, but I hoped I would never have to answer that",
	"Word on the peninsula is YES!",
	"Oh, that's one for sure.",
	"Do you ask this question to everything that's trapped in a ball?",
	"I ask myself that question everyday.",
	"Da King! Chort ready to serve.",
	"Are you making fun of me?",
	"It's like my mother always said: \"Razxx khaj jhashxx xashjx.\"",
	"It pains me to say this, but \"Yes\".",
	"This was NOT in my contract!",
	"It's times like these that I wish I had a cooldown.",
	"Are you my pal, Danny?",
	"Wouldn't you like to know?",
	"That's about as likely as me getting a date with a succubuss.",
	"Yes, it will rain. That's not what you asked? Too bad!",
	"Please... is Kil'jaeden red?",
	"You should be asking \"Is that rogue behind me going to kill me?\"",
	"Yes, is my answer..........NOT!",
	"Yeah, sure. You just keep thinking that.",
	"XRA RAHKI MAZIZRA!",
	"What kind of imp do you think I am?",
	"Three Words - \"ab - so - lutely\"!",
	"Looks good for you...and bad for me.",
	"You need Arcane Intellect, because that answer is obvious! NO!",
	"Ruk!",
	"It won't matter, you'll be dead by tomorrow.",
	"I can make that happen. Just sign below the dotted line...",
	"The outlook is very bad for YOU that is! Haha, take it!",
	"I've consulted my fellow imps, and we think YES, except for that one imp."
};

bool GOUse_go_imp_in_a_bottle(Player* player, GameObject* go)
{
	if (go == nullptr || player == nullptr || !go->IsInWorld() || !player->IsInWorld())
		return false;

	go->MonsterWhisper(ImpInABottleQuotes[urand(0, (sizeof(ImpInABottleQuotes) / sizeof(char*)) - 1)], player);
	return true;
};


void AddSC_go_scripts()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "go_greater_moonlight";
    newscript->pGOHello = &GOHello_go_greater_moonlight;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_cat_figurine";
    newscript->pGOHello =           &GOHello_go_cat_figurine;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_eastern_crystal_pylon";
    newscript->pGOHello =           &GOHello_go_eastern_crystal_pylon;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_northern_crystal_pylon";
    newscript->pGOHello =           &GOHello_go_northern_crystal_pylon;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_western_crystal_pylon";
    newscript->pGOHello =           &GOHello_go_western_crystal_pylon;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_barov_journal";
    newscript->pGOHello =           &GOHello_go_barov_journal;
    newscript->pGOGossipSelect =    &GossipSelect_go_barov_journal;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_field_repair_bot_74A";
    newscript->pGOHello =           &GOHello_go_field_repair_bot_74A;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_gilded_brazier";
    newscript->pGOHello =           &GOHello_go_gilded_brazier;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_orb_of_command";
    newscript->pGOHello =           &GOHello_go_orb_of_command;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_resonite_cask";
    newscript->pGOHello =           &GOHello_go_resonite_cask;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_sacred_fire_of_life";
    newscript->pGOHello =           &GOHello_go_sacred_fire_of_life;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_tablet_of_madness";
    newscript->pGOHello =           &GOHello_go_tablet_of_madness;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_tablet_of_the_seven";
    newscript->pGOHello =           &GOHello_go_tablet_of_the_seven;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_silithyste";
    newscript->pGOHello =           &GOHello_go_silithyste;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_restes_sha_ni";
    newscript->pGOHello =           &GOHello_go_restes_sha_ni;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_Hive_Regal_Glyphed_Crystal";
    newscript->pGOHello =           &(GOHello_go_Hive_Glyphed_Crystal<ITEM_HIVE_REGAL_RUBBING>);
    newscript->pGOGossipSelect =    &(GOSelect_go_Hive_Glyphed_Crystal<ITEM_HIVE_REGAL_RUBBING>);
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_Hive_Ashi_Glyphed_Crystal";
    newscript->pGOHello =           &(GOHello_go_Hive_Glyphed_Crystal<ITEM_HIVE_ASHI_RUBBING>);
    newscript->pGOGossipSelect =    &(GOSelect_go_Hive_Glyphed_Crystal<ITEM_HIVE_ASHI_RUBBING>);
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_Hive_Zora_Glyphed_Crystal";
    newscript->pGOHello =           &(GOHello_go_Hive_Glyphed_Crystal<ITEM_HIVE_ZORA_RUBBING>);
    newscript->pGOGossipSelect =    &(GOSelect_go_Hive_Glyphed_Crystal<ITEM_HIVE_ZORA_RUBBING>);
    newscript->RegisterSelf();

	newscript = new Script;
	newscript->Name = "item_arcane_charges";
	newscript->pItemUse = &ItemUse_item_arcane_charges;
	newscript->RegisterSelf();

	newscript = new Script;
	newscript->Name = "item_flying_machine";
	newscript->pItemUse = &ItemUse_item_flying_machine;
	newscript->RegisterSelf();

	newscript = new Script;
	newscript->Name = "item_gor_dreks_ointment";
	newscript->pItemUse = &ItemUse_item_gor_dreks_ointment;
	newscript->RegisterSelf();

	newscript = new Script;
	newscript->Name = "go_matrix_punchograph";
	newscript->pGOUse = &GOUse_go_matrix_punchograph;
	newscript->RegisterSelf();

	newscript = new Script;
	newscript->Name = "go_imp_in_a_bottle";
	newscript->pGOUse = &GOUse_go_imp_in_a_bottle;
	newscript->RegisterSelf();
}
