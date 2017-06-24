#include "../../../botpch.h"
#include "../../playerbot.h"
#include "PaladinActions.h"
#include "PaladinTriggers.h"
#include "PaladinAiObjectContext.h"
#include "GenericPaladinNonCombatStrategy.h"
#include "TankPaladinStrategy.h"
#include "DpsPaladinStrategy.h"
#include "HealPaladinStrategy.h"
#include "PaladinBuffStrategies.h"
#include "../NamedObjectContext.h"

using namespace ai;

namespace ai
{
    namespace paladin
    {
        using namespace ai;

        class StrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["nc"] = &paladin::StrategyFactoryInternal::nc;
				creators["cure"] = &paladin::StrategyFactoryInternal::cure;
            }
			~StrategyFactoryInternal()
			{
				creators.erase("nc");
				creators.erase("cure");
			}

        private:
            static Strategy* nc(PlayerbotAI* ai) { return new GenericPaladinNonCombatStrategy(ai); }
			static Strategy* cure(PlayerbotAI* ai) { return new PaladinCureStrategy(ai); }
        };

        class ResistanceStrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            ResistanceStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
            {
                creators["rshadow"] = &paladin::ResistanceStrategyFactoryInternal::rshadow;
                creators["rfrost"] = &paladin::ResistanceStrategyFactoryInternal::rfrost;
                creators["rfire"] = &paladin::ResistanceStrategyFactoryInternal::rfire;
            }
			~ResistanceStrategyFactoryInternal()
			{
				creators.erase("rshadow");
				creators.erase("rfrost");
				creators.erase("rfire");
			}

        private:
            static Strategy* rshadow(PlayerbotAI* ai) { return new PaladinShadowResistanceStrategy(ai); }
            static Strategy* rfrost(PlayerbotAI* ai) { return new PaladinFrostResistanceStrategy(ai); }
            static Strategy* rfire(PlayerbotAI* ai) { return new PaladinFireResistanceStrategy(ai); }
        };

        class BuffStrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            BuffStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
            {
                creators["bhealth"] = &paladin::BuffStrategyFactoryInternal::bhealth;
                creators["bmana"] = &paladin::BuffStrategyFactoryInternal::bmana;
                creators["bdps"] = &paladin::BuffStrategyFactoryInternal::bdps;
                creators["barmor"] = &paladin::BuffStrategyFactoryInternal::barmor;
                creators["bspeed"] = &paladin::BuffStrategyFactoryInternal::bspeed;
				creators["bthreat"] = &paladin::BuffStrategyFactoryInternal::bthreat;
            }
			~BuffStrategyFactoryInternal()
			{
				creators.erase("bhealth");
				creators.erase("bmana");
				creators.erase("bdps");
				creators.erase("barmor");
				creators.erase("bspeed");
				creators.erase("bthreat");
			}

        private:
            static Strategy* bhealth(PlayerbotAI* ai) { return new PaladinBuffHealthStrategy(ai); }
            static Strategy* bmana(PlayerbotAI* ai) { return new PaladinBuffManaStrategy(ai); }
            static Strategy* bdps(PlayerbotAI* ai) { return new PaladinBuffDpsStrategy(ai); }
            static Strategy* barmor(PlayerbotAI* ai) { return new PaladinBuffArmorStrategy(ai); }
            static Strategy* bspeed(PlayerbotAI* ai) { return new PaladinBuffSpeedStrategy(ai); }
			static Strategy* bthreat(PlayerbotAI* ai) { return new PaladinBuffThreatStrategy(ai); }
        };

        class CombatStrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            CombatStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
            {
                creators["tank"] = &paladin::CombatStrategyFactoryInternal::tank;
                creators["dps"] = &paladin::CombatStrategyFactoryInternal::dps;
                creators["melee heal"] = &paladin::CombatStrategyFactoryInternal::melee_heal;
                creators["heal"] = &paladin::CombatStrategyFactoryInternal::heal;
            }

        private:
            static Strategy* tank(PlayerbotAI* ai) { return new TankPaladinStrategy(ai); }
            static Strategy* dps(PlayerbotAI* ai) { return new DpsPaladinStrategy(ai); }
            static Strategy* heal(PlayerbotAI* ai) { return new HealPaladinStrategy(ai); }
            static Strategy* melee_heal(PlayerbotAI* ai) { return new MeleeHealPaladinStrategy(ai);}
        };
    };
};

