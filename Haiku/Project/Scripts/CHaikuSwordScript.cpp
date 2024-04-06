#include "pch.h"
#include "CHaikuSwordScript.h"

#include "CHaikuScript.h"

CHaikuSwordScript::CHaikuSwordScript()
	: CScript(HAIKUSWORDSCRIPT)
{
}

CHaikuSwordScript::~CHaikuSwordScript()
{
}

void CHaikuSwordScript::begin()
{
	GetRenderComponent()->GetDynamicMaterial();
}

void CHaikuSwordScript::tick()
{
	// 하이쿠의 자식인 경우
	Transform()->SetRelativePos(Vec3(0,0,0));


	//int a = GetOwner()->GetParent()->GetScript<CHaikuScript>()->GetPrevDir();
	//GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, a);
}

void CHaikuSwordScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CHaikuSwordScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CHaikuSwordScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CHaikuSwordScript::SaveToFile(FILE* _File)
{
}

void CHaikuSwordScript::LoadFromFile(FILE* _File)
{
}
