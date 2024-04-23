#include "pch.h"
#include "CBoss1RoomScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include "CRoomMgrScript.h"
#include "CTraceCameraScript.h"

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
	//CRoomMgrScript* RoomMgrScpt = GetOwner()->GetScript<CRoomMgrScript>();
	//RoomMgrScpt->SetCurBossRoomPos();
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