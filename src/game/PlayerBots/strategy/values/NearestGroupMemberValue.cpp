#include "../../../botpch.h"
#include "../../playerbot.h"
#include "NearestGroupMemberValue.h"

#include "GridNotifiers.h"
#include "GridNotifiersImpl.h"
#include "CellImpl.h"

using namespace ai;
using namespace MaNGOS;

void NearestGroupMemberValue::FindUnits(list<Unit*> &targets)
{
    if (bot->GetGroup())
    {
		AnyFriendlyUnitInObjectRangeCheck u_check(bot, range);
		UnitListSearcher<AnyFriendlyUnitInObjectRangeCheck> searcher(targets, u_check);
		Cell::VisitAllObjects(bot, searcher, range);
    }
}

bool NearestGroupMemberValue::AcceptUnit(Unit* unit)
{
	ObjectGuid guid = unit->GetObjectGuid();
    return (!guid.IsPlayer() && (unit->IsInPartyWith(bot) || unit->IsInRaidWith(bot)));
}
