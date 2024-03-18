#include "pch.h"
#include "Animation2DTool.h"

#include <Engine/CTexture.h>
#include <Engine/CPathMgr.h>
#include <Engine/CAnim.h>

Animation2DTool::Animation2DTool()
	: UI("Animation2DTool", "##Animation2DTool")
	, curAtlasTex(nullptr)
	, curFrameTex(nullptr)
	, gridWidthCnt(1)
	, gridHeightCnt(1)
	, setGrid(false)
	, setClickedRect(false)
	, atlasDiv(1)
{
}

Animation2DTool::~Animation2DTool()
{
}


void Animation2DTool::tick()
{
	int a = 0;
}

void Animation2DTool::render_update()
{
	wstring fileName;

	// 새 애니메이션 추가 NEW 버튼
	if (ImGui::Button("NEW", ImVec2(35, 25)))
	{
		// 파일 탐색기
		wchar_t szFilePath[256] = {};

		OPENFILENAME ofn = {};

		ofn.lStructSize = sizeof(ofn);
		ofn.hwndOwner = nullptr;
		ofn.lpstrFile = szFilePath;
		ofn.lpstrFileTitle = NULL;
		ofn.nMaxFile = sizeof(szFilePath);
		ofn.lpstrFilter = L"ALL\0*.*\0texture\0*.png";
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
		curAtlasTex = CAssetMgr::GetInst()->Load<CTexture>(L"tempTex", L"texture\\" + fileName);
	}

	// Atlas 띄우기
	if (nullptr != curAtlasTex)
	{
		string strPath = string(curAtlasTex->GetRelativePath().begin(), curAtlasTex->GetRelativePath().end());

		realWidth = curAtlasTex->GetWidth();
		realHeight = curAtlasTex->GetHeight();

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

		atlasDiv = realWidth / Width;
		ImGui::Image(curAtlasTex->GetSRV().Get(), ImVec2(Width, Height));

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
			setGrid = true;
		}

		ImGui::Begin("Atlas");
		{
			ImVec2 startPos = ImGui::GetCursorScreenPos(); // 이미지의 시작 위치를 가져온다이
			ImGui::Image(curAtlasTex->GetSRV().Get(), ImVec2(Width, Height));

			if (setGrid)
			{
				ImDrawList* drawList = ImGui::GetWindowDrawList();

				// 수직선 그리기
				for (int x = 0; x <= gridWidthCnt; ++x)
				{
					drawList->AddLine(ImVec2(startPos.x +x * xSize, startPos.y ), ImVec2(startPos.x + x * xSize, startPos.y + Height), IM_COL32(200, 30, 30, 255), 1.5f);
				}

				// 수평선 그리기
				for (int y = 0; y <= gridHeightCnt; ++y)
				{
					drawList->AddLine(ImVec2(startPos.x,startPos.y + y * ySize), ImVec2(startPos.x + Width, startPos.y + y * ySize), IM_COL32(200, 30, 30, 255), 1.5f);
				}

				// 좌클릭 된 칸 -> 색칠하기
				if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
				{
					setClickedRect = true;
					ImVec2 rectLeftTop;
					ImVec2 rectRightBottom;

					tAnimFrm tmpFrm = {};

					ImVec2 mousePos = ImGui::GetMousePos();

					for (int row = 0; row < gridHeightCnt; ++row)
					{
						for (int col = 0; col < gridWidthCnt; ++col)
						{
							if (mousePos.x >= startPos.x + xSize * col && mousePos.x < startPos.x + xSize * (col + 1)
								&& mousePos.y >= startPos.y + ySize * row && mousePos.y < startPos.y + ySize * (row + 1))
							{
								rectLeftTop.x = startPos.x + col * xSize;
								rectLeftTop.y = startPos.y + row * ySize;

								rectRightBottom.x = startPos.x + (col + 1) * xSize;
								rectRightBottom.y = startPos.y + (row + 1) * ySize;

								addRectPos.push_back(rectLeftTop);
								addRectPos.push_back(rectRightBottom);

								

							}
						}
					}

					animFrms.push_back(tmpFrm);
				}

				if (setClickedRect)
				{
					for (int i = 0; i < addRectPos.size(); i += 2)
					{
						drawList->AddRectFilled(addRectPos[i], addRectPos[i+1], IM_COL32(200, 30, 80, 150));
					}
				}
			}

























			//
			//// 애니메이션 Save 과정
			//if (ImGui::Button("Animation Save", ImVec2(100, 25)))
			//{
			//	SaveAnimation2D();
			//}

			ImGui::End();
		}
		
	}





	// 애니메이션 Load 과정
	ImGui::SameLine();
	if (ImGui::Button("Animation Load", ImVec2(110, 25)))
	{
		LoadAnimation2D();
	}
	

}

void Animation2DTool::SaveAnimation2D()
{
	int a = 0;

}

void Animation2DTool::LoadAnimation2D()
{
	int a = 0;
}
