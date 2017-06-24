#pragma once

#include "../actions/GenericActions.h"
#include "../actions/UseItemAction.h"
#include "RogueComboActions.h"
#include "RogueOpeningActions.h"
#include "RogueFinishingActions.h"

namespace ai
{
	class CastStealthAction : public CastBuffSpellAction
	{
	public:
		CastStealthAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "stealth") {}
		virtual bool IsInstant() {return true;}
	};

	class CastEvasionAction : public CastBuffSpellAction
	{
	public:
		CastEvasionAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "evasion") {}

		virtual bool isUseful()
        {
            return (AI_VALUE2(bool, "combat", "self target") && AI_VALUE2(uint8, "health", "self target") < sPlayerbotAIConfig.lowHealth);
            }
        virtual bool IsInstant() {return true;}
	};

	class CastSprintAction : public CastBuffSpellAction
	{
	public:
		CastSprintAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "sprint") {}
		virtual bool IsInstant() {return true;}
	};

	class CastPremeditationAction : public CastBuffSpellAction
	{
	public:
		CastPremeditationAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "premeditation") {}
		virtual bool IsInstant() {return true;}
	};

	class CastPreparationAction : public CastBuffSpellAction
	{
	public:
		CastPreparationAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "preparation") {}
		virtual bool IsInstant() {return true;}
	};

	class CastKickAction : public CastSpellAction
	{
	public:
		CastKickAction(PlayerbotAI* ai) : CastSpellAction(ai, "kick") {}
		virtual bool IsInstant() {return true;}
	};

	class CastFeintAction : public CastBuffSpellAction
	{
	public:
		CastFeintAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "feint") {}
		virtual bool IsInstant() {return true;}
	};

	class CastDismantleAction : public CastSpellAction
	{
	public:
		CastDismantleAction(PlayerbotAI* ai) : CastSpellAction(ai, "dismantle") {}
		virtual bool IsInstant() {return true;}
	};

	class CastDistractAction : public CastSpellAction
	{
	public:
		CastDistractAction(PlayerbotAI* ai) : CastSpellAction(ai, "distract") {}
		virtual bool IsInstant() {return true;}
	};

	class CastVanishAction : public CastBuffSpellAction
	{
	public:
		CastVanishAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "vanish") {}

		virtual bool isUseful()
        {
            return (AI_VALUE2(uint8, "health", "self target") < sPlayerbotAIConfig.almostDead || AI_VALUE2(bool, "rooted", "self target"));
            }
        virtual bool IsInstant() {return true;}
	};

	class CastCloakOfShadowsAction : public CastBuffSpellAction
	{
	public:
		CastCloakOfShadowsAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "cloak of shadows") {}
		virtual bool IsInstant() {return true;}
	};

	class CastTricksOfTradeOnPartyAction : public  BuffOnPartyAction
	{
	public:
		CastTricksOfTradeOnPartyAction(PlayerbotAI* ai) :  BuffOnPartyAction(ai, "tricks of trade") {}
		virtual bool IsInstant() {return true;}
	};

	class CastBlindAction : public CastDebuffSpellAction
	{
	public:
		CastBlindAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "blind") {}
		virtual bool IsInstant() {return true;}
	};

    class CastShadowstepAction : public CastReachTargetSpellAction
	{
	public:
		CastShadowstepAction(PlayerbotAI* ai) : CastReachTargetSpellAction(ai, "shadowstep", 1.5f) {}
		virtual bool IsInstant() {return true;}
	};

    class CastColdBloodAction : public CastBuffSpellAction
	{
	public:
		CastColdBloodAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "cold blood") {}
		virtual bool IsInstant() {return true;}
	};

    class CastHungerForBloodAction : public CastBuffSpellAction
	{
	public:
		CastHungerForBloodAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "hunger for blood") {}
		virtual bool IsInstant() {return true;}
	};

	class CastBladeFlurryAction : public CastBuffSpellAction
	{
	public:
		CastBladeFlurryAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "blade flurry") {}
		virtual bool IsInstant() {return true;}
	};

	class CastAdrenalineRushAction : public CastBuffSpellAction
	{
	public:
		CastAdrenalineRushAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "adrenaline rush") {}
		virtual NextAction** getAlternatives();
		virtual bool IsInstant() {return true;}
	};

	class CastBurstAction : public CastBuffSpellAction
	{
	public:
		CastBurstAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "killing spree") {}
		virtual NextAction** getAlternatives();
	};

	class CastKillingSpreeAction : public CastBuffSpellAction
	{
	public:
		CastKillingSpreeAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "killing spree") {}
		virtual bool IsInstant() {return true;}
	};

    class CastShadowDanceAction : public CastBuffSpellAction
	{
	public:
		CastShadowDanceAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "shadow dance") {}
		virtual NextAction** getAlternatives();
		virtual bool IsInstant() {return true;}
	};

    class CastKickOnEnemyHealerAction : public CastSpellOnEnemyHealerAction
    {
    public:
        CastKickOnEnemyHealerAction(PlayerbotAI* ai) : CastSpellOnEnemyHealerAction(ai, "kick") {}
        virtual bool IsInstant() {return true;}
    };

    class UseInstantPoisonMainhandAction : public UseItemAction
    {
    public:
        UseInstantPoisonMainhandAction(PlayerbotAI* ai) : UseItemAction(ai, "instant poison") {setTargetMainhand();}
    };

    class UseInstantPoisonOffhandAction : public UseItemAction
    {
    public:
        UseInstantPoisonOffhandAction(PlayerbotAI* ai) : UseItemAction(ai, "instant poison") {setTargetOffhand();}
    };

    class UseDeadlyPoisonMainhandAction : public UseItemAction
    {
    public:
        UseDeadlyPoisonMainhandAction(PlayerbotAI* ai) : UseItemAction(ai, "deadly poison") {setTargetMainhand();}
    };

    class UseDeadlyPoisonOffhandAction : public UseItemAction
    {
    public:
        UseDeadlyPoisonOffhandAction(PlayerbotAI* ai) : UseItemAction(ai, "deadly poison") {setTargetOffhand();}
    };

    class UseWoundPoisonMainhandAction : public UseItemAction
    {
    public:
        UseWoundPoisonMainhandAction(PlayerbotAI* ai) : UseItemAction(ai, "wound poison") {setTargetMainhand();}
    };

    class UseWoundPoisonOffhandAction : public UseItemAction
    {
    public:
        UseWoundPoisonOffhandAction(PlayerbotAI* ai) : UseItemAction(ai, "wound poison") {setTargetOffhand();}
    };

    class UseCripplingPoisonMainhandAction : public UseItemAction
    {
    public:
        UseCripplingPoisonMainhandAction(PlayerbotAI* ai) : UseItemAction(ai, "crippling poison") {setTargetMainhand();}
    };

    class UseCripplingPoisonOffhandAction : public UseItemAction
    {
    public:
        UseCripplingPoisonOffhandAction(PlayerbotAI* ai) : UseItemAction(ai, "crippling poison") {setTargetOffhand();}
    };

    class UseMindNumbingPoisonMainhandAction : public UseItemAction
    {
    public:
        UseMindNumbingPoisonMainhandAction(PlayerbotAI* ai) : UseItemAction(ai, "mind-numbing poison") {setTargetMainhand();}
    };

    class UseMindNumbingPoisonOffhandAction : public UseItemAction
    {
    public:
        UseMindNumbingPoisonOffhandAction(PlayerbotAI* ai) : UseItemAction(ai, "mind-numbing poison") {setTargetOffhand();}
    };

}
