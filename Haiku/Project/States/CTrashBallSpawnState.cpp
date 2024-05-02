#include "pch.h"
#include "CTrashBallSpawnState.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include <Engine/CScript.h>

#include <Engine/CAnimator2D.h>

#include <Scripts/CBoss1RoomScript.h>

CTrashBallSpawnState::CTrashBallSpawnState()
	: CState(STATE_TYPE::TRASHBALLSPAWNSTATE)
	, accTime(0)
	, duration(0.4f)
	, spawnAccTime(0)
	, spawnTime(0.35f)
	, bSpawnNextTB(false)
{
}

CTrashBallSpawnState::~CTrashBallSpawnState()
{
}


void CTrashBallSpawnState::Enter()
{
	accTime = 0;
	spawnAccTime = 0;
	bSpawnNextTB = false;

	GetOwnerObj()->Animator2D()->Play(L"TrashBall_Spawn", false);

	CGameObject* boss1room = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"ggbossc2");
	CBoss1RoomScript* RoomScpt = boss1room->GetScript<CBoss1RoomScript>();

	RoomScpt->PlusCurTrashBallCnt();
}

void CTrashBallSpawnState::finaltick()
{
	accTime += DT;
	spawnAccTime += DT;


	if (accTime > duration)
	{
		ChangeState(L"Drop");
	}

	if (spawnAccTime >= spawnTime) // 스폰시간이 되었으면 
	{
		CGameObject* boss1room = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"ggbossc2");
		CBoss1RoomScript* RoomScpt = boss1room->GetScript<CBoss1RoomScript>();

		if ((false == bSpawnNextTB) && (6 > RoomScpt->GetCurTrashBallCnt()))
		{
			Ptr<CPrefab> TrashBall = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"TrashBall");
			TrashBall = CAssetMgr::GetInst()->Load<CPrefab>(L"TrashBall", L"prefab\\TrashBall.pref");

			CGameObject* tbGO = TrashBall->Instantiate();
			GamePlayStatic::SpawnGameObject(tbGO, 11);
			bSpawnNextTB = true;
		}
	}
}

void CTrashBallSpawnState::Exit()
{
	//bSpawnNextTB = false;
	accTime = 0;
	spawnAccTime = 0;
}