#pragma once

#include "NearestGameObjects.h"
#include "LogLevelValue.h"
#include "NearestNpcsValue.h"
#include "PossibleTargetsValue.h"
#include "NearestAdsValue.h"
#include "NearestGroupMemberValue.h"
#include "NearestCorpsesValue.h"
#include "PartyMemberWithoutAuraValue.h"
#include "PartyMemberAfflicted.h"
#include "PartyMemberToHeal.h"
#include "PartyMemberToResurrect.h"
#include "CurrentTargetValue.h"
#include "SelfTargetValue.h"
#include "MasterTargetValue.h"
#include "LineTargetValue.h"
#include "TankTargetValue.h"
#include "DpsTargetValue.h"
#include "CcTargetValue.h"
#include "CurrentCcTargetValue.h"
#include "PetTargetValue.h"
#include "GrindTargetValue.h"
#include "RtiTargetValue.h"
#include "PartyMemberToDispel.h"
#include "StatsValues.h"
#include "AttackerCountValues.h"
#include "AttackersValue.h"
#include "AvailableLootValue.h"
#include "AlwaysLootListValue.h"
#include "LootStrategyValue.h"
#include "HasAvailableLootValue.h"
#include "LastMovementValue.h"
#include "DistanceValue.h"
#include "IsMovingValue.h"
#include "IsBehindValue.h"
#include "IsFacingValue.h"
#include "IsWeaponEnhancedValue.h"
#include "ItemCountValue.h"
#include "SpellIdValue.h"
#include "ItemForSpellValue.h"
#include "SpellCastUsefulValue.h"
#include "LastSpellCastValue.h"
#include "ChatValue.h"
#include "HasTotemValue.h"
#include "LeastHpTargetValue.h"
#include "AoeHealValues.h"
#include "AoeValues.h"
#include "RtiValue.h"
#include "PositionValue.h"
#include "ThreatValues.h"
#include "DuelTargetValue.h"
#include "InvalidTargetValue.h"
#include "EnemyPlayerValue.h"
#include "AttackerWithoutAuraTargetValue.h"
#include "LastSpellCastTimeValue.h"
#include "ManaSaveLevelValue.h"
#include "EnemyHealerTargetValue.h"
#include "Formations.h"
#include "ItemUsageValue.h"
#include "LastSaidValue.h"
#include "OutfitListValue.h"
#include "NearestFriendlyPlayersValue.h"
#include "NearestNonBotPlayersValue.h"
#include "RandomBotUpdateValue.h"

