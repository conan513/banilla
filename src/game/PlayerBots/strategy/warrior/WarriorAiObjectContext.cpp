#include "../../../botpch.h"
#include "../../playerbot.h"
#include "WarriorActions.h"
#include "WarriorAiObjectContext.h"
#include "GenericWarriorNonCombatStrategy.h"
#include "TankWarriorStrategy.h"
#include "DpsWarriorStrategy.h"
#include "../generic/PullStrategy.h"
#include "WarriorTriggers.h"
#include "../NamedObjectContext.h"

using namespace ai;


namespace ai
{
    namespace warrior
    {
        using namespace ai;

        class StrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            StrategyFactoryInternal()
            {
                creators["nc"] = &warrior::StrategyFactoryInternal::nc;
                creators["pull"] = &warrior::StrategyFactoryInternal::pull;
                creators["aoe"] = &warrior::StrategyFactoryInternal::aoe;
            }

        private:
            static Strategy* nc(PlayerbotAI* ai) { return new GenericWarriorNonCombatStrategy(ai); }
            static Strategy* aoe(PlayerbotAI* ai) { return new DpsWarriorAoeStrategy(ai); }
            static Strategy* pull(PlayerbotAI* ai) { return new PullStrategy(ai, "shoot"); }
        };

        class CombatStrategyFactoryInternal : public NamedObjectContext<Strategy>
        {
        public:
            CombatStrategyFactoryInternal() : NamedObjectContext<Strategy>(false, true)
            {
                creators["tank"] = &warrior::CombatStrategyFactoryInternal::tank;
                creators["dps"] = &warrior::CombatStrategyFactoryInternal::dps;
                creators["arms"] = &warrior::CombatStrategyFactoryInternal::arms;
                creators["fury"] = &warrior::CombatStrategyFactoryInternal::fury;
            }

        private:
            static Strategy* tank(PlayerbotAI* ai) { return new TankWarriorStrategy(ai); }
            static Strategy* dps(PlayerbotAI* ai) { return new DpsWarriorStrategy(ai); }
            static Strategy* arms(PlayerbotAI* ai) { return new DpsArmsWarriorStrategy(ai); }
            static Strategy* fury(PlayerbotAI* ai) { return new DpsFuryWarriorStrategy(ai); }
        };
    };
};

namespace ai
{
    namespace warrior
    {
        using namespace ai;

        class TriggerFactoryInternal : public NamedObjectContext<Trigger>
        {
        public:
            TriggerFactoryInternal()
            {
                creators["hamstring"] = &TriggerFactoryInternal::hamstring;
                creators["victory rush"] = &TriggerFactoryInternal::victory_rush;
              //  creators["death wish"] = &TriggerFactoryInternal::death_wish;
                creators["battle shout"] = &TriggerFactoryInternal::battle_shout;
                creators["rend"] = &TriggerFactoryInternal::rend;
                creators["demoralizing shout"] = &TriggerFactoryInternal::demoralizing_shout;
                creators["rend on attacker"] = &TriggerFactoryInternal::rend_on_attacker;
                creators["vigilance on master"] = &TriggerFactoryInternal::vigilance_on_master;
                creators["bloodrage"] = &TriggerFactoryInternal::bloodrage;
                creators["shield bash"] = &TriggerFactoryInternal::shield_bash;
                creators["disarm"] = &TriggerFactoryInternal::disarm;
                creators["concussion blow"] = &TriggerFactoryInternal::concussion_blow;
                creators["sword and board"] = &TriggerFactoryInternal::SwordAndBoard;
                creators["sudden death"] = &TriggerFactoryInternal::sudden_death;
                creators["taste for blood"] = &TriggerFactoryInternal::taste_for_blood;
                creators["shield bash on enemy healer"] = &TriggerFactoryInternal::shield_bash_on_enemy_healer;

            }