namespace ai
{
    namespace paladin
    {
        using namespace ai;

        class TriggerFactoryInternal : public NamedObjectContext<Trigger>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["judgement of wisdom"] = &TriggerFactoryInternal::judgement_of_wisdom;
                creators["judgement of light"] = &TriggerFactoryInternal::judgement_of_light;
                creators["blessing"] = &TriggerFactoryInternal::blessing;
                creators["seal"] = &TriggerFactoryInternal::seal;
                creators["seal mana"] = &TriggerFactoryInternal::seal_mana;
                creators["seal health"] = &TriggerFactoryInternal::seal_health;
                creators["art of war"] = &TriggerFactoryInternal::art_of_war;
				creators["blessing on party"] = &TriggerFactoryInternal::blessing_on_party;                
                creators["beacon of light on master"] = &TriggerFactoryInternal::beacon_of_light_on_master;
                creators["crusader aura"] = &TriggerFactoryInternal::crusader_aura;
                creators["retribution aura"] = &TriggerFactoryInternal::retribution_aura;
                creators["devotion aura"] = &TriggerFactoryInternal::devotion_aura;
                creators["shadow resistance aura"] = &TriggerFactoryInternal::shadow_resistance_aura;
                creators["frost resistance aura"] = &TriggerFactoryInternal::frost_resistance_aura;
                creators["fire resistance aura"] = &TriggerFactoryInternal::fire_resistance_aura;
                creators["hammer of justice snare"] = &TriggerFactoryInternal::hammer_of_justice_snare;
                creators["hammer of justice interrupt"] = &TriggerFactoryInternal::hammer_of_justice_interrupt;
                creators["cleanse cure disease"] = &TriggerFactoryInternal::CleanseCureDisease;
                creators["cleanse party member cure disease"] = &TriggerFactoryInternal::CleanseCurePartyMemberDisease;
                creators["cleanse cure poison"] = &TriggerFactoryInternal::CleanseCurePoison;
                creators["cleanse party member cure poison"] = &TriggerFactoryInternal::CleanseCurePartyMemberPoison;
                creators["cleanse cure magic"] = &TriggerFactoryInternal::CleanseCureMagic;
                creators["cleanse party member cure magic"] = &TriggerFactoryInternal::CleanseCurePartyMemberMagic;
                creators["righteous fury"] = &TriggerFactoryInternal::righteous_fury;
                creators["holy shield"] = &TriggerFactoryInternal::holy_shield;
                creators["hammer of justice on enemy healer"] = &TriggerFactoryInternal::hammer_of_justice_on_enemy_target;
                creators["repentance"] = &TriggerFactoryInternal::repentance;
            }

