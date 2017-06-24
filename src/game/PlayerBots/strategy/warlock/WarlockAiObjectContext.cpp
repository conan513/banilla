#include "../../../botpch.h"
#include "../../playerbot.h"
#include "WarlockActions.h"
#include "WarlockAiObjectContext.h"
#include "DpsWarlockStrategy.h"
#include "GenericWarlockNonCombatStrategy.h"
#include "TankWarlockStrategy.h"
#include "../generic/PullStrategy.h"
#include "WarlockTriggers.h"
#include "../NamedObjectContext.h"
#include "../actions/UseItemAction.h"

using namespace ai;

namespace ai
{
    namespace warlock
    {
        using namespace ai;

        class StrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["nc"] = &warlock::StrategyFactoryInternal::nc;
                creators["pull"] = &warlock::StrategyFactoryInternal::pull;
                creators["aoe"] = &warlock::StrategyFactoryInternal::aoe;
                creators["fire aoe"] = &warlock::StrategyFactoryInternal::fire_aoe;
                creators["dps debuff"] = &warlock::StrategyFactoryInternal::dps_debuff;
                creators["debuff"] = &warlock::StrategyFactoryInternal::debuff;
                creators["imp"] = &warlock::StrategyFactoryInternal::nc_imp;
                creators["voidwalker"] = &warlock::StrategyFactoryInternal::nc_voidwalker;
                creators["succubus"] = &warlock::StrategyFactoryInternal::nc_succubus;
                creators["felhunter"] = &warlock::StrategyFactoryInternal::nc_felhunter;
                creators["felguard"] = &warlock::StrategyFactoryInternal::nc_felguard;
            }
            ~StrategyFactoryInternal()
            {
                creators.erase("nc");
                creators.erase("pull");
                creators.erase("aoe");
                creators.erase("fire aoe");
                creators.erase("dps debuff");
                creators.erase("debuff");
                creators.erase("imp");
                creators.erase("voidwalker");
                creators.erase("succubus");
                creators.erase("felhunter");
                creators.erase("felguard");
            }

        private:
            static Strategy* nc(PlayerbotAI* ai) { return new GenericWarlockNonCombatStrategy(ai); }
            static Strategy* aoe(PlayerbotAI* ai) { return new DpsAoeWarlockStrategy(ai); }
            static Strategy* fire_aoe(PlayerbotAI* ai) { return new DpsFireAoeWarlockStrategy(ai); }
            static Strategy* dps_debuff(PlayerbotAI* ai) { return new DpsWarlockDebuffStrategy(ai); }
            static Strategy* debuff(PlayerbotAI* ai) { return new WarlockDebuffStrategy(ai); }
            static Strategy* pull(PlayerbotAI* ai) { return new PullStrategy(ai, "shoot"); }
            static Strategy* nc_imp(PlayerbotAI* ai) { return new WarlockImpStrategy(ai); }
            static Strategy* nc_voidwalker(PlayerbotAI* ai) { return new WarlockVoidwalkerStrategy(ai); }
            static Strategy* nc_succubus(PlayerbotAI* ai) { return new WarlockSuccubusStrategy(ai); }
            static Strategy* nc_felhunter(PlayerbotAI* ai) { return new WarlockFelhunterStrategy(ai); }
            static Strategy* nc_felguard(PlayerbotAI* ai) { return new WarlockFelguardStrategy(ai); }
        };

        class CombatStrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            CombatStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
            {
                creators["dps"] = &warlock::CombatStrategyFactoryInternal::dps;
                creators["fire"] = &warlock::CombatStrategyFactoryInternal::fire_dps;
                creators["tank"] = &warlock::CombatStrategyFactoryInternal::tank;
            }
            ~CombatStrategyFactoryInternal()
            {
                creators.erase("dps");
                creators.erase("fire");
                creators.erase("tank");
            }

        private:
            static Strategy* tank(PlayerbotAI* ai) { return new TankWarlockStrategy(ai); }
            static Strategy* dps(PlayerbotAI* ai) { return new DpsWarlockStrategy(ai); }
            static Strategy* fire_dps(PlayerbotAI* ai) { return new DpsFireWarlockStrategy(ai); }
        };
    };
};

