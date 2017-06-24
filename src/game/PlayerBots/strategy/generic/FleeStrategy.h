#pragma once

namespace ai
{
    class FleeStrategy : public Strategy
    {
    public:
        FleeStrategy(PlayerbotAI* ai);
        ~FleeStrategy();
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "flee"; };
    protected:
        NamedObjectFactory<ActionNode>* factoryInternal;
    };

    class FleeFromAddsStrategy : public Strategy
    {
    public:
        FleeFromAddsStrategy(PlayerbotAI* ai);
        ~FleeFromAddsStrategy();
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "flee from adds"; };
    protected:
        NamedObjectFactory<ActionNode>* factoryInternal;
    };

}
