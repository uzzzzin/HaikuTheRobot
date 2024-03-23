#include "pch.h"
#include "TileMapUI.h"

#include <Engine/CEngine.h>
#include <Engine/CRenderMgr.h>
#include <Engine/CCamera.h>

#include <Engine/CTileMap.h>
#include <Engine/CTransform.h>



TileMapUI::TileMapUI()
	: ComponentUI("TileMap", "##TileMap", COMPONENT_TYPE::TILEMAP)
	, bStartBtn (false)
	, bReady (false)
{
	SetSize(ImVec2(0.f, 1000.f));
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

	// Ÿ�ϸ� GO�� ��ü ũ�� �����ֱ� : ����, ���� ĭ�� ����, Render�� Ÿ�� ����� !

	ImGui::Text(u8"Ÿ�ϸ� ���� ĭ ���� (FaceX, �⺻ 2)");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(100);
	ImGui::InputInt("##FaceX", &m_faceX, 1, 1, ImGuiInputTextFlags_EnterReturnsTrue);

	ImGui::Text(u8"Ÿ�ϸ� ���� ĭ ���� (FaceY, �⺻ 2)");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(100);
	ImGui::InputInt("##FaceY", &m_faceY, 1, 1, ImGuiInputTextFlags_EnterReturnsTrue);

	ImGui::Text(u8"Ÿ�� X ���� ������ (TileRenderSizeX, �⺻ 128)");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(100);
	ImGui::InputFloat("##TileRenderSizeX", &TileRenderSize.x, ImGuiInputTextFlags_EnterReturnsTrue);

	ImGui::Text(u8"Ÿ�� Y ���� ������ (TileRenderSizeY, �⺻ 128)");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(100);
	ImGui::InputFloat("##TileRenderSizeY", &TileRenderSize.y, ImGuiInputTextFlags_EnterReturnsTrue);

	if (ImGui::Button(u8"TileMap ���� ���� ��Ʋ�� �����ϱ�", ImVec2(220, 25)))
	{
		bStartBtn = true;
		m_curAtlasTex = SetImageForMakeAnim();
	}

	if (nullptr != m_curAtlasTex)
	{
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
			GetTargetObject()->TileMap()->SetTileAtlas(m_curAtlasTex, atlasDiv * Vec2(xSize, ySize));
			GetTargetObject()->TileMap()->SetTileRenderSize(TileRenderSize);
			GetTargetObject()->TileMap()->SetFace(m_faceX, m_faceY);
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

			// ��Ŭ�� �� ĭ�� �ȷ�Ʈ���� ���õ� Ÿ��. ���� �귯���ΰ���
			if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
			{
				ImVec2 mousePos = ImGui::GetMousePos();

				for (int row = 0; row < gridHeightCnt; ++row)
				{
					for (int col = 0; col < gridWidthCnt; ++col)
					{
						if (mousePos.x >= startPos.x + xSize * col && mousePos.x < startPos.x + xSize * (col + 1)
							&& mousePos.y >= startPos.y + ySize * row && mousePos.y < startPos.y + ySize * (row + 1))
						{
							curBrushIdxCol = col;
							curBrushIdxRow = row;

							bReady = true;
						}
					}
				}
			}
		}
	}

	if (bReady) // ��ĥ �� �غ� �Ϸ�Ǿ��ٸ�. (�귯���� �����ؼ� ��� �ִٸ�.)
	{
		// �� ���콺 Pos(�� screenPos)�� Ÿ�ϸ� GO�� ���� Pos�� ����

		if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
		{
			int screenWidth = CEngine::GetInst()->GetResolution().x;
			int screenHeight = CEngine::GetInst()->GetResolution().y;

			POINT pt = {};
			GetCursorPos(&pt);
			ScreenToClient(CEngine::GetInst()->GetMainWind(), &pt);
			Vec2 LClickedScreenPos = Vec2((float)pt.x, (float)pt.y);
			Vec3 CamPos = CRenderMgr::GetInst()->GetEditorCam()->Camera()->Transform()->GetRelativePos();
			Vec3 CamScale = CRenderMgr::GetInst()->GetEditorCam()->Camera()->Transform()->GetRelativeScale();

			Vec2 LClickedRelataivePos = Vec2(CamPos.x - screenWidth / 2 + LClickedScreenPos.x, CamPos.y - screenHeight / 2 + LClickedScreenPos.y);
			//World(X, Y) = (CameraPos.x - Camera.Width / 2 + Screen.X, CameraPos.Y - Camera.Height / 2 + Screen.Y)

			Vec2 GOPos = Vec2(GetTargetObject()->Transform()->GetRelativePos().x, GetTargetObject()->Transform()->GetRelativePos().y);
			Vec2 GOScale = Vec2(GetTargetObject()->Transform()->GetRelativeScale().x, GetTargetObject()->Transform()->GetRelativeScale().y);

			Vec2 GOLeftTop = Vec2(GOPos.x - GOScale.x / 2, GOPos.y - GOScale.y / 2);

			Vec2 TileRendersize = GetTargetObject()->TileMap()->GetTileRenderSize();

			for (int row = 0; row < m_faceY; ++row)
			{
				for (int col = 0; col < m_faceX; ++col)
				{
					if (LClickedRelataivePos.x >= GOLeftTop.x + TileRendersize.x * col && LClickedRelataivePos.x < GOLeftTop.x + TileRendersize.x * (col + 1)
						&& LClickedRelataivePos.y >= GOLeftTop.y + TileRendersize.y * row && LClickedRelataivePos.y < GOLeftTop.y + TileRendersize.y * (row + 1))
					{
						int curTileIdxCol = col;
						int curTileIdxRow = row;

						GetTargetObject()->TileMap()->SetTileIndex(curTileIdxRow, curTileIdxCol, gridWidthCnt * curBrushIdxRow + curBrushIdxCol);
						// (gridWidthCnt-1) * curBrushIdxCol + curBrushIdxRow-1
					}
				}
			}
			
			int a = 0;
		}

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
