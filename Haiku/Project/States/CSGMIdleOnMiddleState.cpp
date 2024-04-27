#include "pch.h"
#include "CSGMIdleOnMiddleState.h"

#include <Scripts/CSwingingGarbageMagnetScript.h>

CSGMIdleOnMiddleState::CSGMIdleOnMiddleState()
	: CState(STATE_TYPE::SGMIDLEONMIDDLESTATE)
	, accTime(0)
	, duration(0.3f)
{
}

CSGMIdleOnMiddleState::~CSGMIdleOnMiddleState()
{
}


void CSGMIdleOnMiddleState::Enter()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetCurStateName(L"IdleOnMiddle");

	accTime = 0;

	GetOwnerObj()->Animator2D()->Play(L"SGM_IdleOnMiddle"); // 1ÇÁ·¹ÀÓ

	GetOwnerObj()->Collider2D()->SetOffset(Vec3(0,-44,0));
	GetOwnerObj()->Collider2D()->SetScale(Vec3(62,56,1));
}

void CSGMIdleOnMiddleState::finaltick()
{
	accTime += DT;

	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	BOSS_SWINGING_GARBAGE_MAGNET stage = pScpt->GetCurStage();

	if (accTime > duration)
	{
		switch (stage)
		{
		case BOSS_SWINGING_GARBAGE_MAGNET::INTRO:
			break;

		case BOSS_SWINGING_GARBAGE_MAGNET::STAGE1:
			ChangeState(L"YumOnMiddle");
			break;

		case BOSS_SWINGING_GARBAGE_MAGNET::STAGE2:
			break;

		case BOSS_SWINGING_GARBAGE_MAGNET::CLEAR:
			break;
		}
	}
}

void CSGMIdleOnMiddleState::Exit()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetPrevStateName(L"IdleOnMiddle");
}