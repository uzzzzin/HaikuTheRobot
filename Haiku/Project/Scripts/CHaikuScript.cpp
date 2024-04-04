#include "pch.h"
#include "CHaikuScript.h"

#include <Engine/CGameObject.h>
#include <Engine/CMovement.h>

#include <Engine/CCollisionMgr.h>
#include "CPlatformScript.h"


CHaikuScript::CHaikuScript()
	: CScript(HAIKUSCRIPT)
	, curDir(false)
	, prevDir(false)
	, curStateName(L"Start")
	, prevStateName(L"Start")
	, prevColDir(COLLISION_DIR::NONE)
	, collisionCnt(0)
{
}

CHaikuScript::~CHaikuScript()
{
}

void CHaikuScript::begin()
{

	if (nullptr != StateMachine()->GetFSM())
	{
		StateMachine()->GetDynamicFSM()->ChangeState(L"Start");
	}

	// 충돌 설정
	CCollisionMgr::GetInst()->LayerCheck(4, 2); // 하이쿠 & 플랫폼
}

void CHaikuScript::tick()
{
	if (KEY_TAP(KEY::LEFT))
	{
		curDir = true; // 현재 왼쪽
		Animator2D()->Play(L"haiku_walk");
	}

	if ((KEY_TAP(KEY::RIGHT)))
	{
		curDir = false; // 현재 오른쪽
		Animator2D()->Play(L"haiku_walk");
	}

	wstring c = GetCurStateName();
	if (KEY_PRESSED(KEY::LEFT) && GetCurStateName() == L"Idle" && Movement()->IsGround()) //점프가 아닐 때만
	{
		Vec3 vVelo = Movement()->GetVelocity();
		Movement()->SetVelocity(Vec3(-400.f, 0.f, 0.f));
	}

	if ( KEY_PRESSED(KEY::RIGHT) && GetCurStateName() == L"Idle" && Movement()->IsGround())
	{
		Vec3 vVelo = Movement()->GetVelocity();
		Movement()->SetVelocity(Vec3(400.f, 0.f, 0.f));
	}

	if (KEY_RELEASED(KEY::LEFT))
	{
		Movement()->SetVelocity(Vec3());
		if (!(KEY_PRESSED(KEY::RIGHT)) && !(KEY_PRESSED(KEY::SPACE)))
		{
			Animator2D()->Play(L"haiku_idle");
		}

	}

	if ((KEY_RELEASED(KEY::RIGHT)) && !(KEY_PRESSED(KEY::SPACE)))
	{
		Movement()->SetVelocity(Vec3());
		if (!(KEY_PRESSED(KEY::LEFT)))
		{
			Animator2D()->Play(L"haiku_idle");
		}
	}

	if (prevDir != curDir) // 현재와 과거의 방향이 달랐다면
	{
		float x = Transform()->GetRelativeScale().x * -1;
		Vec3 vPos = Vec3(Transform()->GetRelativeScale().x * -1, Transform()->GetRelativeScale().y, Transform()->GetRelativeScale().z);
		Transform()->SetRelativeScale(vPos);
	}

	prevDir = curDir;
}

// =====================================================================================================================


void CHaikuScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	++collisionCnt;
	if (2 == _OtherObj->GetLayerIdx())
	{
		colPlatformName = _OtherObj->GetName();

	}
}

void CHaikuScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{

}

void CHaikuScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	
	--collisionCnt;
	colPlatformName = L"";
}

void CHaikuScript::SaveToFile(FILE* _File)
{
}

void CHaikuScript::LoadFromFile(FILE* _File)
{
}

void CHaikuScript::AddOverlapGround(CGameObject* _pObejct)
{
	m_Ground.push_back(_pObejct);

	m_OverlapGround = m_Ground.size();
}

void CHaikuScript::SubOverlapGround(CGameObject* _pObejct)
{
	vector<CGameObject*>::iterator iter = m_Ground.begin();

	for (; iter != m_Ground.end();)
	{
		if (*iter == _pObejct)
		{
			iter = m_Ground.erase(iter);
		}
		else
		{
			++iter;
		}
	}

	m_OverlapGround = m_Ground.size();
}