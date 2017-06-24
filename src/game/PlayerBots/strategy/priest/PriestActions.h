#pragma once

#include "../actions/GenericActions.h"

namespace ai
{
    class CastGreaterHealAction : public CastHealingSpellAction {
    public:
        CastGreaterHealAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "greater heal",30) {}
    };

    class CastGreaterHealOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastGreaterHealOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "greater heal",30) {}

        virtual string getName() { return "greater heal on party"; }
    };

    class CastGreaterHealOnMasterAction : public HealMasterAction
    {
    public:
        CastGreaterHealOnMasterAction(PlayerbotAI* ai) : HealMasterAction(ai, "greater heal",30) {}
    };

    class CastLesserHealAction : public CastHealingSpellAction {
    public:
        CastLesserHealAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "lesser heal",20) {}
    };

    class CastLesserHealOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastLesserHealOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "lesser heal",20) {}

        virtual string getName() { return "lesser heal on party"; }
    };

    class CastLesserHealOnMasterAction : public HealMasterAction
    {
    public:
        CastLesserHealOnMasterAction(PlayerbotAI* ai) : HealMasterAction(ai, "lesser heal",20) {}
    };

    class CastFlashHealAction : public CastHealingSpellAction {
    public:
        CastFlashHealAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "flash heal") {}
    };

    class CastFlashHealOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastFlashHealOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "flash heal") {}

        virtual string getName() { return "flash heal on party"; }
    };

    class CastFlashHealOnMasterAction : public HealMasterAction
    {
    public:
        CastFlashHealOnMasterAction(PlayerbotAI* ai) : HealMasterAction(ai, "flash heal") {}
    };

    class CastPenanceHealAction : public CastHealingSpellAction {
    public:
        CastPenanceHealAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "penance",20) {}
    };

    class CastPenanceOnAttackerAction : public CastSpellAction
	{
    public:
	    CastPenanceOnAttackerAction(PlayerbotAI* ai) : CastSpellAction(ai, "shadow word: pain") {}
	};

    class CastPenanceHealOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastPenanceHealOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "penance",20) {}

        virtual string getName() { return "penance on party"; }
    };

    class CastPenanceHealOnMasterAction : public HealMasterAction
    {
    public:
        CastPenanceHealOnMasterAction(PlayerbotAI* ai) : HealMasterAction(ai, "penance",20) {}
    };

    class CastHealAction : public CastHealingSpellAction {
    public:
        CastHealAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "heal",20) {}
    };

    class CastHealOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastHealOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "heal",20) {}

        virtual string getName() { return "heal on party"; }
    };

    class CastHealOnMasterAction : public HealMasterAction
    {
    public:
        CastHealOnMasterAction(PlayerbotAI* ai) : HealMasterAction(ai, "heal",20) {}
    };

    class CastRenewAction : public CastHealingSpellAction {
    public:
        CastRenewAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "renew",10) {}
    };

    class CastDesperatePrayerAction : public CastHealingSpellAction {
    public:
        CastDesperatePrayerAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "desperate prayer") {}

        virtual NextAction** getAlternatives();

        virtual bool IsInstant() {return true;}
    };

    class CastRenewOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRenewOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "renew",10) {}

        virtual string getName() { return "renew on party"; }

        virtual bool IsInstant() {return true;}
    };

    class CastRenewOnMasterAction : public HealMasterAction
    {
    public:
        CastRenewOnMasterAction(PlayerbotAI* ai) : HealMasterAction(ai, "renew",10) {}

        virtual bool IsInstant() {return true;}
    };

    class CastPrayerOfHealingAction : public CastAoeHealSpellAction {
    public:
        CastPrayerOfHealingAction(PlayerbotAI* ai) : CastAoeHealSpellAction(ai, "prayer of healing") {}
    };

    class CastDivineHymnAction : public CastAoeHealSpellAction {
    public:
        CastDivineHymnAction(PlayerbotAI* ai) : CastAoeHealSpellAction(ai, "divine hymn") {}
    };

    class CastHymnOfHopeAction : public CastBuffSpellAction {
    public:
        CastHymnOfHopeAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "hymn of hope") {}
    };

    class CastInnerFocusAction : public CastBuffSpellAction {
    public:
        CastInnerFocusAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "inner focus") {}
    };

    class CastFadeAction : public CastBuffSpellAction {
    public:
        CastFadeAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "fade") {}

        virtual bool isUseful()
        {
            return (AI_VALUE2(bool, "combat", "self target"));
            }

        virtual bool IsInstant() {return true;}
        virtual bool hasMultipliers() { return false; }
    };

    class CastPrayerOfMendingAction : public CastHealingSpellAction {
    public:
        CastPrayerOfMendingAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "prayer of mending",5) {}
		virtual bool IsInstant() { return true; }
    };

    class CastPrayerOfMendingOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastPrayerOfMendingOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "prayer of mending",5) {}

        virtual string getName() { return "prayer of mending on party"; }
		virtual bool IsInstant() { return true; }
    };

    class CastPrayerOfMendingOnMasterAction : public HealMasterAction
    {
    public:
        CastPrayerOfMendingOnMasterAction(PlayerbotAI* ai) : HealMasterAction(ai, "prayer of mending",5) {}
		virtual bool IsInstant() { return true; }

    };

    class CastBindingHealOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastBindingHealOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "binding heal") {}

        virtual string getName() { return "binding heal on party"; }
    };

    class CastBindingHealOnMasterAction : public HealMasterAction
    {
    public:
        CastBindingHealOnMasterAction(PlayerbotAI* ai) : HealMasterAction(ai, "binding heal") {}
    };

    class CastShadowformAction : public CastBuffSpellAction {
    public:
        CastShadowformAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "shadowform") {}
		virtual bool IsInstant() { return true; }
    };

    class CastShadowfiendAction : public CastBuffSpellAction {
    public:
        CastShadowfiendAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "shadowfiend") {}
		virtual bool IsInstant() { return true; }
    };


    class CastRemoveShadowformAction : public Action {
    public:
        CastRemoveShadowformAction(PlayerbotAI* ai) : Action(ai, "remove shadowform") {}
        virtual bool isUseful() { return ai->HasAura("shadowform", AI_VALUE(Unit*, "self target")); }
        virtual bool isPossible() { return true; }
		virtual bool IsInstant() { return true; }
        virtual bool Execute(Event event) {
            ai->RemoveAura("shadowform");
            return true;
        }
    };

	class CastVampiricEmbraceAction : public CastBuffSpellAction {
	public:
		CastVampiricEmbraceAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "vampiric embrace") {}
	};

	class CastPowerWordShieldAction : public CastBuffSpellAction {
	public:
		CastPowerWordShieldAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "power word: shield") {}

        virtual bool IsInstant() {return true;}
        virtual bool hasMultipliers() { return false; }
	};

    class CastPowerWordShieldOnPartyAction : public BuffOnPartyAction
    {
    public:
        CastPowerWordShieldOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "power word: shield") {}

        virtual string getName() { return "power word: shield on party"; }

        virtual bool IsInstant() {return true;}
        virtual bool hasMultipliers() { return false; }
    };

    class CastPowerWordShieldOnMasterAction : public BuffOnMasterAction {
	public:
		CastPowerWordShieldOnMasterAction(PlayerbotAI* ai) : BuffOnMasterAction(ai, "power word: shield") {}

		virtual bool IsInstant() {return true;}
		virtual bool hasMultipliers() { return false; }
	};

    class CastPainSuppressionAction : public CastBuffSpellAction {
	public:
		CastPainSuppressionAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "pain suppression") {}

		virtual bool IsInstant() {return true;}
		virtual bool hasMultipliers() { return false; }
	};

    class CastPainSuppressionOnPartyAction : public BuffOnPartyAction
    {
    public:
        CastPainSuppressionOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "pain suppression") {}

        virtual string getName() { return "pain suppression on party"; }

        virtual bool IsInstant() {return true;}
        virtual bool hasMultipliers() { return false; }
    };

    class CastPainSuppressionOnMasterAction : public BuffOnMasterAction
    {
    public:
        CastPainSuppressionOnMasterAction(PlayerbotAI* ai) : BuffOnMasterAction(ai, "pain suppression") {}

        virtual bool IsInstant() {return true;}
        virtual bool hasMultipliers() { return false; }
    };

    class CastGuardianSpiritAction : public CastBuffSpellAction {
	public:
		CastGuardianSpiritAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "guardian spirit") {}

		virtual bool IsInstant() {return true;}
		virtual bool hasMultipliers() { return false; }
	};

    class CastGuardianSpiritOnPartyAction : public BuffOnPartyAction
    {
    public:
        CastGuardianSpiritOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "guardian spirit") {}

        virtual string getName() { return "guardian spirit on party"; }

        virtual bool IsInstant() {return true;}
        virtual bool hasMultipliers() { return false; }
    };

    class CastGuardianSpiritOnMasterAction : public BuffOnMasterAction
    {
    public:
        CastGuardianSpiritOnMasterAction(PlayerbotAI* ai) : BuffOnMasterAction(ai, "guardian spirit") {}

        virtual string getName() { return "guardian spirit on party"; }

        virtual bool IsInstant() {return true;}
        virtual bool hasMultipliers() { return false; }
    };

    class CastPowerInfusionAction : public CastBuffSpellAction {
	public:
		CastPowerInfusionAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "power infusion") {}
		virtual bool IsInstant() { return true; }
	};

    class CastPowerInfusionOnPartyAction : public BuffOnPartyAction
    {
    public:
        CastPowerInfusionOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "power infusion") {}
		virtual bool IsInstant() { return true; }

        virtual string getName() { return "power infusion on party"; }
    };

	class CastPowerWordFortitudeAction : public CastBuffSpellAction {
	public:
		CastPowerWordFortitudeAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "power word: fortitude") {}
		virtual bool IsInstant() { return true; }
	};

	class CastPrayerOfShadowProtectionAction : public CastBuffSpellAction {
	public:
		CastPrayerOfShadowProtectionAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "prayer of shadow protection") {}
		virtual bool IsInstant() { return true; }
	};

	class CastFearWardAction : public CastBuffSpellAction {
	public:
		CastFearWardAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "fear ward") {}
	};

	class CastFearWardOnPartyAction : public BuffOnPartyAction {
	public:
		CastFearWardOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "fear ward on party") {}
	};

    class CastFearWardOnMasterAction : public BuffOnMasterAction {
	public:
		CastFearWardOnMasterAction(PlayerbotAI* ai) : BuffOnMasterAction(ai, "fear ward") {}
	};

	class CastDivineSpiritAction : public CastBuffSpellAction {
	public:
		CastDivineSpiritAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "divine spirit") {}
		virtual bool IsInstant() { return true; }
	};

	class CastInnerFireAction : public CastBuffSpellAction {
	public:
		CastInnerFireAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "inner fire") {}
		virtual bool IsInstant() { return true; }
	};

    BEGIN_SPELL_ACTION(CastHolyNovaAction, "holy nova")
	virtual bool IsInstant() { return true; }
	virtual bool hasMultipliers() { return false; }
    virtual bool isUseful() {
        return (!ai->HasAura("shadowform", AI_VALUE(Unit*, "self target")) && (AI_VALUE2(float, "distance", GetTargetName()) <= sPlayerbotAIConfig.meleeDistance) || (AI_VALUE(uint8, "melee attacker count") > 2));
    }
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastHolyNovaAoeAction, "holy nova")
	virtual bool IsInstant() { return true; }
	virtual bool hasMultipliers() { return false; }
    virtual bool isUseful() {
        return (!ai->HasAura("shadowform", AI_VALUE(Unit*, "self target")) && AI_VALUE2(uint8, "mana", "self target") >= 50 || (AI_VALUE(uint8, "melee attacker count") > 2));
    }
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastHolyFireAction, "holy fire")
        virtual bool isUseful() {
            return (!ai->HasAura("shadowform", AI_VALUE(Unit*, "self target")) && (AI_VALUE2(uint8, "mana", "self target") >= 60 && AI_VALUE2(uint8, "aoe heal", "almost full") == 0));
        }
    END_SPELL_ACTION()

    BEGIN_SPELL_ACTION(CastSmiteAction, "smite")
        virtual bool isUseful() {
			return (!ai->HasAura("shadowform", AI_VALUE(Unit*, "self target")) && ((AI_VALUE2(uint8, "mana", "self target") >= 60 && AI_VALUE2(uint8, "aoe heal", "almost full") == 0) || ai->HasAura("surge of light", AI_VALUE(Unit*, "self target"))));
        }
	virtual NextAction** getAlternatives()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("shoot"), NULL), CastSpellAction::getAlternatives());
        }
    END_SPELL_ACTION()

	class CastPowerWordFortitudeOnPartyAction : public BuffOnPartyAction {
	public:
		CastPowerWordFortitudeOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "power word: fortitude") {}
		virtual bool IsInstant() { return true; }
	};

	class CastPrayerOfShadowProtectionOnPartyAction : public BuffOnPartyAction {
	public:
		CastPrayerOfShadowProtectionOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "prayer of shadow protection") {}
	};

	class CastDivineSpiritOnPartyAction : public BuffOnPartyAction {
	public:
		CastDivineSpiritOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "divine spirit") {}
		virtual bool IsInstant() { return true; }
	};

	class CastPowerWordPainAction : public CastDebuffSpellAction
	{
    public:
	    CastPowerWordPainAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "shadow word: pain") {}

	    virtual bool IsInstant() {return true;}
	};

	class CastPowerWordPainOnAttackerAction : public CastDebuffSpellOnAttackerAction
	{
    public:
	    CastPowerWordPainOnAttackerAction(PlayerbotAI* ai) : CastDebuffSpellOnAttackerAction(ai, "shadow word: pain") {}

	    virtual bool IsInstant() {return true;}
	};

    class CastDevouringPlagueAction : public CastDebuffSpellAction
	{
    public:
	    CastDevouringPlagueAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "devouring plague") {}
	     virtual bool isUseful() {
			return !(AI_VALUE2(bool, "target normal", "current target"));
	     }

	     virtual bool IsInstant() {return true;}
	};

    BEGIN_DEBUFF_ACTION(CastVampiricTouchAction, "vampiric touch")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastMindBlastAction, "mind blast")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastMindFlayAction, "mind flay")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastPowerWordDeathAction, "power word: death")
	virtual bool IsInstant() { return true; }
    END_SPELL_ACTION()

	class CastCureDiseaseAction : public CastCureSpellAction {
	public:
		CastCureDiseaseAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "cure disease") {}
		virtual bool IsInstant() { return true; }
		virtual bool hasMultipliers() { return false; }
	};

    class CastCureDiseaseOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastCureDiseaseOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "cure disease", DISPEL_DISEASE) {}
		virtual bool IsInstant() { return true; }
        virtual string getName() { return "cure disease on party"; }
        virtual bool hasMultipliers() { return false; }
    };

	class CastAbolishDiseaseAction : public CastCureSpellAction {
	public:
		CastAbolishDiseaseAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "abolish disease") {}
		virtual bool IsInstant() { return true; }
		virtual bool hasMultipliers() { return false; }
		virtual NextAction** getAlternatives();
	};

    class CastAbolishDiseaseOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastAbolishDiseaseOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "abolish disease", DISPEL_DISEASE) {}
		virtual bool IsInstant() { return true; }
        virtual string getName() { return "abolish disease on party"; }
        virtual bool hasMultipliers() { return false; }
        virtual NextAction** getAlternatives();
    };

	class CastDispelMagicAction : public CastCureSpellAction {
	public:
		CastDispelMagicAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "dispel magic") {}
		virtual bool IsInstant() { return true; }
		virtual bool hasMultipliers() { return false; }
	};

    class CastDispelMagicOnTargetAction : public CastSpellAction {
    public:
        CastDispelMagicOnTargetAction(PlayerbotAI* ai) : CastSpellAction(ai, "dispel magic") {}
		virtual bool IsInstant() { return true; }
		virtual bool hasMultipliers() { return false; }
    };

    class CastDispelMagicOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastDispelMagicOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "dispel magic", DISPEL_MAGIC) {}
        virtual string getName() { return "dispel magic on party"; }
		virtual bool IsInstant() { return true; }
		virtual bool hasMultipliers() { return false; }
    };

	class CastResurrectionAction : public ResurrectPartyMemberAction
	{
	public:
		CastResurrectionAction(PlayerbotAI* ai) : ResurrectPartyMemberAction(ai, "resurrection") {}
	};

	class CastCircleOfHealingAction : public CastAoeHealSpellAction
	{
	public:
		CastCircleOfHealingAction(PlayerbotAI* ai) : CastAoeHealSpellAction(ai, "circle of healing") {}
	};

	class CastPsychicScreamAction : public CastSpellAction
	{
	public:
	    CastPsychicScreamAction(PlayerbotAI* ai) : CastSpellAction(ai, "psychic scream") {}

	    virtual bool IsInstant() {return true;}
	    virtual bool hasMultipliers() { return false; }
	};

	class CastPsychicHorrorAction : public CastSpellAction
	{
	public:
	    CastPsychicHorrorAction(PlayerbotAI* ai) : CastSpellAction(ai, "psychic horror") {}

	    virtual bool IsInstant() {return true;}
	    virtual bool hasMultipliers() { return false; }
	};

	class CastDispersionAction : public CastSpellAction
	{
	public:
	    CastDispersionAction(PlayerbotAI* ai) : CastSpellAction(ai, "dispersion") {}
	    virtual string GetTargetName() { return "self target"; }

	    virtual bool IsInstant() {return true;}
	    virtual bool hasMultipliers() { return false; }
	};

	class CastMindShearAction : public CastSpellAction
	{
	public:
		CastMindShearAction(PlayerbotAI* ai) : CastSpellAction(ai, "mind shear") {}
	};

    class CastSilenceAction : public CastSpellAction {
    public:
        CastSilenceAction(PlayerbotAI* ai) : CastSpellAction(ai, "silence") {}
		virtual bool IsInstant() { return true; }
    };

    class CastShackleUndeadAction : public CastSpellAction
	{
	public:
		CastShackleUndeadAction(PlayerbotAI* ai) : CastSpellAction(ai, "shackle undead") {}
	};

    class CastShackleUndeadCcAction : public CastDebuffSpellAction
    {
    public:
        CastShackleUndeadCcAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "shackle undead on cc") {}
        virtual Value<Unit*>* GetTargetValue();
        virtual bool Execute(Event event);
    };

}
