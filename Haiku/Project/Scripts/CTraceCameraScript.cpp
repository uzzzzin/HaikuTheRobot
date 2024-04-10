#include "pch.h"
#include "CTraceCameraScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CTraceCameraScript::CTraceCameraScript()
	: CScript(SCRIPT_TYPE::TRACECAMERASCRIPT)
	, Target(nullptr)
	, TargetPosX(-480)
	, TargetPosY(-148)
	, TargetPosZ(-130)
{
}

CTraceCameraScript::~CTraceCameraScript()
{
}

void CTraceCameraScript::begin()
{
	CLevel* curLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	Target = curLevel->FindObjectByName(L"Haiku"); // ggboss0bg
	TargetPosX = Target->Transform()->GetRelativePos().x;
	TargetPosY = Target->Transform()->GetRelativePos().y;
	GetOwner()->Transform()->SetRelativePos(Vec3(TargetPosX, TargetPosY, TargetPosZ));
}


void CTraceCameraScript::tick()
{
	if (nullptr != Target)
	{
		TargetPosX = Target->Transform()->GetRelativePos().x;
		TargetPosY = Target->Transform()->GetRelativePos().y;
		GetOwner()->Transform()->SetRelativePos(Vec3(TargetPosX, TargetPosY, TargetPosZ));
	}
}

void CTraceCameraScript::SaveToFile(FILE* _File)
{
}

void CTraceCameraScript::LoadFromFile(FILE* _File)
{
}
