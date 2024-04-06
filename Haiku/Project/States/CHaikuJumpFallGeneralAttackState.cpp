#include "pch.h"
#include "CHaikuJumpFallGeneralAttackState.h"
#include <Scripts/CHaikuScript.h>

CHaikuJumpFallGeneralAttackState::CHaikuJumpFallGeneralAttackState()
	:CState(STATE_TYPE::HAIKUJUMPFALLGENERALATTACKSTATE)
	, duration(0.6f)
	, accTime(0)
{
}

CHaikuJumpFallGeneralAttackState::~CHaikuJumpFallGeneralAttackState()
{
}


void CHaikuJumpFallGeneralAttackState::Enter()
{
	accTime = 0;
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetCurStateName(L"JumpFallGeneralAttack");
	GetFSM()->GetStateMachine()->Animator2D()->Play(L"haiku_jump_fall_gen_attack", false);

	const vector<CGameObject*>& children = GetFSM()->GetStateMachine()->GetOwner()->GetChild();
	for (int i = 0; i < children.size(); ++i)
	{
		children[i]->Animator2D()->Play(L"sword_jump_fall_gen_attack");
	}

}

void CHaikuJumpFallGeneralAttackState::finaltick()
{
	if (KEY_PRESSED(KEY::LEFT)) //점프중인데 이동중인 상태라면
	{
		GetOwnerObj()->Movement()->AddForce(Vec3(-170.f, 0.f, 0.f));
	}

	if ((KEY_PRESSED(KEY::RIGHT)))
	{
		GetOwnerObj()->Movement()->AddForce(Vec3(170.f, 0.f, 0.f));
	}

	if (GetOwnerObj()->Movement()->IsGround())// 땅에 닿아버렸다 ;;
	{
		if ((KEY_PRESSED(KEY::RIGHT)) || (KEY_PRESSED(KEY::LEFT)))
		{
			ChangeState(L"Walk");
			//if (duration <= accTime)
			//{
			//	ChangeState(L"Walk");
			//}
		}
		else if ((KEY_NONE(KEY::RIGHT)) || (KEY_NONE(KEY::LEFT)))
		{
			ChangeState(L"Idle");
			//if (duration <= accTime)
			//{
			//	ChangeState(L"Idle");
			//}
		}
	}
	accTime += DT;
}

void CHaikuJumpFallGeneralAttackState::Exit()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetPrevStateName(L"JumpFallGeneralAttack");
}