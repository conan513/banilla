#pragma once

#include "../Action.h"
#include "GenericSpellActions.h"
#include "ReachTargetActions.h"
#include "ChooseTargetActions.h"
#include "MovementActions.h"

namespace ai
{
    class MeleeAction : public AttackAction
    {
    public:
        MeleeAction(PlayerbotAI* ai) : AttackAction(ai, "melee") {}

        virtual bool isUseful() {return !((bot->getLevel() > 19 && ai->HasAura("stealth",bot)) || (bot->getLevel() > 31 && ai->HasAura("prowl",bot)));}

        virtual string GetTargetName() { return "current target"; }
    };

}
