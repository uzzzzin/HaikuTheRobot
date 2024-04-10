#include "pch.h"
#include "CChangeRoomScript.h"
#include "CRoomMgrScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include "CHaikuScript.h"
#include "CCamEventScript.h"

CChangeRoomScript::CChangeRoomScript()
	:CScript(CHANGEROOMSCRIPT)
	, change(0)
{
}

CChangeRoomScript::~CChangeRoomScript()
{
}

void CChangeRoomScript::begin()
{
	GetRenderComponent()->GetDynamicMaterial();
}

void CChangeRoomScript::tick()
{
	GetRenderComponent()->GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, change);
}

void CChangeRoomScript::BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	change = 1;

	if (false == _OtherObj->GetScript<CHaikuScript>()->GetChanging()) // ü���� ���·� �� �� ( �Ա����� �������� �ɸ�  ��)
	{
		CGameObject* MainCam = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
		MainCam->GetScript<CCamEventScript>()->FadeOut(0.5f);
	}

}

void CChangeRoomScript::Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
}

void CChangeRoomScript::EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider)
{
	if (true == _OtherObj->GetScript<CHaikuScript>()->GetChanging()) // �ⱸ�� ���� ��
	{
		change = 0;
		_OtherObj->GetScript<CHaikuScript>()->SetChanging(false);
		return;
	}
	CGameObject* kingGO = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"ImtheKing");
	kingGO->GetScript<CRoomMgrScript>()->SetChanging(true, GetOwner()->GetName());
}

void CChangeRoomScript::SaveToFile(FILE* _File)
{
}

void CChangeRoomScript::LoadFromFile(FILE* _File)
{
}