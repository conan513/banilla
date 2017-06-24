#include "../../../botpch.h"
#include "../../playerbot.h"
#include "PriestActions.h"

using namespace ai;


NextAction** CastAbolishDiseaseAction::getAlternatives()
{
    return NextAction::merge(NextAction::array(0, new NextAction("cure disease"), NULL), CastSpellAction::getAlternatives());
}

NextAction** CastAbolishDiseaseOnPartyAction::getAlternatives()
{
    return NextAction::merge(NextAction::array(0, new NextAction("cure disease on party"), NULL), CastSpellAction::getAlternatives());
}

NextAction** CastDesperatePrayerAction::getAlternatives()
{
    return NextAction::merge(NextAction::array(0, new NextAction("flash heal"), NULL), CastSpellAction::getAlternatives());
}

Value<Unit*>* CastShackleUndeadCcAction::GetTargetValue()
{
    return context->GetValue<Unit*>("cc target5", getName());
}

bool CastShackleUndeadCcAction::Execute(Event event)
{
    return ai->CastSpell("shackle undead", GetTarget());
}

