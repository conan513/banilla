#pragma once

#include "../AiObjectContext.h"

namespace ai
{
    class PriestAiObjectContext : public AiObjectContext
    {
    private:
        NamedObjectContext<Strategy>* strategyFactoryInternal;
        NamedObjectContext<Strategy>* combatStrategyFactoryInternal;
        NamedObjectContext<Action>* aiObjectContextInternal;
        NamedObjectContext<Trigger>* triggerFactoryInternal;
    public:
        PriestAiObjectContext(PlayerbotAI* ai);
        ~PriestAiObjectContext();
    };
}
