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
	// Ãæµ¹ ¼³Á¤
	CCollisionMgr::GetInst()->LayerCheck(4, 2); // ÇÏÀÌÄí & ÇÃ·§Æû
	CCollisionMgr::GetInst()->LayerCheck(4, 5); // ÇÏÀÌÄí & ¸ó½ºÅÍ
	CCollisionMgr::GetInst()->LayerCheck(8, 5); // ÇÏÀÌÄí °Ë & ¸ó½ºÅÍ
	CCollisionMgr::GetInst()->LayerCheck(5, 2); // ¸ó½ºÅÍ & ÇÃ·§Æû

	CCollisionMgr::GetInst()->LayerCheck(4, 10); // ÇÏÀÌÄí & Ã¼ÀÎÁö·ë


	CCollisionMgr::GetInst()->LayerCheck(11, 2); // TrashBall & ÇÃ·§Æû
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
	// ÇöÀç ÄÝ¶óÀÌ´õ µð¹ö±× »óÅÂ¶û, 1Æ½ ÀüÀÇ ÄÝ¶óÀÌ´õ µð¹ö±× »óÅÂ°¡ ´Ù¸£´Ù¸é -> ²°ÄÑ ÇØÁà¾ß ÇÔ
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