#include "pch.h"
#include "CHaikuPlatformGeneralAttackState.h"

#include <Scripts/CHaikuScript.h>

CHaikuPlatformGeneralAttackState::CHaikuPlatformGeneralAttackState()
	:CState(HAIKUPLATFORMGENERALATTACKSTATE)
	, duration(0.65f)
	, accTime(0)
{
}

CHaikuPlatformGeneralAttackState::~CHaikuPlatformGeneralAttackState()
{
}


void CHaikuPlatformGeneralAttackState::Enter()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetCurStateName(L"PlatformGeneralAttack");

	accTime = 0;

	const vector<CGameObject*>& children = GetFSM()->GetStateMachine()->GetOwner()->GetChild();

	pScpt->ChangeGeneralAttackSeed();
	bool bb = pScpt->GetGeneralAttackSeed();

	if (bb)
	{
		GetFSM()->GetStateMachine()->Animator2D()->Play(L"haiku_generalAttack1", false);
		for (int i = 0; i < children.size(); ++i)
		{
			children[i]->Animator2D()->Play(L"sword_generalAttack1", false);
			children[i]->Collider2D()->Activate();
		}
	}
	else
	{
		GetFSM()->GetStateMachine()->Animator2D()->Play(L"haiku_generalAttack2", false);
		for (int i = 0; i < children.size(); ++i)
		{
			children[i]->Animator2D()->Play(L"sword_generalAttack2", false);
			children[i]->Collider2D()->Activate();
		}
	}

}

void CHaikuPlatformGeneralAttackState::finaltick()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();

	if (duration >= accTime)
	{
		accTime += DT;
	}
	else
	{
		//ChangeState(pScpt->GetPrevStateName());
		ChangeState(L"Idle");
	}
}

void CHaikuPlatformGeneralAttackState::Exit()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetPrevStateName(L"PlatformGeneralAttack");

	const vector<CGameObject*>& children = GetFSM()->GetStateMachine()->GetOwner()->GetChild();
	for (int i = 0; i < children.size(); ++i)
	{
		children[i]->Animator2D()->Play(L"sword_null", false);
		children[i]->Collider2D()->Deactivate();
	}
}