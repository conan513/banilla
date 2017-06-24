#pragma once

namespace ai
{
    class  DisperseStrategy : public Strategy
    {
    public:
         DisperseStrategy(PlayerbotAI* ai) : Strategy(ai) {}
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "disperse"; };
    };
}
