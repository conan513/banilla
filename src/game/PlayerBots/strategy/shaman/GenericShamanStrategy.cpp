#include "../../../botpch.h"
#include "../../playerbot.h"
#include "ShamanMultipliers.h"
#include "HealShamanStrategy.h"

using namespace ai;

class GenericShamanStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    GenericShamanStrategyActionNodeFactory()
    {
        creators["flame shock"] = &flame_shock;
        creators["earth shock"] = &earth_shock;
        creators["flametongue weapon"] = &flametongue_weapon;
        creators["frostbrand weapon"] = &frostbrand_weapon;
        creators["windfury weapon"] = &windfury_weapon;
        creators["lesser healing wave"] = &lesser_healing_wave;
        creators["lesser healing wave on party"] = &lesser_healing_wave_on_party;
        creators["lesser healing wave on master"] = &lesser_healing_wave_on_master;
        creators["healing wave"] = &healing_wave;
        creators["healing wave on party"] = &healing_wave_on_party;
        creators["healing wave on master"] = &healing_wave_on_master;
        creators["chain heal"] = &chain_heal;
        creators["chain heal on party"] = &chain_heal_on_party;
        creators["chain heal on master"] = &chain_heal_on_master;
        creators["strength of earth totem"] = &strength_earth_totem;
        creators["stoneskin totem"] = &stoneskin_totem;
        creators["totem of wrath totem"] = &wrath_totem;
        creators["flametongue totem"] = &flametongue_totem;
        creators["searing totem"] = &searing_totem;
        creators["mana spring totem"] = &mana_spring_totem;
        creators["wrath of air totem"] = &wrath_air_totem;
        creators["grace of air totem"] = &grace_air_totem;
        creators["magma totem"] = &magma_totem;
        creators["boost"] = &bloodlust;
        creators["bloodlust"] = &bloodlust;
        creators["heroism"] = &bloodlust;
        creators["earth elemental totem"] = &earth_elemental_totem;
    }
    ~GenericShamanStrategyActionNodeFactory()
    {
        creators.erase("flame shock");
        creators.erase("earth shock");
        creators.erase("flametongue weapon");
        creators.erase("frostbrand weapon");
        creators.erase("windfury weapon");
        creators.erase("lesser healing wave");
        creators.erase("lesser healing wave on party");
        creators.erase("lesser healing wave on master");
        creators.erase("healing wave");
        creators.erase("healing wave on party");
        creators.erase("healing wave on master");
        creators.erase("chain heal");
        creators.erase("chain heal on party");
        creators.erase("chain heal on master");
        creators.erase("strength of earth totem");
        creators.erase("stoneskin totem");
        creators.erase("totem of wrath totem");
        creators.erase("flametongue totem");
        creators.erase("searing totem");
        creators.erase("mana spring totem");
        creators.erase("wrath of air totem");
        creators.erase("grace of air totem");
        creators.erase("magma totem");
        creators.erase("boost");
        creators.erase("bloodlust");
        creators.erase("heroism");
        creators.erase("earth elemental totem");
    }
