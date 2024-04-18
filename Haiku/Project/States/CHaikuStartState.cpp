#include "pch.h"
#include "CHaikuStartState.h"

#include <Engine/CAnimator2D.h>
#include <Engine/CMovement.h>

#include <Engine/CCollisionMgr.h>
#include <Engine/CKeyMgr.h>
#include <Scripts/CHaikuScript.h>

#include <Engine/CFontMgr.h>

CHaikuStartState::CHaikuStartState()
	:CState(HAIKUSTARTSTATE)
	//, duration(3.5f)
	//, accTime(0)
{
}

CHaikuStartState::~CHaikuStartState()
{
}

void CHaikuStartState::Enter()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetCurStateName(L"Start");
	GetOwnerObj()->Movement()->SetGround(true);

	if (L"None" == pScpt->GetPrevStateName()) // 인트로 없이
	{
		GetOwnerObj()->Animator2D()->Play(L"haiku_null");
	}

	if (L"Intro" == pScpt->GetPrevStateName()) // 인트로에서 넘어온
	{
		GetOwnerObj()->Animator2D()->Play(L"haiku_intro_null");
	}

	//accTime = 0;

	const vector<CGameObject*>& children = GetFSM()->GetStateMachine()->GetOwner()->GetChild();
	for (int i = 0; i < children.size(); ++i)
	{
		children[i]->Animator2D()->Play(L"sword_null");
		children[i]->Collider2D()->Deactivate();
	}
}

void CHaikuStartState::finaltick()
{
	//accTime += DT;

	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();

	if (L"None" == pScpt->GetPrevStateName()) // 인트로 없이
	{
		//if ((KEY_TAP(KEY::Q)))
		//{
		//	GetOwnerObj()->Animator2D()->Play(L"haiku_fall");
		//	GetOwnerObj()->Movement()->SetGround(false);
		//	GetOwnerObj()->Movement()->SetGravityForce(Vec3(0, -1, 0));
		//}
		if ((KEY_PRESSED(KEY::RIGHT)) || (KEY_PRESSED(KEY::LEFT)))
			ChangeState(L"Walk");
		else
			ChangeState(L"Idle");
	}

	if (L"Intro" == pScpt->GetPrevStateName()) // 인트로에서 넘어온
	{

	}
}

void CHaikuStartState::Exit()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetPrevStateName(L"Start");
}
