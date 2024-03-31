#include "pch.h"
#include "CPlatformScript.h"


CPlatformScript::CPlatformScript()
	:CScript(PLATFORMSCRIPT)
{
}

CPlatformScript::~CPlatformScript()
{
}

void CPlatformScript::begin()
{
}

void CPlatformScript::tick()
{

}

void CPlatformScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	int a = 0;
}

void CPlatformScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (4 == _OtherObj->GetLayerIdx()) // ¾ê°¡ ÇÏÀÌÄíÀÏ ¶§
	{
		float y1 = Transform()->GetRelativePos().y + Transform()->GetRelativeScale().y / 2;

		float y2 = _OtherCollider->GetFinalPos().y - _OtherCollider->GetScale().y / 2;

		float y3 = y1 - y2;

		Vec3 v = Vec3(_OtherObj->Transform()->GetRelativePos().x, _OtherObj->Transform()->GetRelativePos().y + y3, _OtherObj->Transform()->GetRelativePos().z);

		_OtherObj->Transform()->SetRelativePos(v);
	}
}

void CPlatformScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CPlatformScript::SaveToFile(FILE* _File)
{
}

void CPlatformScript::LoadFromFile(FILE* _File)
{
}


//Vec3 HaikuPos = _OtherObj->Transform()->GetRelativePos();
//Vec3 HaikuScale = _OtherObj->Transform()->GetRelativeScale();
//float up = (Transform()->GetRelativeScale().y / 2.f + _OtherCollider->GetScale().y / 2.f - abs(Transform()->GetRelativePos().y - HaikuPos.y)) / 2.f;
//HaikuPos.y -= up;
//_OtherObj->Transform()->SetRelativePos(HaikuPos);
/*float up = (_OwnCol->GetScale().y / 2.f + _OtherCol->GetScale().y / 2.f - abs(_OwnCol->GetPos().y - _OtherCol->GetPos().y)) / 2.f;*/
//_OtherObj->SetPos(Vec2(_OtherObj->GetPos().x, _OtherObj->GetPos().y - up));