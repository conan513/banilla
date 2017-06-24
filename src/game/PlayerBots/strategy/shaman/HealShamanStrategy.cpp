#include "../../../botpch.h"
#include "../../playerbot.h"
#include "ShamanMultipliers.h"
#include "HealShamanStrategy.h"

using namespace ai;

class HealShamanStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    HealShamanStrategyActionNodeFactory()
    {
        creators["earthliving weapon"] = &earthliving_weapon;
        creators["mana tide totem"] = &mana_tide_totem;
        creators["riptide"] = &riptide;
        creators["riptide on party"] = &riptide_on_party;
        creators["tidal force"] = &tidal_force;
    }
    ~HealShamanStrategyActionNodeFactory()
    {
        creators.erase("earthliving weapon");
        creators.erase("mana tide totem");
        creators.erase("riptide");
        creators.erase("riptide on party");
        creators.erase("tidal force");
    }
private:
    static ActionNode* earthliving_weapon(PlayerbotAI* ai)
    {
        return new ActionNode ("earthliving weapon",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("flametongue weapon"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* mana_tide_totem(PlayerbotAI* ai)
    {
        return new ActionNode ("mana tide totem",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("mana potion"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* riptide(PlayerbotAI* ai)
    {
        return new ActionNode ("riptide",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("chain heal"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* riptide_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("riptide on party",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("chain heal on party"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* tidal_force(PlayerbotAI* ai)
    {
        return new ActionNode ("tidal force",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("nature's swiftness"), NULL),
            /*C*/ NULL);
    }
};

HealShamanStrategy::HealShamanStrategy(PlayerbotAI* ai) : GenericShamanStrategy(ai)
{
    factoryInternal = new HealShamanStrategyActionNodeFactory();
    actionNodeFactories.Add(factoryInternal);
}

HealShamanStrategy::~HealShamanStrategy()
{
    actionNodeFactories.Remove(factoryInternal);
    delete factoryInternal;
    delete defaultActions;
}

NextAction** HealShamanStrategy::getDefaultActions()
{
    defaultActions = NextAction::array(0, new NextAction("lightning bolt heal", 10.0f),NULL);
    return defaultActions;
}

void HealShamanStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericShamanStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of spell",
        NextAction::array(0, new NextAction("reach spell", ACTION_MOVE + 9), NULL)));

      triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("earthliving weapon", 23.0f), NULL)));

      triggers.push_back(new TriggerNode(
        "random",
        NextAction::array(0, new NextAction("earthliving weapon", 23.0f), NULL)));

      triggers.push_back(new TriggerNode(
        "mainhand not enhanced",
        NextAction::array(0, new NextAction("earthliving weapon", 23.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "shock",
        NextAction::array(0, new NextAction("flame shock", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "earth shield on master",
        NextAction::array(0, new NextAction("earth shield on master", ACTION_CRITICAL_HEAL + 7), NULL)));

	triggers.push_back(new TriggerNode(
		"medium aoe heal",
		NextAction::array(0, new NextAction("chain heal", ACTION_MEDIUM_HEAL + 7), NULL)));

    triggers.push_back(new TriggerNode(
		"medium health",
		NextAction::array(0, new NextAction("healing wave", ACTION_MEDIUM_HEAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
		"master low health",
		NextAction::array(0, new NextAction("healing wave on master", ACTION_MEDIUM_HEAL + 9), NULL)));

    triggers.push_back(new TriggerNode(
		"master critical health",
		NextAction::array(0, new NextAction("lesser healing wave on master", ACTION_CRITICAL_HEAL + 9), NULL)));

    triggers.push_back(new TriggerNode(
        "party member high health",
        NextAction::array(0, new NextAction("chain heal on party",  ACTION_MEDIUM_HEAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "master member high health",
        NextAction::array(0, new NextAction("chain heal on master",  ACTION_MEDIUM_HEAL + 9), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
		NextAction::array(0, new NextAction("healing wave", ACTION_MEDIUM_HEAL + 4), NULL)));

    triggers.push_back(new TriggerNode(
		"almost full health",
		NextAction::array(0, new NextAction("riptide", ACTION_NORMAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member almost full health",
		NextAction::array(0, new NextAction("riptide on party", ACTION_NORMAL), NULL)));

    triggers.push_back(new TriggerNode(
        "master almost full health",
		NextAction::array(0, new NextAction("riptide on master", ACTION_NORMAL + 9), NULL)));

	triggers.push_back(new TriggerNode(
		"have aggro",
		NextAction::array(0, new NextAction("earth shield", ACTION_HIGH + 6), NULL)));

    triggers.push_back(new TriggerNode(
		"almost dead",
		NextAction::array(0, new NextAction("nature's swiftness", ACTION_EMERGENCY), new NextAction("healing wave", ACTION_CRITICAL_HEAL + 9), NULL)));

    triggers.push_back(new TriggerNode(
		"critical health",
		NextAction::array(0, new NextAction("tidal force", ACTION_CRITICAL_HEAL + 8), new NextAction("low healing wave", ACTION_CRITICAL_HEAL + 8),NULL)));

    triggers.push_back(new TriggerNode(
		"party member almost dead",
		NextAction::array(0, new NextAction("nature's swiftness", ACTION_CRITICAL_HEAL + 9), new NextAction("healing wave on party", ACTION_CRITICAL_HEAL + 9),NULL)));

    triggers.push_back(new TriggerNode(
		"party member critical health",
		NextAction::array(0, new NextAction("tidal force", ACTION_CRITICAL_HEAL + 4), new NextAction("lesser healing wave on party", ACTION_CRITICAL_HEAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("mana tide totem", ACTION_EMERGENCY + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe heal",
        NextAction::array(0, new NextAction("chain heal", 27.0f), NULL)));

}
