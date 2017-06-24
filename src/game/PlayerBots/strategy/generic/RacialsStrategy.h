#pragma once

namespace ai
{
    class RacialsStrategy : public Strategy
    {
    public:
        RacialsStrategy(PlayerbotAI* ai);
        ~RacialsStrategy();
        virtual string getName() { return "racials"; }
      protected:
        NamedObjectFactory<ActionNode>* factoryInternal;
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

}
