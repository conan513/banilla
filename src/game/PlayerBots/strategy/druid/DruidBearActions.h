#pragma once

namespace ai {
	class CastFeralChargeBearAction : public CastReachTargetSpellAction
	{
	public:
		CastFeralChargeBearAction(PlayerbotAI* ai) : CastReachTargetSpellAction(ai, "feral charge - bear", 1.5f) {}
		virtual bool IsInstant() {return true;}
	};

	class CastGrowlAction : public CastSpellAction
	{
	public:
		CastGrowlAction(PlayerbotAI* ai) : CastSpellAction(ai, "growl") {}
		virtual bool IsInstant() {return true;}
	};

	class CastMaulAction : public CastMeleeSpellAction
	{
	public:
		CastMaulAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "maul") {}
		virtual bool isUseful() { return CastMeleeSpellAction::isUseful() && AI_VALUE2(uint8, "rage", "self target") >= 45; }
		virtual bool IsInstant() {return true;}
	};

	class CastBashAction : public CastMeleeSpellAction
	{
	public:
		CastBashAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "bash") {}
		virtual bool IsInstant() {return true;}
	};

	class CastSwipeAction : public CastMeleeSpellAction
	{
	public:
		CastSwipeAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "swipe") {}
		virtual bool IsInstant() {return true;}
	};

	class CastDemoralizingRoarAction : public CastDebuffSpellAction
	{
	public:
		CastDemoralizingRoarAction(PlayerbotAI* ai) : CastDebuffSpellAction(ai, "demoralizing roar") {}
		virtual bool IsInstant() {return true;}
	};

	class CastMangleBearAction : public CastMeleeSpellAction
	{
	public:
		CastMangleBearAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "mangle (bear)") {}
		virtual bool IsInstant() {return true;}
	};

	class CastSwipeBearAction : public CastMeleeSpellAction
	{
	public:
		CastSwipeBearAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "swipe (bear)") {}
		virtual bool IsInstant() {return true;}
	};

    class CastLacerateAction : public CastMeleeSpellAction
    {
    public:
        CastLacerateAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "lacerate") {}
        virtual bool IsInstant() {return true;}
    };

    class CastBashOnEnemyHealerAction : public CastSpellOnEnemyHealerAction
    {
    public:
        CastBashOnEnemyHealerAction(PlayerbotAI* ai) : CastSpellOnEnemyHealerAction(ai, "bash") {}
        virtual bool IsInstant() {return true;}
    };
}
