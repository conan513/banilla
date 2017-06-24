#include "../../../botpch.h"
#include "../../playerbot.h"
#include "ChatShortcutActions.h"
#include "../../PlayerbotAIConfig.h"

using namespace ai;

bool FollowChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    ai->Reset();
    ai->ChangeStrategy("+follow,-disperse,-passive", BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("-follow,-disperse,-passive", BOT_STATE_COMBAT);
    if (bot->GetMapId() != master->GetMapId() || bot->GetDistance(master) > sPlayerbotAIConfig.sightDistance)
    {
        ai->TellMaster("I will not follow you - too far away");
        return true;
    }
    ai->TellMaster("Following");
    return true;
}

bool MoveBehindChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    if (bot->GetMapId() != master->GetMapId() || bot->GetDistance(master) > sPlayerbotAIConfig.sightDistance)
    {
        ai->TellMaster("can not get behind target - too far away");
        return true;
    }
    ai->DoSpecificAction("move behind");
    ai->TellMaster("Moving behind target");
    return true;
}

bool RepositionChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    if (bot->GetMapId() != master->GetMapId() || bot->GetDistance(master) > sPlayerbotAIConfig.sightDistance)
    {
        ai->TellMaster("can not reposition - too far away");
        return true;
    }
    ai->DoSpecificAction("reposition");
    ai->TellMaster("reposition");
    return true;
}

bool DisperseChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    ai->ChangeStrategy("-follow,+disperse,-passive", BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("-follow,+disperse,-passive", BOT_STATE_COMBAT);

    if (bot->GetMapId() != master->GetMapId() || bot->GetDistance(master) > sPlayerbotAIConfig.sightDistance)
    {
        ai->TellMaster("can not disperse - too far away");
        return true;
    }
    ai->DoSpecificAction("disperse");
    ai->TellMaster("disperse");
    return true;
}

bool MoveToPointChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    if (bot->GetMapId() != master->GetMapId() || bot->GetDistance(master) > sPlayerbotAIConfig.sightDistance)
    {
        ai->TellMaster("can not move to point - too far away");
        return true;
    }
    ai->DoSpecificAction("move to point");
    ai->TellMaster("Moving to point");
    return true;
}

bool BoostChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    if (bot->GetMapId() != master->GetMapId() || bot->GetDistance(master) > sPlayerbotAIConfig.sightDistance)
    {
        ai->TellMaster("can not move to point - too far away");
        return true;
    }
    ai->DoSpecificAction("boost");
    ai->TellMaster("Moving to point");
    return true;
}

bool BurstChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    if (bot->GetMapId() != master->GetMapId() || bot->GetDistance(master) > sPlayerbotAIConfig.sightDistance)
    {
        ai->TellMaster("can not move to point - too far away");
        return true;
    }
    ai->DoSpecificAction("burst");
    ai->TellMaster("Moving to point");
    return true;
}

bool StayChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    ai->Reset();
    ai->ChangeStrategy("+stay,-passive", BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("-follow,-passive", BOT_STATE_COMBAT);
    ai->TellMaster("Staying");
    return true;
}

bool StopAttackChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    ai->Reset();
    ai->ChangeStrategy("+passive", BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("+passive", BOT_STATE_COMBAT);
    ai->TellMaster("Stop attack");
    return true;
}

bool ResumeAttackChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    ai->Reset();
    ai->ChangeStrategy("-passive", BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("-passive", BOT_STATE_COMBAT);
    ai->TellMaster("Resume attack");
    return true;
}

bool FleeChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    ai->Reset();
    ai->ChangeStrategy("+follow,+disperse,+passive", BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("+follow,+disperse,+passive", BOT_STATE_COMBAT);
    if (bot->GetMapId() != master->GetMapId() || bot->GetDistance(master) > sPlayerbotAIConfig.sightDistance)
    {
        ai->TellMaster("I will not flee with you - too far away");
        return true;
    }
    ai->TellMaster("Fleeing");
    return true;
}

bool GoawayChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    ai->Reset();
    ai->ChangeStrategy("+runaway,+disperse", BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("+runaway,+disperse", BOT_STATE_COMBAT);
    ai->TellMaster("Running away");
    return true;
}

bool GrindChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    ai->Reset();
    ai->ChangeStrategy("+grind,-passive", BOT_STATE_NON_COMBAT);
    ai->TellMaster("Grinding");
    return true;
}

bool TankAttackChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    if (!ai->IsTank(bot))
        return false;

    ai->Reset();
    ai->ChangeStrategy("-passive", BOT_STATE_NON_COMBAT);
    ai->ChangeStrategy("-passive", BOT_STATE_COMBAT);
    ai->TellMaster("Attacking");
    return true;
}

bool MaxDpsChatShortcutAction::Execute(Event event)
{
    Player* master = GetMaster();
    if (!master)
        return false;

    ai->Reset();
    ai->ChangeStrategy("-threat,-conserve mana,-cast time,+dps debuff", BOT_STATE_COMBAT);
    ai->TellMaster("Max DPS");
    return true;
}
