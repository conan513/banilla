#pragma once

#include "../Action.h"
#include "../../PlayerbotAIConfig.h"

#define BEGIN_SPELL_ACTION(clazz, name) \
class clazz : public CastSpellAction \
        { \
        public: \
        clazz(PlayerbotAI* ai) : CastSpellAction(ai, name) {} \


#define END_SPELL_ACTION() \
    };

#define BEGIN_DEBUFF_ACTION(clazz, name) \
class clazz : public CastDebuffSpellAction \
        { \
        public: \
        clazz(PlayerbotAI* ai) : CastDebuffSpellAction(ai, name) {} \

#define BEGIN_RANGED_SPELL_ACTION(clazz, name) \
class clazz : public CastSpellAction \
        { \
        public: \
        clazz(PlayerbotAI* ai) : CastSpellAction(ai, name) {} \

#define BEGIN_MELEE_SPELL_ACTION(clazz, name) \
class clazz : public CastMeleeSpellAction \
        { \
        public: \
        clazz(PlayerbotAI* ai) : CastMeleeSpellAction(ai, name) {} \


#define END_RANGED_SPELL_ACTION() \
    };


#define BEGIN_BUFF_ON_PARTY_ACTION(clazz, name) \
class clazz : public BuffOnPartyAction \
        { \
        public: \
        clazz(PlayerbotAI* ai) : BuffOnPartyAction(ai, name) {}

namespace ai
{
    class CastSpellAction : public Action
    {
    public:
        CastSpellAction(PlayerbotAI* ai, string spell) : Action(ai, spell),
			range(sPlayerbotAIConfig.spellDistance)
        {
            this->spell = spell;
        }

		virtual string GetTargetName() { return "current target"; };
        virtual bool Execute(Event event);
		virtual bool isPossible();

		virtual bool isUseful();
        virtual ActionThreatType getThreatType() { return ACTION_THREAT_SINGLE; }

		virtual NextAction** getPrerequisites()
		{
			if (spell == "mount")
				return NULL;

			if (range > sPlayerbotAIConfig.spellDistance)
				return NULL;
			else if (range > ATTACK_DISTANCE)
				return NextAction::merge( NextAction::array(0, new NextAction("reach spell", ACTION_MOVE), NULL), Action::getPrerequisites());
			else
				return NextAction::merge( NextAction::array(0, new NextAction("reach melee", ACTION_MOVE), NULL), Action::getPrerequisites());
		}

        virtual NextAction** getAlternatives()
		{
		    Unit* target = GetTarget();
            if (target && (target != bot) && !AI_VALUE2(bool, "target in los", GetTargetName()))
                return NextAction::merge( NextAction::array(0, new NextAction("reposition", ACTION_MOVE), NULL), Action::getAlternatives());
            else return NULL;
		}

    protected:
        string spell;
		float range;
    };

	//---------------------------------------------------------------------------------------------------------------------
	class CastAuraSpellAction : public CastSpellAction
	{
	public:
		CastAuraSpellAction(PlayerbotAI* ai, string spell) : CastSpellAction(ai, spell) {}

		virtual bool isUseful();
	};

    //---------------------------------------------------------------------------------------------------------------------
    class CastMeleeSpellAction : public CastSpellAction
    {
    public:
        CastMeleeSpellAction(PlayerbotAI* ai, string spell) : CastSpellAction(ai, spell) {
			range = ATTACK_DISTANCE;
		}
    };

    //---------------------------------------------------------------------------------------------------------------------
    class CastDebuffSpellAction : public CastSpellAction
    {
    public:
        CastDebuffSpellAction(PlayerbotAI* ai, string spell) : CastSpellAction(ai, spell) {}

        virtual bool isUseful();
    };

     class CastOwnDebuffSpellAction : public CastSpellAction
    {
    public:
        CastOwnDebuffSpellAction(PlayerbotAI* ai, string spell) : CastSpellAction(ai, spell) {}

        virtual bool isUseful();
    };

    class CastDebuffSpellOnAttackerAction : public CastDebuffSpellAction
    {
    public:
        CastDebuffSpellOnAttackerAction(PlayerbotAI* ai, string spell) : CastDebuffSpellAction(ai, spell) {}
        Value<Unit*>* GetTargetValue()
        {
            return context->GetValue<Unit*>("attacker without aura", spell);
        }
        virtual string getName() { return spell + " on attacker"; }
        virtual ActionThreatType getThreatType() { return ACTION_THREAT_AOE; }
    };

    class CastOwnDebuffSpellOnAttackerAction : public CastOwnDebuffSpellAction
    {
    public:
        CastOwnDebuffSpellOnAttackerAction(PlayerbotAI* ai, string spell) : CastOwnDebuffSpellAction(ai, spell) {}
        Value<Unit*>* GetTargetValue()
        {
            return context->GetValue<Unit*>("attacker without own aura", spell);
        }
        virtual string getName() { return spell + " on attacker"; }
        virtual ActionThreatType getThreatType() { return ACTION_THREAT_AOE; }
    };

    class CastHotSpellAction : public CastSpellAction
    {
    public:
        CastHotSpellAction(PlayerbotAI* ai, string spell) : CastSpellAction(ai, spell) {}

        virtual bool isUseful();
    };

	class CastBuffSpellAction : public CastAuraSpellAction
	{
	public:
		CastBuffSpellAction(PlayerbotAI* ai, string spell) : CastAuraSpellAction(ai, spell)
		{
			range = sPlayerbotAIConfig.spellDistance;
		}

        virtual string GetTargetName() { return "self target"; }
	};

	class CastEnchantItemAction : public CastSpellAction
	{
	public:
	    CastEnchantItemAction(PlayerbotAI* ai, string spell) : CastSpellAction(ai, spell)
		{
			range = sPlayerbotAIConfig.spellDistance;
		}

        virtual bool isPossible();
        virtual string GetTargetName() { return "self target"; }
	};

    //---------------------------------------------------------------------------------------------------------------------

    class CastHealingSpellAction : public CastHotSpellAction
    {
    public:
        CastHealingSpellAction(PlayerbotAI* ai, string spell, uint8 estAmount = 15.0f) : CastHotSpellAction(ai, spell)
		{
            this->estAmount = estAmount;
			range = sPlayerbotAIConfig.spellDistance;
        }
		virtual string GetTargetName() { return "self target"; }
        virtual bool isUseful();
        virtual ActionThreatType getThreatType() { return ACTION_THREAT_AOE; }

    protected:
        uint8 estAmount;
    };

    class CastAoeHealSpellAction : public CastHealingSpellAction
    {
    public:
    	CastAoeHealSpellAction(PlayerbotAI* ai, string spell, uint8 estAmount = 15.0f) : CastHealingSpellAction(ai, spell, estAmount) {}
		virtual string GetTargetName() { return "party member to heal"; }
        virtual bool isUseful();
    };

	class CastCureSpellAction : public CastSpellAction
	{
	public:
		CastCureSpellAction(PlayerbotAI* ai, string spell) : CastSpellAction(ai, spell)
		{
			range = sPlayerbotAIConfig.spellDistance;
		}

		virtual string GetTargetName() { return "self target"; }
	};

	class PartyMemberActionNameSupport {
	public:
		PartyMemberActionNameSupport(string spell)
		{
			name = string(spell) + " on party";
		}

		virtual string getName() { return name; }

	private:
		string name;
	};

	class MasterActionNameSupport {
	public:
		MasterActionNameSupport(string spell)
		{
			name = string(spell) + " on master";
		}

		virtual string getName() { return name; }

	private:
		string name;
	};

    class HealPartyMemberAction : public CastHealingSpellAction, public PartyMemberActionNameSupport
    {
    public:
        HealPartyMemberAction(PlayerbotAI* ai, string spell, uint8 estAmount = 15.0f) :
			CastHealingSpellAction(ai, spell, estAmount), PartyMemberActionNameSupport(spell) {}

		virtual string GetTargetName() { return "party member to heal"; }
		virtual string getName() { return PartyMemberActionNameSupport::getName(); }
    };

    class HealMasterAction : public CastHealingSpellAction, public MasterActionNameSupport
    {
    public:
        HealMasterAction(PlayerbotAI* ai, string spell, uint8 estAmount = 15.0f) :
			CastHealingSpellAction(ai, spell, estAmount), MasterActionNameSupport(spell) {}

		virtual string GetTargetName() { return "master target"; }
		virtual string getName() { return MasterActionNameSupport::getName(); }
    };

	class ResurrectPartyMemberAction : public CastSpellAction
	{
	public:
		ResurrectPartyMemberAction(PlayerbotAI* ai, string spell) : CastSpellAction(ai, spell) {}

		virtual string GetTargetName() { return "party member to resurrect"; }
	};
    //---------------------------------------------------------------------------------------------------------------------

    class CurePartyMemberAction : public CastSpellAction, public PartyMemberActionNameSupport
    {
    public:
        CurePartyMemberAction(PlayerbotAI* ai, string spell, uint32 dispelType) :
			CastSpellAction(ai, spell), PartyMemberActionNameSupport(spell)
        {
            this->dispelType = dispelType;
        }

		virtual Value<Unit*>* GetTargetValue();
		virtual string getName() { return PartyMemberActionNameSupport::getName(); }

    protected:
        uint32 dispelType;
    };

    class DispelFrozenPartyMemberAction : public CastSpellAction, public PartyMemberActionNameSupport
    {
    public:
        DispelFrozenPartyMemberAction(PlayerbotAI* ai, string spell) :
			CastSpellAction(ai, spell), PartyMemberActionNameSupport(spell)
        { }

		virtual Value<Unit*>* GetTargetValue();
		virtual string getName() { return PartyMemberActionNameSupport::getName(); }
    };

    class DispelRootPartyMemberAction : public CastSpellAction, public PartyMemberActionNameSupport
    {
    public:
        DispelRootPartyMemberAction(PlayerbotAI* ai, string spell) :
			CastSpellAction(ai, spell), PartyMemberActionNameSupport(spell)
        { }

		virtual Value<Unit*>* GetTargetValue();
		virtual string getName() { return PartyMemberActionNameSupport::getName(); }
    };

    class DispelSnarePartyMemberAction : public CastSpellAction, public PartyMemberActionNameSupport
    {
    public:
        DispelSnarePartyMemberAction(PlayerbotAI* ai, string spell) :
			CastSpellAction(ai, spell), PartyMemberActionNameSupport(spell)
        { }

		virtual Value<Unit*>* GetTargetValue();
		virtual string getName() { return PartyMemberActionNameSupport::getName(); }
    };

    class DispelCharmPartyMemberAction : public CastSpellAction, public PartyMemberActionNameSupport
    {
    public:
        DispelCharmPartyMemberAction(PlayerbotAI* ai, string spell) :
			CastSpellAction(ai, spell), PartyMemberActionNameSupport(spell)
        { }

		virtual Value<Unit*>* GetTargetValue();
		virtual string getName() { return PartyMemberActionNameSupport::getName(); }
    };

    class DispelPolymorphPartyMemberAction : public CastSpellAction, public PartyMemberActionNameSupport
    {
    public:
        DispelPolymorphPartyMemberAction(PlayerbotAI* ai, string spell) :
			CastSpellAction(ai, spell), PartyMemberActionNameSupport(spell)
        { }

		virtual Value<Unit*>* GetTargetValue();
		virtual string getName() { return PartyMemberActionNameSupport::getName(); }
    };

    class DispelPossessPartyMemberAction : public CastSpellAction, public PartyMemberActionNameSupport
    {
    public:
        DispelPossessPartyMemberAction(PlayerbotAI* ai, string spell) :
			CastSpellAction(ai, spell), PartyMemberActionNameSupport(spell)
        { }

		virtual Value<Unit*>* GetTargetValue();
		virtual string getName() { return PartyMemberActionNameSupport::getName(); }
    };

    class DispelFearPartyMemberAction : public CastSpellAction, public PartyMemberActionNameSupport
    {
    public:
        DispelFearPartyMemberAction(PlayerbotAI* ai, string spell) :
			CastSpellAction(ai, spell), PartyMemberActionNameSupport(spell)
        { }

		virtual Value<Unit*>* GetTargetValue();
		virtual string getName() { return PartyMemberActionNameSupport::getName(); }
    };
    //---------------------------------------------------------------------------------------------------------------------

    class BuffOnPartyAction : public CastBuffSpellAction, public PartyMemberActionNameSupport
    {
    public:
        BuffOnPartyAction(PlayerbotAI* ai, string spell) :
			CastBuffSpellAction(ai, spell), PartyMemberActionNameSupport(spell) {}
    public:
		virtual Value<Unit*>* GetTargetValue();
		virtual string getName() { return PartyMemberActionNameSupport::getName(); }
    };

    class BuffOnMasterAction : public CastBuffSpellAction, public MasterActionNameSupport
    {
    public:
        BuffOnMasterAction(PlayerbotAI* ai, string spell) :
			CastBuffSpellAction(ai, spell), MasterActionNameSupport(spell) {}
    public:
		virtual Value<Unit*>* GetTargetValue() {return context->GetValue<Unit*>("master target");};
		virtual string getName() { return MasterActionNameSupport::getName(); }
    };

    //---------------------------------------------------------------------------------------------------------------------

    class CastShootAction : public CastSpellAction
    {
    public:
        CastShootAction(PlayerbotAI* ai) : CastSpellAction(ai, "shoot") {}
        virtual ActionThreatType getThreatType() { return ACTION_THREAT_NONE; }
        virtual bool hasMultipliers() {return false;}
        virtual bool isUseful() {return AI_VALUE2(uint8, "mana", "self target") < sPlayerbotAIConfig.lowMana/2 || ai->IsHeal(bot) || ai->IsTank(bot) || bot->getClass() == CLASS_HUNTER;}

        virtual NextAction** getAlternatives()
        {

            if (bot->getClass() == CLASS_WARRIOR || bot->getClass() == CLASS_ROGUE)
                return NextAction::merge( NextAction::array(0, new NextAction("throw"), NULL), CastSpellAction::getAlternatives());
            else
                return NextAction::merge( NextAction::array(0, new NextAction("reposition"), NULL), CastSpellAction::getAlternatives());
        }
    };

    class CastThrowAction : public CastSpellAction
    {
    public:
        CastThrowAction(PlayerbotAI* ai) : CastSpellAction(ai, "throw") {}
        virtual ActionThreatType getThreatType() { return ACTION_THREAT_NONE; }
        virtual bool hasMultipliers() {return false;}

        virtual NextAction** getAlternatives()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("reposition"), NULL), CastSpellAction::getAlternatives());
        }
    };

	class CastLifeBloodAction : public CastHealingSpellAction
	{
	public:
		CastLifeBloodAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "lifeblood") {}
		virtual bool hasMultipliers() {return false;}
	};

	class CastGiftOfTheNaaruAction : public CastHealingSpellAction
	{
	public:
		CastGiftOfTheNaaruAction(PlayerbotAI* ai) : CastHealingSpellAction(ai, "gift of the naaru") {}
		virtual bool hasMultipliers() {return false;}
	};

	class CastGiftOfTheNaaruOnPartyAction : public HealPartyMemberAction
	{
	public:
		CastGiftOfTheNaaruOnPartyAction(PlayerbotAI* ai) : HealPartyMemberAction(ai, "gift of the naaru") {}

		virtual string getName() { return "gift of the naaru on party"; }
	};

    class CastArcaneTorrentAction : public CastBuffSpellAction
    {
    public:
        CastArcaneTorrentAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "arcane torrent") {}
        virtual bool hasMultipliers() {return false;}
    };

    class CastBerserkingAction : public CastBuffSpellAction
    {
    public:
        CastBerserkingAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "berserking") {}
        virtual bool hasMultipliers() {return false;}
        virtual NextAction** getAlternatives()
        {
            return NextAction::merge( NextAction::array(0, new NextAction("blood fury"), NULL), CastBuffSpellAction::getAlternatives());
        }
    };

    class CastBloodFuryAction : public CastBuffSpellAction
    {
    public:
        CastBloodFuryAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "blood fury") {}
        virtual bool hasMultipliers() {return false;}
    };

    class CastWillOfTheForsakenAction : public CastBuffSpellAction
    {
    public:
        CastWillOfTheForsakenAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "will of the forsaken") {}
    };

    class CastEveryManForHimselfAction : public CastBuffSpellAction
    {
    public:
        CastEveryManForHimselfAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "every man for himself") {}
    };

    class CastCannibalizeAction : public CastSpellAction
    {
    public:
        CastCannibalizeAction(PlayerbotAI* ai) : CastSpellAction(ai, "cannibalize") {}
    };

    class CastWarStompAction : public CastSpellAction
    {
    public:
        CastWarStompAction(PlayerbotAI* ai) : CastSpellAction(ai, "war stomp") {}

        virtual bool isUseful() {
        return (AI_VALUE2(float, "distance", GetTargetName()) <= sPlayerbotAIConfig.tooCloseDistance) || (AI_VALUE(uint8, "melee attacker count") > 2);
        }
    };

    class CastStoneformAction : public CastSpellAction
    {
    public:
        CastStoneformAction(PlayerbotAI* ai) : CastSpellAction(ai, "stoneform") {}
        virtual bool hasMultipliers() {return false;}
    };

    class CastShadowmeltAction : public CastSpellAction
    {
    public:
        CastShadowmeltAction(PlayerbotAI* ai) : CastSpellAction(ai, "shadowmelt") {}
        virtual bool hasMultipliers() {return false;}
    };

    class CastEscapeArtistAction : public CastSpellAction
    {
    public:
        CastEscapeArtistAction(PlayerbotAI* ai) : CastSpellAction(ai, "escape artist") {}
        virtual bool hasMultipliers() {return false;}
        virtual bool isUseful() { return AI_VALUE2(bool, "rooted", GetTargetName()); };
    };

    class CastSpellOnEnemyHealerAction : public CastSpellAction
    {
    public:
        CastSpellOnEnemyHealerAction(PlayerbotAI* ai, string spell) : CastSpellAction(ai, spell) {}
        Value<Unit*>* GetTargetValue()
        {
            return context->GetValue<Unit*>("enemy healer target", spell);
        }
        virtual string getName() { return spell + " on enemy healer"; }
    };
}
