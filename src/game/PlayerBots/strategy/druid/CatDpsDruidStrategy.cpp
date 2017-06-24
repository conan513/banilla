#include "../../../botpch.h"
#include "../../playerbot.h"
#include "DruidMultipliers.h"
#include "CatDpsDruidStrategy.h"

using namespace ai;

class CatDpsDruidStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
{
public:
    CatDpsDruidStrategyActionNodeFactory()
    {
        creators["dire bear form"] = &dire_bear_form;
        creators["melee"] = &melee;
        creators["ravage"] = &ravage;
        creators["feral charge - cat"] = &feral_charge_cat;
        creators["pounce"] = &pounce;
        creators["cat form"] = &cat_form;
        creators["faerie fire (feral)"] = &faerie_fire_feral;
        creators["shred"] = &shred;
        creators["mangle (cat)"] = &mangle_cat;
        creators["shred"] = &shred;
        creators["claw"] = &claw;
        creators["rake"] = &rake;
        creators["savage roar"] = &savageroar;
        creators["ferocious bite"] = &ferocious_bite;
        creators["rip"] = &rip;
        creators["boost"] = &berserk;
        creators["berserk"] = &berserk;
        creators["instant regrowth"] = &instant_regrowth;
        creators["instant regrowth on party"] = &instant_regrowth_on_party;
        creators["instant regrowth on master"] = &instant_regrowth_on_master;
        creators["instant healing touch"] = &instant_healing_touch;
        creators["instant healing touch on party"] = &instant_healing_touch_on_party;
        creators["instant healing touch on master"] = &instant_healing_touch_on_master;
        creators["regrowth"] = &regrowth;
        creators["regrowth on party"] = &regrowth_on_party;
        creators["regrowth on master"] = &regrowth_on_master;
        creators["rejuvenation"] = &rejuvenation;
        creators["rejuvenation on party"] = &rejuvenation_on_party;
        creators["rejuvenation on master"] = &rejuvenation_on_master;
        creators["cure poison"] = &cure_poison;
        creators["cure poison on party"] = &cure_poison_on_party;
        creators["abolish poison"] = &abolish_poison;
        creators["abolish poison on party"] = &abolish_poison_on_party;
        creators["rebirth"] = &rebirth;
        creators["entangling roots on cc"] = &entangling_roots_on_cc;
        creators["hibernate"] = &hibernate;
        creators["hibernate on cc"] = &hibernate_on_cc;
        creators["innervate"] = &innervate;
        creators["dash"] = &dash;
	creators["tranquility"] = &tranquility;
    }
private:
    static ActionNode* dire_bear_form(PlayerbotAI* ai)
    {
        return new ActionNode ("dire bear form",
            /*P*/ NULL,
            /*A*/ NextAction::array(0, new NextAction("bear form"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* ravage(PlayerbotAI* ai)
    {
        return new ActionNode ("ravage",
            /*P*/ NextAction::array(0, new NextAction("prowl"), NULL),
            /*A*/ NextAction::array(0, new NextAction("shred"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* pounce(PlayerbotAI* ai)
    {
        return new ActionNode ("pounce",
            /*P*/ NextAction::array(0, new NextAction("prowl"), NULL),
            /*A*/ NextAction::array(0, new NextAction("ravage"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* melee(PlayerbotAI* ai)
    {
        return new ActionNode ("melee",
            /*P*/ NextAction::array(0, new NextAction("cat form")),
            /*A*/ NextAction::array(0, new NextAction("feral charge - cat"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* feral_charge_cat(PlayerbotAI* ai)
    {
        return new ActionNode ("feral charge - cat",
            /*P*/ NextAction::array(0, new NextAction("cat form"),NULL),
            /*A*/ NextAction::array(0, new NextAction("reach melee"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* faerie_fire_feral(PlayerbotAI* ai)
    {
        return new ActionNode ("faerie fire (feral)",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* cat_form(PlayerbotAI* ai)
    {
        return new ActionNode ("cat form",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* shred(PlayerbotAI* ai)
    {
        return new ActionNode ("shred",
            /*P*/ NextAction::array(0, new NextAction("cat form"),NULL),
            /*A*/ NextAction::array(0, new NextAction("move behind"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* mangle_cat(PlayerbotAI* ai)
    {
        return new ActionNode ("mangle (cat)",
            /*P*/ NextAction::array(0, new NextAction("cat form"),NULL),
            /*A*/ NextAction::array(0, new NextAction("claw"), NULL),
            /*C*/ NextAction::array(0, new NextAction("reach melee"), NULL));
    }
    static ActionNode* claw(PlayerbotAI* ai)
    {
        return new ActionNode ("claw",
            /*P*/ NextAction::array(0, new NextAction("cat form"),NULL),
            /*A*/ NextAction::array(0, new NextAction("melee"), NULL),
            /*C*/ NextAction::array(0, new NextAction("reach melee"), NULL));
    }
    static ActionNode* rake(PlayerbotAI* ai)
    {
        return new ActionNode ("rake",
            /*P*/ NextAction::array(0, new NextAction("cat form"),NULL),
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("mangle (cat)"), NULL));
    }
    static ActionNode* savageroar(PlayerbotAI* ai)
    {
        return new ActionNode ("savage roar",
            /*P*/ NextAction::array(0, new NextAction("cat form"),NULL),
            /*A*/ NextAction::array(0, new NextAction("rip"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* ferocious_bite(PlayerbotAI* ai)
    {
        return new ActionNode ("ferocious bite",
            /*P*/ NextAction::array(0, new NextAction("cat form"),NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* rip(PlayerbotAI* ai)
    {
        return new ActionNode ("rip",
            /*P*/ NextAction::array(0, new NextAction("cat form"),NULL),
            /*A*/ NextAction::array(0, new NextAction("ferocious bite"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* berserk(PlayerbotAI* ai)
    {
        return new ActionNode ("berserk",
            /*P*/ NULL,
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* regrowth(PlayerbotAI* ai)
    {
        return new ActionNode ("regrowth",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("rejuvenation"), NULL),
            /*C*/ NextAction::array(0, new NextAction("cat form"), NULL));
    }
    static ActionNode* regrowth_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("regrowth on party",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("rejuvenation on party"), NULL),
            /*C*/ NextAction::array(0, new NextAction("cat form"), NULL));
    }
    static ActionNode* regrowth_on_master(PlayerbotAI* ai)
    {
        return new ActionNode ("regrowth on master",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("rejuvenation on master"), NULL),
            /*C*/ NextAction::array(0, new NextAction("cat form"), NULL));
    }
    static ActionNode* rejuvenation(PlayerbotAI* ai)
    {
        return new ActionNode ("rejuvenation",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("cat form"), NULL));
    }
    static ActionNode* rejuvenation_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("rejuvenation on party",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("cat form"), NULL));
    }
    static ActionNode* rejuvenation_on_master(PlayerbotAI* ai)
    {
        return new ActionNode ("rejuvenation on master",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("cat form"), NULL));
    }
    static ActionNode* instant_regrowth(PlayerbotAI* ai)
    {
        return new ActionNode ("instant regrowth",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("cat form"), NULL));
    }
    static ActionNode* instant_regrowth_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("instant regrowth on party",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("cat form"), NULL));
    }
    static ActionNode* instant_regrowth_on_master(PlayerbotAI* ai)
    {
        return new ActionNode ("instant regrowth on master",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("cat form"), NULL));
    }
    static ActionNode* instant_healing_touch(PlayerbotAI* ai)
    {
        return new ActionNode ("instant healing touch",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("cat form"), NULL));
    }
    static ActionNode* instant_healing_touch_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("instant healing touch on party",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("cat form"), NULL));
    }
    static ActionNode* instant_healing_touch_on_master(PlayerbotAI* ai)
    {
        return new ActionNode ("instant healing touch on master",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NextAction::array(0, new NextAction("cat form"), NULL));
    }
    static ActionNode* cure_poison(PlayerbotAI* ai)
    {
        return new ActionNode ("cure poison",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* cure_poison_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("cure poison on party",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* abolish_poison(PlayerbotAI* ai)
    {
        return new ActionNode ("abolish poison",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* abolish_poison_on_party(PlayerbotAI* ai)
    {
        return new ActionNode ("abolish poison on party",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* rebirth(PlayerbotAI* ai)
    {
        return new ActionNode ("rebirth",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* entangling_roots_on_cc(PlayerbotAI* ai)
    {
        return new ActionNode ("entangling roots on cc",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* hibernate(PlayerbotAI* ai)
    {
        return new ActionNode ("hibernate",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* hibernate_on_cc(PlayerbotAI* ai)
    {
        return new ActionNode ("hibernate on cc",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* innervate(PlayerbotAI* ai)
    {
        return new ActionNode ("innervate",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NextAction::array(0, new NextAction("mana potion"), NULL),
            /*C*/ NULL);
    }
    static ActionNode* tranquility(PlayerbotAI* ai)
    {
        return new ActionNode ("tranquility",
            /*P*/ NextAction::array(0, new NextAction("caster form"), NULL),
            /*A*/ NULL,
            /*C*/ NULL);
    }
    static ActionNode* dash(PlayerbotAI* ai)
    {
        return new ActionNode ("dash",
            /*P*/ NextAction::array(0, new NextAction("cat form")),
            /*A*/ NULL,
            /*C*/ NULL);
    }
};

CatDpsDruidStrategy::CatDpsDruidStrategy(PlayerbotAI* ai) : MeleeCombatStrategy(ai)
{
    actionNodeFactories.Add(new CatDpsDruidStrategyActionNodeFactory());
}

NextAction** CatDpsDruidStrategy::getDefaultActions()
{
    return NextAction::array(0, new NextAction("ravage", ACTION_NORMAL + 5), new NextAction("shred", ACTION_NORMAL), NULL);
}

void CatDpsDruidStrategy::InitTriggers(std::list<TriggerNode*> &triggers)
{
   triggers.push_back(new TriggerNode(
        "enemy too close for melee",
        NextAction::array(0, new NextAction("move out of enemy contact", ACTION_MOVE + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy out of melee",
        NextAction::array(0, new NextAction("feral charge - cat", ACTION_MOVE + 9), NULL)));

    triggers.push_back(new TriggerNode(
        "enemy too close for melee",
        NextAction::array(0, new NextAction("move out of enemy contact", ACTION_MOVE + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "not facing target",
        NextAction::array(0, new NextAction("set facing",  ACTION_MOVE + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "predator's swiftness",
        NextAction::array(0, new NextAction("instant regrowth on party",  ACTION_NORMAL + 8), NULL)));

    triggers.push_back(new TriggerNode(
        "cat form",
        NextAction::array(0, new NextAction("cat form", ACTION_MOVE + 10), NULL)));
/*
    triggers.push_back(new TriggerNode(
        "caster form",
        NextAction::array(0, new NextAction("cat form", ACTION_MOVE + 10), NULL)));
*/
     triggers.push_back(new TriggerNode(
        "rooted",
        NextAction::array(0, new NextAction("cat form", ACTION_MOVE + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "prowl",
        NextAction::array(0, new NextAction("prowl", ACTION_EMERGENCY + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "pounce",
        NextAction::array(0, new NextAction("pounce",  ACTION_EMERGENCY + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "front target",
        NextAction::array(0, new NextAction("mangle(cat)",  ACTION_MOVE + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "mangle(cat)",
        NextAction::array(0, new NextAction("mangle(cat)", ACTION_NORMAL + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "rake",
        NextAction::array(0, new NextAction("rake", ACTION_NORMAL + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "rip",
        NextAction::array(0, new NextAction("rip", ACTION_HIGH + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "combo point available",
        NextAction::array(0, new NextAction("savage roar", ACTION_HIGH + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "combo points available",
        NextAction::array(0, new NextAction("rip", ACTION_NORMAL + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "medium threat",
        NextAction::array(0, new NextAction("cower", ACTION_HIGH + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "have aggro",
        NextAction::array(0, new NextAction("barkskin", ACTION_EMERGENCY + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "lose aggro",
        NextAction::array(0, new NextAction("cat form", ACTION_MOVE + 6), NULL)));

    triggers.push_back(new TriggerNode(
        "faerie fire (feral)",
        NextAction::array(0, new NextAction("faerie fire (feral)", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "behind target",
        NextAction::array(0, new NextAction("shred", ACTION_NORMAL + 2), NULL)));

	triggers.push_back(new TriggerNode(
		"tiger's fury",
		NextAction::array(0, new NextAction("tiger's fury", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
		"target almost dead",
		NextAction::array(0, new NextAction("ferocious bite", ACTION_EMERGENCY + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "entangling roots",
        NextAction::array(0, new NextAction("entangling roots on cc", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "high health",
        NextAction::array(0, new NextAction("instant regrowth", ACTION_LIGHT_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "party member high health",
        NextAction::array(0, new NextAction("instant regrowth on party", ACTION_LIGHT_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "master high health",
        NextAction::array(0, new NextAction("instant regrowth on master", ACTION_LIGHT_HEAL + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "medium health",
        NextAction::array(0, new NextAction("instant healing touch", ACTION_MEDIUM_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "party member medium health",
        NextAction::array(0, new NextAction("instant healing touch on party", ACTION_MEDIUM_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "master medium health",
        NextAction::array(0, new NextAction("instant healing touch on master", ACTION_MEDIUM_HEAL + 7), NULL)));

    triggers.push_back(new TriggerNode(
        "low health",
        NextAction::array(0, new NextAction("instant healing touch", ACTION_CRITICAL_HEAL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "party member low health",
        NextAction::array(0, new NextAction("instant healing touch on party", ACTION_CRITICAL_HEAL + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "master low health",
        NextAction::array(0, new NextAction("instant healing touch on master", ACTION_CRITICAL_HEAL + 7), NULL)));

       triggers.push_back(new TriggerNode(
        "critical health",
        NextAction::array(0, new NextAction("regrowth", ACTION_CRITICAL_HEAL + 3), NULL)));

       triggers.push_back(new TriggerNode(
        "almost dead",
        NextAction::array(0, new NextAction("survival instincts", ACTION_EMERGENCY + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "party member critical health",
        NextAction::array(0,  new NextAction("regrowth on party", ACTION_CRITICAL_HEAL + 4), new NextAction("rejuvenation on party", ACTION_CRITICAL_HEAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "master critical health",
        NextAction::array(0,  new NextAction("regrowth on master", ACTION_CRITICAL_HEAL + 4), new NextAction("rejuvenation on master", ACTION_CRITICAL_HEAL + 3), NULL)));

    triggers.push_back(new TriggerNode(
        "cure poison",
        NextAction::array(0, new NextAction("abolish poison", ACTION_DISPEL + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "party member cure poison",
        NextAction::array(0, new NextAction("abolish poison on party", ACTION_DISPEL + 1), NULL)));

	triggers.push_back(new TriggerNode(
		"party member dead",
		NextAction::array(0, new NextAction("rebirth", ACTION_HIGH + 1), NULL)));

    triggers.push_back(new TriggerNode(
        "low mana",
        NextAction::array(0, new NextAction("innervate", ACTION_EMERGENCY + 5), NULL)));

    triggers.push_back(new TriggerNode(
        "critical aoe heal",
        NextAction::array(0, new NextAction("barkskin", ACTION_EMERGENCY + 5), new NextAction("tranquility", ACTION_EMERGENCY + 4), NULL)));

    triggers.push_back(new TriggerNode(
        "hibernate",
        NextAction::array(0, new NextAction("hibernate on cc", ACTION_HIGH + 2), NULL)));

    triggers.push_back(new TriggerNode(
        "runaway",
        NextAction::array(0, new NextAction("nature's grasp", ACTION_EMERGENCY + 7), new NextAction("cat form", ACTION_EMERGENCY + 7), new NextAction("dash", ACTION_EMERGENCY + 8), NULL)));

}