        private:
            static Trigger* holy_shield(PlayerbotAI* ai) { return new HolyShieldTrigger(ai); }
            static Trigger* righteous_fury(PlayerbotAI* ai) { return new RighteousFuryTrigger(ai); }
            static Trigger* judgement_of_wisdom(PlayerbotAI* ai) { return new JudgementOfWisdomTrigger(ai); }
            static Trigger* judgement_of_light(PlayerbotAI* ai) { return new JudgementOfLightTrigger(ai); }
            static Trigger* blessing(PlayerbotAI* ai) { return new BlessingTrigger(ai); }
            static Trigger* seal(PlayerbotAI* ai) { return new SealTrigger(ai); }
            static Trigger* seal_health(PlayerbotAI* ai) { return new SealLowTrigger(ai); }
            static Trigger* seal_mana(PlayerbotAI* ai) { return new SealManaLowTrigger(ai); }
            static Trigger* art_of_war(PlayerbotAI* ai) { return new ArtOfWarTrigger(ai); }
			static Trigger* blessing_on_party(PlayerbotAI* ai) { return new BlessingOnPartyTrigger(ai); }
            static Trigger* beacon_of_light_on_master(PlayerbotAI* ai) { return new BeaconOfLightOnMasterTrigger(ai); }
            static Trigger* crusader_aura(PlayerbotAI* ai) { return new CrusaderAuraTrigger(ai); }
            static Trigger* retribution_aura(PlayerbotAI* ai) { return new RetributionAuraTrigger(ai); }
            static Trigger* devotion_aura(PlayerbotAI* ai) { return new DevotionAuraTrigger(ai); }
            static Trigger* shadow_resistance_aura(PlayerbotAI* ai) { return new ShadowResistanceAuraTrigger(ai); }
            static Trigger* frost_resistance_aura(PlayerbotAI* ai) { return new FrostResistanceAuraTrigger(ai); }
            static Trigger* fire_resistance_aura(PlayerbotAI* ai) { return new FireResistanceAuraTrigger(ai); }
            static Trigger* hammer_of_justice_snare(PlayerbotAI* ai) { return new HammerOfJusticeSnareTrigger(ai); }
            static Trigger* hammer_of_justice_interrupt(PlayerbotAI* ai) { return new HammerOfJusticeInterruptSpellTrigger(ai); }
            static Trigger* CleanseCureDisease(PlayerbotAI* ai) { return new CleanseCureDiseaseTrigger(ai); }
            static Trigger* CleanseCurePartyMemberDisease(PlayerbotAI* ai) { return new CleanseCurePartyMemberDiseaseTrigger(ai); }
            static Trigger* CleanseCurePoison(PlayerbotAI* ai) { return new CleanseCurePoisonTrigger(ai); }
            static Trigger* CleanseCurePartyMemberPoison(PlayerbotAI* ai) { return new CleanseCurePartyMemberPoisonTrigger(ai); }
            static Trigger* CleanseCureMagic(PlayerbotAI* ai) { return new CleanseCureMagicTrigger(ai); }
            static Trigger* CleanseCurePartyMemberMagic(PlayerbotAI* ai) { return new CleanseCurePartyMemberMagicTrigger(ai); }
            static Trigger* hammer_of_justice_on_enemy_target(PlayerbotAI* ai) { return new HammerOfJusticeEnemyHealerTrigger(ai); }
            static Trigger* repentance(PlayerbotAI* ai) {return new  RepentanceTrigger(ai);}
        };
    };
};

namespace ai
{
    namespace paladin
    {
        using namespace ai;

