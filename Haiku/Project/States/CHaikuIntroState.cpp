#include "pch.h"
#include "CHaikuIntroState.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include <Engine/CAnimator2D.h>
#include <Engine/CMovement.h>
#include <Scripts/CHaikuScript.h>
#include <Scripts/CCamEventScript.h>

CHaikuIntroState::CHaikuIntroState()
	:CState(STATE_TYPE::HAIKUINTROSTATE)
	, accTime(0)
	, duration(6.1f)
	, bShake(false)
	, virusDuration(2.2f)
	, virusAccTime(0.f)
{
}

CHaikuIntroState::~CHaikuIntroState()
{
}

void CHaikuIntroState::Enter()
{
	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetCurStateName(L"Intro");

	accTime = 0;
	virusAccTime = 0;
	
	GetOwnerObj()->Animator2D()->Play(L"haiku_intro", false);

	const vector<CGameObject*>& children = GetFSM()->GetStateMachine()->GetOwner()->GetChild();
	for (int i = 0; i < children.size(); ++i)
	{
		children[i]->Animator2D()->Play(L"sword_null");
		children[i]->Collider2D()->Deactivate();
	}

	CGameObject* MainCam = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
	MainCam->GetScript<CCamEventScript>()->Shake(duration, 2);
}

void CHaikuIntroState::finaltick()
{
	accTime += DT;

	if (accTime < duration)
	{
		if (duration - accTime <= 0.07)
		{
			if (false == bShake)
			{
				CGameObject* MainCam = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
				MainCam->GetScript<CCamEventScript>()->Shake(0.15f, 3);
				bShake = true;
			}
		}
	}
	else
	{
		Vec3 vPos = GetOwnerObj()->Transform()->GetRelativePos();
		vPos = Vec3(vPos.x, 137, vPos.z);
		GetOwnerObj()->Transform()->SetRelativePos(vPos);

		virusAccTime += DT;

		if (virusAccTime < virusDuration)
		{
			//CGameObject* Virus = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"HaikuVirus");
			//Virus->Animator2D()->Play(L"haiku_virus");
		}
		else
		{
			ChangeState(L"Start");
		}
	}
}

void CHaikuIntroState::Exit()
{

	GetOwnerObj()->Movement()->SetGround(true);

	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
	pScpt->SetPrevStateName(L"Intro");
}


//#include "pch.h"
//#include "CHaikuIntroState.h"
//
//#include <Engine/CLevelMgr.h>
//#include <Engine/CLevel.h>
//
//#include <Engine/CAnimator2D.h>
//#include <Engine/CMovement.h>
//#include <Scripts/CHaikuScript.h>
//#include <Scripts/CCamEventScript.h>
//
//CHaikuIntroState::CHaikuIntroState()
//	:CState(STATE_TYPE::HAIKUINTROSTATE)
//	, accTime(0)
//	, duration(6.1f)
//	, bShake(false)
//	, virusDuration(2.2f)
//	, virusAccTime(0.f)
//{
//}
//
//CHaikuIntroState::~CHaikuIntroState()
//{
//}
//
//void CHaikuIntroState::Enter()
//{
//	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
//	pScpt->SetCurStateName(L"Intro");
//
//	accTime = 0;
//	virusAccTime = 0;
//
//	GetOwnerObj()->Animator2D()->Play(L"haiku_intro", false);
//
//	const vector<CGameObject*>& children = GetFSM()->GetStateMachine()->GetOwner()->GetChild();
//	for (int i = 0; i < children.size(); ++i)
//	{
//		children[i]->Animator2D()->Play(L"sword_null");
//		children[i]->Collider2D()->Deactivate();
//	}
//
//	CGameObject* MainCam = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
//	MainCam->GetScript<CCamEventScript>()->Shake(duration, 2);
//}
//
//void CHaikuIntroState::finaltick()
//{
//	accTime += DT;
//
//	if (accTime < duration)
//	{
//		if (duration - accTime <= 0.07)
//		{
//			if (false == bShake)
//			{
//				CGameObject* MainCam = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
//				MainCam->GetScript<CCamEventScript>()->Shake(0.15f, 3);
//				bShake = true;
//			}
//		}
//	}
//	else
//	{
//		Vec3 vPos = GetOwnerObj()->Transform()->GetRelativePos();
//		vPos = Vec3(vPos.x, 137, vPos.z);
//		GetOwnerObj()->Transform()->SetRelativePos(vPos);
//
//		virusAccTime += DT;
//
//		if (virusAccTime < virusDuration)
//		{
//			//CGameObject* Virus = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"HaikuVirus");
//			//Virus->Animator2D()->Play(L"haiku_virus");
//		}
//		else
//		{
//			ChangeState(L"Idle");
//		}
//	}
//}
//
//void CHaikuIntroState::Exit()
//{
//
//	GetOwnerObj()->Movement()->SetGround(true);
//
//	CHaikuScript* pScpt = GetOwnerObj()->GetScript<CHaikuScript>();
//	pScpt->SetPrevStateName(L"Intro");
//}
