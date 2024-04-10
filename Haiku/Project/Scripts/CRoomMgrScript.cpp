#include "pch.h"
#include "CRoomMgrScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include "CHaikuScript.h"
#include "CCamEventScript.h"

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
	Haiku->Transform()->SetRelativePos(Vec3(AfterRoom->Transform()->GetRelativePos().x, AfterRoom->Transform()->GetRelativePos().y+2, Haiku->Transform()->GetRelativePos().z));
	Haiku->GetScript<CHaikuScript>()->SetChanging(true);

	CGameObject* MainCam = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
	MainCam->GetScript<CCamEventScript>()->FadeIn(0.5f);
}

void CRoomMgrScript::SaveToFile(FILE* _File)
{
}

void CRoomMgrScript::LoadFromFile(FILE* _File)
{
}