# Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
# Copyright (C) 2009-2011 MaNGOSZero <https://github.com/mangos/zero>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

set (game_SRCS 
	AdvancedPlayerBotAI.h
	AdvancedPlayerBotAI.cpp
	AccountMgr.cpp
	AutoBroadCastMgr.cpp
	Camera.cpp
	CreatureGroups.cpp
	GameEventMgr.cpp
	GMTicketMgr.cpp
	GossipDef.cpp
	HardcodedEvents.cpp
	HonorMgr.cpp
	ItemEnchantmentMgr.cpp
	LootMgr.cpp
	ObjectAccessor.cpp
	ObjectGridLoader.cpp
	ObjectGuid.cpp
	ObjectMgr.cpp
	ObjectPosSelector.cpp
	pchdef.cpp
	PlayerDump.cpp
	QuestDef.cpp
	ReputationMgr.cpp
	ScriptMgr.cpp
	SkillDiscovery.cpp
	SkillExtraItems.cpp
	SocialMgr.cpp
	StatSystem.cpp
	UnitAuraProcHandler.cpp
	Weather.cpp
	World.cpp
	WorldSession.cpp
	AI/AggressorAI.cpp
	AI/CreatureAI.cpp
	AI/CreatureAIRegistry.cpp
	AI/CreatureAISelector.cpp
	AI/CreatureEventAI.cpp
	AI/CreatureEventAIMgr.cpp
	AI/GenericSpellAI.cpp
	AI/GuardAI.cpp
	AI/NullCreatureAI.cpp
	AI/PetAI.cpp
	AI/PlayerAI.cpp
	AI/ReactorAI.cpp
	AI/ScriptedAI.cpp
	AI/ScriptedEscortAI.cpp
	AI/ScriptedFollowerAI.cpp
	AI/ScriptedGuardAI.cpp
	AI/ScriptedInstance.cpp
	AI/ScriptedPetAI.cpp
	AI/TotemAI.cpp
	Anticheat/Anticheat.cpp
      Anticheat/libanticheat.cpp
      Anticheat/libanticheat.h
      Anticheat/Antispam/Antispam.cpp
      Anticheat/Antispam/Antispam.h
      Anticheat/MovementAnticheat/Cheat.cpp
      Anticheat/MovementAnticheat/Cheat.h
      Anticheat/WardenAnticheat/Warden.cpp
      Anticheat/WardenAnticheat/Warden.h
      Anticheat/WardenAnticheat/WardenMac.cpp
      Anticheat/WardenAnticheat/WardenMac.h
      Anticheat/WardenAnticheat/WardenWin.cpp
      Anticheat/WardenAnticheat/WardenWin.h
      Anticheat/WardenAnticheat/WardenStorageMgr.cpp
      Anticheat/WardenAnticheat/WardenStorageMgr.h
      Anticheat/WardenAnticheat/WardenModuleMac.h
      Anticheat/WardenAnticheat/WardenModuleWin.h
      Anticheat/WardenAnticheat/WardenKeyGeneration.h
	AuctionHouse/AuctionHouseBotMgr.cpp
	AuctionHouse/AuctionHouseMgr.cpp
	AutoTesting/AutoTestingMgr.cpp
	AutoTesting/TestLoader.cpp
	AutoTesting/Tests/AurasStack.cpp
	AutoTesting/Tests/ChanneledSpells.cpp
	AutoTesting/Tests/Cinematics.cpp
	AutoTesting/Tests/ControlSpells.cpp
	AutoTesting/Tests/Generic.cpp
	AutoTesting/Tests/Mage.cpp
	AutoTesting/Tests/PacketBroadcaster.cpp
	AutoTesting/Tests/Shaman.cpp
	AutoTesting/Tests/Test.cpp
	AutoTesting/Tests/Warlock.cpp
	Battlegrounds/BattleGround.cpp
	Battlegrounds/BattleGroundAB.cpp
	Battlegrounds/BattleGroundAV.cpp
	Battlegrounds/BattleGroundMgr.cpp
	Battlegrounds/BattleGroundWS.cpp
	Chat/Channel.cpp
	Chat/ChannelMgr.cpp
	Chat/Chat.cpp
	CinematicStuff/CinematicStuff.cpp
	CinematicStuff/CinematicStuff.h
	Commands/debugcmds.cpp
	Commands/GMTicketCommands.cpp
	Commands/Level0.cpp
	Commands/Level1.cpp
	Commands/Level2.cpp
	Commands/Level3.cpp
	Commands/Nostalrius.cpp
	Database/CharacterDatabaseCache.cpp
	Database/CharacterDatabaseCleaner.cpp
	Database/DBCStores.cpp
	Database/SQLStorages.cpp
	Group/Group.cpp
	Group/GroupReference.cpp
	Guild/Guild.cpp
	Guild/GuildMgr.cpp
	Handlers/AddonHandler.cpp
	Handlers/AuctionHouseHandler.cpp
	Handlers/BattleGroundHandler.cpp
	Handlers/ChannelHandler.cpp
	Handlers/CharacterHandler.cpp
	Handlers/ChatHandler.cpp
	Handlers/CombatHandler.cpp
	Handlers/DuelHandler.cpp
	Handlers/GMTicketHandler.cpp
	Handlers/GroupHandler.cpp
	Handlers/GuildHandler.cpp
	Handlers/ItemHandler.cpp
	Handlers/LootHandler.cpp
	Handlers/MailHandler.cpp
	Handlers/MiscHandler.cpp
	Handlers/MovementHandler.cpp
	Handlers/NPCHandler.cpp
	Handlers/PetHandler.cpp
	Handlers/PetitionsHandler.cpp
	Handlers/QueryHandler.cpp
	Handlers/QuestHandler.cpp
	Handlers/SkillHandler.cpp
	Handlers/SpellHandler.cpp
	Handlers/TaxiHandler.cpp
	Handlers/TradeHandler.cpp
	Lua/BattleGroundHooks.cpp
	Lua/CreatureHooks.cpp
	Lua/ElunaEventMgr.cpp
	Lua/ElunaInstanceAI.cpp
	Lua/ElunaUtility.cpp
	Lua/GameObjectHooks.cpp
	Lua/GossipHooks.cpp
	Lua/GroupHooks.cpp
	Lua/GuildHooks.cpp
	Lua/InstanceHooks.cpp
	Lua/ItemHooks.cpp
	Lua/lmarshal.cpp
	Lua/LuaEngine.cpp
	Lua/LuaFunctions.cpp
	Lua/PacketHooks.cpp
	Lua/PlayerHooks.cpp
	Lua/ServerHooks.cpp
	Lua/VehicleHooks.cpp
	Mail/Mail.cpp
	Mail/MassMailMgr.cpp
	MapNodes/AbstractPlayer.cpp
	MapNodes/GMCommands.cpp
	MapNodes/MapSocket.cpp
	MapNodes/MapSocketMgr.cpp
	MapNodes/MasterPlayer.cpp
	MapNodes/MasterPlayerChat.cpp
	MapNodes/NodeSession.cpp
	MapNodes/NodesMgr.cpp
	MapNodes/NodesOpcodes.cpp
	MapNodes/Handlers/GuidsSynchronization.cpp
	MapNodes/Handlers/Protocol.cpp
	MapNodes/Handlers/SessionTransfert.cpp
	MapNodes/Serializers/ItemSerializer.cpp
	MapNodes/Serializers/PlayerSerializer.cpp
	Maps/GridMap.cpp
	Maps/GridNotifiers.cpp
	Maps/GridSearchers.cpp
	Maps/GridStates.cpp
	Maps/InstanceData.cpp
	Maps/Map.cpp
	Maps/MapManager.cpp
	Maps/MapPersistentStateMgr.cpp
	Maps/MoveMap.cpp
	Maps/PathFinder.cpp
	Maps/ZoneScript.cpp
	Maps/ZoneScriptMgr.cpp
	Maps/Pool/PoolManager.cpp
	Movement/ConfusedMovementGenerator.cpp
	Movement/FearMovementGenerator.cpp
	Movement/FleeingMovementGenerator.cpp
	Movement/FollowerReference.cpp
	Movement/HomeMovementGenerator.cpp
	Movement/IdleMovementGenerator.cpp
	Movement/MotionMaster.cpp
	Movement/MovementGenerator.cpp
	Movement/PointMovementGenerator.cpp
	Movement/RandomMovementGenerator.cpp
	Movement/TargetedMovementGenerator.cpp
	Movement/WaypointManager.cpp
	Movement/WaypointMovementGenerator.cpp
	Movement/spline/MoveSpline.cpp
	Movement/spline/MoveSplineInit.cpp
	Movement/spline/packet_builder.cpp
	Movement/spline/spline.cpp
	Movement/spline/util.cpp
	Objects/Bag.cpp
	Objects/Corpse.cpp
	Objects/Creature.cpp
	Objects/DynamicObject.cpp
	Objects/GameObject.cpp
	Objects/Item.cpp
	Objects/Object.cpp
	Objects/Pet.cpp
	Objects/Player.cpp
	Objects/TemporarySummon.cpp
	Objects/Totem.cpp
	Objects/Unit.cpp
	Objects/UpdateData.cpp
	OutdoorPvP/OutdoorPvPEP.cpp
	OutdoorPvP/OutdoorPvPSI.cpp
	OutdoorPvP/Register.cpp
	PacketBroadcast/ChatCommands.cpp
	PacketBroadcast/MovementBroadcaster.cpp
	PacketBroadcast/PlayerBroadcaster.cpp
	PlayerBots/PlayerBotAI.cpp
	PlayerBots/PlayerBotMgr.cpp
	Protocol/Opcodes.cpp
	Protocol/WorldSocket.cpp
	Protocol/WorldSocketMgr.cpp
	Spells/Spell.cpp
	Spells/SpellAuras.cpp
	Spells/SpellEffects.cpp
	Spells/SpellEntry.cpp
	Spells/SpellMgr.cpp
	Spells/SpellModMgr.cpp
	Threat/HostileRefManager.cpp
	Threat/ThreatManager.cpp
	Transports/Transport.cpp
	Transports/TransportMgr.cpp
	vmap/BIH.cpp
	vmap/DynamicTree.cpp
	vmap/GameObjectModel.cpp
	vmap/MapTree.cpp
	vmap/ModelInstance.cpp
	vmap/TileAssembler.cpp
	vmap/VMapFactory.cpp
	vmap/VMapManager2.cpp
	vmap/WorldModel.cpp
	AccountMgr.h
	AutoBroadCastMgr.h
	Camera.h
	CreatureGroups.h
	Formulas.h
	GameEventMgr.h
	GMTicketMgr.h
	GossipDef.h
	HardcodedEvents.h
	HonorMgr.h
	ItemEnchantmentMgr.h
	Language.h
	LootMgr.h
	ObjectAccessor.h
	ObjectGridLoader.h
	ObjectGuid.h
	ObjectMgr.h
	ObjectPosSelector.h
	pchdef.h
	PlayerDump.h
	QuestDef.h
	ReputationMgr.h
	ScriptedGossip.h
	ScriptMgr.h
	SharedDefines.h
	SkillDiscovery.h
	SkillExtraItems.h
	SocialMgr.h
	UnitEvents.h
	Weather.h
	World.h
	WorldSession.h
	AI/AggressorAI.h
	AI/CreatureAI.h
	AI/CreatureAIImpl.h
	AI/CreatureAIRegistry.h
	AI/CreatureAISelector.h
	AI/CreatureEventAI.h
	AI/CreatureEventAIMgr.h
	AI/GameObjectAI.h
	AI/GuardAI.h
	AI/NullCreatureAI.h
	AI/PetAI.h
	AI/PlayerAI.h
	AI/ReactorAI.h
	AI/ScriptedAI.h
	AI/ScriptedEscortAI.h
	AI/ScriptedFollowerAI.h
	AI/ScriptedGameObject.h
	AI/ScriptedGossip.h
	AI/ScriptedGuardAI.h
	AI/ScriptedInstance.h
	AI/ScriptedPetAI.h
	AI/TotemAI.h
	Anticheat/Anticheat.h
	AuctionHouse/AuctionHouseBotMgr.h
	AuctionHouse/AuctionHouseMgr.h
	AutoTesting/AutoTestingMgr.h
	AutoTesting/Tests/TestPCH.h
	Battlegrounds/BattleGround.h
	Battlegrounds/BattleGroundAB.h
	Battlegrounds/BattleGroundAV.h
	Battlegrounds/BattleGroundMgr.h
	Battlegrounds/BattleGroundWS.h
	Chat/Channel.h
	Chat/ChannelMgr.h
	Chat/Chat.h
	Commands/Nostalrius.h
	Database/CharacterDatabaseCache.h
	Database/CharacterDatabaseCleaner.h
	Database/DBCEnums.h
	Database/DBCfmt.h
	Database/DBCStores.h
	Database/DBCStructure.h
	Database/SQLStorages.h
	Group/Group.h
	Group/GroupReference.h
	Group/GroupRefManager.h
	Guild/Guild.h
	Guild/GuildMgr.h
	Handlers/AddonHandler.h
	Handlers/NPCHandler.h
    Lua/AuraMethods.h
	Lua/BattleGroundMethods.h
	Lua/BindingMap.h
	Lua/CorpseMethods.h
	Lua/CreatureMethods.h
	Lua/ElunaCreatureAI.h
	Lua/ElunaEventMgr.h
	Lua/ElunaIncludes.h
	Lua/ElunaInstanceAI.h
	Lua/ElunaQueryMethods.h
	Lua/ElunaTemplate.h
	Lua/ElunaUtility.h
	Lua/GameObjectMethods.h
	Lua/GlobalMethods.h
	Lua/GroupMethods.h
	Lua/GuildMethods.h
	Lua/HookHelpers.h
	Lua/Hooks.h
	Lua/ItemMethods.h
	Lua/lmarshal.h
	Lua/LuaEngine.h
	Lua/MapMethods.h
	Lua/ObjectMethods.h
	Lua/PlayerMethods.h
	Lua/QuestMethods.h
	Lua/SpellMethods.h
	Lua/UnitMethods.h
	Lua/VehicleMethods.h
	Lua/WorldObjectMethods.h
	Lua/WorldPacketMethods.h
	Mail/Mail.h
	Mail/MassMailMgr.h
	MapNodes/AbstractPlayer.h
	MapNodes/MapSocket.h
	MapNodes/MapSocketMgr.h
	MapNodes/MasterPlayer.h
	MapNodes/NodeSession.h
	MapNodes/NodesMgr.h
	MapNodes/NodesOpcodes.h
	MapNodes/Serializers/ItemSerializer.h
	MapNodes/Serializers/PlayerSerializer.h
	MapNodes/Serializers/Serializer.h
	Maps/Cell.h
	Maps/CellImpl.h
	Maps/GridDefines.h
	Maps/GridMap.h
	Maps/GridNotifiers.h
	Maps/GridNotifiersImpl.h
	Maps/GridSearchers.h
	Maps/GridStates.h
	Maps/InstanceData.h
	Maps/Map.h
	Maps/MapManager.h
	Maps/MapPersistentStateMgr.h
	Maps/MapReference.h
	Maps/MapReferenceImpl.h
	Maps/MapRefManager.h
	Maps/MoveMap.h
	Maps/MoveMapSharedDefines.h
	Maps/Path.h
	Maps/PathFinder.h
	Maps/ZoneScript.h
	Maps/ZoneScriptMgr.h
	Maps/Pool/PoolManager.h
	Movement/ConfusedMovementGenerator.h
	Movement/FearMovementGenerator.h
	Movement/FleeingMovementGenerator.h
	Movement/FollowerReference.h
	Movement/FollowerRefManager.h
	Movement/HomeMovementGenerator.h
	Movement/IdleMovementGenerator.h
	Movement/MotionMaster.h
	Movement/MovementGenerator.h
	Movement/MovementGeneratorImpl.h
	Movement/PointMovementGenerator.h
	Movement/RandomMovementGenerator.h
	Movement/TargetedMovementGenerator.h
	Movement/WaypointManager.h
	Movement/WaypointMovementGenerator.h
	Movement/spline/MoveSpline.h
	Movement/spline/MoveSplineFlag.h
	Movement/spline/MoveSplineInit.h
	Movement/spline/MoveSplineInitArgs.h
	Movement/spline/packet_builder.h
	Movement/spline/spline.h
	Movement/spline/spline.impl.h
	Movement/spline/typedefs.h
	Objects/Bag.h
	Objects/Corpse.h
	Objects/Creature.h
	Objects/DynamicObject.h
	Objects/GameObject.h
	Objects/Item.h
	Objects/ItemPrototype.h
	Objects/Object.h
	Objects/Pet.h
	Objects/Player.h
	Objects/TemporarySummon.h
	Objects/Totem.h
	Objects/Unit.h
	Objects/UpdateData.h
	Objects/UpdateFields.h
	Objects/UpdateMask.h
	OutdoorPvP/OutdoorPvPEP.h
	OutdoorPvP/OutdoorPvPSI.h
	PacketBroadcast/MovementBroadcaster.h
	PacketBroadcast/PlayerBroadcaster.h
	PlayerBots/PlayerBotAI.h
	PlayerBots/PlayerBotMgr.h
	Protocol/Opcodes.h
	Protocol/WorldSocket.h
	Protocol/WorldSocketMgr.h
	Spells/Spell.h
	Spells/SpellAuraDefines.h
	Spells/SpellAuras.h
	Spells/SpellClassMask.h
	Spells/SpellEntry.h
	Spells/SpellMgr.h
	Spells/SpellModMgr.h
	Threat/HostileRefManager.h
	Threat/ThreatManager.h
	Transports/Transport.h
	Transports/TransportMgr.h
	vmap/BIH.h
	vmap/BIHWrap.h
	vmap/DynamicTree.h
	vmap/GameObjectModel.h
	vmap/IVMapManager.h
	vmap/MapTree.h
	vmap/ModelInstance.h
	vmap/RegularGrid.h
	vmap/TileAssembler.h
	vmap/VMapDefinitions.h
	vmap/VMapFactory.h
	vmap/VMapManager2.h
	vmap/VMapTools.h
	vmap/WorldModel.h

)


