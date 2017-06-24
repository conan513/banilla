#include "../../../botpch.h"
#include "../../playerbot.h"
#include "PartyMemberAfflicted.h"
#include "../../../Entities/Pet/Pet.h"

using namespace ai;

class PartyMemberFearedPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PartyMemberFearedPredicate(PlayerbotAI* ai) :
        PlayerbotAIAware(ai), FindPlayerPredicate() {}

public:
    virtual bool Check(Unit* unit)
    {
        if (unit->IsPet())
        {
            Pet* pet = unit->ToPet();
            if (pet && pet->getPetType() == SUMMON_PET)
                return false;
        }

        return unit->IsAlive() && unit->isFeared();
    }
};

Unit* PartyMemberFeared::Calculate()
{
    PartyMemberFearedPredicate predicate(ai);
    return FindPartyMember(predicate);
}

class PartyMemberCharmedPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PartyMemberCharmedPredicate(PlayerbotAI* ai) :
        PlayerbotAIAware(ai), FindPlayerPredicate() {}

public:
    virtual bool Check(Unit* unit)
    {
        if (unit->IsPet())
        {
            Pet* pet = unit->ToPet();
            if (pet && pet->getPetType() == SUMMON_PET)
                return false;
        }

        return unit->IsAlive() && unit->IsCharmed();
    }
};

Unit* PartyMemberCharmed::Calculate()
{
    PartyMemberCharmedPredicate predicate(ai);
    return FindPartyMember(predicate);
}

class PartyMemberPossessedPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PartyMemberPossessedPredicate(PlayerbotAI* ai) :
        PlayerbotAIAware(ai), FindPlayerPredicate() {}

public:
    virtual bool Check(Unit* unit)
    {
        if (unit->IsPet())
        {
            Pet* pet = unit->ToPet();
            if (pet && pet->getPetType() == SUMMON_PET)
                return false;
        }

        return unit->IsAlive() && unit->isPossessed();
    }
};

Unit* PartyMemberPossessed::Calculate()
{
    PartyMemberPossessedPredicate predicate(ai);
    return FindPartyMember(predicate);
}

class PartyMemberPolymorphedPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PartyMemberPolymorphedPredicate(PlayerbotAI* ai) :
        PlayerbotAIAware(ai), FindPlayerPredicate() {}

public:
    virtual bool Check(Unit* unit)
    {
        if (unit->IsPet())
        {
            Pet* pet = unit->ToPet();
            if (pet && pet->getPetType() == SUMMON_PET)
                return false;
        }

        return unit->IsAlive() && unit->IsPolymorphed();
    }
};

Unit* PartyMemberPolymorphed::Calculate()
{
    PartyMemberPolymorphedPredicate predicate(ai);
    return FindPartyMember(predicate);
}

class PartyMemberSnaredPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PartyMemberSnaredPredicate(PlayerbotAI* ai) :
        PlayerbotAIAware(ai), FindPlayerPredicate() {}

public:
    virtual bool Check(Unit* unit)
    {
        if (unit->IsPet())
        {
            Pet* pet = unit->ToPet();
            if (pet && pet->getPetType() == SUMMON_PET)
                return false;
        }

        return unit->IsAlive() && unit->isSnared();
    }
};

Unit* PartyMemberSnared::Calculate()
{
    PartyMemberSnaredPredicate predicate(ai);
    return FindPartyMember(predicate);
}

class PartyMemberFrozenPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PartyMemberFrozenPredicate(PlayerbotAI* ai) :
        PlayerbotAIAware(ai), FindPlayerPredicate() {}

public:
    virtual bool Check(Unit* unit)
    {
        if (unit->IsPet())
        {
            Pet* pet = unit->ToPet();
            if (pet && pet->getPetType() == SUMMON_PET)
                return false;
        }

        return unit->IsAlive() && unit->isFrozen();
    }
};

Unit* PartyMemberFrozen::Calculate()
{
    PartyMemberFrozenPredicate predicate(ai);
    return FindPartyMember(predicate);
}

class PartyMemberRootedPredicate : public FindPlayerPredicate, public PlayerbotAIAware
{
public:
    PartyMemberRootedPredicate(PlayerbotAI* ai) :
        PlayerbotAIAware(ai), FindPlayerPredicate() {}

public:
    virtual bool Check(Unit* unit)
    {
        if (unit->IsPet())
        {
            Pet* pet = unit->ToPet();
            if (pet && pet->getPetType() == SUMMON_PET)
                return false;
        }

        return unit->IsAlive() && unit->isInRoots();
    }
};

Unit* PartyMemberRooted::Calculate()
{
    PartyMemberRootedPredicate predicate(ai);
    return FindPartyMember(predicate);
}

