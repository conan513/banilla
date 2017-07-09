#include "../../../botpch.h"
#include "../../playerbot.h"
#include "CheckMailAction.h"
#include "Mail.h"

#include "../../GuildTaskMgr.h"
using namespace ai;

bool CheckMailAction::Execute(Event event)
{
	WorldPacket p;
	bot->GetSession()->HandleQueryNextMailTime(p);

	MasterPlayer* pl;
	if (bot->GetSession())
		pl = bot->GetSession()->GetMasterPlayer();

	if (!pl)
		return false;

	if (ai->GetMaster() || !pl->GetMailSize())
		return false;

	list<uint32> ids;
	for (PlayerMails::iterator i = pl->GetMailBegin(); i != pl->GetMailEnd(); ++i)
	{
		Mail* mail = *i;

		if (!mail || mail->state == MAIL_STATE_DELETED)
			continue;

		Player* owner = sObjectMgr.GetPlayer((uint64)mail->sender);
		if (!owner)
			continue;

		ProcessMail(mail, owner);
		ids.push_back(mail->messageID);
		mail->state = MAIL_STATE_DELETED;
	}

	for (list<uint32>::iterator i = ids.begin(); i != ids.end(); ++i)
	{
		uint32 id = *i;
		pl->SendMailResult(id, MAIL_DELETED, MAIL_OK);
		CharacterDatabase.PExecute("DELETE FROM mail WHERE id = '%u'", id);
		CharacterDatabase.PExecute("DELETE FROM mail_items WHERE mail_id = '%u'", id);
		pl ->RemoveMail(id);
	}

	return true;
}


void CheckMailAction::ProcessMail(Mail* mail, Player* owner)
{
	if (!mail->HasItems())
		return;

	MasterPlayer* pl;
	if (bot->GetSession())
		pl = bot->GetSession()->GetMasterPlayer();

	if (!pl)
		return;

	for (MailItemInfoVec::iterator i = mail->items.begin(); i != mail->items.end(); ++i)
	{
		Item *item = pl->GetMItem(i->item_guid);
		if (!item)
			continue;

		sGuildTaskMgr.CheckItemTask(i->item_template, item->GetCount(), owner, bot, true);
		pl->RemoveMItem(i->item_guid);
		item->DestroyForPlayer(bot);
	}
}