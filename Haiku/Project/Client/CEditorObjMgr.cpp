#include "pch.h"
#include "CEditorObjMgr.h"

#include "CGameObjectEx.h"

#include <Engine/CGameObject.h>
#include <Engine/components.h>
#include "CCameraMoveScript.h"
#include <Engine/CRenderMgr.h>

CEditorObjMgr::CEditorObjMgr()
{

}

CEditorObjMgr::~CEditorObjMgr()
{
	Delete_Vec(m_vecEditorObj);
}

void CEditorObjMgr::init()
{
	// 에디터용 카메라 오브젝트 생성
	CGameObjectEx* pEditorCam = new CGameObjectEx;
	pEditorCam->SetName(L"EditorCam");
	pEditorCam->AddComponent(new CTransform);
	pEditorCam->AddComponent(new CCamera);
	pEditorCam->AddComponent(new CCameraMoveScript);
	
	pEditorCam->Camera()->LayerCheckAll();
	pEditorCam->Camera()->LayerCheck(31, false);
	pEditorCam->Camera()->SetProjType(PROJ_TYPE::ORTHOGRAPHIC);
	pEditorCam->Camera()->SetFOV(XM_PI / 2.f);
	pEditorCam->Camera()->SetFar(100000.f);

	pEditorCam->Camera()->SetScale(3.f);

	pEditorCam->Transform()->SetRelativePos(Vec3( -480.f, 120.f, -100.f));

	m_vecEditorObj.push_back(pEditorCam);

	// Editor 용 카메라로서 렌더매니저에 등록
	CRenderMgr::GetInst()->RegisterEditorCamera(pEditorCam->Camera());
}

void CEditorObjMgr::progress()
{
	for (size_t i = 0; i < m_vecEditorObj.size(); ++i)
	{
		m_vecEditorObj[i]->tick();
	}

	for (size_t i = 0; i < m_vecEditorObj.size(); ++i)
	{
		m_vecEditorObj[i]->finaltick();
	}
}

CGameObject* CEditorObjMgr::FindObjectByName(const wstring& _strName)
{
	for (int i = 0; i < m_vecEditorObj.size(); ++i)
	{
		if (_strName == m_vecEditorObj[i]->GetName())
		{
			CGameObject* pObject = new CGameObject;
			pObject = m_vecEditorObj[i];
			return pObject;
		}
	}
}