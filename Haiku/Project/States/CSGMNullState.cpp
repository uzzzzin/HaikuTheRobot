#include "pch.h"
#include "CSGMNullState.h"

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
	pScpt->SetCurStateName(L"null");

	GetOwnerObj()->Animator2D()->Play(L"SGM_null");
}

void CSGMNullState::finaltick()
{
}

void CSGMNullState::Exit()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetPrevStateName(L"null");
}