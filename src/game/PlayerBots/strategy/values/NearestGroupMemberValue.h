#pragma once
#include "../Value.h"
#include "NearestUnitsValue.h"
#include "../../PlayerbotAIConfig.h"

namespace ai
{
    class NearestGroupMemberValue : public NearestUnitsValue
	{
	public:
        NearestGroupMemberValue(PlayerbotAI* ai, float range = sPlayerbotAIConfig.disperseDistance) :
          NearestUnitsValue(ai) {}

    protected:
        virtual void FindUnits(list<Unit*> &targets);
        virtual bool AcceptUnit(Unit* unit);

	};
}
