#include "../../../botpch.h"
#include "../../playerbot.h"
#include "PriestActions.h"
#include "PriestAiObjectContext.h"
#include "PriestNonCombatStrategy.h"
#include "ShadowPriestStrategy.h"
#include "../generic/PullStrategy.h"
#include "PriestTriggers.h"
#include "../NamedObjectContext.h"
#include "HolyPriestStrategy.h"

using namespace ai;


namespace ai
{
    namespace priest
    {
        using namespace ai;

        class StrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["nc"] = &priest::StrategyFactoryInternal::nc;
                creators["pull"] = &priest::StrategyFactoryInternal::pull;
                creators["dps debuff"] = &priest::StrategyFactoryInternal::shadow_debuff;
                creators["shadow debuff"] = &priest::StrategyFactoryInternal::shadow_debuff;
				creators["cure"] = &priest::StrategyFactoryInternal::cure;
            }
            ~StrategyFactoryInternal()
            {
                creators.erase("nc");
                creators.erase("pull");
                creators.erase("dps debuff");
                creators.erase("shadow debuff");
				creators.erase("cure");
            }

        private:
            static Strategy* nc(PlayerbotAI* ai) { return new PriestNonCombatStrategy(ai); }
            static Strategy* pull(PlayerbotAI* ai) { return new PullStrategy(ai, "shoot"); }
            static Strategy* shadow_debuff(PlayerbotAI* ai) { return new ShadowPriestDebuffStrategy(ai); }
			static Strategy* cure(PlayerbotAI* ai) { return new PriestCureStrategy(ai); }
        };

        class CombatStrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            CombatStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
            {
                creators["heal"] = &priest::CombatStrategyFactoryInternal::heal;
                creators["shadow"] = &priest::CombatStrategyFactoryInternal::dps;
                creators["dps"] = &priest::CombatStrategyFactoryInternal::dps;
                creators["holy"] = &priest::CombatStrategyFactoryInternal::holy;
                creators["holy dps"] = &priest::CombatStrategyFactoryInternal::holy_dps;
            }
            ~CombatStrategyFactoryInternal()
            {
                creators.erase("heal");
                creators.erase("shadow");
                creators.erase("dps");
                creators.erase("holy");
                creators.erase("holy dps");
            }

        private:
            static Strategy* heal(PlayerbotAI* ai) { return new HealPriestStrategy(ai); }
            static Strategy* dps(PlayerbotAI* ai) { return new ShadowPriestStrategy(ai); }
            static Strategy* holy(PlayerbotAI* ai) { return new HolyPriestStrategy(ai); }
            static Strategy* holy_dps(PlayerbotAI* ai) { return new DpsHolyPriestStrategy(ai); }
        };
    };
};

namespace ai
{
    namespace priest
    {
        using namespace ai;

