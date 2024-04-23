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


	int dir = GetOwner()->GetParent()->GetScript<CHaikuScript>()->GetCurDir();
	GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, dir);
	
	wstring state = GetOwner()->GetParent()->GetScript<CHaikuScript>()->GetCurStateName();
	
	if (L"PlatformGeneralAttack" == state || L"JumpRiseGeneralAttack" == state)
	{
		if (0 == dir) // 방향이 right 일 때
		{
			Collider2D()->SetOffset(Vec3(0.08, -0.02, 0));
			Collider2D()->SetScale(Vec3(0.56, 0.5, 1));
		}
		else if(1 == dir) // 방향이 left 일 때
		{
			Collider2D()->SetOffset(Vec3(-0.08, -0.02, 0));
			Collider2D()->SetScale(Vec3(0.56, 0.5, 1));
		}
	}

	if (L"JumpRiseUpAttack" == state) 
	{
		if (0 == dir) // 방향이 right 일 때
		{
			Collider2D()->SetOffset(Vec3(0, 0.085, 0));
			Collider2D()->SetScale(Vec3(0.56, 0.43, 1));

		}
		else if (1 == dir) // 방향이 left 일 때
		{
			Collider2D()->SetOffset(Vec3(0, 0.085, 0));
			Collider2D()->SetScale(Vec3(0.56, 0.43, 1));
		}
	}

	if (L"JumpRiseDownAttack" == state)
	{
		if (0 == dir) // 방향이 right 일 때
		{
			Collider2D()->SetOffset(Vec3(0.01, -0.125, 0));
			Collider2D()->SetScale(Vec3(0.54, 0.49, 1));
		}
		else if (1 == dir) // 방향이 left 일 때
		{
			Collider2D()->SetOffset(Vec3(-0.01, -0.125, 0));
			Collider2D()->SetScale(Vec3(0.54, 0.49, 1));
		}
	}

	if (L"JumpFallGeneralAttack" == state)
	{
		if (0 == dir) // 방향이 right 일 때
		{
			Collider2D()->SetOffset(Vec3(0.08, -0.02, 0));
			Collider2D()->SetScale(Vec3(0.56, 0.5, 1));
		}
		else if (1 == dir) // 방향이 left 일 때
		{
			Collider2D()->SetOffset(Vec3(-0.08, -0.02, 0));
			Collider2D()->SetScale(Vec3(0.56, 0.5, 1));
		}
	}
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