namespace ai
{
    class ValueContext : public NamedObjectContext<UntypedValue>
    {
    public:
        ValueContext()
        {
            creators["nearest game objects"] = &ValueContext::nearest_game_objects;
            creators["nearest npcs"] = &ValueContext::nearest_npcs;
            creators["possible targets"] = &ValueContext::possible_targets;
            creators["far targets"] = &ValueContext::far_targets;
            creators["nearest adds"] = &ValueContext::nearest_adds;
            creators["near game objects"] = &ValueContext::near_game_objects;
            creators["near npcs"] = &ValueContext::near_npcs;
			creators["nearest friendly players"] = &ValueContext::nearest_friendly_players;
            creators["nearest corpses"] = &ValueContext::nearest_corpses;
            creators["log level"] = &ValueContext::log_level;
            creators["party member without aura"] = &ValueContext::party_member_without_aura;
            creators["master without aura"] = &ValueContext::master_without_aura;
            creators["attacker without aura"] = &ValueContext::attacker_without_aura;
            creators["party member without own aura"] = &ValueContext::party_member_without_own_aura;
            creators["master without own aura"] = &ValueContext::master_without_own_aura;
            creators["attacker without own aura"] = &ValueContext::attacker_without_own_aura;
            creators["party member to heal"] = &ValueContext::party_member_to_heal;
            creators["party member to resurrect"] = &ValueContext::party_member_to_resurrect;
            creators["current target"] = &ValueContext::current_target;
            creators["self target"] = &ValueContext::self_target;
            creators["master target"] = &ValueContext::master;
            creators["line target"] = &ValueContext::line_target;
            creators["tank target"] = &ValueContext::tank_target;
            creators["dps target"] = &ValueContext::dps_target;
            creators["least hp target"] = &ValueContext::least_hp_target;
            creators["enemy player target"] = &ValueContext::enemy_player_target;

            creators["cc target"] = &ValueContext::cc_target;
            creators["cc target2"] = &ValueContext::cc_target2;
            creators["cc target3"] = &ValueContext::cc_target3;
            creators["cc target4"] = &ValueContext::cc_target4;
            creators["cc target5"] = &ValueContext::cc_target5;
            creators["cc target6"] = &ValueContext::cc_target6;

            creators["current cc target"] = &ValueContext::current_cc_target;
            creators["pet target"] = &ValueContext::pet_target;
            creators["old target"] = &ValueContext::old_target;
            creators["grind target"] = &ValueContext::grind_target;
            creators["rti target"] = &ValueContext::rti_target;
            creators["duel target"] = &ValueContext::duel_target;
            creators["in party"] = &ValueContext::in_party;
            creators["party member to dispel"] = &ValueContext::party_member_to_dispel;
            creators["party member dispel root"] = &ValueContext::party_member_dispel_root;
            creators["party member dispel frozen"] = &ValueContext::party_member_dispel_frozen;
            creators["party member dispel snare"] = &ValueContext::party_member_dispel_snare;
            creators["party member dispel charm"] = &ValueContext::party_member_dispel_charm;
            creators["party member dispel possess"] = &ValueContext::party_member_dispel_possess;
            creators["party member dispel fear"] = &ValueContext::party_member_dispel_fear;
            creators["party member dispel polymorph"] = &ValueContext::party_member_dispel_polymorph;
            creators["health"] = &ValueContext::health;
            creators["rage"] = &ValueContext::rage;
            creators["energy"] = &ValueContext::energy;
            creators["mana"] = &ValueContext::mana;
            creators["combo"] = &ValueContext::combo;
            creators["dead"] = &ValueContext::dead;
		creators["pet dead"] = &ValueContext::pet_dead;
	    creators["pet happy"] = &ValueContext::pet_happy;
            creators["target in los"] = &ValueContext::target_in_los;
            creators["target normal"] = &ValueContext::target_normal;
            creators["target elite"] = &ValueContext::target_elite;
            creators["target boss"] = &ValueContext::target_boss;
            creators["target player"] = &ValueContext::target_player;
            creators["charmed"] = &ValueContext::charmed;
            creators["possessed"] = &ValueContext::possessed;
            creators["disoriented"] = &ValueContext::disoriented;
            creators["frozen"] = &ValueContext::frozen;
            creators["feared"] = &ValueContext::feared;
            creators["rooted"] = &ValueContext::rooted;
            creators["stunned"] = &ValueContext::stunned;
            creators["snared"] = &ValueContext::snared;
            creators["silenced"] = &ValueContext::silenced;
            creators["fleeing"] = &ValueContext::fleeing;
            creators["bleeding"] = &ValueContext::bleeding;
            creators["periodic damage"] = &ValueContext::takes_damage;
            creators["polymorphed"] = &ValueContext::polymorphed;
            creators["has mana"] = &ValueContext::has_mana;
            creators["attacker count"] = &ValueContext::attacker_count;
            creators["aoe attacker count"] = &ValueContext::aoe_attacker_count;
            creators["melee attacker count"] = &ValueContext::melee_attacker_count;
            creators["my attacker count"] = &ValueContext::my_attacker_count;
            creators["has aggro"] = &ValueContext::has_aggro;
            creators["mounted"] = &ValueContext::mounted;
            creators["under cc"] = &ValueContext::under_cc;

            creators["can loot"] = &ValueContext::can_loot;
            creators["loot target"] = &ValueContext::loot_target;
            creators["available loot"] = &ValueContext::available_loot;
            creators["has available loot"] = &ValueContext::has_available_loot;
            creators["always loot list"] = &ValueContext::always_loot_list;
            creators["loot strategy"] = &ValueContext::loot_strategy;
            creators["last movement"] = &ValueContext::last_movement;
            creators["distance"] = &ValueContext::distance;
            creators["party members near"] = &ValueContext::party_member_near;
            creators["moving"] = &ValueContext::moving;
            creators["swimming"] = &ValueContext::swimming;
            creators["behind"] = &ValueContext::behind;
            creators["facing"] = &ValueContext::facing;

            creators["mainhand enhanced"] = &ValueContext::mainhand_enhanced;
            creators["offhand enhanced"] = &ValueContext::offhand_enhanced;

            creators["item count"] = &ValueContext::item_count;
            creators["inventory items"] = &ValueContext::inventory_item;

            creators["spell id"] = &ValueContext::spell_id;
            creators["item for spell"] = &ValueContext::item_for_spell;
            creators["spell cast useful"] = &ValueContext::spell_cast_useful;
            creators["last spell cast"] = &ValueContext::last_spell_cast;
            creators["last spell cast time"] = &ValueContext::last_spell_cast_time;
            creators["chat"] = &ValueContext::chat;
            creators["has totem"] = &ValueContext::has_totem;
            creators["has own totem"] = &ValueContext::has_own_totem;
            creators["has any own totem"] = &ValueContext::has_any_own_totem;

            creators["aoe heal"] = &ValueContext::aoe_heal;

            creators["rti"] = &ValueContext::rti;
            creators["position"] = &ValueContext::position;
            creators["threat"] = &ValueContext::threat;

            creators["balance"] = &ValueContext::balance;
            creators["attackers"] = &ValueContext::attackers;
            creators["invalid target"] = &ValueContext::invalid_target;
            creators["mana save level"] = &ValueContext::mana_save_level;
            creators["combat"] = &ValueContext::combat;
            creators["bag space"] = &ValueContext::bag_space;
            creators["enemy healer target"] = &ValueContext::enemy_healer_target;
            creators["formation"] = &ValueContext::formation;
            creators["item usage"] = &ValueContext::item_usage;
            creators["speed"] = &ValueContext::speed;
            creators["last said"] = &ValueContext::last_said;
            creators["last emote"] = &ValueContext::last_emote;

			creators["aoe count"] = &ValueContext::aoe_count;
			creators["aoe position"] = &ValueContext::aoe_position;
			creators["outfit list"] = &ValueContext::outfit_list_value;
			creators["random bot update"] = &ValueContext::random_bot_update_value;
			creators["nearest non bot players"] = &ValueContext::nearest_non_bot_players;
        }

