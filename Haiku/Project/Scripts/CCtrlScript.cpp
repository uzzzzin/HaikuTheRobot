#include "pch.h"
#include "CCtrlScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CCtrlScript::CCtrlScript()
	:CScript(CTRLSCRIPT)
	, curCtrlColliderDebug(true)
	, prevCtrlColliderDebug(true)
{
	AddScriptParam(SCRIPT_PARAM::BOOL, "Collider Debug", &curCtrlColliderDebug);
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