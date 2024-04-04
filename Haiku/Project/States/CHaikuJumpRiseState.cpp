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
	// �����̽� ������ �߰ų�
	if (KEY_RELEASED(KEY::SPACE))
	{
		ChangeState(L"JumpFall");
	}

	// �ƽø� ������ �ð��� �ѱ���� �ϰų�
	// õ�忡 �ε����ų�

	Vec3 vVelo = GetOwnerObj()->Movement()->GetVelocity();

	if (KEY_PRESSED(KEY::SPACE))
	{
		GetOwnerObj()->Movement()->SetVelocity(Vec3(vVelo.x, vVelo.y + 0.5f, vVelo.z));
	}

	if (KEY_PRESSED(KEY::LEFT)&& KEY_PRESSED(KEY::SPACE)) //�������ε� �̵����� ���¶��
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
