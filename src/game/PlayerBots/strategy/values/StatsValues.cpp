#include "../../../botpch.h"
#include "../../playerbot.h"
#include "StatsValues.h"
#include "Pet.h"

using namespace ai;

bool IsTargetInLosValue::Calculate()
{
    Unit* target = GetTarget();

    if (!target)
        return false;
    else
    {

      float targetX = target->GetPositionX();
      float targetY = target->GetPositionY();
      float targetZ = target->GetPositionZ();

      return (bot->IsWithinLOS(targetX, targetY, targetZ));
    }
}

bool IsTargetPlayerValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
    else
        return target->GetOwnerGuid().IsPlayer();
}

bool IsTargetNormalValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
    else
        return (((Creature*)this)->IsNormal());
}

bool IsTargetBossValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
    else
        return (((Creature*)this)->IsWorldBoss());
}

bool IsTargetEliteValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
    else
        return (((Creature*)this)->IsElite());
}


uint8 HealthValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return 100;
    return (static_cast<float> (target->GetHealth()) / target->GetMaxHealth()) * 100;
}

bool IsDeadValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
}

bool PetIsDeadValue::Calculate()
{
	return bot->GetPet() && (!bot->GetPet()->isAlive());
	}

bool PetIsHappyValue::Calculate()
 {
     PetDatabaseStatus status = Pet::GetStatusFromDB(bot);
     if (status == PET_DB_DEAD)
         return true;
 
     return !bot->GetPet() || bot->GetPet()->GetHappinessState() == HAPPY;
 }

bool IsCcValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
    return target->UnderCc();
}

bool IsBleedingValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
    return target->isBleeding();
}

bool IsPolymorphedValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
    return target->IsPolymorphed();
}

bool TakesPeriodicDamageValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
    return target->TakesPeriodicDamage();
}

bool IsFrozenValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
    return target->isFrozen();
}

bool IsSilencedValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
    return target->isFrozen();
}

bool IsFearedValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
    return target->isFeared();
}

bool IsRootedValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
    return target->isInRoots();
}

bool IsCharmedValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
    return target->IsCharmed();
}

bool IsPossessedValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
    return target->isPossessed();
}

bool IsDisorientedValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
    return target->isConfused();
}

bool IsStunnedValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
    return target->IsStunned();
}

bool IsSnaredValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
    return target->isSnared();
}

bool IsFleeingValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
    return target->IsFleeing();
}

uint8 RageValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return 0;
    return (static_cast<float> (target->GetPower(POWER_RAGE)));
}

uint8 EnergyValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return 0;
    return (static_cast<float> (target->GetPower(POWER_ENERGY)));
}


uint8 ManaValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return 100;
    return (static_cast<float> (target->GetPower(POWER_MANA)) / target->GetMaxPower(POWER_MANA)) * 100;
}

bool HasManaValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;
    return target->GetPower(POWER_MANA);
}


uint8 ComboPointsValue::Calculate()
{
    Unit *target = GetTarget();
    if (!target || target->GetGUID() != bot->GetComboTargetGuid())
        return 0;

    return bot->GetComboPoints();
}

bool IsMountedValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;

    return target->IsMounted();
}


bool IsInCombatValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return false;

    return target->isInCombat();
}

uint8 BagSpaceValue::Calculate()
{
    uint32 totalused = 0, total = 16;
    for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
    {
        if (bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
            totalused++;
    }

    uint32 totalfree = 16 - totalused;
    for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)
    {
        const Bag* const pBag = (Bag*) bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
        if (pBag)
        {
            ItemPrototype const* pBagProto = pBag->GetProto();
            if (pBagProto->Class == ITEM_CLASS_CONTAINER && pBagProto->SubClass == ITEM_SUBCLASS_CONTAINER)
            {
                total += pBag->GetBagSize();
                totalfree += pBag->GetFreeSlots();
            }
        }

    }

    return (static_cast<float> (totalused) / total) * 100;
}

uint8 SpeedValue::Calculate()
{
    Unit* target = GetTarget();
    if (!target)
        return 100;

    return (uint8) (100.0f * target->GetSpeedRate(MOVE_RUN));
}
