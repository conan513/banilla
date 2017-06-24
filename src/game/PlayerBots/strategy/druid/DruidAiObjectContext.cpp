#include "../../../botpch.h"
#include "../../playerbot.h"
#include "DruidActions.h"
#include "DruidAiObjectContext.h"
#include "BearTankDruidStrategy.h"
#include "CatDpsDruidStrategy.h"
#include "CasterDruidStrategy.h"
#include "GenericDruidNonCombatStrategy.h"
#include "../NamedObjectContext.h"
#include "DruidTriggers.h"
#include "HealDruidStrategy.h"

using namespace ai;

namespace ai
{
    namespace druid
    {
        using namespace ai;

        class StrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["nc"] = &druid::StrategyFactoryInternal::nc;
                creators["stealth"] = &druid::StrategyFactoryInternal::nc_stealth;                
                creators["caster aoe"] = &druid::StrategyFactoryInternal::caster_aoe;
                creators["caster debuff"] = &druid::StrategyFactoryInternal::caster_debuff;
                creators["dps debuff"] = &druid::StrategyFactoryInternal::caster_debuff;
				creators["cure"] = &druid::StrategyFactoryInternal::cure;
            }
			~StrategyFactoryInternal()
			{
				creators.erase("nc");
				creators.erase("stealth");
				creators.erase("caster aoe");
				creators.erase("caster debuff");
				creators.erase("dps debuff");
				creators.erase("cure");
			}

        private:
            static Strategy* nc(PlayerbotAI* ai) { return new GenericDruidNonCombatStrategy(ai); }
            static Strategy* nc_stealth(PlayerbotAI* ai) { return new GenericDruidStealthStrategy(ai); }
            static Strategy* cat_aoe(PlayerbotAI* ai) { return new CatAoeDruidStrategy(ai); }
            static Strategy* caster_aoe(PlayerbotAI* ai) { return new CasterDruidAoeStrategy(ai); }
            static Strategy* caster_debuff(PlayerbotAI* ai) { return new CasterDruidDebuffStrategy(ai); }
			static Strategy* cure(PlayerbotAI* ai) { return new DruidCureStrategy(ai); }
        };

        class DruidStrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            DruidStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
            {
                creators["bear"] = &druid::DruidStrategyFactoryInternal::bear;
                creators["tank"] = &druid::DruidStrategyFactoryInternal::bear;
                creators["cat"] = &druid::DruidStrategyFactoryInternal::cat;
                creators["caster"] = &druid::DruidStrategyFactoryInternal::caster;
                creators["dps"] = &druid::DruidStrategyFactoryInternal::cat;
                creators["heal"] = &druid::DruidStrategyFactoryInternal::heal;
            }

        private:
            static Strategy* bear(PlayerbotAI* ai) { return new BearTankDruidStrategy(ai); }
            static Strategy* cat(PlayerbotAI* ai) { return new CatDpsDruidStrategy(ai); }
            static Strategy* caster(PlayerbotAI* ai) { return new CasterDruidStrategy(ai); }
            static Strategy* heal(PlayerbotAI* ai) { return new HealDruidStrategy(ai); }
        };
    };
};

namespace ai
{
    namespace druid
    {
        using namespace ai;

