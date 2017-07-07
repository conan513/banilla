#include "../../../botpch.h"
#include "../../playerbot.h"
#include "HunterActions.h"
#include "HunterTriggers.h"
#include "HunterAiObjectContext.h"
#include "DpsHunterStrategy.h"
#include "GenericHunterNonCombatStrategy.h"
#include "HunterBuffStrategies.h"
#include "../NamedObjectContext.h"
#include "../generic/PullStrategy.h"

using namespace ai;


namespace ai
{
    namespace hunter
    {
        using namespace ai;

        class StrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["dps"] = &hunter::StrategyFactoryInternal::dps;
                creators["nc"] = &hunter::StrategyFactoryInternal::nc;
                creators["aoe"] = &hunter::StrategyFactoryInternal::aoe;
                creators["dps debuff"] = &hunter::StrategyFactoryInternal::dps_debuff;
                creators["pull"] = &hunter::StrategyFactoryInternal::pull;
            }
            ~StrategyFactoryInternal()
            {
                creators.erase("dps");
                creators.erase("nc");
                creators.erase("aoe");
                creators.erase("dps debuff");
                creators.erase("pull");
            }

        private:
            static Strategy* aoe(PlayerbotAI* ai) { return new DpsAoeHunterStrategy(ai); }
            static Strategy* dps(PlayerbotAI* ai) { return new DpsHunterStrategy(ai); }
            static Strategy* nc(PlayerbotAI* ai) { return new GenericHunterNonCombatStrategy(ai); }
            static Strategy* dps_debuff(PlayerbotAI* ai) { return new DpsHunterDebuffStrategy(ai); }
            static Strategy* pull(PlayerbotAI* ai) { return new PullStrategy(ai, "auto shoot"); }
        };

        class BuffStrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            BuffStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
            {
                creators["bspeed"] = &hunter::BuffStrategyFactoryInternal::bspeed;
                creators["bdps"] = &hunter::BuffStrategyFactoryInternal::bdps;
                creators["bmana"] = &hunter::BuffStrategyFactoryInternal::bmana;
                creators["rnature"] = &hunter::BuffStrategyFactoryInternal::rnature;
            }
            ~BuffStrategyFactoryInternal()
            {
                creators.erase("bspeed");
                creators.erase("bdps");
                creators.erase("bmana");
                creators.erase("rnature");
            }

        private:
            static Strategy* bspeed(PlayerbotAI* ai) { return new HunterBuffSpeedStrategy(ai); }
            static Strategy* bdps(PlayerbotAI* ai) { return new HunterBuffDpsStrategy(ai); }
            static Strategy* bmana(PlayerbotAI* ai) { return new HunterBuffManaStrategy(ai); }
            static Strategy* rnature(PlayerbotAI* ai) { return new HunterNatureResistanceStrategy(ai); }
        };
    };
};


namespace ai
{
    namespace hunter
    {
        using namespace ai;

