#include "pch.h"
#include "CHaikuJumpFallState.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include <Scripts/CHaikuScript.h>
#include <Engine/CCollisionMgr.h>

CHaikuJumpFallState::CHaikuJumpFallState()
	:CState(HAIKUJUMPFALLSTATE)
{
}

CHaikuJumpFallState::~CHaikuJumpFallState()
{
}


void CHaikuJumpFallState::Enter()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetCurStateName(L"JumpFall");

	GetFSM()->GetStateMachine()->Animator2D()->Play(L"haiku_fall");
}

void CHaikuJumpFallState::finaltick()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();

	if (KEY_PRESSED(KEY::LEFT)) //점프중인데 이동중인 상태라면
	{
		GetOwnerObj()->Movement()->AddForce(Vec3(-170.f, 0.f, 0.f));
	}

	if ((KEY_PRESSED(KEY::RIGHT)))
	{
		GetOwnerObj()->Movement()->AddForce(Vec3(170.f, 0.f, 0.f));
	}

	if (GetOwnerObj()->Movement()->IsGround())// 땅에 닿아버렸다 ;;
	{
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

void CHaikuJumpFallState::Exit()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetPrevStateName(L"JumpFall");
}