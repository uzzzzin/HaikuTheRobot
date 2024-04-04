#include "pch.h"
#include "CHaikuJumpRiseState.h"

#include <ENgine/CKeyMgr.h>
#include <Scripts/CHaikuScript.h>

CHaikuJumpRiseState::CHaikuJumpRiseState()
	:CState(HAIKUJUMPRISESTATE)
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

	GetOwnerObj()->Movement()->SetGround(false);
	GetOwnerObj()->Movement()->SetVelocity(Vec3(0, 250, 0));
}

void CHaikuJumpRiseState::finaltick()
{
	// 스페이스 릴리즈 했거나
	if (KEY_RELEASED(KEY::SPACE))
	{
		ChangeState(L"JumpFall");
	}

	// 맥시멈 프레스 시간을 넘기려고 하거나
	// 천장에 부딪혔거나

	Vec3 vVelo = GetOwnerObj()->Movement()->GetVelocity();

	if (KEY_PRESSED(KEY::SPACE))
	{
		GetOwnerObj()->Movement()->SetVelocity(Vec3(vVelo.x, vVelo.y + 0.5f, vVelo.z));
	}

	if (KEY_PRESSED(KEY::LEFT)&& KEY_PRESSED(KEY::SPACE)) //점프중인데 이동중인 상태라면
	{
		GetOwnerObj()->Movement()->AddForce(Vec3(-150.f, 40.f, 0.f));
	}

	if (KEY_PRESSED(KEY::RIGHT)&& KEY_PRESSED(KEY::SPACE))
	{
		GetOwnerObj()->Movement()->AddForce(Vec3(150.f, 40.f, 0.f));
	}
}

void CHaikuJumpRiseState::Exit()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetPrevStateName(L"JumpRise");
}