        class TriggerFactoryInternal : public NamedObjectContext<Trigger>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["devouring plague"] = &TriggerFactoryInternal::devouring_plague;
                creators["shadow word: pain"] = &TriggerFactoryInternal::shadow_word_pain;
                creators["shadow word: pain on attacker"] = &TriggerFactoryInternal::shadow_word_pain_on_attacker;
                creators["dispel magic"] = &TriggerFactoryInternal::dispel_magic;
                creators["dispel magic on party"] = &TriggerFactoryInternal::dispel_magic_party_member;
                creators["cure disease"] = &TriggerFactoryInternal::cure_disease;
                creators["party member cure disease"] = &TriggerFactoryInternal::party_member_cure_disease;
                creators["power word: fortitude"] = &TriggerFactoryInternal::power_word_fortitude;
                creators["power word: fortitude on party"] = &TriggerFactoryInternal::power_word_fortitude_on_party;
                creators["prayer of shadow protection"] = &TriggerFactoryInternal::power_word_fortitude;
                creators["prayer of shadow protection on party"] = &TriggerFactoryInternal::prayer_of_shadow_protection_on_party;
                creators["divine spirit"] = &TriggerFactoryInternal::divine_spirit;
                creators["divine spirit on party"] = &TriggerFactoryInternal::divine_spirit_on_party;
                creators["inner fire"] = &TriggerFactoryInternal::inner_fire;
                creators["fear ward"] = &TriggerFactoryInternal::fear_ward;
                creators["fear ward on master"] = &TriggerFactoryInternal::fear_ward_on_master;
                creators["vampiric touch"] = &TriggerFactoryInternal::vampiric_touch;
                creators["shadowform"] = &TriggerFactoryInternal::shadowform;
                creators["vampiric embrace"] = &TriggerFactoryInternal::vampiric_embrace;
                creators["surge of light"] = &TriggerFactoryInternal::surge_of_light;
                creators["silence on enemy healer"] = &TriggerFactoryInternal::silence_enemy_healer;
                creators["shackle undead"] = &TriggerFactoryInternal::shackle_undead;
            }
            ~TriggerFactoryInternal()
            {
                creators.erase("devouring plague");
                creators.erase("shadow word: pain");
                creators.erase("shadow word: pain on attacker");
                creators.erase("dispel magic");
                creators.erase("dispel magic on party");
                creators.erase("cure disease");
                creators.erase("party member cure disease");
                creators.erase("power word: fortitude");
                creators.erase("power word: fortitude on party");
                creators.erase("prayer of shadow protection");
                creators.erase("prayer of shadow protection on party");
                creators.erase("divine spirit");
                creators.erase("divine spirit on party");
                creators.erase("inner fire");
                creators.erase("fear ward");
                creators.erase("fear ward on master");
                creators.erase("vampiric touch");
                creators.erase("shadowform");
                creators.erase("vampiric embrace");
                creators.erase("surge of light");
                creators.erase("silence on enemy healer");
                creators.erase("shackle undead");
            }

        private:
            static Trigger* vampiric_embrace(PlayerbotAI* ai) { return new VampiricEmbraceTrigger(ai); }
            static Trigger* shadowform(PlayerbotAI* ai) { return new ShadowformTrigger(ai); }
            static Trigger* vampiric_touch(PlayerbotAI* ai) { return new VampiricTouchTrigger(ai); }
            static Trigger* devouring_plague(PlayerbotAI* ai) { return new DevouringPlagueTrigger(ai); }
            static Trigger* shadow_word_pain(PlayerbotAI* ai) { return new PowerWordPainTrigger(ai); }
            static Trigger* shadow_word_pain_on_attacker(PlayerbotAI* ai) { return new PowerWordPainOnAttackerTrigger(ai); }
            static Trigger* dispel_magic(PlayerbotAI* ai) { return new DispelMagicTrigger(ai); }
            static Trigger* dispel_magic_party_member(PlayerbotAI* ai) { return new DispelMagicPartyMemberTrigger(ai); }
            static Trigger* cure_disease(PlayerbotAI* ai) { return new CureDiseaseTrigger(ai); }
            static Trigger* party_member_cure_disease(PlayerbotAI* ai) { return new PartyMemberCureDiseaseTrigger(ai); }
            static Trigger* power_word_fortitude(PlayerbotAI* ai) { return new PowerWordFortitudeTrigger(ai); }
            static Trigger* power_word_fortitude_on_party(PlayerbotAI* ai) { return new PowerWordFortitudeOnPartyTrigger(ai); }
            static Trigger* prayer_of_shadow_protection(PlayerbotAI* ai) { return new PrayerOfShadowProtectionTrigger(ai); }
            static Trigger* prayer_of_shadow_protection_on_party(PlayerbotAI* ai) { return new PrayerOfShadowProtectionOnPartyTrigger(ai); }
            static Trigger* divine_spirit(PlayerbotAI* ai) { return new DivineSpiritTrigger(ai); }
            static Trigger* divine_spirit_on_party(PlayerbotAI* ai) { return new DivineSpiritOnPartyTrigger(ai); }
            static Trigger* inner_fire(PlayerbotAI* ai) { return new InnerFireTrigger(ai); }
            static Trigger* fear_ward(PlayerbotAI* ai) { return new FearWardTrigger(ai); }
            static Trigger* fear_ward_on_master(PlayerbotAI* ai) { return new FearWardOnMasterTrigger(ai); }
            static Trigger* surge_of_light(PlayerbotAI* ai) { return new SurgeOfLightTrigger(ai); }
            static Trigger* shackle_undead(PlayerbotAI* ai) { return new ShackleUndeadTrigger(ai); }
            static Trigger* silence_enemy_healer(PlayerbotAI* ai) { return new SilenceEnemyHealerTrigger(ai); }
        };
    };
};



