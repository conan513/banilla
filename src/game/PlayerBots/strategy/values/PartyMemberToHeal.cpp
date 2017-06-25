#include "../../botpch.h"
#include "../../playerbot.h"
#include "PartyMemberToHeal.h"
#include "../../PlayerbotAIConfig.h"
#include "Pet.h"

using namespace ai;

class IsTargetOfHealingSpell : public SpellEntryPredicate
{
public:
    virtual bool Check(SpellEntry const* spell) {
        for (int i=0; i<3; i++) {
            if (spell->Effect[i] == SPELL_EFFECT_HEAL ||
                spell->Effect[i] == SPELL_EFFECT_HEAL_MAX_HEALTH ||
                spell->Effect[i] == SPELL_EFFECT_HEAL_MECHANICAL ||
                spell->Effect[i] == SPELL_EFFECT_HEAL_PCT)
                return true;
        }
        return false;
    }

};

Unit* PartyMemberToHeal::Calculate()
{

    IsTargetOfHealingSpell predicate;

    Group* group = bot->GetGroup();
    if (!group)
        return NULL;

    bool isRaid = bot->GetGroup()->isRaidGroup();
    MinValueCalculator calc(100);
    for (GroupReference *gref = group->GetFirstMember(); gref; gref = gref->next())
    {
        Player* player = gref->getSource();
        if (!Check(player) || !player->isAlive())
            continue;

        uint8 health = player->GetHealthPercent();

        if (player->GetPlayerbotAI()->IsTank(player))
            calc.probe(health, player);
        else if (isRaid || health < sPlayerbotAIConfig.almostFullHealth || !IsTargetOfSpellCast(player, predicate))
            calc.probe(health, player);

        Pet* pet = player->GetPet();
        if (pet && CanHealPet(pet))
        {
            health = ((Unit*)pet)->GetHealthPercent();
            if (isRaid || health < sPlayerbotAIConfig.mediumHealth || !IsTargetOfSpellCast(player, predicate))
                calc.probe(health, player);
        }
    }
    return (Unit*)calc.param;
}

bool PartyMemberToHeal::CanHealPet(Pet* pet)
{
    return HUNTER_PET == pet->getPetType();
}
