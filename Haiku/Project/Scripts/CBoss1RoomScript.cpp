#include "pch.h"
#include "CBoss1RoomScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CBoss1RoomScript::CBoss1RoomScript()
	:CScript(BOSS1ROOMSCRIPT)
	, bIntroDoor(false)
{
}

CBoss1RoomScript::~CBoss1RoomScript()
{
}

void CBoss1RoomScript::begin()
{
	CGameObject* bossDoorR = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"gbossDoorR_SGM");
	CGameObject* bossDoorL = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"gbossDoorL_SGM");
	bossDoorR->Animator2D()->Play(L"boss_Door", false);
	bossDoorL->Animator2D()->Play(L"boss_Door", false);
}

void CBoss1RoomScript::tick()
{

}

void CBoss1RoomScript::SaveToFile(FILE* _File)
{

}

void CBoss1RoomScript::LoadFromFile(FILE* _File)
{

}