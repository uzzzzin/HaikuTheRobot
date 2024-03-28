#include "pch.h"
#include "StateMachineUI.h"

#include <Engine\CStateMachine.h>
#include <Engine\CFSM.h>
#include <Engine\CState.h>
#include <States\CStateMgr.h>

#include"ListUI.h"

StateMachineUI::StateMachineUI()
	: ComponentUI("StateMachine", "##StateMachine", COMPONENT_TYPE::STATEMACHINE)
{
	SetSize(ImVec2(0.f, 250.f));
	SetComopnentTitle("StateMachine");
}

StateMachineUI::~StateMachineUI()
{
}

void StateMachineUI::StateSelect(DWORD_PTR _ptr)
{
	string strState = (char*)_ptr;
	wstring strStateName = ToWString(strState);

	if (m_AddStateKey == "")
		return;

	CState* pState = CStateMgr::GetState(strStateName);
	wstring AddKey = ToWString(m_AddStateKey);

	Ptr<CFSM> pFSM = GetTargetObject()->StateMachine()->GetFSM();

	if (pFSM->FindState(AddKey) == nullptr)
	{
		pFSM->AddState(AddKey, pState);
	}
	else
	{
		MessageBoxA(nullptr, "State�� Key�� �̹� �����մϴ�.", "Add State Failed!", MB_OK);
		delete pState;
	}


}



void StateMachineUI::render_update()
{
	if (nullptr == GetTargetObject())
		return;

	ComponentUI::render_update();

	CGameObject* pTarget = GetTargetObject();
	CStateMachine* pStateMachine = pTarget->StateMachine();
	Ptr<CFSM> pFSM = pStateMachine->GetFSM();


	string FSMName = "";

	if (nullptr != pFSM)
	{
		FSMName = ToString(pFSM->GetKey()).c_str();
	}

	ImGui::Text("FSM Key"); ImGui::SameLine(100);	ImGui::InputText("##FSMName", (char*)FSMName.c_str(), FSMName.length(), ImGuiInputTextFlags_ReadOnly);
	// Mesh Drop üũ
	if (ImGui::BeginDragDropTarget())
	{
		const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("ContentTree");

		if (payload)
		{
			DWORD_PTR data = *((DWORD_PTR*)payload->Data);
			CAsset* pAsset = (CAsset*)data;
			if (ASSET_TYPE::FSM == pAsset->GetType())
			{
				GetTargetObject()->StateMachine()->SetFSM((CFSM*)pAsset);
			}
		}
		ImGui::EndDragDropTarget();
	}

	ImGui::Text("State Name"); ImGui::SameLine(100); ImGui::InputText("##StateName", (char*)m_StateName.c_str(), m_StateName.length(), ImGuiInputTextFlags_ReadOnly);

	vector<string> items;

	if (pFSM.Get())
	{
		const map<wstring, CState*>& States = pFSM->GetStates();

		items.reserve(States.size());

		for (const auto& iter : States)
		{
			items.push_back(ToString(iter.first).c_str());
		}
	}

	char buffer[64];
	strcpy_s(buffer, m_AddStateKey.c_str());
	ImGui::Text("Input Key"); ImGui::SameLine(100); ImGui::InputText("##StatesKey", buffer, 64);
	m_AddStateKey = buffer;

	static int item_current_idx = 0; // Here we store our selection data as an index.
	if (ImGui::BeginListBox("##StatesList", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing())))
	{
		for (int i = 0; i < items.size(); i++)
		{
			const bool is_selected = (item_current_idx == i);

			if (ImGui::Selectable(items[i].c_str(), is_selected))
				item_current_idx = i;

			// ����Ʈ �� �ش� �׸��� Ŭ���Ǹ� ���̶���Ʈ �ɾ���
			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndListBox();
	}

	// ���� ���õ� ������Ʈ�� Ŭ�������� ���� ��
	if (pFSM.Get() && items.size() > item_current_idx)
	{
		CState* SelectState = pFSM->FindState(ToWString(items[item_current_idx]));
		wstring StateName = CStateMgr::GetStateName(SelectState);
		m_StateName = ToString(StateName);
		m_CurStateKey = ToWString(items[item_current_idx]);
	}
	else
	{
		m_StateName = "";
	}

	// ��ư �ʺ� ����
	float buttonWidth = 150.0f;

	// ��ư�� ������ �����Ͽ� ��ġ
	float posX = ImGui::GetWindowWidth() - buttonWidth * 3 - ImGui::GetStyle().ItemSpacing.x*2;
	ImGui::SetCursorPosX(posX);

	ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(10, 0)); // ��ư �� ���� ����

	if (ImGui::Button("Add State", ImVec2(buttonWidth, 0)))
	{
		// ����Ʈ UI
		ListUI* pListUI = (ListUI*)CImGuiMgr::GetInst()->FindUI("##List");

		vector<wstring> vecStateName;
		CStateMgr::GetStateInfo(vecStateName);

		vector<string> vecStateList;

		for (int i = 0; i < vecStateName.size(); ++i)
		{
			vecStateList.push_back(ToString(vecStateName[i]));
		}

		pListUI->AddString(vecStateList);
		pListUI->SetDbClickDelegate(this, (Delegate_1)&StateMachineUI::StateSelect);
		pListUI->Activate();
	}

	ImGui::SameLine(0, ImGui::GetStyle().ItemSpacing.x);
	posX = ImGui::GetWindowWidth() - buttonWidth * 2 - ImGui::GetStyle().ItemSpacing.x;
	ImGui::SetCursorPosX(posX);

	if (ImGui::Button("Delete State", ImVec2(buttonWidth, 0)))
	{
		pFSM->DeleteState(m_CurStateKey);
	}

	ImGui::SameLine(0, ImGui::GetStyle().ItemSpacing.x);
	posX = ImGui::GetWindowWidth() - buttonWidth;
	ImGui::SetCursorPosX(posX);


	if (ImGui::Button("Save", ImVec2(buttonWidth, 0)))
	{
		if (pFSM.Get())
		{
			// ��� ����
			wchar_t szPath[255] = {};
			wstring FilePath = CPathMgr::GetContentPath();
			wstring FSMPath = pFSM->GetRelativePath();
			swprintf_s(szPath, L"%s", FSMPath.c_str());


			// ��� ����
			pFSM->SetName(szPath);

			pFSM->Save(szPath);
			MessageBoxA(nullptr, "FSM�� ����Ǿ����ϴ�.", "Save successed!", MB_OK);
		}

	}

	ImGui::PopStyleVar();
}

