#pragma once

#include "HealthTriggers.h"
#include "GenericTriggers.h"
#include "LootTriggers.h"
#include "../triggers/GenericTriggers.h"
#include "LfgTriggers.h"

namespace ai
{

    class TriggerContext : public NamedObjectContext<Trigger>
    {
    public:
        TriggerContext()
        {
            creators["timer"] = &TriggerContext::Timer;
            creators["random"] = &TriggerContext::Random;
            creators["seldom"] = &TriggerContext::seldom;
            creators["often"] = &TriggerContext::often;
			creators["very often"] = &TriggerContext::very_often;

            creators["target critical health"] = &TriggerContext::TargetCriticalHealth;
            creators["target almost dead"] = &TriggerContext::TargetAlmostDead;

            creators["critical health"] = &TriggerContext::CriticalHealth;
            creators["low health"] = &TriggerContext::LowHealth;
            creators["medium health"] = &TriggerContext::MediumHealth;
            creators["high health"] = &TriggerContext::HighHealth;
            creators["almost full health"] = &TriggerContext::AlmostFullHealth;
            creators["full health"] = &TriggerContext::FullHealth;
            creators["almost dead"] = &TriggerContext::AlmostDead;

            creators["low mana"] = &TriggerContext::LowMana;
            creators["medium mana"] = &TriggerContext::MediumMana;
            creators["almost full mana"] = &TriggerContext::AlmostFullMana;
            creators["almost no mana"] = &TriggerContext::AlmostNoMana;
            creators["full mana"] = &TriggerContext::FullMana;
            creators["drink mana"] = &TriggerContext::DrinkMana;

            creators["party member almost dead"] = &TriggerContext::PartyMemberAlmostDead;
            creators["party member critical health"] = &TriggerContext::PartyMemberCriticalHealth;
            creators["party member low health"] = &TriggerContext::PartyMemberLowHealth;
            creators["party member medium health"] = &TriggerContext::PartyMemberMediumHealth;
            creators["party member high health"] = &TriggerContext::PartyMemberHighHealth;
            creators["party member almost full health"] = &TriggerContext::PartyMemberAlmostFullHealth;

            creators["master almost dead"] = &TriggerContext::MasterAlmostDead;
            creators["master critical health"] = &TriggerContext::MasterCriticalHealth;
            creators["master low health"] = &TriggerContext::MasterLowHealth;
            creators["master high health"] = &TriggerContext::MasterHighHealth;
            creators["master almost full health"] = &TriggerContext::MasterAlmostFullHealth;

            creators["light rage available"] = &TriggerContext::LightRageAvailable;
            creators["medium rage available"] = &TriggerContext::MediumRageAvailable;
            creators["high rage available"] = &TriggerContext::HighRageAvailable;

            creators["light energy available"] = &TriggerContext::LightEnergyAvailable;
            creators["medium energy available"] = &TriggerContext::MediumEnergyAvailable;
            creators["high energy available"] = &TriggerContext::HighEnergyAvailable;

            creators["loot available"] = &TriggerContext::LootAvailable;
            creators["no attackers"] = &TriggerContext::NoAttackers;
            creators["no target"] = &TriggerContext::NoTarget;
            creators["target in sight"] = &TriggerContext::TargetInSight;
            creators["not least hp target active"] = &TriggerContext::not_least_hp_target_active;
            creators["has nearest adds"] = &TriggerContext::has_nearest_adds;
            creators["group member near"] = &TriggerContext::has_group_members_near;
            creators["enemy player is attacking"] = &TriggerContext::enemy_player_is_attacking;

            creators["tank aoe"] = &TriggerContext::TankAoe;
            creators["lose aggro"] = &TriggerContext::LoseAggro;
            creators["have aggro"] = &TriggerContext::HasAggro;

            creators["no aoe"] = &TriggerContext::NoAoe;
            creators["light aoe"] = &TriggerContext::LightAoe;
            creators["medium aoe"] = &TriggerContext::MediumAoe;
            creators["high aoe"] = &TriggerContext::HighAoe;

            creators["no melee aoe"] = &TriggerContext::MeleeNoAoe;
            creators["melee light aoe"] = &TriggerContext::MeleeLightAoe;
            creators["melee medium aoe"] = &TriggerContext::MeleeMediumAoe;
            creators["melee high aoe"] = &TriggerContext::MeleeHighAoe;

            // creators["target out of los"] = &TriggerContext::TargetOutOfLOS;
            creators["enemy out of melee"] = &TriggerContext::EnemyOutOfMelee;
            creators["enemy out of spell"] = &TriggerContext::EnemyOutOfSpell;
            creators["enemy too close for spell"] = &TriggerContext::enemy_too_close_for_spell;
			creators["enemy too close for shoot"] = &TriggerContext::enemy_too_close_for_shoot;
            creators["enemy too close for melee"] = &TriggerContext::enemy_too_close_for_melee;
            creators["enemy in melee range"] = &TriggerContext::EnemyInMeleeRange;
			creators["enemy is close"] = &TriggerContext::enemy_is_close;

            creators["combo points available"] = &TriggerContext::ComboPointsAvailable;
            creators["combo point available"] = &TriggerContext::ComboPointAvailable;

            creators["medium threat"] = &TriggerContext::MediumThreat;

            creators["dead"] = &TriggerContext::Dead;
            creators["is rooted"] = &TriggerContext::Rooted;
            creators["is frozen"] = &TriggerContext::Frozen;
            creators["is snared"] = &TriggerContext::Snared;
            creators["is bleeding"] = &TriggerContext::Bleeding;
            creators["is stunned"] = &TriggerContext::Stunned;
            creators["is disoriented"] = &TriggerContext::Disoriented;
            creators["is possessed"] = &TriggerContext::Possessed;
            creators["is charmed"] = &TriggerContext::Charmed;
            creators["is silenced"] = &TriggerContext::Silenced;

            creators["is polymorphed"] = &TriggerContext::Polymorphed;
            creators["takes periodic damage"] = &TriggerContext::TakesPeriodicDamage;

            creators["party member dead"] = &TriggerContext::PartyMemberDead;
            creators["no pet"] = &TriggerContext::no_pet;
            creators["has attackers"] = &TriggerContext::has_attackers;
            creators["no possible targets"] = &TriggerContext::no_possible_targets;

            creators["no drink"] = &TriggerContext::no_drink;
            creators["no food"] = &TriggerContext::no_food;

            creators["mainhand not enhanced"] = &TriggerContext::Mainhand_not_enhanced;
            creators["offhand not enhanced"] = &TriggerContext::Offhand_not_enhanced;

            creators["panic"] = &TriggerContext::panic;
            creators["behind target"] = &TriggerContext::behind_target;
            creators["front target"] = &TriggerContext::front_target;
            creators["not facing target"] = &TriggerContext::not_facing_target;
            creators["far from master"] = &TriggerContext::far_from_master;
            creators["far from loot target"] = &TriggerContext::far_from_loot_target;
            creators["can loot"] = &TriggerContext::can_loot;
            creators["swimming"] = &TriggerContext::swimming;
            creators["target changed"] = &TriggerContext::target_changed;

            creators["enemy rooted"] = &TriggerContext::Target_Rooted;
            creators["enemy frozen"] = &TriggerContext::Target_Frozen;
            creators["enemy snared"] = &TriggerContext::Target_Snared;
            creators["enemy bleeding"] = &TriggerContext::Target_Bleeding;
            creators["enemy stunned"] = &TriggerContext::Target_Stunned;
            creators["enemy polymorphed"] = &TriggerContext::Target_Polymorphed;
            creators["enemy disoriented"] = &TriggerContext::Target_Disoriented;
            creators["enemy possessed"] = &TriggerContext::Target_Possessed;
            creators["enemy charmed"] = &TriggerContext::Target_Charmed;
            creators["enemy silenced"] = &TriggerContext::Target_Silenced;

            creators["party member rooted"] = &TriggerContext::Party_Member_Rooted;
            creators["party member frozen"] = &TriggerContext::Party_Member_Frozen;
            creators["party member snared"] = &TriggerContext::Party_Member_Snared;
            creators["party member polymorphed"] = &TriggerContext::Party_Member_Polymorphed;
            creators["party member charmed"] = &TriggerContext::Party_Member_Charmed;
            creators["party member possessed"] = &TriggerContext::Party_Member_Possessed;

            creators["target not rooted"] = &TriggerContext::Target_NotRooted;
            creators["target not frozen"] = &TriggerContext::Target_NotFrozen;
            creators["target not snared"] = &TriggerContext::Target_NotSnared;
            creators["target not bleeding"] = &TriggerContext::Target_NotBleeding;
            creators["target not stunned"] = &TriggerContext::Target_NotStunned;

            creators["critical aoe heal"] = &TriggerContext::critical_aoe_heal;
            creators["low aoe heal"] = &TriggerContext::low_aoe_heal;
            creators["medium aoe heal"] = &TriggerContext::medium_aoe_heal;
            creators["almost full aoe heal"] = &TriggerContext::almost_full_aoe_heal;
            creators["invalid target"] = &TriggerContext::invalid_target;
			creators["random bot update"] = &TriggerContext::random_bot_update_trigger;
			creators["no non bot players around"] = &TriggerContext::no_non_bot_players_around;

			creators["has no flag"] = &TriggerContext::player_has_no_flag;
			creators["in BattleGround"] = &TriggerContext::player_is_in_BattleGround;
			creators["in BattleGround without flag"] = &TriggerContext::player_is_in_BattleGround_no_flag;
        }
        ~TriggerContext()
        {
            creators.erase("timer");
            creators.erase("random");
            creators.erase("seldom");
            creators.erase("often");
			creators.erase("very often");

            creators.erase("target critical health");
            creators.erase("target almost dead");

            creators.erase("critical health");
            creators.erase("low health");
            creators.erase("medium health");
            creators.erase("high health");
            creators.erase("almost full health");
            creators.erase("full health");
            creators.erase("almost dead");

            creators.erase("low mana");
            creators.erase("medium mana");
            creators.erase("almost full mana");
            creators.erase("almost no mana");
            creators.erase("full mana");
            creators.erase("drink mana");

            creators.erase("party member almost dead");
            creators.erase("party member critical health");
            creators.erase("party member low health");
            creators.erase("party member medium health");
            creators.erase("party member high health");
            creators.erase("party member almost full health");

            creators.erase("master almost dead");
            creators.erase("master critical health");
            creators.erase("master low health");
            creators.erase("master high health");
            creators.erase("master almost full health");

            creators.erase("light rage available");
            creators.erase("medium rage available");
            creators.erase("high rage available");

            creators.erase("light energy available");
            creators.erase("medium energy available");
            creators.erase("high energy available");

            creators.erase("loot available");
            creators.erase("no attackers");
            creators.erase("no target");
            creators.erase("target in sight");
            creators.erase("not least hp target active");
            creators.erase("has nearest adds");
            creators.erase("group member near");
            creators.erase("enemy player is attacking");

            creators.erase("tank aoe");
            creators.erase("lose aggro");
            creators.erase("have aggro");

            creators.erase("no aoe");
            creators.erase("light aoe");
            creators.erase("medium aoe");
            creators.erase("high aoe");

            creators.erase("no melee aoe");
            creators.erase("melee light aoe");
            creators.erase("melee medium aoe");
            creators.erase("melee high aoe");

            // creators.erase("target out of los");
            creators.erase("enemy out of melee");
            creators.erase("enemy out of spell");
            creators.erase("enemy too close for spell");
			creators.erase("enemy too close for shoot");
            creators.erase("enemy too close for melee");
            creators.erase("enemy in melee range");
			creators.erase("enemy is close");

            creators.erase("combo points available");
            creators.erase("combo point available");

            creators.erase("medium threat");

            creators.erase("dead");
            creators.erase("is rooted");
            creators.erase("is frozen");
            creators.erase("is snared");
            creators.erase("is bleeding");
            creators.erase("is stunned");
            creators.erase("is disoriented");
            creators.erase("is possessed");
            creators.erase("is charmed");
            creators.erase("is silenced");

            creators.erase("is polymorphed");
            creators.erase("takes periodic damage");

            creators.erase("party member dead");
            creators.erase("no pet");
            creators.erase("has attackers");
            creators.erase("no possible targets");

            creators.erase("no drink");
            creators.erase("no food");

            creators.erase("mainhand not enhanced");
            creators.erase("offhand not enhanced");

            creators.erase("panic");
            creators.erase("behind target");
            creators.erase("front target");
            creators.erase("not facing target");
            creators.erase("far from master");
            creators.erase("far from loot target");
            creators.erase("can loot");
            creators.erase("swimming");
            creators.erase("target changed");

            creators.erase("enemy rooted");
            creators.erase("enemy frozen");
            creators.erase("enemy snared");
            creators.erase("enemy bleeding");
            creators.erase("enemy stunned");
            creators.erase("enemy polymorphed");
            creators.erase("enemy disoriented");
            creators.erase("enemy possessed");
            creators.erase("enemy charmed");
            creators.erase("enemy silenced");

            creators.erase("party member rooted");
            creators.erase("party member frozen");
            creators.erase("party member snared");
            creators.erase("party member polymorphed");
            creators.erase("party member charmed");
            creators.erase("party member possessed");

            creators.erase("target not rooted");
            creators.erase("target not frozen");
            creators.erase("target not snared");
            creators.erase("target not bleeding");
            creators.erase("target not stunned");

            creators.erase("critical aoe heal");
            creators.erase("low aoe heal");
            creators.erase("medium aoe heal");
            creators.erase("almost full aoe heal");
            creators.erase("invalid target");
            creators.erase("random bot update");
			creators.erase("no non bot players around");

			creators.erase("has no flag");
			creators.erase("in BattleGround");
			creators.erase("in BattleGround without flag");			
        }

