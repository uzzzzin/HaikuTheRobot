#include "pch.h"
#include "UI.h"


UI::UI(const string& _strName, const string& _strID)
	: m_strName(_strName)
	, m_strID(_strID)
	, m_bActive(true)
	, m_Parent(nullptr)
	, m_bModal(false)
{
}

UI::~UI()
{
	Delete_Vec(m_vecChildUI);
}

void UI::tick()
{

}

void UI::render()
{
	if (!m_bActive)
		return;

	bool Active = m_bActive;

	if (nullptr == GetParentUI())
	{
		// Modal
		if (!m_bModal)
		{
			ImGui::Begin(string(m_strName + m_strID).c_str(), &Active);

			// Ȱ��ȭ, ��Ȱ��ȭ ��ȯ�� �߻��� ��쿡�� Activate or Deactivate �� ȣ���Ų��.
			if (Active != m_bActive)
			{
				m_bActive = Active;

				if (m_bActive)
					Activate();
				else
					Deactivate();
			}

			render_update();

			for (size_t i = 0; i < m_vecChildUI.size(); ++i)
			{
				m_vecChildUI[i]->render();
			}

			ImGui::End();
		}

		// Modal
		else
		{
			ImGui::OpenPopup(string(m_strName + m_strID).c_str());
			if (ImGui::BeginPopupModal(string(m_strName + m_strID).c_str(), &Active))
			{
				render_update();

				for (size_t i = 0; i < m_vecChildUI.size(); ++i)
				{
					m_vecChildUI[i]->render();
				}

				ImGui::EndPopup();
			}

			else
			{
				// Ȱ��ȭ, ��Ȱ��ȭ ��ȯ�� �߻��� ��쿡�� Activate or Deactivate �� ȣ���Ų��.
				if (Active != m_bActive)
				{
					m_bActive = Active;

					if (m_bActive)
						Activate();
					else
						Deactivate();
				}
			}
		}		
	}

	// Child UI �� ���
	else
	{
		ImGui::BeginChild(string(m_strName + m_strID).c_str(), m_vSize);

		render_update();

		for (size_t i = 0; i < m_vecChildUI.size(); ++i)
		{
			m_vecChildUI[i]->render();
		}

		ImGui::EndChild();
	}
}