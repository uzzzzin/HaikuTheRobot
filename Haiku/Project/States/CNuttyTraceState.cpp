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

	// Ÿ���� ���� ������ ����ų� Ÿ���̶� �浹�ϸ� ü���� ������Ʈ
	Vec3 vPos = GetOwnerObj()->Transform()->GetRelativePos();

	NuttyDetectLeftPos = vPos.x - NuttyDetectRange;
	NuttyDetectRightPos = vPos.x + NuttyDetectRange;

	Vec3 TargetPos = pScpt->GetTarget()->Transform()->GetRelativePos();

	if ((NuttyDetectLeftPos < TargetPos.x) && (NuttyDetectRightPos > TargetPos.x)) // Ÿ���� ���� ���� �ȿ� �ִ� ���¶��
	{
		if (TargetPos.x < vPos.x) // Ÿ���� ��Ƽ���� ���ʿ� ����
		{
			pScpt->SetCurDir(1);
			GetFSM()->GetStateMachine()->Movement()->SetVelocity(Vec3(-pScpt->GetSpeed()*2, 0.f, 0.f));
		}

		else if (TargetPos.x > vPos.x) // Ÿ���� ��Ƽ���� �����ʿ� ����
		{
			pScpt->SetCurDir(0);
			GetFSM()->GetStateMachine()->Movement()->SetVelocity(Vec3(pScpt->GetSpeed()*2, 0.f, 0.f));
		}

		//if(TargetPos.x == vPos.x && TargetPos.y == vPos.y)
	}
	else // Ÿ���� ���� ������ ��� ���¶��
	{
		ChangeState(L"Idle");
	}
}

void CNuttyTraceState::Exit()
{

}
