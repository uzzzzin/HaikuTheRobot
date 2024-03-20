#include "pch.h"
#include "TileMapUI.h"

#include <Engine/CTileMap.h>


TileMapUI::TileMapUI()
	: ComponentUI("TileMap", "##TileMap", COMPONENT_TYPE::TILEMAP)
	, bStartBtn (false)
{
	SetSize(ImVec2(0.f, 250.f));
	SetComopnentTitle("TileMap");
}

TileMapUI::~TileMapUI()
{
}

void TileMapUI::render_update()
{
	if (nullptr == GetTargetObject())
		return;

	ComponentUI::render_update();

	// =============================================================================

	// Ÿ�ϸ� GO�� ��ü ũ�� �����ֱ� : ����, ���� ĭ�� ����

	ImGui::Text(u8"Ÿ�ϸ� GO ���� ĭ ���� (FaceX)");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(100);
	ImGui::InputInt("##FaceX", &m_faceX, 1, 1, ImGuiInputTextFlags_EnterReturnsTrue);

	ImGui::Text(u8"Ÿ�ϸ� GO ���� ĭ ���� (FaceY)");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(100);
	ImGui::InputInt("##FaceY", &m_faceY, 1, 1, ImGuiInputTextFlags_EnterReturnsTrue);
	
	if (ImGui::Button("TileMap -> SetFace()", ImVec2(220, 30)))
	{
		GetTargetObject()->TileMap()->SetFace(m_faceX, m_faceY);
	}

	// =============================================================================

	if (ImGui::Button(u8"TileMap ���� ���� ��Ʋ�� �����ϱ�", ImVec2(220, 30)))
	{
		bStartBtn = true;
	}

	if (bStartBtn)
	{
		ImGui::Begin(u8"TileMap Component");

		if (nullptr == m_curAtlasTex)
		{
			m_curAtlasTex = SetImageForMakeAnim();
		}

		realWidth = m_curAtlasTex->GetWidth();
		realHeight = m_curAtlasTex->GetHeight();

		float Width = realWidth;
		float Height = realHeight;

		ImGui::Text("Width ");
		ImGui::SameLine();
		ImGui::InputFloat("##TextureWidth", &Width, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);

		ImGui::Text("Height");
		ImGui::SameLine();
		ImGui::InputFloat("##TextureHeight", &Height, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);

		while (Width >= 600 && Height >= 600)
		{
			Width /= 2;
			Height /= 2;
		}

		float atlasDiv = realWidth / Width;

		ImVec2 startPos = ImGui::GetCursorScreenPos(); // �̹����� ���� ��ġ
		ImGui::Image(m_curAtlasTex->GetSRV().Get(), ImVec2(Width, Height));

		// x ������, ��
		ImGui::Text("grid Width cnt (X)");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		ImGui::InputInt("##�׸��� �� ����", &gridWidthCnt, 1, 1, ImGuiInputTextFlags_EnterReturnsTrue);
		float xSize = Width / gridWidthCnt;
		ImGui::SameLine();
		ImGui::Text("X size ");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		ImGui::InputFloat("##�� ������", &xSize, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);

		// y ������, ��
		ImGui::Text("grid Height cnt (Y)");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		ImGui::InputInt("##�׸��� �� ����", &gridHeightCnt, 1, 1, ImGuiInputTextFlags_EnterReturnsTrue);
		float ySize = Height / gridHeightCnt;
		ImGui::SameLine();
		ImGui::Text("Y size ");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		ImGui::InputFloat("##�� ������", &ySize, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);

		if (ImGui::Button("Create Grid", ImVec2(90, 25)))
		{
			bSetGrid = true;
		}

		if (bSetGrid)
		{
			ImDrawList* drawList = ImGui::GetWindowDrawList();

			// ������ �׸���
			for (int x = 0; x <= gridWidthCnt; ++x)
			{
				drawList->AddLine(ImVec2(startPos.x + x * xSize, startPos.y), ImVec2(startPos.x + x * xSize, startPos.y + Height), IM_COL32(200, 30, 30, 255), 1.5f);
			}

			// ���� �׸���
			for (int y = 0; y <= gridHeightCnt; ++y)
			{
				drawList->AddLine(ImVec2(startPos.x, startPos.y + y * ySize), ImVec2(startPos.x + Width, startPos.y + y * ySize), IM_COL32(200, 30, 30, 255), 1.5f);
			}
		}








		

		ImGui::End(); // TileMap �� ���� Begin/End

		// =============================================================================
	}

}


Ptr<CTexture> TileMapUI::SetImageForMakeAnim()
{
	wstring fileName;

	// ���� Ž����
	wchar_t szFilePath[256] = {};

	OPENFILENAME ofn = {};

	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = nullptr;
	ofn.lpstrFile = szFilePath;
	ofn.lpstrFileTitle = NULL;
	ofn.nMaxFile = sizeof(szFilePath);
	ofn.lpstrFilter = L"ALL\0*.*\0texture\0*.png\0*.bmp";
	ofn.nFilterIndex = 1;

	wstring strInitPath = CPathMgr::GetContentPath();
	strInitPath += L"texture\\";
	ofn.lpstrInitialDir = strInitPath.c_str();

	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn))
	{
		fileName = ofn.lpstrFile;
		size_t pos = fileName.find_last_of(L"\\");
		if (pos != wstring::npos)
		{
			fileName = fileName.substr(pos + 1);
		}
	}
	Ptr<CTexture> curAtlasTex = CAssetMgr::GetInst()->Load<CTexture>(L"texture\\" + fileName, L"texture\\" + fileName);
	return curAtlasTex;
}