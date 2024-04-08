#include "pch.h"
#include "CCtrlScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include <Engine/CCollisionMgr.h>

CCtrlScript::CCtrlScript()
	:CScript(CTRLSCRIPT)
	, curCtrlColliderDebug(true)
	, prevCtrlColliderDebug(true)
{
	AddScriptParam(SCRIPT_PARAM::BOOL, "Collider Debug", &curCtrlColliderDebug);
	// 충돌 설정
	CCollisionMgr::GetInst()->LayerCheck(4, 2); // 하이쿠 & 플랫폼
	CCollisionMgr::GetInst()->LayerCheck(4, 5); // 하이쿠 & 몬스터
	CCollisionMgr::GetInst()->LayerCheck(8, 5); // 하이쿠 검 & 몬스터
	CCollisionMgr::GetInst()->LayerCheck(5, 2); // 몬스터 & 플랫폼
}

CCtrlScript::~CCtrlScript()
{
}


void CCtrlScript::begin()
{
}

void CCtrlScript::tick()
{
	if (KEY_TAP(KEY::LCTRL))
	{
		if (curCtrlColliderDebug)
			curCtrlColliderDebug = false;
		else
			curCtrlColliderDebug = true;
	}
	// 현재 콜라이더 디버그 상태랑, 1틱 전의 콜라이더 디버그 상태가 다르다면 -> 껐켜 해줘야 함
	if (curCtrlColliderDebug != prevCtrlColliderDebug)
	{
		CLevel* curLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		curLevel->GetAllObjects(AllObjects);
		
		for (int i = 0; i < AllObjects.size(); ++i)
		{
			if (AllObjects[i]->Collider2D())
			{
				if (curCtrlColliderDebug)
					AllObjects[i]->Collider2D()->SetRenderDebugRect(true);
				else
					AllObjects[i]->Collider2D()->SetRenderDebugRect(false);
			}
		}
	}

	prevCtrlColliderDebug = curCtrlColliderDebug;
	AllObjects.clear();
}

void CCtrlScript::SaveToFile(FILE* _File)
{
}

void CCtrlScript::LoadFromFile(FILE* _File)
{
}