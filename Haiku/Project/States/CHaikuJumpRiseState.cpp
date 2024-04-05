#include "pch.h"
#include "CHaikuJumpRiseState.h"

#include <ENgine/CKeyMgr.h>
#include <Scripts/CHaikuScript.h>

CHaikuJumpRiseState::CHaikuJumpRiseState()
	:CState(HAIKUJUMPRISESTATE)
	, duration(1.f)
	, accTime(0)
{
}

CHaikuJumpRiseState::~CHaikuJumpRiseState()
{
}

void CHaikuJumpRiseState::Enter()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetCurStateName(L"JumpRise");

	GetOwnerObj()->Animator2D()->Play(L"haiku_rise", false);
	accTime = 0;
	GetOwnerObj()->Movement()->SetGround(false);
	GetOwnerObj()->Movement()->SetVelocity(Vec3(0, 250, 0));
}

void CHaikuJumpRiseState::finaltick()
{
	// 스페이스 릴리즈 했거나
	// 맥시멈 프레스 시간을 넘기려고 하거나
	// 천장에 부딪혔거나

	if(duration >= accTime)
	{
		if (LAST_COL_DIR::DOWN == GetOwnerObj()->Collider2D()->GetLastColDir())
		{
			ChangeState(L"JumpFall");
		}

		if (KEY_RELEASED(KEY::SPACE))
		{
			ChangeState(L"JumpFall");
		}

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
		accTime += DT;
	}
	else
	{
		ChangeState(L"JumpFall");
	}
}

void CHaikuJumpRiseState::Exit()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetPrevStateName(L"JumpRise");
}