if(WIN32)
  #allow exceptions in destructors
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:implicitNoexcept-")
  set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /D__ACE_INLINE__")
endif()

# Used in game ScriptMgr
if(SCRIPTS)
  list(APPEND game_SRCS
      ${CMAKE_SOURCE_DIR}/src/scripts/ScriptLoader.cpp
      ${CMAKE_SOURCE_DIR}/src/scripts/ScriptLoader.h
  )
else()
  list(APPEND game_SRCS
      ${CMAKE_SOURCE_DIR}/src/scripts/ScriptLoader_noscripts.cpp
      ${CMAKE_SOURCE_DIR}/src/scripts/ScriptLoader.h
  )
endif()

if(USE_ANTICHEAT)
  list(APPEND game_SRCS
  )
endif()


include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/AI
  ${CMAKE_CURRENT_SOURCE_DIR}/Anticheat
  ${CMAKE_CURRENT_SOURCE_DIR}/AuctionHouse
  ${CMAKE_CURRENT_SOURCE_DIR}/AutoTesting
  ${CMAKE_CURRENT_SOURCE_DIR}/Battlegrounds
  ${CMAKE_CURRENT_SOURCE_DIR}/Chat
  ${CMAKE_CURRENT_SOURCE_DIR}/CinematicStuff
  ${CMAKE_CURRENT_SOURCE_DIR}/Commands
  ${CMAKE_CURRENT_SOURCE_DIR}/Database
  ${CMAKE_CURRENT_SOURCE_DIR}/Group
  ${CMAKE_CURRENT_SOURCE_DIR}/Guild
  ${CMAKE_CURRENT_SOURCE_DIR}/Handlers
  ${CMAKE_CURRENT_SOURCE_DIR}/Lua
  ${CMAKE_CURRENT_SOURCE_DIR}/Mail
  ${CMAKE_CURRENT_SOURCE_DIR}/MapNodes
  ${CMAKE_CURRENT_SOURCE_DIR}/MapNodes/Handlers
  ${CMAKE_CURRENT_SOURCE_DIR}/MapNodes/Serializers
  ${CMAKE_CURRENT_SOURCE_DIR}/Maps
  ${CMAKE_CURRENT_SOURCE_DIR}/Maps/Pool
  ${CMAKE_CURRENT_SOURCE_DIR}/Movement
  ${CMAKE_CURRENT_SOURCE_DIR}/Movement/spline
  ${CMAKE_CURRENT_SOURCE_DIR}/Objects
  ${CMAKE_CURRENT_SOURCE_DIR}/OutdoorPvP
  ${CMAKE_CURRENT_SOURCE_DIR}/PacketBroadcast
  ${CMAKE_CURRENT_SOURCE_DIR}/PlayerBots
  ${CMAKE_CURRENT_SOURCE_DIR}/Protocol
  ${CMAKE_CURRENT_SOURCE_DIR}/Spells
  ${CMAKE_CURRENT_SOURCE_DIR}/Texts
  ${CMAKE_CURRENT_SOURCE_DIR}/Threat
  ${CMAKE_CURRENT_SOURCE_DIR}/Transports
  ${CMAKE_CURRENT_SOURCE_DIR}/vmap
  ${CMAKE_CURRENT_SOURCE_DIR}/Warden
  ${CMAKE_SOURCE_DIR}/src/scripts
  ${CMAKE_SOURCE_DIR}/src/scripts/PrecompiledHeaders
  ${CMAKE_SOURCE_DIR}/dep/include/g3dlite
  ${CMAKE_SOURCE_DIR}/dep/recastnavigation/Detour
  ${CMAKE_SOURCE_DIR}/dep/recastnavigation
  ${CMAKE_SOURCE_DIR}/dep/include
  ${CMAKE_SOURCE_DIR}/dep/lualib
  ${CMAKE_SOURCE_DIR}/src/framework
  ${CMAKE_SOURCE_DIR}/src/framework/Network
  ${CMAKE_SOURCE_DIR}/src/shared
  ${CMAKE_BINARY_DIR}
  ${CMAKE_BINARY_DIR}/src/shared
  ${MYSQL_INCLUDE_DIR}
  ${TBB_INCLUDE_DIRS}
  ${ACE_INCLUDE_DIR}
)