        class TriggerFactoryInternal : public NamedObjectContext<Trigger>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["thorns"] = &TriggerFactoryInternal::Thorns;
                creators["thorns on party"] = &TriggerFactoryInternal::Thorns_on_party;
                creators["bash"] = &TriggerFactoryInternal::bash;
                creators["faerie fire (feral)"] = &TriggerFactoryInternal::faerie_fire_feral;
                creators["faerie fire"] = &TriggerFactoryInternal::faerie_fire;
                creators["insect swarm"] = &TriggerFactoryInternal::insect_swarm;
                creators["moonfire"] = &TriggerFactoryInternal::moonfire;
                creators["nature's grasp"] = &TriggerFactoryInternal::natures_grasp;
                creators["tiger's fury"] = &TriggerFactoryInternal::tigers_fury;
                creators["rake"] = &TriggerFactoryInternal::rake;
                creators["mark of the wild"] = &TriggerFactoryInternal::mark_of_the_wild;
                creators["mark of the wild on party"] = &TriggerFactoryInternal::mark_of_the_wild_on_party;
                creators["cure poison"] = &TriggerFactoryInternal::cure_poison;
                creators["party member cure poison"] = &TriggerFactoryInternal::party_member_cure_poison;
                creators["entangling roots"] = &TriggerFactoryInternal::entangling_roots;
                creators["hibernate"] = &TriggerFactoryInternal::hibernate;
                creators["bear form"] = &TriggerFactoryInternal::bear_form;
                creators["cat form"] = &TriggerFactoryInternal::cat_form;
                creators["tree form"] = &TriggerFactoryInternal::tree_form;
                creators["moonkin form"] = &TriggerFactoryInternal::moonkin_form;
//                creators["caster form"] = &TriggerFactoryInternal::caster_form;
                creators["eclipse (solar)"] = &TriggerFactoryInternal::eclipse_solar;
                creators["eclipse (lunar)"] = &TriggerFactoryInternal::eclipse_lunar;
                creators["bash on enemy healer"] = &TriggerFactoryInternal::bash_on_enemy_healer;
                creators["prowl"] = &TriggerFactoryInternal::prowl;
                creators["savage roar"] = &TriggerFactoryInternal::savage_roar;
                creators["rip"] = &TriggerFactoryInternal::rip;
                creators["pounce"] = &TriggerFactoryInternal::pounce;
                creators["predator's swiftness"] = &TriggerFactoryInternal::predatory_swiftness;
                creators["dash"] = &TriggerFactoryInternal::dash;
            }

        private:
            static Trigger* eclipse_solar(PlayerbotAI* ai) { return new EclipseSolarTrigger(ai); }
            static Trigger* eclipse_lunar(PlayerbotAI* ai) { return new EclipseLunarTrigger(ai); }
            static Trigger* Thorns(PlayerbotAI* ai) { return new ThornsTrigger(ai); }
            static Trigger* Thorns_on_party(PlayerbotAI* ai) { return new ThornsOnPartyTrigger(ai); }
            static Trigger* bash(PlayerbotAI* ai) { return new BashInterruptSpellTrigger(ai); }
            static Trigger* faerie_fire_feral(PlayerbotAI* ai) { return new FaerieFireFeralTrigger(ai); }
            static Trigger* insect_swarm(PlayerbotAI* ai) { return new InsectSwarmTrigger(ai); }
            static Trigger* moonfire(PlayerbotAI* ai) { return new MoonfireTrigger(ai); }
            static Trigger* faerie_fire(PlayerbotAI* ai) { return new FaerieFireTrigger(ai); }
            static Trigger* natures_grasp(PlayerbotAI* ai) { return new NaturesGraspTrigger(ai); }
            static Trigger* tigers_fury(PlayerbotAI* ai) { return new TigersFuryTrigger(ai); }
            static Trigger* rake(PlayerbotAI* ai) { return new RakeTrigger(ai); }
            static Trigger* mark_of_the_wild(PlayerbotAI* ai) { return new MarkOfTheWildTrigger(ai); }
            static Trigger* mark_of_the_wild_on_party(PlayerbotAI* ai) { return new MarkOfTheWildOnPartyTrigger(ai); }
            static Trigger* cure_poison(PlayerbotAI* ai) { return new CurePoisonTrigger(ai); }
            static Trigger* party_member_cure_poison(PlayerbotAI* ai) { return new PartyMemberCurePoisonTrigger(ai); }
            static Trigger* entangling_roots(PlayerbotAI* ai) { return new EntanglingRootsTrigger(ai); }
            static Trigger* hibernate(PlayerbotAI* ai) { return new HibernateTrigger(ai); }
            static Trigger* bear_form(PlayerbotAI* ai) { return new BearFormTrigger(ai); }
            static Trigger* cat_form(PlayerbotAI* ai) { return new CatFormTrigger(ai); }
            static Trigger* tree_form(PlayerbotAI* ai) { return new TreeFormTrigger(ai); }
            static Trigger* moonkin_form(PlayerbotAI* ai) { return new MoonkinFormTrigger(ai); }
//            static Trigger* caster_form(PlayerbotAI* ai) { return new CasterFormTrigger(ai); }
            static Trigger* bash_on_enemy_healer(PlayerbotAI* ai) { return new BashInterruptEnemyHealerSpellTrigger(ai); }
            static Trigger* prowl(PlayerbotAI* ai) { return new ProwlTrigger(ai); }
            static Trigger* savage_roar(PlayerbotAI* ai) { return new SavageRoarTrigger(ai); }
            static Trigger* rip(PlayerbotAI* ai) { return new RipTrigger(ai); }
            static Trigger* pounce(PlayerbotAI* ai) { return new PounceTrigger(ai); }
            static Trigger* predatory_swiftness(PlayerbotAI* ai) { return new PredatorySwiftnessTrigger(ai); }
            static Trigger* dash(PlayerbotAI* ai) { return new DashTrigger(ai); }
        };
    };
};

