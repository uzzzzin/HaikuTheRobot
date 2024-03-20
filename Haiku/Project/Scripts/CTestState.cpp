#include "pch.h"
#include "CTestState.h"

#include <Engine/CGameObject.h>
#include <Engine/CStateMachine.h>
#include <Engine/CTransform.h>

CTestState::CTestState()
{
}

CTestState::~CTestState()
{
}

void CTestState::finaltick()
{
	// �÷��̾ ��ó�� ������, Trace ���·� �����Ѵ�.
	float DetectRange = *((float*)GetBlackboardData(L"DetectRange"));
	CGameObject* pTarget = ((CGameObject*)GetBlackboardData(L"TargetObject"));

	CGameObject* pSelf = GetFSM()->GetStateMachine()->GetOwner();

	Vec3 vDist = pTarget->Transform()->GetWorldPos() - pSelf->Transform()->GetWorldPos();

	GamePlayStatic::DrawDebugCircle(pSelf->Transform()->GetWorldPos(), DetectRange, Vec3(0.1f, 1.f, 0.1f), 0.f);

	if (vDist.Length() <= DetectRange)
	{
		// �������·� �����Ѵ�.
		ChangeState(L"TraceState");
	}
}

void CTestState::Enter()
{

}

void CTestState::Exit()
{

}