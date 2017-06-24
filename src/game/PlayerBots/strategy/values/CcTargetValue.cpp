#include "../../../botpch.h"
#include "../../playerbot.h"
#include "CcTargetValue.h"
#include "../../PlayerbotAIConfig.h"
#include "../Action.h"

using namespace ai;

class FindTargetForCcStrategy : public FindTargetStrategy
{
public:
    FindTargetForCcStrategy(PlayerbotAI* ai, string spell) : FindTargetStrategy(ai)
    {
        this->spell = spell;
        maxDistance = 0;
    }

public:
    virtual void CheckAttacker(Unit* creature, ThreatManager* threatManager)
    {
        Player* bot = ai->GetBot();
        if (*ai->GetAiObjectContext()->GetValue<Unit*>("current target") == creature)
            return;

        uint8 health = creature->GetHealthPercent();
        if (health < 90)
            return;

        if (!ai->CanCastSpell(spell, creature))
            return;

        if (creature->UnderCc())
            return;

        if (*ai->GetAiObjectContext()->GetValue<Unit*>("rti target") == creature)
        {
            result = creature;
            return;
        }

        float minDistance = sPlayerbotAIConfig.spellDistance;
        Group* group = bot->GetGroup();
        if (!group)
            return;

        if (group->GetTargetIcon(3).GetRawValue() == creature->GetGUID())
        {
            result = creature;
            return;
        }

		if (*ai->GetAiObjectContext()->GetValue<uint8>("aoe count") > 2)
		{
			WorldLocation aoe = *ai->GetAiObjectContext()->GetValue<WorldLocation>("aoe position");
			if (creature->GetDistance2d(aoe.coord_x, aoe.coord_y) <= sPlayerbotAIConfig.aoeRadius)
			  return;
			}

        int tankCount, dpsCount;
        GetPlayerCount(creature, &tankCount, &dpsCount);
        if (!tankCount || !dpsCount)
        {
            result = creature;
            return;
        }

        Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player *member = sObjectMgr.GetPlayer(itr->guid);
            if( !member || !member->isAlive() || member == bot)
                continue;

            if (!ai->IsTank(member))
                continue;

            float distance = member->GetDistance(creature);
            if (distance < minDistance)
                minDistance = distance;
        }

        if (!result || minDistance > maxDistance)
        {
            result = creature;
            maxDistance = minDistance;
        }
    }

private:
    string spell;
    float maxDistance;
};

Unit* CcTargetValue::Calculate()
{
    FindTargetForCcStrategy strategy(ai, qualifier);
    return FindTarget(&strategy);
}

class FindTarget2ForCcStrategy : public FindTargetStrategy
{
public:
    FindTarget2ForCcStrategy(PlayerbotAI* ai, string spell) : FindTargetStrategy(ai)
    {
        this->spell = spell;
        maxDistance = 0;
    }

public:
    virtual void CheckAttacker(Unit* creature, ThreatManager* threatManager)
    {
        Player* bot = ai->GetBot();
        if (*ai->GetAiObjectContext()->GetValue<Unit*>("current target") == creature)
            return;

        uint8 health = creature->GetHealthPercent();
         if (health < 90)
            return;

        if (!ai->CanCastSpell(spell, creature))
            return;

        if (creature->UnderCc())
            return;

        if (*ai->GetAiObjectContext()->GetValue<Unit*>("rti target") == creature)
        {
            result = creature;
            return;
        }

        float minDistance = sPlayerbotAIConfig.spellDistance;
        Group* group = bot->GetGroup();
        if (!group)
            return;

        if (group->GetTargetIcon(1).GetRawValue() == creature->GetGUID())
        {
            result = creature;
            return;
        }

		if (*ai->GetAiObjectContext()->GetValue<uint8>("aoe count") > 2)
		{
			WorldLocation aoe = *ai->GetAiObjectContext()->GetValue<WorldLocation>("aoe position");
			if (creature->GetDistance2d(aoe.coord_x, aoe.coord_y) <= sPlayerbotAIConfig.aoeRadius)
				return;
		}

		int tankCount, dpsCount;
		GetPlayerCount(creature, &tankCount, &dpsCount);
		if (!tankCount || !dpsCount)
		{
			result = creature;
			return;
		}

		Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
		for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
		{
			Player *member = sObjectMgr.GetPlayer(itr->guid);
			if (!member || !member->isAlive() || member == bot)
				continue;

			if (!ai->IsTank(member))
				continue;

			float distance = member->GetDistance(creature);
			if (distance < minDistance)
				minDistance = distance;
		}

        if (!result || minDistance > maxDistance)
        {
            result = creature;
            maxDistance = minDistance;
        }
    }

private:
    string spell;
    float maxDistance;
};

