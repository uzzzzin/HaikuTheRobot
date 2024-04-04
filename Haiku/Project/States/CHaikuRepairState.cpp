#include "pch.h"
#include "CHaikuRepairState.h"
#include <Scripts/CHaikuScript.h>


CHaikuRepairState::CHaikuRepairState()
	: CState(STATE_TYPE::HAIKUREPAIRSTATE)
	, duration(3.47f)
	, accTime(0)
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
	accTime = 0;
}

void CHaikuRepairState::finaltick()
{
	if (duration >= accTime)
	{
		accTime += DT;
	}
	else
	{
		ChangeState(L"Idle");
	}
}

void CHaikuRepairState::Exit()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetPrevStateName(L"Repair");
}