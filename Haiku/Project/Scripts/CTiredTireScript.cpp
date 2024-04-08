#include "pch.h"
#include "CTiredTireScript.h"

CTiredTireScript::CTiredTireScript()
	: CScript(TIREDTIRESCRIPT)
{

}

CTiredTireScript::~CTiredTireScript()
{

}



void CTiredTireScript::begin()
{
	if (nullptr != StateMachine()->GetFSM())
	{
		StateMachine()->GetDynamicFSM()->ChangeState(L"Idle");
	}

	GetRenderComponent()->GetDynamicMaterial();
}

void CTiredTireScript::tick()
{

}

void CTiredTireScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
    if (2 == _OtherObj->GetLayerIdx()) // ÇÃ·§ÆûÀÌ 2¶ó¸é
    {
        Movement()->SetGround(true);
    }
}

void CTiredTireScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{

}

void CTiredTireScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{

}

void CTiredTireScript::SaveToFile(FILE* _File)
{

}

void CTiredTireScript::LoadFromFile(FILE* _File)
{

}

void CTiredTireScript::AddOverlapGround(CGameObject* _pObejct)
{
    m_Ground.push_back(_pObejct);

    m_OverlapGround = m_Ground.size();
}

void CTiredTireScript::SubOverlapGround(CGameObject* _pObejct)
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