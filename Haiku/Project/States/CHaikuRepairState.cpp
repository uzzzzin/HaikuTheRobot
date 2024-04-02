#include "pch.h"
#include "CHaikuRepairState.h"
#include <Scripts/CHaikuScript.h>


CHaikuRepairState::CHaikuRepairState()
	: CState(STATE_TYPE::HAIKUREPAIRSTATE)
{
}

CHaikuRepairState::~CHaikuRepairState()
{
}


void CHaikuRepairState::Enter()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetCurStateName(L"Repair");

	GetFSM()->GetStateMachine()->Animator2D()->Play(L"haiku_repair", false);
}

void CHaikuRepairState::finaltick()
{
	if (KEY_TAP(KEY::G))
		ChangeState(L"Idle");
}

void CHaikuRepairState::Exit()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetPrevStateName(L"Repair");
}