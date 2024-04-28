#include "pch.h"
#include "CSGMChangeDirState.h"

#include <Scripts/CSwingingGarbageMagnetScript.h>

CSGMChangeDirState::CSGMChangeDirState()
	: CState(STATE_TYPE::SGMCHANGEDIRSTATE)
	, accTime(0)
	, duration(0.4f)
{
}

CSGMChangeDirState::~CSGMChangeDirState()
{
}

void CSGMChangeDirState::Enter()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetCurStateName(L"ChangeDir");

	GetOwnerObj()->Animator2D()->Play(L"SGM_ChangeDir", false); // 4 ÇÁ·¹ÀÓ

	int dir = pScpt->GetCurDir();

	if (0 == dir)
		pScpt->SetCurDir(1);
	if (1 == dir)
		pScpt->SetCurDir(0);
}

void CSGMChangeDirState::finaltick()
{
	accTime += DT;

	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	BOSS_SWINGING_GARBAGE_MAGNET stage = pScpt->GetCurStage();

	if (accTime > duration)
	{
		switch (stage)
		{
		case BOSS_SWINGING_GARBAGE_MAGNET::INTRO:
			break;

		case BOSS_SWINGING_GARBAGE_MAGNET::STAGE1:
			ChangeState(L"IdleOnMiddle");
			break;

		case BOSS_SWINGING_GARBAGE_MAGNET::STAGE2:
			break;

		case BOSS_SWINGING_GARBAGE_MAGNET::CLEAR:
			break;
		}
	}
}

void CSGMChangeDirState::Exit()
{
	CSwingingGarbageMagnetScript* pScpt = GetOwnerObj()->GetScript<CSwingingGarbageMagnetScript>();
	pScpt->SetPrevStateName(L"ChangeDir");
}
