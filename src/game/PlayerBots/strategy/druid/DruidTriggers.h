#pragma once
#include "../triggers/GenericTriggers.h"

namespace ai {
    class MarkOfTheWildOnPartyTrigger : public BuffOnPartyTrigger
    {
    public:
        MarkOfTheWildOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "mark of the wild") {}
    };

    class MarkOfTheWildTrigger : public BuffTrigger
    {
    public:
        MarkOfTheWildTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "mark of the wild") {}
    };

    class ThornsTrigger : public BuffTrigger
    {
    public:
        ThornsTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "thorns") {}
        virtual bool IsActive() { return !ai->HasAnyAuraOf(bot, "bear form", "dire bear form", "moonkin form", NULL); }
    };

    class ThornsOnPartyTrigger : public BuffOnPartyTrigger
    {
    public:
        ThornsOnPartyTrigger(PlayerbotAI* ai) : BuffOnPartyTrigger(ai, "thorns") {}
        virtual bool IsActive();
    };

    class RakeTrigger : public DebuffTrigger
    {
    public:
        RakeTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "rake") {}
        virtual bool IsActive() { return (DebuffTrigger::IsActive() && ai->HasAura("cat form", bot)) && !ai->HasAura("prowl", bot);}
    };

    class RipTrigger : public DebuffTrigger
    {
    public:
        RipTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "rip") {}
        virtual bool IsActive() { return (DebuffTrigger::IsActive() && ai->HasAura("cat form", bot));}
    };

    class PounceTrigger : public DebuffTrigger
    {
    public:
        PounceTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "pounce") {}
        virtual bool IsActive() { return (DebuffTrigger::IsActive() && ai->HasAura("prowl", bot));}
    };

    class InsectSwarmTrigger : public DebuffTrigger
    {
    public:
        InsectSwarmTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "insect swarm") {}
        virtual bool IsActive() { return DebuffTrigger::IsActive() && ai->HasAnyAuraOf(bot, "caster form", "moonkin form", NULL); }
    };

    class MoonfireTrigger : public DebuffTrigger
    {
    public:
        MoonfireTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "moonfire") {}
        virtual bool IsActive() { return DebuffTrigger::IsActive() && ai->HasAnyAuraOf(bot, "caster form", "moonkin form", NULL); }
    };

    class FaerieFireTrigger : public DebuffTrigger
    {
    public:
        FaerieFireTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "faerie fire") {}
        virtual bool IsActive() { return DebuffTrigger::IsActive() && ai->HasAnyAuraOf(bot, "caster form", "moonkin form", NULL); }
    };

    class FaerieFireFeralTrigger : public DebuffTrigger
    {
    public:
        FaerieFireFeralTrigger(PlayerbotAI* ai) : DebuffTrigger(ai, "faerie fire (feral)") {}
        virtual bool IsActive() { return DebuffTrigger::IsActive() && !ai->HasAura("prowl", bot) && ai->HasAnyAuraOf(bot, "cat form", "bear form", "dire bear form", NULL); }
    };

    class BashInterruptSpellTrigger : public InterruptSpellTrigger
    {
    public:
        BashInterruptSpellTrigger(PlayerbotAI* ai) : InterruptSpellTrigger(ai, "bash") {}
    };

    class TigersFuryTrigger : public BuffTrigger
    {
    public:
        TigersFuryTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "tiger's fury") {}
        virtual bool IsActive() { return (BuffTrigger::IsActive() && ai->HasAura("cat form", bot) && (AI_VALUE2(uint8, "energy", "self target") < 30) && bot->getLevel() > 55);}
    };

    class NaturesGraspTrigger : public BoostTrigger
    {
    public:
        NaturesGraspTrigger(PlayerbotAI* ai) : BoostTrigger(ai, "nature's grasp") {}
    };

    class EntanglingRootsTrigger : public HasCcTarget2Trigger
    {
    public:
        EntanglingRootsTrigger(PlayerbotAI* ai) : HasCcTarget2Trigger(ai, "entangling roots") {}
    };

    class HibernateTrigger : public HasCcTarget3Trigger
    {
    public:
        HibernateTrigger(PlayerbotAI* ai) : HasCcTarget3Trigger(ai, "hibernate") {}
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

    class BearFormTrigger : public BuffTrigger
    {
    public:
        BearFormTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "bear form") {}
        virtual bool IsActive() { return !ai->HasAnyAuraOf(bot, "bear form", "dire bear form", NULL); }
    };
/*
    class CasterFormTrigger : public BuffTrigger
    {
    public:
        CasterFormTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "caster form") {}
        virtual bool IsActive() { return !ai->HasAnyAuraOf(bot, "tree of life","bear form", "dire bear form", "moonkin form", "travel form", "aquatic form", NULL); }
    };
*/
    class TreeFormTrigger : public BuffTrigger
    {
    public:
        TreeFormTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "tree of life") {}
        virtual bool IsActive() { return !ai->HasAura("tree of life", bot); }
    };

    class MoonkinFormTrigger : public BuffTrigger
    {
    public:
        MoonkinFormTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "Moonkin") {}
        virtual bool IsActive() { return !ai->HasAura("moonkin form", bot); }
    };


    class SavageRoarTrigger : public BuffTrigger
    {
    public:
        SavageRoarTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "savage roar") {}
        virtual bool IsActive() { return BuffTrigger::IsActive() && ai->HasAura("cat form", bot); }
    };

    class CatFormTrigger : public BuffTrigger
    {
    public:
        CatFormTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "cat form") {}
        virtual bool IsActive() { return !ai->HasAura("cat form", bot); }
    };

    class ProwlTrigger : public BuffTrigger
    {
    public:
        ProwlTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "prowl") {}
        virtual bool IsActive() { return BuffTrigger::IsActive() && !AI_VALUE2(bool, "combat", "self target") && !AI_VALUE2(bool, "mounted", "self target"); }
    };

    class DashTrigger : public BuffTrigger
    {
    public:
        DashTrigger(PlayerbotAI* ai) : BuffTrigger(ai, "dash") {}
    };

    class PredatorySwiftnessTrigger : public HasAuraTrigger
    {
    public:
        PredatorySwiftnessTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "predator's swiftness") {}
		virtual bool IsActive() { return HasAuraTrigger::IsActive() && (AI_VALUE2(uint8, "mana", "self target") >= 30 && AI_VALUE2(uint8, "aoe heal", "almost full") != 0); }
    };

    class EclipseSolarTrigger : public HasAuraTrigger
    {
    public:
        EclipseSolarTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "eclipse (solar)") {}
    };

    class EclipseLunarTrigger : public HasAuraTrigger
    {
    public:
        EclipseLunarTrigger(PlayerbotAI* ai) : HasAuraTrigger(ai, "eclipse (lunar)") {}
    };

    class BashInterruptEnemyHealerSpellTrigger : public InterruptEnemyHealerTrigger
    {
    public:
        BashInterruptEnemyHealerSpellTrigger(PlayerbotAI* ai) : InterruptEnemyHealerTrigger(ai, "bash") {}
    };
}
