#pragma once

std::vector<std::string> split(const std::string &s, char delim);
#ifndef WIN32
int strcmpi(std::string s1, std::string s2);
#endif

//#include "vld.h"
#include "../Spell.h"
#include "../../Shared/WorldPacket.h"
#include "../../game/LootMgr.h"
#include "../../game/GossipDef.h"
#include "../../game/Chat.h"
#include "../../shared/Common.h"
#include "../../game/World.h"
#include "../../game/SpellMgr.h"
#include "../../game/ObjectMgr.h"
#include "../../game//Unit.h"
#include "../../game/SharedDefines.h"
#include "../../game/MotionMaster.h"
#include "../../game/SpellAuras.h"
#include "../../game/Guild.h"
#include "../../game/Group.h"
#include "../../game/AccountMgr.h"
#include "../../game/ObjectMgr.h"

#include "playerbotDefs.h"
#include "PlayerbotAIAware.h"
#include "PlayerbotMgr.h"
#include "RandomPlayerbotMgr.h"
#include "ChatHelper.h"
#include "PlayerbotAI.h"

//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

//#ifdef _DEBUG
//#ifndef DBG_NEW
//#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
//#define new DBG_NEW
//#endif
//#endif  // _DEBUG
