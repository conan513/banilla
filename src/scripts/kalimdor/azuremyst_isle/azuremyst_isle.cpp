/* This file is part of the ScriptDev2 Project. See AUTHORS file for Copyright information
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
SDName: Azuremyst_Isle
SD%Complete: 75
SDComment: Quest support: 9283, 9528, Injured Draenei cosmetic only
SDCategory: Azuremyst Isle
EndScriptData */

/* ContentData
npc_draenei_survivor
npc_magwin
EndContentData */

#include "scriptPCH.h"

/*######
## npc_draenei_survivor
######*/

enum
{
    SAY_HEAL1           = -1000176,
    SAY_HEAL2           = -1000177,
    SAY_HEAL3           = -1000178,
    SAY_HEAL4           = -1000179,
    SAY_HELP1           = -1000180,
    SAY_HELP2           = -1000181,
    SAY_HELP3           = -1000182,
    SAY_HELP4           = -1000183,

    SPELL_IRRIDATION    = 35046,
    SPELL_STUNNED       = 28630
};

struct npc_draenei_survivorAI : public ScriptedAI
{
    npc_draenei_survivorAI(Creature* pCreature) : ScriptedAI(pCreature) {Reset();}

    ObjectGuid m_casterGuid;

    uint32 m_uiSayThanksTimer;
    uint32 m_uiRunAwayTimer;
    uint32 m_uiSayHelpTimer;

    bool m_bCanSayHelp;

    void Reset() override
    {
        m_casterGuid.Clear();

        m_uiSayThanksTimer = 0;
        m_uiRunAwayTimer = 0;
        m_uiSayHelpTimer = 10000;

        m_bCanSayHelp = true;

        m_creature->CastSpell(m_creature, SPELL_IRRIDATION, true);

        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PVP);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);
        m_creature->SetHealth(int(m_creature->GetMaxHealth()*.1));
        m_creature->SetStandState(UNIT_STAND_STATE_SLEEP);
    }

    void MoveInLineOfSight(Unit* pWho) override
    {
        if (m_bCanSayHelp && pWho->GetTypeId() == TYPEID_PLAYER && m_creature->IsFriendlyTo(pWho) &&
                m_creature->IsWithinDistInMap(pWho, 25.0f))
        {
            // Random switch between 4 texts
            switch (urand(0, 3))
            {
                case 0: DoScriptText(SAY_HELP1, m_creature, pWho); break;
                case 1: DoScriptText(SAY_HELP2, m_creature, pWho); break;
                case 2: DoScriptText(SAY_HELP3, m_creature, pWho); break;
                case 3: DoScriptText(SAY_HELP4, m_creature, pWho); break;
            }

            m_uiSayHelpTimer = 20000;
            m_bCanSayHelp = false;
        }
    }

    void SpellHit(Unit* pCaster, const SpellEntry* pSpell) override
    {
        if (pSpell->Id == 28880)
        {
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PVP);
            m_creature->SetStandState(UNIT_STAND_STATE_STAND);

            m_creature->CastSpell(m_creature, SPELL_STUNNED, true);

            m_casterGuid = pCaster->GetObjectGuid();

            m_uiSayThanksTimer = 5000;
        }
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (m_uiSayThanksTimer)
        {
            if (m_uiSayThanksTimer <= uiDiff)
            {
                m_creature->RemoveAurasDueToSpell(SPELL_IRRIDATION);

                if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_casterGuid))
                {
                    if (pPlayer->GetTypeId() != TYPEID_PLAYER)
                        return;

                    switch (urand(0, 3))
                    {
                        case 0: DoScriptText(SAY_HEAL1, m_creature, pPlayer); break;
                        case 1: DoScriptText(SAY_HEAL2, m_creature, pPlayer); break;
                        case 2: DoScriptText(SAY_HEAL3, m_creature, pPlayer); break;
                        case 3: DoScriptText(SAY_HEAL4, m_creature, pPlayer); break;
                    }

                    pPlayer->TalkedToCreature(m_creature->GetEntry(), m_creature->GetObjectGuid());
                }

                m_creature->GetMotionMaster()->Clear();
                m_creature->GetMotionMaster()->MovePoint(0, -4115.053711f, -13754.831055f, 73.508949f);

                m_uiRunAwayTimer = 10000;
                m_uiSayThanksTimer = 0;
            }
            else m_uiSayThanksTimer -= uiDiff;

            return;
        }

        if (m_uiRunAwayTimer)
        {
            if (m_uiRunAwayTimer <= uiDiff)
                m_creature->ForcedDespawn();
            else
                m_uiRunAwayTimer -= uiDiff;

            return;
        }

        if (m_uiSayHelpTimer < uiDiff)
        {
            m_bCanSayHelp = true;
            m_uiSayHelpTimer = 20000;
        }
        else m_uiSayHelpTimer -= uiDiff;
    }
};