    private:
		static Trigger* random_bot_update_trigger(PlayerbotAI* ai) { return new RandomBotUpdateTrigger(ai); }
		static Trigger* no_non_bot_players_around(PlayerbotAI* ai) { return new NoNonBotPlayersAroundTrigger(ai); }
        static Trigger* invalid_target(PlayerbotAI* ai) { return new InvalidTargetTrigger(ai); }
        static Trigger* critical_aoe_heal(PlayerbotAI* ai) { return new AoeHealTrigger(ai, "critical aoe heal", "critical", 2); }
        static Trigger* low_aoe_heal(PlayerbotAI* ai) { return new AoeHealTrigger(ai, "low aoe heal", "low", 2); }
        static Trigger* medium_aoe_heal(PlayerbotAI* ai) { return new AoeHealTrigger(ai, "medium aoe heal", "medium", 2); }
        static Trigger* almost_full_aoe_heal(PlayerbotAI* ai) { return new AoeHealTrigger(ai, "almost full aoe heal", "almost full", 2); }
        static Trigger* target_changed(PlayerbotAI* ai) { return new TargetChangedTrigger(ai); }
        static Trigger* swimming(PlayerbotAI* ai) { return new IsSwimmingTrigger(ai); }
        static Trigger* no_possible_targets(PlayerbotAI* ai) { return new NoPossibleTargetsTrigger(ai); }
        static Trigger* can_loot(PlayerbotAI* ai) { return new CanLootTrigger(ai); }
        static Trigger* far_from_loot_target(PlayerbotAI* ai) { return new FarFromCurrentLootTrigger(ai); }
        static Trigger* far_from_master(PlayerbotAI* ai) { return new FarFromMasterTrigger(ai); }
        static Trigger* behind_target(PlayerbotAI* ai) { return new IsBehindTargetTrigger(ai); }
        static Trigger* front_target(PlayerbotAI* ai) { return new IsFrontTargetTrigger(ai); }
        static Trigger* not_facing_target(PlayerbotAI* ai) { return new IsNotFacingTargetTrigger(ai); }
        static Trigger* panic(PlayerbotAI* ai) { return new PanicTrigger(ai); }
        static Trigger* no_drink(PlayerbotAI* ai) { return new NoDrinkTrigger(ai); }
        static Trigger* no_food(PlayerbotAI* ai) { return new NoFoodTrigger(ai); }
        static Trigger* NoAoe(PlayerbotAI* ai) { return new NoAoeTrigger(ai); }
        static Trigger* LightAoe(PlayerbotAI* ai) { return new LightAoeTrigger(ai); }
        static Trigger* MediumAoe(PlayerbotAI* ai) { return new MediumAoeTrigger(ai); }
        static Trigger* HighAoe(PlayerbotAI* ai) { return new HighAoeTrigger(ai); }
        static Trigger* MeleeNoAoe(PlayerbotAI* ai) { return new MeleeNoAoeTrigger(ai); }
        static Trigger* MeleeLightAoe(PlayerbotAI* ai) { return new MeleeLightAoeTrigger(ai); }
        static Trigger* MeleeMediumAoe(PlayerbotAI* ai) { return new MeleeMediumAoeTrigger(ai); }
        static Trigger* MeleeHighAoe(PlayerbotAI* ai) { return new MeleeHighAoeTrigger(ai); }
        static Trigger* LoseAggro(PlayerbotAI* ai) { return new LoseAggroTrigger(ai); }
        static Trigger* HasAggro(PlayerbotAI* ai) { return new HasAggroTrigger(ai); }
        static Trigger* LowHealth(PlayerbotAI* ai) { return new LowHealthTrigger(ai); }
        static Trigger* MediumHealth(PlayerbotAI* ai) { return new MediumHealthTrigger(ai); }
        static Trigger* AlmostFullHealth(PlayerbotAI* ai) { return new AlmostFullHealthTrigger(ai); }
		static Trigger* FullHealth(PlayerbotAI* ai) { return new FullHealthTrigger(ai); }
        static Trigger* HighHealth(PlayerbotAI* ai) { return new HighHealthTrigger(ai); }
        static Trigger* AlmostDead(PlayerbotAI* ai) { return new AlmostDeadTrigger(ai); }
        static Trigger* CriticalHealth(PlayerbotAI* ai) { return new CriticalHealthTrigger(ai); }
        static Trigger* TargetCriticalHealth(PlayerbotAI* ai) { return new TargetCriticalHealthTrigger(ai); }
        static Trigger* TargetAlmostDead(PlayerbotAI* ai) { return new TargetAlmostDeadTrigger(ai); }
        static Trigger* LowMana(PlayerbotAI* ai) { return new LowManaTrigger(ai); }
        static Trigger* MediumMana(PlayerbotAI* ai) { return new MediumManaTrigger(ai); }
		static Trigger* AlmostFullMana(PlayerbotAI* ai) { return new AlmostFullManaTrigger(ai); }
		static Trigger* AlmostNoMana(PlayerbotAI* ai) { return new AlmostNoManaTrigger(ai); }
		static Trigger* FullMana(PlayerbotAI* ai) { return new FullManaTrigger(ai); }
        static Trigger* DrinkMana(PlayerbotAI* ai) { return new DrinkManaTrigger(ai); }
        static Trigger* LightRageAvailable(PlayerbotAI* ai) { return new LightRageAvailableTrigger(ai); }
        static Trigger* MediumRageAvailable(PlayerbotAI* ai) { return new MediumRageAvailableTrigger(ai); }
        static Trigger* HighRageAvailable(PlayerbotAI* ai) { return new HighRageAvailableTrigger(ai); }
        static Trigger* LightEnergyAvailable(PlayerbotAI* ai) { return new LightEnergyAvailableTrigger(ai); }
        static Trigger* MediumEnergyAvailable(PlayerbotAI* ai) { return new MediumEnergyAvailableTrigger(ai); }
        static Trigger* HighEnergyAvailable(PlayerbotAI* ai) { return new HighEnergyAvailableTrigger(ai); }
        static Trigger* LootAvailable(PlayerbotAI* ai) { return new LootAvailableTrigger(ai); }
        static Trigger* NoAttackers(PlayerbotAI* ai) { return new NoAttackersTrigger(ai); }
        static Trigger* TankAoe(PlayerbotAI* ai) { return new TankAoeTrigger(ai); }
        static Trigger* Timer(PlayerbotAI* ai) { return new TimerTrigger(ai); }
        static Trigger* NoTarget(PlayerbotAI* ai) { return new NoTargetTrigger(ai); }
        static Trigger* TargetInSight(PlayerbotAI* ai) { return new TargetInSightTrigger(ai); }
        static Trigger* not_least_hp_target_active(PlayerbotAI* ai) { return new NotLeastHpTargetActiveTrigger(ai); }
        static Trigger* has_nearest_adds(PlayerbotAI* ai) { return new HasNearestAddsTrigger(ai); }
        static Trigger* has_group_members_near(PlayerbotAI* ai) { return new HasGroupMemberNearTrigger(ai); }
        static Trigger* enemy_player_is_attacking(PlayerbotAI* ai) { return new EnemyPlayerIsAttacking(ai); }
		static Trigger* Random(PlayerbotAI* ai) { return new RandomTrigger(ai, "random", 15); }
		static Trigger* seldom(PlayerbotAI* ai) { return new RandomTrigger(ai, "seldom", 100); }
		static Trigger* often(PlayerbotAI* ai) { return new RandomTrigger(ai, "often", 5); }
		static Trigger* very_often(PlayerbotAI* ai) {return new RandomTrigger(ai, "very often", 2);};
        // static Trigger* TargetOutOfLOS(PlayerbotAI* ai) { return new TargetOutOfLOSSpellTrigger(ai); }
        static Trigger* EnemyOutOfMelee(PlayerbotAI* ai) { return new EnemyOutOfMeleeTrigger(ai); }
        static Trigger* EnemyInMeleeRange(PlayerbotAI* ai) { return new EnemyInMeleeRangeTrigger(ai); }
        static Trigger* EnemyOutOfSpell(PlayerbotAI* ai) { return new EnemyOutOfSpellRangeTrigger(ai); }
		static Trigger* enemy_is_close(PlayerbotAI* ai) { return new EnemyIsCloseTrigger(ai); }
        static Trigger* enemy_too_close_for_spell(PlayerbotAI* ai) { return new EnemyTooCloseForSpellTrigger(ai); }
		static Trigger* enemy_too_close_for_shoot(PlayerbotAI* ai) { return new EnemyTooCloseForShootTrigger(ai); }
        static Trigger* enemy_too_close_for_melee(PlayerbotAI* ai) { return new EnemyTooCloseForMeleeTrigger(ai); }
        static Trigger* ComboPointsAvailable(PlayerbotAI* ai) { return new ComboPointsAvailableTrigger(ai); }
        static Trigger* ComboPointAvailable(PlayerbotAI* ai) { return new ComboPointAvailableTrigger(ai); }
        static Trigger* MediumThreat(PlayerbotAI* ai) { return new MediumThreatTrigger(ai); }
        static Trigger* Dead(PlayerbotAI* ai) { return new DeadTrigger(ai); }
        static Trigger* Mainhand_not_enhanced(PlayerbotAI* ai) { return new MainhandEnhanceTrigger(ai); }
        static Trigger* Offhand_not_enhanced(PlayerbotAI* ai) { return new OffhandEnhanceTrigger(ai); }
        static Trigger* Rooted(PlayerbotAI* ai) { return new RootedTrigger(ai); }
        static Trigger* Frozen(PlayerbotAI* ai) { return new FrozenTrigger(ai); }
        static Trigger* Snared(PlayerbotAI* ai) { return new SnaredTrigger(ai); }
        static Trigger* Bleeding(PlayerbotAI* ai) { return new BleedingTrigger(ai); }
        static Trigger* Stunned(PlayerbotAI* ai) { return new StunnedTrigger(ai); }
        static Trigger* Polymorphed(PlayerbotAI* ai) { return new PolymorphedTrigger(ai); }
        static Trigger* Possessed(PlayerbotAI* ai) { return new PossessedTrigger(ai); }
        static Trigger* Feared(PlayerbotAI* ai) { return new FearedTrigger(ai); }
        static Trigger* Silenced(PlayerbotAI* ai) { return new SilencedTrigger(ai); }
        static Trigger* Disoriented(PlayerbotAI* ai) { return new DisorientedTrigger(ai); }
        static Trigger* Charmed(PlayerbotAI* ai) { return new CharmedTrigger(ai); }
        static Trigger* Target_Rooted(PlayerbotAI* ai) { return new TargetRootedTrigger(ai); }
        static Trigger* Target_Frozen(PlayerbotAI* ai) { return new TargetFrozenTrigger(ai); }
        static Trigger* Target_Snared(PlayerbotAI* ai) { return new TargetSnaredTrigger(ai); }
        static Trigger* Target_Possessed(PlayerbotAI* ai) { return new TargetPossessedTrigger(ai); }
        static Trigger* Target_Charmed(PlayerbotAI* ai) { return new TargetCharmedTrigger(ai); }
        static Trigger* Target_Disoriented(PlayerbotAI* ai) { return new TargetDisorientedTrigger(ai); }
        static Trigger* Target_Bleeding(PlayerbotAI* ai) { return new TargetBleedingTrigger(ai); }
        static Trigger* Target_Stunned(PlayerbotAI* ai) { return new TargetStunnedTrigger(ai); }
        static Trigger* Target_Feared(PlayerbotAI* ai) { return new TargetFearedTrigger(ai); }
        static Trigger* Target_Silenced(PlayerbotAI* ai) { return new TargetSilencedTrigger(ai); }
        static Trigger* Target_Polymorphed(PlayerbotAI* ai) { return new TargetPolymorphedTrigger(ai); }
        static Trigger* Party_Member_Rooted(PlayerbotAI* ai) { return new PartyMemberRootedTrigger(ai); }
        static Trigger* Party_Member_Frozen(PlayerbotAI* ai) { return new PartyMemberFrozenTrigger(ai); }
        static Trigger* Party_Member_Feared(PlayerbotAI* ai) { return new PartyMemberFearedTrigger(ai); }
        static Trigger* Party_Member_Snared(PlayerbotAI* ai) { return new PartyMemberSnaredTrigger(ai); }
        static Trigger* Party_Member_Polymorphed(PlayerbotAI* ai) { return new PartyMemberPolymorphedTrigger(ai); }
        static Trigger* Party_Member_Charmed(PlayerbotAI* ai) { return new PartyMemberCharmedTrigger(ai); }
        static Trigger* Party_Member_Possessed(PlayerbotAI* ai) { return new PartyMemberPossessedTrigger(ai); }
        static Trigger* Target_NotRooted(PlayerbotAI* ai) { return new TargetNotRootedTrigger(ai); }
        static Trigger* Target_NotFrozen(PlayerbotAI* ai) { return new TargetNotFrozenTrigger(ai); }
        static Trigger* Target_NotSnared(PlayerbotAI* ai) { return new TargetNotSnaredTrigger(ai); }
        static Trigger* Target_NotBleeding(PlayerbotAI* ai) { return new TargetNotBleedingTrigger(ai); }
        static Trigger* Target_NotStunned(PlayerbotAI* ai) { return new TargetNotStunnedTrigger(ai); }
        static Trigger* TakesPeriodicDamage(PlayerbotAI* ai) { return new TakesPeriodicDamageTrigger(ai); }
        static Trigger* PartyMemberDead(PlayerbotAI* ai) { return new PartyMemberDeadTrigger(ai); }
        static Trigger* PartyMemberAlmostDead(PlayerbotAI* ai) { return new PartyMemberAlmostDeadTrigger(ai); }
        static Trigger* PartyMemberLowHealth(PlayerbotAI* ai) { return new PartyMemberLowHealthTrigger(ai); }
        static Trigger* PartyMemberMediumHealth(PlayerbotAI* ai) { return new PartyMemberMediumHealthTrigger(ai); }
        static Trigger* PartyMemberHighHealth(PlayerbotAI* ai) { return new PartyMemberHighHealthTrigger(ai); }
        static Trigger* PartyMemberAlmostFullHealth(PlayerbotAI* ai) { return new PartyMemberAlmostFullHealthTrigger(ai); }
        static Trigger* PartyMemberCriticalHealth(PlayerbotAI* ai) { return new PartyMemberCriticalHealthTrigger(ai); }
        static Trigger* MasterAlmostDead(PlayerbotAI* ai) { return new MasterAlmostDeadTrigger(ai); }
        static Trigger* MasterLowHealth(PlayerbotAI* ai) { return new MasterLowHealthTrigger(ai); }
        static Trigger* MasterHighHealth(PlayerbotAI* ai) { return new MasterHighHealthTrigger(ai); }
        static Trigger* MasterAlmostFullHealth(PlayerbotAI* ai) { return new MasterAlmostFullHealthTrigger(ai); }
        static Trigger* MasterCriticalHealth(PlayerbotAI* ai) { return new MasterCriticalHealthTrigger(ai); }
        static Trigger* no_pet(PlayerbotAI* ai) { return new NoPetTrigger(ai); }
        static Trigger* has_attackers(PlayerbotAI* ai) { return new HasAttackersTrigger(ai); }
		static Trigger* player_has_no_flag(PlayerbotAI* ai) { return new PlayerHasNoFlag(ai); }
		static Trigger* player_is_in_BattleGround(PlayerbotAI *ai) { return new PlayerIsInBattleGround(ai); }
		static Trigger* player_is_in_BattleGround_no_flag(PlayerbotAI *ai) { return new PlayerIsInBattleGroundWithoutFlag(ai); }

    };
};
