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

	if (pScpt->GetPrevStateName() != L"Idle") // Idle에서 온 게 아니라면 비정상적으로 들어온 거임;;
	{
		ChangeState(pScpt->GetPrevStateName()); // 다시 이전으로 돌아가세용 
	}
	else // Idle에서 왔습니다 
	{
		pScpt->SetCurStateName(L"Dash");
		GetFSM()->GetStateMachine()->Animator2D()->Play(L"haiku_dash");
		accTime = 0;
		
		if (pScpt->GetCurDir()) // true 면 left, false 면 right
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
	// 대시 애니메이션이랑 움직임 끝나면 다시 Idle
	// 그래서 대시 움직임 어케 함?
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
		// 대시 끝
		int a = 0;
		ChangeState(L"Idle");
	}
}

void CHaikuDashState::Exit()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();


	if (pScpt->GetCurStateName() != L"Dash") // 정상적이지 않은 Dash
	{
		return;
	}
	else // 정상 Dash
	{
		pScpt->SetPrevStateName(L"Dash");
	}
}