CreatureAI* GetAI_npc_draenei_survivor(Creature* pCreature)
{
    return new npc_draenei_survivorAI(pCreature);
}

/*######
## npc_magwin
######*/

enum
{
    SAY_START               = -1000111,
    SAY_AGGRO               = -1000112,
    SAY_PROGRESS            = -1000113,
    SAY_END1                = -1000114,
    SAY_END2                = -1000115,
    EMOTE_HUG               = -1000116,
    SAY_DAUGHTER            = -1000184,

    NPC_COWLEN              = 17311,

    QUEST_A_CRY_FOR_HELP    = 9528
};

struct npc_magwinAI : public npc_escortAI
{
    npc_magwinAI(Creature* pCreature) : npc_escortAI(pCreature) { Reset(); }

    void Reset() override
    {
        if (!HasEscortState(STATE_ESCORT_ESCORTING))
            m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
    }

    void Aggro(Unit* pWho) override
    {
        if (urand(0, 1))
            DoScriptText(SAY_AGGRO, m_creature);
    }

    void WaypointReached(uint32 uiPointId) override
    {
        switch (uiPointId)
        {
            case 0:
                m_creature->SetStandState(UNIT_STAND_STATE_STAND);
                DoScriptText(SAY_START, m_creature);
                break;
            case 20:
                DoScriptText(SAY_PROGRESS, m_creature);
                break;
            case 33:
                SetRun();
                DoScriptText(SAY_END1, m_creature);
                if (Player* pPlayer = GetPlayerForEscort())
                    pPlayer->GroupEventHappens(QUEST_A_CRY_FOR_HELP, m_creature);
                if (Creature* pFather = GetClosestCreatureWithEntry(m_creature, NPC_COWLEN, 30.0f))
                {
                    pFather->SetStandState(UNIT_STAND_STATE_STAND);
                    pFather->SetFacingToObject(m_creature);
                }
                break;
            case 34:
                if (Creature* pFather = GetClosestCreatureWithEntry(m_creature, NPC_COWLEN, 30.0f))
                    DoScriptText(SAY_DAUGHTER, pFather);
                break;
            case 35:
                DoScriptText(EMOTE_HUG, m_creature);
                break;
            case 36:
                if (Player* pPlayer = GetPlayerForEscort())
                    DoScriptText(SAY_END2, m_creature, pPlayer);
                break;
            case 37:
                if (Creature* pFather = GetClosestCreatureWithEntry(m_creature, NPC_COWLEN, 30.0f))
                {
                    pFather->SetStandState(UNIT_STAND_STATE_SIT);
                    pFather->GetMotionMaster()->MoveTargetedHome();
                }
                SetEscortPaused(true);
                m_creature->ForcedDespawn(10000);
                m_creature->GetMotionMaster()->MoveRandomAroundPoint(m_creature->GetPositionX(), m_creature->GetPositionY(), m_creature->GetPositionZ(), 3.0f);
                break;
        }
    }

