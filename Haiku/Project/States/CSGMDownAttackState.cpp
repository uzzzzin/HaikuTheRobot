#include "pch.h"
#include "CSGMDownAttackState.h"

#include <Scripts/CSwingingGarbageMagnetScript.h>

CSGMDownAttackState::CSGMDownAttackState()
	: CState(STATE_TYPE::SGMDOWNATTACKSTATE)
	, accTime(0)
	, duration(0.4f)
{
}

CSGMDownAttackState::~CSGMDownAttackState()
{
}

void CSGMDownAttackState::Enter()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetCurStateName(L"DownAttack");

	accTime = 0;

	prevColOffset = GetOwnerObj()->Collider2D()->GetOffset();
	prevColScale = GetOwnerObj()->Collider2D()->GetScale();

	GetOwnerObj()->Animator2D()->Play(L"SGM_DownAttack", false); // 4프레임

	wantColOffset = Vec3(0, -49, 0);
	wantColScale = Vec3(62, 57, 1);
}

void CSGMDownAttackState::finaltick()
{
	accTime += DT;

	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	BOSS_SWINGING_GARBAGE_MAGNET stage = pScpt->GetCurStage();

	if (accTime > duration)
	{
		//ChangeState(L"IdleOnMiddle");

		switch (stage)
		{
		case BOSS_SWINGING_GARBAGE_MAGNET::INTRO:
		case BOSS_SWINGING_GARBAGE_MAGNET::STAGE1:
			ChangeState(L"UpToMiddle");
			break;

		case BOSS_SWINGING_GARBAGE_MAGNET::STAGE2:
			break;

		case BOSS_SWINGING_GARBAGE_MAGNET::CLEAR:
			break;
		}
	}
	else
	{
		float ratio = accTime / duration; // 시간이 누적될수록 점점 1에 가까워짐 == 퍼센트가 오른다

		Vec3 vPos = ratio * (wantColOffset - prevColOffset) + prevColOffset;
		Vec3 vScale = ratio * (wantColScale - prevColScale) + prevColScale;

		GetOwnerObj()->Collider2D()->SetOffset(vPos);
		GetOwnerObj()->Collider2D()->SetScale(vScale);
	}
}

void CSGMDownAttackState::Exit()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetPrevStateName(L"DownAttack");
}