#include "pch.h"
#include "CHaikuDashState.h"

#include <Scripts/CHaikuScript.h>

CHaikuDashState::CHaikuDashState()
	: CState(STATE_TYPE::HAIKUDASHSTATE)
	, duration (0.18f)
	, accTime (0)
	, dashLength(180.f)
	, dashSpeed (0)
{
	dashSpeed = dashLength / duration;
}

CHaikuDashState::~CHaikuDashState()
{
}

void CHaikuDashState::DashSet()
{

}

void CHaikuDashState::Enter()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();

	if (pScpt->GetPrevStateName() != L"Idle") // Idle���� �� �� �ƴ϶�� ������������ ���� ����;;
	{
		ChangeState(pScpt->GetPrevStateName()); // �ٽ� �������� ���ư����� 
	}
	else // Idle���� �Խ��ϴ� 
	{
		pScpt->SetCurStateName(L"Dash");
		GetFSM()->GetStateMachine()->Animator2D()->Play(L"haiku_dash");
		accTime = 0;
		
		if (pScpt->GetCurDir()) // true �� left, false �� right
		{
			afterDashPos = Vec3(GetOwnerObj()->Transform()->GetRelativePos().x - dashLength,
				GetOwnerObj()->Transform()->GetRelativePos().y, GetOwnerObj()->Transform()->GetRelativePos().z);
		}
		else
		{
			afterDashPos = Vec3(GetOwnerObj()->Transform()->GetRelativePos().x + dashLength,
				GetOwnerObj()->Transform()->GetRelativePos().y, GetOwnerObj()->Transform()->GetRelativePos().z);
		}
	}
}

void CHaikuDashState::finaltick()
{
	// ��� �ִϸ��̼��̶� ������ ������ �ٽ� Idle
	// �׷��� ��� ������ ���� ��?
	Vec3 pPos = GetOwnerObj()->Transform()->GetRelativePos();

	if (duration >= accTime)
	{
		CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
		
		Vec3 dir = Vec3(afterDashPos.x - pPos.x, 0, 0);
		dir.Normalize();
		pPos += dir * dashSpeed * DT;

		GetOwnerObj()->Transform()->SetRelativePos(pPos);
		accTime += DT;
	}
	else
	{
		// ��� ��
		int a = 0;
		ChangeState(L"Idle");
	}
}

void CHaikuDashState::Exit()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();


	if (pScpt->GetCurStateName() != L"Dash") // ���������� ���� Dash
	{
		return;
	}
	else // ���� Dash
	{
		pScpt->SetPrevStateName(L"Dash");
	}
}