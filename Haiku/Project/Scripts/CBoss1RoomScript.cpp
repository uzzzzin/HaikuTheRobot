#include "pch.h"
#include "CBoss1RoomScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include "CRoomMgrScript.h"
#include "CMainCameraScript.h"

CBoss1RoomScript::CBoss1RoomScript()
	:CScript(BOSS1ROOMSCRIPT)
	, bIntroDoor(false)
{
}

CBoss1RoomScript::~CBoss1RoomScript()
{
}

void CBoss1RoomScript::begin()
{
}

void CBoss1RoomScript::tick()
{
	CGameObject* kingGO = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"ImtheKing");
	CRoomMgrScript* RoomMgrScpt = kingGO->GetScript<CRoomMgrScript>();

	wstring curRoom = RoomMgrScpt->GetCurRoom()->GetName();
	if (L"ChangeRoom2" == curRoom)
	{
		CGameObject* MainCam = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
		CMainCameraScript* MainCamScpt = MainCam->GetScript<CMainCameraScript>();
		MainCamScpt->SetCamType(MAIN_CAMERA_TYPE::FIXED);
		MainCamScpt->SetFixedPos(Vec3(MainCamScpt->TargetPosXYX().x, -5, -120));
	}
}

void CBoss1RoomScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CBoss1RoomScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CBoss1RoomScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CBoss1RoomScript::SaveToFile(FILE* _File)
{

}

void CBoss1RoomScript::LoadFromFile(FILE* _File)
{

}