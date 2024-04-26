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

	if (accTime > duration)
	{
		ChangeState(L"UpToTop");
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