namespace ai
{
    namespace priest
    {
        using namespace ai;

        class AiObjectContextInternal : public NamedObjectContext<Action>
        {
        public:
            AiObjectContextInternal()
            {
                creators["shadow word: pain"] = &AiObjectContextInternal::shadow_word_pain;
                creators["shadow word: pain on attacker"] = &AiObjectContextInternal::shadow_word_pain_on_attacker;
                creators["devouring plague"] = &AiObjectContextInternal::devouring_plague;
                creators["mind flay"] = &AiObjectContextInternal::mind_flay;
                creators["holy fire"] = &AiObjectContextInternal::holy_fire;
                creators["smite"] = &AiObjectContextInternal::smite;
                creators["mind blast"] = &AiObjectContextInternal::mind_blast;
                creators["mind shear"] = &AiObjectContextInternal::mind_shear;
                creators["shadowform"] = &AiObjectContextInternal::shadowform;
                creators["remove shadowform"] = &AiObjectContextInternal::remove_shadowform;
                creators["holy nova"] = &AiObjectContextInternal::holy_nova;
                creators["holy nova aoe"] = &AiObjectContextInternal::holy_nova_aoe;
                creators["power word: fortitude"] = &AiObjectContextInternal::power_word_fortitude;
                creators["power word: fortitude on party"] = &AiObjectContextInternal::power_word_fortitude_on_party;
                creators["divine spirit"] = &AiObjectContextInternal::divine_spirit;
                creators["divine spirit on party"] = &AiObjectContextInternal::divine_spirit_on_party;
                creators["power word: shield"] = &AiObjectContextInternal::power_word_shield;
                creators["power word: shield on party"] = &AiObjectContextInternal::power_word_shield_on_party;
                creators["power word: shield on master"] = &AiObjectContextInternal::power_word_shield_on_master;
                creators["prepare attack"] = &AiObjectContextInternal::power_word_shield_on_master;
                creators["renew"] = &AiObjectContextInternal::renew;
                creators["renew on party"] = &AiObjectContextInternal::renew_on_party;
                creators["renew on master"] = &AiObjectContextInternal::renew_on_master;
                creators["greater heal"] = &AiObjectContextInternal::greater_heal;
                creators["greater heal on party"] = &AiObjectContextInternal::greater_heal_on_party;
                creators["greater heal on master"] = &AiObjectContextInternal::greater_heal_on_master;
                creators["heal"] = &AiObjectContextInternal::heal;
                creators["heal on party"] = &AiObjectContextInternal::heal_on_party;
                creators["heal on master"] = &AiObjectContextInternal::heal_on_master;
                creators["lesser heal"] = &AiObjectContextInternal::lesser_heal;
                creators["lesser heal on party"] = &AiObjectContextInternal::lesser_heal_on_party;
                creators["lesser heal on master"] = &AiObjectContextInternal::lesser_heal_on_master;
                creators["flash heal"] = &AiObjectContextInternal::flash_heal;
                creators["urgent heal"] = &AiObjectContextInternal::flash_heal;
                creators["flash heal on party"] = &AiObjectContextInternal::flash_heal_on_party;
                creators["flash heal on master"] = &AiObjectContextInternal::flash_heal_on_master;
                creators["dispel magic"] = &AiObjectContextInternal::dispel_magic;
                creators["dispel magic on party"] = &AiObjectContextInternal::dispel_magic_on_party;
                creators["dispel magic on target"] = &AiObjectContextInternal::dispel_magic_on_target;
                creators["cure disease"] = &AiObjectContextInternal::cure_disease;
                creators["cure disease on party"] = &AiObjectContextInternal::cure_disease_on_party;
                creators["abolish disease"] = &AiObjectContextInternal::abolish_disease;
                creators["abolish disease on party"] = &AiObjectContextInternal::abolish_disease_on_party;
                creators["fade"] = &AiObjectContextInternal::fade;
                creators["inner fire"] = &AiObjectContextInternal::inner_fire;
                creators["resurrection"] = &AiObjectContextInternal::resurrection;
                creators["circle of healing"] = &AiObjectContextInternal::circle_of_healing;
                creators["psychic scream"] = &AiObjectContextInternal::psychic_scream;
                creators["psychic horror"] = &AiObjectContextInternal::psychic_horror;
                creators["vampiric touch"] = &AiObjectContextInternal::vampiric_touch;
                creators["vampiric embrace"] = &AiObjectContextInternal::vampiric_embrace;
                creators["dispersion"] = &AiObjectContextInternal::dispersion;
                creators["prayer of healing"] = &AiObjectContextInternal::prayer_of_healing;
                creators["prayer of mending"] = &AiObjectContextInternal::prayer_of_healing;
                creators["prayer of mending on party"] = &AiObjectContextInternal::prayer_of_mending_on_party;
                creators["prayer of mending on master"] = &AiObjectContextInternal::prayer_of_mending_on_master;
                creators["binding heal on party"] = &AiObjectContextInternal::binding_heal_on_party;
                creators["penance on attacker"] = &AiObjectContextInternal::penance_on_attacker;
                creators["penance"] = &AiObjectContextInternal::penance;
                creators["penance on party"] = &AiObjectContextInternal::penance_on_party;
                creators["penance on master"] = &AiObjectContextInternal::penance_on_master;
                creators["pain suppression"] = &AiObjectContextInternal::pain_suppression;
                creators["pain suppression on party"] = &AiObjectContextInternal::pain_suppression_on_party;
                creators["pain suppression on master"] = &AiObjectContextInternal::pain_suppression_on_master;
                creators["guardian spirit"] = &AiObjectContextInternal::guardian_spirit;
                creators["guardian spirit on party"] = &AiObjectContextInternal::guardian_spirit_on_party;
                creators["guardian spirit on master"] = &AiObjectContextInternal::guardian_spirit_on_master;
                creators["power infusion"] = &AiObjectContextInternal::power_infusion;
                creators["power infusion on party"] = &AiObjectContextInternal::power_infusion_on_party;
                creators["shadowfiend"] = &AiObjectContextInternal::shadowfiend;
                creators["power word: death"] = &AiObjectContextInternal::power_word_death;
                creators["finish target"] = &AiObjectContextInternal::power_word_death;
                creators["prayer of shadow protection"] = &AiObjectContextInternal::prayer_of_shadow_protection;
                creators["prayer of shadow protection on party"] = &AiObjectContextInternal::prayer_of_shadow_protection_on_party;
                creators["inner focus"] = &AiObjectContextInternal::inner_focus;
                creators["fear ward"] = &AiObjectContextInternal::fear_ward;
                creators["fear ward on party"] = &AiObjectContextInternal::fear_ward_on_party;
                creators["fear ward on master"] = &AiObjectContextInternal::fear_ward_on_master;
                creators["desperate prayer"] = &AiObjectContextInternal::desperate_prayer;
                creators["divine hymn"] = &AiObjectContextInternal::divine_hymn;
                creators["hymn of hope"] = &AiObjectContextInternal::hymn_of_hope;
                creators["instant action"] = &AiObjectContextInternal::shadow_word_pain_on_attacker;
            }
            ~AiObjectContextInternal()
            {
                creators.erase("shadow word: pain");
                creators.erase("shadow word: pain on attacker");
                creators.erase("devouring plague");
                creators.erase("mind flay");
                creators.erase("holy fire");
                creators.erase("smite");
                creators.erase("mind blast");
                creators.erase("mind shear");
                creators.erase("shadowform");
                creators.erase("remove shadowform");
                creators.erase("holy nova");
                creators.erase("holy nova aoe");
                creators.erase("power word: fortitude");
                creators.erase("power word: fortitude on party");
                creators.erase("divine spirit");
                creators.erase("divine spirit on party");
                creators.erase("power word: shield");
                creators.erase("power word: shield on party");
                creators.erase("power word: shield on master");
                creators.erase("prepare attack");
                creators.erase("renew");
                creators.erase("renew on party");
                creators.erase("renew on master");
                creators.erase("greater heal");
                creators.erase("greater heal on party");
                creators.erase("greater heal on master");
                creators.erase("heal");
                creators.erase("heal on party");
                creators.erase("heal on master");
                creators.erase("lesser heal");
                creators.erase("lesser heal on party");
                creators.erase("lesser heal on master");
                creators.erase("flash heal");
                creators.erase("urgent heal");
                creators.erase("flash heal on party");
                creators.erase("flash heal on master");
                creators.erase("dispel magic");
                creators.erase("dispel magic on party");
                creators.erase("dispel magic on target");
                creators.erase("cure disease");
                creators.erase("cure disease on party");
                creators.erase("abolish disease");
                creators.erase("abolish disease on party");
                creators.erase("fade");
                creators.erase("inner fire");
                creators.erase("resurrection");
                creators.erase("circle of healing");
                creators.erase("psychic scream");
                creators.erase("psychic horror");
                creators.erase("vampiric touch");
                creators.erase("vampiric embrace");
                creators.erase("dispersion");
                creators.erase("prayer of healing");
                creators.erase("prayer of mending");
                creators.erase("prayer of mending on party");
                creators.erase("prayer of mending on master");
                creators.erase("binding heal on party");
                creators.erase("penance on attacker");
                creators.erase("penance");
                creators.erase("penance on party");
                creators.erase("penance on master");
                creators.erase("pain suppression");
                creators.erase("pain suppression on party");
                creators.erase("pain suppression on master");
                creators.erase("guardian spirit");
                creators.erase("guardian spirit on party");
                creators.erase("guardian spirit on master");
                creators.erase("power infusion");
                creators.erase("power infusion on party");
                creators.erase("shadowfiend");
                creators.erase("power word: death");
                creators.erase("finish target");
                creators.erase("prayer of shadow protection");
                creators.erase("prayer of shadow protection on party");
                creators.erase("inner focus");
                creators.erase("fear ward");
                creators.erase("fear ward on party");
                creators.erase("fear ward on master");
                creators.erase("desperate prayer");
                creators.erase("divine hymn");
                creators.erase("hymn of hope");
            }
        private:
            static Action* dispersion(PlayerbotAI* ai) { return new CastDispersionAction(ai); }
            static Action* vampiric_embrace(PlayerbotAI* ai) { return new CastVampiricEmbraceAction(ai); }
            static Action* vampiric_touch(PlayerbotAI* ai) { return new CastVampiricTouchAction(ai); }
            static Action* psychic_scream(PlayerbotAI* ai) { return new CastPsychicScreamAction(ai); }
            static Action* circle_of_healing(PlayerbotAI* ai) { return new CastCircleOfHealingAction(ai); }
            static Action* resurrection(PlayerbotAI* ai) { return new CastResurrectionAction(ai); }
            static Action* shadow_word_pain(PlayerbotAI* ai) { return new CastPowerWordPainAction(ai); }
            static Action* shadow_word_pain_on_attacker(PlayerbotAI* ai) { return new CastPowerWordPainOnAttackerAction(ai); }
            static Action* devouring_plague(PlayerbotAI* ai) { return new CastDevouringPlagueAction(ai); }
            static Action* mind_flay(PlayerbotAI* ai) { return new CastMindFlayAction(ai); }
            static Action* holy_fire(PlayerbotAI* ai) { return new CastHolyFireAction(ai); }
            static Action* smite(PlayerbotAI* ai) { return new CastSmiteAction(ai); }
            static Action* mind_blast(PlayerbotAI* ai) { return new CastMindBlastAction(ai); }
            static Action* mind_shear(PlayerbotAI* ai) { return new CastMindShearAction(ai); }
            static Action* shadowform(PlayerbotAI* ai) { return new CastShadowformAction(ai); }
            static Action* remove_shadowform(PlayerbotAI* ai) { return new CastRemoveShadowformAction(ai); }
            static Action* holy_nova(PlayerbotAI* ai) { return new CastHolyNovaAction(ai); }
            static Action* holy_nova_aoe(PlayerbotAI* ai) { return new CastHolyNovaAoeAction(ai); }
            static Action* power_word_fortitude(PlayerbotAI* ai) { return new CastPowerWordFortitudeAction(ai); }
            static Action* power_word_fortitude_on_party(PlayerbotAI* ai) { return new CastPowerWordFortitudeOnPartyAction(ai); }
            static Action* divine_spirit(PlayerbotAI* ai) { return new CastDivineSpiritAction(ai); }
            static Action* divine_spirit_on_party(PlayerbotAI* ai) { return new CastDivineSpiritOnPartyAction(ai); }
            static Action* power_word_shield(PlayerbotAI* ai) { return new CastPowerWordShieldAction(ai); }
            static Action* power_word_shield_on_party(PlayerbotAI* ai) { return new CastPowerWordShieldOnPartyAction(ai); }
            static Action* power_word_shield_on_master(PlayerbotAI* ai) { return new CastPowerWordShieldOnMasterAction(ai); }
            static Action* renew(PlayerbotAI* ai) { return new CastRenewAction(ai); }
            static Action* renew_on_party(PlayerbotAI* ai) { return new CastRenewOnPartyAction(ai); }
            static Action* renew_on_master(PlayerbotAI* ai) { return new CastRenewOnMasterAction(ai); }
            static Action* greater_heal(PlayerbotAI* ai) { return new CastGreaterHealAction(ai); }
            static Action* greater_heal_on_party(PlayerbotAI* ai) { return new CastGreaterHealOnPartyAction(ai); }
            static Action* greater_heal_on_master(PlayerbotAI* ai) { return new CastGreaterHealOnMasterAction(ai); }
            static Action* heal(PlayerbotAI* ai) { return new CastHealAction(ai); }
            static Action* heal_on_party(PlayerbotAI* ai) { return new CastHealOnPartyAction(ai); }
            static Action* heal_on_master(PlayerbotAI* ai) { return new CastHealOnMasterAction(ai); }
            static Action* lesser_heal(PlayerbotAI* ai) { return new CastLesserHealAction(ai); }
            static Action* lesser_heal_on_party(PlayerbotAI* ai) { return new CastLesserHealOnPartyAction(ai); }
            static Action* lesser_heal_on_master(PlayerbotAI* ai) { return new CastLesserHealOnMasterAction(ai); }
            static Action* flash_heal(PlayerbotAI* ai) { return new CastFlashHealAction(ai); }
            static Action* flash_heal_on_party(PlayerbotAI* ai) { return new CastFlashHealOnPartyAction(ai); }
            static Action* flash_heal_on_master(PlayerbotAI* ai) { return new CastFlashHealOnMasterAction(ai); }
            static Action* dispel_magic(PlayerbotAI* ai) { return new CastDispelMagicAction(ai); }
            static Action* dispel_magic_on_party(PlayerbotAI* ai) { return new CastDispelMagicOnPartyAction(ai); }
            static Action* dispel_magic_on_target(PlayerbotAI* ai) { return new CastDispelMagicOnTargetAction(ai); }
            static Action* cure_disease(PlayerbotAI* ai) { return new CastCureDiseaseAction(ai); }
            static Action* cure_disease_on_party(PlayerbotAI* ai) { return new CastCureDiseaseOnPartyAction(ai); }
            static Action* abolish_disease(PlayerbotAI* ai) { return new CastAbolishDiseaseAction(ai); }
            static Action* abolish_disease_on_party(PlayerbotAI* ai) { return new CastAbolishDiseaseOnPartyAction(ai); }
            static Action* fade(PlayerbotAI* ai) { return new CastFadeAction(ai); }
            static Action* inner_fire(PlayerbotAI* ai) { return new CastInnerFireAction(ai); }
            static Action* prayer_of_healing(PlayerbotAI* ai) { return new CastPrayerOfHealingAction(ai); }
            static Action* prayer_of_mending(PlayerbotAI* ai) { return new CastPrayerOfMendingAction(ai); }
            static Action* prayer_of_mending_on_party(PlayerbotAI* ai) { return new CastPrayerOfMendingOnPartyAction(ai); }
            static Action* prayer_of_mending_on_master(PlayerbotAI* ai) { return new CastPrayerOfMendingOnMasterAction(ai); }
            static Action* power_infusion(PlayerbotAI* ai) { return new CastPowerInfusionAction(ai); }
            static Action* power_infusion_on_party(PlayerbotAI* ai) { return new CastPowerInfusionOnPartyAction(ai); }
            static Action* pain_suppression(PlayerbotAI* ai) { return new CastPainSuppressionAction(ai); }
            static Action* pain_suppression_on_party(PlayerbotAI* ai) { return new CastPainSuppressionOnPartyAction(ai); }
            static Action* pain_suppression_on_master(PlayerbotAI* ai) { return new CastPainSuppressionOnMasterAction(ai); }
            static Action* penance_on_attacker(PlayerbotAI* ai) { return new CastPenanceOnAttackerAction(ai); }
            static Action* penance(PlayerbotAI* ai) { return new CastPenanceHealAction(ai); }
            static Action* penance_on_party(PlayerbotAI* ai) { return new CastPenanceHealOnPartyAction(ai); }
            static Action* penance_on_master(PlayerbotAI* ai) { return new CastPenanceHealOnMasterAction(ai); }
            static Action* guardian_spirit(PlayerbotAI* ai) { return new CastGuardianSpiritAction(ai); }
            static Action* guardian_spirit_on_party(PlayerbotAI* ai) { return new CastGuardianSpiritOnPartyAction(ai); }
            static Action* guardian_spirit_on_master(PlayerbotAI* ai) { return new CastGuardianSpiritOnMasterAction(ai); }
            static Action* binding_heal_on_party(PlayerbotAI* ai) { return new CastBindingHealOnPartyAction(ai); }
            static Action* binding_heal_on_master(PlayerbotAI* ai) { return new CastBindingHealOnMasterAction(ai); }
            static Action* shadowfiend(PlayerbotAI* ai) { return new CastShadowfiendAction(ai); }
            static Action* power_word_death(PlayerbotAI* ai) { return new CastPowerWordDeathAction(ai); }
            static Action* prayer_of_shadow_protection(PlayerbotAI* ai) { return new CastPrayerOfShadowProtectionAction(ai); }
            static Action* prayer_of_shadow_protection_on_party(PlayerbotAI* ai) { return new CastPrayerOfShadowProtectionOnPartyAction(ai); }
            static Action* inner_focus(PlayerbotAI* ai) { return new CastInnerFocusAction(ai); }
            static Action* fear_ward(PlayerbotAI* ai) { return new CastFearWardAction(ai); }
            static Action* fear_ward_on_party(PlayerbotAI* ai) { return new CastFearWardOnPartyAction(ai); }
            static Action* fear_ward_on_master(PlayerbotAI* ai) { return new CastFearWardOnMasterAction(ai); }
            static Action* desperate_prayer(PlayerbotAI* ai) { return new CastDesperatePrayerAction(ai); }
            static Action* divine_hymn(PlayerbotAI* ai) { return new CastDivineHymnAction(ai); }
            static Action* hymn_of_hope(PlayerbotAI* ai) { return new CastHymnOfHopeAction(ai); }
            static Action* psychic_horror(PlayerbotAI* ai) { return new CastPsychicHorrorAction(ai); }
        };
    };
};