    void ReceiveAIEvent(AIEventType eventType, Creature* /*pSender*/, Unit* pInvoker, uint32 uiMiscValue) override
    {
        if (eventType == AI_EVENT_START_ESCORT && pInvoker->GetTypeId() == TYPEID_PLAYER)
        {
            m_creature->SetFactionTemporary(FACTION_ESCORT_A_NEUTRAL_PASSIVE, TEMPFACTION_RESTORE_RESPAWN);
            Start(false, ((Player*)pInvoker)->GetGUID(), GetQuestTemplateStore(uiMiscValue));
        }
    }
};

bool QuestAccept_npc_magwin(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_A_CRY_FOR_HELP)
        pCreature->AI()->SendAIEvent(AI_EVENT_START_ESCORT, pPlayer, pCreature, pQuest->GetQuestId());

    return true;
}

CreatureAI* GetAI_npc_magwinAI(Creature* pCreature)
{
    return new npc_magwinAI(pCreature);
}


/*######
## npc_sethir_the_ancient
######*/

//#define EMOTE_SOUND_DIE                  

struct npc_sethir_the_ancientAI : public ScriptedAI
{
	npc_sethir_the_ancientAI(Creature *c) : ScriptedAI(c) {}

	uint32 Timer;       // Do not spawn all mobs immediately
	uint32 temp;
	bool pause_say;     // wait some time until say sentence again

	void Reset()
	{
		Timer = 1000;
		pause_say = false;
	}

	void EnterCombat(Unit *who)
	{
		DoScriptText(-1069090, me);
	}

	void SummonedCreatureDespawn(Creature*)
	{
		EnterEvadeMode();   // evade after 3 seconds if summons do not aggro someone
	}

	void MoveInLineOfSight(Unit *who)
	{
		if (!me->isInCombat() && !pause_say && me->IsWithinDistInMap(who, 30) && me->IsHostileTo(who) && who->HasAuraType(SPELL_AURA_MOD_STEALTH))
		{
			me->MonsterSay("I know you are there, rogue. Leave my home or join the others at the bottom of the World Tree!", LANG_UNIVERSAL, 0);
			pause_say = true;
			temp = 60000;
		}
		//if (!me->isInCombat() && me->IsWithinDistInMap(who, 30) && me->IsHostileTo(who)) AttackStart(who);
		ScriptedAI::MoveInLineOfSight(who);
	}

	void UpdateAI(const uint32 diff)
	{
		if (!UpdateVictim())
			return;

		if (temp <= diff)      // after 1 minute he can say it again
		{
			pause_say = false;
			temp = 60000;
		}
		else
			temp -= diff;

		if (Timer)
		{
			if (Timer <= diff)
			{
				WorldLocation pos;
				me->GetPosition(pos);

				for (int i = 1; i <= 6; i++)
				{
					Creature * tmpC = me->SummonCreature(6911, pos.coord_x, pos.coord_y, pos.coord_z, pos.orientation, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 3000);
					tmpC->AI()->AttackStart(me->getVictim());
				}

				Timer = 0;
			}
			else
				Timer -= diff;
		}

		DoMeleeAttackIfReady();
	}
};

CreatureAI* GetAI_npc_sethir_the_ancient(Creature *_Creature)
{
	return new npc_sethir_the_ancientAI(_Creature);
}

/*######
## npc_engineer_spark_overgrind
######*/

#define SAY_TEXT        -1000256
#define SAY_EMOTE       -1000257
#define ATTACK_YELL     -1000258

#define GOSSIP_FIGHT    "Traitor! You will be brought to justice!"

#define SPELL_DYNAMITE  7978

struct npc_engineer_spark_overgrindAI : public ScriptedAI
{
	npc_engineer_spark_overgrindAI(Creature *c) : ScriptedAI(c) {}

	uint32 Dynamite_Timer;
	uint32 Emote_Timer;

	void Reset()
	{
		Dynamite_Timer = 8000;
		Emote_Timer = 120000 + rand() % 30000;
		me->setFaction(875);
	}

	void EnterCombat(Unit *who) { }