namespace ai
{
    namespace warlock
    {
        using namespace ai;

        class TriggerFactoryInternal : public NamedObjectContext<Trigger>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["shadow trance"] = &TriggerFactoryInternal::shadow_trance;
                creators["demon armor"] = &TriggerFactoryInternal::demon_armor;
                creators["no healthstone"] = &TriggerFactoryInternal::HasHealthstone;
                creators["no firestone"] = &TriggerFactoryInternal::HasFirestone;
                creators["no spellstone"] = &TriggerFactoryInternal::HasSpellstone;
                creators["no soulstone"] = &TriggerFactoryInternal::HasSoulstone;
                creators["corruption"] = &TriggerFactoryInternal::corruption;
                creators["corruption on attacker"] = &TriggerFactoryInternal::corruption_on_attacker;
                creators["no curse"] = &TriggerFactoryInternal::curse_of_agony;
                creators["curse on attacker"] = &TriggerFactoryInternal::curse_on_attacker;
                creators["banish"] = &TriggerFactoryInternal::banish;
             //   creators["spellstone"] = &TriggerFactoryInternal::spellstone;
             //   creators["firestone"] = &TriggerFactoryInternal::firestone;
                creators["no soulstone on master"] = &TriggerFactoryInternal::soulstone_on_master;
                creators["backlash"] = &TriggerFactoryInternal::backlash;
                creators["molten core"] = &TriggerFactoryInternal::molten_core;
                creators["decimation"] = &TriggerFactoryInternal::decimation;
                creators["fear"] = &TriggerFactoryInternal::fear;
                creators["immolate"] = &TriggerFactoryInternal::immolate;
                //creators["immolate on attacker"] = &TriggerFactoryInternal::immolate_on_attacker;
                creators["haunt"] = &TriggerFactoryInternal::haunt;
                creators["demon dead"] = &TriggerFactoryInternal::demon_dead;
                creators["demon low health"] = &TriggerFactoryInternal::demon_low_health;
            }
            ~TriggerFactoryInternal()
            {
                creators.erase("shadow trance");
                creators.erase("demon armor");
                creators.erase("no healthstone");
                creators.erase("no firestone");
                creators.erase("no spellstone");
                creators.erase("no soulstone");
                creators.erase("corruption");
                creators.erase("corruption on attacker");
                creators.erase("no curse");
                creators.erase("curse on attacker");
                creators.erase("banish");
                creators.erase("soulstone on master");
                creators.erase("backlash");
                creators.erase("molten core");
                creators.erase("decimation");
                creators.erase("fear");
                creators.erase("immolate");
                creators.erase("haunt");
                creators.erase("demon dead");
                creators.erase("demon low health");
            }

