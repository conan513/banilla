#pragma once
#include "../triggers/GenericTriggers.h"

namespace ai
{
    class ShamanWeaponTrigger : public BuffTrigger {
    public:
        ShamanWeaponTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "flametongue weapon") {}
        virtual bool IsActive();
    private:
        static list<string> spells;
    };

    class TotemTrigger : public Trigger {
    public:
        TotemTrigger(PlayerbotAI* ai, string spell, int attackerCount = 0) : Trigger(ai, spell), attackerCount(attackerCount) {}

        virtual bool IsActive()
		{
            return AI_VALUE(uint8, "attacker count") >= attackerCount && !AI_VALUE2(bool, "has totem", name);
        }

    protected:
        int attackerCount;
    };

    class RecallTotemTrigger : public Trigger {
    public:
        RecallTotemTrigger(PlayerbotAI* ai) : Trigger(ai, "recall all totems") {}

        virtual bool IsActive()
		{
            return !AI_VALUE2(bool, "combat", "self target") && AI_VALUE(uint8, "possible targets") == 0 && !AI_VALUE2(bool, "mounted", "self target") && AI_VALUE2(bool, "has any own totem", "totem");
        }
    };

    class WindfuryTotemTrigger : public TotemTrigger {
    public:
        WindfuryTotemTrigger(PlayerbotAI* ai) : TotemTrigger(ai, "windfury totem") {}

        virtual bool IsActive()
		{
            return TotemTrigger::IsActive() && !AI_VALUE2(bool, "has own totem", "grounding totem");
        }
    };

    class ManaSpringTotemTrigger : public TotemTrigger {
    public:
        ManaSpringTotemTrigger(PlayerbotAI* ai) : TotemTrigger(ai, "mana spring totem") {}
        virtual bool IsActive()
        {
            return AI_VALUE(uint8, "attacker count") >= attackerCount &&
                    !AI_VALUE2(bool, "has totem", "mana tide totem") &&
                    !AI_VALUE2(bool, "has totem", name);
        }
    };

    class FlametongueTotemTrigger : public TotemTrigger {
    public:
        FlametongueTotemTrigger(PlayerbotAI* ai) : TotemTrigger(ai, "flametongue totem") {}

        virtual bool IsActive()
		{
            return TotemTrigger::IsActive() && !AI_VALUE2(bool, "has own totem", "fire elemental totem");
        }
    };

    class StrengthOfEarthTotemTrigger : public TotemTrigger {
    public:
        StrengthOfEarthTotemTrigger(PlayerbotAI* ai) : TotemTrigger(ai, "strength of earth totem") {}

        virtual bool IsActive()
		{
            return TotemTrigger::IsActive() && !AI_VALUE2(bool, "has own totem", "tremor totem") && !AI_VALUE2(bool, "has own totem", "stoneclaw totem") &&
                    !AI_VALUE2(bool, "has own totem", "earth elemental totem");
        }
    };

    class MagmaTotemTrigger : public TotemTrigger {
    public:
        MagmaTotemTrigger(PlayerbotAI* ai) : TotemTrigger(ai, "magma totem", 4) {}

        virtual bool IsActive()
		{
            return TotemTrigger::IsActive() && AI_VALUE(uint8, "aoe attacker count") > 2 && !AI_VALUE2(bool, "has own totem", "fire elemental totem");
        }
    };

    class SearingTotemTrigger : public TotemTrigger {
    public:
        SearingTotemTrigger(PlayerbotAI* ai) : TotemTrigger(ai, "searing totem", 1) {}

        virtual bool IsActive()
		{
            return TotemTrigger::IsActive() && AI_VALUE(uint8, "aoe attacker count") <= 2 && !AI_VALUE2(bool, "has own totem", "fire elemental totem");
        }
    };

    class WindShearInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        WindShearInterruptSpellTrigger(PlayerbotAI* ai) : InterruptSpellTrigger(ai, "wind shear") {}
    };

    class WaterShieldTrigger : public BuffTrigger
    {
    public:
        WaterShieldTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "water shield") {}
    };

    class LightningShieldTrigger : public BuffTrigger
    {
    public:
        LightningShieldTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "lightning shield") {}
    };

    class PurgeTrigger : public TargetAuraDispelTrigger
    {
    public:
        PurgeTrigger(PlayerbotAI* ai) : TargetAuraDispelTrigger(ai, "purge", DISPEL_MAGIC) {}
    };

    class WaterWalkingTrigger : public BuffTrigger {
    public:
        WaterWalkingTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "water walking") {}

        virtual bool IsActive()
        {
            return BuffTrigger::IsActive() && AI_VALUE2(bool, "swimming", "self target");
        }
    };

    class WaterBreathingTrigger : public BuffTrigger {
    public:
        WaterBreathingTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "water breathing") {}

        virtual bool IsActive()
        {
            return BuffTrigger::IsActive() && AI_VALUE2(bool, "swimming", "self target");
        }
    };

    class WaterWalkingOnPartyTrigger : public BuffOnPartyTrigger {
    public:
        WaterWalkingOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "water walking") {}

        virtual bool IsActive()
        {
            return BuffOnPartyTrigger::IsActive() && AI_VALUE2(bool, "swimming", "current target");
        }
    };

    class WaterBreathingOnPartyTrigger : public BuffOnPartyTrigger {
    public:
        WaterBreathingOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "water breathing") {}

        virtual bool IsActive()
        {
            return BuffOnPartyTrigger::IsActive() && AI_VALUE2(bool, "swimming", "current target");
        }
    };

    class EarthShieldOnPartyTrigger : public BuffOnPartyTrigger {
    public:
        EarthShieldOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "earth shield") {}
    };

    class EarthShieldOnMasterTrigger : public BuffOnMasterTrigger {
    public:
        EarthShieldOnMasterTrigger(PlayerbotAI* ai) : BuffOnMasterTrigger(ai, "earth shield") {}
    };

	class CurePoisonTrigger : public NeedCureTrigger
	{
	public:
		CurePoisonTrigger(PlayerbotAI* ai) : NeedCureTrigger(ai, "cure poison", DISPEL_POISON) {}
	};

	class PartyMemberCurePoisonTrigger : public PartyMemberNeedCureTrigger
	{
	public:
		PartyMemberCurePoisonTrigger(PlayerbotAI* ai) : PartyMemberNeedCureTrigger(ai, "cure poison", DISPEL_POISON) {}
	};

	class CureDiseaseTrigger : public NeedCureTrigger
	{
	public:
		CureDiseaseTrigger(PlayerbotAI* ai) : NeedCureTrigger(ai, "cure disease", DISPEL_DISEASE) {}
	};

	class PartyMemberCureDiseaseTrigger : public PartyMemberNeedCureTrigger
	{
	public:
		PartyMemberCureDiseaseTrigger(PlayerbotAI* ai) : PartyMemberNeedCureTrigger(ai, "cure disease", DISPEL_DISEASE) {}
	};

    class PartyMemberCleanseSpiritDiseaseTrigger : public PartyMemberNeedCureTrigger
    {
    public:
        PartyMemberCleanseSpiritDiseaseTrigger(PlayerbotAI* ai) : PartyMemberNeedCureTrigger(ai, "cleanse spirit", DISPEL_DISEASE) {}
    };

    class ShockTrigger : public DebuffTrigger {
    public:
        ShockTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "flame shock") {}
        virtual bool IsActive();
    };

    class FrostShockSnareTrigger : public SnareTargetTrigger {
    public:
        FrostShockSnareTrigger(PlayerbotAI* ai) : SnareTargetTrigger(ai, "frost shock") {}
    };

    //class HeroismTrigger : public BoostTrigger
    //{
    //public:
    //    HeroismTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "heroism") {}
    //};

    //class BloodlustTrigger : public BoostTrigger
    //{
    //public:
    //    BloodlustTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "bloodlust") {}
    //};

    class MaelstromWeaponTrigger : public HasAuraTrigger
    {
    public:
        MaelstromWeaponTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "maelstrom weapon") {}
    };

    class WindShearInterruptEnemyHealerSpellTrigger : public InterruptEnemyHealerTrigger
    {
    public:
        WindShearInterruptEnemyHealerSpellTrigger(PlayerbotAI* ai) : InterruptEnemyHealerTrigger(ai, "wind shear") {}
    };

    class HexTrigger : public HasCcTarget6Trigger
    {
    public:
        HexTrigger(PlayerbotAI* ai) : HasCcTarget6Trigger(ai, "hex") {}
    };

}
