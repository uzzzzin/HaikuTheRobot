#include "pch.h"
#include "CSwingingGarbageMagnetScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include "CMainCameraScript.h"
#include "CCamEventScript.h"
#include "CBoss1RoomScript.h"


CSwingingGarbageMagnetScript::CSwingingGarbageMagnetScript()
	:CScript(SWINGINGGARBAGEMAGNETSCRIPT)
	, curStateName(L"None")
	, prevStateName(L"None")
	, curStage(BOSS_SWINGING_GARBAGE_MAGNET::INTRO)
	, curDir(1)
	, prevDir(0)
{
}

CSwingingGarbageMagnetScript::~CSwingingGarbageMagnetScript()
{
}

void CSwingingGarbageMagnetScript::begin()
{
	GetRenderComponent()->GetDynamicMaterial();

	CGameObject* SGMBar = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"SwingingGarbageMagnetBar");
	SGMBar->Animator2D()->Play(L"SGM_Bar", false);
	SGMBar->Transform()->SetRelativeScale(Vec3(400,160,1));

	curStage = BOSS_SWINGING_GARBAGE_MAGNET::INTRO;

	StateMachine()->GetDynamicFSM()->ChangeState(L"Null");

	CGameObject* mainCam = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
	CMainCameraScript* mainCamScpt = mainCam->GetScript<CMainCameraScript>();
}

void CSwingingGarbageMagnetScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (8 == _OtherObj->GetLayerIdx() && L"Null" == curStateName) // 맨 처음 보스 타격 -> 카메라 고정
	{
		CGameObject* mainCam = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
		
		mainCam->GetScript<CCamEventScript>()->FadeIn(0.14f);
		mainCam->GetScript<CCamEventScript>()->Shake(0.36f, 6);
	}
}

void CSwingingGarbageMagnetScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CSwingingGarbageMagnetScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if( 8 == _OtherObj->GetLayerIdx() && L"Null" == curStateName)
	{

		CGameObject* mainCam = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");

		CMainCameraScript* mainCamScpt = mainCam->GetScript<CMainCameraScript>();

		if (GetOwner() != mainCamScpt->GetTraceTarget())
		{
			//mainCamScpt->SetTraceTarget(GetOwner());
			
			CGameObject* boss1room = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"ggbossc2");
			CBoss1RoomScript* scpt = boss1room->GetScript<CBoss1RoomScript>();
			scpt->SetCameraLock(true);

			mainCamScpt->SetFixedPos(Vec3(GetOwner()->Transform()->GetRelativePos().x, -5,-120));
			StateMachine()->GetDynamicFSM()->ChangeState(L"Start");
		}
	}
}

void CSwingingGarbageMagnetScript::tick()
{
	GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, curDir);
	prevDir = curDir;
}

void CSwingingGarbageMagnetScript::SaveToFile(FILE* _File)
{
}

void CSwingingGarbageMagnetScript::LoadFromFile(FILE* _File)
{
}
