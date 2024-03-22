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

	// 타일맵 GO의 전체 크기 정해주기 : 가로, 세로 칸수 지정, Render할 타일 사이즈도 !

	ImGui::Text(u8"타일맵 가로 칸 개수 (FaceX, 기본 2)");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(100);
	ImGui::InputInt("##FaceX", &m_faceX, 1, 1, ImGuiInputTextFlags_EnterReturnsTrue);

	ImGui::Text(u8"타일맵 세로 칸 개수 (FaceY, 기본 2)");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(100);
	ImGui::InputInt("##FaceY", &m_faceY, 1, 1, ImGuiInputTextFlags_EnterReturnsTrue);

	ImGui::Text(u8"타일 X 사이즈 (TileRenderSizeX, 기본 128)");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(100);
	ImGui::InputFloat("##TileRenderSizeX", &TileRenderSize.x, ImGuiInputTextFlags_EnterReturnsTrue);

	ImGui::Text(u8"타일 Y 사이즈 (TileRenderSizeY, 기본 128)");
	ImGui::SameLine();
	ImGui::SetNextItemWidth(100);
	ImGui::InputFloat("##TileRenderSizeY", &TileRenderSize.y, ImGuiInputTextFlags_EnterReturnsTrue);

	if (ImGui::Button("TileMap -> SetFace(), SetTileRenderSize()", ImVec2(220, 30)))
	{
		GetTargetObject()->TileMap()->SetTileRenderSize(TileRenderSize);
		GetTargetObject()->TileMap()->SetFace(m_faceX, m_faceY);
	}

	// =============================================================================

	if (ImGui::Button(u8"TileMap 에서 쓰일 아틀라스 세팅하기", ImVec2(220, 30)))
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

		ImVec2 startPos = ImGui::GetCursorScreenPos(); // 이미지의 시작 위치
		ImGui::Image(m_curAtlasTex->GetSRV().Get(), ImVec2(Width, Height));

		// x 가르기, 열
		ImGui::Text("grid Width cnt (X)");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		ImGui::InputInt("##그리드 열 개수", &gridWidthCnt, 1, 1, ImGuiInputTextFlags_EnterReturnsTrue);
		float xSize = Width / gridWidthCnt;
		ImGui::SameLine();
		ImGui::Text("X size ");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		ImGui::InputFloat("##열 사이즈", &xSize, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);

		// y 가르기, 행
		ImGui::Text("grid Height cnt (Y)");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		ImGui::InputInt("##그리드 행 개수", &gridHeightCnt, 1, 1, ImGuiInputTextFlags_EnterReturnsTrue);
		float ySize = Height / gridHeightCnt;
		ImGui::SameLine();
		ImGui::Text("Y size ");
		ImGui::SameLine();
		ImGui::SetNextItemWidth(100);
		ImGui::InputFloat("##열 사이즈", &ySize, 0.f, 0.f, "%.3f", ImGuiInputTextFlags_ReadOnly);

		if (ImGui::Button("Create Grid", ImVec2(90, 25)))
		{
			bSetGrid = true;
			GetTargetObject()->TileMap()->SetTileAtlas(m_curAtlasTex, atlasDiv * Vec2(xSize, ySize));
			GetTargetObject()->TileMap()->SetFace(m_faceX, m_faceY);
		}

		if (bSetGrid)
		{
			ImDrawList* drawList = ImGui::GetWindowDrawList();

			// 수직선 그리기
			for (int x = 0; x <= gridWidthCnt; ++x)
			{
				drawList->AddLine(ImVec2(startPos.x + x * xSize, startPos.y), ImVec2(startPos.x + x * xSize, startPos.y + Height), IM_COL32(200, 30, 30, 255), 1.5f);
			}

			// 수평선 그리기
			for (int y = 0; y <= gridHeightCnt; ++y)
			{
				drawList->AddLine(ImVec2(startPos.x, startPos.y + y * ySize), ImVec2(startPos.x + Width, startPos.y + y * ySize), IM_COL32(200, 30, 30, 255), 1.5f);
			}

			// 좌클릭 된 칸은 팔레트에서 선택된 타일. 현재 브러쉬인거지
			if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
			{
				ImVec2 mousePos = ImGui::GetMousePos();
				// 선택된 타일 -> 아틀라스 기준 인덱스를 뽑아와서 -> setTileIndex()

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

							////세번째 인자
							//gridWidthCnt* col + row;

							//// 첫번째, 두번째 인자 => 화면에 클릭한 타일의 위치 인덱스. Face 걔네의 인덱스 말하는 거임 ㅇㅇ
							////GetTargetObject()->TileMap()->SetTileIndex(gridWidthCnt, gridHeightCnt, gridWidthCnt * 6 + j);
						}
					}
				}
			}
		}

		if (bReady) // 색칠 할 준비가 완료되었다면. (브러쉬를 선택해서 들고 있다면.)
		{
			// 화면에 찍어야지..

			////세번째 인자
			//gridWidthCnt* col + row;

			//// 첫번째, 두번째 인자 => 화면에 클릭한 타일의 위치 인덱스. Face 걔네의 인덱스 말하는 거임 ㅇㅇ
			////GetTargetObject()->TileMap()->SetTileIndex(gridWidthCnt, gridHeightCnt, gridWidthCnt * 6 + j);

			// 내 마우스 Pos(얜 screenPos)와 타일맵 GO의 현재 Pos의 차이

			if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
			{
				ImVec2 mousePos = ImGui::GetMousePos(); // 얘 ScreenPos네
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

				//  일단 TileMap GO의 안에 들어와있는지 계산

				// TileMap 오브젝트를 클릭한 것이라면, 그 후 LeftTop 기준으로 인덱스 계산

				// 알아낸 인덱스 ---> GO TileMap의 SetTileIndex() 진행.
			}

		}





		

		ImGui::End(); // TileMap 툴 시작 Begin/End

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

	// 파일 탐색기
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
