#pragma once
#include "../triggers/GenericTriggers.h"

namespace ai
{
    BUFF_ON_PARTY_TRIGGER(ArcaneIntellectOnPartyTrigger, "arcane intellect", "arcane intellect on party")
    BUFF_ON_PARTY_TRIGGER(FocusMagicOnPartyTrigger, "focus magic", "focus magic on party")
    BUFF_TRIGGER(ArcaneIntellectTrigger, "arcane intellect", "arcane intellect")
    //BUFF_TRIGGER(MoltenArmorTrigger, "molten armor", "molten armor")
    BUFF_TRIGGER(SummonWaterElementalTrigger, "summon water elemental", "summon water elemental")
    DEBUFF_TRIGGER(LivingBombTrigger, "living bomb", "living bomb")
    DEBUFF_TRIGGER(SlowTrigger, "slow", "slow")
    DEBUFF_TRIGGER(ImprovedScorchTrigger, "improved scorch", "improved scorch")

    class MoltenArmorTrigger : public BuffTrigger {
    public:
        MoltenArmorTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "molten armor") {}
        virtual bool IsActive();
    };

 //   class LivingBombTrigger : public DebuffTrigger {
 //   public:
 //       LivingBombTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "living bomb") {}
//	};

    //class FireballTrigger : public DebuffTrigger {
    //public:
    //    FireballTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "fireball") {}
	//};

 //   class PyroblastTrigger : public DebuffTrigger {
 //   public:
 //       PyroblastTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "pyroblast") {}
 //   };

    class HotStreakTrigger : public HasAuraTrigger {
    public:
        HotStreakTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "hot streak") {}
    };

    class BlazingSpeedTrigger : public HasAuraTrigger {
    public:
        BlazingSpeedTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "blazing speed") {}
    };

    class MissileBarrageTrigger : public HasAuraTrigger {
    public:
        MissileBarrageTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "missile barrage") {}
    };

    class FingersFrostTrigger : public HasAuraTrigger {
    public:
        FingersFrostTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "fingers of frost") {}
    };

    class BrainfreezeTrigger : public HasAuraTrigger {
    public:
        BrainfreezeTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "brain freeze") {}
    };

    class FieryPaybackTrigger : public HasAuraTrigger {
    public:
        FieryPaybackTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "fiery payback") {}
    };

    class ArcaneBlastTrigger : public BuffTrigger {
    public:
        ArcaneBlastTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "arcane blast") {}
    };

    class CounterspellInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        CounterspellInterruptSpellTrigger(PlayerbotAI* ai) : InterruptSpellTrigger(ai, "counterspell") {}
    };

    class CombustionTrigger : public BoostTrigger
    {
    public:
        CombustionTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "combustion") {}
    };

    class IcyVeinsTrigger : public BoostTrigger
    {
    public:
        IcyVeinsTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "icy veins") {}
    };

    class PolymorphTrigger : public HasCcTarget5Trigger
    {
    public:
        PolymorphTrigger(PlayerbotAI* ai) : HasCcTarget5Trigger(ai, "polymorph") {}
    };

    class RemoveCurseTrigger : public NeedCureTrigger
    {
    public:
        RemoveCurseTrigger(PlayerbotAI* ai) : NeedCureTrigger(ai, "remove curse", DISPEL_CURSE) {}
    };

    class PartyMemberRemoveCurseTrigger : public PartyMemberNeedCureTrigger
    {
    public:
        PartyMemberRemoveCurseTrigger(PlayerbotAI* ai) : PartyMemberNeedCureTrigger(ai, "remove curse", DISPEL_CURSE) {}
    };

    class SpellstealTrigger : public TargetAuraDispelTrigger
    {
    public:
        SpellstealTrigger(PlayerbotAI* ai) : TargetAuraDispelTrigger(ai, "spellsteal", DISPEL_MAGIC) {}
    };

    class CounterspellEnemyHealerTrigger : public InterruptEnemyHealerTrigger
    {
    public:
        CounterspellEnemyHealerTrigger(PlayerbotAI* ai) : InterruptEnemyHealerTrigger(ai, "counterspell") {}
    };
}
