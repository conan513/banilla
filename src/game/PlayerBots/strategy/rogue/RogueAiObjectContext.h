#pragma once

#include "../AiObjectContext.h"

namespace ai
{
    class RogueAiObjectContext : public AiObjectContext
    {
    private:
        NamedObjectContext<Strategy>* strategyFactoryInternal;
        NamedObjectContext<Action>* aiObjectContextInternal;
        NamedObjectContext<Trigger>* triggerFactoryInternal;
    public:
        RogueAiObjectContext(PlayerbotAI* ai);
        ~RogueAiObjectContext();
    };
}