        class TriggerFactoryInternal : public NamedObjectContext<Trigger>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["aspect of the viper"] = &TriggerFactoryInternal::aspect_of_the_viper;
                creators["black arrow"] = &TriggerFactoryInternal::black_arrow;
                creators["no stings"] = &TriggerFactoryInternal::NoStings;
                creators["hunters pet dead"] = &TriggerFactoryInternal::hunters_pet_dead;
                creators["hunters pet low health"] = &TriggerFactoryInternal::hunters_pet_low_health;
                creators["hunter's mark"] = &TriggerFactoryInternal::hunters_mark;
                creators["freezing trap on cc"] = &TriggerFactoryInternal::freezing_trap_cc;
                creators["aspect of the pack"] = &TriggerFactoryInternal::aspect_of_the_pack;
                creators["rapid fire"] = &TriggerFactoryInternal::rapid_fire;
                creators["kill command"] = &TriggerFactoryInternal::kill_command;
                creators["kill shot"] = &TriggerFactoryInternal::kill_shot;
                creators["aspect of the dragonhawk"] = &TriggerFactoryInternal::aspect_of_the_dragonhawk;
                creators["aspect of the hawk"] = &TriggerFactoryInternal::aspect_of_the_hawk;
                creators["aspect of the wild"] = &TriggerFactoryInternal::aspect_of_the_wild;
                creators["aspect of the viper"] = &TriggerFactoryInternal::aspect_of_the_viper;
                creators["trueshot aura"] = &TriggerFactoryInternal::trueshot_aura;
                creators["serpent sting on attacker"] = &TriggerFactoryInternal::serpent_sting_on_attacker;
                creators["silencing shot"] = &TriggerFactoryInternal::silencing_shot_interrupt;
                creators["silencing shot on enemy healer"] = &TriggerFactoryInternal::silencing_shot_on_enemy_healer;
                creators["concussive shot snare"] = &TriggerFactoryInternal::concussive_shot_snare;
                creators["arcane shot"] = &TriggerFactoryInternal::arcane_shot;
                creators["misdirection on party"] = &TriggerFactoryInternal::misdirection_on_party;
                creators["wyvern sting"] = &TriggerFactoryInternal::wyvern_sting;
                creators["counterstrike"] = &TriggerFactoryInternal::counterstrike;
		creators["pet not happy"] = &TriggerFactoryInternal::pet_not_happy;
            }
            ~TriggerFactoryInternal()
            {
                creators.erase("aspect of the viper");
                creators.erase("black arrow");
                creators.erase("no stings");
                creators.erase("hunters pet dead");
                creators.erase("hunters pet low health");
                creators.erase("hunter's mark");
                creators.erase("freezing trap on cc");
                creators.erase("aspect of the pack");
                creators.erase("rapid fire");
                creators.erase("kill command");
                creators.erase("kill shot");
                creators.erase("aspect of the dragonhawk");
                creators.erase("aspect of the hawk");
                creators.erase("aspect of the wild");
                creators.erase("aspect of the viper");
                creators.erase("trueshot aura");
                creators.erase("serpent sting on attacker");
                creators.erase("silencing shot");
                creators.erase("silencing shot on enemy healer");
                creators.erase("concussive shot snare");
                creators.erase("arcane shot");
                creators.erase("misdirection on party");
                creators.erase("wyvern sting");
                creators.erase("counterstrike");
                creators.erase("pet not happy");
            }