Unit* CcTarget2Value::Calculate()
{
    FindTarget2ForCcStrategy strategy(ai, qualifier);
    return FindTarget(&strategy);
}

class FindTarget3ForCcStrategy : public FindTargetStrategy
{
public:
    FindTarget3ForCcStrategy(PlayerbotAI* ai, string spell) : FindTargetStrategy(ai)
    {
        this->spell = spell;
        maxDistance = 0;
    }

public:
    virtual void CheckAttacker(Unit* creature, ThreatManager* threatManager)
    {
        Player* bot = ai->GetBot();
        if (*ai->GetAiObjectContext()->GetValue<Unit*>("current target") == creature)
            return;

        uint8 health = creature->GetHealthPercent();

        if (health < 90)
            return;

        if (!ai->CanCastSpell(spell, creature))
            return;

        if (creature->UnderCc())
            return;

        if (*ai->GetAiObjectContext()->GetValue<Unit*>("rti target") == creature)
        {
            result = creature;
            return;
        }

        float minDistance = sPlayerbotAIConfig.spellDistance;
        Group* group = bot->GetGroup();
        if (!group)
            return;

        if (group->GetTargetIcon(2).GetRawValue() == creature->GetGUID())
        {
            result = creature;
            return;
        }

		if (*ai->GetAiObjectContext()->GetValue<uint8>("aoe count") > 2)
		{
			WorldLocation aoe = *ai->GetAiObjectContext()->GetValue<WorldLocation>("aoe position");
			if (creature->GetDistance2d(aoe.coord_x, aoe.coord_y) <= sPlayerbotAIConfig.aoeRadius)
				return;
		}

		int tankCount, dpsCount;
		GetPlayerCount(creature, &tankCount, &dpsCount);
		if (!tankCount || !dpsCount)
		{
			result = creature;
			return;
		}

		Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
		for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
		{
			Player *member = sObjectMgr.GetPlayer(itr->guid);
			if (!member || !member->isAlive() || member == bot)
				continue;

			if (!ai->IsTank(member))
				continue;

			float distance = member->GetDistance(creature);
			if (distance < minDistance)
				minDistance = distance;
		}

        if (!result || minDistance > maxDistance)
        {
            result = creature;
            maxDistance = minDistance;
        }
    }

private:
    string spell;
    float maxDistance;
};

Unit* CcTarget3Value::Calculate()
{
    FindTarget3ForCcStrategy strategy(ai, qualifier);
    return FindTarget(&strategy);
}

class FindTarget4ForCcStrategy : public FindTargetStrategy
{
public:
    FindTarget4ForCcStrategy(PlayerbotAI* ai, string spell) : FindTargetStrategy(ai)
    {
        this->spell = spell;
        maxDistance = 0;
    }

public:
    virtual void CheckAttacker(Unit* creature, ThreatManager* threatManager)
    {
        Player* bot = ai->GetBot();
        if (*ai->GetAiObjectContext()->GetValue<Unit*>("current target") == creature)
            return;

        uint8 health = creature->GetHealthPercent();
        if (health < 90)
            return;

        if (!ai->CanCastSpell(spell, creature))
            return;

        if (creature->UnderCc())
            return;

        if (*ai->GetAiObjectContext()->GetValue<Unit*>("rti target") == creature)
        {
            result = creature;
            return;
        }

        float minDistance = sPlayerbotAIConfig.spellDistance;
        Group* group = bot->GetGroup();
        if (!group)
            return;

        if (group->GetTargetIcon(0).GetRawValue() == creature->GetGUID())
        {
            result = creature;
            return;
        }

		if (*ai->GetAiObjectContext()->GetValue<uint8>("aoe count") > 2)
		{
			WorldLocation aoe = *ai->GetAiObjectContext()->GetValue<WorldLocation>("aoe position");
			if (creature->GetDistance2d(aoe.coord_x, aoe.coord_y) <= sPlayerbotAIConfig.aoeRadius)
				return;
		}

		int tankCount, dpsCount;
		GetPlayerCount(creature, &tankCount, &dpsCount);
		if (!tankCount || !dpsCount)
		{
			result = creature;
			return;
		}

		Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
		for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
		{
			Player *member = sObjectMgr.GetPlayer(itr->guid);
			if (!member || !member->isAlive() || member == bot)
				continue;

			if (!ai->IsTank(member))
				continue;

			float distance = member->GetDistance(creature);
			if (distance < minDistance)
				minDistance = distance;
		}

        if (!result || minDistance > maxDistance)
        {
            result = creature;
            maxDistance = minDistance;
        }
    }

private:
    string spell;
    float maxDistance;
};

Unit* CcTarget4Value::Calculate()
{
    FindTarget4ForCcStrategy strategy(ai, qualifier);
    return FindTarget(&strategy);
}

