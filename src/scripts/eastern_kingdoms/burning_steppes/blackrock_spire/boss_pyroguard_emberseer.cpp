/* Copyright (C) 2006 - 2010 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Boss_Pyroguard_Emberseer
SD%Complete: 100
SDComment: Event to activate Emberseer NYI - 'aggro'-text missing
SDCategory: Blackrock Spire
EndScriptData */

#include "scriptPCH.h"
#include "blackrock_spire.h"

enum
{
    SPELL_FIRENOVA          = 23462,
    SPELL_FLAMEBUFFET       = 23341,
    SPELL_PYROBLAST         = 20228,                        // guesswork, but best fitting in spells-area, was 17274 (has mana cost)

    CANALISEURS_ENTRY           = 10316,

    SPELL_MISE_EN_CAGE          = 15281,
    SPELL_SELF_CAGE             = 15282,
    AURA_PLAYER_CANALISATION    = 16532,
    SPELL_PLAYER_MISE_EN_CAGE   = 16045,

    SPELL_LIBERATION            = 16047,
    SPELL_GROWTH                = 16048,

    DOOR_OPEN_ID                = 175705,

    REQUIRED_SUMMONERS          = 3,
    SAY_BOSS_FREE               = NOST_TEXT(151),
};

struct boss_pyroguard_emberseerAI : public ScriptedAI
{
    boss_pyroguard_emberseerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_blackrock_spire*) pCreature->GetInstanceData();
        initialized = false;
        Reset();
    }

    instance_blackrock_spire* m_pInstance;
    uint32 m_uiFireNovaTimer;
    uint32 m_uiFlameBuffetTimer;
    uint32 m_uiPyroBlastTimer;

    // NOSTALRIUS
    bool initialized;
    bool bCanalisationEnCours;
    bool bBossEnferme;
    std::vector<ObjectGuid> canaliseurs;

    void RespawnAddWarlocks()
    {
        std::vector<ObjectGuid>::iterator it;
        for (it = canaliseurs.begin(); it != canaliseurs.end(); ++it)
            if (Creature* pCanaliser = m_creature->GetMap()->GetCreature(*it))
            {
                if (!pCanaliser->isAlive())
                    pCanaliser->Respawn();
                pCanaliser->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PASSIVE);
            }
    }

    bool Initialize()
    {
        std::list<Creature*> tmpFoundCrea;
        GetCreatureListWithEntryInGrid(tmpFoundCrea, m_creature, CANALISEURS_ENTRY, 35.0f);
        while (!tmpFoundCrea.empty())
        {
            canaliseurs.push_back(tmpFoundCrea.front()->GetObjectGuid());
            tmpFoundCrea.pop_front();
        }

        if (canaliseurs.empty())
            return false;

        // Tous doivent etre en vie au debut de l'event.
        RespawnAddWarlocks();
        return true;
    }

    // Tous les canaliseurs sont-ils morts ?
    bool AreAllWarlockDead()
    {
        std::vector<ObjectGuid>::iterator it;
        for (it = canaliseurs.begin(); it != canaliseurs.end(); ++it)
            if (Creature* pCanaliser = m_creature->GetMap()->GetCreature(*it))
                if (pCanaliser->isAlive())
                    return false;
        return true;
    }

    void RefreshCanalisation(uint32 const diff)
    {
        if (!m_pInstance)
            return;
        std::vector<ObjectGuid>::iterator it;
        if (!m_creature->HasAura(SPELL_SELF_CAGE))
            m_creature->CastSpell(m_creature, SPELL_SELF_CAGE, false);
        // Verification si la canalisation a commence
        uint32 playerSummonersCount = 0;
        uint32 requiredSummoners = REQUIRED_SUMMONERS;
        Player* pSummoners[REQUIRED_SUMMONERS] = {NULL};
        Map::PlayerList const &pl = m_creature->GetMap()->GetPlayers();
        for (Map::PlayerList::const_iterator it2 = pl.begin(); it2 != pl.end(); ++it2)
        {
            Player* currPlayer = it2->getSource();
            if (currPlayer && currPlayer->HasAura(AURA_PLAYER_CANALISATION))
            {
                pSummoners[playerSummonersCount] = currPlayer;
                if (currPlayer->isGameMaster()) // Debug mode
                    requiredSummoners = 1;
                playerSummonersCount++;
                if (playerSummonersCount >= requiredSummoners)
                    break;
            }
        }

        if (playerSummonersCount >= requiredSummoners)
        {
            // Le combat avec les adds commence
            m_pInstance->SetData(TYPE_EMBERSEER, SPECIAL);
            for (it = canaliseurs.begin(); it != canaliseurs.end(); ++it)
            {
                Creature *currCanaliseur = m_creature->GetMap()->GetCreature(*it);
                if (!currCanaliseur)
                    continue;
                currCanaliseur->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PASSIVE);
                currCanaliseur->InterruptNonMeleeSpells(false);
                if (currCanaliseur->AI())
                    currCanaliseur->AI()->AttackStart(pSummoners[urand(0, requiredSummoners - 1)]);
            }
            bCanalisationEnCours = false;
            bBossEnferme = true;
        }
    }

    void EventBossLiberation()
    {
        m_creature->RemoveAllAuras();
        m_creature->CastSpell(m_creature, SPELL_LIBERATION, true);
        m_creature->CastSpell(m_creature, SPELL_GROWTH, true);
        m_creature->MonsterSay(SAY_BOSS_FREE, LANG_UNIVERSAL, 0);

        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PASSIVE);
        // On attaque tout le monde.
        Map::PlayerList const &pl = m_creature->GetMap()->GetPlayers();
        for (Map::PlayerList::const_iterator it2 = pl.begin(); it2 != pl.end(); ++it2)
        {
            Player* currPlayer = it2->getSource();
            if (currPlayer && currPlayer->isAlive() && m_creature->IsInRange(currPlayer, 0.0f, 50.0f))
                AttackStart(currPlayer);
        }
        m_creature->SetInCombatWithZone();

        if (GameObject* pGo = m_creature->FindNearestGameObject(GO_EMBERSEER_RUNE01, 100.0f))
            pGo->SetGoState(GO_STATE_ACTIVE);
        if (GameObject* pGo = m_creature->FindNearestGameObject(GO_EMBERSEER_RUNE02, 100.0f))
            pGo->SetGoState(GO_STATE_ACTIVE);
        if (GameObject* pGo = m_creature->FindNearestGameObject(GO_EMBERSEER_RUNE03, 100.0f))
            pGo->SetGoState(GO_STATE_ACTIVE);
        if (GameObject* pGo = m_creature->FindNearestGameObject(GO_EMBERSEER_RUNE04, 100.0f))
            pGo->SetGoState(GO_STATE_ACTIVE);
        if (GameObject* pGo = m_creature->FindNearestGameObject(GO_EMBERSEER_RUNE05, 100.0f))
            pGo->SetGoState(GO_STATE_ACTIVE);
        if (GameObject* pGo = m_creature->FindNearestGameObject(GO_EMBERSEER_RUNE06, 100.0f))
            pGo->SetGoState(GO_STATE_ACTIVE);
        if (GameObject* pGo = m_creature->FindNearestGameObject(GO_EMBERSEER_RUNE07, 100.0f))
            pGo->SetGoState(GO_STATE_ACTIVE);

    }
    // END NOSTALRIUS

    void Reset()
    {
        m_uiFireNovaTimer = 6000;
        m_uiFlameBuffetTimer = 3000;
        m_uiPyroBlastTimer = Randomize(14000);

        // NOSTALRIUS
        bCanalisationEnCours = true;
        bBossEnferme = true;

        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_PASSIVE);
    }

    void AttackStart(Unit *target)
    {
        // $target commence a nous attaquer.
        // Pas de combat autorise avec le boss.
        if (bCanalisationEnCours || bBossEnferme)
            return;

        // Sinon, go attaquer.
        if (m_creature->Attack(target, true))
        {
            m_creature->AddThreat(target);
            m_creature->SetInCombatWith(target);
            target->SetInCombatWith(m_creature);

            m_creature->GetMotionMaster()->MoveChase(target);
        }
    }

    void Aggro(Unit* pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_EMBERSEER, IN_PROGRESS);
    }

    void JustDied(Unit* pKiller)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_EMBERSEER, DONE);
    }

    void JustReachedHome()
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_EMBERSEER, FAIL);
        RespawnAddWarlocks();
        bCanalisationEnCours = true;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance)
            return;
        if (!initialized)
        {
            Initialize();
            initialized = true;
        }
        // Return since we have no target
        if (bCanalisationEnCours)
        {
            RefreshCanalisation(uiDiff);
            return;
        }
        if (bBossEnferme)
        {
            if (AreAllWarlockDead())
            {
                bBossEnferme = false;
                EventBossLiberation();
            }
            return;
        }

        // Sinon, on est "normalement" en combat.
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        // FireNova Timer
        if (m_uiFireNovaTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_FIRENOVA);
            m_uiFireNovaTimer = 6000;
        }
        else
            m_uiFireNovaTimer -= uiDiff;

        // FlameBuffet Timer
        if (m_uiFlameBuffetTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature, SPELL_FLAMEBUFFET);
            m_uiFlameBuffetTimer = Randomize(14000);
        }
        else
            m_uiFlameBuffetTimer -= uiDiff;

        // PyroBlast Timer
        if (m_uiPyroBlastTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                DoCastSpellIfCan(pTarget, SPELL_PYROBLAST);
            m_uiPyroBlastTimer += Randomize(15000);
        }
        else
            m_uiPyroBlastTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_pyroguard_emberseer(Creature* pCreature)
{
    return new boss_pyroguard_emberseerAI(pCreature);
}

