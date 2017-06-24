#pragma once

namespace ai {

    class CastCatComboAction : public CastMeleeSpellAction
	{
	public:
	    CastCatComboAction(PlayerbotAI* ai, string name) : CastMeleeSpellAction(ai, name) {}

	    virtual bool isUseful()
	    {
	        return CastMeleeSpellAction::isUseful() && !ai->HasAura("prowl", bot) && AI_VALUE2(uint8, "combo", "current target") <= 5;
	    }
	    virtual bool IsInstant() {return true;}
	};

	class CastFeralChargeCatAction : public CastReachTargetSpellAction
	{
	public:
		CastFeralChargeCatAction(PlayerbotAI* ai) : CastReachTargetSpellAction(ai, "feral charge - cat", 3.0f) {}
		virtual bool IsInstant() {return true;}

		//virtual bool isUseful()
	    //{
	    //    return CastReachTargetSpellAction::isUseful() && AI_VALUE2(bool, "combat", "self target");
	    //}
	};

	class CastCowerAction : public CastBuffSpellAction
	{
	public:
		CastCowerAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "cower") {}
		virtual bool IsInstant() {return true;}
	};

	class CastDashAction : public CastBuffSpellAction
	{
	public:
		CastDashAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "dash") {}
		virtual bool IsInstant() {return true;}
	};

    class CastProwlAction : public CastBuffSpellAction
	{
	public:
		CastProwlAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "prowl") {}
		virtual bool IsInstant() {return true;}
	};

	class CastSavageRoarAction : public CastBuffSpellAction
	{
	public:
		CastSavageRoarAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "savage roar") {}
		virtual bool IsInstant() {return true;}
	};

	class CastTigersFuryAction : public CastBuffSpellAction
	{
	public:
		CastTigersFuryAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "tiger's fury") {}
		virtual bool IsInstant() {return true;}
	};

	class CastRakeAction : public CastDebuffSpellAction
	{
	public:
		CastRakeAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "rake") {}
		virtual bool IsInstant() {return true;}

        virtual NextAction** getPrerequisites()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("move behind"), NULL), CastDebuffSpellAction::getPrerequisites());
        }

        virtual bool isUseful()
	    {
	        return CastDebuffSpellAction::isUseful() && !ai->HasAura("prowl", bot);
	    }
	};

    class CastRipAction : public CastDebuffSpellAction {
	public:
		CastRipAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "rip") {}
		virtual bool IsInstant() {return true;}
		virtual bool isUseful()
	    {
	        return  CastDebuffSpellAction::isUseful() && AI_VALUE2(uint8, "combo", "current target") >= 3;
	    }
	};

    class CastShredAction : public CastCatComboAction {
	public:
		CastShredAction(PlayerbotAI* ai) : CastCatComboAction(ai, "shred") {}
		//virtual bool isUseful()
	    //{
        //    return CastCatComboAction::isUseful() && AI_VALUE2(bool, "behind", "current target");
	    //}
	};

	class CastClawAction : public  CastCatComboAction {
	public:
		CastClawAction(PlayerbotAI* ai) : CastCatComboAction(ai, "claw") {}
	};

	class CastMangleCatAction : public  CastCatComboAction {
	public:
		CastMangleCatAction(PlayerbotAI* ai) : CastCatComboAction(ai, "mangle (cat)") {}
	};

	class CastSwipeCatAction : public  CastCatComboAction {
	public:
		CastSwipeCatAction(PlayerbotAI* ai) : CastCatComboAction(ai, "swipe (cat)") {}
	};

	class CastFerociousBiteAction : public CastMeleeSpellAction {
	public:
		CastFerociousBiteAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "ferocious bite") {}

        virtual bool IsInstant() {return true;}
		virtual bool isUseful()
	    {
	         return AI_VALUE2(uint8, "combo", "current target") > 4 || AI_VALUE2(uint8, "health", "current target") < sPlayerbotAIConfig.almostDead;
	    }
	};

	class CastPounceAction : public CastMeleeSpellAction {
	public:
		CastPounceAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "pounce") {}

        virtual bool IsInstant() {return true;}
		virtual bool isUseful() {
            return CastMeleeSpellAction::isUseful() && ai->HasAura("prowl", bot);
        }

        virtual NextAction** getPrerequisites()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("prowl"), NULL), CastMeleeSpellAction::getPrerequisites());
        }
	};

	class CastRavageAction : public CastMeleeSpellAction {
	public:
		CastRavageAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "ravage") {}

		virtual bool IsInstant() {return true;}

		virtual bool isUseful() {
                return CastMeleeSpellAction::isUseful() && ai->HasAura("prowl", bot) && ((AI_VALUE(uint8, "balance") < 100) || AI_VALUE2(bool, "stunned", "current target"));
        }

        virtual NextAction** getPrerequisites()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("prowl"), NULL), CastMeleeSpellAction::getPrerequisites());
        }

	};

	//Predator's swiftness aura
	class CastInstantRegrowthOnMasterAction : public HealMasterAction
    {
    public:
        CastInstantRegrowthOnMasterAction(PlayerbotAI* ai) : HealMasterAction(ai, "regrowth",10) {}

		bool isUseful() { return HealMasterAction::isUseful() && ai->HasAura("predator's swiftness", bot) && AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig.lowMana && (AI_VALUE2(uint8, "aoe heal", "almost full") != 0); }
        virtual bool IsInstant() {return true;}
    };

    class CastInstantHealingTouchOnMasterAction : public HealMasterAction
    {
    public:
        CastInstantHealingTouchOnMasterAction(PlayerbotAI* ai) : HealMasterAction(ai, "healing touch",10) {}

		bool isUseful() { return HealMasterAction::isUseful() && ai->HasAura("predator's swiftness", bot) && AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig.lowMana && (AI_VALUE2(uint8, "aoe heal", "almost full") != 0); }
        virtual bool IsInstant() {return true;}
    };

    class CastInstantRegrowthAction : public CastHealingSpellAction {
	public:
		CastInstantRegrowthAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "regrowth",5) {}

		virtual bool isUseful() { return CastHealingSpellAction::isUseful() && ai->HasAura("predator's swiftness", bot) && AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig.lowMana; }
		virtual bool IsInstant() {return true;}
	};

	class CastInstantRegrowthOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastInstantRegrowthOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "regrowth",5) {}

		virtual bool isUseful() { return HealPartyMemberAction::isUseful() && ai->HasAura("predator's swiftness", bot) && AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig.lowMana && (AI_VALUE2(uint8, "aoe heal", "almost full") != 0); }
        virtual bool IsInstant() {return true;}
    };

    class CastInstantHealingTouchAction : public CastHealingSpellAction {
    public:
        CastInstantHealingTouchAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "healing touch",10) {}

		virtual bool isUseful() { return CastHealingSpellAction::isUseful() && ai->HasAura("predator's swiftness", bot) && AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig.lowMana; }
        virtual bool IsInstant() {return true;}
    };

    class CastInstantHealingTouchOnPartyAction : public HealPartyMemberAction
    {
    public:
        CastInstantHealingTouchOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "healing touch",10) {}

		virtual bool isUseful() { return HealPartyMemberAction::isUseful() && ai->HasAura("predator's swiftness", bot) && AI_VALUE2(uint8, "mana", "self target") > sPlayerbotAIConfig.lowMana && (AI_VALUE2(uint8, "aoe heal", "almost full") != 0); }
        virtual bool IsInstant() {return true;}
    };

}