        private:
            static Trigger* shadow_trance(PlayerbotAI* ai) { return new ShadowTranceTrigger(ai); }
            static Trigger* molten_core(PlayerbotAI* ai) { return new MoltenCoreTrigger(ai); }
            static Trigger* decimation(PlayerbotAI* ai) { return new DecimationTrigger(ai); }
            static Trigger* demon_armor(PlayerbotAI* ai) { return new DemonArmorTrigger(ai); }
            static Trigger* HasHealthstone(PlayerbotAI* ai) { return new HasHealthstoneTrigger(ai); }
            static Trigger* HasFirestone(PlayerbotAI* ai) { return new HasFirestoneTrigger(ai); }
            static Trigger* HasSpellstone(PlayerbotAI* ai) { return new HasSpellstoneTrigger(ai); }
            static Trigger* HasSoulstone(PlayerbotAI* ai) { return new HasSoulstoneTrigger(ai); }
            static Trigger* soulstone_on_master(PlayerbotAI* ai) { return new SoulstoneOnMasterTrigger(ai); }
            static Trigger* corruption(PlayerbotAI* ai) { return new NoCorruptionTrigger(ai); }
            static Trigger* corruption_on_attacker(PlayerbotAI* ai) { return new CorruptionOnAttackerTrigger(ai); }
            static Trigger* curse_of_agony(PlayerbotAI* ai) { return new NoCurseTrigger(ai); }
            static Trigger* curse_on_attacker(PlayerbotAI* ai) { return new CurseOnAttackerTrigger(ai); }
            static Trigger* banish(PlayerbotAI* ai) { return new BanishTrigger(ai); }
       //     static Trigger* spellstone(PlayerbotAI* ai) { return new SpellstoneTrigger(ai); }
       //     static Trigger* firestone(PlayerbotAI* ai) { return new FirestoneTrigger(ai); }
            static Trigger* backlash(PlayerbotAI* ai) { return new BacklashTrigger(ai); }
            static Trigger* fear(PlayerbotAI* ai) { return new FearTrigger(ai); }
            static Trigger* immolate(PlayerbotAI* ai) { return new ImmolateTrigger(ai); }
            //static Trigger* immolate_on_attacker(PlayerbotAI* ai) { return new ImmolateOnAttackerTrigger(ai); }
            static Trigger* haunt(PlayerbotAI* ai) { return new HauntTrigger(ai); }
            static Trigger* demon_dead(PlayerbotAI* ai) { return new DemonDeadTrigger(ai); }
            static Trigger* demon_low_health(PlayerbotAI* ai) { return new DemonLowHealthTrigger(ai); }
        };
    };
};

namespace ai
{
    namespace warlock
    {
        using namespace ai;

