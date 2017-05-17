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
SDName: world_map_scripts
SD%Complete: 100
SDComment: Quest support: 4740, 11538
SDCategory: World Map Scripts
EndScriptData */

#include "scriptPCH.h"

enum
{
    // Quest 6134
    GO_GHOST_MAGNET             = 177746,
    NPC_MAGRAMI_SPECTRE         = 11560,

    // Quest 10998
    NPC_VIMGOL_VISUAL_BUNNY = 23040,
};

/* *********************************************************
 *                  EASTERN KINGDOMS
 */
struct world_map_eastern_kingdoms : public ScriptedMap
{
    world_map_eastern_kingdoms(Map* pMap) : ScriptedMap(pMap) {}

   
    void SetData(uint32 /*uiType*/, uint32 /*uiData*/) {}
};

InstanceData* GetInstanceData_world_map_eastern_kingdoms(Map* pMap)
{
    return new world_map_eastern_kingdoms(pMap);
}

struct GhostOPlasmEvent
{
    ObjectGuid guid;
    uint32 despawnTimer;
    uint8 phaseCounter;
    std::vector<ObjectGuid> summonedMagrami;
};

/* *********************************************************
 *                     KALIMDOR
 */
struct world_map_kalimdor : public ScriptedMap
{
    world_map_kalimdor(Map* pMap) : ScriptedMap(pMap) { Initialize(); }

    std::vector<GhostOPlasmEvent> m_vGOEvents;

    void Initialize()
    {
        m_vGOEvents.clear();
    }


    void OnObjectCreate(GameObject* pGo) override
    {
        switch (pGo->GetEntry())
        {
            case GO_GHOST_MAGNET:
                m_vGOEvents.push_back({ pGo->GetObjectGuid(),0,0 }); // insert new event with 0 timer
                pGo->SetActiveObjectState(true);
                break;
        }
    }

    bool GhostOPlasmEventStep(GhostOPlasmEvent& eventData)
    {
        if (eventData.despawnTimer > 180000)
        {
            for (auto guid : eventData.summonedMagrami)
                if (Creature* magrami = instance->GetCreature(guid))
                    if (magrami->isAlive()) // dont despawn corpses with loot
                        magrami->ForcedDespawn();

            if (GameObject* go = instance->GetGameObject(eventData.guid))
                go->AddObjectToRemoveList(); // TODO: Establish rules for despawning temporary GOs that were used in their lifetime (buttons for example)

            return false;
        }
            

        if (GameObject* go = instance->GetGameObject(eventData.guid))
        {
            if (eventData.despawnTimer / 15000 >= eventData.phaseCounter)
            {
                float x, y, z;
                go->GetPosition(x, y, z); // do some urand radius shenanigans to spawn it further and make it walk to go using doing X and Y yourself and using function in MAP to get proper Z
                uint32 random = urand(0, 35);
                float xR = x + random, yR = y + (40 - random), zR = z;
                instance->GetHeightInRange(xR, yR, zR);
                Creature* creature = go->SummonCreature(NPC_MAGRAMI_SPECTRE, xR, yR, zR, 0, TEMPSUMMON_TIMED_COMBAT_OR_DEAD_DESPAWN, 180000); // add more timed logic here
                instance->GetReachableRandomPointOnGround(x, y, z, 10.0f); // get position to which spectre will walk
                eventData.phaseCounter++;
                eventData.summonedMagrami.push_back(creature->GetObjectGuid());
                creature->GetMotionMaster()->MovePoint(1, x, y, z);
            }
            return true;
        }
        else
            return false;
    }

    void Update(uint32 diff)
    {
        if (!m_vGOEvents.empty())
        {
            for (auto iter = m_vGOEvents.begin(); iter != m_vGOEvents.end();)
            {
                iter->despawnTimer += diff;
                if (!GhostOPlasmEventStep((*iter)))                
                    iter = m_vGOEvents.erase(iter);
                else
                    ++iter;
            }
        }
    }

    void SetData(uint32 /*uiType*/, uint32 /*uiData*/) {}
};

InstanceData* GetInstanceData_world_map_kalimdor(Map* pMap)
{
    return new world_map_kalimdor(pMap);
}

/* *********************************************************
 *                     OUTLAND
 */
struct world_map_outland : public ScriptedMap
{
    world_map_outland(Map* pMap) : ScriptedMap(pMap) { Initialize(); }

    void OnCreatureCreate(Creature* pCreature)
    {
        switch (pCreature->GetEntry())
        {
            case NPC_VIMGOL_VISUAL_BUNNY:
                m_mNpcEntryGuidCollection.insert(EntryGuidSet::value_type(pCreature->GetEntry(), pCreature->GetObjectGuid()));
                break;
        }
    }

    void SetData(uint32 /*uiType*/, uint32 /*uiData*/) {}
};

InstanceData* GetInstanceData_world_map_outland(Map* pMap)
{
    return new world_map_outland(pMap);
}

void AddSC_world_map_scripts()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "world_map_eastern_kingdoms";
    pNewScript->GetInstanceData = &GetInstanceData_world_map_eastern_kingdoms;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "world_map_kalimdor";
    pNewScript->GetInstanceData = &GetInstanceData_world_map_kalimdor;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "world_map_outland";
    pNewScript->GetInstanceData = &GetInstanceData_world_map_outland;
    pNewScript->RegisterSelf();
}