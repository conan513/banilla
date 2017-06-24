#include "../../../botpch.h"
#include "../../playerbot.h"
#include "MageActions.h"

using namespace ai;

Value<Unit*>* CastPolymorphCcAction::GetTargetValue()
{
    return context->GetValue<Unit*>("cc target5", getName());
}
bool CastPolymorphCcAction::Execute(Event event)
{
    return ai->CastSpell("polymorph", GetTarget());
}

bool CastPolymorphAction::isUseful()
{
    return (AI_VALUE2(uint8, "health", GetTargetName()) == 100);
}

bool CastPolymorphCcAction::isUseful()
{
    return (AI_VALUE2(uint8, "health", GetTargetName()) == 100);
}

bool CastScorchAction::isUseful()
{
    return !ai->HasAnyAuraOf(GetTarget(), "shadow mastery", "improved scorch", NULL);
}

bool CastFocusMagicOnPartyAction::isUseful()
{
    if (ai->HasAura("focus magic", AI_VALUE(Unit*, "self target")))
        return false;

    Unit* player = GetTarget();
    if (player)
    {
        switch (player->getClass())
        {
        case CLASS_MAGE:
        case CLASS_WARLOCK:
            return true;
        case CLASS_DRUID:
            return ai->HasAnyAuraOf(player, "moonkin form", NULL);
        }
        return false;

    }
    else return false;


}