        class AiObjectContextInternal : public NamedObjectContext<Action>
        {
        public:
            AiObjectContextInternal()
            {
                creators["summon imp"] = &AiObjectContextInternal::summon_imp;
                creators["fel armor"] = &AiObjectContextInternal::fel_armor;
                creators["demon armor"] = &AiObjectContextInternal::demon_armor;
                creators["demon skin"] = &AiObjectContextInternal::demon_skin;
                creators["create healthstone"] = &AiObjectContextInternal::create_healthstone;
                creators["create firestone"] = &AiObjectContextInternal::create_firestone;
                creators["create spellstone"] = &AiObjectContextInternal::create_spellstone;
                creators["create soulstone"] = &AiObjectContextInternal::create_soulstone;
                creators["spellstone"] = &AiObjectContextInternal::spellstone;
                creators["firestone"] = &AiObjectContextInternal::firestone;
                creators["soulstone on master"] = &AiObjectContextInternal::soulstone_on_master;
                creators["summon voidwalker"] = &AiObjectContextInternal::summon_voidwalker;
                creators["summon felguard"] = &AiObjectContextInternal::summon_felguard;
                creators["summon succubus"] = &AiObjectContextInternal::summon_succubus;
                creators["summon felhunter"] = &AiObjectContextInternal::summon_felhunter;
                creators["immolate"] = &AiObjectContextInternal::immolate;
                creators["corruption"] = &AiObjectContextInternal::corruption;
                creators["immolate on attacker"] = &AiObjectContextInternal::immolate_on_attacker;
                creators["corruption on attacker"] = &AiObjectContextInternal::corruption_on_attacker;
                creators["instant action"] = &AiObjectContextInternal::corruption_on_attacker;
                //creators["death coil on attacker"] = &AiObjectContextInternal::death_coil_on_attacker;
                creators["curse of agony"] = &AiObjectContextInternal::curse_of_agony;
                creators["curse of agony on attacker"] = &AiObjectContextInternal::curse_of_agony_on_attacker;
                creators["curse of exhaustion"] = &AiObjectContextInternal::curse_of_exhaustion;
                creators["curse of the elements"] = &AiObjectContextInternal::curse_of_the_elements;
                creators["curse of the elements on attacker"] = &AiObjectContextInternal::curse_of_the_elements_on_attacker;
                creators["curse of doom"] = &AiObjectContextInternal::curse_of_doom;
                creators["curse of weakness"] = &AiObjectContextInternal::curse_of_weakness;
                creators["curse of weakness on attacker"] = &AiObjectContextInternal::curse_of_weakness_on_attacker;
                creators["shadow bolt"] = &AiObjectContextInternal::shadow_bolt;
                creators["drain soul"] = &AiObjectContextInternal::drain_soul;
                creators["drain mana"] = &AiObjectContextInternal::drain_mana;
                creators["drain life"] = &AiObjectContextInternal::drain_life;
                creators["banish"] = &AiObjectContextInternal::banish;
                creators["banish on cc"] = &AiObjectContextInternal::banish_on_cc;
                creators["seed of corruption"] = &AiObjectContextInternal::seed_of_corruption;
                creators["rain of fire"] = &AiObjectContextInternal::rain_of_fire;
                creators["shadowfury"] = &AiObjectContextInternal::shadowfury;
                creators["chaos bolt"] = &AiObjectContextInternal::chaos_bolt;
                creators["haunt"] = &AiObjectContextInternal::haunt;
                creators["death coil"] = &AiObjectContextInternal::death_coil;
                creators["soul fire"] = &AiObjectContextInternal::soul_fire;
                creators["howl of terror"] = &AiObjectContextInternal::howl_of_terror;
                creators["shadowfury"] = &AiObjectContextInternal::shadowfury;
                creators["life tap"] = &AiObjectContextInternal::life_tap;
                creators["fear"] = &AiObjectContextInternal::fear;
                creators["fear on cc"] = &AiObjectContextInternal::fear_on_cc;
                creators["incinerate"] = &AiObjectContextInternal::incinerate;
                creators["conflagrate"] = &AiObjectContextInternal::conflagrate;
                creators["fel domination"] = &AiObjectContextInternal::fel_domination;
                creators["demonic empowerment"] = &AiObjectContextInternal::demonic_empowerment;
                creators["metamorphosis"] = &AiObjectContextInternal::metamorphosis;
                creators["shadow cleave"] = &AiObjectContextInternal::shadow_cleave;
                creators["immolation aura"] = &AiObjectContextInternal::immolation_aura;
                creators["demon charge"] = &AiObjectContextInternal::demon_charge;
                creators["challenging howl"] = &AiObjectContextInternal::challenging_howl;
                creators["soul shatter"] = &AiObjectContextInternal::soul_shatter;
            }
            ~AiObjectContextInternal()
            {
                creators.erase("summon imp");
                creators.erase("fel armor");
                creators.erase("demon armor");
                creators.erase("demon skin");
                creators.erase("create healthstone");
                creators.erase("create firestone");
                creators.erase("create spellstone");
                creators.erase("create soulstone");
                creators.erase("spellstone");
                creators.erase("firestone");
                creators.erase("soulstone on master");
                creators.erase("summon voidwalker");
                creators.erase("summon felguard");
                creators.erase("summon succubus");
                creators.erase("summon felhunter");
                creators.erase("immolate");
                creators.erase("corruption");
                creators.erase("immolate on attacker");
                creators.erase("corruption on attacker");
                creators.erase("curse of agony");
                creators.erase("curse of agony on attacker");
                creators.erase("curse of exhaustion");
                creators.erase("curse of the elements");
                creators.erase("curse of the elements on attacker");
                creators.erase("curse of doom");
                creators.erase("curse of weakness");
                creators.erase("curse of weakness on attacker");
                creators.erase("shadow bolt");
                creators.erase("drain soul");
                creators.erase("drain mana");
                creators.erase("drain life");
                creators.erase("banish");
                creators.erase("banish on cc");
                creators.erase("seed of corruption");
                creators.erase("rain of fire");
                creators.erase("shadowfury");
                creators.erase("chaos bolt");
                creators.erase("haunt");
                creators.erase("death coil");
                creators.erase("soul fire");
                creators.erase("howl of terror");
                creators.erase("shadowfury");
                creators.erase("life tap");
                creators.erase("fear");
                creators.erase("fear on cc");
                creators.erase("incinerate");
                creators.erase("conflagrate");
                creators.erase("fel domination");
                creators.erase("demonic empowerment");
                creators.erase("metamorphosis");
                creators.erase("shadow cleave");
                creators.erase("immolation aura");
                creators.erase("demon charge");
                creators.erase("challenging howl");
                creators.erase("soul shatter");
            }

