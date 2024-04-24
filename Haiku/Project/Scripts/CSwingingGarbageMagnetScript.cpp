#include "pch.h"
#include "CSwingingGarbageMagnetScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include "CMainCameraScript.h"
#include "CCamEventScript.h"


CSwingingGarbageMagnetScript::CSwingingGarbageMagnetScript()
	:CScript(SWINGINGGARBAGEMAGNETSCRIPT)
	, curStateName(L"None")
	, prevStateName(L"None")
{
}

CSwingingGarbageMagnetScript::~CSwingingGarbageMagnetScript()
{
}

void CSwingingGarbageMagnetScript::begin()
{
	CGameObject* SGMBar = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"SwingingGarbageMagnetBar");
	SGMBar->Animator2D()->Play(L"SGM_Bar", false);
	SGMBar->Transform()->SetRelativeScale(Vec3(400,160,1));

	StateMachine()->GetDynamicFSM()->ChangeState(L"null");

	CGameObject* mainCam = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
	CMainCameraScript* mainCamScpt = mainCam->GetScript<CMainCameraScript>();
}

void CSwingingGarbageMagnetScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CSwingingGarbageMagnetScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CSwingingGarbageMagnetScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if( 8 == _OtherObj->GetLayerIdx())
	{

		CGameObject* mainCam = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
		CMainCameraScript* mainCamScpt = mainCam->GetScript<CMainCameraScript>();

		if (GetOwner() != mainCamScpt->GetTraceTarget())
		{
			mainCamScpt->SetTraceTarget(GetOwner());
			StateMachine()->GetDynamicFSM()->ChangeState(L"start");
		}
	}
}

void CSwingingGarbageMagnetScript::tick()
{
}

void CSwingingGarbageMagnetScript::SaveToFile(FILE* _File)
{
}

void CSwingingGarbageMagnetScript::LoadFromFile(FILE* _File)
{
}
