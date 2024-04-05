#include "pch.h"
#include "CHaikuPlatformGeneralAttackState.h"

#include <Scripts/CHaikuScript.h>

CHaikuPlatformGeneralAttackState::CHaikuPlatformGeneralAttackState()
	:CState(HAIKUPLATFORMGENERALATTACKSTATE)
	, duration(0.77f)
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
	bool bb = pScpt->GetGeneralAttackSeed();
	if (bb)
	{
		GetFSM()->GetStateMachine()->Animator2D()->Play(L"haiku_generalAttack1", false);
	}
	else
	{
		GetFSM()->GetStateMachine()->Animator2D()->Play(L"haiku_generalAttack2", false);
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
		ChangeState(pScpt->GetPrevStateName());
	}
}

void CHaikuPlatformGeneralAttackState::Exit()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetPrevStateName(L"PlatformGeneralAttack");

	pScpt->ChangeGeneralAttackSeed();
}