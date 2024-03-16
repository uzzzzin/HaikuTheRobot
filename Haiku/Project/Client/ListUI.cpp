#include "pch.h"
#include "ListUI.h"

ListUI::ListUI()
	: UI("", "##List")
    , m_CallBackFunc(nullptr)
{
	Deactivate();
    SetModal(true);
}

ListUI::~ListUI()
{
}

void ListUI::render_update()
{
    ImVec2 vWinSize = ImGui::GetWindowContentRegionMax();
    vWinSize.y -= 27;
       
    static int item_current_idx = 0; // Here we store our selection data as an index.
    if (ImGui::BeginListBox("##ListBox", vWinSize))
    {
        for (int i = 0; i < m_vecStr.size(); i++)
        {
            const bool is_selected = (item_current_idx == i);

            if (ImGui::Selectable(m_vecStr[i].c_str(), is_selected))
                item_current_idx = i;

            // ����Ʈ �� �ش� �׸��� Ŭ���Ǹ� ���̶���Ʈ �ɾ���
            if (is_selected)
                ImGui::SetItemDefaultFocus();

            // ����Ʈ �׸� �� ����Ŭ���� �߻��Ѵٸ�            
            if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
            {
                m_strDBClicked = m_vecStr[i];

                // ��ϵ� CallBack �� ������ ȣ��
                if (nullptr != m_CallBackFunc)
                {
                    m_CallBackFunc((DWORD_PTR)m_strDBClicked.c_str());
                }

                // ��ϵ� Delegate �� ������ ȣ��
                if (m_pUI && m_Func)
                {
                    (m_pUI->*m_Func)((DWORD_PTR)m_strDBClicked.c_str());
                }                 

                Deactivate();
            }
        }
        ImGui::EndListBox();
    }
}

void ListUI::Deactivate()
{
	UI::Deactivate();
	m_vecStr.clear();
    ImGui::SetWindowFocus(nullptr);
}