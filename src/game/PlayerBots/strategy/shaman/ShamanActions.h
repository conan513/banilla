#pragma once

#include "../actions/GenericActions.h"

namespace ai
{
    class CastLesserHealingWaveAction : public CastHealingSpellAction {
    public:
        CastLesserHealingWaveAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "lesser healing wave") {}
    };

    class CastLesserHealingWaveOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastLesserHealingWaveOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "lesser healing wave") {}
    };

    class CastLesserHealingWaveOnMasterAction : public HealMasterAction
    {
    public:
        CastLesserHealingWaveOnMasterAction(PlayerbotAI* ai) : HealMasterAction(ai, "lesser healing wave") {}
    };

    class CastHealingWaveAction : public CastHealingSpellAction {
    public:
        CastHealingWaveAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "healing wave",25) {}
    };

    class CastHealingWaveOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastHealingWaveOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "healing wave",25) {}
    };

    class CastHealingWaveOnMasterAction : public HealMasterAction
    {
    public:
        CastHealingWaveOnMasterAction(PlayerbotAI* ai) : HealMasterAction(ai, "healing wave",25) {}
    };

    class CastChainHealAction : public CastAoeHealSpellAction {
    public:
        CastChainHealAction(PlayerbotAI* ai) : CastAoeHealSpellAction(ai, "chain heal") {}
    };

    class CastChainHealOnPartyAction : public HealPartyMemberAction {
    public:
        CastChainHealOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "chain heal") {}
        virtual bool isUseful() {return HealPartyMemberAction::isUseful() && AI_VALUE2(uint8, "aoe heal", "light") > 0;}
    };

    class CastChainHealOnMasterAction : public HealMasterAction {
    public:
        CastChainHealOnMasterAction(PlayerbotAI* ai) : HealMasterAction(ai, "chain heal") {}
        virtual bool isUseful() {return HealMasterAction::isUseful() && AI_VALUE2(uint8, "aoe heal", "light") > 0;}
    };

    class CastRiptideAction : public CastHealingSpellAction {
    public:
        CastRiptideAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "riptide",10) {}
        virtual bool IsInstant() {return true;}
    };

    class CastRiptideOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastRiptideOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "riptide",10) {}
        virtual bool IsInstant() {return true;}
    };

    class CastRiptideOnMasterAction : public HealMasterAction
    {
    public:
        CastRiptideOnMasterAction(PlayerbotAI* ai) : HealMasterAction(ai, "riptide",10) {}
        virtual bool IsInstant() {return true;}
    };

    class CastEarthShieldAction : public CastBuffSpellAction {
    public:
        CastEarthShieldAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "earth shield") {}
        virtual bool IsInstant() {return true;}
    };

    class CastEarthShieldOnPartyAction : public BuffOnPartyAction
    {
    public:
        CastEarthShieldOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "earth shield") {}
        virtual bool isUseful();
        virtual bool IsInstant() {return true;}
    };

    class CastEarthShieldOnMasterAction : public BuffOnMasterAction
    {
    public:
        CastEarthShieldOnMasterAction(PlayerbotAI* ai) : BuffOnMasterAction(ai, "earth shield") {}
        virtual bool IsInstant() {return true;}
    };

    class CastWaterShieldAction : public CastBuffSpellAction {
    public:
        CastWaterShieldAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "water shield") {}
        virtual bool IsInstant() {return true;}
        virtual bool hasMultipliers() { return false; }
    };

	class CastLightningShieldAction : public CastBuffSpellAction {
	public:
		CastLightningShieldAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "lightning shield") {}
		virtual bool IsInstant() {return true;}
	};

    class CastEarthlivingWeaponAction : public CastEnchantItemAction {
    public:
        CastEarthlivingWeaponAction(PlayerbotAI* ai) : CastEnchantItemAction(ai, "earthliving weapon") {}

        virtual NextAction** getAlternatives()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("flametongue weapon"), NULL), CastEnchantItemAction::getAlternatives());
        }
    };

    class CastRockbiterWeaponAction : public CastEnchantItemAction {
    public:
        CastRockbiterWeaponAction(PlayerbotAI* ai) : CastEnchantItemAction(ai, "rockbiter weapon") {}
    };

    class CastFlametongueWeaponAction : public CastEnchantItemAction {
    public:
        CastFlametongueWeaponAction(PlayerbotAI* ai) : CastEnchantItemAction(ai, "flametongue weapon") {}
    };

    class CastFrostbrandWeaponAction : public CastEnchantItemAction {
    public:
        CastFrostbrandWeaponAction(PlayerbotAI* ai) : CastEnchantItemAction(ai, "frostbrand weapon") {}
    };

    class CastWindfuryWeaponAction : public CastEnchantItemAction {
    public:
        CastWindfuryWeaponAction(PlayerbotAI* ai) : CastEnchantItemAction(ai, "windfury weapon") {}

        virtual NextAction** getAlternatives()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("flametongue weapon"), NULL), CastEnchantItemAction::getAlternatives());
        }
    };

    class CastTotemAction : public CastBuffSpellAction
    {
    public:
        CastTotemAction(PlayerbotAI* ai, string spell) : CastBuffSpellAction(ai, spell) {}
        virtual bool isUseful() { return CastBuffSpellAction::isUseful() && !AI_VALUE2(bool, "has totem", name); }
        virtual bool IsInstant() {return true;}
        virtual bool hasMultipliers() { return false; }
    };

    class CastOwnTotemAction : public CastBuffSpellAction
    {
    public:
        CastOwnTotemAction(PlayerbotAI* ai, string spell) : CastBuffSpellAction(ai, spell) {}
        virtual bool isUseful() { return CastBuffSpellAction::isUseful() && !AI_VALUE2(bool, "has own totem", name); }
    };

    class CastStoneskinTotemAction : public CastTotemAction
    {
    public:
        CastStoneskinTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "stoneskin totem") {}
        virtual bool isUseful() { return CastTotemAction::isUseful() && !ai->HasAnyAuraOf(GetTarget(), "devotion aura", NULL);}
    };

    class CastEarthbindTotemAction : public CastTotemAction
    {
    public:
        CastEarthbindTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "earthbind totem") {}
    };

    class CastTremorTotemAction : public CastTotemAction
    {
    public:
        CastTremorTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "tremor totem") {}
    };

    class CastStoneclawTotemAction : public CastOwnTotemAction
    {
    public:
        CastStoneclawTotemAction(PlayerbotAI* ai) : CastOwnTotemAction(ai, "stoneclaw totem") {}
    };

    class CastStrengthOfEarthTotemAction : public CastTotemAction
    {
    public:
        CastStrengthOfEarthTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "strength of earth totem") {}
    };

    class CastManaSpringTotemAction : public CastTotemAction
    {
    public:
        CastManaSpringTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "mana spring totem") {}
    };

	class CastManaTideTotemAction : public CastTotemAction
	{
	public:
		CastManaTideTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "mana tide totem") {}
		virtual string GetTargetName() { return "self target"; }
	};

	class CastHealingStreamTotemAction : public CastOwnTotemAction
	{
	public:
		CastHealingStreamTotemAction(PlayerbotAI* ai) : CastOwnTotemAction(ai, "healing stream totem") {}
	};

    class CastCleansingTotemAction : public CastTotemAction
    {
    public:
        CastCleansingTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "cleansing totem") {}
    };

    class CastCallOfTheElementsTotemAction : public CastBuffSpellAction
    {
    public:
        CastCallOfTheElementsTotemAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "call of the elements") {}
        virtual bool IsInstant() {return true;}

        virtual bool isUseful() {
           return true;
            }
    };

    class CastCallOfTheAncestorsTotemAction : public CastBuffSpellAction
    {
    public:
        CastCallOfTheAncestorsTotemAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "call of the ancestors") {}
        virtual bool IsInstant() {return true;}

        virtual bool isUseful() {
           return CastBuffSpellAction::isUseful() && !AI_VALUE2(bool, "has own totem", "totem");
            }
    };

    class CastCallOfTheSpiritsTotemAction : public CastBuffSpellAction
    {
    public:
        CastCallOfTheSpiritsTotemAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "call of the spirits") {}
        virtual bool IsInstant() {return true;}

        virtual bool isUseful() {
           return CastBuffSpellAction::isUseful() && !AI_VALUE2(bool, "has own totem", "totem");
            }
    };

    class CastFlametongueTotemAction : public CastTotemAction
    {
    public:
        CastFlametongueTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "flametongue totem") {}
    };

    class CastWindfuryTotemAction : public CastTotemAction
    {
    public:
        CastWindfuryTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "windfury totem") {}
    };

    class CastTotemOfWrathAction : public CastTotemAction
    {
    public:
        CastTotemOfWrathAction(PlayerbotAI* ai) : CastTotemAction(ai, "totem of wrath") {}
    };

    class CastWrathOfAirTotemAction : public CastTotemAction
    {
    public:
        CastWrathOfAirTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "wrath of air totem") {}
    };

    class CastSearingTotemAction : public CastTotemAction
    {
    public:
        CastSearingTotemAction(PlayerbotAI* ai) : CastTotemAction(ai, "searing totem") {}
        virtual string GetTargetName() { return "self target"; }
        virtual bool isUseful() { return CastSpellAction::isUseful() && !AI_VALUE2(bool, "has own totem", name) && (AI_VALUE(uint8, "aoe attacker count") <= 2 || bot->getLevel() < 32); }
    };

    class CastMagmaTotemAction : public CastSpellAction
    {
    public:
        CastMagmaTotemAction(PlayerbotAI* ai) : CastSpellAction(ai, "magma totem") {}
        virtual string GetTargetName() { return "self target"; }
        virtual bool isUseful() { return CastSpellAction::isUseful() && AI_VALUE(uint8, "melee attacker count") > 2 && !AI_VALUE2(bool, "has own totem", name) && !AI_VALUE2(bool, "has own totem", "fire elemental totem"); }
        virtual bool IsInstant() {return true;}
    };

    class CastFireNovaAction : public CastSpellAction {
    public:
        CastFireNovaAction(PlayerbotAI* ai) : CastSpellAction(ai, "fire nova") {}

	virtual bool isUseful() { return CastSpellAction::isUseful() && AI_VALUE(uint8, "melee attacker count") > 2 && (AI_VALUE2(bool, "has own totem", "magma totem") || AI_VALUE2(bool, "has own totem", "searing totem")); }
    };

    class CastWindShearAction : public CastSpellAction {
    public:
        CastWindShearAction(PlayerbotAI* ai) : CastSpellAction(ai, "wind shear") {}
    };

	class CastAncestralSpiritAction : public ResurrectPartyMemberAction
	{
	public:
		CastAncestralSpiritAction(PlayerbotAI* ai) : ResurrectPartyMemberAction(ai, "ancestral spirit") {}
	};

	class CastPurgeAction : public CastSpellAction
	{
	public:
		CastPurgeAction(PlayerbotAI* ai) : CastSpellAction(ai, "purge") {}
		virtual bool IsInstant() {return true;}
	};

	class CastStormstrikeAction : public CastMeleeSpellAction {
	public:
		CastStormstrikeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "stormstrike") {}
		virtual bool IsInstant() {return true;}
	};

	class CastLavaLashAction : public CastMeleeSpellAction {
	public:
		CastLavaLashAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "lava lash") {}
		virtual bool IsInstant() {return true;}
	};

    class CastWaterBreathingAction : public CastBuffSpellAction {
    public:
        CastWaterBreathingAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "water breathing") {}
    };

    class CastWaterWalkingAction : public CastBuffSpellAction {
    public:
        CastWaterWalkingAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "water walking") {}
    };

    class CastWaterBreathingOnPartyAction : public BuffOnPartyAction {
    public:
        CastWaterBreathingOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "water breathing") {}
    };

    class CastWaterWalkingOnPartyAction : public BuffOnPartyAction {
    public:
        CastWaterWalkingOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "water walking") {}
    };

	class CastCurePoisonAction : public CastCureSpellAction
	{
	public:
		CastCurePoisonAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "cure poison") {}
		virtual bool IsInstant() { return true; }
	};

	class CastCurePoisonOnPartyAction : public CurePartyMemberAction
	{
	public:
		CastCurePoisonOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "cure poison", DISPEL_POISON) {}
		virtual string getName() { return "cure poison on party"; }
		virtual bool IsInstant() { return true; }
	};

	class CastCureDiseaseAction : public CastCureSpellAction {
	public:
		CastCureDiseaseAction(PlayerbotAI* ai) : CastCureSpellAction(ai, "cure disease") {}
		virtual bool IsInstant() { return true; }
	};

	class CastCureDiseaseOnPartyAction : public CurePartyMemberAction
	{
	public:
		CastCureDiseaseOnPartyAction(PlayerbotAI* ai) : CurePartyMemberAction(ai, "cure disease", DISPEL_DISEASE) {}
		virtual string getName() { return "cure disease on party"; }
		virtual bool IsInstant() { return true; }
	};

    class CastFlameShockAction : public CastDebuffSpellAction
    {
    public:
        CastFlameShockAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "flame shock") {}
        virtual bool IsInstant() {return true;}
    };

    class CastEarthShockAction : public CastSpellAction
    {
    public:
        CastEarthShockAction(PlayerbotAI* ai) : CastSpellAction(ai, "earth shock") {}
        virtual bool IsInstant() {return true;}
    };

    class CastFrostShockAction : public CastDebuffSpellAction
    {
    public:
        CastFrostShockAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "frost shock") {}

         virtual bool isUseful()
        {
           return CastDebuffSpellAction::isUseful() && !ai->HasAnyAuraOf(GetTarget(), "slow", "wing clip", "frost shock", "crippling poison", "hamstring", NULL);
        }

        virtual bool IsInstant() {return true;}
    };

    class CastChainLightningAction : public CastSpellAction
    {
    public:
        CastChainLightningAction(PlayerbotAI* ai) : CastSpellAction(ai, "chain lightning") {}
    };

    class CastLightningBoltAction : public CastSpellAction
    {
    public:
        CastLightningBoltAction(PlayerbotAI* ai) : CastSpellAction(ai, "lightning bolt") {}

        virtual NextAction** getAlternatives()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("reposition"), NULL), CastSpellAction::getAlternatives());
        }
    };

   class CastLightningBoltHealAction : public CastSpellAction
    {
    public:
        CastLightningBoltHealAction(PlayerbotAI* ai) : CastSpellAction(ai, "lightning bolt") {}
        virtual bool isUseful() {
            return (CastSpellAction::isUseful() && (AI_VALUE2(uint8, "mana", "self target") >= 60 && AI_VALUE2(uint8, "aoe heal", "almost full") == 0));
        }
    };

    class CastLavaBurstAction : public CastSpellAction
    {
    public:
        CastLavaBurstAction(PlayerbotAI* ai) : CastSpellAction(ai, "lava burst") {}

        virtual bool isUseful() {
           return CastSpellAction::isUseful() && ai->HasAura("flame shock",GetTarget(),BOT_AURA_DAMAGE);
            }
    };

    class CastThunderstormAction : public CastMeleeSpellAction
    {
    public:
        CastThunderstormAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "thunderstorm") {}
        virtual bool IsInstant() {return true;}
    };

    class CastHeroismAction : public CastBuffSpellAction
    {
    public:
        CastHeroismAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "heroism") {}
        NextAction** getAlternatives()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("bloodlust"), NULL), CastBuffSpellAction::getPrerequisites());
        }
    };

    class CastBloodlustAction : public CastBuffSpellAction
    {
    public:
        CastBloodlustAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "bloodlust") {}
        NextAction** getAlternatives()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("heroism"), NULL), CastBuffSpellAction::getPrerequisites());
        }
    };

    class CastTotemicRecallAction : public CastSpellAction
    {
    public:
        CastTotemicRecallAction(PlayerbotAI* ai) : CastSpellAction(ai, "totemic recall") {}

        virtual bool isUseful() {
           return CastSpellAction::isUseful() && AI_VALUE2(bool, "has any own totem", "totem");
            }
    };

    class CastWindShearOnEnemyHealerAction : public CastSpellOnEnemyHealerAction
    {
    public:
        CastWindShearOnEnemyHealerAction(PlayerbotAI* ai) : CastSpellOnEnemyHealerAction(ai, "wind shear") {}
        virtual bool IsInstant() {return true;}
        virtual bool hasMultipliers() { return false; }
    };

    class CastSummonEarthElementalAction : public CastBuffSpellAction
    {
    public:
        CastSummonEarthElementalAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "earth elemental totem") {}
        virtual bool IsInstant() {return true;}
        virtual bool hasMultipliers() { return false; }
    };

    class CastSummonFireElementalAction : public CastBuffSpellAction
    {
    public:
        CastSummonFireElementalAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "fire elemental totem") {}
        virtual bool IsInstant() {return true;}
    };

    class CastElementalMasteryAction : public CastBuffSpellAction
    {
    public:
        CastElementalMasteryAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "elemental mastery") {}
    };

    class CastFeralSpiritAction : public CastBuffSpellAction
    {
    public:
        CastFeralSpiritAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "feral spirit") {}
        virtual bool IsInstant() {return true;}
    };

    class CastTidalForceAction : public CastBuffSpellAction
    {
    public:
        CastTidalForceAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "tidal force") {}
    };

    class CastShamanisticRageAction : public CastBuffSpellAction
    {
    public:
        CastShamanisticRageAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "shamanistic rage") {}
        virtual bool IsInstant() {return true;}
    };

    class CastNaturesSwiftnessAction : public CastBuffSpellAction
    {
    public:
        CastNaturesSwiftnessAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "nature's swiftness") {}
        virtual bool IsInstant() {return true;}
    };

    class CastHexAction : public CastDebuffSpellAction
    {
    public:
        CastHexAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "hex") {}
    };

    class CastHexCcAction : public CastSpellAction
    {
    public:
        CastHexCcAction(PlayerbotAI* ai) : CastSpellAction(ai, "hex on cc") {}
        virtual Value<Unit*>* GetTargetValue()
        {
            return context->GetValue<Unit*>("cc target", "hex");
        }
        virtual bool Execute(Event event)
        {
            return ai->CastSpell("hex", GetTarget());
        }
    };

}
