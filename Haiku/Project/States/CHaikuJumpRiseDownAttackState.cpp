#include "pch.h"
#include "CHaikuJumpRiseDownAttackState.h"
#include <Scripts/CHaikuScript.h>

CHaikuJumpRiseDownAttackState::CHaikuJumpRiseDownAttackState()
	: CState(HAIKUJUMPRISEDOWNATTACKSTATE)
{
}

CHaikuJumpRiseDownAttackState::~CHaikuJumpRiseDownAttackState()
{
}

void CHaikuJumpRiseDownAttackState::Enter()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetCurStateName(L"JumpRiseDownAttack");
	GetFSM()->GetStateMachine()->Animator2D()->Play(L"haiku_jump_rise_down_attack");
}

void CHaikuJumpRiseDownAttackState::finaltick()
{
}

void CHaikuJumpRiseDownAttackState::Exit()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetPrevStateName(L"JumpRiseDownAttack");
}

