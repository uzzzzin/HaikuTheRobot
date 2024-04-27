#include "pch.h"
#include "CSGMUpToMiddleState.h"

#include <Scripts/CSwingingGarbageMagnetScript.h>

CSGMUpToMiddleState::CSGMUpToMiddleState()
	: CState(STATE_TYPE::SGMUPTOMIDDLESTATE)
	, accTime(0)
	, duration(0.4f)
{
}

CSGMUpToMiddleState::~CSGMUpToMiddleState()
{
}


void CSGMUpToMiddleState::Enter()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetCurStateName(L"UpToMiddle");

	accTime = 0;

	GetOwnerObj()->Animator2D()->Play(L"SGM_UpToMiddle", false);
	GetOwnerObj()->Collider2D()->SetOffset(Vec3(0, -44, 0));
	GetOwnerObj()->Collider2D()->SetScale(Vec3(62, 56, 1));
}

void CSGMUpToMiddleState::finaltick()
{
	accTime += DT;

	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	BOSS_SWINGING_GARBAGE_MAGNET stage = pScpt->GetCurStage();

	if (accTime > duration)
	{
		switch (stage)
		{
		case BOSS_SWINGING_GARBAGE_MAGNET::INTRO:
			ChangeState(L"YumOnMiddle");
			break;

		case BOSS_SWINGING_GARBAGE_MAGNET::STAGE1:
			ChangeState(L"IdleOnMiddle");
			break;

		case BOSS_SWINGING_GARBAGE_MAGNET::STAGE2:
			break;

		case BOSS_SWINGING_GARBAGE_MAGNET::CLEAR:
			break;
		}
	}
}

void CSGMUpToMiddleState::Exit()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetPrevStateName(L"UpToMiddle");
}