        class AiObjectContextInternal : public NamedObjectContext<Action>
        {
        public:
            AiObjectContextInternal()
            {
                creators["seal of command"] = &AiObjectContextInternal::seal_of_command;
                creators["seal of vengeance"] = &AiObjectContextInternal::seal_of_vengeance;
                creators["blessing of might"] = &AiObjectContextInternal::blessing_of_might;
                creators["blessing of wisdom"] = &AiObjectContextInternal::blessing_of_wisdom;
				creators["blessing of kings"] = &AiObjectContextInternal::blessing_of_kings;
				creators["blessing of sanctuary"] = &AiObjectContextInternal::blessing_of_sanctuary;
                creators["divine storm"] = &AiObjectContextInternal::divine_storm;
                creators["blessing of kings on party"] = &AiObjectContextInternal::blessing_of_kings_on_party;
                creators["blessing of wisdom on party"] = &AiObjectContextInternal::blessing_of_wisdom_on_party;
				creators["blessing of might on party"] = &AiObjectContextInternal::blessing_of_might_on_party;
                creators["redemption"] = &AiObjectContextInternal::redemption;
                creators["crusader strike"] = &AiObjectContextInternal::crusader_strike;
                creators["crusader aura"] = &AiObjectContextInternal::crusader_aura;
                creators["seal of light"] = &AiObjectContextInternal::seal_of_light;
                creators["devotion aura"] = &AiObjectContextInternal::devotion_aura;
                creators["holy wrath"] = &AiObjectContextInternal::holy_wrath;
                creators["consecration"] = &AiObjectContextInternal::consecration;
                creators["cleanse disease"] = &AiObjectContextInternal::cleanse_disease;
                creators["cleanse poison"] = &AiObjectContextInternal::cleanse_poison;
                creators["cleanse magic"] = &AiObjectContextInternal::cleanse_magic;
                creators["purify disease"] = &AiObjectContextInternal::purify_disease;
                creators["purify poison"] = &AiObjectContextInternal::purify_poison;
                creators["cleanse poison on party"] = &AiObjectContextInternal::cleanse_poison_on_party;
                creators["cleanse disease on party"] = &AiObjectContextInternal::cleanse_disease_on_party;
                creators["cleanse magic on party"] = &AiObjectContextInternal::cleanse_magic_on_party;
                creators["purify poison on party"] = &AiObjectContextInternal::purify_poison_on_party;
                creators["purify disease on party"] = &AiObjectContextInternal::purify_disease_on_party;
                creators["seal of wisdom"] = &AiObjectContextInternal::seal_of_wisdom;
                creators["seal of justice"] = &AiObjectContextInternal::seal_of_justice;
                creators["seal of righteousness"] = &AiObjectContextInternal::seal_of_righteousness;
                creators["urgent heal"] = &AiObjectContextInternal::flash_of_light;
                creators["flash of light"] = &AiObjectContextInternal::flash_of_light;
                creators["instant flash of light"] = &AiObjectContextInternal::instant_flash_of_light;
                creators["hand of reckoning"] = &AiObjectContextInternal::hand_of_reckoning;
                creators["avenger's shield"] = &AiObjectContextInternal::avengers_shield;
                creators["exorcism"] = &AiObjectContextInternal::exorcism;
                creators["exorcism heal"] = &AiObjectContextInternal::exorcism_heal;
                creators["instant exorcism"] = &AiObjectContextInternal::instant_exorcism;
                creators["judgement of light"] = &AiObjectContextInternal::judgement_of_light;
                creators["judgement of wisdom"] = &AiObjectContextInternal::judgement_of_wisdom;
                creators["ranged judgement of light"] = &AiObjectContextInternal::ranged_judgement_of_light;
                creators["ranged judgement of wisdom"] = &AiObjectContextInternal::ranged_judgement_of_wisdom;
                creators["divine shield"] = &AiObjectContextInternal::divine_shield;
                creators["divine protection"] = &AiObjectContextInternal::divine_protection;
                creators["divine protection on party"] =&AiObjectContextInternal::divine_protection_on_party;
                creators["divine protection on master"] =&AiObjectContextInternal::divine_protection_on_master;
                creators["hammer of justice"] = &AiObjectContextInternal::hammer_of_justice;
                creators["flash of light on party"] = &AiObjectContextInternal::flash_of_light_on_party;
                creators["flash of light on master"] = &AiObjectContextInternal::flash_of_light_on_master;
                creators["instant flash of light on party"] = &AiObjectContextInternal::instant_flash_of_light_on_party;
                creators["instant flash of light on master"] = &AiObjectContextInternal::instant_flash_of_light_on_master;
                creators["holy light"] = &AiObjectContextInternal::holy_light;
                creators["holy light on party"] = &AiObjectContextInternal::holy_light_on_party;
                creators["holy light on master"] = &AiObjectContextInternal::holy_light_on_master;
                creators["lay on hands"] = &AiObjectContextInternal::lay_on_hands;
                creators["lay on hands on party"] = &AiObjectContextInternal::lay_on_hands_on_party;
                creators["lay on hands on master"] = &AiObjectContextInternal::lay_on_hands_on_master;
                creators["judgement of justice"] = &AiObjectContextInternal::judgement_of_justice;
                creators["hammer of wrath"] = &AiObjectContextInternal::hammer_of_wrath;
                creators["holy shield"] = &AiObjectContextInternal::holy_shield;
                creators["hammer of the righteous"] = &AiObjectContextInternal::hammer_of_the_righteous;
                creators["retribution aura"] = &AiObjectContextInternal::retribution_aura;
                creators["shadow resistance aura"] = &AiObjectContextInternal::shadow_resistance_aura;
                creators["frost resistance aura"] = &AiObjectContextInternal::frost_resistance_aura;
                creators["fire resistance aura"] = &AiObjectContextInternal::fire_resistance_aura;
                creators["righteous fury"] = &AiObjectContextInternal::righteous_fury;
                creators["hammer of justice on enemy healer"] = &AiObjectContextInternal::hammer_of_justice_on_enemy_healer;
                creators["holy shock"] = &AiObjectContextInternal::holy_shock;
                creators["holy shock on party"] = &AiObjectContextInternal::holy_shock_on_party;
                creators["holy shock on master"] = &AiObjectContextInternal::holy_shock_on_master;
                creators["holy shock on attacker"] = &AiObjectContextInternal::holy_shock_on_attacker;
                creators["divine plea"] = &AiObjectContextInternal::divine_plea;
                creators["divine favor"] = &AiObjectContextInternal::divine_favor;
                creators["divine illumination"] = &AiObjectContextInternal::divine_illumination;
                creators["aura mastery"] = &AiObjectContextInternal::aura_mastery;
                creators["beacon of light on party"] = &AiObjectContextInternal::beacon_of_light_on_party;
                creators["hand of sacrifice on party"] = &AiObjectContextInternal::hand_of_sacrifice_on_party;
                creators["hand of salvation on party"] = &AiObjectContextInternal::hand_of_salvation_on_party;
                creators["hand of sacrifice on master"] = &AiObjectContextInternal::hand_of_sacrifice_on_master;
                creators["hand of salvation on master"] = &AiObjectContextInternal::hand_of_salvation_on_master;
                creators["hand of freedom on party"] = &AiObjectContextInternal::hand_of_freedom_on_party;
                creators["hand of protection on party"] = &AiObjectContextInternal::hand_of_protection_on_party;
                creators["hand of protection on master"] = &AiObjectContextInternal::hand_of_protection_on_master;
                creators["hand of freedom"] = &AiObjectContextInternal::hand_of_freedom;
                creators["avenging wrath"] = &AiObjectContextInternal::avenging_wrath;
                creators["sacred shield on party"] = &AiObjectContextInternal::hand_of_salvation_on_party;
                creators["sacred shield on master"] = &AiObjectContextInternal::hand_of_salvation_on_master;
            }

