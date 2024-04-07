#include "pch.h"
#include "CHaikuJumpRiseGeneralAttackState.h"

#include <Scripts/CHaikuScript.h>

CHaikuJumpRiseGeneralAttackState::CHaikuJumpRiseGeneralAttackState()
	: CState(HAIKUJUMPRISEGENERALATTACKSTATE)
	, duration(0.6f)
	, accTime(0)
{
}

CHaikuJumpRiseGeneralAttackState::~CHaikuJumpRiseGeneralAttackState()
{
}

void CHaikuJumpRiseGeneralAttackState::Enter()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetCurStateName(L"JumpRiseGeneralAttack");
	GetFSM()->GetStateMachine()->Animator2D()->Play(L"haiku_jump_rise_gen_attack", false);

	accTime = 0;

	const vector<CGameObject*>& children = GetFSM()->GetStateMachine()->GetOwner()->GetChild();
	for (int i = 0; i < children.size(); ++i)
	{
		children[i]->Animator2D()->Play(L"sword_jump_rise_gen_attack", false);
		children[i]->Collider2D()->Activate();
	}
}

void CHaikuJumpRiseGeneralAttackState::finaltick()
{
	if (duration >= accTime)
	{
		Vec3 vVelo = GetOwnerObj()->Movement()->GetVelocity();

		if (KEY_PRESSED(KEY::SPACE))
		{
			GetOwnerObj()->Movement()->SetVelocity(Vec3(vVelo.x, vVelo.y + 0.5f, vVelo.z));

			if (KEY_PRESSED(KEY::LEFT))
			{
				GetOwnerObj()->Movement()->AddForce(Vec3(-170.f, 20.f, 0.f));
			}

			if (KEY_PRESSED(KEY::RIGHT))
			{
				GetOwnerObj()->Movement()->AddForce(Vec3(170.f, 20.f, 0.f));
			}
		}

		if (GetOwnerObj()->Movement()->IsGround())// ¶¥¿¡ ´ê¾Æ¹ö·È´Ù ;;
		{
			if ((KEY_PRESSED(KEY::RIGHT)) || (KEY_PRESSED(KEY::LEFT)))
			{
				ChangeState(L"Walk");
			}
			else if ((KEY_NONE(KEY::RIGHT)) || (KEY_NONE(KEY::LEFT)))
			{
				ChangeState(L"Idle");
			}
		}

		accTime += DT;
	}
	else
	{
		ChangeState(L"JumpFall");
	}
}

void CHaikuJumpRiseGeneralAttackState::Exit()
{
 	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetPrevStateName(L"JumpRiseGeneralAttack");

	const vector<CGameObject*>& children = GetFSM()->GetStateMachine()->GetOwner()->GetChild();
	for (int i = 0; i < children.size(); ++i)
	{
		children[i]->Animator2D()->Play(L"sword_null", false);
		children[i]->Collider2D()->Deactivate();
	}
}