private:

    static ActionNode* flame_shock(PlayerbotAI* ai)
    {
        return new ActionNode ("flame shock",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("earth shock"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* earth_shock(PlayerbotAI* ai)
    {
        return new ActionNode ("earth shock",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("reach spell"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* frost_shock(PlayerbotAI* ai)
    {
        return new ActionNode ("frost shock",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("earthbind totem"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* flametongue_weapon(PlayerbotAI* ai)
    {
        return new ActionNode ("flametongue weapon",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("frostbrand weapon"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* frostbrand_weapon(PlayerbotAI* ai)
    {
        return new ActionNode ("frostbrand weapon",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("rockbiter weapon"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* windfury_weapon(PlayerbotAI* ai)
    {
        return new ActionNode ("windfury weapon",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("rockbiter weapon"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* strength_earth_totem(PlayerbotAI* ai)
    {
        return new ActionNode ("strength of earth totem",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("stoneskin totem"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* stoneskin_totem(PlayerbotAI* ai)
    {
        return new ActionNode ("stoneskin totem",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("tremor totem"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* wrath_totem(PlayerbotAI* ai)
    {
        return new ActionNode ("totem of wrath",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("flametongue totem"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* magma_totem(PlayerbotAI* ai)
    {
        return new ActionNode ("magma totem",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("fire nova"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* flametongue_totem(PlayerbotAI* ai)
    {
        return new ActionNode ("flametongue totem",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("searing totem"), NULL),
            /*C*/ NULL);
    }
   static ActionNode* searing_totem(PlayerbotAI* ai)
    {
        return new ActionNode ("searing totem",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("magma totem"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* mana_spring_totem(PlayerbotAI* ai)
    {
        return new ActionNode ("mana spring totem",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("healing stream totem"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* wrath_air_totem(PlayerbotAI* ai)
    {
        return new ActionNode ("wrath of air totem",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* grace_air_totem(PlayerbotAI* ai)
    {
        return new ActionNode ("grace of air totem",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("windfury totem"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* bloodlust(PlayerbotAI* ai)
    {
        return new ActionNode ("bloodlust",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("heroism"), NULL),
            /*C*/ NextAction::array(0, new NextAction("fire elemental"), NULL));
    }
    static ActionNode* heroism(PlayerbotAI* ai)
    {
        return new ActionNode ("heroism",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("bloodlust"), NULL),
            /*C*/ NextAction::array(0, new NextAction("fire elemental"), NULL));
    }
    static ActionNode* earth_elemental_totem(PlayerbotAI* ai)
    {
        return new ActionNode ("earth elemental totem",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("stoneclaw totem"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* chain_heal(PlayerbotAI* ai)
    {
        return new ActionNode ("chain heal",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("lesser healing wave"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* chain_heal_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("chain heal on party",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("lesser healing wave on party"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* chain_heal_on_master(PlayerbotAI* ai)
    {
        return new ActionNode ("chain heal on master",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("lesser healing wave on master"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* lesser_healing_wave(PlayerbotAI* ai)
    {
        return new ActionNode ("lesser healing wave",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("healing wave"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* lesser_healing_wave_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("lesser healing wave on party",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("healing wave on party"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* lesser_healing_wave_on_master(PlayerbotAI* ai)
    {
        return new ActionNode ("lesser healing wave on master",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("healing wave on master"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* healing_wave(PlayerbotAI* ai)
    {
        return new ActionNode ("healing wave",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("relocate"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* healing_wave_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("healing wave on party",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("relocate"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* healing_wave_on_master(PlayerbotAI* ai)
    {
        return new ActionNode ("healing wave on master",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("relocate"), NULL),
            /*C*/ NULL);
    }
};

GenericShamanStrategy::GenericShamanStrategy(PlayerbotAI* ai) : CombatStrategy(ai)
{
    factoryInternal = new GenericShamanStrategyActionNodeFactory();
    actionNodeFactories.Add(factoryInternal);
}

GenericShamanStrategy::~GenericShamanStrategy()
{
    actionNodeFactories.Remove(factoryInternal);
    delete factoryInternal;
}

void GenericShamanStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    CombatStrategy::InitTriggers(triggers);

     triggers.push_back(new TriggerNode(
        "shock",
        NextAction::array(0, new NextAction("flame shock", 20.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "takes periodic damage",
        NextAction::array(0, new NextAction("flee", ACTION_MOVE + 9), NULL)));

     triggers.push_back(new TriggerNode(
        "runaway",
        NextAction::array(0, new NextAction("earthbind totem", ACTION_EMERGENCY + 7), new NextAction("frost shock", ACTION_EMERGENCY + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy out of spell",
        NextAction::array(0, new NextAction("reach spell", ACTION_MOVE + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "not facing target",
        NextAction::array(0, new NextAction("set facing", ACTION_MOVE + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "wind shear",
        NextAction::array(0, new NextAction("wind shear", ACTION_INTERRUPT), NULL)));

     triggers.push_back(new TriggerNode(
        "target fleeing",
        NextAction::array(0, new NextAction("frost shock", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "wind shear on enemy healer",
        NextAction::array(0, new NextAction("wind shear on enemy healer", ACTION_INTERRUPT + 3), NULL)));

	triggers.push_back(new TriggerNode(
        "purge",
		NextAction::array(0, new NextAction("purge", 10.0f), NULL)));

    triggers.push_back(new TriggerNode(
		"almost dead",
		NextAction::array(0, new NextAction("stoneclaw totem", ACTION_EMERGENCY + 2), NULL)));

    triggers.push_back(new TriggerNode(
		"party member critical health",
		NextAction::array(0, new NextAction("lesser healing wave on party", ACTION_CRITICAL_HEAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "critical aoe heal",
        NextAction::array(0, new NextAction("chain heal", ACTION_CRITICAL_HEAL + 7), NULL)));

    triggers.push_back(new TriggerNode(
		"low health",
		NextAction::array(0, new NextAction("lesser healing wave", ACTION_CRITICAL_HEAL + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
		NextAction::array(0, new NextAction("lesser healing wave on party", ACTION_CRITICAL_HEAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "party member charmed",
        NextAction::array(0, new NextAction("tremor totem ", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "party member feared",
        NextAction::array(0, new NextAction("tremor totem", 60.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "hex",
        NextAction::array(0, new NextAction("hex", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
        "have aggro",
        NextAction::array(0, new NextAction("earth elemental totem", 60.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"heroism",
		NextAction::array(0, new NextAction("heroism", 31.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"bloodlust",
		NextAction::array(0, new NextAction("bloodlust", 30.0f), NULL)));

    triggers.push_back(new TriggerNode(
		"finish target",
		NextAction::array(0, new NextAction("earth shock", ACTION_HIGH + 9), NULL)));

    triggers.push_back(new TriggerNode(
		"target almost dead",
		NextAction::array(0, new NextAction("earth shock", ACTION_HIGH + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "light aoe heal",
        NextAction::array(0, new NextAction("healing stream totem", ACTION_LIGHT_HEAL), NULL)));
}

void ShamanBuffDpsStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "lightning shield",
        NextAction::array(0, new NextAction("lightning shield", 22.0f), NULL)));
}

void ShamanBuffManaStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
    triggers.push_back(new TriggerNode(
        "water shield",
        NextAction::array(0, new NextAction("water shield", 22.0f), NULL)));
}

void ShamanCureStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
	triggers.push_back(new TriggerNode(
		"cure poison",
		NextAction::array(0, new NextAction("cure poison", 21.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"party member cure poison",
		NextAction::array(0, new NextAction("cure poison on party", 21.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"cleanse spirit poison",
		NextAction::array(0, new NextAction("cleanse spirit", 24.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"party member cleanse spirit poison",
		NextAction::array(0, new NextAction("cleanse spirit poison on party", 23.0f), NULL)));
	
	triggers.push_back(new TriggerNode(
		"cure disease",
		NextAction::array(0, new NextAction("cure disease", 31.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"party member cure disease",
		NextAction::array(0, new NextAction("cure disease on party", 30.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"cleanse spirit disease",
		NextAction::array(0, new NextAction("cleanse spirit", 24.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"party member cleanse spirit disease",
		NextAction::array(0, new NextAction("cleanse spirit disease on party", 23.0f), NULL)));


	triggers.push_back(new TriggerNode(
		"cleanse spirit curse",
		NextAction::array(0, new NextAction("cleanse spirit", 24.0f), NULL)));

	triggers.push_back(new TriggerNode(
		"party member cleanse spirit curse",
		NextAction::array(0, new NextAction("cleanse spirit curse on party", 23.0f), NULL)));

}

