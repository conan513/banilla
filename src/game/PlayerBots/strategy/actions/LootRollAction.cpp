#include "../../../botpch.h"
#include "../../playerbot.h"
#include "LootRollAction.h"


using namespace ai;

bool LootRollAction::Execute(Event event)
{
	Player *bot = QueryItemUsageAction::ai->GetBot();

	WorldPacket p(event.getPacket()); //WorldPacket packet for CMSG_LOOT_ROLL, (8+4+1)
	ObjectGuid guid;
	uint32 slot;
	uint8 rollType;
	p.rpos(0); //reset packet pointer
	p >> guid; //guid of the item rolled
	p >> slot; //number of players invited to roll
	p >> rollType; //need,greed or pass on roll

	Group* group = bot->GetGroup();
	if (!group)
		return false;
	
	// check that the bot did not already vote
	if (rollType >= ROLL_NOT_EMITED_YET)
		return;

	Loot* loot = sLootMgr.GetLoot(bot, guid);

	if (!loot)
	{
		sLog.outError("LootMgr::PlayerVote> Error cannot get loot object info!");
		return;
	}

	LootItem* lootItem = loot->GetLootItemInSlot(slot);
	RollVote vote = ROLL_PASS;

	ItemPrototype const *proto = sItemStorage.LookupEntry<ItemPrototype>(lootItem->itemId);
	if (proto)
	{	
		QueryItemUsage(proto);
		if (IsLootAllowed(lootItem->itemId, bot->GetPlayerbotAI()))
		{
			vote = ROLL_NEED;
		}
	}

	switch (group->GetLootMethod())
	{
	case MASTER_LOOT:
	case FREE_FOR_ALL:
		sLootMgr.PlayerVote(bot, guid, slot, ROLL_PASS);
		break;
	default:
		sLootMgr.PlayerVote(bot, guid, slot, vote);
		break;
	}

	return true;
}