        private:
            static Action* conflagrate(PlayerbotAI* ai) { return new CastConflagrateAction(ai); }
            static Action* incinerate(PlayerbotAI* ai) { return new CastIncinerateAction(ai); }
            static Action* fear_on_cc(PlayerbotAI* ai) { return new CastFearOnCcAction(ai); }
            static Action* fear(PlayerbotAI* ai) { return new CastFearAction(ai); }
            static Action* immolate(PlayerbotAI* ai) { return new CastImmolateAction(ai); }
            static Action* immolate_on_attacker(PlayerbotAI* ai) { return new CastImmolateOnAttackerAction(ai); }
            static Action* summon_imp(PlayerbotAI* ai) { return new CastSummonImpAction(ai); }
            static Action* fel_armor(PlayerbotAI* ai) { return new CastFelArmorAction(ai); }
            static Action* demon_armor(PlayerbotAI* ai) { return new CastDemonArmorAction(ai); }
            static Action* demon_skin(PlayerbotAI* ai) { return new CastDemonSkinAction(ai); }
            static Action* create_healthstone(PlayerbotAI* ai) { return new CastCreateHealthstoneAction(ai); }
            static Action* create_firestone(PlayerbotAI* ai) { return new CastCreateFirestoneAction(ai); }
            static Action* create_spellstone(PlayerbotAI* ai) { return new CastCreateSpellstoneAction(ai); }
            static Action* create_soulstone(PlayerbotAI* ai) { return new CastCreateSoulstoneAction(ai); }
            static Action* spellstone(PlayerbotAI* ai) { return new UseSpellstoneMainhandAction(ai); }
            static Action* firestone(PlayerbotAI* ai) { return new UseFirestoneMainhandAction(ai); }
            static Action* soulstone_on_master(PlayerbotAI* ai) { return new UseSoulstoneOnMasterAction(ai); }
            static Action* summon_voidwalker(PlayerbotAI* ai) { return new CastSummonVoidwalkerAction(ai); }
            static Action* summon_succubus(PlayerbotAI* ai) { return new CastSummonSuccubusAction(ai); }
            static Action* summon_felguard(PlayerbotAI* ai) { return new CastSummonFelguardAction(ai); }
            static Action* summon_felhunter(PlayerbotAI* ai) { return new CastSummonFelhunterAction(ai); }
            static Action* corruption(PlayerbotAI* ai) { return new CastCorruptionAction(ai); }
            static Action* corruption_on_attacker(PlayerbotAI* ai) { return new CastCorruptionOnAttackerAction(ai); }
            //static Action* death_coil_on_attacker(PlayerbotAI* ai) { return new CastDeathCoilOnAttackerAction(ai); }
            static Action* curse_of_agony(PlayerbotAI* ai) { return new CastCurseOfAgonyAction(ai); }
            static Action* curse_of_agony_on_attacker(PlayerbotAI* ai) { return new CastCurseOfAgonyOnAttackerAction(ai); }
            static Action* curse_of_exhaustion(PlayerbotAI* ai) { return new CastCurseOfExhaustionAction(ai); }
            static Action* curse_of_doom(PlayerbotAI* ai) { return new CastCurseOfDoomAction(ai); }
            static Action* curse_of_the_elements(PlayerbotAI* ai) { return new CastCurseOfTheElementsAction(ai); }
            static Action* curse_of_weakness(PlayerbotAI* ai) { return new CastCurseOfWeaknessAction(ai); }
            static Action* curse_of_the_elements_on_attacker(PlayerbotAI* ai) { return new CastCurseOfTheElementsOnAttackerAction(ai); }
            static Action* curse_of_weakness_on_attacker(PlayerbotAI* ai) { return new CastCurseOfWeaknessOnAttackerAction(ai); }
            static Action* shadow_bolt(PlayerbotAI* ai) { return new CastShadowBoltAction(ai); }
            static Action* haunt(PlayerbotAI* ai) { return new CastHauntAction(ai); }
            static Action* howl_of_terror(PlayerbotAI* ai) { return new CastHowlOfTerrorAction(ai); }
            static Action* death_coil(PlayerbotAI* ai) { return new CastDeathcoilAction(ai); }
            static Action* chaos_bolt(PlayerbotAI* ai) { return new CastChaosBoltAction(ai); }
            static Action* soul_fire(PlayerbotAI* ai) { return new CastSoulFireAction(ai); }
            static Action* drain_soul(PlayerbotAI* ai) { return new CastDrainSoulAction(ai); }
            static Action* drain_mana(PlayerbotAI* ai) { return new CastDrainManaAction(ai); }
            static Action* drain_life(PlayerbotAI* ai) { return new CastDrainLifeAction(ai); }
            static Action* banish(PlayerbotAI* ai) { return new CastBanishAction(ai); }
            static Action* banish_on_cc(PlayerbotAI* ai) { return new CastBanishCcAction(ai); }
            static Action* seed_of_corruption(PlayerbotAI* ai) { return new CastSeedOfCorruptionAction(ai); }
            static Action* rain_of_fire(PlayerbotAI* ai) { return new CastRainOfFireAction(ai); }
            static Action* shadowfury(PlayerbotAI* ai) { return new CastShadowfuryAction(ai); }
            static Action* life_tap(PlayerbotAI* ai) { return new CastLifeTapAction(ai); }
            static Action* fel_domination(PlayerbotAI* ai) { return new CastFelDominationAction(ai); }
            static Action* demonic_empowerment(PlayerbotAI* ai) { return new CastDemonicEmpowermentAction(ai); }
            static Action* metamorphosis(PlayerbotAI* ai) { return new CastMetamorphosisAction(ai); }
            static Action* shadow_cleave(PlayerbotAI* ai) { return new CastShadowCleaveAction(ai); }
            static Action* immolation_aura(PlayerbotAI* ai) { return new CastImmolationAuraAction(ai); }
            static Action* demon_charge(PlayerbotAI* ai) { return new CastDemonChargeAction(ai); }
            static Action* challenging_howl(PlayerbotAI* ai) { return new CastChallengingHowlAction(ai); }
            static Action* soul_shatter(PlayerbotAI* ai) { return new CastSoulShatterAction(ai); }
        };
    };
};



