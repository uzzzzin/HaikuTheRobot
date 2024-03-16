#include "pch.h"
#include "CCollisionMgr.h"

#include "CLevelMgr.h"
#include "CLevel.h"
#include "CLayer.h"

#include "CGameObject.h"
#include "CCollider2D.h"

CCollisionMgr::CCollisionMgr()
	: m_matrix{}
{

}

CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::tick()
{
	for (UINT iRow = 0; iRow < LAYER_MAX; ++iRow)
	{
		for (UINT iCol = iRow; iCol < LAYER_MAX; ++iCol)
		{
			if (!(m_matrix[iRow] & (1 << iCol)) )			
				continue;
			
			// iRow ���̾�� iCol ���̾�� ���� �浹�˻縦 �����Ѵ�.
			CollisionBtwLayer(iRow, iCol);
		}
	}
}

void CCollisionMgr::CollisionBtwLayer(UINT _left, UINT _right)
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();

	CLayer* pLeftLayer = pCurLevel->GetLayer(_left);
	CLayer* pRightLayer = pCurLevel->GetLayer(_right);

	const vector<CGameObject*>& vecLeft = pLeftLayer->GetLayerObjects();
	const vector<CGameObject*>& vecRight = pRightLayer->GetLayerObjects();

	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// �浹ü�� ���� ���
		if (nullptr == vecLeft[i]->Collider2D())
			continue;
				
		size_t j = 0;
		if (_left == _right) // Left, Right ���� ���̾��� ���, ���� �˻縦 ���ϱ� ����
		{
			j = i + 1;
		}

		for (; j < vecRight.size(); ++j)
		{
			// �浹ü�� �����ϰ� ���� �ʰų�, �浹�� �����ų �� ����� ������ ������Ʈ�� ���
			if (nullptr == vecRight[j]->Collider2D())// || vecLeft[i] == vecRight[j] )
				continue;

			// �� �浹ü�� ���̵� ����
			CollisionID ID = {};
			ID.LeftID = vecLeft[i]->Collider2D()->GetID();
			ID.RightID = vecRight[j]->Collider2D()->GetID();

			// ���� ������ �浹 Ȯ��
			map<UINT_PTR, bool>::iterator iter = m_mapPrevInfo.find(ID.id);
			if (iter == m_mapPrevInfo.end())
			{
				m_mapPrevInfo.insert(make_pair(ID.id, false));
				iter = m_mapPrevInfo.find(ID.id);
			}


			bool bDead = vecLeft[i]->IsDead() || vecRight[j]->IsDead();

			// ���� �����ִ�.
			if (CollisionBtwCollider(vecLeft[i]->Collider2D(), vecRight[j]->Collider2D()))
			{
				// �������� �����־���.
				if (iter->second)
				{
					if (bDead)
					{
						vecLeft[i]->Collider2D()->EndOverlap(vecRight[j]->Collider2D());
						vecRight[j]->Collider2D()->EndOverlap(vecLeft[i]->Collider2D());
					}
					else
					{
						vecLeft[i]->Collider2D()->Overlap(vecRight[j]->Collider2D());
						vecRight[j]->Collider2D()->Overlap(vecLeft[i]->Collider2D());
					}					
				}

				// ������ �浹�� ���� ����.
				else
				{
					// ���� �ϳ��� Dead ���¸�, �浹�� ������ ������ �Ѵ�.
					if (!bDead)
					{
						vecLeft[i]->Collider2D()->BeginOverlap(vecRight[j]->Collider2D());
						vecRight[j]->Collider2D()->BeginOverlap(vecLeft[i]->Collider2D());
						iter->second = true;
					}					
				}
			}

			// ���� ������ �ִ�.
			else
			{
				// �������� �����־���.
				if (iter->second)
				{					
					vecLeft[i]->Collider2D()->EndOverlap(vecRight[j]->Collider2D());
					vecRight[j]->Collider2D()->EndOverlap(vecLeft[i]->Collider2D());
					iter->second = false;
				}				
			}			
		}
	}
}

bool CCollisionMgr::CollisionBtwCollider(CCollider2D* _pLeft, CCollider2D* _pRight)
{
	const Matrix& matLeft = _pLeft->GetColliderWorldMat();
	const Matrix& matRight = _pRight->GetColliderWorldMat();

	// Rect Local
	// 0 -- 1
	// |    |
	// 3 -- 2
	static Vec3 arrRect[4] = { Vec3(-0.5f, 0.5f, 0.f)
							  , Vec3(0.5f, 0.5f, 0.f)
							  , Vec3(0.5f, -0.5f, 0.f)
							  , Vec3(-0.5f, -0.5f, 0.f) };

	Vec3 arrProj[4] = {};
	
	arrProj[0] = XMVector3TransformCoord(arrRect[1], matLeft) - XMVector3TransformCoord(arrRect[0], matLeft);
	arrProj[1] = XMVector3TransformCoord(arrRect[3], matLeft) - XMVector3TransformCoord(arrRect[0], matLeft);

	arrProj[2] = XMVector3TransformCoord(arrRect[1], matRight) - XMVector3TransformCoord(arrRect[0], matRight);
	arrProj[3] = XMVector3TransformCoord(arrRect[3], matRight) - XMVector3TransformCoord(arrRect[0], matRight);

	Vec3 vCenter = XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), matRight) - XMVector3TransformCoord(Vec3(0.f, 0.f, 0.f), matLeft);
	
	// i ��° ���������� 4���� ǥ�麤�͸� ������Ų��.
	for (int i = 0; i < 4; ++i)
	{		
		// i ��° ǥ����͸� ���������� ��´�
		Vec3 vProj = arrProj[i];

		// �������ͷ� ���� ������ ��� ������ ���̸� ���� �� �ְ� �Ѵ�.
		vProj.Normalize(); 

		// ������ ���̸� ������ų ����
		float ProjAcc = 0.f;

		// �ݺ��� ���鼭 4���� ǥ�麤�͸� ������ ���������� �������Ѽ� ���̸� �����޴´�.
		for (int j = 0; j < 4; ++j)
		{
			ProjAcc += abs(vProj.Dot(arrProj[j]));
		}

		// ������ ������ ���ݾ� ��ģ ���̰� �ʿ��ϱ� ������ ��ü ��ģ���̸� 2 �� ������
		ProjAcc /= 2.f;

		// �� �浹ü�� �߽��� ���� ���͵� ������Ų��.
		float fCenterDist = abs(vProj.Dot(vCenter));

		// �߽��� ���� ���͸� ������Ų ���̰�, ǥ���� ������Ų ������ ���ݺ��� ũ�ٸ� 
		// ���� �и���ų �� �ִ�.
		if (ProjAcc < fCenterDist)
		{
			return false;
		}
	}

	// 4���� �׽�Ʈ���� �и��� �� ������.
	return true;
}




void CCollisionMgr::LayerCheck(UINT _left, UINT _right)
{
	UINT iRow = (UINT)_left;
	UINT iCol = (UINT)_right;

	if (iRow > iCol)
	{
		UINT iTemp = iCol;
		iCol = iRow;
		iRow = iTemp;
	}

	m_matrix[iRow] |= (1 << iCol);
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