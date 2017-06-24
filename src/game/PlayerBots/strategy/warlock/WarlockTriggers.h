#pragma once
#include "../triggers/GenericTriggers.h"

namespace ai
{
	class DemonArmorTrigger : public BuffTrigger
	{
	public:
		DemonArmorTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "demon armor") {}
		virtual bool IsActive();
	};

	BEGIN_TRIGGER(DemonDeadTrigger, Trigger)
    END_TRIGGER()

    BEGIN_TRIGGER(DemonLowHealthTrigger, Trigger)
    END_TRIGGER()

/*
    class SpellstoneTrigger : public BuffTrigger
    {
    public:
        SpellstoneTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "spellstone") {}
        virtual bool IsActive();
    };

    class FirestoneTrigger : public BuffTrigger
    {
    public:
        FirestoneTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "firestone") {}
        virtual bool IsActive();
    };
*/


    //DEBUFF_TRIGGER(CurseOfAgonyTrigger, "curse of agony", "curse of agony");
    //DEBUFF_TRIGGER(CorruptionTrigger, "corruption", "corruption");


    //class DeathCoilOnAttackerTrigger : public DebuffOnAttackerTrigger
    //{
    //public:
    //    DeathCoilOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "corruption") {}
    //};


    class NoCurseTrigger : public OwnDebuffTrigger
	{
	public:
		NoCurseTrigger(PlayerbotAI* ai) : OwnDebuffTrigger(ai, "curse of the elements") {}
		virtual bool IsActive();
	};

    class NoCorruptionTrigger : public DebuffTrigger
	{
	public:
		NoCorruptionTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "corruption") {}
		virtual bool IsActive();
	};

    class ImmolateTrigger : public DebuffTrigger
	{
	public:
		ImmolateTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "immolate") {}
	};


    //DEBUFF_TRIGGER(WarlockNoCurseTrigger, "curse of agony", "curse of agony");
    //DEBUFF_TRIGGER(WarlockNoCorruptionTrigger, "corruption", "corruption");
    //DEBUFF_TRIGGER(ImmolateTrigger, "immolate", "immolate");
    DEBUFF_TRIGGER(HauntTrigger, "haunt", "haunt");
    DEBUFF_TRIGGER(ImprovedShadowbolt, "shadow Mastery", "shadow Mastery")

    class CurseOnAttackerTrigger : public OwnDebuffOnAttackerTrigger
    {
    public:
        CurseOnAttackerTrigger(PlayerbotAI* ai) : OwnDebuffOnAttackerTrigger(ai, "curse of agony") {}
        virtual bool IsActive();
    };

    class CorruptionOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        CorruptionOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "corruption") {}
        virtual bool IsActive();
    };

    class ImmolateOnAttackerTrigger : public DebuffOnAttackerTrigger
    {
    public:
        ImmolateOnAttackerTrigger(PlayerbotAI* ai) : DebuffOnAttackerTrigger(ai, "immolate") {}
    };


    class ShadowTranceTrigger : public HasAuraTrigger
    {
    public:
        ShadowTranceTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "shadow trance") {}
    };

    class MoltenCoreTrigger : public HasAuraTrigger
    {
    public:
        MoltenCoreTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "molten core") {}
    };

    class DecimationTrigger : public HasAuraTrigger
    {
    public:
        DecimationTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "decimation") {}
    };

    class BacklashTrigger : public HasAuraTrigger
    {
    public:
        BacklashTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "backlash") {}
    };

    class BanishTrigger : public HasCcTarget3Trigger
    {
    public:
        BanishTrigger(PlayerbotAI* ai) : HasCcTarget3Trigger(ai, "banish") {}
    };

    class WarlockConjuredItemTrigger : public ItemCountTrigger
    {
    public:
        WarlockConjuredItemTrigger(PlayerbotAI* ai, string item) : ItemCountTrigger(ai, item, 1) {}

        virtual bool IsActive() { return ItemCountTrigger::IsActive() && AI_VALUE2(uint8, "item count", "soul shard") > 0; }
    };

    class HasSpellstoneTrigger : public WarlockConjuredItemTrigger
    {
    public:
        HasSpellstoneTrigger(PlayerbotAI* ai) : WarlockConjuredItemTrigger(ai, "spellstone") {}
    };

    class HasFirestoneTrigger : public WarlockConjuredItemTrigger
    {
    public:
        HasFirestoneTrigger(PlayerbotAI* ai) : WarlockConjuredItemTrigger(ai, "firestone") {}
    };

    class HasHealthstoneTrigger : public WarlockConjuredItemTrigger
    {
    public:
        HasHealthstoneTrigger(PlayerbotAI* ai) : WarlockConjuredItemTrigger(ai, "healthstone") {}
    };

    class HasSoulstoneTrigger : public WarlockConjuredItemTrigger
    {
    public:
        HasSoulstoneTrigger(PlayerbotAI* ai) : WarlockConjuredItemTrigger(ai, "soulstone") {}
    };

    class SoulstoneOnMasterTrigger : public BuffOnMasterTrigger {
    public:
        SoulstoneOnMasterTrigger(PlayerbotAI* ai) : BuffOnMasterTrigger(ai, "soulstone") {}

        virtual bool IsActive() { return BuffOnMasterTrigger::IsActive() && AI_VALUE2(uint8, "item count", "soulstone") > 0; }
    };

    class FearTrigger : public HasCcTargetTrigger
    {
    public:
        FearTrigger(PlayerbotAI* ai) : HasCcTargetTrigger(ai, "fear") {}
    };


}
