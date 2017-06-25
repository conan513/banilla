#pragma once

#include "../Action.h"
#include "InventoryAction.h"
#include "MovementActions.h"
#include "../../AiFactory.h"
#include "../../PlayerbotAIConfig.h"
#include "../ItemVisitors.h"
#include "../../RandomPlayerbotMgr.h"
#include "BattleGround.h"
#include "BattleGroundMgr.h"
#include "BattleGroundWS.h"
#include "ChooseTargetActions.h"
#include "CheckMountStateAction.h"

namespace ai
{
	class BGJoinAction : public InventoryAction
	{
	public:
		BGJoinAction(PlayerbotAI* ai, string name = "bg join") : InventoryAction(ai, name) {}
		virtual bool Execute(Event event);

	protected:
		bool JoinProposal();
	};

	class BGStatusAction : public BGJoinAction
	{
	public:
		BGStatusAction(PlayerbotAI* ai) : BGJoinAction(ai, "bg status") {}
		virtual bool Execute(Event event);
	};

	class BGTacticsWS : public MovementAction
	{
	public:
		BGTacticsWS(PlayerbotAI* ai, string name = "bg tactics ws") : MovementAction(ai, name) {}
		virtual bool Execute(Event event);
	private:
		bool moveTowardsEnemyFlag(BattleGroundWS *bg);
		bool consumeHealthy(BattleGround *bg);
		bool homerun(BattleGroundWS *bg);
		bool runPathTo(WorldObject *unit, BattleGround *bg);
		bool wasInCombat = false;
	};

}