        private:
            static Trigger* hamstring(PlayerbotAI* ai) { return new HamstringTrigger(ai); }
            static Trigger* victory_rush(PlayerbotAI* ai) { return new VictoryRushTrigger(ai); }
    //        static Trigger* death_wish(PlayerbotAI* ai) { return new DeathWishTrigger(ai); }
            static Trigger* battle_shout(PlayerbotAI* ai) { return new BattleShoutTrigger(ai); }
            static Trigger* demoralizing_shout(PlayerbotAI* ai) { return new DemoralizingShoutDebuffTrigger(ai); }
            static Trigger* rend(PlayerbotAI* ai) { return new RendDebuffTrigger(ai); }
            static Trigger* rend_on_attacker(PlayerbotAI* ai) { return new RendDebuffOnAttackerTrigger(ai); }
            static Trigger* vigilance_on_master(PlayerbotAI* ai) { return new VigilanceOnMasterTrigger(ai); }
            static Trigger* bloodrage(PlayerbotAI* ai) { return new BloodrageDebuffTrigger(ai); }
            static Trigger* shield_bash(PlayerbotAI* ai) { return new ShieldBashInterruptSpellTrigger(ai); }
            static Trigger* disarm(PlayerbotAI* ai) { return new DisarmDebuffTrigger(ai); }
            static Trigger* concussion_blow(PlayerbotAI* ai) { return new ConcussionBlowTrigger(ai); }
            static Trigger* SwordAndBoard(PlayerbotAI* ai) { return new SwordAndBoardTrigger(ai); }
            static Trigger* sudden_death(PlayerbotAI* ai) { return new SuddenDeathTrigger(ai); }
            static Trigger* taste_for_blood(PlayerbotAI* ai) { return new TasteForBloodTrigger(ai); }
            static Trigger* shield_bash_on_enemy_healer(PlayerbotAI* ai) { return new ShieldBashInterruptEnemyHealerSpellTrigger(ai); }
        };
    };
};


namespace ai
{
    namespace warrior
    {
        using namespace ai;

        class AiObjectContextInternal : public NamedObjectContext<Action>
        {
        public:
            AiObjectContextInternal()
            {
                creators["devastate"] = &AiObjectContextInternal::devastate;
                creators["overpower"] = &AiObjectContextInternal::overpower;
                creators["charge"] = &AiObjectContextInternal::charge;
                creators["boost"] = &AiObjectContextInternal::boost_warrior;
                creators["bloodthirst"] = &AiObjectContextInternal::bloodthirst;
                creators["rend"] = &AiObjectContextInternal::rend;
                creators["rend on attacker"] = &AiObjectContextInternal::rend_on_attacker;
                creators["mocking blow"] = &AiObjectContextInternal::mocking_blow;
      //          creators["death wish"] = &AiObjectContextInternal::death_wish;
                creators["berserker rage"] = &AiObjectContextInternal::berserker_rage;
                creators["victory rush"] = &AiObjectContextInternal::victory_rush;
                creators["execute"] = &AiObjectContextInternal::execute;
                creators["defensive stance"] = &AiObjectContextInternal::defensive_stance;
                creators["hamstring"] = &AiObjectContextInternal::hamstring;
                creators["shield bash"] = &AiObjectContextInternal::shield_bash;
                creators["shield block"] = &AiObjectContextInternal::shield_block;
                creators["bloodrage"] = &AiObjectContextInternal::bloodrage;
                creators["battle stance"] = &AiObjectContextInternal::battle_stance;
                creators["berserker stance"] = &AiObjectContextInternal::berserker_stance;
                creators["heroic strike"] = &AiObjectContextInternal::heroic_strike;
                creators["intimidating shout"] = &AiObjectContextInternal::intimidating_shout;
                creators["demoralizing shout"] = &AiObjectContextInternal::demoralizing_shout;
                creators["challenging shout"] = &AiObjectContextInternal::challenging_shout;
                creators["shield wall"] = &AiObjectContextInternal::shield_wall;
                creators["battle shout"] = &AiObjectContextInternal::battle_shout;
                creators["thunder clap"] = &AiObjectContextInternal::thunder_clap;
                creators["taunt"] = &AiObjectContextInternal::taunt;
                creators["revenge"] = &AiObjectContextInternal::revenge;
                creators["slam"] = &AiObjectContextInternal::slam;
                creators["shield slam"] = &AiObjectContextInternal::shield_slam;
                creators["disarm"] = &AiObjectContextInternal::disarm;
                creators["sunder armor"] = &AiObjectContextInternal::sunder_armor;
                creators["last stand"] = &AiObjectContextInternal::last_stand;
                creators["shockwave"] = &AiObjectContextInternal::shockwave;
                creators["cleave"] = &AiObjectContextInternal::cleave;
                creators["intervene on party"] = &AiObjectContextInternal::intervene_on_party;
                creators["vigilance on master"] = &AiObjectContextInternal::vigilance_on_master;
                creators["vigilance on party"] = &AiObjectContextInternal::vigilance_on_party;
                creators["heroic fury"] = &AiObjectContextInternal::heroic_fury;
                creators["whirlwind"] = &AiObjectContextInternal::whirlwind;
                creators["intercept"] = &AiObjectContextInternal::intercept;
                creators["mortal strike"] = &AiObjectContextInternal::mortal_strike;
                creators["bladestorm"] = &AiObjectContextInternal::bladestorm;
                creators["sweeping strikes"] = &AiObjectContextInternal::sweeping_strikes;
                creators["retaliation"] = &AiObjectContextInternal::retaliation;
                creators["recklessness"] = &AiObjectContextInternal::recklessness;
                creators["spell reflect"] = &AiObjectContextInternal::spell_reflect;
                creators["shattering throw"] = &AiObjectContextInternal::shattering_throw;
                creators["heroic throw"] = &AiObjectContextInternal::heroic_throw;
                creators["concussion blow"] = &AiObjectContextInternal::concussion_blow;
                creators["shield bash on enemy healer"] = &AiObjectContextInternal::shield_bash_on_enemy_healer;
            }

