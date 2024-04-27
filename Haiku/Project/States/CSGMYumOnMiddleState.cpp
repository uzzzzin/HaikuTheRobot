#include "pch.h"
#include "CSGMYumOnMiddleState.h"

#include <Scripts/CSwingingGarbageMagnetScript.h>

CSGMYumOnMiddleState::CSGMYumOnMiddleState()
	: CState(STATE_TYPE::SGMYUMONMIDDLESTATE)
	, accTime(0)
	, duration(1.2f)
	, bIntroParticle(false)
{
}

CSGMYumOnMiddleState::~CSGMYumOnMiddleState()
{
}

void CSGMYumOnMiddleState::Enter()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetCurStateName(L"YumOnMiddle");

	accTime = 0;

	if (true == bIntroParticle) // 인트로일 때
	{
		//duration = 파티클 와라라거리는 만큼;
		bIntroParticle = false; //
	}
	else // false == bIntroParticle
	{
		duration = 1.2f;
	}

	GetOwnerObj()->Animator2D()->Play(L"SGM_YumOnMiddle"); // 4프레임
}

void CSGMYumOnMiddleState::finaltick()
{
	accTime += DT;

	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	BOSS_SWINGING_GARBAGE_MAGNET stage = pScpt->GetCurStage();

	if (accTime > duration)
	{
		//ChangeState(L"UpToTop");

		switch (stage)
		{
		case BOSS_SWINGING_GARBAGE_MAGNET::INTRO:
			pScpt->SetCurStage(BOSS_SWINGING_GARBAGE_MAGNET::STAGE1);
			ChangeState(L"UpToTop");
			break;

		case BOSS_SWINGING_GARBAGE_MAGNET::STAGE1:
			ChangeState(L"MoveOnMiddle");
			break;

		case BOSS_SWINGING_GARBAGE_MAGNET::STAGE2:
			break;

		case BOSS_SWINGING_GARBAGE_MAGNET::CLEAR:
			break;
		}
	}
	else
	{
		//f(accTime) 틱단위 콜라이더 오프셋 조정은 나중에 언젠간..
	}
}

void CSGMYumOnMiddleState::Exit()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetPrevStateName(L"YumOnMiddle");
}