	void UpdateAI(const uint32 diff)
	{
		if (!me->isInCombat())
		{
			if (Emote_Timer < diff)
			{
				DoScriptText(-1000256, me);
				DoScriptText(-1000257, me);
				Emote_Timer = 120000 + rand() % 30000;
			}
			else
				Emote_Timer -= diff;
		}

		if (!UpdateVictim())
			return;

		if (Dynamite_Timer < diff)
		{
			DoCast(me->getVictim(), 7978);
			Dynamite_Timer = 8000;
		}
		else
			Dynamite_Timer -= diff;

		DoMeleeAttackIfReady();
	}
};

CreatureAI* GetAI_npc_engineer_spark_overgrind(Creature *_Creature)
{
	return new npc_engineer_spark_overgrindAI(_Creature);
}

bool GossipHello_npc_engineer_spark_overgrind(Player *player, Creature *_Creature)
{
	if (player->GetQuestStatus(9537) == QUEST_STATUS_INCOMPLETE)
		player->ADD_GOSSIP_ITEM(0, GOSSIP_FIGHT, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

	player->SEND_GOSSIP_MENU(player->GetGossipTextId(_Creature), _Creature->GetGUID());
	return true;
}

bool GossipSelect_npc_engineer_spark_overgrind(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
	if (action == GOSSIP_ACTION_INFO_DEF)
	{
		player->CLOSE_GOSSIP_MENU();
		_Creature->setFaction(14);
		DoScriptText(-1000258, _Creature, player);
		((npc_engineer_spark_overgrindAI*)_Creature->AI())->AttackStart(player);
	}
	return true;
}

/*######
## npc_injured_draenei
######*/

struct npc_injured_draeneiAI : public ScriptedAI
{
	npc_injured_draeneiAI(Creature *c) : ScriptedAI(c) {}

	void Reset()
	{
		me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IN_COMBAT);
		me->SetHealth(int(me->GetMaxHealth()*.15));

		me->SetUInt32Value(UNIT_FIELD_BYTES_1, RAND(UNIT_STAND_STATE_STAND, UNIT_STAND_STATE_SLEEP));
	}

	void EnterCombat(Unit *who) {}

	void MoveInLineOfSight(Unit *who)
	{
		return;                                             //ignore everyone around them (won't aggro anything)
	}

	void UpdateAI(const uint32 diff)
	{
		return;
	}

};
CreatureAI* GetAI_npc_injured_draenei(Creature *_Creature)
{
	return new npc_injured_draeneiAI(_Creature);
}

/*######
## npc_susurrus
######*/