        private:
            static Action* devastate(PlayerbotAI* ai) { return new CastDevastateAction(ai); }
            static Action* last_stand(PlayerbotAI* ai) { return new CastLastStandAction(ai); }
            static Action* shockwave(PlayerbotAI* ai) { return new CastShockwaveAction(ai); }
            static Action* cleave(PlayerbotAI* ai) { return new CastCleaveAction(ai); }
            static Action* concussion_blow(PlayerbotAI* ai) { return new CastConcussionBlowAction(ai); }
            static Action* taunt(PlayerbotAI* ai) { return new CastTauntAction(ai); }
            static Action* boost_warrior(PlayerbotAI* ai) { return new CastDeathWishAction(ai); }
            static Action* revenge(PlayerbotAI* ai) { return new CastRevengeAction(ai); }
            static Action* slam(PlayerbotAI* ai) { return new CastSlamAction(ai); }
            static Action* shield_slam(PlayerbotAI* ai) { return new CastShieldSlamAction(ai); }
            static Action* disarm(PlayerbotAI* ai) { return new CastDisarmAction(ai); }
            static Action* sunder_armor(PlayerbotAI* ai) { return new CastSunderArmorAction(ai); }
            static Action* overpower(PlayerbotAI* ai) { return new CastOverpowerAction(ai); }
            static Action* charge(PlayerbotAI* ai) { return new CastChargeAction(ai); }
            static Action* bloodthirst(PlayerbotAI* ai) { return new CastBloodthirstAction(ai); }
            static Action* rend(PlayerbotAI* ai) { return new CastRendAction(ai); }
            static Action* rend_on_attacker(PlayerbotAI* ai) { return new CastRendOnAttackerAction(ai); }
            static Action* mocking_blow(PlayerbotAI* ai) { return new CastMockingBlowAction(ai); }
            static Action* death_wish(PlayerbotAI* ai) { return new CastDeathWishAction(ai); }
            static Action* berserker_rage(PlayerbotAI* ai) { return new CastBerserkerRageAction(ai); }
            static Action* victory_rush(PlayerbotAI* ai) { return new CastVictoryRushAction(ai); }
            static Action* execute(PlayerbotAI* ai) { return new CastExecuteAction(ai); }
            static Action* defensive_stance(PlayerbotAI* ai) { return new CastDefensiveStanceAction(ai); }
            static Action* hamstring(PlayerbotAI* ai) { return new CastHamstringAction(ai); }
            static Action* shield_bash(PlayerbotAI* ai) { return new CastShieldBashAction(ai); }
            static Action* shield_block(PlayerbotAI* ai) { return new CastShieldBlockAction(ai); }
            static Action* bloodrage(PlayerbotAI* ai) { return new CastBloodrageAction(ai); }
            static Action* battle_stance(PlayerbotAI* ai) { return new CastBattleStanceAction(ai); }
            static Action* berserker_stance(PlayerbotAI* ai) { return new CastBerserkerStanceAction(ai); }
            static Action* heroic_strike(PlayerbotAI* ai) { return new CastHeroicStrikeAction(ai); }
            static Action* intimidating_shout(PlayerbotAI* ai) { return new CastIntimidatingShoutAction(ai); }
            static Action* demoralizing_shout(PlayerbotAI* ai) { return new CastDemoralizingShoutAction(ai); }
            static Action* challenging_shout(PlayerbotAI* ai) { return new CastChallengingShoutAction(ai); }
            static Action* shield_wall(PlayerbotAI* ai) { return new CastShieldWallAction(ai); }
            static Action* battle_shout(PlayerbotAI* ai) { return new CastBattleShoutAction(ai); }
            static Action* thunder_clap(PlayerbotAI* ai) { return new CastThunderClapAction(ai); }
            static Action* vigilance_on_master(PlayerbotAI* ai) { return new CastVigilanceOnMasterAction(ai); }
            static Action* intervene_on_party(PlayerbotAI* ai) { return new CastInterveneOnPartyAction(ai); }
            static Action* vigilance_on_party(PlayerbotAI* ai) { return new CastVigilanceOnPartyAction(ai); }
            static Action* heroic_fury(PlayerbotAI* ai) { return new CastHeroicFuryAction(ai); }
            static Action* whirlwind(PlayerbotAI* ai) { return new CastWhirlwindAction(ai); }
            static Action* intercept(PlayerbotAI* ai) { return new CastInterceptAction(ai); }
            static Action* mortal_strike(PlayerbotAI* ai) { return new CastMortalStrikeAction(ai); }
            static Action* bladestorm(PlayerbotAI* ai) { return new CastBladestormAction(ai); }
            static Action* sweeping_strikes(PlayerbotAI* ai) { return new CastSweepingStrikesAction(ai); }
            static Action* retaliation(PlayerbotAI* ai) { return new CastRetaliationAction(ai); }
            static Action* recklessness(PlayerbotAI* ai) { return new CastRecklessnessAction(ai); }
            static Action* spell_reflect(PlayerbotAI* ai) { return new CastSpellReflectAction(ai); }
            static Action* shattering_throw(PlayerbotAI* ai) { return new CastShatteringThrowAction(ai); }
            static Action* heroic_throw(PlayerbotAI* ai) { return new CastHeroicThrowAction(ai); }
            static Action* shield_bash_on_enemy_healer(PlayerbotAI* ai) { return new CastShieldBashOnEnemyHealerAction(ai); }

        };
    };
};

WarriorAiObjectContext::WarriorAiObjectContext(PlayerbotAI* ai) : AiObjectContext(ai)
{
    strategyContexts.Add(new ai::warrior::StrategyFactoryInternal());
    strategyContexts.Add(new ai::warrior::CombatStrategyFactoryInternal());
    actionContexts.Add(new ai::warrior::AiObjectContextInternal());
    triggerContexts.Add(new ai::warrior::TriggerFactoryInternal());
}
