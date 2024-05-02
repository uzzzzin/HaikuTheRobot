#include "pch.h"
#include "CTrashBallDropState.h"

#include <Engine/CAnimator2D.h>

#include <Scripts/CTrashBallScript.h>

CTrashBallDropState::CTrashBallDropState()
	: CState(STATE_TYPE::TRASHBALLDROPSTATE)
	, platform(-83.f)
	, velocity(0.7f)
	, acceleration(20.f)
{
}

CTrashBallDropState::~CTrashBallDropState()
{
}

void CTrashBallDropState::Enter()
{
	GetOwnerObj()->Animator2D()->Play(L"TrashBall_Drop");

	prevPos = GetOwnerObj()->Transform()->GetRelativePos();

	velocity = 1.1f;

	acceleration = 9.8f;
}

void CTrashBallDropState::finaltick()
{
	CTrashBallScript* pScpt = GetOwnerObj()->GetScript<CTrashBallScript>();
	Vec3 curPos = GetOwnerObj()->Transform()->GetRelativePos();

	if (true == pScpt->GetWillDestroy()) // ÇÃ·§Æû¿¡ ´êÀº°Å´Ï ¼Ò¸êÇÕ½Ã´Ù
	{
		ChangeState(L"Destroy");
	}

	//float ratio = 1 - abs((platform - curPos.y) / (platform - prevPos.y)) + velocity * DT;
	//float vPosY = ratio * (platform - prevPos.y) + prevPos.y;

	// °¡¼Óµµ °í·Á
	float ratio = 1 - abs((platform - curPos.y) / (platform - prevPos.y)) + velocity * DT + 0.5 * acceleration * (DT * DT);
	float vPosY = ratio * (platform - prevPos.y) + prevPos.y;

	GetOwnerObj()->Transform()->SetRelativePos(Vec3(curPos.x, vPosY, curPos.z));

}

void CTrashBallDropState::Exit()
{
}
