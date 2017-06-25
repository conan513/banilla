#include "../../../botpch.h"
#include "../../playerbot.h"
#include "InventoryAction.h"

#include "../values/ItemCountValue.h"

using namespace ai;


class FindPotionVisitor : public FindUsableItemVisitor
{
public:
    FindPotionVisitor(Player* bot, uint32 effectId) : FindUsableItemVisitor(bot), effectId(effectId) {}

    virtual bool Accept(const ItemPrototype* proto)
    {
		if (proto->Class == ITEM_CLASS_CONSUMABLE && (proto->SubClass == ITEM_SUBCLASS_POTION || proto->SubClass == ITEM_SUBCLASS_FLASK))
		{
			for (int j = 0; j < MAX_ITEM_PROTO_SPELLS; j++)
			{
				const SpellEntry* const spellInfo = sSpellMgr.GetSpellEntry(proto->Spells[j].SpellId);
				if (!spellInfo)
					return false;

				for (int i = 0; i < 3; i++)
				{
					if (spellInfo->Effect[i] == effectId)
						return true;
				}
			}
		}
		return false;
    }

private:
    uint32 effectId;
};


class FindFoodVisitor : public FindUsableItemVisitor
{
public:
    FindFoodVisitor(Player* bot, uint32 spellCategory) : FindUsableItemVisitor(bot)
    {
        this->spellCategory = spellCategory;
    }

    virtual bool Accept(const ItemPrototype* proto)
    {
        return proto->Class == ITEM_CLASS_CONSUMABLE &&
            (proto->SubClass == ITEM_SUBCLASS_CONSUMABLE || proto->SubClass == ITEM_SUBCLASS_FOOD) &&
            proto->Spells[0].SpellCategory == spellCategory;
    }

private:
    uint32 spellCategory;
};


class FindBandageVisitor : public FindUsableItemVisitor
{
public:
    FindBandageVisitor(Player* bot) : FindUsableItemVisitor(bot){}

    virtual bool Accept(const ItemPrototype* proto)
    {
        return proto->Class == ITEM_CLASS_CONSUMABLE &&
            proto->SubClass == ITEM_SUBCLASS_BANDAGE;
    }
};

class FindBombVisitor : public FindUsableItemVisitor
{
public:
    FindBombVisitor(Player* bot) : FindUsableItemVisitor(bot){}

    virtual bool Accept(const ItemPrototype* proto)
    {
        return proto->Class == ITEM_CLASS_CONSUMABLE &&
            proto->SubClass == ITEM_SUBCLASS_EXPLOSIVES;
    }
};


void InventoryAction::IterateItems(IterateItemsVisitor* visitor, IterateItemsMask mask)
{
    if (mask & ITERATE_ITEMS_IN_BAGS)
        IterateItemsInBags(visitor);

    if (mask & ITERATE_ITEMS_IN_EQUIP)
        IterateItemsInEquip(visitor);
}

