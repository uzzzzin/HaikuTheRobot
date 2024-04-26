#include "pch.h"
#include "CSGMNullState.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include <Engine/CAnimator2D.h>
#include <Scripts/CSwingingGarbageMagnetScript.h>

CSGMNullState::CSGMNullState()
	: CState(STATE_TYPE::SGMNULLSTATE)
{
}

CSGMNullState::~CSGMNullState()
{
}


void CSGMNullState::Enter()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetCurStateName(L"Null");

	GetOwnerObj()->Animator2D()->Play(L"SGM_null");

	CGameObject* bossDoorR = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"gbossDoorR_SGM");
	CGameObject* bossDoorL = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"gbossDoorL_SGM");

	bossDoorR->Collider2D()->Deactivate();
	bossDoorL->Collider2D()->Deactivate();
}

void CSGMNullState::finaltick()
{
}

void CSGMNullState::Exit()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetPrevStateName(L"Null");
}