#pragma once

#include "../AiObjectContext.h"

namespace ai
{
    class MageAiObjectContext : public AiObjectContext
    {
    private:
        NamedObjectContext<Strategy>* strategyFactoryInternal;
        NamedObjectContext<Strategy>* mageStrategyFactoryInternal;
        NamedObjectContext<Strategy>* buffStrategyFactoryInternal;
        NamedObjectContext<Action>* aiObjectContextInternal;
        NamedObjectContext<Trigger>* triggerFactoryInternal;
    public:
        MageAiObjectContext(PlayerbotAI* ai);
        ~MageAiObjectContext();
    };
}
