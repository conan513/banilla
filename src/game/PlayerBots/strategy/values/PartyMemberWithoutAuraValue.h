#pragma once
#include "../Value.h"
#include "PartyMemberValue.h"
#include "../../PlayerbotAIConfig.h"

namespace ai
{
    class PartyMemberWithoutAuraValue : public PartyMemberValue, public Qualified
	{
	public:
        PartyMemberWithoutAuraValue(PlayerbotAI* ai, float range = sPlayerbotAIConfig.sightDistance) :
          PartyMemberValue(ai) {}

    protected:
        virtual Unit* Calculate();
	};

	class MasterWithoutAuraValue : public PartyMemberValue, public Qualified
	{
	public:
        MasterWithoutAuraValue(PlayerbotAI* ai, float range = sPlayerbotAIConfig.sightDistance) :
          PartyMemberValue(ai) {}

    protected:
        virtual Unit* Calculate();
	};

    class PartyMemberWithoutOwnAuraValue : public PartyMemberValue, public Qualified
	{
	public:
        PartyMemberWithoutOwnAuraValue(PlayerbotAI* ai, float range = sPlayerbotAIConfig.sightDistance) :
          PartyMemberValue(ai) {}

    protected:
        virtual Unit* Calculate();
	};

	class MasterWithoutOwnAuraValue : public PartyMemberValue, public Qualified
	{
	public:
        MasterWithoutOwnAuraValue(PlayerbotAI* ai, float range = sPlayerbotAIConfig.sightDistance) :
          PartyMemberValue(ai) {}

    protected:
        virtual Unit* Calculate();
	};
}
