#pragma once

namespace ai {
	class CastBearFormAction : public CastBuffSpellAction {
	public:
		CastBearFormAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "bear form") {}

        virtual bool isPossible() {
			return CastBuffSpellAction::isPossible() && !ai->HasAura("dire bear form", GetTarget());
		}
        virtual bool isUseful() {
			return CastBuffSpellAction::isUseful() && !ai->HasAura("dire bear form", GetTarget());
		}

        virtual bool hasMultipliers() {return false;}
		virtual bool Execute(Event event);
	};

	class CastDireBearFormAction : public CastBuffSpellAction {
	public:
		CastDireBearFormAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "dire bear form") {}

        virtual NextAction** getAlternatives() {
			return NextAction::merge(NextAction::array(0, new NextAction("bear form"), NULL), CastSpellAction::getAlternatives());
		}

		virtual bool Execute(Event event);
		virtual bool hasMultipliers() {return false;}
	};

	class CastCatFormAction : public CastBuffSpellAction {
	public:
		CastCatFormAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "cat form") {}
		virtual bool hasMultipliers() {return false;}

		virtual bool Execute(Event event);
	};

	class CastTreeFormAction : public CastBuffSpellAction {
	public:
		CastTreeFormAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "tree of life") {}
		virtual bool hasMultipliers() {return false;}

		virtual bool Execute(Event event);
	};

	class CastMoonkinFormAction : public CastBuffSpellAction {
	public:
		CastMoonkinFormAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "moonkin form") {}

		virtual bool Execute(Event event);
	};

	class CastCasterFormAction : public CastBuffSpellAction {
	public:
		CastCasterFormAction(PlayerbotAI* ai) : CastBuffSpellAction(ai, "caster form") {}

		virtual bool isUseful() {
			return ai->HasAnyAuraOf(GetTarget(), "dire bear form", "bear form", "cat form", "travel form", "aquatic form",
				"flight form", "swift flight form", "moonkin form", "tree of life", NULL);
		}
		virtual bool isPossible() { return true; }
		virtual bool hasMultipliers() {return false;}

		virtual bool Execute(Event event);
	};

}
