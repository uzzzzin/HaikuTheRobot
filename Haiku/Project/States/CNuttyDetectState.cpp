#include "pch.h"
#include "CNuttyDetectState.h"

#include <Engine/CStateMachine.h>

#include <Engine/CAnimator2D.h>

CNuttyDetectState::CNuttyDetectState()
	: CState(STATE_TYPE::NUTTYDETECTSTATE)
	, duration(0.4f)
	, accTime(0)
{
}

CNuttyDetectState::~CNuttyDetectState()
{
}

void CNuttyDetectState::Enter()
{
	accTime = 0;
	GetFSM()->GetStateMachine()->Animator2D()->Play(L"nutty_detect", false);
}

void CNuttyDetectState::finaltick()
{
	if (duration >= accTime)
	{
		accTime += DT;
	}
	else
	{
		ChangeState(L"Trace");
	}
}

void CNuttyDetectState::Exit()
{
}
