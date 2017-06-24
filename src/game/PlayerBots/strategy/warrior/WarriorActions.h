#pragma once
#include "../actions/GenericActions.h"

namespace ai
{
    // battle
    class CastBattleMeleeSpellAction : public CastMeleeSpellAction {
    public:
        CastBattleMeleeSpellAction(PlayerbotAI* ai, string spell) : CastMeleeSpellAction(ai, spell) {}
        virtual bool IsInstant() {return true;}
        virtual NextAction** getPrerequisites() {
            return NextAction::merge( NextAction::array(0, new NextAction("battle stance"), NULL), CastMeleeSpellAction::getPrerequisites());
        }
    };

    //berserker
    class CastBerserkerMeleeSpellAction : public CastMeleeSpellAction {
    public:
        CastBerserkerMeleeSpellAction(PlayerbotAI* ai, string spell) : CastMeleeSpellAction(ai, spell) {}
        virtual bool IsInstant() {return true;}
        virtual NextAction** getPrerequisites() {
            return NextAction::merge( NextAction::array(0, new NextAction("berserker stance"), NULL), CastMeleeSpellAction::getPrerequisites());
        }
    };

    // defensive
    class CastDefensiveMeleeSpellAction : public CastMeleeSpellAction {
    public:
        CastDefensiveMeleeSpellAction(PlayerbotAI* ai, string spell) : CastMeleeSpellAction(ai, spell) {}
        virtual bool IsInstant() {return true;}
        virtual NextAction** getPrerequisites() {
            return NextAction::merge( NextAction::array(0, new NextAction("defensive stance"), NULL), CastMeleeSpellAction::getPrerequisites());
        }
    };

