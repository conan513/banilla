#pragma once

#include "GenericActions.h"
#include "NonCombatActions.h"
#include "EmoteAction.h"
#include "AddLootAction.h"
#include "LootAction.h"
#include "AddLootAction.h"
#include "StayActions.h"
#include "FollowActions.h"
#include "ChangeStrategyAction.h"
#include "ChooseTargetActions.h"
#include "SuggestWhatToDoAction.h"
#include "PositionAction.h"
#include "AttackAction.h"
#include "CheckMailAction.h"
#include "DelayAction.h"
#include "OutfitAction.h"
#include "SayAction.h"
#include "CheckMountStateAction.h"
#include "RevealGatheringItemAction.h"
#include "OutfitAction.h"
#include "RandomBotUpdateAction.h"

namespace ai
{
    class ActionContext : public NamedObjectContext<Action>
    {
    public:
        ActionContext()
        {
            creators["attack"] = &ActionContext::melee;
            creators["melee"] = &ActionContext::melee;
            creators["reach spell"] = &ActionContext::ReachSpell;
            creators["reach melee"] = &ActionContext::ReachMelee;
            creators["flee"] = &ActionContext::flee;
            creators["disperse"] = &ActionContext::disperse;
            creators["gift of the naaru"] = &ActionContext::gift_of_the_naaru;
            creators["gift of the naaru on party"] = &ActionContext::gift_of_the_naaru_on_party;
            creators["shoot"] = &ActionContext::shoot;
            creators["lifeblood"] = &ActionContext::lifeblood;
            creators["arcane torrent"] = &ActionContext::arcane_torrent;
            creators["will of the forsaken"] = &ActionContext::will_of_the_forsaken;
            creators["blood fury"] = &ActionContext::blood_fury;
            creators["berserking"] = &ActionContext::berserking;
            creators["racial boost"] = &ActionContext::berserking;
            creators["cannibalize"] = &ActionContext::cannibalize;
            creators["war stomp"] = &ActionContext::war_stomp;
            creators["every man for himself"] = &ActionContext::every_man_for_himself;
            creators["shadowmelt"] = &ActionContext::shadowmelt;
            creators["escape artist"] = &ActionContext::escape_artist;
            creators["stoneform"] = &ActionContext::stoneform;
            creators["end pull"] = &ActionContext::end_pull;
            creators["healthstone"] = &ActionContext::healthstone;
            creators["bandage"] = &ActionContext::bandage;
            creators["healing potion"] = &ActionContext::healing_potion;
            creators["mana potion"] = &ActionContext::mana_potion;
            creators["food"] = &ActionContext::food;
            creators["drink"] = &ActionContext::drink;
            creators["bomb"] = &ActionContext::bomb;
            creators["tank assist"] = &ActionContext::tank_assist;
            creators["dps assist"] = &ActionContext::dps_assist;
            creators["attack rti target"] = &ActionContext::attack_rti_target;
            creators["loot"] = &ActionContext::loot;
            creators["add loot"] = &ActionContext::add_loot;
            creators["add gathering loot"] = &ActionContext::add_gathering_loot;
            creators["add all loot"] = &ActionContext::add_all_loot;
            creators["shoot"] = &ActionContext::shoot;
            creators["follow"] = &ActionContext::follow;
            creators["throw"] = &ActionContext::throwaction;
            creators["runaway"] = &ActionContext::runaway;
            creators["stay"] = &ActionContext::stay;
            creators["attack anything"] = &ActionContext::attack_anything;
            creators["attack least hp target"] = &ActionContext::attack_least_hp_target;
            creators["attack enemy player"] = &ActionContext::enemy_player_target;
            creators["emote"] = &ActionContext::emote;
            creators["suggest what to do"] = &ActionContext::suggest_what_to_do;
			creators["suggest trade"] = &ActionContext::suggest_trade;
            creators["move random"] = &ActionContext::move_random;
            creators["move to loot"] = &ActionContext::move_to_loot;
            creators["open loot"] = &ActionContext::open_loot;
            creators["guard"] = &ActionContext::guard;
            creators["move out of enemy contact"] = &ActionContext::move_out_of_enemy_contact;
            creators["set facing"] = &ActionContext::set_facing;
            creators["attack duel opponent"] = &ActionContext::attack_duel_opponent;
            creators["drop target"] = &ActionContext::drop_target;
            creators["check mail"] = &ActionContext::check_mail;
            creators["say"] = &ActionContext::say;
            creators["reposition"] = &ActionContext::reposition;
			creators["move to guestgiver"] = &ActionContext::move_questgiver;
			creators["move to guestender"] = &ActionContext::move_questender;
			creators["move to quest"] = &ActionContext::move_quest;
			creators["mount"] = &ActionContext::mount;
			creators["reveal gathering item"] = &ActionContext::reveal_gathering_item;
			creators["outfit"] = &ActionContext::outfit;
			creators["random bot update"] = &ActionContext::random_bot_update;
			creators["delay"] = &ActionContext::delay;
        }
		~ActionContext()
		{			
			creators.erase("attack");
			creators.erase("melee");
			creators.erase("reach spell");
			creators.erase("reach melee");
			creators.erase("flee");
			creators.erase("disperse");
			creators.erase("gift of the naaru");
			creators.erase("gift of the naaru on party");
			creators.erase("shoot");
			creators.erase("lifeblood");
			creators.erase("arcane torrent");
			creators.erase("will of the forsaken");
			creators.erase("blood fury");
			creators.erase("berserking");
			creators.erase("racial boost");
			creators.erase("cannibalize");
			creators.erase("war stomp");
			creators.erase("every man for himself");
			creators.erase("shadowmelt");
			creators.erase("escape artist");
			creators.erase("stoneform");
			creators.erase("end pull");
			creators.erase("healthstone");
			creators.erase("bandage");
			creators.erase("healing potion");
			creators.erase("mana potion");
			creators.erase("food");
			creators.erase("drink");
			creators.erase("bomb");
			creators.erase("tank assist");
			creators.erase("dps assist");
			creators.erase("attack rti target");
			creators.erase("loot");
			creators.erase("add loot");
			creators.erase("add gathering loot");
			creators.erase("add all loot");
			creators.erase("shoot");
			creators.erase("follow");
			creators.erase("throw");
			creators.erase("runaway");
			creators.erase("stay");
			creators.erase("attack anything");
			creators.erase("attack least hp target");
			creators.erase("attack enemy player");
			creators.erase("emote");
			creators.erase("suggest what to do");
			creators.erase("suggest trade");
			creators.erase("move random");
			creators.erase("move to loot");
			creators.erase("open loot");
			creators.erase("guard");
			creators.erase("move out of enemy contact");
			creators.erase("set facing");
			creators.erase("attack duel opponent");
			creators.erase("drop target");
			creators.erase("check mail");
			creators.erase("say");
			creators.erase("reposition");
			creators.erase("move to guestgiver");
			creators.erase("move to guestender");
			creators.erase("move to quest");
			creators.erase("mount");
			creators.erase("reveal gathering item");
			creators.erase("outfit");
			creators.erase("random bot update");
			creators.erase("delay");
		}

