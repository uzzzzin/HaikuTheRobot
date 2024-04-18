#include "pch.h"
#include "CSwingingGarbageMagnetScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

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
}

void CSwingingGarbageMagnetScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CSwingingGarbageMagnetScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CSwingingGarbageMagnetScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
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
