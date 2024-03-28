#include "pch.h"
#include "ObjectController.h"


#include <Engine\CTimeMgr.h>
#include <Engine\CRenderMgr.h>
#include <Engine\CLevelMgr.h>
#include <Engine\CKeyMgr.h>
#include <Engine\CLevel.h>
#include <Engine\CLayer.h>

#include <Engine\CTransform.h>
#include <Engine\CCamera.h>

#include "CImGuiMgr.h"
#include "Inspector.h"
#include <Engine\CGameObject.h>

#include "UI.h"

ObjectController::ObjectController()
	: m_CurLayer("[All]")
	, m_ClickedObject(nullptr)
{
}

ObjectController::~ObjectController()
{
}

void ObjectController::FocusObject(CGameObject* _Object)
{
	CCamera* pEditCam = CRenderMgr::GetInst()->GetEditorCam();

	if (nullptr == pEditCam)
		return;

	Vec3 ObjectPos = _Object->Transform()->GetRelativePos();
	Vec3 EditCamPos = pEditCam->Transform()->GetRelativePos();
	
	pEditCam->Transform()->SetRelativePos(Vec3(ObjectPos.x, ObjectPos.y, EditCamPos.z));
}

void ObjectController::tick()
{
	CCamera* pCurCam = nullptr;
	if (CRenderMgr::GetInst()->IsEditorMode())
	{
		pCurCam = CRenderMgr::GetInst()->GetEditorCam();
	}
	else
	{
		vector<CCamera*> vecCams = CRenderMgr::GetInst()->GetCameras();
		if (vecCams.size() > 0)
		{
			pCurCam = vecCams[0];
		}
	}

	// ī�޶� ���ٸ� return
	if (nullptr ==  pCurCam)
	{
		return;
	}

	// mouse pos
	ImVec2 mousePosition = ImGui::GetMousePos();


	ImVec2 ViewportStart = CImGuiMgr::GetInst()->GetViewportStart();
	ImVec2 ViewportSize = CImGuiMgr::GetInst()->GetViewportSize();


	// ���콺�� ���� �ȿ� �ִٸ�
	if (mousePosition.x >= ViewportStart.x && mousePosition.y >= ViewportStart.y
		&& mousePosition.x <= ViewportStart.x + ViewportSize.x && mousePosition.y <= ViewportStart.y + ViewportSize.y)
	{
		// �ش� ���콺 Pos -> World Pos�� ��ȯ 
		// �ش� ������ �߾�
		ImVec2 WinCenter = ImVec2(ViewportStart.x + ViewportSize.x / 2.f, ViewportStart.y + ViewportSize.y / 2.f);

		// Window ��ǥ��� y�� ������ ��� ��
		ImVec2 diffVec = mousePosition - WinCenter;
		diffVec.y *= -1;

		Vec2 MouseWorldPos = pCurCam->GetWorldPosInWindow(Vec2(diffVec.x, diffVec.y));


		// ���콺�� Ŭ�� �Ǿ��ٸ�
		if (KEY_TAP(KEY::LBTN) && KEY_PRESSED(KEY::LCTRL))
		{
			CGameObject* pObject = FindObject(MouseWorldPos);

			Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
			pInspector->SetTargetObject(pObject);
			m_ClickedObject = pObject;

		}

		if (nullptr != m_ClickedObject)
		{
			// ���� Ÿ�ٵ� ������Ʈ ���� ��������
			Vec3 TargetPos = m_ClickedObject->Transform()->GetWorldPos();
			Vec3 TargetScale = m_ClickedObject->Transform()->GetWorldScale();

			// ���콺�� ������Ʈ ���� �ȿ� �ִٸ�
			if (MouseWorldPos.x >= TargetPos.x - TargetScale.x / 2.f && MouseWorldPos.x <= TargetPos.x + TargetScale.x / 2.f
				&& MouseWorldPos.y >= TargetPos.y - TargetScale.y / 2.f && MouseWorldPos.y <= TargetPos.y + TargetScale.y / 2.f)
			{
				// ���콺�� Ŭ�� �Ǿ��ٸ�
				if (KEY_PRESSED(KEY::LBTN))
				{
					// ������Ʈ �̵�
					Vec2 Drag = CKeyMgr::GetInst()->GetMouseDrag();

					if (Drag.Length() < 100.f)
					{
						float CamScale = pCurCam->GetScale();

						TargetPos.x += Drag.x * CamScale;
						TargetPos.y -= Drag.y * CamScale;

						m_ClickedObject->Transform()->SetRelativePos(TargetPos);
					}


				}
			}
		}

		// Ű���� �̵�
		if (nullptr != m_ClickedObject)
		{
			// ���� Ÿ�ٵ� ������Ʈ ���� ��������
			Vec3 TargetPos = m_ClickedObject->Transform()->GetWorldPos();
			Vec3 TargetScale = m_ClickedObject->Transform()->GetWorldScale();

			if (KEY_PRESSED(KEY::LEFT))
			{
				TargetPos.x += -100.f * DT_ENGINE;

				m_ClickedObject->Transform()->SetRelativePos(TargetPos);
			}

			if (KEY_PRESSED(KEY::RIGHT))
			{
				TargetPos.x += 100.f * DT_ENGINE;

				m_ClickedObject->Transform()->SetRelativePos(TargetPos);
			}

			if (KEY_PRESSED(KEY::UP))
			{
				TargetPos.y += 100.f * DT_ENGINE;

				m_ClickedObject->Transform()->SetRelativePos(TargetPos);
			}

			if (KEY_PRESSED(KEY::DOWN))
			{
				TargetPos.y += -100.f * DT_ENGINE;

				m_ClickedObject->Transform()->SetRelativePos(TargetPos);
			}
		}

		//// ���� Ÿ�ٵ� ������Ʈ�� ���ٸ�
		//if (nullptr == m_ClickedObject)
		//{
		//	// ���콺�� Ŭ�� �Ǿ��ٸ�
		//	if (KEY_TAP(KEY::LBTN))
		//	{
		//		CGameObject* pObject = FindObject(MouseWorldPos);

		//		if (pObject != nullptr)
		//		{
		//			Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
		//			pInspector->SetTargetObject(pObject);
		//		}
		//	}
		//}
		//// ���� Ÿ�ٵ� ������Ʈ�� �ִٸ�
		//else
		//{
		//	// ���� Ÿ�ٵ� ������Ʈ ���� ��������
		//	Vec3 TargetPos = m_ClickedObject->Transform()->GetWorldPos();
		//	Vec3 TargetScale = m_ClickedObject->Transform()->GetWorldScale();

		//	// ���콺�� ������Ʈ ���� �ȿ� �ִٸ�
		//	if (MouseWorldPos.x >= TargetPos.x - TargetScale.x / 2.f && MouseWorldPos.x <= TargetPos.x + TargetScale.x / 2.f
		//		&& MouseWorldPos.y >= TargetPos.y - TargetScale.y / 2.f && MouseWorldPos.y <= TargetPos.y + TargetScale.y / 2.f)
		//	{
		//		// ���콺�� Ŭ�� �Ǿ��ٸ�
		//		if (KEY_PRESSED(KEY::LBTN))
		//		{
		//			// ������Ʈ �̵�
		//			Vec2 Drag = CKeyMgr::GetInst()->GetMouseDrag();
		//			float CamScale = pCurCam->GetScale();

		//			TargetPos.x += Drag.x * CamScale;
		//			TargetPos.y -= Drag.y * CamScale;

		//			m_ClickedObject->Transform()->SetRelativePos(TargetPos);
		//		}
		//	}
		//	// ���콺�� ������Ʈ ���� �ۿ� �ִٸ�
		//	else 
		//	{
		//		// ���콺�� Ŭ�� �Ǿ��ٸ�
		//		if (KEY_TAP(KEY::LBTN))
		//		{
		//			CGameObject* pObject = FindObject(MouseWorldPos);


		//			if (pObject != nullptr)
		//			{
		//				Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
		//				pInspector->SetTargetObject(pObject);
		//			}
		//		}
		//	}
		//}

	}

	m_vecObject.clear();

}

