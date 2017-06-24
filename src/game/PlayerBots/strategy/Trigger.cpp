#include "../../pchdef.h"
#include "../playerbot.h"
#include "Trigger.h"
#include "Action.h"
#include "../PlayerbotAIConfig.h"

using namespace ai;

Event Trigger::Check()
{
	if (IsActive())
	{
	    //Debug only
/*
	    Player* master = GetMaster();
        if (master)
        {
            if (getName() != "often" && getName() != "timer" && getName() != "no possible targets")
            //if (sPlayerbotAIConfig.outputTriggers && (GetLastEvent() != getName()) && (getName() != "timer" && getName() != "no possible targets"))
            {
                ai->TellMaster(getName());
                }
        }
        //Stop debug
*/
		Event event(getName());
		return event;
	}
	Event event;
	return event;
}

Value<Unit*>* Trigger::GetTargetValue()
{
    return context->GetValue<Unit*>(GetTargetName());
}

Unit* Trigger::GetTarget()
{
    return GetTargetValue()->Get();
}