    private:
        static Action* check_mail(PlayerbotAI* ai) { return new CheckMailAction(ai); }
        static Action* drop_target(PlayerbotAI* ai) { return new DropTargetAction(ai); }
        static Action* attack_duel_opponent(PlayerbotAI* ai) { return new AttackDuelOpponentAction(ai); }
        static Action* guard(PlayerbotAI* ai) { return new GuardAction(ai); }
        static Action* open_loot(PlayerbotAI* ai) { return new OpenLootAction(ai); }
        static Action* move_to_loot(PlayerbotAI* ai) { return new MoveToLootAction(ai); }
        static Action* move_random(PlayerbotAI* ai) { return new MoveRandomAction(ai); }
        static Action* shoot(PlayerbotAI* ai) { return new CastShootAction(ai); }
        static Action* throwaction(PlayerbotAI* ai) { return new CastThrowAction(ai); }
        static Action* melee(PlayerbotAI* ai) { return new MeleeAction(ai); }
        static Action* ReachSpell(PlayerbotAI* ai) { return new ReachSpellAction(ai); }
        static Action* ReachMelee(PlayerbotAI* ai) { return new ReachMeleeAction(ai); }
        static Action* flee(PlayerbotAI* ai) { return new FleeAction(ai); }
        static Action* disperse(PlayerbotAI* ai) { return new DisperseAction(ai); }
        static Action* gift_of_the_naaru(PlayerbotAI* ai) { return new CastGiftOfTheNaaruAction(ai); }
        static Action* gift_of_the_naaru_on_party(PlayerbotAI* ai) { return new CastGiftOfTheNaaruOnPartyAction(ai); }
        static Action* lifeblood(PlayerbotAI* ai) { return new CastLifeBloodAction(ai); }
        static Action* arcane_torrent(PlayerbotAI* ai) { return new CastArcaneTorrentAction(ai); }
        static Action* end_pull(PlayerbotAI* ai) { return new ChangeCombatStrategyAction(ai, "-pull"); }

