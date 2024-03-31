#include "pch.h"
#include "CHaikuStartState.h"

#include <Engine/CGameObject.h>
#include <Engine/CAnimator2D.h>
#include <Engine/CMovement.h>

#include <Engine/CCollisionMgr.h>
#include <Engine/CKeyMgr.h>
#include <Scripts/CHaikuScript.h>

CHaikuStartState::CHaikuStartState()
	:CState(HAIKUSTARTSTATE)
	, bStart(false)
{
}

CHaikuStartState::~CHaikuStartState()
{
}


void CHaikuStartState::Enter()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetCurStateName(L"Start");

	GetOwnerObj()->Animator2D()->Play(L"haiku_null");
}

void CHaikuStartState::finaltick()
{
	if((KEY_TAP(KEY::Q)))
	{
		GetOwnerObj()->Animator2D()->Play(L"haiku_fall");
		GetOwnerObj()->Movement()->SetGround(false);
		GetOwnerObj()->Movement()->SetGravityForce(Vec3(0, -1, 0));
		bStart = true;
	}

	if ( true== bStart && true == GetOwnerObj()->Movement()->IsGround())
	{
		ChangeState(L"Idle");
	}
}

void CHaikuStartState::Exit()
{
	GetOwnerObj()->Movement()->SetGravityForce(Vec3(0, -980, 0));
	bStart = false;

	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetCurStateName(L"Start");
}
