#include "pch.h"
#include "CHaikuJumpRiseGeneralAttackState.h"

#include <Scripts/CHaikuScript.h>

CHaikuJumpRiseGeneralAttackState::CHaikuJumpRiseGeneralAttackState()
	: CState(HAIKUJUMPRISEGENERALATTACKSTATE)
{
}

CHaikuJumpRiseGeneralAttackState::~CHaikuJumpRiseGeneralAttackState()
{
}

void CHaikuJumpRiseGeneralAttackState::Enter()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetCurStateName(L"JumpRiseGeneralAttack");
	//haiku_jump_rise_gen_attack
}

void CHaikuJumpRiseGeneralAttackState::finaltick()
{
}

void CHaikuJumpRiseGeneralAttackState::Exit()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetPrevStateName(L"JumpRiseGeneralAttack");
}
