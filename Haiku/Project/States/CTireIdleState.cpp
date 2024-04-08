#include "pch.h"
#include "CTireIdleState.h"

#include <Engine/CStateMachine.h>
#include <Engine/CAnimator2D.h>

CTireIdleState::CTireIdleState()
	: CState(STATE_TYPE::TIREIDLESTATE)
{
}

CTireIdleState::~CTireIdleState()
{
}

void CTireIdleState::Enter()
{
	GetFSM()->GetStateMachine()->Animator2D()->Play(L"TiredTire_idle");
}

void CTireIdleState::finaltick()
{
}

void CTireIdleState::Exit()
{
}