void InventoryAction::IterateItemsInBags(IterateItemsVisitor* visitor)
{


    for(int i = INVENTORY_SLOT_ITEM_START; i < INVENTORY_SLOT_ITEM_END; ++i)
        if (Item *pItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            if (!visitor->Visit(pItem))
                return;

    for(int i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
        if (Bag *pBag = (Bag*)bot->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
            for(uint32 j = 0; j < pBag->GetBagSize(); ++j)
                if (Item* pItem = pBag->GetItemByPos(j))
                    if (!visitor->Visit(pItem))
                        return;
}

void InventoryAction::IterateItemsInEquip(IterateItemsVisitor* visitor)
{
    for (uint8 slot = EQUIPMENT_SLOT_START; slot < EQUIPMENT_SLOT_END; slot++)
    {
        Item* const pItem = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if(!pItem)
            continue;

        if (!visitor->Visit(pItem))
            return;
    }
}

bool compare_items(const ItemPrototype *proto1, const ItemPrototype *proto2)
{
    if (proto1->Class != proto2->Class)
        return proto1->Class > proto2->Class;

    if (proto1->SubClass != proto2->SubClass)
        return proto1->SubClass < proto2->SubClass;

    if (proto1->Quality != proto2->Quality)
        return proto1->Quality < proto2->Quality;

    if (proto1->ItemLevel != proto2->ItemLevel)
        return proto1->ItemLevel > proto2->ItemLevel;

    return false;
}

bool compare_items_by_level(const Item* item1, const Item* item2)
{
    return compare_items(item1->GetProto(), item2->GetProto());
}

void InventoryAction::TellItems(map<uint32, int> itemMap)
{
    list<ItemPrototype const*> items;
    for (map<uint32, int>::iterator i = itemMap.begin(); i != itemMap.end(); i++)
    {
        items.push_back(sObjectMgr.GetItemPrototype(i->first));
    }

    items.sort(compare_items);

    uint32 oldClass = -1;
    for (list<ItemPrototype const*>::iterator i = items.begin(); i != items.end(); i++)
    {
        ItemPrototype const *proto = *i;

        if (proto->Class != oldClass)
        {
            oldClass = proto->Class;
            switch (proto->Class)
            {
            case ITEM_CLASS_CONSUMABLE:
                ai->TellMaster("--- consumable ---");
                break;
            case ITEM_CLASS_CONTAINER:
                ai->TellMaster("--- container ---");
                break;
            case ITEM_CLASS_WEAPON:
                ai->TellMaster("--- weapon ---");
                break;
            case ITEM_CLASS_GEM:
                ai->TellMaster("--- gem ---");
                break;
            case ITEM_CLASS_ARMOR:
                ai->TellMaster("--- armor ---");
                break;
            case ITEM_CLASS_REAGENT:
                ai->TellMaster("--- reagent ---");
                break;
            case ITEM_CLASS_PROJECTILE:
                ai->TellMaster("--- projectile ---");
                break;
            case ITEM_CLASS_TRADE_GOODS:
                ai->TellMaster("--- trade goods ---");
                break;
            case ITEM_CLASS_GENERIC:
                ai->TellMaster("--- generic ---");
                break;
            case ITEM_CLASS_RECIPE:
                ai->TellMaster("--- recipe ---");
                break;
            case ITEM_CLASS_MONEY:
                ai->TellMaster("--- money ---");
                break;
            case ITEM_CLASS_QUIVER:
                ai->TellMaster("--- quiver ---");
                break;
            case ITEM_CLASS_QUEST:
                ai->TellMaster("--- quest items ---");
                break;
            case ITEM_CLASS_KEY:
                ai->TellMaster("--- keys ---");
                break;
            case ITEM_CLASS_PERMANENT:
                ai->TellMaster("--- permanent ---");
                break;
            case ITEM_CLASS_JUNK:
                ai->TellMaster("--- other ---");
                break;
            }
        }

        TellItem(proto, itemMap[proto->ItemId]);
    }
}

void InventoryAction::TellItem(ItemPrototype const * proto, int count)
{
    ai->TellMaster(chat->formatItem(proto, count));
}

list<Item*> InventoryAction::parseItems(string text)
{
    set<Item*> found;
    size_t pos = text.find(" ");
    int count = pos!=string::npos ? atoi(text.substr(pos + 1).c_str()) : TRADE_SLOT_TRADED_COUNT;
    if (count < 1) count = 1;
    else if (count > TRADE_SLOT_TRADED_COUNT) count = TRADE_SLOT_TRADED_COUNT;

    if (text == "food")
    {
        FindFoodVisitor visitor(bot, 11);
        IterateItems(&visitor, ITERATE_ITEMS_IN_BAGS);
        found.insert(visitor.GetResult().begin(), visitor.GetResult().end());
    }

    if (text == "drink")
    {
        FindFoodVisitor visitor(bot, 59);
        IterateItems(&visitor, ITERATE_ITEMS_IN_BAGS);
        found.insert(visitor.GetResult().begin(), visitor.GetResult().end());
    }

    if (text == "mana potion")
    {
        FindPotionVisitor visitor(bot, SPELL_EFFECT_ENERGIZE);
        IterateItems(&visitor, ITERATE_ITEMS_IN_BAGS);
        found.insert(visitor.GetResult().begin(), visitor.GetResult().end());
    }

    if (text == "bandage")
    {
        FindBandageVisitor visitor(bot);
        IterateItems(&visitor, ITERATE_ITEMS_IN_BAGS);
        found.insert(visitor.GetResult().begin(), visitor.GetResult().end());
    }

    if (text == "bomb")
    {
        FindBombVisitor visitor(bot);
        IterateItems(&visitor, ITERATE_ITEMS_IN_BAGS);
        found.insert(visitor.GetResult().begin(), visitor.GetResult().end());
    }

    if (text == "healing potion")
    {
        FindPotionVisitor visitor(bot, SPELL_EFFECT_HEAL);
        IterateItems(&visitor, ITERATE_ITEMS_IN_BAGS);
        found.insert(visitor.GetResult().begin(), visitor.GetResult().end());
    }

	FindNamedItemVisitor visitor(bot, text);
    IterateItems(&visitor, ITERATE_ITEMS_IN_BAGS);
    found.insert(visitor.GetResult().begin(), visitor.GetResult().end());

    uint32 quality = chat->parseItemQuality(text);
    if (quality != MAX_ITEM_QUALITY)
    {
        FindItemsToTradeByQualityVisitor visitor(quality, count);
        IterateItems(&visitor);
        found.insert(visitor.GetResult().begin(), visitor.GetResult().end());
    }

    uint32 itemClass = MAX_ITEM_CLASS, itemSubClass = 0;
    if (chat->parseItemClass(text, &itemClass, &itemSubClass))
    {
        FindItemsToTradeByClassVisitor visitor(itemClass, itemSubClass, count);
        IterateItems(&visitor);
        found.insert(visitor.GetResult().begin(), visitor.GetResult().end());
    }

    uint32 fromSlot = chat->parseSlot(text);
    if (fromSlot != EQUIPMENT_SLOT_END)
    {
        Item* item = bot->GetItemByPos(INVENTORY_SLOT_BAG_0, fromSlot);
        if (item)
            found.insert(item);
    }

    ItemIds ids = chat->parseItems(text);
    for (ItemIds::iterator i = ids.begin(); i != ids.end(); i++)
    {
        FindItemByIdVisitor visitor(*i);
        IterateItems(&visitor, ITERATE_ALL_ITEMS);
        found.insert(visitor.GetResult().begin(), visitor.GetResult().end());
    }

    list<Item*> result;
    for (set<Item*>::iterator i = found.begin(); i != found.end(); ++i)
        result.push_back(*i);

    result.sort(compare_items_by_level);

    return result;
}

bool InventoryAction::UseItem(Item* item,  Item* itemTarget)
{
    if (bot->CanUseItem(item) != EQUIP_ERR_OK)
        return false;

    if (bot->IsNonMeleeSpellCasted(true))
        return false;

    uint8 bagIndex = item->GetBagSlot();
    uint8 slot = item->GetSlot();
    uint8 cast_count = 1;
    uint64 item_guid = item->GetGUID();
    uint32 glyphIndex = 0;
    uint8 unk_flags = 0;

	WorldPacket* const packet = new WorldPacket(CMSG_USE_ITEM, 1 + 1 + 1 + 4 + 8 + 4 + 1 + 8 + 1);
    *packet << bagIndex << slot << cast_count << uint32(0) << item_guid
        << glyphIndex << unk_flags;

    bool targetSelected = false;
    ostringstream out; out << "Using " << chat->formatItem(item->GetProto());
    if (item->GetProto()->Stackable)
    {
        uint32 count = item->GetCount();
        if (count > 1)
            out << " (" << count << " available) ";
        else
            out << " (the last one!)";
    }


    if (itemTarget)
    {
            uint32 targetFlag = TARGET_FLAG_ITEM;
            *packet << targetFlag;
            packet->appendPackGUID(itemTarget->GetGUID());
            out << " on " << chat->formatItem(itemTarget->GetProto());
            targetSelected = true;
    }

    MotionMaster &mm = *bot->GetMotionMaster();
    mm.Clear();
    bot->clearUnitState( UNIT_STAT_CHASE );
    bot->clearUnitState( UNIT_STAT_FOLLOW );

    if (bot->IsMoving())
        return false;

    for (int i=0; i<MAX_ITEM_PROTO_SPELLS; i++)
    {
        uint32 spellId = item->GetProto()->Spells[i].SpellId;
        if (!spellId)
            continue;

        if (!ai->CanCastSpell(spellId, bot, false))
            continue;

		const SpellEntry* const pSpellInfo = sSpellMgr.GetSpellEntry(spellId);
		if (pSpellInfo->Targets & TARGET_FLAG_ITEM)
        {
            Item* itemForSpell = AI_VALUE2(Item*, "item for spell", spellId);
            if (!itemForSpell)
                continue;

            if (itemForSpell->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT))
                continue;

            *packet << TARGET_FLAG_ITEM;
             packet->appendPackGUID(itemForSpell->GetGUID());
             targetSelected = true;
             out << " on "<< chat->formatItem(itemForSpell->GetProto());


			 Spell *spell = new Spell(bot, pSpellInfo, false);
            ai->WaitForSpellCast(spell);
            delete spell;
        }
        else
        {
            *packet << TARGET_FLAG_SELF;
            targetSelected = true;
            out << " on self";
        }
        break;
    }

    if (!targetSelected)
        return false;

    if (item->GetProto()->Class == ITEM_CLASS_CONSUMABLE && item->GetProto()->SubClass == ITEM_SUBCLASS_FOOD)
    {
        if (bot->isInCombat())
            return false;

        ai->InterruptSpell();
        ai->SetNextCheckDelay(30000);
    }
    else
    {
        ai->InterruptSpell();
        ai->SetNextCheckDelay(3000);
    }

    ai->TellMasterNoFacing(out.str());
    bot->GetSession()->QueuePacket(std::move(packet));
    return true;
}
