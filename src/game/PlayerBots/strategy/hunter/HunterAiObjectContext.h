#pragma once

#include "../AiObjectContext.h"

namespace ai
{
    class HunterAiObjectContext : public AiObjectContext
    {
    private:
        NamedObjectContext<Strategy>* strategyFactoryInternal;
        NamedObjectContext<Strategy>* buffStrategyFactoryInternal;
        NamedObjectContext<Action>* aiObjectContextInternal;
        NamedObjectContext<Trigger>* triggerFactoryInternal;
    public:
        HunterAiObjectContext(PlayerbotAI* ai);
        ~HunterAiObjectContext();
    };
}
