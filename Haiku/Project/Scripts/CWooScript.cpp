#include "pch.h"
#include "CWooScript.h"

CWooScript::CWooScript()
	:CScript(WOOSCRIPT)
{
}

CWooScript::~CWooScript()
{
}

void CWooScript::begin()
{
}

void CWooScript::tick()
{
	if (KEY_TAP(KEY::B))
		Animator2D()->Play(L"test");

	if (KEY_TAP(KEY::V))
		Animator2D()->Play(L"test2");
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


