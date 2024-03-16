#include "pch.h"
#include "CCameraMoveScript.h"

CCameraMoveScript::CCameraMoveScript()
	: m_CamSpeed(500.f)
	, CScript(-1)
{
}

CCameraMoveScript::~CCameraMoveScript()
{
}

void CCameraMoveScript::tick()
{
	if (KEY_TAP(KEY::P))
	{
		if (Camera()->GetProjType() == PROJ_TYPE::ORTHOGRAPHIC)
			Camera()->SetProjType(PROJ_TYPE::PERSPECTIVE);
		else
		{
			Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
			Transform()->SetRelativeRotation(Vec3(0.f, 0.f, 0.f));
		}		
	}


	if (Camera()->GetProjType() == PROJ_TYPE::ORTHOGRAPHIC)
	{
		MoveOrthographic();
	}

	else
	{
		MovePerspective();
	}

	if (KEY_PRESSED(KEY::NUM1))
	{
		if (Camera()->GetProjType() == PROJ_TYPE::ORTHOGRAPHIC)		
			Camera()->SetScale(Camera()->GetScale() + DT_ENGINE * 0.2f);
		else
			Camera()->SetFOV(Camera()->GetFOV() + DT_ENGINE * 2.f);
	}

	if (KEY_PRESSED(KEY::NUM2))
	{
		if (Camera()->GetProjType() == PROJ_TYPE::ORTHOGRAPHIC)
			Camera()->SetScale(Camera()->GetScale() - DT_ENGINE * 0.2f);
		else
			Camera()->SetFOV(Camera()->GetFOV() - DT_ENGINE * 2.f);
	}
}

void CCameraMoveScript::MoveOrthographic()
{
	Vec3 vPos = Transform()->GetRelativePos();

	if (KEY_PRESSED(KEY::W))
	{
		vPos.y += DT_ENGINE * m_CamSpeed;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vPos.y -= DT_ENGINE * m_CamSpeed;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vPos.x -= DT_ENGINE * m_CamSpeed;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos.x += DT_ENGINE * m_CamSpeed;
	}

	Transform()->SetRelativePos(vPos);
}

void CCameraMoveScript::MovePerspective()
{
	Vec3 vPos = Transform()->GetRelativePos();

	Vec3 vFront = Transform()->GetWorldDir(DIR_TYPE::FRONT);
	Vec3 vRight = Transform()->GetWorldDir(DIR_TYPE::RIGHT);

	if (KEY_PRESSED(KEY::W))
	{
		vPos += DT_ENGINE * m_CamSpeed * vFront;
	}

	if (KEY_PRESSED(KEY::S))
	{
		vPos += DT_ENGINE * m_CamSpeed * -vFront;
	}

	if (KEY_PRESSED(KEY::A))
	{
		vPos += DT_ENGINE * m_CamSpeed * -vRight;
	}

	if (KEY_PRESSED(KEY::D))
	{
		vPos += DT_ENGINE * m_CamSpeed * vRight;
	}

	Transform()->SetRelativePos(vPos);

	if (KEY_PRESSED(KEY::RBTN))
	{
		Vec2 vDrag = CKeyMgr::GetInst()->GetMouseDrag();
		Vec3 vRot = Transform()->GetRelativeRotation();
		vRot.y += vDrag.x * DT_ENGINE * XM_PI * 4.f;
		vRot.x += vDrag.y * DT_ENGINE * XM_PI * 4.f;
		Transform()->SetRelativeRotation(vRot);
	}	
}
