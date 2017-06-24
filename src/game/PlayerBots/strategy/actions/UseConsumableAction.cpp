#include "../../../botpch.h"
#include "../../playerbot.h"
#include "UseConsumableAction.h"
#include "UseItemAction.h"

#include "../values/ItemCountValue.h"

using namespace ai;

class FindConsumableVisitor : public IterateItemsVisitor {
public:
    FindConsumableVisitor(Player* bot) : IterateItemsVisitor(), bot(bot)
    {
    }

    virtual bool Visit(Item* item)
    {
        if (bot->CanUseItem(item->GetProto()) != EQUIP_ERR_OK)
            return true;

        const ItemPrototype* proto = item->GetProto();

        if (proto->Class != ITEM_CLASS_CONSUMABLE)
            return true;

        if (proto->SubClass != ITEM_SUBCLASS_ELIXIR &&
            proto->SubClass != ITEM_SUBCLASS_FLASK &&
            proto->SubClass != ITEM_SUBCLASS_SCROLL &&
            proto->SubClass != ITEM_SUBCLASS_FOOD &&
            proto->SubClass != ITEM_SUBCLASS_CONSUMABLE_OTHER)
            return true;

        for (int i=0; i<MAX_ITEM_PROTO_SPELLS; i++)
        {
            uint32 spellId = proto->Spells[i].SpellId;
            if (!spellId)
                continue;

            if (bot->HasAura(spellId))
                return true;

            Item* itemForSpell = *bot->GetPlayerbotAI()->GetAiObjectContext()->GetValue<Item*>("item for spell", spellId);
            if (itemForSpell && itemForSpell->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT))
                return true;

            if (items.find(proto->SubClass) == items.end())
                items[proto->SubClass] = list<Item*>();

            items[proto->SubClass].push_back(item);
            break;
        }

        return true;
    }

public:
    map<uint32, list<Item*> > items;

private:
    Player* bot;
};

void UseConsumableAction::TellHeader(uint32 subClass)
{
    switch (subClass)
    {
    case ITEM_SUBCLASS_ELIXIR:
        ai->TellMaster("--- Buffed with Elixir ---");
        return;
    case ITEM_SUBCLASS_FLASK:
        ai->TellMaster("--- Buffed with Flask ---");
        return;
    case ITEM_SUBCLASS_SCROLL:
        ai->TellMaster("--- Buffed with Scroll ---");
        return;
    case ITEM_SUBCLASS_FOOD:
        ai->TellMaster("--- Buffed with Food ---");
        return;
    case ITEM_SUBCLASS_GENERIC:
        ai->TellMaster("--- Buffed with Other ---");
        return;
    }
}


bool UseConsumableAction::Execute(Event event)
{
    string text = event.getParam();

    FindConsumableVisitor visitor(bot);
    IterateItems(&visitor);

    uint32 oldSubClass = -1;
    for (map<uint32, list<Item*> >::iterator i = visitor.items.begin(); i != visitor.items.end(); ++i)
    {
        list<Item*> items = i->second;

        uint32 subClass = i->first;
        if (oldSubClass != subClass)
        {
            if (!items.empty())
                TellHeader(subClass);
            oldSubClass = subClass;
        }
        for (list<Item*>::iterator j = items.begin(); j != items.end(); ++j)
        {
            Item* item = *j;

            switch (subClass)
            {
                case ITEM_SUBCLASS_ELIXIR:
                    if (UseItem(item,NULL))
                    {
                        ostringstream out;
                        out << chat->formatItem(item->GetProto(), item->GetCount());
                        ai->TellMaster(out);
                        }
                case ITEM_SUBCLASS_FLASK:
                    if (UseItem(item,NULL))
                    {
                        ostringstream out;
                        out << chat->formatItem(item->GetProto(), item->GetCount());
                        ai->TellMaster(out);
                        }
                case ITEM_SUBCLASS_SCROLL:
                    if (UseItem(item,NULL))
                    {
                        ostringstream out;
                        out << chat->formatItem(item->GetProto(), item->GetCount());
                        ai->TellMaster(out);
                        }
                case ITEM_SUBCLASS_FOOD:
                    if (UseItem(item,NULL))
                    {
                        ostringstream out;
                        out << chat->formatItem(item->GetProto(), item->GetCount());
                        ai->TellMaster(out);
                        }
                case ITEM_SUBCLASS_GENERIC:
                    if (UseItem(item,NULL))
                    {
                        ostringstream out;
                        out << chat->formatItem(item->GetProto(), item->GetCount());
                        ai->TellMaster(out);
                        }
                }
        }
    }

    return true;
}

class FindEnhancementVisitor : public IterateItemsVisitor {
public:
    FindEnhancementVisitor(Player* bot) : IterateItemsVisitor(), bot(bot)
    {
    }

    virtual bool Visit(Item* item)
    {
        if (bot->CanUseItem(item->GetProto()) != EQUIP_ERR_OK)
            return true;

        const ItemPrototype* proto = item->GetProto();

        if (proto->Class != ITEM_CLASS_CONSUMABLE)
            return true;

        if (proto->SubClass != ITEM_SUBCLASS_ITEM_ENHANCEMENT)
            return true;

        for (int i=0; i<MAX_ITEM_PROTO_SPELLS; i++)
        {
            uint32 spellId = proto->Spells[i].SpellId;
            if (!spellId)
                continue;

            if (bot->HasAura(spellId))
                return true;

            Item* itemForSpell = *bot->GetPlayerbotAI()->GetAiObjectContext()->GetValue<Item*>("item for spell", spellId);
            if (itemForSpell && itemForSpell->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT))
                return true;

            if (items.find(proto->SubClass) == items.end())
                items[proto->SubClass] = list<Item*>();

            items[proto->SubClass].push_back(item);
            break;
        }

        return true;
    }

public:
    map<uint32, list<Item*> > items;

private:
    Player* bot;
};

void UseEnhancementAction::TellHeader(uint32 subClass)
{
    switch (subClass)
    {
    case ITEM_SUBCLASS_ITEM_ENHANCEMENT:
        ai->TellMaster("--- Applied Enhancement ---");
        return;
    }
}


bool UseEnhancementAction::Execute(Event event)
{
    string text = event.getParam();

    FindEnhancementVisitor visitor(bot);
    IterateItems(&visitor);

    uint32 oldSubClass = -1;
    for (map<uint32, list<Item*> >::iterator i = visitor.items.begin(); i != visitor.items.end(); ++i)
    {
        list<Item*> items = i->second;

        uint32 subClass = i->first;
        if (oldSubClass != subClass)
        {
            if (!items.empty())
                TellHeader(subClass);
            oldSubClass = subClass;
        }
        for (list<Item*>::iterator j = items.begin(); j != items.end(); ++j)
        {
            Item* item = *j;

            switch (subClass)
            {
                case ITEM_SUBCLASS_ITEM_ENHANCEMENT:
                    if (UseItem(item,bot->GetItemByPos(EQUIPMENT_SLOT_MAINHAND)))
                    {
                        ostringstream out;
                        out << chat->formatItem(item->GetProto(), item->GetCount());
                        ai->TellMaster(out);
                        }
                    if (UseItem(item,bot->GetItemByPos(EQUIPMENT_SLOT_OFFHAND)))
                    {
                        ostringstream out;
                        out << chat->formatItem(item->GetProto(), item->GetCount());
                        ai->TellMaster(out);
                        }
                }
        }
    }

    return true;
}