void ObjectController::render()
{

	if (!CRenderMgr::GetInst()->IsEditorMode())
	{
		return;
	}

	ImGui::Text("Layer"); ImGui::SameLine(150);


	// ---------------------------------------- ���̾� �̸� ���� �����ϰ� -> ��ø� ���� ������
	
	//if (ImGui::Button("Fix", ImVec2(20, 20)))
	//{

	//}

	// ----------------------------------------

	m_vecLayerName.push_back("[All]");

	const vector<string>& LayerName = CImGuiMgr::GetInst()->GetLayerName();

	for (int i = 0; i < LayerName.size(); ++i)
	{
		m_vecLayerName.push_back(LayerName[i]);
	}

	if (ImGui::BeginCombo("##LayerCombo", m_CurLayer.data())) {

		for (int i = 0; i < m_vecLayerName.size(); ++i)
		{
			if (ImGui::Selectable(m_vecLayerName[i].c_str())) 
			{
				m_CurLayer = m_vecLayerName[i];
			}
		}

		ImGui::EndCombo();
	}

	CCamera* EditorCam = CRenderMgr::GetInst()->GetEditorCam();

	if (m_CurLayer == "[All]")
	{
		EditorCam->LayerCheckAll();
		EditorCam->LayerCheck(L"UI", false);
	}
	else
	{
		int LayerIdx = -1;

		size_t start_pos = m_CurLayer.find("[") + 1;
		size_t end_pos = m_CurLayer.find("]");
		if (start_pos != std::string::npos && end_pos != std::string::npos) 
		{
			std::string num_str = m_CurLayer.substr(start_pos, end_pos - start_pos);
			LayerIdx = std::stoi(num_str);
		}

		EditorCam->LayerCheckOffAll();
		EditorCam->LayerCheck(LayerIdx,true);
	}


	m_vecLayerName.clear();
}

