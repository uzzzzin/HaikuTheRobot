#include "pch.h"
#include "CHaikuJumpRiseUpAttackState.h"
#include <Scripts/CHaikuScript.h>


CHaikuJumpRiseUpAttackState::CHaikuJumpRiseUpAttackState()
	: CState(HAIKUJUMPRISEUPATTACKSTATE)
{
}

CHaikuJumpRiseUpAttackState::~CHaikuJumpRiseUpAttackState()
{
}

void CHaikuJumpRiseUpAttackState::Enter()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetCurStateName(L"JumpRiseUpAttack");
	// haiku_jump_rise_up_attack
}

void CHaikuJumpRiseUpAttackState::finaltick()
{
}

void CHaikuJumpRiseUpAttackState::Exit()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetPrevStateName(L"JumpRiseUpAttack");
}