        private:
            static Trigger* serpent_sting_on_attacker(PlayerbotAI* ai) { return new SerpentStingOnAttackerTrigger(ai); }
            static Trigger* trueshot_aura(PlayerbotAI* ai) { return new TrueshotAuraTrigger(ai); }
            static Trigger* aspect_of_the_viper(PlayerbotAI* ai) { return new HunterAspectOfTheViperTrigger(ai); }
            static Trigger* black_arrow(PlayerbotAI* ai) { return new BlackArrowTrigger(ai); }
            static Trigger* NoStings(PlayerbotAI* ai) { return new HunterNoStingsActiveTrigger(ai); }
            static Trigger* hunters_pet_dead(PlayerbotAI* ai) { return new HuntersPetDeadTrigger(ai); }
            static Trigger* hunters_pet_low_health(PlayerbotAI* ai) { return new HuntersPetLowHealthTrigger(ai); }
            static Trigger* hunters_mark(PlayerbotAI* ai) { return new HuntersMarkTrigger(ai); }
            static Trigger* freezing_trap_cc(PlayerbotAI* ai) { return new FreezingTrapTrigger(ai); }
            static Trigger* aspect_of_the_pack(PlayerbotAI* ai) { return new HunterAspectOfThePackTrigger(ai); }
            static Trigger* rapid_fire(PlayerbotAI* ai) { return new RapidFireTrigger(ai); }
            static Trigger* kill_command(PlayerbotAI* ai) { return new KillCommandTrigger(ai); }
            static Trigger* kill_shot(PlayerbotAI* ai) { return new KillShotTrigger(ai); }
            static Trigger* aspect_of_the_hawk(PlayerbotAI* ai) { return new HunterAspectOfTheHawkTrigger(ai); }
            static Trigger* aspect_of_the_dragonhawk(PlayerbotAI* ai) { return new HunterAspectOfTheDragonHawkTrigger(ai); }
            static Trigger* aspect_of_the_wild(PlayerbotAI* ai) { return new HunterAspectOfTheWildTrigger(ai); }
            static Trigger* silencing_shot_interrupt(PlayerbotAI* ai) { return new SilencingShotInterruptSpellTrigger(ai); }
            static Trigger* concussive_shot_snare(PlayerbotAI* ai) { return new ConcussiveShotSnareTrigger(ai); }
            static Trigger* silencing_shot_on_enemy_healer(PlayerbotAI* ai) { return new SilencingShotEnemyHealerTrigger(ai); }
            static Trigger* arcane_shot(PlayerbotAI* ai) { return new ArcaneShotOnAttackerTrigger(ai); }
            static Trigger* misdirection_on_party(PlayerbotAI* ai) { return new MisdirectionOnPartyTrigger(ai); }
            static Trigger* wyvern_sting(PlayerbotAI* ai) { return new WyvernStingTrigger(ai); }
            static Trigger* counterstrike(PlayerbotAI* ai) { return new CounterstrikeTrigger(ai); }
	    static Trigger* pet_not_happy(PlayerbotAI* ai) { return new HunterPetNotHappy(ai); }
        };
    };
};



namespace ai
{
    namespace hunter
    {
        using namespace ai;

