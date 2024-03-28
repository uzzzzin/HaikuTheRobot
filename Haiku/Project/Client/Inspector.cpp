#include "pch.h"
#include "Inspector.h"

#include <Engine/CTransform.h>

#include "TransformUI.h"
#include "MeshRenderUI.h"
#include "Collider2DUI.h"
#include "Light2DUI.h"
#include "Animator2DUI.h"
#include "ScriptUI.h"

#include "AssetUI.h"

#include "ObjectController.h"
#include "Outliner.h"


Inspector::Inspector()
	: UI("Inspector", "##Inspector")
	, m_TargetObject(nullptr)
	, m_arrComUI{}
	, m_ObjController(nullptr)
{
	// �ڽ� UI ����
	CreateChildUI();
}

Inspector::~Inspector()
{
	if (nullptr != m_ObjController)
		delete m_ObjController;
}


void Inspector::tick()
{
	m_ObjController->tick();
}

void Inspector::render_update()
{
	m_ObjController->render();

	ImGui::Separator();

	if (nullptr == m_TargetObject)
		return;

	if (nullptr != m_TargetObject)
	{
		string strName = string(m_TargetObject->GetName().begin(), m_TargetObject->GetName().end());
		ImGui::Text(strName.c_str());

		// name
		char str[100]{};
		strcpy_s(str, ToString(GetTargetObject()->GetName()).c_str());

		ImGui::Text("Name"); ImGui::SameLine();
		if (ImGui::InputText("##InspectorObjName", str, 100, ImGuiInputTextFlags_EnterReturnsTrue))
		{
			GetTargetObject()->SetName(ToWString(string(str)));
			Outliner* outliner = (Outliner*)CImGuiMgr::GetInst()->FindUI("##Outliner");
			outliner->ResetCurrentLevel();
		}

		// layer
		ImGui::Text("Layer"); ImGui::SameLine();
		DrawLayerUI();
		ImGui::Separator();
	}
}

void Inspector::SetTargetObject(CGameObject* _Object)
{
	// Target ������Ʈ ����
	m_TargetObject = _Object;

	// �ش� ������Ʈ�� �����ϰ� �ִ� ������Ʈ�� �����ϴ� ������ƮUI Ȱ��ȭ
	for (UINT i = 0; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		if (nullptr != m_arrComUI[i])
		{
			m_arrComUI[i]->SetTargetObject(_Object);
		}
	}

	// �ش� ������Ʈ�� �����ϰ� �ִ� Script �� ���߾ ScriptUI �� Ȱ��ȭ ��Ų��.
	for (size_t i = 0; i < m_vecScriptUI.size(); ++i)
	{
		m_vecScriptUI[i]->Deactivate();
	}


	if(nullptr != _Object) // ������Ʈ ���� ��
	{

		if (m_vecScriptUI.size() < _Object->GetScripts().size())
		{
			ResizeScriptUI(_Object->GetScripts().size());
		}

		const vector<CScript*>& vecScripts = _Object->GetScripts();

		for (size_t i = 0; i < vecScripts.size(); ++i)
		{
			m_vecScriptUI[i]->SetScript(vecScripts[i]);			
		}
	}


	// AssetUI ��Ȱ��ȭ
	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		m_arrAssetUI[i]->Deactivate();
	}
}

void Inspector::SetTargetAsset(Ptr<CAsset> _Asset)
{
	SetTargetObject(nullptr);

	m_TargetAsset = _Asset;

	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		m_arrAssetUI[i]->Deactivate();
	}
		
	if(nullptr != m_TargetAsset)
	{
		m_arrAssetUI[(UINT)m_TargetAsset->GetType()]->Activate();
		m_arrAssetUI[(UINT)m_TargetAsset->GetType()]->SetAsset(_Asset);
	}	
}


void Inspector::DrawLayerUI()
{
	ImGui::BeginGroup();
	{
		const vector<string>& LayerName = CImGuiMgr::GetInst()->GetLayerName();
		int item_current_idx = m_TargetObject->GetLayerIdx();
		int item_prev_idx = item_current_idx;
		if (ImGui::BeginCombo("##CheckLayerList", LayerName[item_current_idx].c_str()))
		{
			for (int i = 0; i < LayerName.size(); i++)
			{
				const bool is_selected = (item_current_idx == i);

				if (ImGui::Selectable(LayerName[i].c_str(), is_selected))
					item_current_idx = i;

				if (is_selected)
					ImGui::SetItemDefaultFocus();
			}
			ImGui::EndCombo();
		}

		if (item_prev_idx != item_current_idx)
			m_TargetObject->ChangeLayer(item_current_idx);
		item_prev_idx = item_current_idx;

		ImGui::EndGroup();
	}
}