        static Action* will_of_the_forsaken(PlayerbotAI* ai) { return new CastWillOfTheForsakenAction(ai); }
        static Action* blood_fury(PlayerbotAI* ai) { return new CastBloodFuryAction(ai); }
        static Action* berserking(PlayerbotAI* ai) { return new CastBerserkingAction(ai); }
        static Action* cannibalize(PlayerbotAI* ai) { return new CastCannibalizeAction(ai); }
        static Action* war_stomp(PlayerbotAI* ai) { return new CastWarStompAction(ai); }
        static Action* every_man_for_himself(PlayerbotAI* ai) { return new CastEveryManForHimselfAction(ai); }
        static Action* shadowmelt(PlayerbotAI* ai) { return new CastShadowmeltAction(ai); }
        static Action* escape_artist(PlayerbotAI* ai) { return new CastEscapeArtistAction(ai); }
        static Action* stoneform(PlayerbotAI* ai) { return new CastStoneformAction(ai); }

        static Action* emote(PlayerbotAI* ai) { return new EmoteAction(ai); }
        static Action* suggest_what_to_do(PlayerbotAI* ai) { return new SuggestWhatToDoAction(ai); }
		static Action* suggest_trade(PlayerbotAI* ai) { return new SuggestTradeAction(ai); }
        static Action* attack_anything(PlayerbotAI* ai) { return new AttackAnythingAction(ai); }
        static Action* attack_least_hp_target(PlayerbotAI* ai) { return new AttackLeastHpTargetAction(ai); }
        static Action* enemy_player_target(PlayerbotAI* ai) { return new AttackEnemyPlayerAction(ai); }
        static Action* stay(PlayerbotAI* ai) { return new StayAction(ai); }
        static Action* runaway(PlayerbotAI* ai) { return new RunAwayAction(ai); }
        static Action* follow(PlayerbotAI* ai) { return new FollowAction(ai); }
        static Action* add_gathering_loot(PlayerbotAI* ai) { return new AddGatheringLootAction(ai); }
        static Action* add_loot(PlayerbotAI* ai) { return new AddLootAction(ai); }
        static Action* add_all_loot(PlayerbotAI* ai) { return new AddAllLootAction(ai); }
        static Action* loot(PlayerbotAI* ai) { return new LootAction(ai); }
        static Action* dps_assist(PlayerbotAI* ai) { return new DpsAssistAction(ai); }
        static Action* attack_rti_target(PlayerbotAI* ai) { return new AttackRtiTargetAction(ai); }
        static Action* tank_assist(PlayerbotAI* ai) { return new TankAssistAction(ai); }
        static Action* drink(PlayerbotAI* ai) { return new DrinkAction(ai); }
        static Action* food(PlayerbotAI* ai) { return new EatAction(ai); }
        static Action* bomb(PlayerbotAI* ai) { return new UseBombAction(ai); }
        static Action* bandage(PlayerbotAI* ai) { return new BandageAction(ai); }
        static Action* mana_potion(PlayerbotAI* ai) { return new UseManaPotion(ai); }
        static Action* healing_potion(PlayerbotAI* ai) { return new UseHealingPotion(ai); }
        static Action* healthstone(PlayerbotAI* ai) { return new UseItemAction(ai, "healthstone"); }
        static Action* move_out_of_enemy_contact(PlayerbotAI* ai) { return new MoveOutOfEnemyContactAction(ai); }
        static Action* set_facing(PlayerbotAI* ai) { return new SetFacingTargetAction(ai); }
        static Action* say(PlayerbotAI* ai) { return new SayAction(ai); }
        static Action* reposition(PlayerbotAI* ai) { return new RepositionAction(ai); }
		static Action* move_questgiver(PlayerbotAI* ai) { return new MoveQuestGiverAction(ai); }
		static Action* move_questender(PlayerbotAI* ai) { return new MoveQuestEnderAction(ai); }
		static Action* move_quest(PlayerbotAI* ai) { return new MoveQuestPositionAction(ai); }
		static Action* mount(PlayerbotAI *ai) { return new CastSpellAction(ai, "mount"); }
		static Action* reveal_gathering_item(PlayerbotAI* ai) { return new RevealGatheringItemAction(ai); }
		static Action* outfit(PlayerbotAI* ai) { return new OutfitAction(ai); }
		static Action* random_bot_update(PlayerbotAI* ai) { return new RandomBotUpdateAction(ai); }
		static Action* delay(PlayerbotAI* ai) { return new DelayAction(ai); }
    };

};