WarlockAiObjectContext::WarlockAiObjectContext(PlayerbotAI* ai) : AiObjectContext(ai)
{
    strategyFactoryInternal = new ai::warlock::StrategyFactoryInternal();
    combatStrategyFactoryInternal = new ai::warlock::CombatStrategyFactoryInternal();
    aiObjectContextInternal = new ai::warlock::AiObjectContextInternal();
    triggerFactoryInternal = new ai::warlock::TriggerFactoryInternal();

    strategyContexts.Add(strategyFactoryInternal);
    strategyContexts.Add(combatStrategyFactoryInternal);
    actionContexts.Add(aiObjectContextInternal);
    triggerContexts.Add(triggerFactoryInternal);
}

WarlockAiObjectContext::~WarlockAiObjectContext()
{
    strategyContexts.Remove(strategyFactoryInternal);
    strategyContexts.Remove(combatStrategyFactoryInternal);
    actionContexts.Remove(aiObjectContextInternal);
    triggerContexts.Remove(triggerFactoryInternal);

    delete dynamic_cast<ai::warlock::StrategyFactoryInternal*>(strategyFactoryInternal);
    delete dynamic_cast<ai::warlock::CombatStrategyFactoryInternal*>(combatStrategyFactoryInternal);
    delete dynamic_cast<ai::warlock::AiObjectContextInternal*>(aiObjectContextInternal);
    delete dynamic_cast<ai::warlock::TriggerFactoryInternal*>(triggerFactoryInternal);
}