class FindTarget5ForCcStrategy : public FindTargetStrategy
{
public:
    FindTarget5ForCcStrategy(PlayerbotAI* ai, string spell) : FindTargetStrategy(ai)
    {
        this->spell = spell;
        maxDistance = 0;
    }

public:
    virtual void CheckAttacker(Unit* creature, ThreatManager* threatManager)
    {
        Player* bot = ai->GetBot();
        if (*ai->GetAiObjectContext()->GetValue<Unit*>("current target") == creature)
            return;

        uint8 health = creature->GetHealthPercent();
         if (health < 90)
            return;

        if (!ai->CanCastSpell(spell, creature))
            return;

        if (creature->UnderCc())
            return;

        if (*ai->GetAiObjectContext()->GetValue<Unit*>("rti target") == creature)
        {
            result = creature;
            return;
        }

        float minDistance = sPlayerbotAIConfig.spellDistance;
        Group* group = bot->GetGroup();
        if (!group)
            return;

        if (group->GetTargetIcon(4).GetRawValue() == creature->GetGUID())
        {
            result = creature;
            return;
        }

		if (*ai->GetAiObjectContext()->GetValue<uint8>("aoe count") > 2)
		{
			WorldLocation aoe = *ai->GetAiObjectContext()->GetValue<WorldLocation>("aoe position");
			if (creature->GetDistance2d(aoe.coord_x, aoe.coord_y) <= sPlayerbotAIConfig.aoeRadius)
				return;
		}

		int tankCount, dpsCount;
		GetPlayerCount(creature, &tankCount, &dpsCount);
		if (!tankCount || !dpsCount)
		{
			result = creature;
			return;
		}

		Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
		for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
		{
			Player *member = sObjectMgr.GetPlayer(itr->guid);
			if (!member || !member->isAlive() || member == bot)
				continue;

			if (!ai->IsTank(member))
				continue;

			float distance = member->GetDistance(creature);
			if (distance < minDistance)
				minDistance = distance;
		}

        if (!result || minDistance > maxDistance)
        {
            result = creature;
            maxDistance = minDistance;
        }
    }

private:
    string spell;
    float maxDistance;
};

Unit* CcTarget5Value::Calculate()
{
    FindTarget5ForCcStrategy strategy(ai, qualifier);
    return FindTarget(&strategy);
}

class FindTarget6ForCcStrategy : public FindTargetStrategy
{
public:
    FindTarget6ForCcStrategy(PlayerbotAI* ai, string spell) : FindTargetStrategy(ai)
    {
        this->spell = spell;
        maxDistance = 0;
    }

public:
    virtual void CheckAttacker(Unit* creature, ThreatManager* threatManager)
    {
        Player* bot = ai->GetBot();
        if (*ai->GetAiObjectContext()->GetValue<Unit*>("current target") == creature)
            return;

        uint8 health = creature->GetHealthPercent();
         if (health < 90)
            return;

        if (!ai->CanCastSpell(spell, creature))
            return;

        if (creature->UnderCc())
            return;

        if (*ai->GetAiObjectContext()->GetValue<Unit*>("rti target") == creature)
        {
            result = creature;
            return;
        }

        float minDistance = sPlayerbotAIConfig.spellDistance;
        Group* group = bot->GetGroup();
        if (!group)
            return;

        if (group->GetTargetIcon(5).GetRawValue() == creature->GetGUID())
        {
            result = creature;
            return;
        }

		if (*ai->GetAiObjectContext()->GetValue<uint8>("aoe count") > 2)
		{
			WorldLocation aoe = *ai->GetAiObjectContext()->GetValue<WorldLocation>("aoe position");
			if (creature->GetDistance2d(aoe.coord_x, aoe.coord_y) <= sPlayerbotAIConfig.aoeRadius)
				return;
		}

		int tankCount, dpsCount;
		GetPlayerCount(creature, &tankCount, &dpsCount);
		if (!tankCount || !dpsCount)
		{
			result = creature;
			return;
		}

		Group::MemberSlotList const& groupSlot = group->GetMemberSlots();
		for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
		{
			Player *member = sObjectMgr.GetPlayer(itr->guid);
			if (!member || !member->isAlive() || member == bot)
				continue;

			if (!ai->IsTank(member))
				continue;

			float distance = member->GetDistance(creature);
			if (distance < minDistance)
				minDistance = distance;
		}

        if (!result || minDistance > maxDistance)
        {
            result = creature;
            maxDistance = minDistance;
        }
    }

private:
    string spell;
    float maxDistance;
};

Unit* CcTarget6Value::Calculate()
{
    FindTarget6ForCcStrategy strategy(ai, qualifier);
    return FindTarget(&strategy);
}
