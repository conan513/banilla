#pragma once

#include "../actions/GenericActions.h"
#include "../actions/UseItemAction.h"

namespace ai
{
	class CastDemonSkinAction : public CastBuffSpellAction {
	public:
		CastDemonSkinAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "demon skin") {}
	};

	class CastDemonArmorAction : public CastBuffSpellAction
	{
	public:
		CastDemonArmorAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "demon armor") {}
	};

	class CastFelArmorAction : public CastBuffSpellAction
	{
	public:
		CastFelArmorAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "fel armor") {}
	};

    BEGIN_RANGED_SPELL_ACTION(CastShadowBoltAction, "shadow bolt")
    END_SPELL_ACTION()

	class CastDrainSoulAction : public CastSpellAction
	{
	public:
		CastDrainSoulAction(PlayerbotAI* ai) : CastSpellAction(ai, "drain soul") {}
		virtual bool isUseful()
		{
			return AI_VALUE2(uint8, "item count", "soul shard") < 16;
		}
	};

	class CastDrainManaAction : public CastSpellAction
	{
	public:
		CastDrainManaAction(PlayerbotAI* ai) : CastSpellAction(ai, "drain mana") {}
	};

	class CastDrainLifeAction : public CastSpellAction
	{
	public:
		CastDrainLifeAction(PlayerbotAI* ai) : CastSpellAction(ai, "drain life") {}

		virtual bool isUseful()
	    {
	        return CastSpellAction::isUseful() && AI_VALUE2(uint8, "health", "self target") < sPlayerbotAIConfig.criticalHealth;
	    }
	};


	class CastCurseOfAgonyAction : public CastDebuffSpellAction
	{
	public:
		CastCurseOfAgonyAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "curse of agony") {}
		virtual bool IsInstant() {return true;}

       virtual bool isUseful()
        {
            return CastDebuffSpellAction::isUseful() && !ai->HasAura("curse of doom",  GetTarget());
            }
	};

    class CastCurseOfExhaustionAction : public CastOwnDebuffSpellAction
	{
	public:
		CastCurseOfExhaustionAction(PlayerbotAI* ai) : CastOwnDebuffSpellAction(ai, "curse of exhaustion") {}
		virtual bool IsInstant() {return true;}
	};

    class CastCurseOfDoomAction : public CastDebuffSpellAction
	{
	public:
		CastCurseOfDoomAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "curse of doom") {}
		virtual bool IsInstant() {return true;}

        virtual bool isUseful()
        {
            return CastDebuffSpellAction::isUseful() && !ai->HasAura("curse of agony",  GetTarget());
            }
	};

	class CastCurseOfWeaknessAction : public CastOwnDebuffSpellAction
	{
	public:
		CastCurseOfWeaknessAction(PlayerbotAI* ai) : CastOwnDebuffSpellAction(ai, "curse of weakness") {}
		virtual bool IsInstant() {return true;}

    virtual bool isUseful()
        {
            return CastOwnDebuffSpellAction::isUseful() && !ai->HasOwnAura("curse of the elements",  GetTarget());
            }
	};

	class CastCurseOfTheElementsAction : public CastOwnDebuffSpellAction
	{
	public:
		CastCurseOfTheElementsAction(PlayerbotAI* ai) : CastOwnDebuffSpellAction(ai, "curse of the elements") {}
		virtual bool IsInstant() {return true;}

        virtual bool isUseful()
        {
            return CastOwnDebuffSpellAction::isUseful() && !ai->HasOwnAura("curse of weakness",  GetTarget());
            }
	};

	class CastCorruptionAction : public CastDebuffSpellAction
	{
	public:
		CastCorruptionAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "corruption") {}
		virtual bool IsInstant() {return true;}

        virtual bool isUseful()
        {
            return CastDebuffSpellAction::isUseful() && !ai->HasAura("seed of corruption", GetTarget());
            }
	};


	class CastSummonVoidwalkerAction : public CastBuffSpellAction
	{
	public:
		CastSummonVoidwalkerAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "summon voidwalker") {}

        virtual bool isUseful()
		{
		    if (AI_VALUE2(uint8, "item count", "soul shard") < 1)
                return false;
            else if (!AI_VALUE2(bool, "combat", "self target"))
                return true;
            else if (ai->HasAura("fel domination", bot))
                return true;
            else if (AI_VALUE2(bool,"target boss", "current target"))
                return !AI_VALUE2(bool, "has aggro", "current target");
            else return false;
		}
	};


	class CastSummonFelhunterAction : public CastBuffSpellAction
	{
	public:
		CastSummonFelhunterAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "summon felhunter") {}

        virtual bool isUseful()
		{
		    if (AI_VALUE2(uint8, "item count", "soul shard") < 1)
                return false;
            else if (!AI_VALUE2(bool, "combat", "self target"))
                return true;
            else if (ai->HasAura("fel domination", bot))
                return true;
            else if (AI_VALUE2(bool,"target boss", "current target"))
                return !AI_VALUE2(bool, "has aggro", "current target");
            else return false;
		}
	};

	class CastSummonSuccubusAction : public CastBuffSpellAction
	{
	public:
		CastSummonSuccubusAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "summon succubus") {}

        virtual bool isUseful()
		{
		    if (AI_VALUE2(uint8, "item count", "soul shard") < 1)
                return false;
            else if (!AI_VALUE2(bool, "combat", "self target"))
                return true;
            else if (ai->HasAura("fel domination", bot))
                return true;
            else if (AI_VALUE2(bool,"target boss", "current target"))
                return !AI_VALUE2(bool, "has aggro", "current target");
            else return false;
		}
	};

	class CastSummonFelguardAction : public CastBuffSpellAction
	{
	public:
		CastSummonFelguardAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "summon felguard") {}
        virtual bool isUseful()
		{
		    if (AI_VALUE2(uint8, "item count", "soul shard") < 1)
                return false;
            else if (!AI_VALUE2(bool, "combat", "self target"))
                return true;
            else if (ai->HasAura("fel domination", bot))
                return true;
            else if (AI_VALUE2(bool,"target boss", "current target"))
                return !AI_VALUE2(bool, "has aggro", "current target");
            else return false;
		}
	};

	class CastSummonImpAction : public CastBuffSpellAction
	{
	public:
		CastSummonImpAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "summon imp") {}

        virtual bool isUseful()
		{
            if (!AI_VALUE2(bool, "combat", "self target"))
                return true;
            else if (ai->HasAura("fel domination", bot))
                return true;
            else if (AI_VALUE2(bool,"target boss", "current target"))
                return !AI_VALUE2(bool, "has aggro", "current target");
            else return false;
		}
	};

	class CastCreateHealthstoneAction : public CastBuffSpellAction
	{
	public:
		CastCreateHealthstoneAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "create healthstone") {}
		virtual bool isUseful()
		{
			return AI_VALUE2(uint8, "item count", "soul shard") > 0;
		}
	};

	class CastCreateSoulstoneAction : public CastBuffSpellAction
	{
	public:
		CastCreateSoulstoneAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "create soulstone") {}
		virtual bool isUseful()
		{
			return AI_VALUE2(uint8, "item count", "soul shard") > 0;
		}
	};

    class CastDemonicEmpowermentAction : public CastBuffSpellAction
	{
	public:
		CastDemonicEmpowermentAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "demonic empowerment") {}
	};

    class CastFelDominationAction : public CastBuffSpellAction
	{
	public:
		CastFelDominationAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "fel domination") {}
	};

    class CastMetamorphosisAction : public CastBuffSpellAction
	{
	public:
		CastMetamorphosisAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "metamorphosis") {}
	};

	class CastShadowCleaveAction : public CastSpellAction
	{
	public:
		CastShadowCleaveAction(PlayerbotAI* ai) : CastSpellAction(ai, "shadow cleave") {}

		virtual bool isUseful() {
            return CastSpellAction::isUseful() && ai->HasAura("metamorphosis", AI_VALUE(Unit*, "self target"));
        }
	};

	class CastImmolationAuraAction : public CastBuffSpellAction
	{
	public:
		CastImmolationAuraAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "immolation aura") {}

     virtual bool isUseful() {
            return CastBuffSpellAction::isUseful() && ai->HasAura("metamorphosis", AI_VALUE(Unit*, "self target"));
        }
	};

	class CastChallengingHowlAction : public CastMeleeSpellAction
	{
	public:
		CastChallengingHowlAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "challenging howl") {}
        virtual bool isUseful() {
            return CastMeleeSpellAction::isUseful() && ai->HasAura("metamorphosis", AI_VALUE(Unit*, "self target"));
        }
	};

	class CastDemonChargeAction : public CastSpellAction
	{
	public:
		CastDemonChargeAction(PlayerbotAI* ai) : CastSpellAction(ai, "demon charge") {}

		virtual bool isUseful() {
            return CastSpellAction::isUseful() && ai->HasAura("metamorphosis", AI_VALUE(Unit*, "self target"));
        }
	};

    class CastCreateSpellstoneAction : public CastBuffSpellAction
	{
	public:
		CastCreateSpellstoneAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "create spellstone") {}
		virtual bool isUseful()
		{
			return AI_VALUE2(uint8, "item count", "soul shard") > 0;
		}
	};

	class UseSoulstoneOnMasterAction : public UseItemAction
	{
	public:
		UseSoulstoneOnMasterAction(PlayerbotAI* ai) : UseItemAction(ai, "soulstone",true) {setTargetUnit(AI_VALUE(Unit*, "master target"));}
		virtual bool isUseful()
	    {
	        return !ai->HasAura("soulstone", AI_VALUE(Unit*, "master target"));
	    }
	    virtual string getName() { return "soulstone on master";}
        virtual string GetTargetName() { return "master target";}
	};

	class CastCreateFirestoneAction : public CastBuffSpellAction
	{
	public:
		CastCreateFirestoneAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "create firestone") {}
		virtual bool isUseful()
		{
			return AI_VALUE2(uint8, "item count", "soul shard") > 0;
		}
	};

    class UseFirestoneMainhandAction : public UseItemAction
    {
    public:
        UseFirestoneMainhandAction(PlayerbotAI* ai) : UseItemAction(ai, "firestone") {setTargetMainhand();}
    };

    class UseSpellstoneMainhandAction : public UseItemAction
    {
    public:
        UseSpellstoneMainhandAction(PlayerbotAI* ai) : UseItemAction(ai, "spellstone") {setTargetMainhand();}
    };

    class CastSoulShatterAction : public CastBuffSpellAction
	{
	public:
		CastSoulShatterAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "soul shatter") {}
	};

    class CastBanishAction : public CastDebuffSpellAction
	{
	public:
		CastBanishAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "banish") {}
	};

    class CastBanishCcAction : public CastDebuffSpellAction
    {
    public:
        CastBanishCcAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "banish on cc") {}
        virtual Value<Unit*>* GetTargetValue() { return context->GetValue<Unit*>("cc target3", "banish"); }
        virtual bool Execute(Event event) { return ai->CastSpell("banish", GetTarget()); }
    };

    class CastSeedOfCorruptionAction : public CastDebuffSpellAction
    {
    public:
        CastSeedOfCorruptionAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "seed of corruption") {}

        virtual bool isUseful()
        {
            return CastDebuffSpellAction::isUseful() && !ai->HasOwnAura("corruption", GetTarget());
            }
    };

    class CastRainOfFireAction : public CastSpellAction
    {
    public:
        CastRainOfFireAction(PlayerbotAI* ai) : CastSpellAction(ai, "rain of fire") {}
    };

    class CastShadowfuryAction : public CastSpellAction
    {
    public:
        CastShadowfuryAction(PlayerbotAI* ai) : CastSpellAction(ai, "shadowfury") {}
        virtual bool isUseful() { return AI_VALUE2(float, "distance", "current target") <= sPlayerbotAIConfig.tooCloseDistance; }
    };

    class CastImmolateAction : public CastDebuffSpellAction
    {
    public:
        CastImmolateAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "immolate") {}
 //       virtual bool isUseful() {
 //           return CastSpellAction::isUseful() && !ai->HasOwnAura("immolate", AI_VALUE(Unit*, "current target"));
 //       }
    };

    class CastImmolateOnAttackerAction : public CastDebuffSpellOnAttackerAction
    {
    public:
        CastImmolateOnAttackerAction(PlayerbotAI* ai) : CastDebuffSpellOnAttackerAction(ai, "immolate") {}
        virtual bool IsInstant() {return true;}
    };

    class CastCorruptionOnAttackerAction : public CastDebuffSpellOnAttackerAction
    {
    public:
        CastCorruptionOnAttackerAction(PlayerbotAI* ai) : CastDebuffSpellOnAttackerAction(ai, "corruption") {}
        virtual bool IsInstant() {return true;}
    };

    class CastCurseOfAgonyOnAttackerAction : public CastDebuffSpellOnAttackerAction
    {
    public:
        CastCurseOfAgonyOnAttackerAction(PlayerbotAI* ai) : CastDebuffSpellOnAttackerAction(ai, "curse of agony") {}
        virtual bool IsInstant() {return true;}
    };

    class CastCurseOfTheElementsOnAttackerAction : public CastOwnDebuffSpellOnAttackerAction
    {
    public:
        CastCurseOfTheElementsOnAttackerAction(PlayerbotAI* ai) : CastOwnDebuffSpellOnAttackerAction(ai, "curse of the elements") {}
        virtual bool IsInstant() {return true;}
    };

    class CastCurseOfWeaknessOnAttackerAction : public CastOwnDebuffSpellOnAttackerAction
    {
    public:
        CastCurseOfWeaknessOnAttackerAction(PlayerbotAI* ai) : CastOwnDebuffSpellOnAttackerAction(ai, "curse of weakness") {}
        virtual bool IsInstant() {return true;}
    };

    class CastConflagrateAction : public CastSpellAction
    {
    public:
        CastConflagrateAction(PlayerbotAI* ai) : CastSpellAction(ai, "conflagrate") {}

        virtual NextAction** getAlternatives()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("incinerate"), NULL), CastSpellAction::getAlternatives());
        }

            virtual bool IsInstant() {return true;}
            virtual bool isUseful() {
            return CastSpellAction::isUseful() && ai->HasOwnAura("immolate", AI_VALUE(Unit*, "current target"));
        }

    };

    class CastIncinerateAction : public CastSpellAction
    {
    public:
        CastIncinerateAction(PlayerbotAI* ai) : CastSpellAction(ai, "incinerate") {}

        virtual NextAction** getAlternatives()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("shadow bolt"), NULL), CastSpellAction::getAlternatives());
        }
    };

    class CastSoulFireAction : public CastSpellAction
    {
    public:
        CastSoulFireAction(PlayerbotAI* ai) : CastSpellAction(ai, "soul fire") {}
    };

    class CastChaosBoltAction : public CastSpellAction
    {
    public:
        CastChaosBoltAction(PlayerbotAI* ai) : CastSpellAction(ai, "chaos bolt") {}
        virtual NextAction** getAlternatives()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("shadow bolt"), NULL), CastSpellAction::getAlternatives());
        }

    };

    class CastHauntAction : public CastDebuffSpellAction
    {
    public:
        CastHauntAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "haunt") {}
    };

    class CastHowlOfTerrorAction : public CastDebuffSpellAction
    {
    public:
        CastHowlOfTerrorAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "howl of terror") {}
        virtual bool isUseful() { return AI_VALUE2(float, "distance", GetTargetName()) <= sPlayerbotAIConfig.tooCloseDistance; }
    };

    class CastDeathcoilAction : public CastDebuffSpellAction
    {
    public:
        CastDeathcoilAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "death coil") {}
    };

    class CastUnstableAfflictionAction : public CastDebuffSpellAction
    {
    public:
        CastUnstableAfflictionAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "unstable affliction") {}
        virtual bool IsInstant() {return true;}
    };

    class CastFearAction : public CastDebuffSpellAction
    {
    public:
        CastFearAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "fear") {}

        virtual bool isUseful()
        {
            if (AI_VALUE2(bool, "has aggro", "current target"))
                return true;
            else if (AI_VALUE2(bool, "target player", "current target"))
                return true;
            else if (AI_VALUE2(bool, "in party", "self target"))
                return false;
            else
            {
                list<ObjectGuid> targets = AI_VALUE(list<ObjectGuid>, "possible targets");
                list<ObjectGuid> attackers = AI_VALUE(list<ObjectGuid>, "attackers");
                return targets.size() == attackers.size();
            }
        }
    };

    class CastFearOnCcAction : public CastBuffSpellAction
    {
    public:
        CastFearOnCcAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "fear on cc") {}
        virtual Value<Unit*>* GetTargetValue() { return context->GetValue<Unit*>("cc target", "fear"); }
        virtual bool Execute(Event event) { return ai->CastSpell("fear", GetTarget()); }

        virtual bool isUseful()
        {
            if (AI_VALUE2(bool, "target player", "cc target"))
                return true;
             else if (AI_VALUE2(bool, "in party", "self target"))
                return false;
            else
            {
                list<ObjectGuid> targets = AI_VALUE(list<ObjectGuid>, "possible targets");
                list<ObjectGuid> attackers = AI_VALUE(list<ObjectGuid>, "attackers");
                return targets.size() == attackers.size();
            }
        }
    };

    class CastLifeTapAction: public CastSpellAction
    {
    public:
        CastLifeTapAction(PlayerbotAI* ai) : CastSpellAction(ai, "life tap") {}
        virtual string GetTargetName() { return "self target"; }
        virtual bool isUseful() { return AI_VALUE2(uint8, "health", "self target") > sPlayerbotAIConfig.lowHealth; }
    };

}
