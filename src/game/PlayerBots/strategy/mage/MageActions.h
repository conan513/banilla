#pragma once

#include "../actions/GenericActions.h"

namespace ai
{
    class CastFireballAction : public CastSpellAction
    {
    public:
        CastFireballAction(PlayerbotAI* ai) : CastSpellAction(ai, "fireball") {}
    };

    class CastScorchAction : public CastSpellAction
    {
    public:
        CastScorchAction(PlayerbotAI* ai) : CastSpellAction(ai, "scorch") {}
        virtual bool isUseful();
    };

    class CastFireBlastAction : public CastSpellAction
    {
    public:
        CastFireBlastAction(PlayerbotAI* ai) : CastSpellAction(ai, "fire blast") {}

        virtual bool IsInstant() {return true;}
    };

    class CastArcaneBlastAction : public CastBuffSpellAction
    {
    public:
        CastArcaneBlastAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "arcane blast") {}
        virtual string GetTargetName() { return "current target"; }
    };

    class CastArcaneBarrageAction : public CastSpellAction
    {
    public:
        CastArcaneBarrageAction(PlayerbotAI* ai) : CastSpellAction(ai, "arcane barrage") {}
    };

    class CastArcaneMissilesAction : public CastSpellAction
    {
    public:
        CastArcaneMissilesAction(PlayerbotAI* ai) : CastSpellAction(ai, "arcane missiles") {}
    };

    class CastPyroblastAction : public CastSpellAction
    {
    public:
        CastPyroblastAction(PlayerbotAI* ai) : CastSpellAction(ai, "pyroblast") {}
    };

    class CastFlamestrikeAction : public CastSpellAction
    {
    public:
        CastFlamestrikeAction(PlayerbotAI* ai) : CastSpellAction(ai, "flamestrike") {}
    };

    class CastFrostNovaAction : public CastSpellAction
    {
    public:
        CastFrostNovaAction(PlayerbotAI* ai) : CastSpellAction(ai, "frost nova") {}
        virtual bool isUseful() { return  (AI_VALUE2(float, "distance", "current target") <= sPlayerbotAIConfig.tooCloseDistance || AI_VALUE(uint8, "melee attacker count") > 0); }

        virtual bool IsInstant() {return true;}
        virtual bool hasMultipliers() { return false; }
    };

    class CastArcaneExplosionAction : public CastSpellAction
    {
    public:
        CastArcaneExplosionAction(PlayerbotAI* ai) : CastSpellAction(ai, "arcane explosion") {}
        virtual bool isUseful() { return AI_VALUE(uint8, "melee attacker count") > 1; }
        virtual bool IsInstant() {return true;}
    };

	class CastFrostboltAction : public CastSpellAction
	{
	public:
		CastFrostboltAction(PlayerbotAI* ai) : CastSpellAction(ai, "frostbolt") {}
		virtual bool hasMultipliers() { return false; }
	};

	class CastIceLanceAction : public CastSpellAction
	{
	public:
		CastIceLanceAction(PlayerbotAI* ai) : CastSpellAction(ai, "ice lance") {}

		virtual bool isUseful() {return AI_VALUE2(bool, "frozen", "current target");}
		virtual bool IsInstant() {return true;}
		virtual bool hasMultipliers() { return false; }
	};

	class CastFrostfireBoltAction : public CastSpellAction
	{
	public:
		CastFrostfireBoltAction(PlayerbotAI* ai) : CastSpellAction(ai, "frostfire bolt") {}
	};

    class CastDeepFreezeAction : public CastSpellAction
	{
	public:
		CastDeepFreezeAction(PlayerbotAI* ai) : CastSpellAction(ai, "deep freeze") {}
	};

	class CastBlizzardAction : public CastSpellAction
	{
	public:
		CastBlizzardAction(PlayerbotAI* ai) : CastSpellAction(ai, "blizzard") {}
	};

	class CastArcaneIntellectAction : public CastBuffSpellAction
    {
	public:
		CastArcaneIntellectAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "arcane intellect") {}
		virtual bool IsInstant() { return true; }
	};

	class CastArcaneIntellectOnPartyAction : public BuffOnPartyAction
    {
	public:
		CastArcaneIntellectOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "arcane intellect") {}

		virtual bool isUseful() {return AI_VALUE2(bool, "has mana", GetTargetName());}
	};

	class CastFocusMagicOnPartyAction : public BuffOnPartyAction
    {
	public:
		CastFocusMagicOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "focus magic") {}
		virtual bool isUseful();
	};

	class CastRemoveCurseAction : public CastCureSpellAction
    {
	public:
		CastRemoveCurseAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "remove curse") {}
		virtual bool IsInstant() {return true;}
		virtual bool hasMultipliers() { return false; }
	};

	class CastRemoveLesserCurseAction : public CastCureSpellAction
	{
		public:
			CastRemoveLesserCurseAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "remove lesser curse") {}
			};

    class CastArcanePowerAction : public CastBuffSpellAction
	{
	public:
	    CastArcanePowerAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "arcane power") {}
	};

	class CastPresenceMindAction : public CastBuffSpellAction
	{
	public:
	    CastPresenceMindAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "presence of mind") {}
	};

    class CastSlowAction : public CastDebuffSpellAction
	{
	public:
	    CastSlowAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "slow") {}
	    virtual bool IsInstant() {return true;}
	};

	class CastIcyVeinsAction : public CastBuffSpellAction
    {
	public:
		CastIcyVeinsAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "icy veins") {}
	};

	class CastCombustionAction : public CastBuffSpellAction
    {
	public:
		CastCombustionAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "combustion") {}
	};

	class CastIceBlockAction : public CastBuffSpellAction
    {
	public:
		CastIceBlockAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "ice block") {}
		virtual bool IsInstant() {return true;}
		virtual bool hasMultipliers() { return false; }
	};

	class CastColdSnapAction : public CastBuffSpellAction
    {
	public:
		CastColdSnapAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "cold snap") {}
		virtual bool IsInstant() {return true;}
		virtual bool hasMultipliers() { return false; }
	};

	class CastIceBarrierAction : public CastBuffSpellAction
    {
	public:
		CastIceBarrierAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "ice barrier") {}
        virtual bool IsInstant() {return true;}
        virtual bool hasMultipliers() { return false; }
	};

    BEGIN_SPELL_ACTION(CastCounterspellAction, "counterspell")
    END_SPELL_ACTION()

    class CastRemoveCurseOnPartyAction : public CurePartyMemberAction
    {
    public:
        CastRemoveCurseOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "remove curse", DISPEL_CURSE) {}
        virtual bool hasMultipliers() { return false; }
    };

	class CastRemoveLesserCurseOnPartyAction : public CurePartyMemberAction
	{
		public:
			CastRemoveLesserCurseOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "remove lesser curse", DISPEL_CURSE) {}
	};

	class CastConjureFoodAction : public CastBuffSpellAction
    {
	public:
		CastConjureFoodAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "conjure food") {}
	};

	class CastConjureWaterAction : public CastBuffSpellAction
    {
	public:
		CastConjureWaterAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "conjure water") {}
	};

    class CastSummonWaterElementalAction : public CastBuffSpellAction
    {
	public:
		CastSummonWaterElementalAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "summon water elemental") {}
	};

    class CastMoltenArmorAction : public CastBuffSpellAction
    {
    public:
        CastMoltenArmorAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "molten armor") {}
        virtual string GetTargetName() { return "self target"; }
		virtual bool IsInstant() { return true; }
        virtual NextAction** getAlternatives()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("mage armor"), NULL), CastBuffSpellAction::getAlternatives());
        }
    };

    class CastMageArmorAction : public CastBuffSpellAction
    {
    public:
        CastMageArmorAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "mage armor") {}
        virtual string GetTargetName() { return "self target"; }
		virtual bool IsInstant() { return true; }
        virtual NextAction** getAlternatives()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("ice armor"), NULL), CastBuffSpellAction::getAlternatives());
        }
    };

    class CastIceArmorAction : public CastBuffSpellAction
    {
    public:
        CastIceArmorAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "ice armor") {}
        virtual string GetTargetName() { return "self target"; }
		virtual bool IsInstant() { return true; }
        virtual NextAction** getAlternatives()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("frost armor"), NULL), CastBuffSpellAction::getAlternatives());
        }
    };

    class CastFrostArmorAction : public CastBuffSpellAction
    {
    public:
        CastFrostArmorAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "frost armor") {}
		virtual bool IsInstant() { return true; }
        virtual string GetTargetName() { return "self target"; }
    };

    class CastPolymorphAction : public CastDebuffSpellAction
    {
    public:
        CastPolymorphAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "polymorph") {}
        virtual bool isUseful();
    };

    class CastPolymorphCcAction : public CastBuffSpellAction
    {
    public:
        CastPolymorphCcAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "polymorph on cc") {}
        virtual Value<Unit*>* GetTargetValue();
        virtual bool Execute(Event event);
        virtual bool isUseful();
    };

	class CastSpellstealAction : public CastDebuffSpellAction
    {
    public:
        CastSpellstealAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "spellsteal") {}
		virtual bool IsInstant() { return true; }
    };

	class CastLivingBombAction : public CastDebuffSpellAction
	{
	public:
	    CastLivingBombAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "living bomb") {}
		virtual bool IsInstant() { return true; }
	};

	class CastConeOfColdAction : public CastSpellAction
	{
	public:
	    CastConeOfColdAction(PlayerbotAI* ai) : CastSpellAction(ai, "cone of cold") {}
	    virtual bool isUseful() { return AI_VALUE2(float, "distance", "current target") <= sPlayerbotAIConfig.tooCloseDistance; }

	    virtual bool IsInstant() {return true;}
	};

	class CastDragonsBreathAction : public CastSpellAction
	{
	public:
	    CastDragonsBreathAction(PlayerbotAI* ai) : CastSpellAction(ai, "dragon's breath") {}
	    virtual bool isUseful() { return AI_VALUE2(float, "distance", "current target") <= sPlayerbotAIConfig.tooCloseDistance; }
	    virtual bool IsInstant() {return true;}
	};

	class CastBlastWaveAction : public CastSpellAction
	{
	public:
	    CastBlastWaveAction(PlayerbotAI* ai) : CastSpellAction(ai, "blast wave") {}
	    virtual bool isUseful() { return (AI_VALUE2(float, "distance", "current target") <= sPlayerbotAIConfig.tooCloseDistance || AI_VALUE(uint8, "melee attacker count") > 1); }
	    virtual bool IsInstant() {return true;}
	};

	class CastInvisibilityAction : public CastBuffSpellAction
	{
	public:
	    CastInvisibilityAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "invisibility") {}
	    virtual bool IsInstant() {return true;}
	};

	class CastManaShieldAction : public CastBuffSpellAction
	{
	public:
	    CastManaShieldAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "mana shield") {}
	    virtual bool IsInstant() {return true;}
	};

    class CastFrostWardAction : public CastBuffSpellAction
	{
	public:
	    CastFrostWardAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "frost ward") {}
	    virtual bool IsInstant() {return true;}
	};

	class CastFireWardAction : public CastBuffSpellAction
	{
	public:
	    CastFireWardAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "fire ward") {}
	    virtual bool IsInstant() {return true;}
	};

	class CastBlinkAction : public CastBuffSpellAction
	{
	public:
	    CastBlinkAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "blink") {}

	    virtual bool isUseful()
        {
            return (AI_VALUE2(bool, "combat", "self target"));
            }

        virtual bool IsInstant() {return true;}
        virtual bool hasMultipliers() { return false; }
	};

	class CastEvocationAction : public CastSpellAction
	{
	public:
	    CastEvocationAction(PlayerbotAI* ai) : CastSpellAction(ai, "evocation") {}
	    virtual string GetTargetName() { return "self target"; }
	};

    class CastCounterspellOnEnemyHealerAction : public CastSpellOnEnemyHealerAction
    {
    public:
	    CastCounterspellOnEnemyHealerAction(PlayerbotAI* ai) : CastSpellOnEnemyHealerAction(ai, "counterspell") {}
	    virtual bool IsInstant() {return true;}
    };
}
