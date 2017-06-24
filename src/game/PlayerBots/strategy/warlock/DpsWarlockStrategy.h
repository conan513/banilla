#pragma once

#include "GenericWarlockStrategy.h"
#include "../generic/CombatStrategy.h"

namespace ai
{
    class DpsWarlockStrategy : public GenericWarlockStrategy
    {
    public:
        DpsWarlockStrategy(PlayerbotAI* ai);
        ~DpsWarlockStrategy();
        virtual string getName() { return "dps"; }
    protected:
        NamedObjectFactory<ActionNode>* factoryInternal;
        NextAction** defaultActions;
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual NextAction** getDefaultActions();
    };

    class DpsAoeWarlockStrategy : public CombatStrategy
    {
    public:
        DpsAoeWarlockStrategy(PlayerbotAI* ai) : CombatStrategy(ai) {}
    protected:
        NamedObjectFactory<ActionNode>* factoryInternal;
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "aoe"; }
    };

    class DpsFireWarlockStrategy : public GenericWarlockStrategy
    {
    public:
        DpsFireWarlockStrategy(PlayerbotAI* ai);
        ~DpsFireWarlockStrategy();
        virtual string getName() { return "fire"; }
    protected:
        NamedObjectFactory<ActionNode>* factoryInternal;
        NextAction** defaultActions;
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual NextAction** getDefaultActions();
    };

    class DpsFireAoeWarlockStrategy : public CombatStrategy
    {
    public:
        DpsFireAoeWarlockStrategy(PlayerbotAI* ai) : CombatStrategy(ai) {}

    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "fire aoe"; }
    };

    class DpsWarlockDebuffStrategy : public CombatStrategy
    {
    public:
        DpsWarlockDebuffStrategy(PlayerbotAI* ai);
        ~DpsWarlockDebuffStrategy();
    protected:
        NamedObjectFactory<ActionNode>* factoryInternal;
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "dps debuff"; }
    };

    class WarlockDebuffStrategy : public CombatStrategy
    {
    public:
        WarlockDebuffStrategy(PlayerbotAI* ai);
         ~WarlockDebuffStrategy();
    protected:
        NamedObjectFactory<ActionNode>* factoryInternal;
    public:
        virtual void InitTriggers(std::list<TriggerNode*> &triggers);
        virtual string getName() { return "debuff"; }
    };

}
