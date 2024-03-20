#include "pch.h"
#include "CWooScript.h"

#include <Engine/CGameObject.h>

#include <Engine/CMaterial.h>
#include <Engine/CRenderComponent.h>

CWooScript::CWooScript()
	:CScript(WOOSCRIPT)
{
}

CWooScript::~CWooScript()
{
}

void CWooScript::begin()
{
	//Ptr<CTexture> pAltasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\TILE.bmp", L"texture\\TILE.bmp");

	//GetRenderComponent()->GetDynamicMaterial();
}

void CWooScript::tick()
{
	if (KEY_TAP(KEY::T))
		Animator2D()->Play(L"tileTest");
}

void CWooScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CWooScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CWooScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}


