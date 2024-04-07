#include "pch.h"
#include "CNuttyIdleState.h"

#include <Engine/CStateMachine.h>

#include <Engine/CAnimator2D.h>

#include <Scripts/CNuttyScript.h>

CNuttyIdleState::CNuttyIdleState()
	:CState(STATE_TYPE::NUTTYIDLESTATE)
{
}

CNuttyIdleState::~CNuttyIdleState()
{
}

void CNuttyIdleState::Enter()
{
	GetFSM()->GetStateMachine()->Animator2D()->Play(L"nutty_idle");

	CNuttyScript* pScpt = GetOwnerObj()->GetScript<CNuttyScript>();

	NuttyMoveRange = pScpt->GetMoveRange();
	NuttyDetectRange = pScpt->GetDetectRange();
	NuttyOriginPos = pScpt->GetOriginPos();
	NuttySpeed = pScpt->GetSpeed();
	
	NuttyMoveLeftPos = NuttyOriginPos.x - NuttyMoveRange;
	NuttyMoveRightPos = NuttyOriginPos.x + NuttyMoveRange;
}

void CNuttyIdleState::finaltick()
{
	Vec3 vPos = GetOwnerObj()->Transform()->GetRelativePos();

	CNuttyScript* pScpt = GetOwnerObj()->GetScript<CNuttyScript>();
	int dir = pScpt->GetCurDir();

	if ((NuttyMoveLeftPos < vPos.x) && (NuttyMoveRightPos > vPos.x)) // 너티가 이동 반경 안에 있다면
	{
		// 움직여야 함

		if (1 == dir) // 왼
		{
			GetFSM()->GetStateMachine()->Movement()->SetVelocity(Vec3(-NuttySpeed, 0.f, 0.f));
		}
		else if (0 == dir) // 오
		{
			GetFSM()->GetStateMachine()->Movement()->SetVelocity(Vec3(NuttySpeed, 0.f, 0.f));
		}
	}
	else // 이동 반경 안에 들어와있지 않다면 방향을 틀어야지
	{
		if (1 == dir)
		{
			GetFSM()->GetStateMachine()->Movement()->SetVelocity(Vec3(0.f, 0.f, 0.f));
			pScpt->SetCurDir(0); // 왼 -> 오
			GetOwnerObj()->Transform()->SetRelativePos(Vec3(vPos.x + 1, vPos.y, vPos.z));
		}
		else if (0 == dir)
		{
			GetFSM()->GetStateMachine()->Movement()->SetVelocity(Vec3(0.f, 0.f, 0.f));
			pScpt->SetCurDir(1); // 오 -> 왼
			GetOwnerObj()->Transform()->SetRelativePos(Vec3(vPos.x - 1, vPos.y, vPos.z));
		}
	}

	NuttyDetectLeftPos = vPos.x - NuttyDetectRange;
	NuttyDetectRightPos = vPos.x + NuttyDetectRange;

	Vec3 TargetPos = pScpt->GetTarget()->Transform()->GetRelativePos();

	if ((NuttyDetectLeftPos < TargetPos.x) && (NuttyDetectRightPos > TargetPos.x)) // 타겟이 감지 범위 안에 들어왔다면
	{
		if (TargetPos.x < vPos.x) // 타겟이 너티보다 왼쪽에 있음
		{
			pScpt->SetCurDir(1); // 오 -> 왼
			ChangeState(L"Detect");
		}

		else if (TargetPos.x > vPos.x) // 타겟이 너티보다 오른쪽에 있음
		{
			pScpt->SetCurDir(0); // 왼 -> 오
			ChangeState(L"Detect");
		}
	}
}

void CNuttyIdleState::Exit()
{
}
