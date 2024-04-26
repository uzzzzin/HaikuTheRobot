#include "pch.h"
#include "CSGMStartState.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include <Scripts/CSwingingGarbageMagnetScript.h>

CSGMStartState::CSGMStartState()
	: CState(STATE_TYPE::SGMSTARTSTATE)
	, accTime(0)
	, duration(0.4f)
{
}

CSGMStartState::~CSGMStartState()
{
}


void CSGMStartState::Enter()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetCurStateName(L"Start");

	accTime = 0;

	CGameObject* bossDoorR = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"gbossDoorR_SGM");
	CGameObject* bossDoorL = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"gbossDoorL_SGM");
	bossDoorR->Animator2D()->Play(L"boss_Door", false);
	bossDoorL->Animator2D()->Play(L"boss_Door", false);
	bossDoorR->Collider2D()->Activate();
	bossDoorL->Collider2D()->Activate();
}

void CSGMStartState::finaltick()
{
	accTime += DT;

	if (accTime > duration)
	{
		ChangeState(L"UpToMiddle");
	}
}

void CSGMStartState::Exit()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetPrevStateName(L"Start");
}