void ObjectController::FindObject(vector<CGameObject*>& _OutObject, Vec2 _MouseWorldPos)
{
	CLevel* CurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLayer* pLayer = nullptr;


	for (int i = 0; i < LAYER_MAX; ++i)
	{
		pLayer = CurLevel->GetLayer(i);

		// Layer�� ������Ʈ ��������
		const vector<CGameObject*> LayerObject = pLayer->GetLayerObjects();

		for (int j = 0; j < LayerObject.size(); ++j)
		{
			Vec3 ObjPos = LayerObject[j]->Transform()->GetWorldPos();
			Vec3 ObjScale = LayerObject[j]->Transform()->GetWorldScale();

			// ���콺 ���� �ȿ� �ִٸ�
			if (_MouseWorldPos.x >= ObjPos.x - ObjScale.x / 2.f && _MouseWorldPos.x <= ObjPos.x + ObjScale.x / 2.f
				&& _MouseWorldPos.y >= ObjPos.y - ObjScale.y / 2.f && _MouseWorldPos.y <= ObjPos.y + ObjScale.y / 2.f)
			{
				_OutObject.push_back(LayerObject[j]);
			}
		}
	}
}

CGameObject* ObjectController::FindObject(Vec2 _MouseWorldPos)
{
	CLevel* CurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	CLayer* pLayer = nullptr;

	CGameObject* pTarget = nullptr;
	float minDepth = 100000.f;

	for (int i = 0; i < LAYER_MAX; ++i)
	{
		pLayer = CurLevel->GetLayer(i);

		// Layer�� ������Ʈ ��������
		const vector<CGameObject*> LayerObject = pLayer->GetLayerObjects();

		for (int j = 0; j < LayerObject.size(); ++j)
		{
			Vec3 ObjPos = LayerObject[j]->Transform()->GetWorldPos();
			Vec3 ObjScale = LayerObject[j]->Transform()->GetWorldScale();

			// ���콺 ���� �ȿ� �ִٸ�
			if (_MouseWorldPos.x >= ObjPos.x - ObjScale.x / 2.f && _MouseWorldPos.x <= ObjPos.x + ObjScale.x / 2.f
				&& _MouseWorldPos.y >= ObjPos.y - ObjScale.y / 2.f && _MouseWorldPos.y <= ObjPos.y + ObjScale.y / 2.f)
			{

				// ���� �տ� �ִ� ������ƮƲ Ÿ������ ��
				if (LayerObject[j]->Transform()->GetWorldPos().z < minDepth)
				{
					pTarget = LayerObject[j];
					minDepth = LayerObject[j]->Transform()->GetWorldPos().z;
				}
			}
		}
	}

	return pTarget;
}
