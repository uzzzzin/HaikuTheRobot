#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"
#include "CGameObject.h"
#include "CCollider2D.h"

CCollisionMgr::CCollisionMgr()
    : m_Matrix{}
{
}

CCollisionMgr::~CCollisionMgr()
{
}

void CCollisionMgr::tick()
{
    for (UINT Row = 0; Row < LAYER_MAX; ++Row)
    {
        for (UINT Col = Row; Col < LAYER_MAX; ++Col)
        {
            if (m_Matrix[Row] & (1 << Col))
            {
                CollisionBtwLayers(Row, Col);
            }
        }
    }
}

void CCollisionMgr::LayerCheck(UINT _LayerLeftIdx, UINT _LayerRightIdx)
{
    UINT Row = _LayerLeftIdx;
    UINT Col = _LayerRightIdx;

    if (Col < Row)
    {
        Row = _LayerRightIdx;
        Col = _LayerLeftIdx;
    }

    UINT CheckBit = (1 << Col);

    if (m_Matrix[Row] & CheckBit)
    {
        m_Matrix[Row] &= ~CheckBit;
    }
    else
    {
        m_Matrix[Row] |= CheckBit;
    }
}

void CCollisionMgr::LayerCheck(const wstring& _LeftLayer, const wstring& _RightLayer)
{
    CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
    CLayer* pLeftLayer = pCurLevel->GetLayer(_LeftLayer);
    CLayer* pRightLayer = pCurLevel->GetLayer(_RightLayer);

    // �̸��� �ش��ϴ� Layer �� �������� ������
    assert(pLeftLayer && pRightLayer);

    LayerCheck(pLeftLayer->GetLayerIdx(), pRightLayer->GetLayerIdx());
}



void CCollisionMgr::CollisionBtwLayers(UINT _Left, UINT _Right)
{
    CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

    CLayer* pLeftLayer = pCurLevel->GetLayer(_Left);
    CLayer* pRightLayer = pCurLevel->GetLayer(_Right);

    const vector<CGameObject*>& vecLeft = pLeftLayer->GetLayerObjects();
    const vector<CGameObject*>& vecRight = pRightLayer->GetLayerObjects();

    // ���� �ٸ� ���̾�� �浹 �˻�
    if (_Left != _Right)
    {
        for (size_t i = 0; i < vecLeft.size(); ++i)
        {
            if (nullptr == vecLeft[i]->Collider2D())
                continue;

            for (size_t j = 0; j < vecRight.size(); ++j)
            {
                if (nullptr == vecRight[j]->Collider2D())
                    continue;

                CollisionBtwCollider2D(vecLeft[i]->Collider2D(), vecRight[j]->Collider2D());
            }
        }
    }

    // ������ ���̾� ������ �浹 �˻�
    else
    {
        for (size_t i = 0; i < vecLeft.size(); ++i)
        {
            if (nullptr == vecLeft[i]->Collider2D())
                continue;

            for (size_t j = i + 1; j < vecRight.size(); ++j)
            {
                if (nullptr == vecRight[j]->Collider2D())
                    continue;

                CollisionBtwCollider2D(vecLeft[i]->Collider2D(), vecRight[j]->Collider2D());
            }
        }
    }
}

void CCollisionMgr::CollisionBtwCollider2D(CCollider2D* _LeftCol, CCollider2D* _RightCol)
{
    COL_ID id;
    id.LeftID = _LeftCol->GetID();
    id.RightID = _RightCol->GetID();

    map<LONGLONG, bool>::iterator iter = m_ColInfo.find(id.ID);
    if (iter == m_ColInfo.end())
    {
        m_ColInfo.insert(make_pair(id.ID, false));
        iter = m_ColInfo.find(id.ID);
    }

    bool IsDead = _LeftCol->GetOwner()->IsDead() || _RightCol->GetOwner()->IsDead();
    bool IsActive = _LeftCol->IsActive() && _RightCol->IsActive();
    bool IsSemiDeactive = _LeftCol->IsSemiDeactive() || _RightCol->IsSemiDeactive();

    // �� �浹ü�� �ϳ��� Ȱ��ȭ ���� �ƴ϶��, �浹�� �˻����� �ʴ´�.
    if (!IsActive)
        return;

    // ���� �����ִ� �����̴�.
    if (IsCollision(_LeftCol, _RightCol))
    {
        if (iter->second)
        {
            // ���� �ϳ��� ���� �����̰ų�, ��Ȱ��ȭ ���� ���¶��
            if (IsDead || IsSemiDeactive)
            {
                _LeftCol->EndOverlap(_RightCol);
                _RightCol->EndOverlap(_LeftCol);
                iter->second = false;
            }
            else
            {
                // Overlap
                _LeftCol->Overlap(_RightCol);
                _RightCol->Overlap(_LeftCol);
            }
        }

        else
        {
            if (!IsDead && !IsSemiDeactive)
            {
                // BeginOverlap
                _LeftCol->BeginOverlap(_RightCol);
                _RightCol->BeginOverlap(_LeftCol);
                iter->second = true;
            }
        }
    }

    // �浹�ϰ� ���� �ʴ�.
    else
    {
        if (iter->second)
        {
            // �������� �浹���̾���.
            // EndOverlap
            _LeftCol->EndOverlap(_RightCol);
            _RightCol->EndOverlap(_LeftCol);
        }

        iter->second = false;
    }
}


bool CCollisionMgr::IsCollision(CCollider2D* _LeftCol, CCollider2D* _RightCol)
{
    // OBB
    // 0 -- 1
    // | \  |
    // 3 -- 2
    static Vec3 vLocal[4] =
    {
       Vec3(-0.5f, 0.5f, 0.f),
       Vec3(0.5f, 0.5f, 0.f),
       Vec3(0.5f, -0.5f, 0.f),
       Vec3(-0.5f, -0.5f, 0.f),
    };

    Vec3 vLeftCol[3] = {};
    Vec3 vRightCol[3] = {};

    for (int i = 0; i < 3; ++i)
    {
        vLeftCol[i] = XMVector3TransformCoord(vLocal[i], _LeftCol->GetWorldMat());
        vRightCol[i] = XMVector3TransformCoord(vLocal[i], _RightCol->GetWorldMat());
    }

    Vec3 vLeftCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _LeftCol->GetWorldMat());
    Vec3 vRightCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), _RightCol->GetWorldMat());
    Vec3 vCenter = vRightCenter - vLeftCenter;

    Vec3 arrProj[4] =
    {
       vLeftCol[1] - vLeftCol[0],
       vLeftCol[2] - vLeftCol[1],
       vRightCol[1] - vRightCol[0],
       vRightCol[2] - vRightCol[1],
    };


    // �� ���� ������ 4���� �����۾��� ����
    for (int i = 0; i < 4; ++i)
    {
        Vec3 vProj = arrProj[i];
        vProj.Normalize();

        float fProjLen = 0.f;
        for (int j = 0; j < 4; ++j)
        {
            fProjLen += fabs(arrProj[j].Dot(vProj));
        }

        // fProjLen : �������� 4���� ���������� ������ ������ ��
        fProjLen *= 0.5f;
        float fCenter = fabs(vCenter.Dot(vProj));

        if (fProjLen < fCenter)
            return false;
    }

    return true;
}
