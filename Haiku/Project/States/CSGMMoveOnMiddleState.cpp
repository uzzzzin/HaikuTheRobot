#include "pch.h"
#include "CSGMMoveOnMiddleState.h"

#include <Scripts/CSwingingGarbageMagnetScript.h>

CSGMMoveOnMiddleState::CSGMMoveOnMiddleState()
	: CState(STATE_TYPE::SGMMOVEONMIDDLESTATE)
	, accTime(0)
	, duration(0.1f)
	, speed(1.f)
	, WallL(1291.f)
	, WallR(1564.f)
{
}

CSGMMoveOnMiddleState::~CSGMMoveOnMiddleState()
{
}

void CSGMMoveOnMiddleState::Enter()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetCurStateName(L"MoveOnMiddle");

	accTime = 0;

	prevColOffset = GetOwnerObj()->Collider2D()->GetOffset();
	prevColScale = GetOwnerObj()->Collider2D()->GetScale();
	//prevColRotZ = GetOwnerObj()->Collider2D()->GetRotationZ();

	GetOwnerObj()->Animator2D()->Play(L"SGM_MoveOnMiddle", false); // ??? 프레임

	wantColOffsetL = Vec3(31.f, -41.f, 0.f); // L
	wantColScaleL = Vec3(62.f, 67.f, 1.f); // L
	//wantColRotZL = 15.f;
	//GetOwnerObj()->Collider2D()->SetRotationZ(wantColRotZL);

	prevPos = GetOwnerObj()->Transform()->GetRelativePos();
}

void CSGMMoveOnMiddleState::finaltick()
{
	accTime += DT;

	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	BOSS_SWINGING_GARBAGE_MAGNET stage = pScpt->GetCurStage();

	if (accTime <= duration)
	{
		if (0 == pScpt->GetCurDir()) // L
		{
			// 콜라이더 움직이기
			float ratio = accTime / duration; // 시간이 누적될수록 점점 1에 가까워짐 == 퍼센트가 오른다

			Vec3 vPos = ratio * (wantColOffsetL - prevColOffset) + prevColOffset;
			Vec3 vScale = ratio * (wantColScaleL - prevColScale) + prevColScale;

			GetOwnerObj()->Collider2D()->SetOffset(vPos);
			GetOwnerObj()->Collider2D()->SetScale(vScale);
		}
		else // R
		{
		}
	}
	else
	{
		Vec3 curPos = GetOwnerObj()->Transform()->GetRelativePos();

		if ((0 == pScpt->GetCurDir() && curPos.x > WallL) || (1 == pScpt->GetCurDir() && curPos.x < WallR) ) // 구역 안에 있으면 // && curPos.x > WallR)
		{
			if (0 == pScpt->GetCurDir())
			{
				// 방향대로 트랜스폼 움직이기
				float ratio = 1 - abs((WallL - curPos.x) / (WallL - prevPos.x)) + speed * DT;

				float vPosX = ratio * (WallL - prevPos.x) + prevPos.x;
				GetOwnerObj()->Transform()->SetRelativePos(Vec3(vPosX, curPos.y, curPos.z));
			}

			if (1 == pScpt->GetCurDir())
			{
				float ratio = 1 - abs((WallR - curPos.x) / (WallR - prevPos.x)) + speed * DT;

				float vPosX = ratio * (WallR - prevPos.x) + prevPos.x;
				GetOwnerObj()->Transform()->SetRelativePos(Vec3(vPosX, curPos.y, curPos.z));
			}
		}
		else //벽에 부딪혔다면
		{
			switch (stage)
			{
			case BOSS_SWINGING_GARBAGE_MAGNET::INTRO:
				break;

			case BOSS_SWINGING_GARBAGE_MAGNET::STAGE1:
				ChangeState(L"ChangeDir");
				break;

			case BOSS_SWINGING_GARBAGE_MAGNET::STAGE2:
				break;

			case BOSS_SWINGING_GARBAGE_MAGNET::CLEAR:
				break;
			}
		}
	}
}

void CSGMMoveOnMiddleState::Exit()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetPrevStateName(L"MoveOnMiddle");
}

