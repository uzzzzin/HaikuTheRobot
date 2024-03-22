#include "pch.h"
#include "TileMapUI.h"

#include <Engine/CEngine.h>

#include <Engine/CTileMap.h>
#include <Engine/CTransform.h>


TileMapUI::TileMapUI()
	: ComponentUI("TileMap", "##TileMap", COMPONENT_TYPE::TILEMAP)
	, bStartBtn (false)
	, bReady (false)
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

	// Ÿ�ϸ� GO�� ��ü ũ�� �����ֱ� : ����, ���� ĭ�� ����, Render�� Ÿ�� ����� !

	ImGui::Text(u8"Ÿ�ϸ� ���� ĭ ���� (FaceX, �⺻ 2)");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(100);
	ImGui::InputInt("##FaceX", &m_faceX, 1, 1, ImGuiInputTextFlags_EnterReturnsTrue);

	ImGui::Text(u8"Ÿ�ϸ� ���� ĭ ���� (FaceY, �⺻ 2)");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(100);
	ImGui::InputInt("##FaceY", &m_faceY, 1, 1, ImGuiInputTextFlags_EnterReturnsTrue);

	ImGui::Text(u8"Ÿ�� X ������ (TileRenderSizeX, �⺻ 128)");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(100);
	ImGui::InputFloat("##TileRenderSizeX", &TileRenderSize.x, ImGuiInputTextFlags_EnterReturnsTrue);

	ImGui::Text(u8"Ÿ�� Y ������ (TileRenderSizeY, �⺻ 128)");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(100);
	ImGui::InputFloat("##TileRenderSizeY", &TileRenderSize.y, ImGuiInputTextFlags_EnterReturnsTrue);

	if (ImGui::Button("TileMap -> SetFace(), SetTileRenderSize()", ImVec2(220, 30)))
	{
		GetTargetObject()->TileMap()->SetTileRenderSize(TileRenderSize);
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

		//if (nullptr == m_curAtlasTex)
		//{
		//	m_curAtlasTex = SetImageForMakeAnim();
		//}

		if ((nullptr == m_curAtlasTex) || (nullptr == GetTargetObject()->TileMap()->GetTileAtlas()))
		{
			m_curAtlasTex = SetImageForMakeAnim();
			/*GetTargetObject()->TileMap()->SetTileAtlas(m_curAtlasTex)*/
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
			GetTargetObject()->TileMap()->SetTileAtlas(m_curAtlasTex, atlasDiv * Vec2(xSize, ySize));
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
				// ���õ� Ÿ�� -> ��Ʋ�� ���� �ε����� �̾ƿͼ� -> setTileIndex()

				//int curBrushIdxCol; // x
				//int curBrushIdxRow; // y

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

							////����° ����
							//gridWidthCnt* col + row;

							//// ù��°, �ι�° ���� => ȭ�鿡 Ŭ���� Ÿ���� ��ġ �ε���. Face �³��� �ε��� ���ϴ� ���� ����
							////GetTargetObject()->TileMap()->SetTileIndex(gridWidthCnt, gridHeightCnt, gridWidthCnt * 6 + j);
						}
					}
				}
			}
		}

		if (bReady) // ��ĥ �� �غ� �Ϸ�Ǿ��ٸ�. (�귯���� �����ؼ� ��� �ִٸ�.)
		{
			// ȭ�鿡 ������..

			////����° ����
			//gridWidthCnt* col + row;

			//// ù��°, �ι�° ���� => ȭ�鿡 Ŭ���� Ÿ���� ��ġ �ε���. Face �³��� �ε��� ���ϴ� ���� ����
			////GetTargetObject()->TileMap()->SetTileIndex(gridWidthCnt, gridHeightCnt, gridWidthCnt * 6 + j);

			// �� ���콺 Pos(�� screenPos)�� Ÿ�ϸ� GO�� ���� Pos�� ����

			if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
			{
				ImVec2 mousePos = ImGui::GetMousePos(); // �� ScreenPos��
				/*POINT pt = {};
				GetCursorPos(&pt);
				ScreenToClient(CEngine::GetInst()->GetMainWind(), &pt);
				Vec2 RelativeMousePos = Vec2((float)pt.x, (float)pt.y);*/
				Vec3 v1 = GetTargetObject()->Transform()->GetRelativePos();
				Vec3 v2 = GetTargetObject()->Transform()->GetWorldPos();

				
				//float tmpX = (2.0f * mousePos.x / screenWidth - 1.0f);
				//float tmpY = (1.0f - 2.0f * screenY / screenHeight);



				int a = 0;




				//Vec3 mouseRelativePos = ToRelativePos(DirectX::XMFLOAT3(mousePos.x, mousePos.y, 0));

				//  �ϴ� TileMap GO�� �ȿ� �����ִ��� ���

				// TileMap ������Ʈ�� Ŭ���� ���̶��, �� �� LeftTop �������� �ε��� ���

				// �˾Ƴ� �ε��� ---> GO TileMap�� SetTileIndex() ����.
			}

		}





		

		ImGui::End(); // TileMap �� ���� Begin/End

		// =============================================================================
	}

}

Vec3 ToRelativePos(Vec3 _curWindowPos)
{

	
	return Vec3();
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
