#include "../../../botpch.h"
#include "../../playerbot.h"
#include "PriestMultipliers.h"
#include "HealPriestStrategy.h"

using namespace ai;

class HealPriestStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
    public:
        HealPriestStrategyActionNodeFactory()
        {
            creators["smite"] = &smite;
            creators["divine hymn"] = &divine_hymn;
            creators["holy nova"] = &holy_nova;
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
                /*A*/ NextAction::array(0, new NextAction("prayer of healing"), NULL),
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


HealPriestStrategy::HealPriestStrategy(PlayerbotAI* ai) : GenericPriestStrategy(ai)
{
    actionNodeFactories.Add(new HealPriestStrategyActionNodeFactory());
}

NextAction** HealPriestStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("smite", 10.0f), new NextAction("shoot", 8.0f), NULL);
}

void HealPriestStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericPriestStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of spell",
        NextAction::array(0, new NextAction("reach spell", ACTION_NORMAL + 9), NULL)));

	triggers.push_back(new TriggerNode(
		"medium aoe heal",
		NextAction::array(0, new NextAction("inner focus", 30.0f), new NextAction("prayer of healing", 27.0f), NULL)));

    triggers.push_back(new TriggerNode(
		"critical aoe heal",
		NextAction::array(0, new NextAction("holy nova", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "almost full health",
        NextAction::array(0, new NextAction("prayer of mending", ACTION_LIGHT_HEAL + 1), new NextAction("power word: shield", ACTION_LIGHT_HEAL), NULL)));

    triggers.push_back(new TriggerNode(
        "master almost full health",
        NextAction::array(0, new NextAction("prayer of mending on master", ACTION_LIGHT_HEAL + 3), new NextAction("power word: shield on master", ACTION_LIGHT_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "party member high health",
        NextAction::array(0, new NextAction("renew on party", ACTION_LIGHT_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("greater heal", ACTION_MEDIUM_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "master medium health",
        NextAction::array(0, new NextAction("greater heal on master", ACTION_MEDIUM_HEAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("greater heal on party", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("penance", ACTION_CRITICAL_HEAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("penance on party", ACTION_CRITICAL_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "master low health",
        NextAction::array(0, new NextAction("penance on master", ACTION_CRITICAL_HEAL + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0, new NextAction("power word: shield on party", ACTION_CRITICAL_HEAL + 5), new NextAction("flash heal on party", ACTION_CRITICAL_HEAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "master critical health",
        NextAction::array(0, new NextAction("power word: shield on master", ACTION_CRITICAL_HEAL + 9), new NextAction("flash heal on master", ACTION_CRITICAL_HEAL + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "have aggro",
        NextAction::array(0, new NextAction("fade", 50.0f), new NextAction("psychic scream", 49.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "almost dead",
        NextAction::array(0, new NextAction("pain suppression", ACTION_EMERGENCY + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost dead",
        NextAction::array(0, new NextAction("pain suppression on party", ACTION_EMERGENCY + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "master almost dead",
        NextAction::array(0, new NextAction("pain suppression on party", ACTION_EMERGENCY + 9), NULL)));
}
