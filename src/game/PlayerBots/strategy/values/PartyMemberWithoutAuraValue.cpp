#include "../../../botpch.h"
#include "../../playerbot.h"
#include "PartyMemberWithoutAuraValue.h"
#include "Pet.h"

using namespace ai;

class PlayerWithoutAuraPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PlayerWithoutAuraPredicate(PlayerbotAI* ai, string aura) :
        PlayerbotAIAware(ai), FindPlayerPredicate(), aura(aura) {}

public:
    virtual bool Check(Unit* unit)
    {
        if (unit->IsPet())
        {
            Pet* pet = unit->ToPet();
            if (pet && pet->getPetType() == SUMMON_PET)
                return false;
        }

        return unit->IsAlive() && !ai->HasAura(aura, unit);
    }

private:
    string aura;
};

Unit* PartyMemberWithoutAuraValue::Calculate()
{
	PlayerWithoutAuraPredicate predicate(ai, qualifier);
    return FindPartyMember(predicate);
}

class MasterWithoutAuraPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    MasterWithoutAuraPredicate(PlayerbotAI* ai, string aura) :
        PlayerbotAIAware(ai), FindPlayerPredicate(), aura(aura) {}

public:
    virtual bool Check(Unit* unit)
    {
        Unit* unitMaster = ai->GetMaster();
        if (unit != unitMaster)
                return false;

        return (unit->IsAlive() && !ai->HasAura(aura, unit));
    }

private:
    string aura;
};

Unit* MasterWithoutAuraValue::Calculate()
{
	MasterWithoutAuraPredicate predicate(ai, qualifier);
    return FindPartyMember(predicate);
}

class PlayerWithoutOwnAuraPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PlayerWithoutOwnAuraPredicate(PlayerbotAI* ai, string aura) :
        PlayerbotAIAware(ai), FindPlayerPredicate(), aura(aura) {}

public:
    virtual bool Check(Unit* unit)
    {
        if (unit->IsPet())
        {
            Pet* pet = unit->ToPet();
            if (pet && pet->getPetType() == SUMMON_PET)
                return false;
        }

        return unit->IsAlive() && !ai->HasOwnAura(aura, unit);
    }

private:
    string aura;
};

Unit* PartyMemberWithoutOwnAuraValue::Calculate()
{
	PlayerWithoutOwnAuraPredicate predicate(ai, qualifier);
    return FindPartyMember(predicate);
}

class MasterWithoutOwnAuraPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    MasterWithoutOwnAuraPredicate(PlayerbotAI* ai, string aura) :
        PlayerbotAIAware(ai), FindPlayerPredicate(), aura(aura) {}

public:
    virtual bool Check(Unit* unit)
    {
        Unit* unitMaster = ai->GetMaster();
        if (unit != unitMaster)
                return false;

        return (unit->IsAlive() && !ai->HasOwnAura(aura, unit));
    }

private:
    string aura;
};

Unit* MasterWithoutOwnAuraValue::Calculate()
{
	MasterWithoutOwnAuraPredicate predicate(ai, qualifier);
    return FindPartyMember(predicate);
}
