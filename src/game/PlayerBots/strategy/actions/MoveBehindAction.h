#pragma once

#include "../Action.h"
#include "MovementActions.h"

namespace ai
{
	class MoveBehindAction : public MovementAction {
	public:
		MoveBehindAction(PlayerbotAI* ai) : MovementAction(ai, "move behind") {}
		virtual bool Execute(Event event);
        virtual bool isUseful();
	};
}
