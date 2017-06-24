#include "../../../botpch.h"
#include "../../playerbot.h"
#include "ShamanMultipliers.h"
#include "MeleeShamanStrategy.h"

using namespace ai;

class MeleeShamanStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    MeleeShamanStrategyActionNodeFactory()
    {
        creators["stormstrike"] = &stormstrike;
        creators["lava lash"] = &lava_lash;
        creators["magma totem"] = &magma_totem;
    }
private:
    static ActionNode* stormstrike(PlayerbotAI* ai)
    {
        return new ActionNode ("stormstrike",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("lava lash"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* lava_lash(PlayerbotAI* ai)
    {
        return new ActionNode ("lava lash",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* magma_totem(PlayerbotAI* ai)
    {
        return new ActionNode ("magma totem",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("fire nova"), NULL));
    }
    static ActionNode* shamanistic_rage(PlayerbotAI* ai)
    {
        return new ActionNode ("shamanistic rage",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("mana potion"), NULL),
            /*C*/ NULL);
    }
};

MeleeShamanStrategy::MeleeShamanStrategy(PlayerbotAI* ai) : GenericShamanStrategy(ai)
{
    actionNodeFactories.Add(new MeleeShamanStrategyActionNodeFactory());
}

NextAction** MeleeShamanStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("stormstrike", 20.0f), NULL);
}

void MeleeShamanStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericShamanStrategy::InitTriggers(triggers);

     triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("move behind", ACTION_MOVE + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("windfury weapon", 22.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "random",
        NextAction::array(0, new NextAction("windfury weapon", 22.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "searing totem",
        NextAction::array(0,  new NextAction("reach melee", 22.0f), new NextAction("searing totem", 22.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "rooted",
        NextAction::array(0, new NextAction("earthbind totem", ACTION_EMERGENCY + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "shock",
        NextAction::array(0, new NextAction("earth shock", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "not facing target",
        NextAction::array(0, new NextAction("set facing", ACTION_MOVE + 9), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy too close for melee",
        NextAction::array(0, new NextAction("move out of enemy contact", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "medium aoe",
        NextAction::array(0, new NextAction("fire nova", 25.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("shamanistic rage", ACTION_NORMAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "maelstrom weapon",
        NextAction::array(0, new NextAction("lightning bolt", 32.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse spirit poison",
        NextAction::array(0, new NextAction("cure toxin", 24.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "cleanse spirit disease",
        NextAction::array(0, new NextAction("cure toxin", 24.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure toxins poison",
        NextAction::array(0, new NextAction("cure toxins poison on party", 23.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure toxins disease",
        NextAction::array(0, new NextAction("cure toxins disease on party", 23.0f), NULL)));
}

void MeleeAoeShamanStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("reach melee", ACTION_EMERGENCY), NULL)));

    triggers.push_back(new TriggerNode(
        "magma totem",
        NextAction::array(0, new NextAction("magma totem", 26.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium melee aoe",
        NextAction::array(0, new NextAction("magma totem", 26.0f), new NextAction("fire nova", 26.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "maelstrom weapon",
        NextAction::array(0, new NextAction("chain lightning", 30.0f), NULL)));
}
