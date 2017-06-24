#pragma once

#include "../Action.h"
#include "../../PlayerbotAIConfig.h"

namespace ai
{
	class UseItemAction : public Action {
	public:
		UseItemAction(PlayerbotAI* ai, string name = "use", bool selfOnly = false) : Action(ai, name), selfOnly(selfOnly) {}

    public:
        virtual bool Execute(Event event);
        virtual bool isPossible();
        void setTargetMainhand();
        void setTargetOffhand();
        void setTargetUnit(Unit* target) {actionUnit = target;}
        virtual bool hasMultipliers() {return false;}
    private:
        bool UseItemAuto(Item* item);
        bool UseItemOnGameObject(Item* item, ObjectGuid go);
        bool UseItemOnItem(Item* item, Item* itemTarget);
        bool UseItem(Item* item, ObjectGuid go, Item* itemTarget);
        bool UseItemOnUnit(Item* item, Unit* unitTarget);
        bool UseGameObject(ObjectGuid guid);
    private:
        bool selfOnly;
        uint8 targetSlot;
        Unit* actionUnit;
    };

    class UseSpellItemAction : public UseItemAction {
    public:
        UseSpellItemAction(PlayerbotAI* ai, string name, bool selfOnly = false) : UseItemAction(ai, name, selfOnly) {}

    public:
        virtual bool isUseful();
    };

    class UseHealingPotion : public UseItemAction {
    public:
        UseHealingPotion(PlayerbotAI* ai) : UseItemAction(ai, "healing potion") {}
        virtual bool isUseful() { return AI_VALUE2(bool, "combat", "self target") && AI_VALUE2(uint8, "health", "self target") < sPlayerbotAIConfig.almostDead; }
    };

    class UseManaPotion : public UseItemAction
    {
    public:
        UseManaPotion(PlayerbotAI* ai) : UseItemAction(ai, "mana potion") {}
        virtual bool isUseful() { return AI_VALUE2(bool, "combat", "self target") && AI_VALUE2(uint8, "mana", "self target") < sPlayerbotAIConfig.lowMana; }
    };

    class BandageAction : public UseItemAction
    {
    public:
        BandageAction(PlayerbotAI* ai) : UseItemAction(ai, "bandage") {}
        virtual bool isUseful() { return AI_VALUE2(uint8, "health", "self target") < sPlayerbotAIConfig.almostDead;}
    };

 class UseBombAction : public UseItemAction
    {
    public:
        UseBombAction(PlayerbotAI* ai) : UseItemAction(ai, "bomb") {}
    };
}
