#include "pch.h"
#include "CHaikuDashState.h"

#include <Scripts/CHaikuScript.h>

CHaikuDashState::CHaikuDashState()
	: CState(STATE_TYPE::HAIKUDASHSTATE)
	, duration (0.15f)
	, accTime (0)
	, dashLength(110.f)
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
	pScpt->SetCurStateName(L"Dash");
	GetFSM()->GetStateMachine()->Animator2D()->Play(L"haiku_dash");
	accTime = 0;
		
	if (1 == pScpt->GetCurDir()) // true 면 left, false 면 right
	{
		afterDashPos = Vec3(GetOwnerObj()->Transform()->GetRelativePos().x - dashLength,
			GetOwnerObj()->Transform()->GetRelativePos().y, GetOwnerObj()->Transform()->GetRelativePos().z);
	}
	else if (0 == pScpt->GetCurDir())
	{
		afterDashPos = Vec3(GetOwnerObj()->Transform()->GetRelativePos().x + dashLength,
			GetOwnerObj()->Transform()->GetRelativePos().y, GetOwnerObj()->Transform()->GetRelativePos().z);
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
		if ((KEY_PRESSED(KEY::RIGHT)) || (KEY_PRESSED(KEY::LEFT)))
		{
			ChangeState(L"Walk");
		}
		else if ((KEY_NONE(KEY::RIGHT)) || (KEY_NONE(KEY::LEFT)))
		{
			ChangeState(L"Idle");
		}
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