bool GossipHello_npc_susurrus(Player *player, Creature *_Creature)
{
	if (_Creature->isQuestGiver())
		player->PrepareQuestMenu(_Creature->GetGUID());

	if (player->HasItemCount(23843, 1, true))
		player->ADD_GOSSIP_ITEM(0, "I am ready.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF);

	player->SEND_GOSSIP_MENU(player->GetGossipTextId(_Creature), _Creature->GetGUID());

	return true;
}

bool GossipSelect_npc_susurrus(Player *player, Creature *_Creature, uint32 sender, uint32 action)
{
	if (action == GOSSIP_ACTION_INFO_DEF)
	{
		player->CLOSE_GOSSIP_MENU();
		player->CastSpell(player, 32474, true);               //apparently correct spell, possible not correct place to cast, or correct caster
		
		player->ActivateTaxiPathTo(92, 11686);            //TaxiPath 506. Using invisible model, possible Trinity must allow 0(from dbc) for cases like this.
		player->ActivateTaxiPathTo(91, 11686);            //TaxiPath 506. Using invisible model, possible Trinity must allow 0(from dbc) for cases like this.
	}
	return true;
}

/*######
## npc_geezle
######*/

#define GEEZLE_SAY_1    -1000259
#define SPARK_SAY_2     -1000260
#define SPARK_SAY_3     -1000261
#define GEEZLE_SAY_4    -1000262
#define SPARK_SAY_5     -1000263
#define SPARK_SAY_6     -1000264
#define GEEZLE_SAY_7    -1000265

#define EMOTE_SPARK     -1000266

#define MOB_SPARK       17243
#define GO_NAGA_FLAG    181694

static float SparkPos[3] = { -5030.95f, -11291.99f, 7.97f };

struct npc_geezleAI : public ScriptedAI
{
	npc_geezleAI(Creature *c) : ScriptedAI(c) {}

	std::list<GameObject*> FlagList;

	uint64 SparkGUID;

	uint32 Step;
	uint32 SayTimer;

	bool EventStarted;

	void Reset()
	{
		SparkGUID = 0;
		Step = 0;
		StartEvent();
	}

	void StartEvent()
	{
		Step = 1;
		EventStarted = true;
		Creature* Spark = me->SummonCreature(MOB_SPARK, SparkPos[0], SparkPos[1], SparkPos[2], 0, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 1000);
		if (Spark)
		{
			SparkGUID = Spark->GetGUID();
			Spark->SetActiveObjectState(true);
			Spark->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
			Spark->GetMotionMaster()->MovePoint(0, -5080.70f, -11253.61f, 0.56f);
		}
		me->GetMotionMaster()->MovePoint(0, -5092.26f, -11252, 0.71f);
		SayTimer = 23000;
	}

	uint32 NextStep(uint32 Step)
	{
		Unit* Spark = Unit::GetUnit((*me), SparkGUID);

		switch (Step)
		{
		case 0: return 99999;
		case 1:
			//DespawnNagaFlag(true);
			DoScriptText(EMOTE_SPARK, Spark);
			return 1000;
		case 2:
			DoScriptText(GEEZLE_SAY_1, me, Spark);
			if (Spark)
			{
				Spark->SetInFront(me);
				me->SetInFront(Spark);
			}
			return 5000;
		case 3: DoScriptText(SPARK_SAY_2, Spark); return 7000;
		case 4: DoScriptText(SPARK_SAY_3, Spark); return 8000;
		case 5: DoScriptText(GEEZLE_SAY_4, me, Spark); return 8000;
		case 6: DoScriptText(SPARK_SAY_5, Spark); return 9000;
		case 7: DoScriptText(SPARK_SAY_6, Spark); return 8000;
		case 8: DoScriptText(GEEZLE_SAY_7, me, Spark); return 2000;
		case 9:
			me->GetMotionMaster()->MoveTargetedHome();
			if (Spark)
				Spark->GetMotionMaster()->MovePoint(0, -5030.95f, -11291.99f, 7.97f);
			return 20000;
		case 10:
			if (Spark)
				Spark->DealDamage(Spark, Spark->GetHealth(), NULL,DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
			//DespawnNagaFlag(false);
			me->SetVisibility(VISIBILITY_OFF);
		default: return 99999999;
		}
	}

	void DespawnNagaFlag(bool despawn)
	{
		/*
		MaNGOS::AllGameObjectsWithEntryInGrid go_check(GO_NAGA_FLAG);
		MaNGOS::GameObjectListSearcher<GameObject, MaNGOS::AllGameObjectsWithEntryInGrid> go_search(FlagList, go_check);
		Cell::VisitGridObjects(me, go_search, me->GetMap()->GetVisibilityDistance());

		Player* player = NULL;
		if (!FlagList.empty())
		{
			for (std::list<GameObject*>::iterator itr = FlagList.begin(); itr != FlagList.end(); ++itr)
			{
				//TODO: Found how to despawn and respawn
				if (despawn)
					(*itr)->RemoveFromWorld();
				else
					(*itr)->Respawn();
			}
		}
		*/

		GameObject* NagaFlag = me->FindNearestGameObject(GO_NAGA_FLAG, 250.f);
		if (NagaFlag)
			if (despawn)
				NagaFlag->RemoveFromWorld();
			else
				NagaFlag->Respawn();
		//else
		//	error_log("SD2 ERROR: FlagList is empty!");
	}

	void UpdateAI(const uint32 diff)
	{
		if (SayTimer < diff)
		{
			if (EventStarted)
			{
				SayTimer = NextStep(++Step);
			}
		}
		else
			SayTimer -= diff;
	}
};

CreatureAI* GetAI_npc_geezleAI(Creature *_Creature)
{
	return new npc_geezleAI(_Creature);
}

/*######
## mob_nestlewood_owlkin
######*/

#define INOCULATION_CHANNEL 29528
#define INOCULATED_OWLKIN   16534

struct mob_nestlewood_owlkinAI : public ScriptedAI
{
	mob_nestlewood_owlkinAI(Creature *c) : ScriptedAI(c) {}

	uint32 ChannelTimer;
	bool Channeled;
	bool Hitted;

	void Reset()
	{
		ChannelTimer = 0;
		Channeled = false;
		Hitted = false;
	}

	void EnterCombat(Unit *who) {}

	void SpellHit(Unit* caster, const SpellEntry* spell)
	{
		if (!caster)
			return;

		if (caster->GetTypeId() == TYPEID_PLAYER && spell->Id == 29528)
		{
			ChannelTimer = 3000;
			Hitted = true;
		}
	}

	void UpdateAI(const uint32 diff)
	{
		if (ChannelTimer < diff && !Channeled && Hitted)
		{
			me->DealDamage(me, me->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
			me->RemoveCorpse();
			me->SummonCreature(16534, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN, 180000);
			Channeled = true;
		}
		else
			ChannelTimer -= diff;

		DoMeleeAttackIfReady();
	}
};

CreatureAI* GetAI_mob_nestlewood_owlkinAI(Creature *_Creature)
{
	return new mob_nestlewood_owlkinAI(_Creature);
}

/*######
## mob_siltfin_murloc
######*/

struct mob_siltfin_murlocAI : public ScriptedAI
{
	mob_siltfin_murlocAI(Creature *c) : ScriptedAI(c) {}

	void EnterCombat(Unit *who) {}

	void Reset() {}

	void JustDied(Unit *player)
	{
		player = player->GetCharmerOrOwnerPlayerOrPlayerItself();

		if (roll_chance_i(20) && player)
		{
			if (((Player*)player)->GetQuestStatus(9595) == QUEST_STATUS_INCOMPLETE)
			{
				Unit* summon = me->SummonCreature(17612, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);
				player->CastSpell(summon, 30790, false);
			}
		}
	}

};

CreatureAI* GetAI_mob_siltfin_murlocAI(Creature *_Creature)
{
	return new mob_siltfin_murlocAI(_Creature);
}

/*######
## npc_death_ravager
######*/

enum eRavegerCage
{
	NPC_DEATH_RAVAGER = 17556,

	SPELL_REND = 13443,
	SPELL_ENRAGING_BITE = 30736,
	SPELL_DISSOLVE_ARMOR = 54938,

	QUEST_STRENGTH_ONE = 9582
};

bool go_ravager_cage(Player* pPlayer, GameObject* pGo)
{

	if (pPlayer->GetQuestStatus(QUEST_STRENGTH_ONE) == QUEST_STATUS_INCOMPLETE)
	{
		if (Creature* ravager = GetClosestCreatureWithEntry(pGo, NPC_DEATH_RAVAGER, 5.0f))
		{
			ravager->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
			ravager->SetReactState(REACT_AGGRESSIVE);
			ravager->AI()->AttackStart(pPlayer);
		}
	}
	return true;
}

struct npc_death_ravagerAI : public ScriptedAI
{
	npc_death_ravagerAI(Creature *c) : ScriptedAI(c) {}

	uint32 RendTimer;
	uint32 EnragingBiteTimer;
	uint32 DissolveArmorTimer;

	void Reset()
	{
		RendTimer = 15000;
		EnragingBiteTimer = 8000;
		DissolveArmorTimer = 12000;

		me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
		me->SetReactState(REACT_PASSIVE);
	}

	void UpdateAI(const uint32 diff)
	{
		if (!UpdateVictim())
			return;

		if (RendTimer <= diff)
		{
			DoCast(me->getVictim(), SPELL_REND);
			RendTimer = 15000;
		}
		else RendTimer -= diff;

		if (EnragingBiteTimer <= diff)
		{
			DoCast(me->getVictim(), SPELL_ENRAGING_BITE);
			EnragingBiteTimer = 12000;
		}
		else EnragingBiteTimer -= diff;

		if (DissolveArmorTimer <= diff)
		{
			DoCast(me->getVictim(), DissolveArmorTimer);
			DissolveArmorTimer = 15000;
		}
		else DissolveArmorTimer -= diff;

		DoMeleeAttackIfReady();
	}
};

CreatureAI* GetAI_npc_death_ravagerAI(Creature* pCreature)
{
	return new npc_death_ravagerAI(pCreature);
}

/*########
## Quest: The Prophecy of Akida
########*/

enum BristlelimbCage
{
	CAPITIVE_SAY_1 = -1600474,
	CAPITIVE_SAY_2 = -1600475,
	CAPITIVE_SAY_3 = -1600476,

	QUEST_THE_PROPHECY_OF_AKIDA = 9544,
	NPC_STILLPINE_CAPITIVE = 17375,
	GO_BRISTELIMB_CAGE = 181714

};


struct npc_stillpine_capitiveAI : public ScriptedAI
{
	npc_stillpine_capitiveAI(Creature *c) : ScriptedAI(c) {}

	uint32 FleeTimer;

	void Reset()
	{
		FleeTimer = 0;
		GameObject* cage = me->FindNearestGameObject(GO_BRISTELIMB_CAGE, 5.0f);
		if (cage)
			cage->ResetDoorOrButton();
	}

	void UpdateAI(const uint32 diff)
	{
	}
};

CreatureAI* GetAI_npc_stillpine_capitiveAI(Creature* pCreature)
{
	return new npc_stillpine_capitiveAI(pCreature);
}

bool go_bristlelimb_cage(Player* pPlayer, GameObject* pGo)
{
	if (pPlayer->GetQuestStatus(QUEST_THE_PROPHECY_OF_AKIDA) == QUEST_STATUS_INCOMPLETE)
	{
		Creature* pCreature = GetClosestCreatureWithEntry(pGo, NPC_STILLPINE_CAPITIVE, 5.0f);
		if (pCreature)
		{
			DoScriptText(RAND(CAPITIVE_SAY_1, CAPITIVE_SAY_2, CAPITIVE_SAY_3), pCreature, pPlayer);
			pCreature->GetMotionMaster()->MoveFleeing(pPlayer, 3500);
			pPlayer->KilledMonster(pCreature->GetCreatureInfo(), pCreature->GetGUID());
			pCreature->ForcedDespawn(3500);
			return false;
		}
	}
	return true;
}

/*######
## Quest: Matis the Cruel
######*/

#define NPC_MATIS    17664
#define SAY_1        -1900255
#define SAY_2        -1900256

struct npc_trackerAI : public ScriptedAI
{
	npc_trackerAI(Creature* creature) : ScriptedAI(creature) {}

	ShortTimeTracker CheckTimer;

	void Reset()
	{
		CheckTimer.Reset(2000);
		DoScriptText(-1900255, me);
		me->setFaction(1700);
		if (Creature* Matis = GetClosestCreatureWithEntry(me, 17664, 35.0f))
			me->AI()->AttackStart(Matis);
	}

	void Credit()
	{
		Map* map = me->GetMap();
		Map::PlayerList const &PlayerList = map->GetPlayers();

		for (Map::PlayerList::const_iterator itr = PlayerList.begin(); itr != PlayerList.end(); ++itr)
		{
			if (Player* player = itr->getSource())
			{
				if (me->IsWithinDistInMap(player, 35.0f) && (player->GetQuestStatus(9711) == QUEST_STATUS_INCOMPLETE))
					player->GroupEventHappens(9711, me);
			}
		}
	}

	void EnterEvadeMode()
	{
		me->DeleteThreatList();
		me->CombatStop(true);
	}

	void UpdateAI(const uint32 diff)
	{
		CheckTimer.Update(diff);

		if (CheckTimer.Passed())
		{
			if (Creature* Matis = GetClosestCreatureWithEntry(me, 17664, 35.0f))
			{
				if ((Matis->GetHealth()) * 100 / Matis->GetMaxHealth() < 25)
				{
					me->AI()->EnterEvadeMode();
					Matis->setFaction(35);
					Matis->CombatStop();
					Matis->DeleteThreatList();
					Matis->SetHealth(Matis->GetMaxHealth());
					Matis->SetStandState(UNIT_STAND_STATE_KNEEL);
					DoScriptText(-1900256, me);
					Credit();
					Matis->ForcedDespawn(30000);
					me->ForcedDespawn(35000);
				}
			}
			else
			{
				if (Creature* Matis = GetClosestCreatureWithEntry(me, 17664, 55.0f))
					Matis->setFaction(1701);
			}

			CheckTimer.Reset(1000);
		}

		if (!UpdateVictim())
			return;

		DoMeleeAttackIfReady();
	}
};

CreatureAI* GetAI_npc_tracker(Creature* creature)
{
	return new npc_trackerAI(creature);
}

void AddSC_azuremyst_isle()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_draenei_survivor";
    pNewScript->GetAI = &GetAI_npc_draenei_survivor;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_magwin";
    pNewScript->GetAI = &GetAI_npc_magwinAI;
    pNewScript->pQuestAcceptNPC = &QuestAccept_npc_magwin;
    pNewScript->RegisterSelf();

	 pNewScript = new Script;
	 pNewScript->Name = "npc_sethir_the_ancient";
	 pNewScript->GetAI = &GetAI_npc_sethir_the_ancient;
	 pNewScript->RegisterSelf();


	 pNewScript = new Script;
	 pNewScript->Name = "npc_engineer_spark_overgrind";
	 pNewScript->GetAI = &GetAI_npc_engineer_spark_overgrind;
	 pNewScript->pGossipHello = &GossipHello_npc_engineer_spark_overgrind;
	 pNewScript->pGossipSelect = &GossipSelect_npc_engineer_spark_overgrind;
	 pNewScript->RegisterSelf();

	 pNewScript = new Script;
	 pNewScript->Name = "npc_injured_draenei";
	 pNewScript->GetAI = &GetAI_npc_injured_draenei;
	 pNewScript->RegisterSelf();

	 pNewScript = new Script;
	 pNewScript->Name = "npc_susurrus";
	 pNewScript->pGossipHello = &GossipHello_npc_susurrus;
	 pNewScript->pGossipSelect = &GossipSelect_npc_susurrus;
	 pNewScript->RegisterSelf();

	 pNewScript = new Script;
	 pNewScript->Name = "npc_geezle";
	 pNewScript->GetAI = &GetAI_npc_geezleAI;
	 pNewScript->RegisterSelf();

	 pNewScript = new Script;
	 pNewScript->Name = "mob_nestlewood_owlkin";
	 pNewScript->GetAI = &GetAI_mob_nestlewood_owlkinAI;
	 pNewScript->RegisterSelf();

	 pNewScript = new Script;
	 pNewScript->Name = "mob_siltfin_murloc";
	 pNewScript->GetAI = &GetAI_mob_siltfin_murlocAI;
	 pNewScript->RegisterSelf();

	 pNewScript = new Script;
	 pNewScript->Name = "npc_death_ravager";
	 pNewScript->GetAI = &GetAI_npc_death_ravagerAI;
	 pNewScript->RegisterSelf();

	 pNewScript = new Script;
	 pNewScript->Name = "go_ravager_cage";
	 pNewScript->pGOUse = &go_ravager_cage;
	 pNewScript->RegisterSelf();

	 pNewScript = new Script;
	 pNewScript->Name = "npc_stillpine_capitive";
	 pNewScript->GetAI = &GetAI_npc_stillpine_capitiveAI;
	 pNewScript->RegisterSelf();

	 pNewScript = new Script;
	 pNewScript->Name = "go_bristlelimb_cage";
	 pNewScript->pGOUse = &go_bristlelimb_cage;
	 pNewScript->RegisterSelf();

	 pNewScript = new Script;
	 pNewScript->Name = "npc_tracker";
	 pNewScript->GetAI = &GetAI_npc_tracker;
	 pNewScript->RegisterSelf();
}
