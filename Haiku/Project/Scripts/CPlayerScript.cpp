#include "pch.h"
#include "CPlayerScript.h"
#include <Engine/CAssetMgr.h>

#include <Engine/CGameObject.h>
#include "CMissileScript.h"

#include <Engine/CMaterial.h>
#include <Engine/CRenderComponent.h>


CPlayerScript::CPlayerScript()
	: CScript(PLAYERSCRIPT)
	, m_Speed(500.f)
{
	AddScriptParam(SCRIPT_PARAM::FLOAT, "Player Speed", &m_Speed);
}

CPlayerScript::~CPlayerScript()
{

}

void CPlayerScript::begin()
{
	//m_Missile = CAssetMgr::GetInst()->FindAsset<CPrefab>(L"MissilePrefab");
	//m_Missile = CAssetMgr::GetInst()->Load<CPrefab>(L"prefab\\missile.pref", L"prefab\\missile.pref");
	
	
	Animator2D()->Play(L"haiku_walk");
}

void CPlayerScript::tick()
{
	Vec3 vPos = Transform()->GetRelativePos();
	Vec3 vRot = Transform()->GetRelativeRotation();


	if (KEY_PRESSED(KEY::UP))
		vPos.y += DT * m_Speed;	
	if (KEY_TAP(KEY::UP))
		Animator2D()->Play(L"haiku_walk");
	if (KEY_RELEASED(UP))
		Animator2D()->Play(L"haiku_idle");
	
	if (KEY_PRESSED(KEY::DOWN))
		vPos.y -= DT * m_Speed;
	if (KEY_TAP(KEY::DOWN))
		Animator2D()->Play(L"haiku_walk");
	if (KEY_RELEASED(DOWN))
		Animator2D()->Play(L"haiku_idle");

	if (KEY_PRESSED(KEY::LEFT))
		vPos.x -= DT * m_Speed;
	if (KEY_TAP(KEY::LEFT))
		Animator2D()->Play(L"haiku_walk");
	if (KEY_RELEASED(LEFT))
		Animator2D()->Play(L"haiku_idle");

	if (KEY_PRESSED(KEY::RIGHT))
		vPos.x += DT * m_Speed;
	if (KEY_TAP(KEY::RIGHT))
		Animator2D()->Play(L"haiku_walk");
	if (KEY_RELEASED(RIGHT))
		Animator2D()->Play(L"haiku_idle");
	
	Transform()->SetRelativePos(vPos);
	Transform()->SetRelativeRotation(vRot);

	if (KEY_TAP(KEY::SPACE))
	{
		if (Collider2D()->IsActive())
		{
			Collider2D()->Deactivate();
		}
		else
		{
			Collider2D()->Activate();
		}
		

	}

	/*if (KEY_PRESSED(KEY::X))
	{
		vRot.x += DT * XM_PI;
	}

	if (KEY_PRESSED(KEY::Y))
	{
		vRot.y += DT * XM_PI;
	}

	if (KEY_PRESSED(KEY::Z))
	{
		vRot.z += DT * XM_PI;
	}*/
	//if (KEY_PRESSED(KEY::SPACE))
	//{
	//	Ptr<CMaterial> pMtrl = MeshRender()->GetMaterial();
	//	if (nullptr != pMtrl)
	//	{
	//		pMtrl->SetScalarParam(SCALAR_PARAM::INT_0, 1);
	//	}
	//}
	//else if (KEY_RELEASED(KEY::SPACE))
	//{
	//	Ptr<CMaterial> pMtrl = MeshRender()->GetMaterial();
	//	if (nullptr != pMtrl)
	//	{
	//		pMtrl->SetScalarParam(SCALAR_PARAM::INT_0, 0);
	//	}

	//static float f = 0.f;
	//f += DT * 0.3f;
	//GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::FLOAT_1, f);

	//GamePlayStatic::DrawDebugRect(Vec3(0.f, 0.f, 0.f), Vec3(200.f, 200.f, 1.f), Vec3(0.f, 0.f, 0.f), Vec3(1.f, 1.f, 1.f), true, 20);
	//GamePlayStatic::DrawDebugCircle(Vec3(0.f, 0.f, 0.f), 200.f, Vec3(0.f, 1.f, 1.f), true);
}

void CPlayerScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CPlayerScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	
}

void CPlayerScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CPlayerScript::SaveToFile(FILE* _File)
{
	fwrite(&m_Speed, sizeof(float), 1, _File);
}

void CPlayerScript::LoadFromFile(FILE* _File)
{
	fread(&m_Speed, sizeof(float), 1, _File);
}
