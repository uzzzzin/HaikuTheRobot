#include "pch.h"
#include "CCollider2D.h"

#include "CTransform.h"
#include "CScript.h"

CCollider2D::CCollider2D()
	: CComponent(COMPONENT_TYPE::COLLIDER2D)
	, m_CollisionCount(0)
	, m_bAbsolute(false)
	, m_Type(COLLIDER2D_TYPE::RECT)
{
}

CCollider2D::CCollider2D(const CCollider2D& _OriginCollider2D)
	: CComponent(_OriginCollider2D)
	, m_vOffsetPos(_OriginCollider2D.m_vOffsetPos)
	, m_vOffsetScale(_OriginCollider2D.m_vOffsetScale)
	, m_CollisionCount(0)
	, m_bAbsolute(_OriginCollider2D.m_bAbsolute)
	, m_Type(_OriginCollider2D.m_Type)
{
}

CCollider2D::~CCollider2D()
{
}

void CCollider2D::finaltick()
{
	// �浹ü�� ���� ��� ���
	m_matColWorld = XMMatrixScaling(m_vOffsetScale.x, m_vOffsetScale.y, m_vOffsetScale.z);
	m_matColWorld *= XMMatrixTranslation(m_vOffsetPos.x, m_vOffsetPos.y, m_vOffsetPos.z);

	// �浹ü�� �����ų GameObject �� �������
	const Matrix& matObjWorld = Transform()->GetWorldMat();

	// GameObject �� Scale �� ������ ���� �������� ���
	if (m_bAbsolute)
	{
		Vec3 vWorldScale = Transform()->GetWorldScale();
		Matrix matScaleInv = XMMatrixScaling(vWorldScale.x, vWorldScale.y, vWorldScale.z);
		matScaleInv = XMMatrixInverse(nullptr, matScaleInv);

		// Object �� Scale �� ������� ���̿� ��ġ�ؼ� ��ȿȭ ��Ŵ
		m_matColWorld = m_matColWorld * matScaleInv *  matObjWorld;
	}
	else
	{
		m_matColWorld *= matObjWorld;
	}	

	return;
	// �浹���̸� Red, �浹�ϰ� ���� ������ Green
	if (0 == m_CollisionCount)
	{
		GamePlayStatic::DrawDebugRect(m_matColWorld, Vec3(0.f, 1.f, 0.f), false);
	}
	else
	{
		GamePlayStatic::DrawDebugRect(m_matColWorld, Vec3(1.f, 0.f, 0.f), false);
	}
}

void CCollider2D::BeginOverlap(CCollider2D* _OtherCollider)
{
	++m_CollisionCount;

	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScript.size(); ++i)
	{
		vecScript[i]->BeginOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
	}
}

void CCollider2D::Overlap(CCollider2D* _OtherCollider)
{
	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScript.size(); ++i)
	{
		vecScript[i]->Overlap(this, _OtherCollider->GetOwner(), _OtherCollider);
	}
}

void CCollider2D::EndOverlap(CCollider2D* _OtherCollider)
{
	--m_CollisionCount;

	const vector<CScript*>& vecScript = GetOwner()->GetScripts();
	for (size_t i = 0; i < vecScript.size(); ++i)
	{
		vecScript[i]->EndOverlap(this, _OtherCollider->GetOwner(), _OtherCollider);
	}
}

void CCollider2D::SaveToFile(FILE* _File)
{
	fwrite(&m_vOffsetPos, sizeof(Vec3), 1, _File);
	fwrite(&m_vOffsetScale, sizeof(Vec3), 1, _File);
	fwrite(&m_bAbsolute, sizeof(bool), 1, _File);
	fwrite(&m_Type, sizeof(UINT), 1, _File);	
}

void CCollider2D::LoadFromFile(FILE* _File)
{
	fread(&m_vOffsetPos, sizeof(Vec3), 1, _File);
	fread(&m_vOffsetScale, sizeof(Vec3), 1, _File);
	fread(&m_bAbsolute, sizeof(bool), 1, _File);
	fread(&m_Type, sizeof(UINT), 1, _File);
}
