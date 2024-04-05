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
	// haiku_jump_rise_down_attack
}

void CHaikuJumpRiseDownAttackState::finaltick()
{
}

void CHaikuJumpRiseDownAttackState::Exit()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetPrevStateName(L"JumpRiseDownAttack");
}