source_group("Object"
  REGULAR_EXPRESSION .*
)

source_group("World/Handlers"
  REGULAR_EXPRESSION Mgr|Handler|Manager|Cell|Channel|Chat|Gossip|Grid|Instance|Map|Path|Pool|Script|Skill|Transports|Update|Weather|World
)

source_group("Motion generators"
  REGULAR_EXPRESSION MoveMap|MoveMapSharedDefines|Movement|Holder|Motion|Traveller
)

source_group("Server"
  REGULAR_EXPRESSION Socket|Session|Opcodes|DBC
  FILES
    SharedDefines.h
)

source_group("Chat Commands"
  REGULAR_EXPRESSION Level[0-9]
  FILES
    debugcmds.cpp
)

source_group("Tool"
  REGULAR_EXPRESSION DatabaseCleaner|Language|PlayerDump
)

source_group("References"
  REGULAR_EXPRESSION Reference|RefManager|ThreatManager
)

source_group("Anticheat"
  REGULAR_EXPRESSION Anticheat
)

set(LIBRARY_NAME Bots)

#Add PCH Files
set(bots_PCH "${CMAKE_CURRENT_SOURCE_DIR}/botpch.h")
if(PCH)
    LIST(APPEND bots_PCH "${CMAKE_CURRENT_SOURCE_DIR}/botpch.cpp")