        private:
            static Action* righteous_fury(PlayerbotAI* ai) { return new CastRighteousFuryAction(ai); }            
            static Action* seal_of_command(PlayerbotAI* ai) { return new CastSealOfCommandAction(ai); }
            static Action* seal_of_vengeance(PlayerbotAI* ai) { return new CastSealOfVengeanceAction(ai); }
			static Action* blessing_of_sanctuary(PlayerbotAI* ai) { return new CastBlessingOfSanctuaryAction(ai); }			
            static Action* blessing_of_might(PlayerbotAI* ai) { return new CastBlessingOfMightAction(ai); }
            static Action* blessing_of_wisdom(PlayerbotAI* ai) { return new CastBlessingOfWisdomAction(ai); }
			static Action* blessing_of_kings(PlayerbotAI* ai) { return new CastBlessingOfKingsAction(ai); }
            static Action* divine_storm(PlayerbotAI* ai) { return new CastDivineStormAction(ai); }
            static Action* blessing_of_kings_on_party(PlayerbotAI* ai) { return new CastBlessingOfKingsOnPartyAction(ai); }
            static Action* blessing_of_wisdom_on_party(PlayerbotAI* ai) { return new CastBlessingOfWisdomOnPartyAction(ai); }
			static Action* blessing_of_might_on_party(PlayerbotAI* ai) { return new CastBlessingOfMightOnPartyAction(ai); }
			static Action* redemption(PlayerbotAI* ai) { return new CastRedemptionAction(ai); }
            static Action* crusader_strike(PlayerbotAI* ai) { return new CastCrusaderStrikeAction(ai); }
            static Action* crusader_aura(PlayerbotAI* ai) { return new CastCrusaderAuraAction(ai); }
            static Action* seal_of_light(PlayerbotAI* ai) { return new CastSealOfLightAction(ai); }
            static Action* devotion_aura(PlayerbotAI* ai) { return new CastDevotionAuraAction(ai); }
            static Action* holy_wrath(PlayerbotAI* ai) { return new CastHolyWrathAction(ai); }
            static Action* consecration(PlayerbotAI* ai) { return new CastConsecrationAction(ai); }
            static Action* cleanse_poison(PlayerbotAI* ai) { return new CastCleansePoisonAction(ai); }
            static Action* cleanse_disease(PlayerbotAI* ai) { return new CastCleanseDiseaseAction(ai); }
            static Action* cleanse_magic(PlayerbotAI* ai) { return new CastCleanseMagicAction(ai); }
            static Action* purify_poison(PlayerbotAI* ai) { return new CastPurifyPoisonAction(ai); }
            static Action* purify_disease(PlayerbotAI* ai) { return new CastPurifyDiseaseAction(ai); }
            static Action* cleanse_poison_on_party(PlayerbotAI* ai) { return new CastCleansePoisonOnPartyAction(ai); }
            static Action* cleanse_disease_on_party(PlayerbotAI* ai) { return new CastCleanseDiseaseOnPartyAction(ai); }
            static Action* cleanse_magic_on_party(PlayerbotAI* ai) { return new CastCleanseMagicOnPartyAction(ai); }
            static Action* purify_poison_on_party(PlayerbotAI* ai) { return new CastPurifyPoisonOnPartyAction(ai); }
            static Action* purify_disease_on_party(PlayerbotAI* ai) { return new CastPurifyDiseaseOnPartyAction(ai); }
            static Action* seal_of_wisdom(PlayerbotAI* ai) { return new CastSealOfWisdomAction(ai); }
            static Action* seal_of_justice(PlayerbotAI* ai) { return new CastSealOfJusticeAction(ai); }
            static Action* seal_of_righteousness(PlayerbotAI* ai) { return new CastSealOfRighteousnessAction(ai); }
            static Action* flash_of_light(PlayerbotAI* ai) { return new CastFlashOfLightAction(ai); }
            static Action* instant_flash_of_light(PlayerbotAI* ai) { return new CastInstantFlashOfLightAction(ai); }
            static Action* hand_of_reckoning(PlayerbotAI* ai) { return new CastHandOfReckoningAction(ai); }
            static Action* avengers_shield(PlayerbotAI* ai) { return new CastAvengersShieldAction(ai); }
            static Action* exorcism(PlayerbotAI* ai) { return new CastExorcismAction(ai); }
            static Action* exorcism_heal(PlayerbotAI* ai) { return new CastExorcismHealAction(ai); }
            static Action* instant_exorcism(PlayerbotAI* ai) { return new CastInstantExorcismAction(ai); }
            static Action* judgement_of_light(PlayerbotAI* ai) { return new CastJudgementOfLightAction(ai); }
            static Action* judgement_of_wisdom(PlayerbotAI* ai) { return new CastJudgementOfWisdomAction(ai); }
            static Action* ranged_judgement_of_light(PlayerbotAI* ai) { return new CastRangedJudgementOfLightAction(ai); }
            static Action* ranged_judgement_of_wisdom(PlayerbotAI* ai) { return new CastRangedJudgementOfWisdomAction(ai); }
            static Action* divine_shield(PlayerbotAI* ai) { return new CastDivineShieldAction(ai); }
            static Action* divine_protection(PlayerbotAI* ai) { return new CastDivineProtectionAction(ai); }
            static Action* divine_protection_on_party(PlayerbotAI* ai) { return new CastDivineProtectionOnPartyAction(ai); }
            static Action* divine_protection_on_master(PlayerbotAI* ai) { return new CastDivineProtectionOnMasterAction(ai); }
            static Action* hammer_of_justice(PlayerbotAI* ai) { return new CastHammerOfJusticeAction(ai); }
            static Action* flash_of_light_on_party(PlayerbotAI* ai) { return new CastFlashOfLightOnPartyAction(ai); }
            static Action* instant_flash_of_light_on_party(PlayerbotAI* ai) { return new CastInstantFlashOfLightOnPartyAction(ai); }
            static Action* flash_of_light_on_master(PlayerbotAI* ai) { return new CastFlashOfLightOnMasterAction(ai); }
            static Action* instant_flash_of_light_on_master(PlayerbotAI* ai) { return new CastInstantFlashOfLightOnMasterAction(ai); }
            static Action* holy_light(PlayerbotAI* ai) { return new CastHolyLightAction(ai); }
            static Action* holy_light_on_party(PlayerbotAI* ai) { return new CastHolyLightOnPartyAction(ai); }
            static Action* holy_light_on_master(PlayerbotAI* ai) { return new CastHolyLightOnMasterAction(ai); }
            static Action* lay_on_hands(PlayerbotAI* ai) { return new CastLayOnHandsAction(ai); }
            static Action* lay_on_hands_on_party(PlayerbotAI* ai) { return new CastLayOnHandsOnPartyAction(ai); }
            static Action* lay_on_hands_on_master(PlayerbotAI* ai) { return new CastLayOnHandsOnMasterAction(ai); }
            static Action* judgement_of_justice(PlayerbotAI* ai) { return new CastJudgementOfJusticeAction(ai); }
            static Action* hammer_of_wrath(PlayerbotAI* ai) { return new CastHammerOfWrathAction(ai); }
            static Action* holy_shield(PlayerbotAI* ai) { return new CastHolyShieldAction(ai); }
            static Action* hammer_of_the_righteous(PlayerbotAI* ai) { return new CastHammerOfTheRighteousAction(ai); }            
            static Action* retribution_aura(PlayerbotAI* ai) { return new CastRetributionAuraAction(ai); }
            static Action* shadow_resistance_aura(PlayerbotAI* ai) { return new CastShadowResistanceAuraAction(ai); }
            static Action* frost_resistance_aura(PlayerbotAI* ai) { return new CastFrostResistanceAuraAction(ai); }
            static Action* fire_resistance_aura(PlayerbotAI* ai) { return new CastFireResistanceAuraAction(ai); }
            static Action* hammer_of_justice_on_enemy_healer(PlayerbotAI* ai) { return new CastHammerOfJusticeOnEnemyHealerAction(ai); }
            static Action* holy_shock(PlayerbotAI* ai) { return new CastHolyShockAction(ai); }
            static Action* holy_shock_on_party(PlayerbotAI* ai) { return new CastHolyShockOnPartyAction(ai); }
            static Action* holy_shock_on_master(PlayerbotAI* ai) { return new CastHolyShockOnMasterAction(ai); }
            static Action* holy_shock_on_attacker(PlayerbotAI* ai) { return new CastHolyShockOnAttackerAction(ai); }
            static Action* divine_plea(PlayerbotAI* ai) { return new CastDivinePleaAction(ai); }
            static Action* divine_favor(PlayerbotAI* ai) { return new CastDivineFavorAction(ai); }
            static Action* aura_mastery(PlayerbotAI* ai) { return new CastAuraMasteryAction(ai); }
            static Action* divine_illumination(PlayerbotAI* ai) { return new CastDivineIlluminationAction(ai); }
            static Action* beacon_of_light_on_party(PlayerbotAI* ai) { return new CastBeaconOfLightActionOnParty(ai); }
            static Action* hand_of_protection_on_party(PlayerbotAI* ai) { return new CastHandOfProtectionOnPartyAction(ai); }
            static Action* hand_of_sacrifice_on_party(PlayerbotAI* ai) { return new CastHandOfSacrificeOnPartyAction(ai); }
            static Action* hand_of_salvation_on_party(PlayerbotAI* ai) { return new CastHandOfSalvationOnPartyAction(ai); }
            static Action* beacon_of_light_on_master(PlayerbotAI* ai) { return new CastBeaconOfLightActionOnMaster(ai); }
            static Action* hand_of_protection_on_master(PlayerbotAI* ai) { return new CastHandOfProtectionOnMasterAction(ai); }
            static Action* hand_of_sacrifice_on_master(PlayerbotAI* ai) { return new CastHandOfSacrificeOnMasterAction(ai); }
            static Action* hand_of_salvation_on_master(PlayerbotAI* ai) { return new CastHandOfSalvationOnMasterAction(ai); }
            static Action* sacred_shield_on_party(PlayerbotAI* ai) { return new CastSacredShieldOnPartyAction(ai); }
            static Action* sacred_shield_on_master(PlayerbotAI* ai) { return new CastSacredShieldOnMasterAction(ai); }
            static Action* hand_of_freedom(PlayerbotAI* ai) { return new CastHandOfFreedomAction(ai); }
            static Action* hand_of_freedom_on_party(PlayerbotAI* ai) { return new CastHandOfFreedomOnPartyAction(ai); }
            static Action* avenging_wrath(PlayerbotAI* ai) { return new CastAvengingWrathAction(ai); }
        };
    };
};


PaladinAiObjectContext::PaladinAiObjectContext(PlayerbotAI* ai) : AiObjectContext(ai)
{
    strategyContexts.Add(new ai::paladin::StrategyFactoryInternal());
    strategyContexts.Add(new ai::paladin::CombatStrategyFactoryInternal());
    strategyContexts.Add(new ai::paladin::BuffStrategyFactoryInternal());
    strategyContexts.Add(new ai::paladin::ResistanceStrategyFactoryInternal());
    actionContexts.Add(new ai::paladin::AiObjectContextInternal());
    triggerContexts.Add(new ai::paladin::TriggerFactoryInternal());
}
