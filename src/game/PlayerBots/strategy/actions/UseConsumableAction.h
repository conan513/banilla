#pragma once

#include "../Action.h"
#include "InventoryAction.h"

namespace ai
{
    class UseConsumableAction : public InventoryAction {
    public:
        UseConsumableAction(PlayerbotAI* ai) : InventoryAction(ai, "buff") {}
        virtual bool Execute(Event event);

    private:
        void TellHeader(uint32 subClass);
    };

}

namespace ai
{
    class UseEnhancementAction : public InventoryAction {
    public:
        UseEnhancementAction(PlayerbotAI* ai) : InventoryAction(ai, "enhance weapon") {}
        virtual bool Execute(Event event);

    private:
        void TellHeader(uint32 subClass);
    };

}