        class AiObjectContextInternal : public NamedObjectContext<Action>
        {
        public:
            AiObjectContextInternal()
            {
                creators["auto shot"] = &AiObjectContextInternal::auto_shot;
                creators["aimed shot"] = &AiObjectContextInternal::aimed_shot;
                creators["chimera shot"] = &AiObjectContextInternal::chimera_shot;
                creators["explosive shot"] = &AiObjectContextInternal::explosive_shot;
                creators["arcane shot"] = &AiObjectContextInternal::arcane_shot;
                creators["concussive shot"] = &AiObjectContextInternal::concussive_shot;
                creators["distracting shot"] = &AiObjectContextInternal::distracting_shot;
                creators["multi-shot"] = &AiObjectContextInternal::multi_shot;
                creators["volley"] = &AiObjectContextInternal::volley;
                creators["serpent sting"] = &AiObjectContextInternal::serpent_sting;
                creators["serpent sting on attacker"] = &AiObjectContextInternal::serpent_sting_on_attacker;
                creators["misdirection on party"] = &AiObjectContextInternal::misdirection_on_party;
                creators["wyvern sting"] = &AiObjectContextInternal::wyvern_sting;
                creators["wyvern sting on cc"] = &AiObjectContextInternal::wyvern_sting_on_cc;
                creators["prepare attack"] = &AiObjectContextInternal::freezing_trap;
                creators["viper sting"] = &AiObjectContextInternal::viper_sting;
                creators["scorpid sting"] = &AiObjectContextInternal::scorpid_sting;
                creators["hunter's mark"] = &AiObjectContextInternal::hunters_mark;
                creators["mend pet"] = &AiObjectContextInternal::mend_pet;
                creators["revive pet"] = &AiObjectContextInternal::revive_pet;
                creators["call pet"] = &AiObjectContextInternal::call_pet;
                creators["black arrow"] = &AiObjectContextInternal::black_arrow;
                creators["frost trap"] = &AiObjectContextInternal::frost_trap;
                creators["freezing trap"] = &AiObjectContextInternal::freezing_trap;
                creators["freezing trap on cc"] = &AiObjectContextInternal::freezing_trap_on_cc;
                creators["rapid fire"] = &AiObjectContextInternal::rapid_fire;
                creators["boost"] = &AiObjectContextInternal::rapid_fire;
                creators["readiness"] = &AiObjectContextInternal::readiness_action;
                creators["aspect of the hawk"] = &AiObjectContextInternal::aspect_of_the_hawk;
                creators["aspect of the dragonhawk"] = &AiObjectContextInternal::aspect_of_the_dragonhawk;
                creators["aspect of the wild"] = &AiObjectContextInternal::aspect_of_the_wild;
                creators["aspect of the monkey"] = &AiObjectContextInternal::aspect_of_the_monkey;
                creators["aspect of the viper"] = &AiObjectContextInternal::aspect_of_the_viper;
                creators["aspect of the pack"] = &AiObjectContextInternal::aspect_of_the_pack;
                creators["aspect of the cheetah"] = &AiObjectContextInternal::aspect_of_the_cheetah;
                creators["trueshot aura"] = &AiObjectContextInternal::trueshot_aura;
                creators["feign death"] = &AiObjectContextInternal::feign_death;
                creators["wing clip"] = &AiObjectContextInternal::wing_clip;
                creators["steady shot"] = &AiObjectContextInternal::steady_shot;
                creators["kill command"] = &AiObjectContextInternal::kill_command;
                creators["kill shot"] = &AiObjectContextInternal::kill_shot;
                creators["misdirection"] = &AiObjectContextInternal::misdirection;
                creators["silencing shot"] = &AiObjectContextInternal::silencing_shot;
                creators["bestial wrath"] = &AiObjectContextInternal::bestial_wrath;
                creators["intimidation"] = &AiObjectContextInternal::intimidation;
                creators["deterrence"] = &AiObjectContextInternal::deterrence;
                creators["disengage"] = &AiObjectContextInternal::disengage;
                creators["readiness"] = &AiObjectContextInternal::readiness;
                creators["scatter shot"] = &AiObjectContextInternal::scatter_shot;
                creators["counterattack"] = &AiObjectContextInternal::counterattack;
                creators["snake trap"] = &AiObjectContextInternal::snake_trap;
                creators["immolation trap"] = &AiObjectContextInternal::immolation_trap;
                creators["explosive trap"] = &AiObjectContextInternal::explosive_trap;
                creators["instant action"] = &AiObjectContextInternal::explosive_shot;
		creators["feed pet"] = &AiObjectContextInternal::feed_pet;
            }
            ~AiObjectContextInternal()
            {
                creators.erase("auto shot");
                creators.erase("aimed shot");
                creators.erase("chimera shot");
                creators.erase("explosive shot");
                creators.erase("arcane shot");
                creators.erase("concussive shot");
                creators.erase("distracting shot");
                creators.erase("multi-shot");
                creators.erase("volley");
                creators.erase("serpent sting");
                creators.erase("serpent sting on attacker");
                creators.erase("misdirection on party");
                creators.erase("wyvern sting");
                creators.erase("wyvern sting on cc");
                creators.erase("prepare attack");
                creators.erase("viper sting");
                creators.erase("scorpid sting");
                creators.erase("hunter's mark");
                creators.erase("mend pet");
                creators.erase("revive pet");
                creators.erase("call pet");
                creators.erase("black arrow");
                creators.erase("frost trap");
                creators.erase("freezing trap");
                creators.erase("freezing trap on cc");
                creators.erase("rapid fire");
                creators.erase("boost");
                creators.erase("readiness");
                creators.erase("aspect of the hawk");
                creators.erase("aspect of the dragonhawk");
                creators.erase("aspect of the wild");
                creators.erase("aspect of the monkey");
                creators.erase("aspect of the viper");
                creators.erase("aspect of the pack");
                creators.erase("aspect of the cheetah");
                creators.erase("trueshot aura");
                creators.erase("feign death");
                creators.erase("wing clip");
                creators.erase("steady shot");
                creators.erase("kill command");
                creators.erase("kill shot");
                creators.erase("misdirection");
                creators.erase("silencing shot");
                creators.erase("bestial wrath");
                creators.erase("intimidation");
                creators.erase("deterrence");
                creators.erase("disengage");
                creators.erase("readiness");
                creators.erase("scatter shot");
                creators.erase("counterattack");
                creators.erase("snake trap");
                creators.erase("immolation trap");
                creators.erase("explosive trap");
		creators.erase("feed pet");
            }

