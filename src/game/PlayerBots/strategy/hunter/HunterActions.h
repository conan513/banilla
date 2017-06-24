#pragma once

#include "../actions/GenericActions.h"

namespace ai
{
    BEGIN_RANGED_SPELL_ACTION(CastHuntersMarkAction, "hunter's mark")
    virtual bool IsInstant() {return true;}
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastAutoShotAction, "auto shot")
    virtual bool IsInstant() {return true;}
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastArcaneShotAction, "arcane shot")
    virtual bool IsInstant() {return true;}
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastExplosiveShotAction, "explosive shot")
    virtual bool IsInstant() {return true;}
    virtual NextAction** getAlternatives()
    {
            return NextAction::merge( NextAction::array(0, new NextAction("chimera shot"), NULL), CastSpellAction::getAlternatives());
       }
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastSteadyShotAction, "steady shot")
    virtual NextAction** getAlternatives()
    {
            return NextAction::merge( NextAction::array(0, new NextAction("arcane shot"), NULL), CastSpellAction::getAlternatives());
       }
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastAimedShotAction, "aimed shot")
    virtual bool IsInstant() {return true;}
    virtual NextAction** getAlternatives()
    {
            return NextAction::merge( NextAction::array(0, new NextAction("arcane shot"), NULL), CastSpellAction::getAlternatives());
       }
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastChimeraShotAction, "chimera shot")
    virtual NextAction** getAlternatives()
    {
            return NextAction::merge( NextAction::array(0, new NextAction("aimed shot"), NULL), CastSpellAction::getAlternatives());
       }
    virtual bool IsInstant() {return true;}
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastConcussiveShotAction, "concussive shot")
    virtual bool IsInstant() {return true;}
    virtual bool hasMultipliers() { return false; }
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastDistractingShotAction, "distracting shot")
    virtual bool IsInstant() {return true;}
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastSilencingShotAction, "silencing shot")
    virtual bool IsInstant() {return true;}
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastMisdirectionAction, "misdirection")
    virtual bool IsInstant() {return true;}
    virtual bool hasMultipliers() { return false; }
    END_SPELL_ACTION()

    class CastMisdirectionOnPartyAction : public BuffOnPartyAction
    {
    public:
        CastMisdirectionOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "misdirection") {}
        virtual bool isUseful();
        virtual bool hasMultipliers() { return false; }
    };

    class CasttMisdirectionOnMasterAction : public BuffOnPartyAction
    {
    public:
        CasttMisdirectionOnMasterAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "misdirection") {}
        virtual string getName() { return "misdirection on master";}
        virtual string GetTargetName() { return "master target";}
        virtual bool hasMultipliers() { return false; }
    };

    BEGIN_RANGED_SPELL_ACTION(CastMultiShotAction, "multi-shot")
    END_SPELL_ACTION()

	BEGIN_RANGED_SPELL_ACTION(CastVolleyAction, "volley")
	END_SPELL_ACTION()


    BEGIN_RANGED_SPELL_ACTION(CastWyvernStingAction, "wyvern sting")
    virtual bool IsInstant() {return true;}
    virtual bool hasMultipliers() { return false; }
    END_SPELL_ACTION()

    class CastWyvernStingCcAction : public CastBuffSpellAction
    {
    public:
        CastWyvernStingCcAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "wyvern sting on cc") {}
        virtual Value<Unit*>* GetTargetValue();
        virtual bool IsInstant() {return true;}
    };

   class CastSerpentStingAction : public CastDebuffSpellAction
   {
    public:
	CastSerpentStingAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "serpent sting") {}
    virtual bool IsInstant() {return true;}
   };

    class CastViperStingAction : public CastDebuffSpellAction
   {
    public:
	CastViperStingAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "viper sting") {}
    	virtual bool IsInstant() {return true;}
    	virtual bool isUseful();
   };

    BEGIN_RANGED_SPELL_ACTION(CastScorpidStingAction, "scorpid sting")
    virtual bool IsInstant() {return true;}
    END_SPELL_ACTION()

	class CastAspectOfTheHawkAction : public CastBuffSpellAction
	{
	public:
		CastAspectOfTheHawkAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "aspect of the hawk") {}
		virtual bool IsInstant() {return true;}
	};

	class CastAspectOfTheDragonHawkAction : public CastBuffSpellAction
	{
	public:
		CastAspectOfTheDragonHawkAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "aspect of the dragonhawk") {}
		virtual bool IsInstant() {return true;}
	};

	class CastAspectOfTheWildAction : public CastBuffSpellAction
	{
	public:
		CastAspectOfTheWildAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "aspect of the wild") {}
		virtual bool IsInstant() {return true;}
	};

	class CastAspectOfTheCheetahAction : public CastBuffSpellAction
	{
	public:
		CastAspectOfTheCheetahAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "aspect of the cheetah") {}
		virtual bool IsInstant() {return true;}
		virtual bool isUseful();
	};

	class CastAspectOfThePackAction : public CastBuffSpellAction
	{
	public:
		CastAspectOfThePackAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "aspect of the pack") {}
		virtual bool IsInstant() {return true;}
	};

	class CastAspectOfTheViperAction : public CastBuffSpellAction
	{
	public:
		CastAspectOfTheViperAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "aspect of the viper") {}
		virtual bool IsInstant() {return true;}
	};

	class CastAspectOfTheMonkeyAction : public CastBuffSpellAction
	{
	public:
		CastAspectOfTheMonkeyAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "aspect of the monkey") {}
		virtual bool IsInstant() {return true;}
	};

	class CastCallPetAction : public CastBuffSpellAction
	{
	public:
		CastCallPetAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "call pet") {}
		virtual bool IsInstant() {return true;}
	};

	class CastMendPetAction : public CastAuraSpellAction
	{
	public:
		CastMendPetAction(PlayerbotAI* ai) : CastAuraSpellAction(ai, "mend pet") {}
		virtual string GetTargetName() { return "pet target"; }
		virtual bool IsInstant() {return true;}
	};

	class CastRevivePetAction : public CastBuffSpellAction
	{
	public:
		CastRevivePetAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "revive pet") {}
		virtual bool isUseful() {return !AI_VALUE2(bool, "combat", "self target");}
	};

    class CastTrueshotAuraAction : public CastBuffSpellAction
    {
    public:
        CastTrueshotAuraAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "trueshot aura") {}
    };

    class CastFeignDeathAction : public CastBuffSpellAction
    {
    public:
        CastFeignDeathAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "feign death") {}
        virtual bool IsInstant() {return true;}
        virtual bool hasMultipliers() { return false; }
    };

	class CastDisengageAction : public CastMeleeSpellAction
    {
    public:
		CastDisengageAction(PlayerbotAI* ai) :CastMeleeSpellAction(ai, "disengage") {}
        virtual bool IsInstant() {return true;}
        virtual bool isPossible() {return true;}
        virtual bool hasMultipliers() { return false; }
    };

    class CastDeterrenceAction : public CastBuffSpellAction
    {
    public:
        CastDeterrenceAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "deterrence") {}

        virtual bool IsInstant() {return true;}
        virtual bool hasMultipliers() { return false; }
    };

	class CastRapidFireAction : public CastBuffSpellAction
	{
	public:
		CastRapidFireAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "rapid fire") {}
	};

	class CastReadinessAction : public CastBuffSpellAction
	{
	public:
		CastReadinessAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "readiness") {}
		virtual bool IsInstant() {return true;}
	};

	class CastBestialWrathAction : public CastBuffSpellAction
	{
	public:
		CastBestialWrathAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "bestial wrath") {}
		virtual bool IsInstant() {return true;}
	};

	class CastIntimidationAction : public CastBuffSpellAction
	{
	public:
		CastIntimidationAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "intimidation") {}
		virtual bool IsInstant() {return true;}
		virtual bool hasMultipliers() { return false; }
	};

	class CastKillCommandAction : public CastBuffSpellAction
	{
	public:
		CastKillCommandAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "kill command") {}
		virtual bool IsInstant() {return true;}
	};

	class CastKillShotAction : public CastBuffSpellAction
	{
	public:
		CastKillShotAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "kill shot") {}
		virtual bool IsInstant() {return true;}
	};

	class CastBlackArrow : public CastDebuffSpellAction
	{
	public:
		CastBlackArrow(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "black arrow") {}
		virtual bool IsInstant() {return true;}
	};

    class CastFreezingTrapCcAction : public CastDebuffSpellAction
    {
    public:
        CastFreezingTrapCcAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "freezing trap on cc") {}
        virtual Value<Unit*>* GetTargetValue();
        virtual bool IsInstant() {return true;}
		virtual bool IsUseful() {return true;}
    };

    class CastFreezingTrapAction : public CastSpellAction
    {
    public:
        CastFreezingTrapAction(PlayerbotAI* ai) : CastSpellAction(ai, "freezing trap") {}

        virtual NextAction** getAlternatives()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("immolation trap"), NULL), CastSpellAction::getAlternatives());
        }
        virtual bool IsInstant() {return true;}
		virtual bool isUseful() {return true;}
    };

    class CastFrostTrapAction : public CastDebuffSpellAction
    {
    public:
        CastFrostTrapAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "frost trap") {}
        virtual bool IsInstant() {return true;}
        virtual bool isUseful() {return true;}
    };

    class CastWingClipAction : public CastMeleeSpellAction
    {
    public:
        CastWingClipAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "wing clip") {}
        virtual bool isUseful()
        {
           // return CastMeleeSpellAction::isUseful() && !ai->HasAura("wing clip"), GetTarget());
           return CastMeleeSpellAction::isUseful() && !ai->HasAnyAuraOf(GetTarget(), "slow", "wing clip", "frost shock", "crippling poison", "hamstring", "chains of ice", NULL);
        }
        virtual bool IsInstant() {return true;}

        virtual NextAction** getPrerequisites()
        {
            return NULL;
        }
   //     NextAction** getContinuers()
   //     {
    //        return NextAction::merge( NextAction::array(0, new NextAction("flee"), NULL), CastMeleeSpellAction::getContinuers());
    //    }
    };

  class CastSnakeTrapAction : public CastSpellAction
    {
    public:
        CastSnakeTrapAction(PlayerbotAI* ai) : CastSpellAction(ai, "snake trap") {}
        virtual bool IsInstant() {return true;}
    };

    class CastImmolationTrapAction : public CastSpellAction
    {
    public:
        CastImmolationTrapAction(PlayerbotAI* ai) : CastSpellAction(ai, "immolation trap") {}
        virtual bool IsInstant() {return true;}

        virtual bool isUseful() { return (AI_VALUE(uint8, "melee attacker count") <= 2) && (AI_VALUE(uint8, "melee attacker count") > 0); }

    };

    class CastExplosiveTrapAction : public CastSpellAction
    {
    public:
        CastExplosiveTrapAction(PlayerbotAI* ai) : CastSpellAction(ai, "explosive trap") {}
        virtual bool IsInstant() {return true;}

        virtual bool isUseful() { return (AI_VALUE(uint8, "melee attacker count") > 2); }
    };

    class CastCounterAttackAction : public CastMeleeSpellAction
    {
    public:
        CastCounterAttackAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "counterattack") {}
        virtual bool isUseful()
        {
            return CastMeleeSpellAction::isUseful();
        }
        virtual bool IsInstant() {return true;}
    };


    class CastScatterShotAction : public CastMeleeSpellAction
    {
    public:
        CastScatterShotAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "scatter shot") {}
        virtual bool isUseful()
        {
            return CastMeleeSpellAction::isUseful();
        }
        virtual NextAction** getPrerequisites()
        {
            return NULL;
        }
    };

    class CastSerpentStingOnAttackerAction : public CastDebuffSpellOnAttackerAction
    {
    public:
        CastSerpentStingOnAttackerAction(PlayerbotAI* ai) : CastDebuffSpellOnAttackerAction(ai, "serpent sting") {}
        virtual bool IsInstant() {return true;}
    };

    class CastHuntersMarkActionOnAttackerAction : public CastDebuffSpellOnAttackerAction
    {
    public:
        CastHuntersMarkActionOnAttackerAction(PlayerbotAI* ai) : CastDebuffSpellOnAttackerAction(ai, "hunter's mark") {}
        virtual bool IsInstant() {return true;}
    };
}