struct npc_geolier_main_noireAI : public ScriptedAI
{
    npc_geolier_main_noireAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (instance_blackrock_spire*) pCreature->GetInstanceData();
        Reset();
    }

    instance_blackrock_spire* m_pInstance;
    uint32 MiseEnCage_Timer;
    uint32 Frappe_Timer;
    bool fled;
    // END NOSTALRIUS

    void Reset()
    {
        MiseEnCage_Timer = urand(5000, 40000);
        Frappe_Timer     = urand(2000, 12100);
        fled = false;
    }

    void AttackStart(Unit *target)
    {
        if (!m_pInstance)
            return;
        // Pas pret (event pas commence)
        if (m_pInstance->GetData(TYPE_EMBERSEER) != SPECIAL)
            return;

        // Sinon, go attaquer.
        if (m_creature->Attack(target, true))
        {
            m_creature->AddThreat(target);
            m_creature->SetInCombatWith(target);
            target->SetInCombatWith(m_creature);

            m_creature->GetMotionMaster()->MoveChase(target);
        }
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!m_pInstance)
            return;

        if (m_pInstance->GetData(TYPE_EMBERSEER) != SPECIAL)
        {
            // Pas de combat autorise pour l'instant.
            if (!m_creature->IsNonMeleeSpellCasted(false, false, true))
                m_creature->CastSpell(m_creature, SPELL_MISE_EN_CAGE, false);
            // Regen vie
            m_creature->RegenerateHealth();
            return;
        }
        // Sinon go.
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;
        if (MiseEnCage_Timer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
            {
                if (pTarget->IsWithinLOSInMap(m_creature) && !pTarget->HasAura(SPELL_PLAYER_MISE_EN_CAGE))
                {
                    m_creature->CastSpell(pTarget, SPELL_PLAYER_MISE_EN_CAGE, false);
                    MiseEnCage_Timer = Randomize(urand(20000, 40000));
                }
            }
        }
        else
            MiseEnCage_Timer -= uiDiff;

        if (Frappe_Timer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->getVictim(), 15580) == CAST_OK)
                Frappe_Timer = Randomize(urand(7900, 14000));
        }
        else
            Frappe_Timer -= uiDiff;
        if (!fled && m_creature->GetHealthPercent() < 15.0f)
        {
            m_creature->DoFleeToGetAssistance();
            fled = true;
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_geolier_main_noire(Creature* pCreature)
{
    return new npc_geolier_main_noireAI(pCreature);
}

void AddSC_boss_pyroguard_emberseer()
{
    Script* pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "boss_pyroguard_emberseer";
    pNewScript->GetAI = &GetAI_boss_pyroguard_emberseer;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_geolier_main_noire";
    pNewScript->GetAI = &GetAI_npc_geolier_main_noire;
    pNewScript->RegisterSelf();
}