        private:
	    static Action* feed_pet(PlayerbotAI* ai) { return new FeedPetAction(ai); }
            static Action* feign_death(PlayerbotAI* ai) { return new CastFeignDeathAction(ai); }
            static Action* trueshot_aura(PlayerbotAI* ai) { return new CastTrueshotAuraAction(ai); }
            static Action* auto_shot(PlayerbotAI* ai) { return new CastAutoShotAction(ai); }
            static Action* aimed_shot(PlayerbotAI* ai) { return new CastAimedShotAction(ai); }
            static Action* chimera_shot(PlayerbotAI* ai) { return new CastChimeraShotAction(ai); }
            static Action* explosive_shot(PlayerbotAI* ai) { return new CastExplosiveShotAction(ai); }
            static Action* arcane_shot(PlayerbotAI* ai) { return new CastArcaneShotAction(ai); }
            static Action* concussive_shot(PlayerbotAI* ai) { return new CastConcussiveShotAction(ai); }
            static Action* distracting_shot(PlayerbotAI* ai) { return new CastDistractingShotAction(ai); }
            static Action* multi_shot(PlayerbotAI* ai) { return new CastMultiShotAction(ai); }
            static Action* volley(PlayerbotAI* ai) { return new CastVolleyAction(ai); }
            static Action* serpent_sting(PlayerbotAI* ai) { return new CastSerpentStingAction(ai); }
            static Action* serpent_sting_on_attacker(PlayerbotAI* ai) { return new CastSerpentStingOnAttackerAction(ai); }
            static Action* misdirection_on_party(PlayerbotAI* ai) { return new CastMisdirectionOnPartyAction(ai); }
            static Action* wyvern_sting(PlayerbotAI* ai) { return new CastWyvernStingAction(ai); }
            static Action* wyvern_sting_on_cc(PlayerbotAI* ai) { return new CastWyvernStingCcAction(ai); }
            static Action* viper_sting(PlayerbotAI* ai) { return new CastViperStingAction(ai); }
            static Action* scorpid_sting(PlayerbotAI* ai) { return new CastScorpidStingAction(ai); }
            static Action* hunters_mark(PlayerbotAI* ai) { return new CastHuntersMarkAction(ai); }
            static Action* mend_pet(PlayerbotAI* ai) { return new CastMendPetAction(ai); }
            static Action* revive_pet(PlayerbotAI* ai) { return new CastRevivePetAction(ai); }
            static Action* call_pet(PlayerbotAI* ai) { return new CastCallPetAction(ai); }
            static Action* black_arrow(PlayerbotAI* ai) { return new CastBlackArrow(ai); }
            static Action* frost_trap(PlayerbotAI* ai) { return new CastFrostTrapAction(ai); }
            static Action* freezing_trap(PlayerbotAI* ai) { return new CastFreezingTrapAction(ai); }
            static Action* freezing_trap_on_cc(PlayerbotAI* ai) { return new CastFreezingTrapCcAction(ai); }
            static Action* rapid_fire(PlayerbotAI* ai) { return new CastRapidFireAction(ai); }
            static Action* readiness(PlayerbotAI* ai) { return new CastReadinessAction(ai); }
            static Action* aspect_of_the_hawk(PlayerbotAI* ai) { return new CastAspectOfTheHawkAction(ai); }
            static Action* aspect_of_the_dragonhawk(PlayerbotAI* ai) { return new CastAspectOfTheDragonHawkAction(ai); }
            static Action* aspect_of_the_wild(PlayerbotAI* ai) { return new CastAspectOfTheWildAction(ai); }
            static Action* aspect_of_the_viper(PlayerbotAI* ai) { return new CastAspectOfTheViperAction(ai); }
            static Action* aspect_of_the_pack(PlayerbotAI* ai) { return new CastAspectOfThePackAction(ai); }
            static Action* aspect_of_the_cheetah(PlayerbotAI* ai) { return new CastAspectOfTheCheetahAction(ai); }
            static Action* aspect_of_the_monkey(PlayerbotAI* ai) { return new CastAspectOfTheMonkeyAction(ai); }
            static Action* wing_clip(PlayerbotAI* ai) { return new CastWingClipAction(ai); }
            static Action* steady_shot(PlayerbotAI* ai) { return new CastSteadyShotAction(ai); }
            static Action* kill_command(PlayerbotAI* ai) { return new CastKillCommandAction(ai); }
            static Action* kill_shot(PlayerbotAI* ai) { return new CastKillShotAction(ai); }
            static Action* misdirection(PlayerbotAI* ai) { return new CastMisdirectionAction(ai); }
            static Action* silencing_shot(PlayerbotAI* ai) { return new CastSilencingShotAction(ai); }
            static Action* bestial_wrath(PlayerbotAI* ai) { return new CastBestialWrathAction(ai); }
            static Action* intimidation(PlayerbotAI* ai) { return new CastIntimidationAction(ai); }
            static Action* disengage(PlayerbotAI* ai) { return new CastDisengageAction(ai); }
            static Action* readiness_action(PlayerbotAI* ai) { return new CastReadinessAction(ai); }
            static Action* deterrence(PlayerbotAI* ai) { return new CastDeterrenceAction(ai); }
            static Action* scatter_shot(PlayerbotAI* ai) { return new CastScatterShotAction(ai); }
            static Action* counterattack(PlayerbotAI* ai) { return new CastCounterAttackAction(ai); }
            static Action* snake_trap(PlayerbotAI* ai) { return new CastSnakeTrapAction(ai); }
            static Action* immolation_trap(PlayerbotAI* ai) { return new CastImmolationTrapAction(ai); }
            static Action* explosive_trap(PlayerbotAI* ai) { return new CastExplosiveTrapAction(ai); }
        };
    };
};

