#include "../../../botpch.h"
#include "../../playerbot.h"
#include "DruidActions.h"

using namespace ai;

bool CastCasterFormAction::Execute(Event event)
{
    ai->RemoveShapeshift();
    return true;
}

bool CastCatFormAction::Execute(Event event)
{
	if (ai->HasAnyAuraOf(GetTarget(), "dire bear form", "bear form", "travel form", "aquatic form",
		"flight form", "swift flight form", "moonkin form", "tree of life", NULL))
		ai->RemoveShapeshift();
	
	ai->CastSpell("cat form", bot);
	return true;
}

bool CastBearFormAction::Execute(Event event)
{
	if (ai->HasAnyAuraOf(GetTarget(),"cat form","travel form", "aquatic form",
		"flight form", "swift flight form", "moonkin form", "tree of life", NULL))
		ai->RemoveShapeshift();

	ai->CastSpell("bear form", bot);
	return true;
}

bool CastDireBearFormAction::Execute(Event event)
{
	if (ai->HasAnyAuraOf(GetTarget(), "cat form", "travel form", "aquatic form",
		"flight form", "swift flight form", "moonkin form", "tree of life", NULL))
		ai->RemoveShapeshift();

	ai->CastSpell("dire bear form", bot);
	return true;
}

bool CastMoonkinFormAction::Execute(Event event)
{
	if (ai->HasAnyAuraOf(GetTarget(), "dire bear form", "bear form", "cat form", "travel form", "aquatic form",
		"flight form", "swift flight form", "tree of life", NULL))
		ai->RemoveShapeshift();

	ai->CastSpell("moonkin form", bot);
	return true;
}

bool CastTreeFormAction::Execute(Event event)
{
	if (ai->HasAnyAuraOf(GetTarget(), "dire bear form", "bear form", "cat form", "travel form", "aquatic form",
		"flight form", "swift flight form", "moonkin form", NULL))
		ai->RemoveShapeshift();

	ai->CastSpell("tree of life", bot);
	return true;
}


NextAction** CastAbolishPoisonAction::getAlternatives()
{
    return NextAction::merge( NextAction::array(0, new NextAction("cure poison"), NULL), CastSpellAction::getPrerequisites());
}

NextAction** CastBoostAction::getAlternatives()
{
    return NextAction::merge( NextAction::array(0, new NextAction("force of nature"), NULL), CastSpellAction::getPrerequisites());
}

NextAction** CastAbolishPoisonOnPartyAction::getAlternatives()
{
    return NextAction::merge( NextAction::array(0, new NextAction("cure poison on party"), NULL), CastSpellAction::getPrerequisites());
}

Value<Unit*>* CastEntanglingRootsCcAction::GetTargetValue()
{
    return context->GetValue<Unit*>("cc target2", "entangling roots");
}

bool CastEntanglingRootsCcAction::Execute(Event event)
{
    return ai->CastSpell("entangling roots", GetTarget());
}

Value<Unit*>* CastHibernateCcAction::GetTargetValue()
{
    return context->GetValue<Unit*>("cc target3", "hibernate");
}

bool CastHibernateCcAction::Execute(Event event)
{
    return ai->CastSpell("hibernate", GetTarget());
}

bool CastNaturesSwiftnessOnMasterAction::Execute(Event event)
{
    return ai->CastSpell("nature's swiftness", GetTarget());
}

bool CastNaturesSwiftnessOnPartyAction::Execute(Event event)
{
    return ai->CastSpell("nature's swiftness", GetTarget());
}

bool CastMoonfireHealAction::Execute(Event event)
{
    return ai->CastSpell("moonfire", GetTarget());
}

bool CastWrathHealAction::Execute(Event event)
{
    return ai->CastSpell("wrath", GetTarget());
}

bool CastThornsOnPartyAction::isUseful()
{
    Unit* player = GetTarget();

    if (player)
    {
        if (ai->IsTank(dynamic_cast<Player*>(player)))
        {
           return true;
        }

        switch (player->getClass())
        {
            case CLASS_DEATH_KNIGHT:
                return ai->HasAura("frost presence", player);
            case CLASS_WARRIOR:
                return ai->HasAura("defensive stance", player);
            case CLASS_PALADIN:
                return ai->HasAnyAuraOf(player, "blessing of sanctuary", "retribution aura", NULL);
            case CLASS_DRUID:
                return ai->HasAnyAuraOf(player, "bear form", "dire bear form", "moonkin form", NULL);
        }
            return false;
    }
    else return true;
}

