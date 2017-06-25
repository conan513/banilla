#include "../../../botpch.h"
#include "../../playerbot.h"
#include "NearestGroupMemberValue.h"

#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CellImpl.h"

using namespace ai;
using namespace Trinity;

void NearestGroupMemberValue::FindUnits(list<Unit*> &targets)
{
    if (bot->GetGroup())
    {
        AnyGroupedUnitInObjectRangeCheck u_check(bot, bot, range, bot->GetGroup()->isRaidGroup());
        UnitListSearcher<AnyGroupedUnitInObjectRangeCheck> searcher(bot, targets, u_check);
        bot->VisitNearbyObject(bot->GetMap()->GetVisibilityRange(), searcher);
    }
}

bool NearestGroupMemberValue::AcceptUnit(Unit* unit)
{
    return (!unit->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE) && (unit->IsInPartyWith(bot) || unit->IsInRaidWith(bot)));
}
