#pragma once
#include "../Value.h"

namespace ai
{
    class FindPlayerPredicate
    {
    public:
        virtual bool Check(Unit*) = 0;
    };

    class SpellEntryPredicate
    {
    public:
        virtual bool Check(SpellEntry const*) = 0;
    };

    class PartyMemberValue : public UnitCalculatedValue
	{
	public:
        PartyMemberValue(PlayerbotAI* ai) : UnitCalculatedValue(ai) {}

    public:
        bool IsTargetOfSpellCast(Player* target, SpellEntryPredicate &predicate);

    protected:
        Unit* FindPartyMember(FindPlayerPredicate &predicate);
        Unit* FindPartyMember(list<Player*>* party, FindPlayerPredicate &predicate);
        bool Check(Unit* player);
	};


    class IsPartyValue : public BoolCalculatedValue, public Qualified
    {
    public:
        IsPartyValue(PlayerbotAI* ai) : BoolCalculatedValue(ai) {}

        Unit* GetTarget()
        {
            AiObjectContext* ctx = AiObject::context;
            return ctx->GetValue<Unit*>(qualifier)->Get();
        }
        virtual bool Calculate()
        {
            return ((bot->GetGroup()) ? true:false);
        }
    };
}