PriestAiObjectContext::PriestAiObjectContext(PlayerbotAI* ai) : AiObjectContext(ai)
{
    strategyFactoryInternal = new ai::priest::StrategyFactoryInternal();
    combatStrategyFactoryInternal = new ai::priest::CombatStrategyFactoryInternal();
    aiObjectContextInternal = new ai::priest::AiObjectContextInternal();
    triggerFactoryInternal = new ai::priest::TriggerFactoryInternal();

    strategyContexts.Add(strategyFactoryInternal);
    strategyContexts.Add(combatStrategyFactoryInternal);
    actionContexts.Add(aiObjectContextInternal);
    triggerContexts.Add(triggerFactoryInternal);
}

PriestAiObjectContext::~PriestAiObjectContext()
{
    strategyContexts.Remove(strategyFactoryInternal);
    strategyContexts.Remove(combatStrategyFactoryInternal);
    actionContexts.Remove(aiObjectContextInternal);
    triggerContexts.Remove(triggerFactoryInternal);

    delete dynamic_cast<ai::priest::StrategyFactoryInternal*>(strategyFactoryInternal);
    delete dynamic_cast<ai::priest::StrategyFactoryInternal*>(combatStrategyFactoryInternal);
    delete dynamic_cast<ai::priest::AiObjectContextInternal*>(aiObjectContextInternal);
    delete dynamic_cast<ai::priest::TriggerFactoryInternal*>(triggerFactoryInternal);
}

