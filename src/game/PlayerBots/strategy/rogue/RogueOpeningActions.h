#pragma once

namespace ai
{
    class CastSapAction : public CastMeleeSpellAction
	{
	public:
		CastSapAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "sap") {}

		virtual bool isUseful() {
            return CastMeleeSpellAction::isUseful() && !AI_VALUE2(bool, "combat", "current target") && ai->HasAura("stealth", AI_VALUE(Unit*, "self target"));
        }

        virtual bool IsInstant() {return true;}
        virtual NextAction** getPrerequisites()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("move behind"), NULL), CastMeleeSpellAction::getPrerequisites());
        }
	};

	class CastSapCcAction : public CastMeleeSpellAction
    {
    public:
        CastSapCcAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "sap on cc") {}

        virtual bool isUseful() {
            return CastMeleeSpellAction::isUseful() && !AI_VALUE2(bool, "combat", "current target") && ai->HasAura("stealth", AI_VALUE(Unit*, "self target"));
        }

        virtual bool IsInstant() {return true;}

        virtual Value<Unit*>* GetTargetValue()
        {
            return context->GetValue<Unit*>("cc target4", "sap");
        }

        virtual bool Execute(Event event)
        {
            return ai->CastSpell("sap", GetTarget());
        }

        virtual NextAction** getPrerequisites()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("move behind"), NULL), CastMeleeSpellAction::getPrerequisites());
        }

        virtual NextAction** getAlternatives();
    };


	class CastGarroteAction : public CastMeleeSpellAction
	{
	public:
		CastGarroteAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "garrote") {}

        virtual bool isUseful() {
            return CastMeleeSpellAction::isUseful() && ai->HasAura("stealth", bot)&& (!AI_VALUE2(bool, "target normal", "current target"));
        }
//
        virtual bool IsInstant() {return true;}

        virtual NextAction** getAlternatives()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("ambush"), NULL), CastMeleeSpellAction::getAlternatives());
        }

        virtual NextAction** getPrerequisites()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("move behind"), NULL), CastMeleeSpellAction::getPrerequisites());
        }
	};

	class CastGarroteAction2 : public CastMeleeSpellAction
	{
	public:
		CastGarroteAction2(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "garrote") {}

        virtual bool isUseful() {
            return CastMeleeSpellAction::isUseful() && ai->HasAura("stealth", bot);
        }

        virtual bool Execute(Event event)
        {
            return ai->CastSpell("garrote", GetTarget());
        }

        virtual NextAction** getPrerequisites()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("move behind"), NULL), CastMeleeSpellAction::getPrerequisites());
        }

        virtual bool IsInstant() {return true;}

	};


    class CastAmbushAction : public CastMeleeSpellAction
	{
	public:
		CastAmbushAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "ambush") {}

        virtual bool IsInstant() {return true;}
        virtual bool isUseful() {

            // return CastMeleeSpellAction::isUseful() && ai->HasAura("stealth", bot) && (ai->HasAura("garrote", GetTarget()) || AI_VALUE2(bool, "target normal", "current target"));
            return CastMeleeSpellAction::isUseful() && ai->HasAura("stealth", bot); //&& AI_VALUE2(bool, "behind", "current target")
        }
// && AI_VALUE2(bool, "behind", "current target")
    virtual NextAction** getPrerequisites()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("move behind"), NULL), CastMeleeSpellAction::getPrerequisites());
        }

	virtual NextAction** getAlternatives()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("cheap shot"), NULL), CastMeleeSpellAction::getAlternatives());
        }

	};

	class CastCheapShotAction : public CastMeleeSpellAction
	{
	public:
		CastCheapShotAction(PlayerbotAI* ai) : CastMeleeSpellAction(ai, "cheap shot") {}

        virtual bool IsInstant() {return true;}
        virtual bool isUseful() {
            return CastMeleeSpellAction::isUseful() && (!AI_VALUE2(bool, "stunned", "current target")) && ai->HasAura("stealth", bot);
        }

        virtual NextAction** getAlternatives()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("garrote sword"), NULL), CastMeleeSpellAction::getAlternatives());
        }

        virtual NextAction** getPrerequisites()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("move behind"), NULL), CastMeleeSpellAction::getPrerequisites());
        }
    };
}
