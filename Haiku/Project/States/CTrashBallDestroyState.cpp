#include "pch.h"
#include "CTrashBallDestroyState.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include <Scripts/CBoss1RoomScript.h>

CTrashBallDestroyState::CTrashBallDestroyState()
	: CState(STATE_TYPE::TRASHBALLDESTROYSTATE)
{
}

CTrashBallDestroyState::~CTrashBallDestroyState()
{
}

void CTrashBallDestroyState::Enter()
{
	CGameObject* boss1room = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"ggbossc2");
	CBoss1RoomScript* RoomScpt = boss1room->GetScript<CBoss1RoomScript>();
	RoomScpt->MinusCurTrashBallCnt();
	GamePlayStatic::DestroyGameObject(GetOwnerObj());
}

void CTrashBallDestroyState::finaltick()
{
}

void CTrashBallDestroyState::Exit()
{

}