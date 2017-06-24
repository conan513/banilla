#pragma once

namespace ai
{
    class GenericPriestStrategyActionNodeFactory : public NamedObjectFactory<ActionNode>
    {
    public:
        GenericPriestStrategyActionNodeFactory()
        {
            creators["inner fire"] = &inner_fire;
            creators["holy nova"] = &holy_nova;
            creators["power word: fortitude"] = &power_word_fortitude;
            creators["power word: fortitude on party"] = &power_word_fortitude_on_party;
            creators["divine spirit"] = &divine_spirit;
            creators["divine spirit on party"] = &divine_spirit_on_party;
            creators["power word: shield"] = &power_word_shield;
            creators["power word: shield on party"] = &power_word_shield_on_party;
            creators["power word: shield on master"] = &power_word_shield_on_master;
            creators["renew"] = &renew;
            creators["renew on party"] = &renew_on_party;
            creators["renew on master"] = &renew_on_master;
            creators["guardian spirit"] = &guardian_spirit;
            creators["guardian spirit on party"] = &guardian_spirit_on_party;
            creators["guardian spirit on master"] = &guardian_spirit_on_master;
            creators["pain suppression"] = &renew;
            creators["pain suppression on party"] = &renew_on_party;
            creators["pain suppression on master"] = &renew_on_master;
            creators["greater heal"] = &greater_heal;
            creators["greater heal on party"] = &greater_heal_on_party;
            creators["greater heal on master"] = &greater_heal_on_master;
            creators["heal"] = &heal;
            creators["heal on party"] = &heal_on_party;
            creators["heal on master"] = &heal_on_master;
            creators["lesser heal"] = &lesser_heal;
            creators["lesser heal on party"] = &lesser_heal_on_party;
            creators["lesser heal on master"] = &lesser_heal_on_master;
            creators["flash heal"] = &flash_heal;
            creators["flash heal on party"] = &flash_heal_on_party;
            creators["flash heal on master"] = &flash_heal_on_master;
            creators["desperate prayer"] = &desperate_prayer;
            creators["psychic scream"] = &psychic_scream;
            creators["fade"] = &fade;
            creators["boost"] = &power_infusion;
            creators["hymn of hope"] = &hymn_of_hope;
            creators["divine hymn"] = &divine_hymn;
            creators["desperate prayer"] = &desperate_prayer;
            creators["penance"] = &penance;
            creators["penance on party"] = &penance_on_party;
            creators["penance on master"] = &penance_on_master;
            creators["circle of healing"] = &circle_of_healing;
            creators["circle of healing on party"] = &circle_of_healing_on_party;
            creators["prayer of mending"] = &prayer_of_mending;
            creators["prayer of mending on party"] = &prayer_of_mending_on_party;
            creators["circle of healing on master"] = &circle_of_healing_on_master;
            creators["prayer of mending on master"] = &prayer_of_mending_on_master;
        }
    private:
        static ActionNode* inner_fire(PlayerbotAI* ai)
        {
            return new ActionNode ("inner fire",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NULL,
                /*C*/ NULL);
        }
        static ActionNode* holy_nova(PlayerbotAI* ai)
        {
            return new ActionNode ("holy nova",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NULL,
                /*C*/ NULL);
        }
        static ActionNode* power_word_fortitude(PlayerbotAI* ai)
        {
            return new ActionNode ("power word: fortitude",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NULL,
                /*C*/ NULL);
        }
        static ActionNode* power_word_fortitude_on_party(PlayerbotAI* ai)
        {
            return new ActionNode ("power word: fortitude on party",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NULL,
                /*C*/ NULL);
        }
        static ActionNode* divine_spirit(PlayerbotAI* ai)
        {
            return new ActionNode ("divine spirit",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NULL,
                /*C*/ NULL);
        }
        static ActionNode* divine_spirit_on_party(PlayerbotAI* ai)
        {
            return new ActionNode ("divine spirit on party",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NULL,
                /*C*/ NULL);
        }
        static ActionNode* power_word_shield(PlayerbotAI* ai)
        {
            return new ActionNode ("power word: shield",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("renew", 50.0f), NULL),
                /*C*/ NULL);
        }
        static ActionNode* power_word_shield_on_party(PlayerbotAI* ai)
        {
            return new ActionNode ("power word: shield on party",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("renew on party", 50.0f), NULL),
                /*C*/ NULL);
        }
        static ActionNode* power_word_shield_on_master(PlayerbotAI* ai)
        {
            return new ActionNode ("power word: shield on master",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("renew on master", 50.0f), NULL),
                /*C*/ NULL);
        }
        static ActionNode* circle_of_healing(PlayerbotAI* ai)
        {
            return new ActionNode ("circle_of_healing",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("prayer of healing", 50.0f), NULL),
                /*C*/ NULL);
        }
        static ActionNode* circle_of_healing_on_party(PlayerbotAI* ai)
        {
            return new ActionNode ("circle of healing on party",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("prayer of healing", 50.0f), NULL),
                /*C*/ NULL);
        }
        static ActionNode* circle_of_healing_on_master(PlayerbotAI* ai)
        {
            return new ActionNode ("circle of healing on master",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("prayer of healing", 50.0f), NULL),
                /*C*/ NULL);
        }
        static ActionNode* pain_suppression(PlayerbotAI* ai)
        {
            return new ActionNode ("pain suppression",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("guardian spirit", ACTION_EMERGENCY+8), NULL),
                /*C*/ NULL);
        }
        static ActionNode* pain_suppression_on_party(PlayerbotAI* ai)
        {
            return new ActionNode ("pain suppression on party",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("guardian spirit on party", ACTION_EMERGENCY+7), NULL),
                /*C*/ NULL);
        }
        static ActionNode* pain_suppression_on_master(PlayerbotAI* ai)
        {
            return new ActionNode ("pain suppression on master",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("guardian spirit on master", ACTION_EMERGENCY+9), NULL),
                /*C*/ NULL);
        }
        static ActionNode* guardian_spirit(PlayerbotAI* ai)
        {
            return new ActionNode ("guardian spirit",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("power word: shield", ACTION_EMERGENCY+8), NULL),
                /*C*/ NULL);
        }
        static ActionNode* guardian_spirit_on_party(PlayerbotAI* ai)
        {
            return new ActionNode ("guardian spirit on party",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("power word: shield on party", ACTION_EMERGENCY+7), NULL),
                /*C*/ NULL);
        }
        static ActionNode* guardian_spirit_on_master(PlayerbotAI* ai)
        {
            return new ActionNode ("guardian spirit on master",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("power word: shield on Master", ACTION_EMERGENCY+9), NULL),
                /*C*/ NULL);
        }
        static ActionNode* renew(PlayerbotAI* ai)
        {
            return new ActionNode ("renew",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NULL,
                /*C*/ NULL);
        }
        static ActionNode* renew_on_party(PlayerbotAI* ai)
        {
            return new ActionNode ("renew on party",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NULL,
                /*C*/ NULL);
        }
        static ActionNode* renew_on_master(PlayerbotAI* ai)
        {
            return new ActionNode ("renew on master",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NULL,
                /*C*/ NULL);
        }
        static ActionNode* greater_heal(PlayerbotAI* ai)
        {
            return new ActionNode ("greater heal",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NextAction::array(0, new NextAction("heal"), NULL),
                /*C*/ NULL);
        }
        static ActionNode* greater_heal_on_party(PlayerbotAI* ai)
        {
            return new ActionNode ("greater heal on party",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NextAction::array(0, new NextAction("heal on party"), NULL),
                /*C*/ NULL);
        }
        static ActionNode* greater_heal_on_master(PlayerbotAI* ai)
        {
            return new ActionNode ("greater heal on master",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NextAction::array(0, new NextAction("heal on master"), NULL),
                /*C*/ NULL);
        }
        static ActionNode* heal(PlayerbotAI* ai)
        {
            return new ActionNode ("heal",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NextAction::array(0, new NextAction("lesser heal"), NULL),
                /*C*/ NULL);
        }
        static ActionNode* heal_on_party(PlayerbotAI* ai)
        {
            return new ActionNode ("heal on party",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NextAction::array(0, new NextAction("lesser heal on party"), NULL),
                /*C*/ NULL);
        }
        static ActionNode* heal_on_master(PlayerbotAI* ai)
        {
            return new ActionNode ("heal on master",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NextAction::array(0, new NextAction("lesser heal on party"), NULL),
                /*C*/ NULL);
        }
        static ActionNode* lesser_heal(PlayerbotAI* ai)
        {
            return new ActionNode ("lesser heal",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NextAction::array(0, new NextAction("relocate"), NULL),
                /*C*/ NULL);
        }
        static ActionNode* lesser_heal_on_party(PlayerbotAI* ai)
        {
            return new ActionNode ("lesser heal on party",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NextAction::array(0, new NextAction("relocate"), NULL),
                /*C*/ NULL);
        }
        static ActionNode* lesser_heal_on_master(PlayerbotAI* ai)
        {
            return new ActionNode ("lesser heal on master",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NextAction::array(0, new NextAction("relocate"), NULL),
                /*C*/ NULL);
        }
        static ActionNode* flash_heal(PlayerbotAI* ai)
        {
            return new ActionNode ("flash heal",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NextAction::array(0, new NextAction("greater heal"), NULL),
                /*C*/ NULL);
        }
        static ActionNode* flash_heal_on_party(PlayerbotAI* ai)
        {
            return new ActionNode ("flash heal on party",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NextAction::array(0, new NextAction("greater heal on party"), NULL),
                /*C*/ NULL);
        }
        static ActionNode* flash_heal_on_master(PlayerbotAI* ai)
        {
            return new ActionNode ("flash heal on master",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NextAction::array(0, new NextAction("greater heal on master"), NULL),
                /*C*/ NULL);
        }
        static ActionNode* prayer_of_mending(PlayerbotAI* ai)
        {
            return new ActionNode ("prayer of mending",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NextAction::array(0, new NextAction("renew"), NULL),
                /*C*/ NULL);
        }
        static ActionNode* prayer_of_mending_on_party(PlayerbotAI* ai)
        {
            return new ActionNode ("prayer of mending on party",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NextAction::array(0, new NextAction("renew on party"), NULL),
                /*C*/ NULL);
        }
        static ActionNode* prayer_of_mending_on_master(PlayerbotAI* ai)
        {
            return new ActionNode ("prayer of mending on master",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NextAction::array(0, new NextAction("renew on master"), NULL),
                /*C*/ NULL);
        }
        static ActionNode* desperate_prayer(PlayerbotAI* ai)
        {
            return new ActionNode ("desperate prayer",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NextAction::array(0, new NextAction("power word: shield"), NULL),
                /*C*/ NULL);
        }
        static ActionNode* hymn_of_hope(PlayerbotAI* ai)
        {
            return new ActionNode ("hymn of hope",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NextAction::array(0, new NextAction("mana potion"), NULL),
                /*C*/ NULL);
        }
         static ActionNode* divine_hymn(PlayerbotAI* ai)
        {
            return new ActionNode ("divine_hymn",
                /*P*/ NextAction::array(0, new NextAction("remove shadowform"), NULL),
                /*A*/ NextAction::array(0, new NextAction("circle of healing"), NULL),
                /*C*/ NULL);
        }

        static ActionNode* psychic_scream(PlayerbotAI* ai)
        {
            return new ActionNode ("psychic scream",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("flee"), NULL),
                /*C*/ NULL);
        }
        static ActionNode* fade(PlayerbotAI* ai)
        {
            return new ActionNode ("fade",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("power word: shield"), NULL),
                /*C*/ NULL);
        }
        static ActionNode* power_infusion(PlayerbotAI* ai)
        {
            return new ActionNode ("power infusion",
                /*P*/ NULL,
                /*A*/ NULL,
                /*C*/ NULL);
        }
        static ActionNode* penance(PlayerbotAI* ai)
        {
            return new ActionNode ("penance",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("flash heal"), NULL),
                /*C*/ NULL);
        }
        static ActionNode* penance_on_party(PlayerbotAI* ai)
        {
            return new ActionNode ("penance on party",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("flash heal on party"), NULL),
                /*C*/ NULL);
        }
        static ActionNode* penance_on_master(PlayerbotAI* ai)
        {
            return new ActionNode ("penance on master",
                /*P*/ NULL,
                /*A*/ NextAction::array(0, new NextAction("flash heal on master"), NULL),
                /*C*/ NULL);
        }
    };
};