endif()

#Base files
file(GLOB Playerbot_Source ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/*.h)
    source_group("Player Bot" FILES ${Playerbot_Source})
    
#file(GLOB AHbot_Source ${CMAKE_CURRENT_SOURCE_DIR}/ahbot/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/ahbot/*.h)
#    source_group("AH Bot" FILES ${AHbot_Source})
    
#Define base source library
set(LIBRARY_SRCS 
    ${Playerbot_Source}
#    ${AHbot_Source}
    ${bots_PCH}
)

#Strategy files
file(GLOB Playerbot_Strategy ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/*.h)
    source_group("Player Bot\\Strategies" FILES ${Playerbot_Strategy})
    LIST(APPEND LIBRARY_SRCS ${Playerbot_Strategy})
    
#Action files
file(GLOB Playerbot_Actions ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/actions/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/actions/*.h)
    source_group("Player Bot\\Strategies\\Actions" FILES ${Playerbot_Actions})
    LIST(APPEND LIBRARY_SRCS ${Playerbot_Actions})
    
#Generic files
file(GLOB Playerbot_Generic ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/generic/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/generic/*.h)
    source_group("Player Bot\\Strategies\\Generic" FILES ${Playerbot_Generic})
    LIST(APPEND LIBRARY_SRCS ${Playerbot_Generic})
    
#Trigger files
file(GLOB Playerbot_Triggers ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/triggers/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/triggers/*.h)
    source_group("Player Bot\\Strategies\\Triggers" FILES ${Playerbot_Triggers})
    LIST(APPEND LIBRARY_SRCS ${Playerbot_Triggers})
    
#Value files
file(GLOB Playerbot_Values ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/values/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/values/*.h)
    source_group("Player Bot\\Strategies\\Values" FILES ${Playerbot_Values})
    LIST(APPEND LIBRARY_SRCS ${Playerbot_Values})
    
## Class files

#Druid AI
file(GLOB Playerbot_Druid ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/druid/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/druid/*.h)
    source_group("Player Bot\\Strategies\\Druid" FILES ${Playerbot_Druid})
    LIST(APPEND LIBRARY_SRCS ${Playerbot_Druid})
    
#Hunter AI
file(GLOB Playerbot_Hunter ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/hunter/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/hunter/*.h)
    source_group("Player Bot\\Strategies\\Hunter" FILES ${Playerbot_Hunter})
    LIST(APPEND LIBRARY_SRCS ${Playerbot_Hunter})
    
#Mage AI
file(GLOB Playerbot_Mage ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/mage/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/mage/*.h)
    source_group("Player Bot\\Strategies\\Mage" FILES ${Playerbot_Mage})
    LIST(APPEND LIBRARY_SRCS ${Playerbot_Mage})
    
#Paladin AI
file(GLOB Playerbot_Paladin ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/paladin/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/paladin/*.h)
    source_group("Player Bot\\Strategies\\Paladin" FILES ${Playerbot_Paladin})
    LIST(APPEND LIBRARY_SRCS ${Playerbot_Paladin})
    
#Priest AI
file(GLOB Playerbot_Priest ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/priest/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/priest/*.h)
    source_group("Player Bot\\Strategies\\Priest" FILES ${Playerbot_Priest})
    LIST(APPEND LIBRARY_SRCS ${Playerbot_Priest})
    
#Rogue AI
file(GLOB Playerbot_Rogue ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/rogue/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/rogue/*.h)
    source_group("Player Bot\\Strategies\\Rogue" FILES ${Playerbot_Rogue})
    LIST(APPEND LIBRARY_SRCS ${Playerbot_Rogue})
    
#Shaman AI
file(GLOB Playerbot_Shaman ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/shaman/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/shaman/*.h)
    source_group("Player Bot\\Strategies\\Shaman" FILES ${Playerbot_Shaman})
    LIST(APPEND LIBRARY_SRCS ${Playerbot_Shaman})
    
#Warlock AI
file(GLOB Playerbot_Warlock ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/warlock/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/warlock/*.h)
    source_group("Player Bot\\Strategies\\Warlock" FILES ${Playerbot_Warlock})
    LIST(APPEND LIBRARY_SRCS ${Playerbot_Warlock})
    
#Warrior AI
file(GLOB Playerbot_Warrior ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/warrior/*.cpp ${CMAKE_CURRENT_SOURCE_DIR}/playerbot/strategy/warrior/*.h)
    source_group("Player Bot\\Strategies\\Warrior" FILES ${Playerbot_Warrior})
    LIST(APPEND LIBRARY_SRCS ${Playerbot_Warrior})

# Install config files
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/playerbot/aiplayerbot.conf.dist.in ${CMAKE_CURRENT_BINARY_DIR}/aiplayerbot.conf.dist)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/aiplayerbot.conf.dist DESTINATION ${CONF_INSTALL_DIR})

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ahbot/ahbot.conf.dist.in ${CMAKE_CURRENT_BINARY_DIR}/ahbot.conf.dist)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/ahbot.conf.dist DESTINATION ${CONF_INSTALL_DIR})

if(WIN32 AND MSVC)
  add_custom_command(TARGET ${LIBRARY_NAME}
    POST_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/ahbot.conf.dist" "${CONF_COPY_DIR}"
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_BINARY_DIR}/aiplayerbot.conf.dist" "${CONF_COPY_DIR}"
  )
endif()