namespace ai
{
    namespace druid
    {
        using namespace ai;

        class AiObjectContextInternal : public NamedObjectContext<Action>
        {
        public:
            AiObjectContextInternal()
            {
                creators["feral charge - bear"] = &AiObjectContextInternal::feral_charge_bear;
                creators["feral charge - cat"] = &AiObjectContextInternal::feral_charge_cat;
                creators["swipe (bear)"] = &AiObjectContextInternal::swipe_bear;
                creators["faerie fire (feral)"] = &AiObjectContextInternal::faerie_fire_feral;
                creators["faerie fire"] = &AiObjectContextInternal::faerie_fire;
                creators["bear form"] = &AiObjectContextInternal::bear_form;
                creators["dire bear form"] = &AiObjectContextInternal::dire_bear_form;
                creators["moonkin form"] = &AiObjectContextInternal::moonkin_form;
                creators["cat form"] = &AiObjectContextInternal::cat_form;
                creators["tree form"] = &AiObjectContextInternal::tree_form;
                creators["caster form"] = &AiObjectContextInternal::caster_form;
                creators["mangle (bear)"] = &AiObjectContextInternal::mangle_bear;
                creators["maul"] = &AiObjectContextInternal::maul;
                creators["bash"] = &AiObjectContextInternal::bash;
                creators["swipe"] = &AiObjectContextInternal::swipe;
                creators["growl"] = &AiObjectContextInternal::growl;
                creators["demoralizing roar"] = &AiObjectContextInternal::demoralizing_roar;
                creators["hibernate"] = &AiObjectContextInternal::hibernate;
                creators["hibernate on cc"] = &AiObjectContextInternal::hibernate_on_cc;
                creators["entangling roots"] = &AiObjectContextInternal::entangling_roots;
                creators["entangling roots on cc"] = &AiObjectContextInternal::entangling_roots_on_cc;
                creators["wrath"] = &AiObjectContextInternal::wrath;
                creators["wrath heal"] = &AiObjectContextInternal::wrath_heal;
                creators["starfall"] = &AiObjectContextInternal::starfall;
                creators["insect swarm"] = &AiObjectContextInternal::insect_swarm;
                creators["moonfire"] = &AiObjectContextInternal::moonfire;
                creators["moonfire heal"] = &AiObjectContextInternal::moonfire_heal;
                creators["starfire"] = &AiObjectContextInternal::starfire;
                creators["nature's grasp"] = &AiObjectContextInternal::natures_grasp;
                creators["typhoon"] = &AiObjectContextInternal::typhoon;
                creators["force of nature"] = &AiObjectContextInternal::force_of_nature;
                creators["claw"] = &AiObjectContextInternal::claw;
                creators["mangle (cat)"] = &AiObjectContextInternal::mangle_cat;
                creators["swipe (cat)"] = &AiObjectContextInternal::swipe_cat;
                creators["rake"] = &AiObjectContextInternal::rake;
                creators["ferocious bite"] = &AiObjectContextInternal::ferocious_bite;
                creators["rip"] = &AiObjectContextInternal::rip;
                creators["cower"] = &AiObjectContextInternal::cower;
                creators["prowl"] = &AiObjectContextInternal::prowl;
                creators["prepare attack"] = &AiObjectContextInternal::prowl;
                creators["ravage"] = &AiObjectContextInternal::ravage;
                creators["pounce"] = &AiObjectContextInternal::pounce;
                creators["shred"] = &AiObjectContextInternal::shred;
                creators["dash"] = &AiObjectContextInternal::dash;
                creators["berserk"] = &AiObjectContextInternal::berserk;
                creators["boost"] = &AiObjectContextInternal::boost_action;
                creators["savage roar"] = &AiObjectContextInternal::savage_roar;
                creators["survival instincts"] = &AiObjectContextInternal::survival_instincts;
                creators["thorns"] = &AiObjectContextInternal::thorns;
                creators["thorns on party"] = &AiObjectContextInternal::thorns_on_party;
                creators["thorns on master"] = &AiObjectContextInternal::thorns_on_master;
                creators["cure poison"] = &AiObjectContextInternal::cure_poison;
                creators["cure poison on party"] = &AiObjectContextInternal::cure_poison_on_party;
                creators["abolish poison"] = &AiObjectContextInternal::abolish_poison;
                creators["abolish poison on party"] = &AiObjectContextInternal::abolish_poison_on_party;
                creators["berserk"] = &AiObjectContextInternal::berserk_action;
                creators["tiger's fury"] = &AiObjectContextInternal::tigers_fury;
                creators["mark of the wild"] = &AiObjectContextInternal::mark_of_the_wild;
                creators["mark of the wild on party"] = &AiObjectContextInternal::mark_of_the_wild_on_party;
                creators["regrowth"] = &AiObjectContextInternal::regrowth;
                creators["urgent heal"] = &AiObjectContextInternal::regrowth;
                creators["wild growth"] = &AiObjectContextInternal::wild_growth;
                creators["nourish"] = &AiObjectContextInternal::nourish;
                creators["lifebloom"] = &AiObjectContextInternal::lifebloom;
                creators["swiftmend"] = &AiObjectContextInternal::swiftmend;
                creators["nature's swiftness"] = &AiObjectContextInternal::natures_swiftness;
                creators["nature's swiftness on master"] = &AiObjectContextInternal::natures_swiftness_on_master;
                creators["nature's swiftness on party"] = &AiObjectContextInternal::natures_swiftness_on_party;
                creators["rejuvenation"] = &AiObjectContextInternal::rejuvenation;
                creators["healing touch"] = &AiObjectContextInternal::healing_touch;
                creators["regrowth on party"] = &AiObjectContextInternal::regrowth_on_party;
                creators["rejuvenation on party"] = &AiObjectContextInternal::rejuvenation_on_party;
                creators["healing touch on party"] = &AiObjectContextInternal::healing_touch_on_party;
                creators["instant regrowth"] = &AiObjectContextInternal::instant_regrowth;
                creators["instant healing touch"] = &AiObjectContextInternal::instant_healing_touch;
                creators["instant regrowth on party"] = &AiObjectContextInternal::instant_regrowth_on_party;
                creators["instant healing touch on party"] = &AiObjectContextInternal::instant_healing_touch_on_party;
                creators["wild growth on party"] = &AiObjectContextInternal::wild_growth_on_party;
                creators["nourish on party"] = &AiObjectContextInternal::nourish_on_party;
                creators["lifebloom on party"] = &AiObjectContextInternal::lifebloom_on_party;
                creators["swiftmend on party"] = &AiObjectContextInternal::swiftmend_on_party;
                creators["regrowth on master"] = &AiObjectContextInternal::regrowth_on_master;
                creators["rejuvenation on master"] = &AiObjectContextInternal::rejuvenation_on_master;
                creators["healing touch on master"] = &AiObjectContextInternal::healing_touch_on_master;
                creators["instant regrowth on master"] = &AiObjectContextInternal::instant_regrowth_on_master;
                creators["instant healing touch on master"] = &AiObjectContextInternal::instant_healing_touch_on_master;
                creators["wild growth on master"] = &AiObjectContextInternal::wild_growth_on_master;
                creators["nourish on master"] = &AiObjectContextInternal::nourish_on_master;
                creators["lifebloom on master"] = &AiObjectContextInternal::lifebloom_on_master;
                creators["swiftmend on master"] = &AiObjectContextInternal::swiftmend_on_master;
                creators["rebirth"] = &AiObjectContextInternal::rebirth;
                creators["revive"] = &AiObjectContextInternal::revive;
                creators["barkskin"] = &AiObjectContextInternal::barkskin;
                creators["lacerate"] = &AiObjectContextInternal::lacerate;
                creators["hurricane"] = &AiObjectContextInternal::hurricane;
                creators["innervate"] = &AiObjectContextInternal::innervate;
                creators["tranquility"] = &AiObjectContextInternal::tranquility;
                creators["bash on enemy healer"] = &AiObjectContextInternal::bash_on_enemy_healer;
            }

