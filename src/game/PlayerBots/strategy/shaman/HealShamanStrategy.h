#pragma once

#include "GenericShamanStrategy.h"

namespace ai
{
    class HealShamanStrategy : public GenericShamanStrategy
    {
    public:
        HealShamanStrategy(PlayerbotAI* ai);
        ~HealShamanStrategy();
    protected:
        NamedObjectFactory<ActionNode>* factoryInternal;
        NextAction** defaultActions;
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual NextAction** getDefaultActions();
        virtual string getName() { return "heal"; }
	virtual int GetType() { return STRATEGY_TYPE_HEAL; }
    };
}