    // all
    class CastHeroicStrikeAction : public CastMeleeSpellAction {
    public:
        CastHeroicStrikeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "heroic strike") {}
        virtual bool IsInstant() {return true;}
        virtual bool isUseful() { return CastMeleeSpellAction::isUseful() && AI_VALUE(uint8, "melee attacker count") <= 1 && AI_VALUE2(uint8, "rage", "self target") > 30; }
    };

    // all
    class CastCleaveAction : public CastMeleeSpellAction {
    public:
        CastCleaveAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "cleave") {}

        virtual bool IsInstant() {return true;}
        virtual bool isUseful() { return CastMeleeSpellAction::isUseful() && AI_VALUE(uint8, "melee attacker count") > 1 && AI_VALUE2(uint8, "rage", "self target") > 30; }
    };

    // battle, berserker
    class CastMockingBlowAction : public CastMeleeSpellAction {
    public:
        CastMockingBlowAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "mocking blow") {}
        virtual bool IsInstant() {return true;}
    };

    class CastBloodthirstAction : public CastMeleeSpellAction {
    public:
        CastBloodthirstAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "bloodthirst") {}
        virtual bool IsInstant() {return true;}

        virtual NextAction** getAlternatives();
    };

    // battle, berserker
    class CastExecuteAction : public CastMeleeSpellAction {
    public:
        CastExecuteAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "execute") {}

        virtual bool isUseful()
	    {
	        return CastMeleeSpellAction::isUseful() && AI_VALUE2(uint8, "health", "current target") < 20;
	    }
	    virtual bool IsInstant() {return true;}
    };

    // battle
    class CastOverpowerAction : public CastBattleMeleeSpellAction {
    public:
        CastOverpowerAction(PlayerbotAI* ai) : CastBattleMeleeSpellAction(ai, "overpower") {}
        virtual bool IsInstant() {return true;}
    };

    // battle, berserker
    class CastHamstringAction : public CastMeleeSpellAction {
    public:
        CastHamstringAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "hamstring") {}

        virtual bool isUseful()
        {
           // return CastMeleeSpellAction::isUseful() && !ai->HasAura("wing clip"), GetTarget());
           return CastMeleeSpellAction::isUseful() && !ai->HasAnyAuraOf(GetTarget(), "slow", "wing clip", "frost shock", "crippling poison", "hamstring", NULL)
           && (AI_VALUE2(bool, "target player", "current target")||AI_VALUE2(bool, "fleeing", "current target"));
        }
        virtual bool IsInstant() {return true;}
    };
    // battle, berserker
    class CastMortalStrikeAction : public CastMeleeSpellAction {
    public:
        CastMortalStrikeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "mortal strike") {}

        virtual bool IsInstant() {return true;}
        virtual NextAction** getAlternatives();
    };
    // berserker
    class CastWhirlwindAction : public CastBerserkerMeleeSpellAction {
    public:
        CastWhirlwindAction(PlayerbotAI* ai) : CastBerserkerMeleeSpellAction(ai, "whirlwind") {}
        virtual bool IsInstant() {return true;}
    };
    // Intercept
    class CastInterceptAction : public CastBerserkerMeleeSpellAction {
    public:
        CastInterceptAction(PlayerbotAI* ai) :CastBerserkerMeleeSpellAction(ai, "intercept") {}
        virtual bool IsInstant() {return true;}
    };

    // battle, berserker
    class CastBladestormAction : public CastMeleeSpellAction {
    public:
        CastBladestormAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "bladestorm") {}
        virtual bool IsInstant() {return true;}
    };

    // defensive
    class CastTauntAction : public CastSpellAction {
    public:
        CastTauntAction(PlayerbotAI* ai) : CastSpellAction(ai, "taunt") {}
        virtual bool IsInstant() {return true;}
        virtual NextAction** getPrerequisites() {
            return NextAction::merge( NextAction::array(0, new NextAction("defensive stance"), NULL), CastSpellAction::getPrerequisites());
        }
    };

    // defensive
    class CastShieldBlockAction : public CastBuffSpellAction {
    public:
        CastShieldBlockAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "shield block") {}
        virtual bool IsInstant() {return true;}
		virtual NextAction** getPrerequisites() {
			return NextAction::merge( NextAction::array(0, new NextAction("defensive stance"), NULL), CastSpellAction::getPrerequisites());
		}
    };

    // defensive
    class CastShieldWallAction : public CastDefensiveMeleeSpellAction {
    public:
        CastShieldWallAction(PlayerbotAI* ai) : CastDefensiveMeleeSpellAction(ai, "shield wall") {}
        virtual bool IsInstant() {return true;}
    };

    class CastBloodrageAction : public CastBuffSpellAction {
    public:
        CastBloodrageAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "bloodrage") {}
        virtual bool IsInstant() {return true;}
    };

    class CastRecklessnessAction : public CastBuffSpellAction {
    public:
        CastRecklessnessAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "recklessness") {}
        virtual bool IsInstant() {return true;}
    };

    class CastRetaliationAction : public CastBuffSpellAction {
    public:
        CastRetaliationAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "retaliation") {}
        virtual bool IsInstant() {return true;}
    };


    // defensive
    class CastDevastateAction : public CastDefensiveMeleeSpellAction {
    public:
        CastDevastateAction(PlayerbotAI* ai) : CastDefensiveMeleeSpellAction(ai, "devastate") {}
        virtual bool IsInstant() {return true;}
    };

    class CastSpellReflectAction : public CastDefensiveMeleeSpellAction {
    public:
        CastSpellReflectAction(PlayerbotAI* ai) : CastDefensiveMeleeSpellAction(ai, "spell reflect") {}
        virtual bool IsInstant() {return true;}
    };

    // all
    class CastSlamAction : public CastMeleeSpellAction {
    public:
        CastSlamAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "slam") {}
    };

	// all
	class CastShieldSlamAction : public CastMeleeSpellAction {
	public:
		CastShieldSlamAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "shield slam") {}
		virtual bool IsInstant() {return true;}
	};

    // after dodge
    BEGIN_MELEE_SPELL_ACTION(CastRevengeAction, "revenge")
        virtual NextAction** getPrerequisites();
        virtual bool IsInstant() {return true;}
    END_SPELL_ACTION()


    //debuffs
    BEGIN_DEBUFF_ACTION(CastRendAction, "rend")
        virtual bool IsInstant() {return true;}
    END_SPELL_ACTION()

    class CastRendOnAttackerAction : public CastDebuffSpellOnAttackerAction
    {
    public:
        CastRendOnAttackerAction(PlayerbotAI* ai) : CastDebuffSpellOnAttackerAction(ai, "rend") {}
        virtual bool IsInstant() {return true;}
    };

    BEGIN_DEBUFF_ACTION(CastDisarmAction, "disarm")
        virtual NextAction** getPrerequisites();
        virtual bool IsInstant() {return true;}
    END_SPELL_ACTION()

    BEGIN_DEBUFF_ACTION(CastSunderArmorAction, "sunder armor") // 5 times
        virtual NextAction** getPrerequisites();
        virtual bool IsInstant() {return true;}
    END_SPELL_ACTION()

    class CastDemoralizingShoutAction : public CastDebuffSpellAction {
    public:
        CastDemoralizingShoutAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "demoralizing shout") {}
        virtual bool IsInstant() {return true;}
    };

    BEGIN_MELEE_SPELL_ACTION(CastChallengingShoutAction, "challenging shout")
    virtual bool IsInstant() {return true;}
    END_SPELL_ACTION()

    // stuns
    BEGIN_MELEE_SPELL_ACTION(CastShieldBashAction, "shield bash")
    virtual bool IsInstant() {return true;}
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastIntimidatingShoutAction, "intimidating shout")
    virtual bool IsInstant() {return true;}
    END_SPELL_ACTION()

    BEGIN_MELEE_SPELL_ACTION(CastThunderClapAction, "thunder clap")
    virtual bool IsInstant() {return true;}
    END_SPELL_ACTION()

    // buffs
	class CastBattleShoutAction : public CastBuffSpellAction {
	public:
		CastBattleShoutAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "battle shout") {}

        virtual NextAction** getAlternatives();
        virtual bool IsInstant() {return true;}
        virtual bool isUseful()
	    {
	        return !ai->HasAura("blessing of might", AI_VALUE(Unit*, "self target"));
	    }
	};

	class CastCommandingShoutAction : public CastBuffSpellAction {
	public:
		CastCommandingShoutAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "commanding shout") {}

        virtual NextAction** getAlternatives();
        virtual bool IsInstant() {return true;}
        virtual bool isUseful()
	    {
	        return !ai->HasAura("blood pact", AI_VALUE(Unit*, "self target"));
	    }
	};

    class CastSweepingStrikesAction : public CastBuffSpellAction {
	public:
		CastSweepingStrikesAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "sweeping strikes") {}
		virtual bool IsInstant() {return true;}
	};

	class CastDefensiveStanceAction : public CastBuffSpellAction {
	public:
		CastDefensiveStanceAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "defensive stance") {}
		virtual bool IsInstant() {return true;}
	};

	class CastBattleStanceAction : public CastBuffSpellAction {
	public:
		CastBattleStanceAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "battle stance") {}
		virtual bool IsInstant() {return true;}
	};

	class CastBerserkerStanceAction : public CastBuffSpellAction {
	public:
		CastBerserkerStanceAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "berserker stance") {}
		virtual bool IsInstant() {return true;}
	};

    BEGIN_RANGED_SPELL_ACTION(CastChargeAction, "charge")
    virtual bool IsInstant() {return true;}
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastShatteringThrowAction, "shattering throw")
    END_SPELL_ACTION()

    BEGIN_RANGED_SPELL_ACTION(CastHeroicThrowAction, "heroic throw")
    END_SPELL_ACTION()

	class CastDeathWishAction : public CastBuffSpellAction {
	public:
		CastDeathWishAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "death wish") {}
		virtual bool IsInstant() {return true;}
	};

	class CastBerserkerRageAction : public CastBuffSpellAction {
	public:
		CastBerserkerRageAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "berserker rage") {}
		virtual bool IsInstant() {return true;}
	};

	class CastHeroicFuryAction : public CastBuffSpellAction {
	public:
		CastHeroicFuryAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "heroic fury") {}
		virtual bool IsInstant() {return true;}
	};

	class CastLastStandAction : public CastBuffSpellAction {
	public:
		CastLastStandAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "last stand") {}
		virtual bool IsInstant() {return true;}
	};

	// defensive
	class CastShockwaveAction : public CastDefensiveMeleeSpellAction {
	public:
		CastShockwaveAction(PlayerbotAI* ai) : CastDefensiveMeleeSpellAction(ai, "shockwave") {}
		virtual bool IsInstant() {return true;}
	};

	// defensive
	class CastConcussionBlowAction : public CastDefensiveMeleeSpellAction {
	public:
		CastConcussionBlowAction(PlayerbotAI* ai) : CastDefensiveMeleeSpellAction(ai, "concussion blow") {}
		virtual bool IsInstant() {return true;}
	};

	BEGIN_MELEE_SPELL_ACTION(CastVictoryRushAction, "victory rush")
	virtual bool IsInstant() {return true;}
	END_SPELL_ACTION()

    class CastShieldBashOnEnemyHealerAction : public CastSpellOnEnemyHealerAction
    {
    public:
        CastShieldBashOnEnemyHealerAction(PlayerbotAI* ai) : CastSpellOnEnemyHealerAction(ai, "shield bash") {}
        virtual bool IsInstant() {return true;}
    };

    class CastInterveneOnPartyAction : public BuffOnPartyAction {
	public:
		CastInterveneOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "intervene") {}
		virtual bool IsInstant() {return true;}
	};

    class CastVigilanceOnMasterAction : public BuffOnPartyAction
    {
    public:
        CastVigilanceOnMasterAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "vigilance") {}
        virtual string getName() { return "vigilance on master";}
        virtual string GetTargetName() { return "master target";}
        virtual bool IsInstant() {return true;}
    };

	class CastVigilanceOnPartyAction : public BuffOnPartyAction {
	public:
		CastVigilanceOnPartyAction(PlayerbotAI* ai) : BuffOnPartyAction(ai, "vigilance") {}
		virtual bool IsInstant() {return true;}
	};
}
