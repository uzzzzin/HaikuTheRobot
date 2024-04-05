#include "pch.h"
#include "CHaikuWalkState.h"

#include <Engine/CKeyMgr.h>

#include <Scripts/CHaikuScript.h>

CHaikuWalkState::CHaikuWalkState()
	:CState(STATE_TYPE::HAIKUWALKSTATE)
{
}

CHaikuWalkState::~CHaikuWalkState()
{
}

void CHaikuWalkState::Enter()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetCurStateName(L"Walk");
	GetFSM()->GetStateMachine()->Animator2D()->Play(L"haiku_walk");
}


void CHaikuWalkState::finaltick()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();

	if (KEY_TAP(KEY::SPACE))
	{
		ChangeState(L"JumpRise");
	}

	if (KEY_TAP(KEY::C))
	{
		ChangeState(L"Dash");
	}

	if (KEY_PRESSED(KEY::LEFT) && KEY_NONE(KEY::RIGHT) && GetFSM()->GetStateMachine()->Movement()->IsGround()) 
	{
		GetFSM()->GetStateMachine()->Movement()->SetVelocity(Vec3(-400.f, 0.f, 0.f));
	}

	if (KEY_PRESSED(KEY::RIGHT) && KEY_NONE(KEY::LEFT) && GetFSM()->GetStateMachine()->Movement()->IsGround())
	{
		GetFSM()->GetStateMachine()->Movement()->SetVelocity(Vec3(400.f, 0.f, 0.f));
	}

	if (KEY_RELEASED(KEY::LEFT))
	{
		if (KEY_NONE(KEY::RIGHT))
		{
			GetFSM()->GetStateMachine()->Movement()->SetVelocity(Vec3());
			ChangeState(L"Idle");
		}
	}
	if (KEY_RELEASED(KEY::RIGHT))
	{
		if (KEY_NONE(KEY::LEFT))
		{
			GetFSM()->GetStateMachine()->Movement()->SetVelocity(Vec3());
			ChangeState(L"Idle");
		}
	}
}


void CHaikuWalkState::Exit()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetPrevStateName(L"Walk");
}
