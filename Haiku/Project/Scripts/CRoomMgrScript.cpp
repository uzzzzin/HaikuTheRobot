#include "pch.h"
#include "CRoomMgrScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include "CHaikuScript.h"

CRoomMgrScript::CRoomMgrScript()
	: CScript(ROOMMGRSCRIPT)
	, bChanging (false)
{
}

CRoomMgrScript::~CRoomMgrScript()
{
}

void CRoomMgrScript::begin()
{
	map_connectedRoom.insert({ L"ChangeRoom1", L"ChangeRoom2"});
	map_connectedRoom.insert({L"ChangeRoom2", L"ChangeRoom1"});
}

void CRoomMgrScript::tick()
{
	if (true == bChanging)
	{
		Change(curBeforeChangeRoomName);
		bChanging = false;
	}
}

void CRoomMgrScript::Change(wstring _name)
{
	wstring afterRoomName = map_connectedRoom.find(_name)->second;
	CGameObject* AfterRoom = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(afterRoomName);
	
	CGameObject* Haiku = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Haiku");
	Haiku->Transform()->SetRelativePos(AfterRoom->Transform()->GetRelativePos());
	Haiku->GetScript<CHaikuScript>()->SetChanging(true);
}

void CRoomMgrScript::SaveToFile(FILE* _File)
{
}

void CRoomMgrScript::LoadFromFile(FILE* _File)
{
}