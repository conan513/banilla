#pragma once
#include "../Trigger.h"
#include "../../PlayerbotAIConfig.h"

namespace ai
{
    class ValueInRangeTrigger : public Trigger
    {
    public:
        ValueInRangeTrigger(PlayerbotAI* ai, string name, float maxValue, float minValue) : Trigger(ai, name) {
            this->maxValue = maxValue;
            this->minValue = minValue;
        }
    public:
        virtual float GetValue() = 0;
        virtual bool IsActive() {
            float value = GetValue();
            return value < maxValue && value >= minValue;
        }

    protected:
        float maxValue, minValue;
    };

	class HealthInRangeTrigger : public ValueInRangeTrigger
	{
	public:
		HealthInRangeTrigger(PlayerbotAI* ai, string name, float maxValue, float minValue = 0) :
		  ValueInRangeTrigger(ai, name, maxValue, minValue) {}

		virtual bool IsActive()
		{
		    return ValueInRangeTrigger::IsActive() && !AI_VALUE2(bool, "dead", GetTargetName());
		}

		virtual float GetValue();
	};

    class LowHealthTrigger : public HealthInRangeTrigger
    {
    public:
        LowHealthTrigger(PlayerbotAI* ai, string name = "low health",
            float value = sPlayerbotAIConfig.lowHealth, float minValue = sPlayerbotAIConfig.criticalHealth) :
            HealthInRangeTrigger(ai, name, value, minValue) {}

		virtual string GetTargetName() { return "self target"; }
    };

    class CriticalHealthTrigger : public LowHealthTrigger
    {
    public:
        CriticalHealthTrigger(PlayerbotAI* ai) :
            LowHealthTrigger(ai, "critical health", sPlayerbotAIConfig.criticalHealth, sPlayerbotAIConfig.almostDead) {}
    };

    class AlmostDeadTrigger : public LowHealthTrigger
    {
    public:
        AlmostDeadTrigger(PlayerbotAI* ai) :
            LowHealthTrigger(ai, "almost dead", sPlayerbotAIConfig.almostDead, 0) {}
    };

    class MediumHealthTrigger : public LowHealthTrigger
    {
    public:
        MediumHealthTrigger(PlayerbotAI* ai) :
            LowHealthTrigger(ai, "medium health", sPlayerbotAIConfig.mediumHealth, sPlayerbotAIConfig.lowHealth) {}
    };

    class HighHealthTrigger : public LowHealthTrigger
    {
    public:
        HighHealthTrigger(PlayerbotAI* ai) :
            LowHealthTrigger(ai, "high health", sPlayerbotAIConfig.highHealth, sPlayerbotAIConfig.mediumHealth) {}
    };

    class AlmostFullHealthTrigger : public LowHealthTrigger
    {
    public:
        AlmostFullHealthTrigger(PlayerbotAI* ai) :
            LowHealthTrigger(ai, "almost full health", sPlayerbotAIConfig.almostFullHealth, sPlayerbotAIConfig.highHealth) {}
    };

    class FullHealthTrigger : public LowHealthTrigger
    {
    public:
        FullHealthTrigger(PlayerbotAI* ai) :
            LowHealthTrigger(ai, "full health", 100, sPlayerbotAIConfig.almostFullHealth) {}
    };

    class MasterLowHealthTrigger : public HealthInRangeTrigger
    {
    public:
        MasterLowHealthTrigger(PlayerbotAI* ai, string name = "master low health",
            float value = sPlayerbotAIConfig.mediumHealth, float minValue = sPlayerbotAIConfig.criticalHealth) :
            HealthInRangeTrigger(ai, name, value, minValue) {}

		virtual string GetTargetName() { return "master target"; }
    };

    class MasterCriticalHealthTrigger : public MasterLowHealthTrigger
    {
    public:
        MasterCriticalHealthTrigger(PlayerbotAI* ai) :
            MasterLowHealthTrigger(ai, "master critical health", sPlayerbotAIConfig.criticalHealth, sPlayerbotAIConfig.almostDead) {}
    };

    class MasterAlmostDeadTrigger : public MasterLowHealthTrigger
    {
    public:
        MasterAlmostDeadTrigger(PlayerbotAI* ai) :
            MasterLowHealthTrigger(ai, "master almost dead", sPlayerbotAIConfig.almostDead, 0) {}
    };

    class MasterHighHealthTrigger : public MasterLowHealthTrigger
    {
    public:
        MasterHighHealthTrigger(PlayerbotAI* ai) :
            MasterLowHealthTrigger(ai, "master high health", sPlayerbotAIConfig.highHealth, sPlayerbotAIConfig.mediumHealth) {}
    };

