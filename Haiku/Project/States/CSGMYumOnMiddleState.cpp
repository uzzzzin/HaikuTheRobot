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

	if (true == bIntroParticle) // ��Ʈ���� ��
	{
		//duration = ��ƼŬ �Ͷ��Ÿ��� ��ŭ;
		bIntroParticle = false; //
	}
	else // false == bIntroParticle
	{
		duration = 1.2f;
	}

	GetOwnerObj()->Animator2D()->Play(L"SGM_YumOnMiddle"); // 4������
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
		//f(accTime) ƽ���� �ݶ��̴� ������ ������ ���߿� ������..
	}
}

void CSGMYumOnMiddleState::Exit()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetPrevStateName(L"YumOnMiddle");
}