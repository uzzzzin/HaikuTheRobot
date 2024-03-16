#include "pch.h"
#include "AssetUI.h"

AssetUI::AssetUI(const string& _strName, const string& _ID, ASSET_TYPE _Type)
	: UI(_strName, _ID)
	, m_Type(_Type)
{
	Deactivate();

}

AssetUI::~AssetUI()
{
}

void AssetUI::render_update()
{
	ImGui::PushID(0);
	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(0.6f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(0.6f, 0.6f, 0.6f));
	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(0.6f, 0.6f, 0.6f));

	ImGui::Button(ASSET_TYPE_STRING[(UINT)m_Type]);

	ImGui::PopStyleColor(3);
	ImGui::PopID();
}



void AssetUI::SetAsset(Ptr<CAsset> _Asset)
{
	m_Asset = _Asset;

	// �Էµ� Asset �� nullptr �̸� �ش� AssetUI �� ��Ȱ��ȭ �Ѵ�.
	if (nullptr == m_Asset)
	{
		Deactivate();
	}

	else
	{
		// �������� ���� �ּҰ� ���� ���, �� ����UI �� Ÿ�԰� ���� ������ Ÿ���� ��ġ�ϸ�
		// �ش� ����UI �� Ȱ��ȭ ��Ű�� �ƴϸ� ��Ȱ��ȭ ��Ų��.
		if (_Asset->GetType() == m_Type)
		{
			Activate();
		}
		else
		{
			Deactivate();
		}
	}
}
