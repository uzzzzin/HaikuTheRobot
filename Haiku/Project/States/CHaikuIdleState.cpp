#include "pch.h"
#include "CHaikuIdleState.h"


#include <Engine/CStateMachine.h>

#include <Engine/CAnimator2D.h>

#include <ENgine/CKeyMgr.h>


#include <Scripts/CHaikuScript.h>

CHaikuIdleState::CHaikuIdleState()
	: CState(STATE_TYPE::HAIKUIDLESTATE)
{
}

CHaikuIdleState::~CHaikuIdleState()
{
}

void CHaikuIdleState::Enter()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetCurStateName(L"Idle");

	GetFSM()->GetStateMachine()->Animator2D()->Play(L"haiku_idle");
}

void CHaikuIdleState::finaltick()
{

	if (KEY_TAP(KEY::C))
	{
		ChangeState(L"Dash");
	}

	if (KEY_TAP(KEY::D))
	{
		ChangeState(L"Repair");
	}

	if (KEY_TAP(KEY::SPACE))
	{
		ChangeState(L"JumpRise");
	}

	if (KEY_TAP(KEY::X))
	{
		ChangeState(L"PlatformGeneralAttack");
	}

	//if (몬스터에게 피해를 입으면)
	//{
	//	GetFSM()->ChangeState(L"Attacked");
	//}
}

void CHaikuIdleState::Exit()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetPrevStateName(L"Idle");
}