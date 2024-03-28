#include "pch.h"
#include "CMovement.h"

#include "CGameObject.h"
#include "CTransform.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"

CMovement::CMovement()
	: CComponent(COMPONENT_TYPE::MOVEMENT)
	, m_vGravityForce(Vec3(0.f, -981.f, 0.f))
	, m_fMass(1.f)
	, m_fInitSpeed(0.f)
	, m_fMaxSpeed_Ground(100.f)
	, m_fMaxSpeed_InAir(1000.f)
	, m_fFrictionScale(0.f)
	, m_bUseGravity(true)
	, m_bGround(false)
{
}

CMovement::CMovement(const CMovement& _Origin)
	: CComponent(_Origin)
	, m_vGravityForce(_Origin.m_vGravityForce)
	, m_fMass(_Origin.m_fMass)
	, m_fInitSpeed(_Origin.m_fInitSpeed)
	, m_fMaxSpeed_Ground(_Origin.m_fMaxSpeed_Ground)
	, m_fMaxSpeed_InAir(_Origin.m_fMaxSpeed_InAir)
	, m_bUseGravity(_Origin.m_bUseGravity)
	, m_bGround(false)
{
}

CMovement::~CMovement()
{
}

void CMovement::begin()
{
}

void CMovement::finaltick()
{
	// ------------------------------
	// 0. ���ӵ� ���
	// ------------------------------
	m_vAccel = m_vForce / m_fMass;

	if (m_bUseGravity && !m_bGround)
	{
		m_vAccel += m_vGravityForce;
	}
	else if (m_bUseGravity && m_bGround)
	{
		m_vAccel.y = 0.f; // @TODO ���ӵ��� �״�� �ΰ�, ���� ���� ���� ����
	}

	// ------------------------------
	// 1. �ӵ� ���
	// ------------------------------
	// case: ���� �ֱ� �����ϴ� ��� �ʱ���� ����
	if (m_vVelocity.Length() < 0.1f && m_vAccel != Vec3())
	{
		Vec3 vAccelDir = m_vAccel;
		vAccelDir.Normalize();
		m_vVelocity = vAccelDir * m_fInitSpeed;
	}
	else
	{
		m_vVelocity += m_vAccel * DT;
	}

	// �ִ� �ӵ� ����
	if (m_bGround && fabs(m_vVelocity.Length() > m_fMaxSpeed_Ground))
	{
		m_vVelocity = m_vVelocity.Normalize() * m_fMaxSpeed_Ground;
	}
	else if (not m_bGround && fabs(m_vVelocity.Length() > m_fMaxSpeed_InAir))
	{
		m_vVelocity = m_vVelocity.Normalize() * m_fMaxSpeed_InAir;
	}

	// ------------------------------
	// ������ ���
	// ------------------------------
	// - ��ü�� ����ǰ� �ִ� ���� ������ �������� ����
	if (m_vForce == Vec3() && m_vVelocity.x != 0.f && m_bGround)
	{
		// ������ ũ��
		float fFriction = -m_vVelocity.x / fabs(m_vVelocity.x);
		fFriction *= m_fFrictionScale;

		// ���� ������ ũ��
		float fFrictionAccel = (fFriction / m_fMass) * DT;
		if (fabs(m_vVelocity.x) < fabs(fFrictionAccel))
		{
			m_vVelocity.x = 0.f;
		}
		else
			m_vVelocity.x += fFrictionAccel;
	}

	// ------------------------------
	// ��ġ ���
	// ------------------------------
	Vec3 vObjPos = GetOwner()->Transform()->GetRelativePos();
	vObjPos += m_vVelocity * DT;
	GetOwner()->Transform()->SetRelativePos(vObjPos);

	// ------------------------------
	// �� ����
	// ------------------------------
	// - �̵��ϰ��� �ϴ� �� ���� ���� ���ϴ� ���
	m_vForce = Vec3();
}

void CMovement::SaveToFile(FILE* _File)
{
	fwrite(&m_vGravityForce, sizeof(Vec3), 1, _File);
	fwrite(&m_fMass, sizeof(float), 1, _File);
	fwrite(&m_fInitSpeed, sizeof(float), 1, _File);
	fwrite(&m_fMaxSpeed_InAir, sizeof(float), 1, _File);
	fwrite(&m_fFrictionScale, sizeof(float), 1, _File);
	fwrite(&m_bUseGravity, sizeof(bool), 1, _File);
	fwrite(&m_bGround, sizeof(bool), 1, _File);
}

void CMovement::LoadFromFile(FILE* _File)
{
	fread(&m_vGravityForce, sizeof(Vec3), 1, _File);
	fread(&m_fMass, sizeof(float), 1, _File);
	fread(&m_fInitSpeed, sizeof(float), 1, _File);
	fread(&m_fMaxSpeed_InAir, sizeof(float), 1, _File);
	fread(&m_fFrictionScale, sizeof(float), 1, _File);
	fread(&m_bUseGravity, sizeof(bool), 1, _File);
	fread(&m_bGround, sizeof(bool), 1, _File);
}