HunterAiObjectContext::HunterAiObjectContext(PlayerbotAI* ai) : AiObjectContext(ai)
{
    strategyFactoryInternal = new ai::hunter::StrategyFactoryInternal();
    buffStrategyFactoryInternal = new ai::hunter::BuffStrategyFactoryInternal();
    aiObjectContextInternal = new ai::hunter::AiObjectContextInternal();
    triggerFactoryInternal = new ai::hunter::TriggerFactoryInternal();

    strategyContexts.Add(strategyFactoryInternal);
    strategyContexts.Add(buffStrategyFactoryInternal);
    actionContexts.Add(aiObjectContextInternal);
    triggerContexts.Add(triggerFactoryInternal);
}

HunterAiObjectContext::~HunterAiObjectContext()
{
    strategyContexts.Remove(strategyFactoryInternal);
    strategyContexts.Remove(buffStrategyFactoryInternal);
    actionContexts.Remove(aiObjectContextInternal);
    triggerContexts.Remove(triggerFactoryInternal);

    delete dynamic_cast<ai::hunter::StrategyFactoryInternal*>(strategyFactoryInternal);
    delete dynamic_cast<ai::hunter::StrategyFactoryInternal*>(buffStrategyFactoryInternal);
    delete dynamic_cast<ai::hunter::AiObjectContextInternal*>(aiObjectContextInternal);
    delete dynamic_cast<ai::hunter::TriggerFactoryInternal*>(triggerFactoryInternal);
}
