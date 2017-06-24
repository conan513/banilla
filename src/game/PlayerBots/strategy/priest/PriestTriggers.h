#pragma once

#include "../triggers/GenericTriggers.h"

namespace ai
{
    BUFF_ON_PARTY_TRIGGER(PowerWordFortitudeOnPartyTrigger, "power word: fortitude", "power word: fortitude on party")
    BUFF_TRIGGER(PowerWordFortitudeTrigger, "power word: fortitude", "power word: fortitude")

    //BUFF_ON_PARTY_TRIGGER(, "divine spirit", "divine spirit on party")

    class DivineSpiritOnPartyTrigger : public BuffOnPartyTrigger
    {
    public:
        DivineSpiritOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "divine spirit") {}
        virtual bool IsActive();
    };

    class DivineSpiritTrigger : public BuffTrigger
    {
    public:
        DivineSpiritTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "divine spirit") {}
        virtual bool IsActive();
    };

    class PrayerOfShadowProtectionOnPartyTrigger : public BuffOnPartyTrigger
    {
    public:
        PrayerOfShadowProtectionOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "prayer of shadow protection") {}
        virtual bool IsActive();
    };

    class PrayerOfShadowProtectionTrigger : public BuffTrigger
    {
    public:
        PrayerOfShadowProtectionTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "prayer of shadow protection") {}
        virtual bool IsActive();
    };

    //BUFF_ON_PARTY_TRIGGER(PrayerOfShadowProtectionOnPartyTrigger, "prayer of shadow protection", "prayer of shadow protection on party")
    //BUFF_TRIGGER(PrayerOfShadowProtectionTrigger, "prayer of shadow protection", "prayer of shadow protection")

    BUFF_TRIGGER(InnerFireTrigger, "inner fire", "inner fire")
    BUFF_TRIGGER(FearWardTrigger, "fear ward", "fear ward")

    class FearWardOnMasterTrigger : public BuffOnMasterTrigger {
    public:
        FearWardOnMasterTrigger(PlayerbotAI* ai) : BuffOnMasterTrigger(ai, "fear ward") {}
    };


    BUFF_TRIGGER(VampiricEmbraceTrigger, "vampiric embrace", "vampiric embrace")

    class SurgeOfLightTrigger : public HasAuraTrigger
    {
    public:
        SurgeOfLightTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "surge of light") {}
    };

    class PowerWordPainOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        PowerWordPainOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "shadow word: pain") {}
    };

    class DevouringPlagueTrigger : public DebuffTrigger
    {
    public:
        DevouringPlagueTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "devouring plague") {}
        virtual bool IsActive() {
			return (DebuffTrigger::IsActive() && !(AI_VALUE2(bool, "target normal", "current target")));
	     }
    };

    DEBUFF_TRIGGER(PowerWordPainTrigger, "shadow word: pain", "shadow word: pain")
    DEBUFF_TRIGGER(VampiricTouchTrigger, "vampiric touch", "vampiric touch")

     class ShackleUndeadTrigger : public HasCcTarget5Trigger
    {
    public:
        ShackleUndeadTrigger(PlayerbotAI* ai) : HasCcTarget5Trigger(ai, "shackle undead") {}
    };

    class DispelMagicTrigger : public NeedCureTrigger
    {
    public:
        DispelMagicTrigger(PlayerbotAI* ai) : NeedCureTrigger(ai, "dispel magic", DISPEL_MAGIC) {}
    };

    class DispelMagicPartyMemberTrigger : public PartyMemberNeedCureTrigger
    {
    public:
        DispelMagicPartyMemberTrigger(PlayerbotAI* ai) : PartyMemberNeedCureTrigger(ai, "dispel magic", DISPEL_MAGIC) {}
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

    class ShadowformTrigger : public BuffTrigger {
    public:
        ShadowformTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "shadowform") {}
        virtual bool IsActive() { return !ai->HasAura("shadowform", bot); }
    };

    class SilenceEnemyHealerTrigger : public InterruptEnemyHealerTrigger
    {
    public:
        SilenceEnemyHealerTrigger(PlayerbotAI* ai) : InterruptEnemyHealerTrigger(ai, "silence") {}
    };
}
