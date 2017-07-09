#include "../../../botpch.h"
#include "../../playerbot.h"
#include "GuildBankAction.h"

#include "../values/ItemCountValue.h"
#include "Guild.h"
#include "GuildMgr.h"

using namespace std;
using namespace ai;

bool GuildBankAction::Execute(Event event)
{
    return false;
}

bool GuildBankAction::Execute(string text, GameObject* bank)
{
	return true;
}

bool GuildBankAction::MoveFromCharToBank(Item* item, GameObject* bank)
{
    return true;
}
