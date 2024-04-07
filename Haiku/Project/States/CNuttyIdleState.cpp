#include "pch.h"
#include "CNuttyIdleState.h"

#include <Engine/CStateMachine.h>

#include <Engine/CAnimator2D.h>

#include <Scripts/CNuttyScript.h>

CNuttyIdleState::CNuttyIdleState()
	:CState(STATE_TYPE::NUTTYIDLESTATE)
{
}

CNuttyIdleState::~CNuttyIdleState()
{
}

void CNuttyIdleState::Enter()
{
	GetFSM()->GetStateMachine()->Animator2D()->Play(L"nutty_idle");

	CNuttyScript* pScpt = GetOwnerObj()->GetScript<CNuttyScript>();

	NuttyMoveRange = pScpt->GetMoveRange();
	NuttyDetectRange = pScpt->GetDetectRange();
	NuttyOriginPos = pScpt->GetOriginPos();
	NuttySpeed = pScpt->GetSpeed();
	
	NuttyMoveLeftPos = NuttyOriginPos.x - NuttyMoveRange;
	NuttyMoveRightPos = NuttyOriginPos.x + NuttyMoveRange;
}

void CNuttyIdleState::finaltick()
{
	Vec3 vPos = GetOwnerObj()->Transform()->GetRelativePos();

	CNuttyScript* pScpt = GetOwnerObj()->GetScript<CNuttyScript>();
	int dir = pScpt->GetCurDir();

	if ((NuttyMoveLeftPos < vPos.x) && (NuttyMoveRightPos > vPos.x)) // ��Ƽ�� �̵� �ݰ� �ȿ� �ִٸ�
	{
		// �������� ��

		if (1 == dir) // ��
		{
			GetFSM()->GetStateMachine()->Movement()->SetVelocity(Vec3(-NuttySpeed, 0.f, 0.f));
		}
		else if (0 == dir) // ��
		{
			GetFSM()->GetStateMachine()->Movement()->SetVelocity(Vec3(NuttySpeed, 0.f, 0.f));
		}
	}
	else // �̵� �ݰ� �ȿ� �������� �ʴٸ� ������ Ʋ�����
	{
		if (1 == dir)
		{
			GetFSM()->GetStateMachine()->Movement()->SetVelocity(Vec3(0.f, 0.f, 0.f));
			pScpt->SetCurDir(0); // �� -> ��
			GetOwnerObj()->Transform()->SetRelativePos(Vec3(vPos.x + 1, vPos.y, vPos.z));
		}
		else if (0 == dir)
		{
			GetFSM()->GetStateMachine()->Movement()->SetVelocity(Vec3(0.f, 0.f, 0.f));
			pScpt->SetCurDir(1); // �� -> ��
			GetOwnerObj()->Transform()->SetRelativePos(Vec3(vPos.x - 1, vPos.y, vPos.z));
		}
	}

	NuttyDetectLeftPos = vPos.x - NuttyDetectRange;
	NuttyDetectRightPos = vPos.x + NuttyDetectRange;

	Vec3 TargetPos = pScpt->GetTarget()->Transform()->GetRelativePos();

	if ((NuttyDetectLeftPos < TargetPos.x) && (NuttyDetectRightPos > TargetPos.x)) // Ÿ���� ���� ���� �ȿ� ���Դٸ�
	{
		if (TargetPos.x < vPos.x) // Ÿ���� ��Ƽ���� ���ʿ� ����
		{
			pScpt->SetCurDir(1); // �� -> ��
			ChangeState(L"Detect");
		}

		else if (TargetPos.x > vPos.x) // Ÿ���� ��Ƽ���� �����ʿ� ����
		{
			pScpt->SetCurDir(0); // �� -> ��
			ChangeState(L"Detect");
		}
	}
}

void CNuttyIdleState::Exit()
{
}
