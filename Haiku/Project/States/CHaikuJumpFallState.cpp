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
	wstring colName = pScpt->GetColPlatformName();

	if (L"" != colName)
	{
		CLevel* curLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		CGameObject* colPlatform = curLevel->FindObjectByName(colName);
		
		if (CCollisionMgr::GetInst()->IsCollision(GetOwnerObj()->Collider2D(), colPlatform->Collider2D()))
		{
			GetOwnerObj()->Movement()->SetVelocity(Vec3());
			ChangeState(L"Idle");
		}
	}

	if (KEY_PRESSED(KEY::LEFT)) //점프중인데 이동중인 상태라면
	{
		GetOwnerObj()->Movement()->AddForce(Vec3(-400.f, 0.f, 0.f) * DT);
	}

	if ((KEY_PRESSED(KEY::RIGHT)))
	{
		GetOwnerObj()->Movement()->AddForce(Vec3(400.f, 0.f, 0.f) * DT);
	}
}

void CHaikuJumpFallState::Exit()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetPrevStateName(L"JumpFall");
}