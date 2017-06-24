#include "../../pchdef.h"
#include "../playerbot.h"
#include "AiObjectContext.h"
#include "NamedObjectContext.h"
#include "StrategyContext.h"
#include "triggers/TriggerContext.h"
#include "actions/ActionContext.h"
#include "triggers/ChatTriggerContext.h"
#include "actions/ChatActionContext.h"
#include "triggers/WorldPacketTriggerContext.h"
#include "actions/WorldPacketActionContext.h"
#include "values/ValueContext.h"

using namespace ai;

AiObjectContext::AiObjectContext(PlayerbotAI* ai) : PlayerbotAIAware(ai)
{
    strategyContext = new ai::StrategyContext();
    movementStrategyContext = new ai::MovementStrategyContext();
    assistStrategyContext = new ai::AssistStrategyContext();
    questStrategyContext = new ai::QuestStrategyContext();

    actionContext = new ai::ActionContext();
    chatActionContext = new ai::ChatActionContext();
    worldPacketActionContext = new ai::WorldPacketActionContext();

    triggerContext = new ai::TriggerContext();
    chatTriggerContext = new ai::ChatTriggerContext();
    worldPacketTriggerContext = new ai::WorldPacketTriggerContext();

    valueContext = new ai::ValueContext();

    strategyContexts.Add(strategyContext);
    strategyContexts.Add(movementStrategyContext);
    strategyContexts.Add(assistStrategyContext);
    strategyContexts.Add(questStrategyContext);

    actionContexts.Add(actionContext);
    actionContexts.Add(chatActionContext);
    actionContexts.Add(worldPacketActionContext);

    triggerContexts.Add(triggerContext);
    triggerContexts.Add(chatTriggerContext);
    triggerContexts.Add(worldPacketTriggerContext);

    valueContexts.Add(valueContext);
}

AiObjectContext::~AiObjectContext()
{
    strategyContexts.Remove(strategyContext);
    strategyContexts.Remove(movementStrategyContext);
    strategyContexts.Remove(assistStrategyContext);
    strategyContexts.Remove(questStrategyContext);

    actionContexts.Remove(actionContext);
    actionContexts.Remove(chatActionContext);
    actionContexts.Remove(worldPacketActionContext);

    triggerContexts.Remove(triggerContext);
    triggerContexts.Remove(chatTriggerContext);
    triggerContexts.Remove(worldPacketTriggerContext);

    valueContexts.Remove(valueContext);

    delete dynamic_cast<ai::StrategyContext*>(strategyContext);
    delete dynamic_cast<ai::MovementStrategyContext*>(movementStrategyContext);
    delete dynamic_cast<ai::AssistStrategyContext*>(assistStrategyContext);
    delete dynamic_cast<ai::QuestStrategyContext*>(questStrategyContext);

    delete dynamic_cast<ai::ActionContext*>(actionContext);
    delete dynamic_cast<ai::ChatActionContext*>(chatActionContext);
    delete dynamic_cast<ai::WorldPacketActionContext*>(worldPacketActionContext);

    delete dynamic_cast<ai::TriggerContext*>(triggerContext);
    delete dynamic_cast<ai::ChatTriggerContext*>(chatTriggerContext);
    delete dynamic_cast<ai::WorldPacketTriggerContext*>(worldPacketTriggerContext);

    delete dynamic_cast<ai::ValueContext*>(valueContext);
}

void AiObjectContext::Update()
{
    strategyContexts.Update();
    triggerContexts.Update();
    actionContexts.Update();
    valueContexts.Update();
}

void AiObjectContext::Reset()
{
    strategyContexts.Reset();
    triggerContexts.Reset();
    actionContexts.Reset();
    valueContexts.Reset();
}
