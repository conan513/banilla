#pragma once

#include "../Action.h"
#include "InventoryAction.h"

namespace ai
{
    class FollowChatShortcutAction : public Action
    {
    public:
        FollowChatShortcutAction(PlayerbotAI* ai) : Action(ai, "follow chat shortcut") {}
        virtual bool Execute(Event event);
    };

    class MoveBehindChatShortcutAction : public Action
    {
    public:
        MoveBehindChatShortcutAction(PlayerbotAI* ai) : Action(ai, "move behind chat shortcut") {}
        virtual bool Execute(Event event);
    };

    class MoveToPointChatShortcutAction : public Action
    {
    public:
        MoveToPointChatShortcutAction(PlayerbotAI* ai) : Action(ai, "move to point chat shortcut") {}
        virtual bool Execute(Event event);
    };

    class BoostChatShortcutAction : public Action
    {
    public:
        BoostChatShortcutAction(PlayerbotAI* ai) : Action(ai, "boost chat shortcut") {}
        virtual bool Execute(Event event);
    };

    class BurstChatShortcutAction : public Action
    {
    public:
        BurstChatShortcutAction(PlayerbotAI* ai) : Action(ai, "burst chat shortcut") {}
        virtual bool Execute(Event event);
    };

    class RepositionChatShortcutAction : public Action
    {
    public:
        RepositionChatShortcutAction(PlayerbotAI* ai) : Action(ai, "reposition chat shortcut") {}
        virtual bool Execute(Event event);
    };

    class StayChatShortcutAction : public Action
    {
    public:
        StayChatShortcutAction(PlayerbotAI* ai) : Action(ai, "stay chat shortcut") {}
        virtual bool Execute(Event event);
    };

    class StopAttackChatShortcutAction : public Action
    {
    public:
        StopAttackChatShortcutAction(PlayerbotAI* ai) : Action(ai, "stop attack chat shortcut") {}
        virtual bool Execute(Event event);
    };

    class ResumeAttackChatShortcutAction : public Action
    {
    public:
        ResumeAttackChatShortcutAction(PlayerbotAI* ai) : Action(ai, "resume attack chat shortcut") {}
        virtual bool Execute(Event event);
    };

    class FleeChatShortcutAction : public Action
    {
    public:
        FleeChatShortcutAction(PlayerbotAI* ai) : Action(ai, "flee chat shortcut") {}
        virtual bool Execute(Event event);
    };

    class DisperseChatShortcutAction : public Action
    {
    public:
        DisperseChatShortcutAction(PlayerbotAI* ai) : Action(ai, "disperse chat shortcut") {}
        virtual bool Execute(Event event);
    };

    class GoawayChatShortcutAction : public Action
    {
    public:
        GoawayChatShortcutAction(PlayerbotAI* ai) : Action(ai, "runaway chat shortcut") {}
        virtual bool Execute(Event event);
    };

    class GrindChatShortcutAction : public Action
    {
    public:
        GrindChatShortcutAction(PlayerbotAI* ai) : Action(ai, "grind chat shortcut") {}
        virtual bool Execute(Event event);
    };

    class TankAttackChatShortcutAction : public Action
    {
    public:
        TankAttackChatShortcutAction(PlayerbotAI* ai) : Action(ai, "tank attack chat shortcut") {}
        virtual bool Execute(Event event);
    };

    class MaxDpsChatShortcutAction : public Action
    {
    public:
        MaxDpsChatShortcutAction(PlayerbotAI* ai) : Action(ai, "max dps chat shortcut") {}
        virtual bool Execute(Event event);
    };

}
