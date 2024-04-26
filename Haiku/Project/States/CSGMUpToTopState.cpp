#include "pch.h"
#include "CSGMUpToTopState.h"

#include <Scripts/CSwingingGarbageMagnetScript.h>

CSGMUpToTopState::CSGMUpToTopState()
	: CState(STATE_TYPE::SGMUPTOTOPSTATE)
	, accTime(0)
	, duration(0.2f)
{
}

CSGMUpToTopState::~CSGMUpToTopState()
{
}

void CSGMUpToTopState::Enter()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetCurStateName(L"UpToTop");

	accTime = 0;

	prevColOffset = GetOwnerObj()->Collider2D()->GetOffset();
	prevColScale = GetOwnerObj()->Collider2D()->GetScale();

	GetOwnerObj()->Animator2D()->Play(L"SGM_UpToTop", false); // 2프레임?

	//GetOwnerObj()->Collider2D()->SetOffset(Vec3(0,7,0));
	//GetOwnerObj()->Collider2D()->SetScale(Vec3(62,50,1));

	wantColOffset = Vec3(0, 7, 0);
	wantColScale = Vec3(62, 50, 1);
}

void CSGMUpToTopState::finaltick()
{
	accTime += DT;

	if (accTime > duration)
	{
		ChangeState(L"YumOnTop");
		int a = 0;
	}
	else
	{
		// 콜라이더 위치가 스르륵 옮겨가야해요..
		//if()
		int a = 0;

		float ratio = accTime / duration; // 시간이 누적될수록 점점 1에 가까워짐 == 퍼센트가 오른다

		Vec3 vPos = ratio * (wantColOffset - prevColOffset) + prevColOffset;
		Vec3 vScale = ratio * (wantColScale - prevColScale) + prevColScale;

		GetOwnerObj()->Collider2D()->SetOffset(vPos);
		GetOwnerObj()->Collider2D()->SetScale(vScale);
	}
}

void CSGMUpToTopState::Exit()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetPrevStateName(L"UpToTop");
}
