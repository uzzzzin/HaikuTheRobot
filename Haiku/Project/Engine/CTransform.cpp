#include "pch.h"
#include "CTransform.h"

#include "CDevice.h"
#include "CConstBuffer.h"



CTransform::CTransform()
	: CComponent(COMPONENT_TYPE::TRANSFORM)
	, m_vRelativeScale(Vec3(1.f, 1.f, 1.f))
	, m_bAbsolute(true)
{
}

CTransform::~CTransform()
{
}

void CTransform::finaltick()
{	
	m_matWorld = XMMatrixIdentity();

	Matrix matScale = XMMatrixScaling(m_vRelativeScale.x, m_vRelativeScale.y, m_vRelativeScale.z);
	
	Matrix matRotX = XMMatrixRotationX(m_vRealtiveRotation.x);
	Matrix matRotY = XMMatrixRotationY(m_vRealtiveRotation.y);
	Matrix matRotZ = XMMatrixRotationZ(m_vRealtiveRotation.z);

	Matrix matTranslation = XMMatrixTranslation(m_vRelativePos.x, m_vRelativePos.y, m_vRelativePos.z);

	m_matWorld = matScale * matRotX * matRotY * matRotZ * matTranslation;

	// ��ü�� ���Ⱚ�� �ٽ� ����Ѵ�.
	static const Vec3 arrAxis[3] =
	{
		Vec3(1.f, 0.f, 0.f),
		Vec3(0.f, 1.f, 0.f),
		Vec3(0.f, 0.f, 1.f)
	};

	// Vec3 �� Vec4 Ÿ������ Ȯ���ؼ� ����� ������Ѿ� ��
	// XMVector3TransformCoord	- w �� 1�� Ȯ��
	// XMVector3TransformNormal - w �� 0���� Ȯ��
	// mul(float4(_in.vPos, 1 or 0), g_matWorld); 
	// ���� ���� ��������� �̵��� �������� ���� ����
	for (int i = 0; i < 3; ++i)
	{
		// m_matWorld ��Ŀ� ũ�������� ���� �� �ֱ� ������ �ٽ� ���̸� 1�� ����ȭ ��Ų��.
		m_arrLocalDir[i] = XMVector3TransformNormal(arrAxis[i], m_matWorld);
		m_arrWorldDir[i] = m_arrLocalDir[i].Normalize();
	}

	// �θ� ������Ʈ�� �ִٸ�
	if (GetOwner()->GetParent())
	{
		const Matrix& matParentWorld = GetOwner()->GetParent()->Transform()->GetWorldMat();

		if (m_bAbsolute)
		{
			Vec3 vParentScale = GetOwner()->GetParent()->Transform()->GetRelativeScale();

			Matrix matParentScaleInv = XMMatrixScaling(1.f / vParentScale.x, 1.f / vParentScale.y, 1.f / vParentScale.z);

			m_matWorld = m_matWorld * matParentScaleInv* matParentWorld;
		}
		else
		{
			m_matWorld *= matParentWorld;
		}		

		for (int i = 0; i < 3; ++i)
		{
			// m_matWorld ��Ŀ� ũ�������� ���� �� �ֱ� ������ �ٽ� ���̸� 1�� ����ȭ ��Ų��.
			m_arrWorldDir[i] = XMVector3TransformNormal(arrAxis[i], m_matWorld);
			m_arrWorldDir[i].Normalize();
		}
	}
}

void CTransform::UpdateData()
{
	g_Transform.matWorld = m_matWorld;
	g_Transform.matWV = g_Transform.matWorld * g_Transform.matView;
	g_Transform.matWVP = g_Transform.matWV * g_Transform.matProj;
		
	// ��ġ������ Transform ������ۿ� ������, B0 �������Ϳ� ���ε� �ص�
	CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::TRANSFORM);
	pCB->SetData(&g_Transform);
	pCB->UpdateData();
}

Vec3 CTransform::GetWorldScale()
{
	CGameObject* pParent = GetOwner()->GetParent();
	Vec3 vWorldScale = m_vRelativeScale;

	while (pParent)
	{
		vWorldScale *= pParent->Transform()->GetRelativeScale();
		pParent = pParent->GetParent();
	}

	return vWorldScale;
}

void CTransform::SaveToFile(FILE* _File)
{
	fwrite(&m_vRelativePos, sizeof(Vec3), 1, _File);
	fwrite(&m_vRelativeScale, sizeof(Vec3), 1, _File);
	fwrite(&m_vRealtiveRotation, sizeof(Vec3), 1, _File);
	fwrite(&m_bAbsolute, sizeof(bool), 1, _File);	
}

void CTransform::LoadFromFile(FILE* _File)
{
	fread(&m_vRelativePos, sizeof(Vec3), 1, _File);
	fread(&m_vRelativeScale, sizeof(Vec3), 1, _File);
	fread(&m_vRealtiveRotation, sizeof(Vec3), 1, _File);
	fread(&m_bAbsolute, sizeof(bool), 1, _File);
}