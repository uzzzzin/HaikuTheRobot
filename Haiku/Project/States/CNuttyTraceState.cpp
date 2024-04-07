#include "pch.h"
#include "CNuttyTraceState.h"

#include <Engine/CStateMachine.h>

#include <Engine/CAnimator2D.h>

#include <Scripts/CNuttyScript.h>

CNuttyTraceState::CNuttyTraceState()
	: CState(STATE_TYPE::NUTTYTRACESTATE)
{
}

CNuttyTraceState::~CNuttyTraceState()
{
}

void CNuttyTraceState::Enter()
{
	GetFSM()->GetStateMachine()->Animator2D()->Play(L"nutty_trace");

	CNuttyScript* pScpt = GetOwnerObj()->GetScript<CNuttyScript>();
	NuttyDetectRange = pScpt->GetDetectRange();
}

void CNuttyTraceState::finaltick()
{
	CNuttyScript* pScpt = GetOwnerObj()->GetScript<CNuttyScript>();

	// 타겟이 감지 범위를 벗어나거나 타겟이랑 충돌하면 체인지 스테이트
	Vec3 vPos = GetOwnerObj()->Transform()->GetRelativePos();

	NuttyDetectLeftPos = vPos.x - NuttyDetectRange;
	NuttyDetectRightPos = vPos.x + NuttyDetectRange;

	Vec3 TargetPos = pScpt->GetTarget()->Transform()->GetRelativePos();

	if ((NuttyDetectLeftPos < TargetPos.x) && (NuttyDetectRightPos > TargetPos.x)) // 타겟이 감지 범위 안에 있는 상태라면
	{
		if (TargetPos.x < vPos.x) // 타겟이 너티보다 왼쪽에 있음
		{
			pScpt->SetCurDir(1);
			GetFSM()->GetStateMachine()->Movement()->SetVelocity(Vec3(-pScpt->GetSpeed()*2, 0.f, 0.f));
		}

		else if (TargetPos.x > vPos.x) // 타겟이 너티보다 오른쪽에 있음
		{
			pScpt->SetCurDir(0);
			GetFSM()->GetStateMachine()->Movement()->SetVelocity(Vec3(pScpt->GetSpeed()*2, 0.f, 0.f));
		}

		//if(TargetPos.x == vPos.x && TargetPos.y == vPos.y)
	}
	else // 타겟이 감지 범위를 벗어난 상태라면
	{
		ChangeState(L"Idle");
	}
}

void CNuttyTraceState::Exit()
{

}