    private:
        static UntypedValue* item_usage(PlayerbotAI* ai) { return new ItemUsageValue(ai); }
        static UntypedValue* formation(PlayerbotAI* ai) { return new FormationValue(ai); }
        static UntypedValue* mana_save_level(PlayerbotAI* ai) { return new ManaSaveLevelValue(ai); }
        static UntypedValue* invalid_target(PlayerbotAI* ai) { return new InvalidTargetValue(ai); }
        static UntypedValue* balance(PlayerbotAI* ai) { return new BalancePercentValue(ai); }
        static UntypedValue* attackers(PlayerbotAI* ai) { return new AttackersValue(ai); }

        static UntypedValue* position(PlayerbotAI* ai) { return new PositionValue(ai); }
        static UntypedValue* rti(PlayerbotAI* ai) { return new RtiValue(ai); }

        static UntypedValue* aoe_heal(PlayerbotAI* ai) { return new AoeHealValue(ai); }

        static UntypedValue* chat(PlayerbotAI* ai) { return new ChatValue(ai); }
        static UntypedValue* last_spell_cast(PlayerbotAI* ai) { return new LastSpellCastValue(ai); }
        static UntypedValue* last_spell_cast_time(PlayerbotAI* ai) { return new LastSpellCastTimeValue(ai); }
        static UntypedValue* spell_cast_useful(PlayerbotAI* ai) { return new SpellCastUsefulValue(ai); }
        static UntypedValue* item_for_spell(PlayerbotAI* ai) { return new ItemForSpellValue(ai); }
        static UntypedValue* spell_id(PlayerbotAI* ai) { return new SpellIdValue(ai); }
        static UntypedValue* inventory_item(PlayerbotAI* ai) { return new InventoryItemValue(ai); }
        static UntypedValue* item_count(PlayerbotAI* ai) { return new ItemCountValue(ai); }
        static UntypedValue* behind(PlayerbotAI* ai) { return new IsBehindValue(ai); }
        static UntypedValue* facing(PlayerbotAI* ai) { return new IsFacingValue(ai); }
        static UntypedValue* moving(PlayerbotAI* ai) { return new IsMovingValue(ai); }
        static UntypedValue* mainhand_enhanced(PlayerbotAI* ai) { return new IsMainhandEnhancedValue(ai); }
        static UntypedValue* offhand_enhanced(PlayerbotAI* ai) { return new IsOffhandEnhancedValue(ai); }
        static UntypedValue* swimming(PlayerbotAI* ai) { return new IsSwimmingValue(ai); }
        static UntypedValue* distance(PlayerbotAI* ai) { return new DistanceValue(ai); }
        static UntypedValue* last_movement(PlayerbotAI* ai) { return new LastMovementValue(ai); }

