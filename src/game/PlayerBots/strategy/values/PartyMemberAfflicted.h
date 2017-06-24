#pragma once
#include "../Value.h"
#include "PartyMemberValue.h"

namespace ai
{
    class PartyMemberFeared : public PartyMemberValue, Qualified
	{
	public:
        PartyMemberFeared(PlayerbotAI* ai) :
          PartyMemberValue(ai) {}

    protected:
        virtual Unit* Calculate();
	};

    class PartyMemberCharmed : public PartyMemberValue, Qualified
	{
	public:
        PartyMemberCharmed(PlayerbotAI* ai) :
          PartyMemberValue(ai) {}

    protected:
        virtual Unit* Calculate();
	};

	class PartyMemberPossessed : public PartyMemberValue, Qualified
	{
	public:
        PartyMemberPossessed(PlayerbotAI* ai) :
          PartyMemberValue(ai) {}

    protected:
        virtual Unit* Calculate();
	};

	class PartyMemberPolymorphed : public PartyMemberValue, Qualified
	{
	public:
        PartyMemberPolymorphed(PlayerbotAI* ai) :
          PartyMemberValue(ai) {}

    protected:
        virtual Unit* Calculate();
	};

	class PartyMemberSnared : public PartyMemberValue, Qualified
	{
	public:
        PartyMemberSnared(PlayerbotAI* ai) :
          PartyMemberValue(ai) {}

    protected:
        virtual Unit* Calculate();
	};

	class PartyMemberRooted : public PartyMemberValue, Qualified
	{
	public:
        PartyMemberRooted(PlayerbotAI* ai) :
          PartyMemberValue(ai) {}

    protected:
        virtual Unit* Calculate();
	};

	class PartyMemberFrozen : public PartyMemberValue, Qualified
	{
	public:
        PartyMemberFrozen(PlayerbotAI* ai) :
          PartyMemberValue(ai) {}

    protected:
        virtual Unit* Calculate();
	};
}
