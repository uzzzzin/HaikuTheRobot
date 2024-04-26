#include "pch.h"
#include "CSGMUpOnTopState.h"
#include <Scripts/CSwingingGarbageMagnetScript.h>

CSGMUpOnTopState::CSGMUpOnTopState()
	: CState(STATE_TYPE::SGMUPONTOPSTATE)
{
}

CSGMUpOnTopState::~CSGMUpOnTopState()
{
}


void CSGMUpOnTopState::Enter()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetCurStateName(L"UpOnTop");

	accTime = 0;

	GetOwnerObj()->Animator2D()->Play(L"SGM_UpOnTop", false); // 2ÇÁ·¹ÀÓ?
}

void CSGMUpOnTopState::finaltick()
{
}

void CSGMUpOnTopState::Exit()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetPrevStateName(L"UpOnTop");
}