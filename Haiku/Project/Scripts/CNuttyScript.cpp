#include "pch.h"
#include "CNuttyScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

CNuttyScript::CNuttyScript()
	:CScript(NUTTYSCRIPT)
	, m_MoveRange(180.f)
	, m_DetectRange(100.f)
	, m_Speed(30.f)
	, m_CurDir(1)
{
}

CNuttyScript::~CNuttyScript()
{
}

void CNuttyScript::begin()
{
	m_OriginPos = Transform()->GetRelativePos();

	if (nullptr != StateMachine()->GetFSM())
	{
		StateMachine()->GetDynamicFSM()->ChangeState(L"Idle");
	}

	GetRenderComponent()->GetDynamicMaterial();

	m_Target = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Haiku");
}

void CNuttyScript::tick()
{
	GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, m_CurDir);
}


void CNuttyScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	//
}

void CNuttyScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CNuttyScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}


void CNuttyScript::SaveToFile(FILE* _File)
{
}

void CNuttyScript::LoadFromFile(FILE* _File)
{
}