        static UntypedValue* can_loot(PlayerbotAI* ai) { return new CanLootValue(ai); }
        static UntypedValue* available_loot(PlayerbotAI* ai) { return new AvailableLootValue(ai); }
        static UntypedValue* loot_target(PlayerbotAI* ai) { return new LootTargetValue(ai); }
        static UntypedValue* has_available_loot(PlayerbotAI* ai) { return new HasAvailableLootValue(ai); }
        static UntypedValue* always_loot_list(PlayerbotAI* ai) { return new AlwaysLootListValue(ai); }
        static UntypedValue* loot_strategy(PlayerbotAI* ai) { return new LootStrategyValue(ai); }

        static UntypedValue* attacker_count(PlayerbotAI* ai) { return new AttackerCountValue(ai); }
        static UntypedValue* aoe_attacker_count(PlayerbotAI* ai) { return new AoeAttackerCountValue(ai); }
        static UntypedValue* melee_attacker_count(PlayerbotAI* ai) { return new MeleeAttackerCountValue(ai); }
        static UntypedValue* my_attacker_count(PlayerbotAI* ai) { return new MyAttackerCountValue(ai); }
        static UntypedValue* has_aggro(PlayerbotAI* ai) { return new HasAggroValue(ai); }
        static UntypedValue* mounted(PlayerbotAI* ai) { return new IsMountedValue(ai); }
        static UntypedValue* health(PlayerbotAI* ai) { return new HealthValue(ai); }
        static UntypedValue* rage(PlayerbotAI* ai) { return new RageValue(ai); }
        static UntypedValue* energy(PlayerbotAI* ai) { return new EnergyValue(ai); }
        static UntypedValue* mana(PlayerbotAI* ai) { return new ManaValue(ai); }
        static UntypedValue* combo(PlayerbotAI* ai) { return new ComboPointsValue(ai); }
        static UntypedValue* dead(PlayerbotAI* ai) { return new IsDeadValue(ai); }
	static UntypedValue* pet_happy(PlayerbotAI* ai) { return new PetIsHappyValue(ai); }
	static UntypedValue* pet_dead(PlayerbotAI* ai) { return new PetIsDeadValue(ai); }
        static UntypedValue* target_in_los(PlayerbotAI* ai) { return new IsTargetInLosValue(ai); }
        static UntypedValue* target_normal(PlayerbotAI* ai) { return new IsTargetNormalValue(ai); }
        static UntypedValue* target_elite(PlayerbotAI* ai) { return new IsTargetEliteValue(ai); }
        static UntypedValue* target_boss(PlayerbotAI* ai) { return new IsTargetBossValue(ai); }
        static UntypedValue* target_player(PlayerbotAI* ai) { return new IsTargetPlayerValue(ai); }
        static UntypedValue* charmed(PlayerbotAI* ai) { return new IsCharmedValue(ai); }
        static UntypedValue* under_cc(PlayerbotAI* ai) { return new IsCcValue(ai); }
        static UntypedValue* possessed(PlayerbotAI* ai) { return new IsPossessedValue(ai); }
        static UntypedValue* disoriented(PlayerbotAI* ai) { return new IsDisorientedValue(ai); }
        static UntypedValue* frozen(PlayerbotAI* ai) { return new IsFrozenValue(ai); }
        static UntypedValue* feared(PlayerbotAI* ai) { return new IsFearedValue(ai); }
        static UntypedValue* rooted(PlayerbotAI* ai) { return new IsRootedValue(ai); }
        static UntypedValue* stunned(PlayerbotAI* ai) { return new IsStunnedValue(ai); }
        static UntypedValue* snared(PlayerbotAI* ai) { return new IsSnaredValue(ai); }
        static UntypedValue* fleeing(PlayerbotAI* ai) { return new IsFleeingValue(ai); }
        static UntypedValue* silenced(PlayerbotAI* ai) { return new IsSilencedValue(ai); }
        static UntypedValue* bleeding(PlayerbotAI* ai) { return new IsBleedingValue(ai); }
        static UntypedValue* polymorphed(PlayerbotAI* ai) { return new IsPolymorphedValue(ai); }
        static UntypedValue* takes_damage(PlayerbotAI* ai) { return new TakesPeriodicDamageValue(ai); }
        static UntypedValue* has_mana(PlayerbotAI* ai) { return new HasManaValue(ai); }
        static UntypedValue* nearest_game_objects(PlayerbotAI* ai) { return new NearestGameObjects(ai); }
        static UntypedValue* near_game_objects(PlayerbotAI* ai) { return new NearestGameObjects(ai,sPlayerbotAIConfig.grindDistance); }
        static UntypedValue* party_member_near(PlayerbotAI* ai) { return new NearestGroupMemberValue(ai,sPlayerbotAIConfig.disperseDistance); }
        static UntypedValue* log_level(PlayerbotAI* ai) { return new LogLevelValue(ai); }
        static UntypedValue* nearest_npcs(PlayerbotAI* ai) { return new NearestNpcsValue(ai); }
		static UntypedValue* nearest_friendly_players(PlayerbotAI* ai) { return new NearestFriendlyPlayersValue(ai); }
        static UntypedValue* near_npcs(PlayerbotAI* ai) { return new NearestNpcsValue(ai,sPlayerbotAIConfig.grindDistance); }
        static UntypedValue* nearest_corpses(PlayerbotAI* ai) { return new NearestCorpsesValue(ai); }
        static UntypedValue* possible_targets(PlayerbotAI* ai) { return new PossibleTargetsValue(ai); }
        static UntypedValue* far_targets(PlayerbotAI* ai) { return new PossibleTargetsValue(ai,sPlayerbotAIConfig.grindDistance); }
        static UntypedValue* nearest_adds(PlayerbotAI* ai) { return new NearestAdsValue(ai); }
        static UntypedValue* party_member_without_aura(PlayerbotAI* ai) { return new PartyMemberWithoutAuraValue(ai); }
        static UntypedValue* master_without_aura(PlayerbotAI* ai) { return new MasterWithoutAuraValue(ai); }
        static UntypedValue* attacker_without_aura(PlayerbotAI* ai) { return new AttackerWithoutAuraTargetValue(ai); }
        static UntypedValue* party_member_without_own_aura(PlayerbotAI* ai) { return new PartyMemberWithoutOwnAuraValue(ai); }
        static UntypedValue* master_without_own_aura(PlayerbotAI* ai) { return new MasterWithoutOwnAuraValue(ai); }
        static UntypedValue* attacker_without_own_aura(PlayerbotAI* ai) { return new AttackerWithoutOwnAuraTargetValue(ai); }
        static UntypedValue* in_party(PlayerbotAI* ai) { return new IsPartyValue(ai); }
        static UntypedValue* party_member_to_heal(PlayerbotAI* ai) { return new PartyMemberToHeal(ai); }
        static UntypedValue* party_member_to_resurrect(PlayerbotAI* ai) { return new PartyMemberToResurrect(ai); }
        static UntypedValue* party_member_to_dispel(PlayerbotAI* ai) { return new PartyMemberToDispel(ai); }
        static UntypedValue* party_member_dispel_fear(PlayerbotAI* ai) { return new PartyMemberFeared(ai); }
        static UntypedValue* party_member_dispel_root(PlayerbotAI* ai) { return new PartyMemberRooted(ai); }
        static UntypedValue* party_member_dispel_snare(PlayerbotAI* ai) { return new PartyMemberSnared(ai); }
        static UntypedValue* party_member_dispel_charm(PlayerbotAI* ai) { return new PartyMemberCharmed(ai); }
        static UntypedValue* party_member_dispel_possess(PlayerbotAI* ai) { return new PartyMemberPossessed(ai); }
        static UntypedValue* party_member_dispel_polymorph(PlayerbotAI* ai) { return new PartyMemberPolymorphed(ai); }
        static UntypedValue* party_member_dispel_frozen(PlayerbotAI* ai) { return new PartyMemberFrozen(ai); }
        static UntypedValue* current_target(PlayerbotAI* ai) { return new CurrentTargetValue(ai); }
        static UntypedValue* old_target(PlayerbotAI* ai) { return new CurrentTargetValue(ai); }
        static UntypedValue* self_target(PlayerbotAI* ai) { return new SelfTargetValue(ai); }
        static UntypedValue* master(PlayerbotAI* ai) { return new MasterTargetValue(ai); }
        static UntypedValue* line_target(PlayerbotAI* ai) { return new LineTargetValue(ai); }
        static UntypedValue* tank_target(PlayerbotAI* ai) { return new TankTargetValue(ai); }
        static UntypedValue* dps_target(PlayerbotAI* ai) { return new DpsTargetValue(ai); }
        static UntypedValue* least_hp_target(PlayerbotAI* ai) { return new LeastHpTargetValue(ai); }
        static UntypedValue* enemy_player_target(PlayerbotAI* ai) { return new EnemyPlayerValue(ai); }
        static UntypedValue* cc_target(PlayerbotAI* ai) { return new CcTargetValue(ai); }
        static UntypedValue* cc_target2(PlayerbotAI* ai) { return new CcTarget2Value(ai); }
        static UntypedValue* cc_target3(PlayerbotAI* ai) { return new CcTarget3Value(ai); }
        static UntypedValue* cc_target4(PlayerbotAI* ai) { return new CcTarget4Value(ai); }
        static UntypedValue* cc_target5(PlayerbotAI* ai) { return new CcTarget5Value(ai); }
        static UntypedValue* cc_target6(PlayerbotAI* ai) { return new CcTarget6Value(ai); }
        static UntypedValue* current_cc_target(PlayerbotAI* ai) { return new CurrentCcTargetValue(ai); }
        static UntypedValue* pet_target(PlayerbotAI* ai) { return new PetTargetValue(ai); }
        static UntypedValue* grind_target(PlayerbotAI* ai) { return new GrindTargetValue(ai); }
        static UntypedValue* rti_target(PlayerbotAI* ai) { return new RtiTargetValue(ai); }
        static UntypedValue* duel_target(PlayerbotAI* ai) { return new DuelTargetValue(ai); }
        static UntypedValue* has_totem(PlayerbotAI* ai) { return new HasTotemValue(ai); }
        static UntypedValue* has_own_totem(PlayerbotAI* ai) { return new HasOwnTotemValue(ai); }
        static UntypedValue* has_any_own_totem(PlayerbotAI* ai) { return new HasAnyOwnTotemValue(ai); }
        static UntypedValue* threat(PlayerbotAI* ai) { return new ThreatValue(ai); }
        static UntypedValue* combat(PlayerbotAI* ai) { return new IsInCombatValue(ai); }
        static UntypedValue* bag_space(PlayerbotAI* ai) { return new BagSpaceValue(ai); }
        static UntypedValue* enemy_healer_target(PlayerbotAI* ai) { return new EnemyHealerTargetValue(ai); }
        static UntypedValue* speed(PlayerbotAI* ai) { return new SpeedValue(ai); }
        static UntypedValue* last_said(PlayerbotAI* ai) { return new LastSaidValue(ai); }
        static UntypedValue* last_emote(PlayerbotAI* ai) { return new LastEmoteValue(ai); }
		static UntypedValue* aoe_count(PlayerbotAI* ai) { return new AoeCountValue(ai); }
		static UntypedValue* aoe_position(PlayerbotAI* ai) { return new AoePositionValue(ai); }
		static UntypedValue* outfit_list_value(PlayerbotAI* ai) { return new OutfitListValue(ai); }
		static UntypedValue* random_bot_update_value(PlayerbotAI* ai) { return new RandomBotUpdateValue(ai); }
		static UntypedValue* nearest_non_bot_players(PlayerbotAI* ai) { return new NearestNonBotPlayersValue(ai); }
    };
};
