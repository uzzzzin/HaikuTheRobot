#include "pch.h"
#include "CTiredTireScript.h"

CTiredTireScript::CTiredTireScript()
    : CScript(TIREDTIRESCRIPT)
    , life(2)
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

    Collider2D()->SetLastColDir(LAST_COL_DIR::UP); // 무조건 첫 충돌은 플랫폼이라 UP으로 고정
}

void CTiredTireScript::tick()
{
    //if (Movement()->GetVelocity().x > 250)
    //{
    //    Movement()->SetVelocity(Vec3(250, Movement()->GetVelocity().y, Movement()->GetVelocity().z));
    //}
    //if (Movement()->GetVelocity().y > 250)
    //{
    //    Movement()->SetVelocity(Vec3(Movement()->GetVelocity().x, 250, Movement()->GetVelocity().z));
    //}
}

void CTiredTireScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
    if (2 == _OtherObj->GetLayerIdx()) // 충돌한 것이 플랫폼 일 때
    {
        if (LAST_COL_DIR::UP == Collider2D()->GetLastColDir() || LAST_COL_DIR::DOWN == Collider2D()->GetLastColDir())
        {
            Vec3 v3 = Vec3(Movement()->GetVelocity().x, Movement()->GetVelocity().y * -1, Movement()->GetVelocity().z);
            Movement()->SetVelocity(v3);
        }
        if (LAST_COL_DIR::LEFT == Collider2D()->GetLastColDir() || LAST_COL_DIR::RIGHT == Collider2D()->GetLastColDir())
        {
            Vec3 v3 = Vec3(Movement()->GetVelocity().x * -1, Movement()->GetVelocity().y, Movement()->GetVelocity().z);
            Movement()->SetVelocity(v3);
        }

        if (Movement()->GetVelocity().y >= -200 && Movement()->GetVelocity().y <= 0)
        {
            Movement()->SetVelocity(Vec3(0, -250, 0));
        }

        if (Movement()->GetVelocity().y <= 200 && Movement()->GetVelocity().y >= 0)
        {
            Movement()->SetVelocity(Vec3(0, -250, 0));
        }
    }

    if (8 == _OtherObj->GetLayerIdx()) // 충돌한 것이 하이쿠의 검일 때
    {
        Vec2 v2 = Vec2(_OtherCollider->GetFinalPos().x - _Collider->GetFinalPos().x, _OtherCollider->GetFinalPos().y - _Collider->GetFinalPos().y);
        Vec3 v3 = Vec3(v2.x, v2.y, 0);
        float speed = v2.Length();
        


        if (_OtherObj->GetParent()->Collider2D()->GetFinalPos().x > _Collider->GetFinalPos().x) //하이쿠가 오른쪽에서 치면
        {
            v3 = Vec3(v3.x * -1, v3.y, 0);
            Movement()->AddForce(v3 * speed * 4);
        }
        else // 하이쿠가 왼쪽에서 치면
        {
            Movement()->AddForce(v3*speed*4);
        }

        --life;
    }
}

void CTiredTireScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
    if (2 == _OtherObj->GetLayerIdx()) // 충돌한 것이 플랫폼 일 때
    {
        if (LAST_COL_DIR::LEFT == Collider2D()->GetLastColDir())
        {
            Vec3 v3 = Vec3(Movement()->GetVelocity().x, Movement()->GetVelocity().y, Movement()->GetVelocity().z);
            Movement()->SetVelocity(v3);
        }

        if (LAST_COL_DIR::RIGHT == Collider2D()->GetLastColDir())
        {
            Vec3 v3 = Vec3(Movement()->GetVelocity().x, Movement()->GetVelocity().y, Movement()->GetVelocity().z);
            Movement()->SetVelocity(v3);
        }
    }
}

void CTiredTireScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
    if (2 == _OtherObj->GetLayerIdx())
    {
        if (Movement()->GetVelocity().y >= -200 && Movement()->GetVelocity().y <= 0)
        {
            Movement()->SetVelocity(Vec3(0, -250, 0));
        }

        if (Movement()->GetVelocity().y <= 200 && Movement()->GetVelocity().y >= 0)
        {
            Movement()->SetVelocity(Vec3(0, -250, 0));
        }
    }

    if (life <= 0)
    {
        StateMachine()->GetDynamicFSM()->ChangeState(L"Die");
    }
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