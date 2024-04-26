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

	GetOwnerObj()->Animator2D()->Play(L"SGM_UpToTop", false); // 2������?

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
		// �ݶ��̴� ��ġ�� ������ �Űܰ����ؿ�..
		//if()
		int a = 0;

		float ratio = accTime / duration; // �ð��� �����ɼ��� ���� 1�� ������� == �ۼ�Ʈ�� ������

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
