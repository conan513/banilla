#pragma once

#include "../AiObjectContext.h"

namespace ai
{
    class WarlockAiObjectContext : public AiObjectContext
    {
    private:
        NamedObjectContext<Strategy>* strategyFactoryInternal;
        NamedObjectContext<Strategy>* combatStrategyFactoryInternal;
        NamedObjectContext<Action>* aiObjectContextInternal;
        NamedObjectContext<Trigger>* triggerFactoryInternal;
    public:
        WarlockAiObjectContext(PlayerbotAI* ai);
        ~WarlockAiObjectContext();
    };
}
