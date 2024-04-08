#include "pch.h"
#include "CHaikuScript.h"

#include <Engine/CGameObject.h>
#include <Engine/CMovement.h>

#include <Engine/CCollisionMgr.h>
#include "CPlatformScript.h"


CHaikuScript::CHaikuScript()
	: CScript(HAIKUSCRIPT)
	, curDir(0)
	, prevDir(0)
	, curStateName(L"Start")
	, prevStateName(L"Start")
	, prevColDir(COLLISION_DIR::NONE)
	, collisionCnt(0)
	, bGeneralAttackSeed(false)
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

	GetRenderComponent()->GetDynamicMaterial();

}

void CHaikuScript::tick()
{
	if(KEY_TAP(KEY::LEFT))
	{
		curDir = 1; // 현재 왼쪽
		StateMachine()->GetDynamicFSM()->ChangeState(L"Walk");
	}

	if(KEY_TAP(KEY::RIGHT))
	{
		curDir = 0; // 현재 오른쪽
		StateMachine()->GetDynamicFSM()->ChangeState(L"Walk");
	}
	
	GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, curDir);

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