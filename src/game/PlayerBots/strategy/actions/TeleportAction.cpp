#include "../../../botpch.h"
#include "../../playerbot.h"
#include "TeleportAction.h"
#include "../values/LastMovementValue.h"

using namespace ai;

bool TeleportAction::Execute(Event event)
{
    list<ObjectGuid> gos = *context->GetValue<list<ObjectGuid> >("nearest game objects");
    for (list<ObjectGuid>::iterator i = gos.begin(); i != gos.end(); i++)
    {
        GameObject* go = ai->GetGameObject(*i);
        if (!go)
            continue;

		GameObjectInfo const *goInfo = go->GetGOInfo();
        if (goInfo->type != GAMEOBJECT_TYPE_SPELLCASTER)
            continue;

        uint32 spellId = goInfo->spellcaster.spellId;
		SpellEntry const* pSpellProto = sSpellMgr.GetSpellEntry(spellId);
        if (pSpellProto->Effect[0] != SPELL_EFFECT_TELEPORT_UNITS && pSpellProto->Effect[1] != SPELL_EFFECT_TELEPORT_UNITS && pSpellProto->Effect[2] != SPELL_EFFECT_TELEPORT_UNITS)
            continue;

        ostringstream out; out << "Teleporting using " << goInfo->name;
        ai->TellMasterNoFacing(out.str());

        ai->ChangeStrategy("-follow,+stay", BOT_STATE_NON_COMBAT);

        Spell *spell = new Spell(bot, pSpellProto, false);
        SpellCastTargets targets;
        targets.setUnitTarget(bot);
        spell->prepare(targets);
        spell->cast(true);
        return true;
    }


    LastMovement& movement = context->GetValue<LastMovement&>("last movement")->Get();
    if (movement.lastAreaTrigger)
    {
        WorldPacket p(CMSG_AREATRIGGER);
        p << movement.lastAreaTrigger;
        p.rpos(0);

        bot->GetSession()->HandleAreaTriggerOpcode(p);
        movement.lastAreaTrigger = 0;
        return true;
    }

    ai->TellMaster("Cannot find any portal to teleport");
    return false;
}