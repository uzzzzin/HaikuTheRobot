#include "pch.h"
#include "CTireDieState.h"


CTireDieState::CTireDieState()
	: CState(TIREDIESTATE)
	, duration(0.2f)
	, accTime(0)
{
}

CTireDieState::~CTireDieState()
{
}

void CTireDieState::Enter()
{
	accTime = 0;
	diePos = GetOwnerObj()->Transform()->GetRelativePos();
}

void CTireDieState::finaltick()
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

void CTireDieState::Exit()
{
}

