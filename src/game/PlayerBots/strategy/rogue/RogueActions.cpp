#include "../../../botpch.h"
#include "../../playerbot.h"
#include "RogueActions.h"
#include "RogueOpeningActions.h"
#include "RogueFinishingActions.h"
#include "RogueComboActions.h"

using namespace ai;

NextAction** CastEnvenomAction :: getAlternatives()
{
 return NextAction::merge( NextAction::array(0, new NextAction("eviscerate"), NULL), CastMeleeSpellAction::getAlternatives());
}

NextAction** CastSliceAndDiceAction :: getAlternatives()
{
 return NextAction::merge( NextAction::array(0, new NextAction("eviscerate"), NULL), CastMeleeSpellAction::getAlternatives());
}

NextAction** CastMutilateAction :: getAlternatives()
{
 return NextAction::merge( NextAction::array(0, new NextAction("backstab"), NULL), CastMeleeSpellAction::getAlternatives());
}

NextAction** CastSapCcAction :: getAlternatives()
{
            return NextAction::merge( NextAction::array(0, new NextAction("garrote"), NULL), CastMeleeSpellAction::getAlternatives());
}

NextAction** CastAdrenalineRushAction :: getAlternatives()
{
            return NextAction::merge( NextAction::array(0, new NextAction("blade flurry"), NULL), CastBuffSpellAction::getAlternatives());
}

NextAction** CastBurstAction :: getAlternatives()
{
            return NextAction::merge( NextAction::array(0, new NextAction("shadow dance"), NULL), CastBuffSpellAction::getAlternatives());
}

NextAction** CastShadowDanceAction :: getAlternatives()
{
            return NextAction::merge( NextAction::array(0, new NextAction("cold blood"), NULL), CastBuffSpellAction::getAlternatives());
}

NextAction** CastRuptureAction :: getAlternatives()
{
 return NextAction::merge( NextAction::array(0, new NextAction("eviscerate"), NULL), CastDebuffSpellAction::getAlternatives());
}


