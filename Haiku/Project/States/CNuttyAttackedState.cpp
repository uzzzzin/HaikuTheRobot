#include "pch.h"
#include "CNuttyAttackedState.h"

#include <Engine/CTransform.h>
#include <Engine/CStateMachine.h>
#include <Engine/CAnimator2D.h>

CNuttyAttackedState::CNuttyAttackedState()
	: CState(STATE_TYPE::NUTTYATTACKEDSTATE)
	, duration(0.1f)
	, accTime(0)
{
}

CNuttyAttackedState::~CNuttyAttackedState()
{
}


void CNuttyAttackedState::Enter()
{
	accTime = 0;
	GetFSM()->GetStateMachine()->Animator2D()->Play(L"nutty_idle");
	diePos = GetOwnerObj()->Transform()->GetRelativePos();
}

void CNuttyAttackedState::finaltick()
{
	if (duration > accTime)
	{
		accTime += DT;
		GetOwnerObj()->Transform()->SetRelativePos(diePos);
	}
	else
	{
		GamePlayStatic::DestroyGameObject(GetOwnerObj());
	}
}

void CNuttyAttackedState::Exit()
{
}