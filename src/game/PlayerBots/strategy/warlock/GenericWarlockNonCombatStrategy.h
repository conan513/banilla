#pragma once

#include "../generic/NonCombatStrategy.h"

namespace ai
{
    class GenericWarlockNonCombatStrategy : public NonCombatStrategy
    {
    public:
        GenericWarlockNonCombatStrategy(PlayerbotAI* ai);
        virtual string getName() { return "nc"; }

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
    };

     class WarlockImpStrategy : public NonCombatStrategy
    {
    public:
        WarlockImpStrategy(PlayerbotAI* ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "imp"; }
    };

    class WarlockVoidwalkerStrategy : public NonCombatStrategy
    {
    public:
        WarlockVoidwalkerStrategy(PlayerbotAI* ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "voidwalker"; }
    };

    class WarlockSuccubusStrategy : public NonCombatStrategy
    {
    public:
        WarlockSuccubusStrategy(PlayerbotAI* ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "succubus"; }
    };

class WarlockFelhunterStrategy : public NonCombatStrategy
    {
    public:
        WarlockFelhunterStrategy(PlayerbotAI* ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "felhunter"; }
    };

class WarlockFelguardStrategy : public NonCombatStrategy
    {
    public:
        WarlockFelguardStrategy(PlayerbotAI* ai);

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "felguard"; }
    };

}