    class MasterAlmostFullHealthTrigger : public MasterLowHealthTrigger
    {
    public:
        MasterAlmostFullHealthTrigger(PlayerbotAI* ai) :
            MasterLowHealthTrigger(ai, "master almost full health", sPlayerbotAIConfig.almostFullHealth, sPlayerbotAIConfig.highHealth) {}
    };

    class PartyMemberLowHealthTrigger : public HealthInRangeTrigger
    {
    public:
        PartyMemberLowHealthTrigger(PlayerbotAI* ai, string name = "party member low health", float value = sPlayerbotAIConfig.lowHealth, float minValue = sPlayerbotAIConfig.criticalHealth) :
            HealthInRangeTrigger(ai, name, value, minValue) {}

        virtual string GetTargetName() { return "party member to heal"; }
    };

    class PartyMemberCriticalHealthTrigger : public PartyMemberLowHealthTrigger
    {
    public:
        PartyMemberCriticalHealthTrigger(PlayerbotAI* ai) :
            PartyMemberLowHealthTrigger(ai, "party member critical health", sPlayerbotAIConfig.criticalHealth, sPlayerbotAIConfig.almostDead) {}
    };

    class PartyMemberAlmostDeadTrigger : public PartyMemberLowHealthTrigger
    {
    public:
        PartyMemberAlmostDeadTrigger(PlayerbotAI* ai) :
            PartyMemberLowHealthTrigger(ai, "party member almost dead", sPlayerbotAIConfig.almostDead, 0) {}
    };

    class PartyMemberMediumHealthTrigger : public PartyMemberLowHealthTrigger
    {
    public:
        PartyMemberMediumHealthTrigger(PlayerbotAI* ai) :
            PartyMemberLowHealthTrigger(ai, "party member medium health", sPlayerbotAIConfig.mediumHealth,sPlayerbotAIConfig.lowHealth) {}
    };

    class PartyMemberAlmostFullHealthTrigger : public PartyMemberLowHealthTrigger
    {
    public:
        PartyMemberAlmostFullHealthTrigger(PlayerbotAI* ai) :
            PartyMemberLowHealthTrigger(ai, "party member almost full health", sPlayerbotAIConfig.almostFullHealth,sPlayerbotAIConfig.highHealth) {}
    };

    class PartyMemberHighHealthTrigger : public PartyMemberLowHealthTrigger
    {
    public:
        PartyMemberHighHealthTrigger(PlayerbotAI* ai) :
            PartyMemberLowHealthTrigger(ai, "party member high health", sPlayerbotAIConfig.highHealth,sPlayerbotAIConfig.mediumHealth) {}
    };

    class TargetLowHealthTrigger : public HealthInRangeTrigger {
    public:
        TargetLowHealthTrigger(PlayerbotAI* ai, float value, float minValue = 0) :
            HealthInRangeTrigger(ai, "target low health", value, minValue) {}
        virtual string GetTargetName() { return "current target"; }
    };

    class TargetCriticalHealthTrigger : public TargetLowHealthTrigger
    {
    public:
        TargetCriticalHealthTrigger(PlayerbotAI* ai) : TargetLowHealthTrigger(ai, 20) {}
    };

    class TargetVeryLowHealthTrigger : public HealthInRangeTrigger {
    public:
        TargetVeryLowHealthTrigger(PlayerbotAI* ai, float value, float minValue = 0) :
            HealthInRangeTrigger(ai, "target almost dead", value, minValue) {}
        virtual string GetTargetName() { return "current target"; }
    };

    class TargetAlmostDeadTrigger : public TargetVeryLowHealthTrigger
    {
    public:
        TargetAlmostDeadTrigger(PlayerbotAI* ai) : TargetVeryLowHealthTrigger(ai, 10) {}
    };

	class PartyMemberDeadTrigger : public Trigger {
	public:
		PartyMemberDeadTrigger(PlayerbotAI* ai) : Trigger(ai, "resurrect", 10) {}
        virtual string GetTargetName() { return "party member to resurrect"; }
		virtual bool IsActive();
	};

    class DeadTrigger : public Trigger {
    public:
        DeadTrigger(PlayerbotAI* ai) : Trigger(ai, "dead", 10) {}
        virtual string GetTargetName() { return "self target"; }
        virtual bool IsActive();
    };

    class AoeHealTrigger : public Trigger {
    public:
    	AoeHealTrigger(PlayerbotAI* ai, string name, string type, int count) :
    		Trigger(ai, name), type(type), count(count) {}
    public:
        virtual bool IsActive();

    protected:
        int count;
        string type;
    };

}
