#include "../../../botpch.h"
#include "../../playerbot.h"
#include "PriestMultipliers.h"
#include "HolyPriestStrategy.h"

namespace ai
{
    class HolyPriestStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
    {
    public:
        HolyPriestStrategyActionNodeFactory()
        {
            creators["smite"] = &smite;
            creators["divine hymn"] = &divine_hymn;
            creators["holy nova"] = &holy_nova;
            creators["circle of healing"] = &circle_of_healing;
        }
        ~HolyPriestStrategyActionNodeFactory()
        {
            creators.erase("smite");
            creators.erase("divine hymn");
            creators.erase("holy nova");
            creators.erase("circle of healing");
        }
    private:
        static ActionNode* smite(PlayerbotAI* ai)
        {
            return new ActionNode ("smite",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("shoot"), NULL),
                /*C*/ NULL);
        }
	static ActionNode* divine_hymn(PlayerbotAI* ai)
        {
            return new ActionNode ("divine hymn",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("circle of healing"), NULL),
                /*C*/ NULL);
        }

        static ActionNode* circle_of_healing(PlayerbotAI* ai)
        {
            return new ActionNode ("circle of healing",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("holy nova"), NULL),
                /*C*/ NULL);
        }

	static ActionNode* holy_nova(PlayerbotAI* ai)
        {
            return new ActionNode ("holy nova",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("prayer of healing"), NULL),
                /*C*/ NULL);
        }
    };
};

using namespace ai;

HolyPriestStrategy::HolyPriestStrategy(PlayerbotAI* ai) : GenericPriestStrategy(ai)
{
    factoryInternal = new HolyPriestStrategyActionNodeFactory();
    actionNodeFactories.Add(factoryInternal);
}

NextAction** HolyPriestStrategy::getDefaultActions()
{
    defaultActions =  NextAction::array(0, new NextAction("shoot", ACTION_NORMAL), NULL);
    return defaultActions;
}

HolyPriestStrategy::~HolyPriestStrategy()
{
    actionNodeFactories.Remove(factoryInternal);
    delete factoryInternal;
    delete defaultActions;
}

void HolyPriestStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericPriestStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of spell",
        NextAction::array(0, new NextAction("reach spell", ACTION_MOVE + 9), NULL)));

    triggers.push_back(new TriggerNode(
        "surge of light",
        NextAction::array(0, new NextAction("smite", ACTION_NORMAL + 10), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("prayer of mending", ACTION_LIGHT_HEAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
        NextAction::array(0, new NextAction("prayer of mending on party", ACTION_LIGHT_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "master almost full health",
        NextAction::array(0, new NextAction("prayer of mending on master", ACTION_LIGHT_HEAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
		"light aoe heal",
		NextAction::array(0, new NextAction("holy nova", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
		"medium aoe heal",
		NextAction::array(0, new NextAction("circle of healing", ACTION_MEDIUM_HEAL + 2), NULL)));

     triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("greater heal", ACTION_MEDIUM_HEAL + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("greater heal on party", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "master medium health",
        NextAction::array(0, new NextAction("greater heal on master", ACTION_MEDIUM_HEAL + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("flash heal on party", ACTION_CRITICAL_HEAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "master critical health",
        NextAction::array(0, new NextAction("flash heal on master", ACTION_CRITICAL_HEAL + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("flash heal", ACTION_CRITICAL_HEAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("flash heal on party", ACTION_CRITICAL_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "master low health",
        NextAction::array(0, new NextAction("flash heal on party", ACTION_CRITICAL_HEAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "almost dead",
        NextAction::array(0, new NextAction("guardian spirit", ACTION_EMERGENCY + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost dead",
        NextAction::array(0, new NextAction("guardian spirit on party", ACTION_EMERGENCY + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "master almost dead",
        NextAction::array(0, new NextAction("guardian spirit on master", ACTION_EMERGENCY + 9), NULL)));
}

   class DpsHolyPriestStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
    {
    public:
        DpsHolyPriestStrategyActionNodeFactory()
        {
            creators["smite"] = &smite;
        }
        ~DpsHolyPriestStrategyActionNodeFactory()
        {
            creators["smite"] = &smite;
        }
    private:
        static ActionNode* smite(PlayerbotAI* ai)
        {
            return new ActionNode ("smite",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("shoot"), NULL),
                /*C*/ NULL);
        }
    };

NextAction** DpsHolyPriestStrategy::getDefaultActions()
{
    defaultActions =   NextAction::array(0, new NextAction("holy fire", ACTION_NORMAL + 4), new NextAction("smite", ACTION_NORMAL + 2), NULL);
    return defaultActions;
}

DpsHolyPriestStrategy::DpsHolyPriestStrategy(PlayerbotAI* ai) : GenericPriestStrategy(ai)
{
    factoryInternal = new DpsHolyPriestStrategyActionNodeFactory();
    actionNodeFactories.Add(factoryInternal);
}

DpsHolyPriestStrategy::~DpsHolyPriestStrategy()
{
    actionNodeFactories.Remove(factoryInternal);
    delete factoryInternal;
    delete defaultActions;
}

void DpsHolyPriestStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericPriestStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of spell",
        NextAction::array(0, new NextAction("reach spell", ACTION_MOVE + 9), NULL)));

    triggers.push_back(new TriggerNode(
        "surge of light",
        NextAction::array(0, new NextAction("smite", ACTION_NORMAL + 10), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("flash heal on party", ACTION_CRITICAL_HEAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "master critical health",
        NextAction::array(0, new NextAction("flash heal on master", ACTION_CRITICAL_HEAL + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("renew", ACTION_CRITICAL_HEAL + 4), new NextAction("greater heal", ACTION_CRITICAL_HEAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("renew on party", ACTION_CRITICAL_HEAL + 2), new NextAction("greater heal on party", ACTION_CRITICAL_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "master low health",
        NextAction::array(0, new NextAction("renew on master", ACTION_CRITICAL_HEAL + 6), new NextAction("greater heal on party", ACTION_CRITICAL_HEAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "almost dead",
        NextAction::array(0, new NextAction("guardian spirit", ACTION_EMERGENCY + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost dead",
        NextAction::array(0, new NextAction("guardian spirit on party", ACTION_EMERGENCY + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "master almost dead",
        NextAction::array(0, new NextAction("guardian spirit on master", ACTION_EMERGENCY + 9), NULL)));

     triggers.push_back(new TriggerNode(
        "melee medium aoe",
        NextAction::array(0, new NextAction("holy nova aoe", ACTION_NORMAL + 6), NULL)));
}

