#include "../../../botpch.h"
#include "../../playerbot.h"
#include "ShamanMultipliers.h"
#include "CasterShamanStrategy.h"

using namespace ai;

class CasterShamanStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    CasterShamanStrategyActionNodeFactory()
    {
        creators["magma totem"] = &magma_totem;
        creators["burst"] = &elemental_mastery;
        creators["lava burst"] = &lava_burst;
    }
private:
    static ActionNode* magma_totem(PlayerbotAI* ai)
    {
        return new ActionNode ("magma totem",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("fire nova"), NULL));
    }
    static ActionNode* elemental_mastery(PlayerbotAI* ai)
    {
        return new ActionNode ("elemental mastery",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* lava_burst(PlayerbotAI* ai)
    {
        return new ActionNode ("lava burst",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("lightning bolt"), NULL),
            /*C*/ NULL);
    }
};

CasterShamanStrategy::CasterShamanStrategy(PlayerbotAI* ai) : GenericShamanStrategy(ai)
{
    actionNodeFactories.Add(new CasterShamanStrategyActionNodeFactory());
}

NextAction** CasterShamanStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("lava burst", 19.0f), new NextAction("lightning bolt", 10.0f),NULL);
}

void CasterShamanStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    GenericShamanStrategy::InitTriggers(triggers);

    triggers.push_back(new TriggerNode(
        "enemy out of spell",
        NextAction::array(0, new NextAction("reach spell", ACTION_MOVE + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "shaman weapon",
        NextAction::array(0, new NextAction("flametongue weapon", 23.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "mainhand not enhanced",
        NextAction::array(0, new NextAction("flametongue weapon", 23.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "seldom",
        NextAction::array(0, new NextAction("flametongue weapon", 23.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "totem of wrath",
        NextAction::array(0, new NextAction("totem of wrath", 19.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "shock",
        NextAction::array(0, new NextAction("flame shock", 25.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "frost shock snare",
        NextAction::array(0, new NextAction("frost shock", 21.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium melee aoe",
        NextAction::array(0, new NextAction("magma totem", 19.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy too close for spell",
        NextAction::array(0, new NextAction("thunderstorm", 50.0f), NULL)));

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

void CasterAoeShamanStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "light aoe",
        NextAction::array(0, new NextAction("chain lightning", 25.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "medium melee aoe",
        NextAction::array(0, new NextAction("magma totem", 26.0f), new NextAction("fire nova", 25.0f), NULL)));

 //   triggers.push_back(new TriggerNode(
 //       "high aoe",
 //       NextAction::array(0, new NextAction("reach melee", ACTION_MOVE + 5), new NextAction("magma totem", 26.0f), new NextAction("fire nova", 26.0f), new NextAction("chain lightning", 24.0f),NULL)));

    triggers.push_back(new TriggerNode(
        "magma totem",
        NextAction::array(0, new NextAction("magma totem", 26.0f), new NextAction("fire nova", 25.0f), NULL)));

}
