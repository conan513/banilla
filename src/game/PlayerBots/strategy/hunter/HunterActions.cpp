#include "../../../botpch.h"
#include "../../playerbot.h"
#include "../actions/GenericActions.h"
#include "HunterActions.h"

using namespace ai;

bool CastViperStingAction::isUseful()
{
    return CastDebuffSpellAction::isUseful() && AI_VALUE2(uint8, "mana", "self target") < 30 && AI_VALUE2(uint8, "mana", "current target") >= 30;
}

bool CastAspectOfTheCheetahAction::isUseful()
{
    return !ai->HasAnyAuraOf(GetTarget(), "aspect of the cheetah", "aspect of the pack", NULL);
}

Value<Unit*>* CastFreezingTrapCcAction::GetTargetValue()
{
    return context->GetValue<Unit*>("cc target", "freezing trap");
}

Value<Unit*>* CastWyvernStingCcAction::GetTargetValue()
{
    return context->GetValue<Unit*>("cc target4", getName());
}

bool FeedPetAction::Execute(Event event)
 {
     Pet* pet = bot->GetPet();
     if (pet && pet->getPetType() == HUNTER_PET && pet->GetHappinessState() != HAPPY)
         pet->SetPower(POWER_HAPPINESS, HAPPINESS_LEVEL_SIZE * 2);
 
     return true;
}

bool CastMisdirectionOnPartyAction::isUseful()
{
    Unit* player = GetTarget();

    if (player)
    {
        switch (player->getClass())
        {
            case CLASS_WARRIOR:
                return ai->HasAura("defensive stance", player);
            case CLASS_PALADIN:
                return ai->HasAura("blessing of sanctuary", player);
            case CLASS_DRUID:
                return ai->HasAnyAuraOf(player, "bear form", "dire bear form",  NULL);
        }
            return false;
    }
    else return false;
}
