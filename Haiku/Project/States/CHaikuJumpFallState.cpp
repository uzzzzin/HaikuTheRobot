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


	if (KEY_PRESSED(KEY::LEFT)) //�������ε� �̵����� ���¶��
	{
		GetOwnerObj()->Movement()->AddForce(Vec3(-150.f, 0.f, 0.f));
	}

	if ((KEY_PRESSED(KEY::RIGHT)))
	{
		GetOwnerObj()->Movement()->AddForce(Vec3(150.f, 0.f, 0.f));
	}

	if (GetOwnerObj()->Movement()->IsGround())// ���� ��ƹ��ȴ� ;;
	{
	 	ChangeState(L"Idle");
	}
}

void CHaikuJumpFallState::Exit()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetPrevStateName(L"JumpFall");
}