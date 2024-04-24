#include "pch.h"
#include "CMainCameraScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include "CCamEventScript.h"

CMainCameraScript::CMainCameraScript()
	: CScript(MAINCAMERASCRIPT)
	, camType(MAIN_CAMERA_TYPE::TRACE)
	, TargetPosZ(-130)
{
}

CMainCameraScript::~CMainCameraScript()
{
}


void CMainCameraScript::begin()
{
	CLevel* curLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	Target = curLevel->FindObjectByName(L"Haiku"); // ggboss0bg
	TargetPosX = Target->Transform()->GetRelativePos().x;
	TargetPosY = Target->Transform()->GetRelativePos().y;
	GetOwner()->Transform()->SetRelativePos(Vec3(TargetPosX, TargetPosY, TargetPosZ));
}

void CMainCameraScript::tick()
{
	CCamEventScript* pScpt = GetOwner()->GetScript<CCamEventScript>();

	switch (camType)
	{
	case MAIN_CAMERA_TYPE::TRACE:
	{

		if (pScpt != nullptr)
		{
			if (CAM_EFFECT::SHAKE == pScpt->GetCurCamEffect()) // ī�޶� ����ŷ ������ �Ϸ���
				return;
		}

		if (nullptr != Target)
		{
			TargetPosX = Target->Transform()->GetRelativePos().x;
			TargetPosY = Target->Transform()->GetRelativePos().y;
			GetOwner()->Transform()->SetRelativePos(Vec3(TargetPosX, TargetPosY, TargetPosZ));
		}
	}
	break;

	case MAIN_CAMERA_TYPE::FIXED:
	{
		if (nullptr != Target)
		{ // Ÿ��(������)�� ��ġ ������ ��� �޾ƿðž� 
			TargetPosX = Target->Transform()->GetRelativePos().x;
			TargetPosY = Target->Transform()->GetRelativePos().y;
		}

		if (pScpt != nullptr)
		{
			if (CAM_EFFECT::SHAKE == pScpt->GetCurCamEffect())
				return;
		}

		GetOwner()->Transform()->SetRelativePos(FixedPos);
	}
	break;

	case MAIN_CAMERA_TYPE::NONE:
	{

	}
	break;
	}
}

void CMainCameraScript::SaveToFile(FILE* _File)
{
}

void CMainCameraScript::LoadFromFile(FILE* _File)
{
}
