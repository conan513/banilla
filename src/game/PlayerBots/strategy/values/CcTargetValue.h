#pragma once
#include "../Value.h"
#include "TargetValue.h"

namespace ai
{

    class CcTargetValue : public TargetValue, public Qualified
	{
	public:
        CcTargetValue(PlayerbotAI* ai) : TargetValue(ai) {}

    public:
        Unit* Calculate();
    };

    class CcTarget2Value : public TargetValue, public Qualified
	{
	public:
        CcTarget2Value(PlayerbotAI* ai) : TargetValue(ai) {}

    public:
        Unit* Calculate();
    };

    class CcTarget3Value : public TargetValue, public Qualified
	{
	public:
        CcTarget3Value(PlayerbotAI* ai) : TargetValue(ai) {}

    public:
        Unit* Calculate();
    };

    class CcTarget4Value : public TargetValue, public Qualified
	{
	public:
        CcTarget4Value(PlayerbotAI* ai) : TargetValue(ai) {}

    public:
        Unit* Calculate();
    };

    class CcTarget5Value : public TargetValue, public Qualified
	{
	public:
        CcTarget5Value(PlayerbotAI* ai) : TargetValue(ai) {}

    public:
        Unit* Calculate();
    };

    class CcTarget6Value : public TargetValue, public Qualified
	{
	public:
        CcTarget6Value(PlayerbotAI* ai) : TargetValue(ai) {}

    public:
        Unit* Calculate();
    };
}
