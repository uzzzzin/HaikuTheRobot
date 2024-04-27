#include "pch.h"
#include "CSGMYumOnTopState.h"

#include <Scripts/CSwingingGarbageMagnetScript.h>

CSGMYumOnTopState::CSGMYumOnTopState()
	: CState(STATE_TYPE::SGMYUMONTOPSTATE)
	, accTime(0)
	, duration(1.2f)
{
}

CSGMYumOnTopState::~CSGMYumOnTopState()
{
}

void CSGMYumOnTopState::Enter()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetCurStateName(L"YumOnTop");

	accTime = 0;

	GetOwnerObj()->Animator2D()->Play(L"SGM_YumOnTop"); // 4프레임 3번 반복
	GetOwnerObj()->Collider2D()->SetOffset(Vec3(0, 4, 0));
	GetOwnerObj()->Collider2D()->SetScale(Vec3(62, 57, 1));
}

void CSGMYumOnTopState::finaltick()
{
	accTime += DT;

	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	BOSS_SWINGING_GARBAGE_MAGNET stage = pScpt->GetCurStage();


	if (accTime > duration)
	{
		switch (stage)
		{
		case BOSS_SWINGING_GARBAGE_MAGNET::INTRO:
		case BOSS_SWINGING_GARBAGE_MAGNET::STAGE1:
			ChangeState(L"DownAttack");
			break;

		case BOSS_SWINGING_GARBAGE_MAGNET::STAGE2:
			break;

		case BOSS_SWINGING_GARBAGE_MAGNET::CLEAR:
			break;
		}
	}
}

void CSGMYumOnTopState::Exit()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetPrevStateName(L"YumOnTop");
}