        private:
            static Action* tranquility(PlayerbotAI* ai) { return new CastTranquilityAction(ai); }
            static Action* feral_charge_bear(PlayerbotAI* ai) { return new CastFeralChargeBearAction(ai); }
            static Action* feral_charge_cat(PlayerbotAI* ai) { return new CastFeralChargeCatAction(ai); }
            static Action* swipe_bear(PlayerbotAI* ai) { return new CastSwipeBearAction(ai); }
            static Action* faerie_fire_feral(PlayerbotAI* ai) { return new CastFaerieFireFeralAction(ai); }
            static Action* faerie_fire(PlayerbotAI* ai) { return new CastFaerieFireAction(ai); }
            static Action* bear_form(PlayerbotAI* ai) { return new CastBearFormAction(ai); }
            static Action* dire_bear_form(PlayerbotAI* ai) { return new CastDireBearFormAction(ai); }
            static Action* cat_form(PlayerbotAI* ai) { return new CastCatFormAction(ai); }
            static Action* tree_form(PlayerbotAI* ai) { return new CastTreeFormAction(ai); }
            static Action* caster_form(PlayerbotAI* ai) { return new CastCasterFormAction(ai); }
            static Action* mangle_bear(PlayerbotAI* ai) { return new CastMangleBearAction(ai); }
            static Action* maul(PlayerbotAI* ai) { return new CastMaulAction(ai); }
            static Action* bash(PlayerbotAI* ai) { return new CastBashAction(ai); }
            static Action* swipe(PlayerbotAI* ai) { return new CastSwipeAction(ai); }
            static Action* growl(PlayerbotAI* ai) { return new CastGrowlAction(ai); }
            static Action* demoralizing_roar(PlayerbotAI* ai) { return new CastDemoralizingRoarAction(ai); }
            static Action* moonkin_form(PlayerbotAI* ai) { return new CastMoonkinFormAction(ai); }
            static Action* hibernate(PlayerbotAI* ai) { return new CastHibernateAction(ai); }
            static Action* hibernate_on_cc(PlayerbotAI* ai) { return new CastHibernateCcAction(ai); }
            static Action* entangling_roots(PlayerbotAI* ai) { return new CastEntanglingRootsAction(ai); }
            static Action* entangling_roots_on_cc(PlayerbotAI* ai) { return new CastEntanglingRootsCcAction(ai); }
            static Action* wrath(PlayerbotAI* ai) { return new CastWrathAction(ai); }
            static Action* wrath_heal(PlayerbotAI* ai) { return new CastWrathHealAction(ai); }
            static Action* starfall(PlayerbotAI* ai) { return new CastStarfallAction(ai); }
            static Action* force_of_nature(PlayerbotAI* ai) { return new CastForceofNatureAction(ai); }
            static Action* typhoon(PlayerbotAI* ai) { return new CastTyphoonAction(ai); }
            static Action* insect_swarm(PlayerbotAI* ai) { return new CastInsectSwarmAction(ai); }
            static Action* moonfire(PlayerbotAI* ai) { return new CastMoonfireAction(ai); }
            static Action* moonfire_heal(PlayerbotAI* ai) { return new CastMoonfireHealAction(ai); }
            static Action* starfire(PlayerbotAI* ai) { return new CastStarfireAction(ai); }
            static Action* natures_grasp(PlayerbotAI* ai) { return new CastNaturesGraspAction(ai); }
            static Action* claw(PlayerbotAI* ai) { return new CastClawAction(ai); }
            static Action* mangle_cat(PlayerbotAI* ai) { return new CastMangleCatAction(ai); }
            static Action* swipe_cat(PlayerbotAI* ai) { return new CastSwipeCatAction(ai); }
            static Action* rake(PlayerbotAI* ai) { return new CastRakeAction(ai); }
            static Action* ferocious_bite(PlayerbotAI* ai) { return new CastFerociousBiteAction(ai); }
            static Action* rip(PlayerbotAI* ai) { return new CastRipAction(ai); }
            static Action* cower(PlayerbotAI* ai) { return new CastCowerAction(ai); }
            static Action* prowl(PlayerbotAI* ai) { return new CastProwlAction(ai); }
            static Action* ravage(PlayerbotAI* ai) { return new CastRavageAction(ai); }
            static Action* pounce(PlayerbotAI* ai) { return new CastPounceAction(ai); }
            static Action* shred(PlayerbotAI* ai) { return new CastShredAction(ai); }
            static Action* savage_roar(PlayerbotAI* ai) { return new CastSavageRoarAction(ai); }
            static Action* dash(PlayerbotAI* ai) { return new CastDashAction(ai); }
            static Action* berserk_action(PlayerbotAI* ai) { return new CastBerserkAction(ai); }
            static Action* boost_action(PlayerbotAI* ai) { return new CastBoostAction(ai); }
            static Action* survival_instincts(PlayerbotAI* ai) { return new CastSurvivalInstinctsAction(ai); }
            static Action* thorns(PlayerbotAI* ai) { return new CastThornsAction(ai); }
            static Action* thorns_on_party(PlayerbotAI* ai) { return new CastThornsOnPartyAction(ai); }
            static Action* thorns_on_master(PlayerbotAI* ai) { return new CastThornsOnMasterAction(ai); }
            static Action* cure_poison(PlayerbotAI* ai) { return new CastCurePoisonAction(ai); }
            static Action* cure_poison_on_party(PlayerbotAI* ai) { return new CastCurePoisonOnPartyAction(ai); }
            static Action* abolish_poison(PlayerbotAI* ai) { return new CastAbolishPoisonAction(ai); }
            static Action* abolish_poison_on_party(PlayerbotAI* ai) { return new CastAbolishPoisonOnPartyAction(ai); }
            static Action* berserk(PlayerbotAI* ai) { return new CastBerserkAction(ai); }
            static Action* tigers_fury(PlayerbotAI* ai) { return new CastTigersFuryAction(ai); }
            static Action* mark_of_the_wild(PlayerbotAI* ai) { return new CastMarkOfTheWildAction(ai); }
            static Action* mark_of_the_wild_on_party(PlayerbotAI* ai) { return new CastMarkOfTheWildOnPartyAction(ai); }
            static Action* regrowth(PlayerbotAI* ai) { return new CastRegrowthAction(ai); }
            static Action* rejuvenation(PlayerbotAI* ai) { return new CastRejuvenationAction(ai); }
            static Action* healing_touch(PlayerbotAI* ai) { return new CastHealingTouchAction(ai); }
            static Action* nourish(PlayerbotAI* ai) { return new CastNourishAction(ai); }
            static Action* lifebloom(PlayerbotAI* ai) { return new CastLifeBloomAction(ai); }
            static Action* swiftmend(PlayerbotAI* ai) { return new CastSwiftmendAction(ai); }
            static Action* wild_growth(PlayerbotAI* ai) { return new CastWildGrowthAction(ai); }
            static Action* natures_swiftness(PlayerbotAI* ai) { return new CastNaturesSwiftnessAction(ai); }
            static Action* natures_swiftness_on_party(PlayerbotAI* ai) { return new CastNaturesSwiftnessOnPartyAction(ai); }
            static Action* natures_swiftness_on_master(PlayerbotAI* ai) { return new CastNaturesSwiftnessOnMasterAction(ai); }
            static Action* regrowth_on_party(PlayerbotAI* ai) { return new CastRegrowthOnPartyAction(ai); }
            static Action* nourish_on_party(PlayerbotAI* ai) { return new CastNourishOnPartyAction(ai); }
            static Action* lifebloom_on_party(PlayerbotAI* ai) { return new CastLifebloomOnPartyAction(ai); }
            static Action* swiftmend_on_party(PlayerbotAI* ai) { return new CastSwiftmendOnPartyAction(ai); }
            static Action* wild_growth_on_party(PlayerbotAI* ai) { return new CastWildGrowthOnPartyAction(ai); }
            static Action* rejuvenation_on_party(PlayerbotAI* ai) { return new CastRejuvenationOnPartyAction(ai); }
            static Action* healing_touch_on_party(PlayerbotAI* ai) { return new CastHealingTouchOnPartyAction(ai); }
            static Action* instant_regrowth(PlayerbotAI* ai) { return new CastInstantRegrowthAction(ai); }
            static Action* instant_healing_touch(PlayerbotAI* ai) { return new CastInstantHealingTouchAction(ai); }
            static Action* instant_healing_touch_on_party(PlayerbotAI* ai) { return new CastInstantHealingTouchOnPartyAction(ai); }
            static Action* instant_regrowth_on_party(PlayerbotAI* ai) { return new CastInstantRegrowthOnPartyAction(ai); }
            static Action* regrowth_on_master(PlayerbotAI* ai) { return new CastRegrowthOnMasterAction(ai); }
            static Action* nourish_on_master(PlayerbotAI* ai) { return new CastNourishOnMasterAction(ai); }
            static Action* lifebloom_on_master(PlayerbotAI* ai) { return new CastLifebloomOnMasterAction(ai); }
            static Action* swiftmend_on_master(PlayerbotAI* ai) { return new CastSwiftmendOnMasterAction(ai); }
            static Action* wild_growth_on_master(PlayerbotAI* ai) { return new CastWildGrowthOnMasterAction(ai); }
            static Action* rejuvenation_on_master(PlayerbotAI* ai) { return new CastRejuvenationOnMasterAction(ai); }
            static Action* healing_touch_on_master(PlayerbotAI* ai) { return new CastHealingTouchOnMasterAction(ai); }
            static Action* instant_healing_touch_on_master(PlayerbotAI* ai) { return new CastInstantHealingTouchOnMasterAction(ai); }
            static Action* instant_regrowth_on_master(PlayerbotAI* ai) { return new CastInstantRegrowthOnMasterAction(ai); }
            static Action* rebirth(PlayerbotAI* ai) { return new CastRebirthAction(ai); }
            static Action* revive(PlayerbotAI* ai) { return new CastReviveAction(ai); }
            static Action* barkskin(PlayerbotAI* ai) { return new CastBarkskinAction(ai); }
            static Action* lacerate(PlayerbotAI* ai) { return new CastLacerateAction(ai); }
            static Action* hurricane(PlayerbotAI* ai) { return new CastHurricaneAction(ai); }
            static Action* innervate(PlayerbotAI* ai) { return new CastInnervateAction(ai); }
            static Action* bash_on_enemy_healer(PlayerbotAI* ai) { return new CastBashOnEnemyHealerAction(ai); }
        };
    };
};

DruidAiObjectContext::DruidAiObjectContext(PlayerbotAI* ai) : AiObjectContext(ai)
{
    strategyContexts.Add(new ai::druid::StrategyFactoryInternal());
    strategyContexts.Add(new ai::druid::DruidStrategyFactoryInternal());
    actionContexts.Add(new ai::druid::AiObjectContextInternal());
    triggerContexts.Add(new ai::druid::TriggerFactoryInternal());
}
