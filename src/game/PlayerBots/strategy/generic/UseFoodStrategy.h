#pragma once

namespace ai
{
    class UseFoodStrategy : public Strategy
    {
    public:
        UseFoodStrategy(PlayerbotAI* ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "food"; }
    };

}
