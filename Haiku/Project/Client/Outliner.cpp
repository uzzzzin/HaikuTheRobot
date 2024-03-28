#include "pch.h"
#include "Outliner.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/CKeyMgr.h>

#include "CImGuiMgr.h"
#include "Inspector.h"
#include "TreeUI.h"
#include "MenuUI.h"

#include <Engine/CTaskMgr.h>

//Outliner::Outliner()
//	: UI("Outliner", "##Outliner")
//{
//	m_Tree = new TreeUI("OutlinerTree");
//	m_Tree->ShowRootNode(false);
//	m_Tree->UseDragDrop(true);
//
//	AddChildUI(m_Tree);
//
//	// Ʈ���� Ŭ�� �̺�Ʈ ���
//	m_Tree->AddSelectDelegate(this, (Delegate_1)&Outliner::SelectObject);
//	m_Tree->AddDragDropDelegate(this, (Delegate_2)&Outliner::DragDropObject);
//
//	m_Tree->AddRightClickDelegate(this, (Delegate_0)&Outliner::OpenRightClickMenu);
//
//	if (KEY_TAP(KEY::DEL))
//		DeleteObject();
//
//	if (m_bRightClick)
//	{
//		DrawRightClickMenu();
//	}
//
//	// Ʈ�� ������ ���� ������ ��ü��� ����
//	ResetCurrentLevel();
//}

Outliner::Outliner()
	: UI("Outliner", "##Outliner")
{
	m_Tree = new TreeUI("OutlinerTree");
	m_Tree->ShowRootNode(false);
	m_Tree->UseDragDrop(true);
	m_Tree->AddSelectDelegate(this, (Delegate_1)&Outliner::SelectObject);
	m_Tree->AddRightClickDelegate(this, (Delegate_0)&Outliner::OpenRightClickMenu);
	m_Tree->AddDragDropDelegate(this, (Delegate_2)&Outliner::DragDropObject);

	AddChildUI(m_Tree);

	ResetCurrentLevel();
}

Outliner::~Outliner()
{
}


void Outliner::DrawRightClickMenu()
{
	bool bHovered = false;

	//if (ImGui::BeginPopupContextItem("##OutlinerRightClickPopup"))
	if (ImGui::BeginPopupContextItem("##OutlinerRightClickPopup"))
	{
		if (ImGui::Selectable("Delete"))
		{
			DeleteObject();
			m_bRightClick = false;
		}
		if (ImGui::IsItemHovered()) bHovered |= true;

		if (ImGui::Selectable("Create Prefab"))
		{
			TreeNode* pNode = m_Tree->GetSelectedNode();

			if (pNode)
			{
				// create prefab
				CGameObject* pSelectObj = (CGameObject*)pNode->GetData();
				Ptr<CPrefab> pPrefab = new CPrefab(pSelectObj->Clone(), false);
				wstring strPath = L"prefab\\" + pSelectObj->GetName() + L".pref";
				CAssetMgr::GetInst()->AddAsset(strPath, pPrefab.Get());

				// save prefab
				pPrefab->Save(strPath);
			}

			m_bRightClick = false;
		}
		if (ImGui::IsItemHovered()) bHovered |= true;

		//if (ImGui::Selectable("Create Prefab")) {} //value = 0.0f;

		if (ImGui::Selectable("Close"))
		{
			ImGui::CloseCurrentPopup();
			m_bRightClick = false;
		}

		if (KEY_TAP(KEY::LBTN) && not bHovered)
			m_bRightClick = false;

		ImGui::EndPopup();
	}

	ImGui::OpenPopup("##OutlinerRightClickPopup", ImGuiPopupFlags_MouseButtonRight);
}

void Outliner::DeleteObject()
{
	TreeNode* pNode = m_Tree->GetSelectedNode();

	if (pNode)
	{
		CGameObject* pSelectObj = (CGameObject*)pNode->GetData();
		GamePlayStatic::DestroyGameObject(pSelectObj);
	}
}

//void Outliner::render_update()
//{
//	if (CTaskMgr::GetInst()->GetObjectEvent())
//	{
//		ResetCurrentLevel();
//	}
//
//	if (KEY_TAP(KEY::DEL))
//	{
//		TreeNode* pNode = m_Tree->GetSelectedNode();
//		if (nullptr != pNode)
//		{
//			CGameObject* pSelectObj = (CGameObject*)pNode->GetData();
//			GamePlayStatic::DestroyGameObject(pSelectObj);
//		}
//	}
//}

void Outliner::render_update()
{
	if (CTaskMgr::GetInst()->GetObjectEvent())
		ResetCurrentLevel();


	if (KEY_TAP(KEY::DEL))
		DeleteObject();

	if (m_bRightClick)
	{
		DrawRightClickMenu();
	}
}

void Outliner::ResetCurrentLevel()
{
	// Ʈ�� ������ ����
	m_Tree->ClearNode();

	// ���� ������ �����´�.
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	if (nullptr == pCurLevel)
		return;

	// Ʈ���� ��Ʈ �߰�
	TreeNode* pRootNode = m_Tree->AddTreeNode(nullptr, "DummyRoot", 0);

	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		CLayer* pLayer = pCurLevel->GetLayer(i);
		const vector<CGameObject*>& vecParent = pLayer->GetParentObjects();

		for (size_t i = 0; i < vecParent.size(); ++i)
		{
			AddObjectToTree(pRootNode, vecParent[i]);
		}
	}
}

void Outliner::AddObjectToTree(TreeNode* _Node, CGameObject* _Object)
{
	TreeNode* pNode = m_Tree->AddTreeNode(_Node, string(_Object->GetName().begin(), _Object->GetName().end()), (DWORD_PTR)_Object);

	const vector<CGameObject*>& vecChild = _Object->GetChild();

	for (size_t i = 0; i < vecChild.size(); ++i)
	{
		AddObjectToTree(pNode, vecChild[i]);
	}
}

void Outliner::SelectObject(DWORD_PTR _Node)
{
	TreeNode* pNode = (TreeNode*)_Node;
	CGameObject* pObject = (CGameObject*)pNode->GetData();

	if (nullptr == pObject)
		return;

	Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");

	if (pInspector->GetTargetObject() == pObject)
	{
		pInspector->GetObjController()->FocusObject(pObject);
	}

	pInspector->SetTargetObject(pObject);
}

void Outliner::DragDropObject(DWORD_PTR _Dest, DWORD_PTR _Source)
{
	TreeNode* pDestNode = (TreeNode*)_Dest;
	TreeNode* pSourceNode = (TreeNode*)_Source;

	CGameObject* pDestObj = nullptr;
	if(nullptr != pDestNode)
		pDestObj = (CGameObject*)pDestNode->GetData();

	CGameObject* pSourceObj = (CGameObject*)pSourceNode->GetData();

	// �θ� ������Ʈ�� �ڽ��� �ڽĿ�����Ʈ�� �ڽ����� ������ ���� ����
	if (pDestObj != nullptr && pDestObj->IsAncestor(pSourceObj))
		return;

	if (nullptr == pDestNode)
	{
		int LayerIdx = pSourceObj->DisconnectWithParent();

		// ���� �θ� ������
		if (LayerIdx == -1)
			return;

		CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
		pCurLevel->AddObject(pSourceObj, LayerIdx, false);
	}
	else
	{		
		pDestObj->AddChild(pSourceObj);
	}

	ResetCurrentLevel();
}
