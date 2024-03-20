#include "pch.h"
#include "Animator2DUI.h"

#include <Shobjidl.h>
#include <iostream>

#include <Engine/CAnimator2D.h>

Vec2 LoadMeta(const wstring& _strMetaRelativePath);
void openFileDialog(vector<wstring>& _FilesName);

Animator2DUI::Animator2DUI()
	: ComponentUI("Animator2D", "##Animator2D", COMPONENT_TYPE::ANIMATOR2D)
	, makeAnimStart(false)
	, bPushback (true)
	, curAnimRepeat (true)
	, bAtlasMakeStart (false)
{
	SetSize(ImVec2(0.f, 300.f));
	SetComopnentTitle("Animator2D");

	//m_mapList = new ListUI();
	//AddChildUI(m_mapList);
}

Animator2DUI::~Animator2DUI()
{
}


void Animator2DUI::SetMapAnims(map<wstring, class CAnim*> _map)
{
	if (_map == m_MapAnims)
		return;

	m_MapAnims.clear();
	m_Keys.clear();

	if (nullptr == GetTargetObject())
	{
		return;
	}

	m_MapAnims = _map; 

	for (auto iter = m_MapAnims.begin(); iter != m_MapAnims.end(); ++iter)
	{
		m_Keys.push_back((ToString(iter->first)));
	}
}

void Animator2DUI::render_update()
{
	if (nullptr == GetTargetObject())
		return;

	ComponentUI::render_update();

	static tAnimFrm tmpFrm = {};

	ImGui::Text(u8"Anim List *����* Anim ������ �� ����Ŭ���ϰ� ��������.");
	static int item_current_idx = 0;
	if (ImGui::BeginListBox("##ListBox"))
	{
		SetMapAnims(GetTargetObject()->Animator2D()->GetMapAnims());
		
		for (int i = 0; i < m_Keys.size(); ++i)
		{
			const bool is_selected = (item_current_idx == i);
			if (ImGui::Selectable(m_Keys[i].c_str(), is_selected))
				item_current_idx = i;

			if (is_selected)
				ImGui::SetItemDefaultFocus();

			if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(ImGuiMouseButton_Left))
			{
				m_selectedKey = m_Keys[i].c_str();
				//bPreviewBegin = true;
				//CAnim* tempAnim = (CAnim*)GetTargetObject()->Animator2D()->FindAnim(ToWString(m_Keys[i]));
				//ImGui::Begin();
				// ���� ���� �߰�
			}
		}
		ImGui::EndListBox();
	}

	if (ImGui::Button(u8"Anim ���� �� �߰�", ImVec2(120, 25)))
	{
		m_curAtlasTex = SetImageForMakeAnim();
		ImGui::SetNextWindowSize(ImVec2(900, 900));
	}
	ImGui::SameLine();
	if (ImGui::Button(u8"Anim ����", ImVec2(70, 25)))
	{
		auto iter = std::find(m_Keys.begin(), m_Keys.end(), m_selectedKey);
		m_Keys.erase(iter);
		GetTargetObject()->Animator2D()->AnimDelete(ToWString(m_selectedKey));
	}


	if (nullptr != m_curAtlasTex)
	{
		realWidth = m_curAtlasTex->GetWidth();
		realHeight = m_curAtlasTex->GetHeight();

		float Width = realWidth;
		float Height = realHeight;
		ImGui::Begin(u8"Anim �����ϱ�", &s,ImGuiWindowFlags_NoMove);
		ImGui::SameLine();
		string strPath = string(m_curAtlasTex->GetRelativePath().begin(), m_curAtlasTex->GetRelativePath().end());

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

		ImVec2 startPos = ImGui::GetCursorScreenPos(); // �̹����� ���� ��ġ�� �����´���
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
			setGrid = true;
		}

		if (setGrid)
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

			// ��Ŭ�� �� ĭ -> ��ĥ�ϱ�
			if (ImGui::IsMouseClicked(ImGuiMouseButton_Left))
			{
				setClickedRect = true;
				ImVec2 rectLeftTop;
				ImVec2 rectRightBottom;

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
			}

			for (int i = 0; i < addRectPos.size(); i += 2)
			{
				drawList->AddRectFilled(addRectPos[i], addRectPos[i + 1], IM_COL32(200, 30, 80, 150));
			}

			if (setClickedRect) // ��� ��ĥ�ϰڴٴ� �ǵ�
			{
				static int k = 0;
				for (int i = k; i < addRectPos.size(); i += 2)
				{
					//static tAnimFrm tmpFrm = {};

					//tmpFrm.vLeftTop = atlasDiv * Vec2(DirectX::XMFLOAT2(addRectPos[i].x, addRectPos[i].y));
					ImVec2 tmpLeftTop = ImVec2(addRectPos[i].x- startPos.x, addRectPos[i].y- startPos.y);
					
					tmpFrm.vLeftTop = atlasDiv * Vec2(DirectX::XMFLOAT2(tmpLeftTop.x, tmpLeftTop.y));

					ImVec2 tmpSlice = addRectPos[i + 1] - addRectPos[i];
					tmpFrm.vSlice = atlasDiv * Vec2(DirectX::XMFLOAT2(tmpSlice.x, tmpSlice.y));

					tmpFrm.vOffset = Vec2(0, 0);

					tmpFrm.vBackground = tmpFrm.vSlice;


					tmpFrm.Duration = 1 / 20.f;

					animFrms.push_back(tmpFrm);

					k += 2;
					setClickedRect = false;
				}
			}
		}

		ImGui::SameLine();
		ImGui::Text("Anim Repeat->");
		ImGui::SameLine();
		ImGui::Checkbox("##AnimRepeat", &curAnimRepeat);
		ImGui::SameLine();
		ImGui::Text("Anim Key :");
		static char textBuffer[256] = "";
		ImGui::InputText("##AnimKey", textBuffer, IM_ARRAYSIZE(textBuffer));

		// ----------------------------------------------------------

		static float tmpFPS = 10.f;
		ImGui::Text("Duration Setting");
		ImGui::SameLine();
		ImGui::InputFloat("##Duration", &tmpFPS);

		for (int i = 0; i < animFrms.size(); ++i)
		{
			animFrms[i].Duration = 1 / tmpFPS;
		}

		// ----------------------------------------------------------

		if (ImGui::Button("offset setting"))
		{
			vector<wstring> wvec;
			openFileDialog(wvec);

			vector<Vec2> TmpOffset;
			for (int i = 0; i < wvec.size(); ++i)
			{
				TmpOffset.push_back(LoadMeta(wvec[i]));
			}

			if (TmpOffset.size() != animFrms.size())
			{
				MessageBoxA(nullptr, "��Ÿ������ ������ ���õ� �׸����� ������ ���� �ʽ��ϴ�", "Offset Load Error", MB_OK);
			}
			else
			{
				for (int i = 0; i < TmpOffset.size(); ++i)
				{
					animFrms[i].vOffset = TmpOffset[i];
				}
				//�����ӿ� ���� �ֱ�

			}

		}

		// Anim ����, ���� �ܰ�
		if (ImGui::Button(u8"Anim ���� �� ����"))
		{
			if (0 == animFrms.size())
				return;

			string str(textBuffer);
			m_Keys.push_back(str);
			wstring tmpKey = ToWString(str);

			CAnim* pAnim = GetTargetObject()->Animator2D()->FindAnim(tmpKey);
			assert(!pAnim);

			pAnim = new CAnim;
			pAnim->SetAtlasTex(m_curAtlasTex);
			pAnim->SetAnimator(GetTargetObject()->Animator2D());

			//pAnim->SetAnimFrm(animFrms);

			GetTargetObject()->Animator2D()->Create(tmpKey, m_curAtlasTex, animFrms);

			m_curAtlasTex = nullptr;
		}


		ImGui::End(); // ��Ʋ�� ����â �ݴ�

	}


}

Ptr<CTexture> Animator2DUI::SetImageForMakeAnim()
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


void Animator2DUI::MakeAnim()
{
}

void openFileDialog(vector<wstring>& _FilesName)
{

	IFileOpenDialog* pFileDialog;
	HRESULT hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL, IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileDialog));
	if (FAILED(hr)) {
		std::cerr << "Failed to create FileOpenDialog instance" << std::endl;
		return;
	}

	// ���� ���� ���� ����
	DWORD dwOptions;
	hr = pFileDialog->GetOptions(&dwOptions);
	if (SUCCEEDED(hr)) {
		hr = pFileDialog->SetOptions(dwOptions | FOS_ALLOWMULTISELECT);
	}

	// ���� ���� ����
	COMDLG_FILTERSPEC fileTypes[] = { { L"All Files", L"*.*" }, { L"Text Files", L"*.txt" }, { L"FBX Files", L"*.fbx" } };
	hr = pFileDialog->SetFileTypes(ARRAYSIZE(fileTypes), fileTypes);
	if (FAILED(hr)) {
		std::cerr << "Failed to set file types" << std::endl;
		pFileDialog->Release();
		return;
	}

	// ��ȭ ���� ����
	hr = pFileDialog->Show(NULL);
	if (FAILED(hr)) {
		std::cerr << "Failed to open FileOpenDialog" << std::endl;
		pFileDialog->Release();
		return;
	}

	// ���õ� ���� ��� ��������
	IShellItemArray* pItems;
	hr = pFileDialog->GetResults(&pItems);
	if (FAILED(hr)) {
		std::cerr << "Failed to get selected items" << std::endl;
		pFileDialog->Release();
		return;
	}

	// ���õ� ���ϵ��� ��� ��������
	DWORD itemCount;
	hr = pItems->GetCount(&itemCount);
	if (SUCCEEDED(hr)) {
		for (DWORD i = 0; i < itemCount; ++i) {
			IShellItem* pItem;
			hr = pItems->GetItemAt(i, &pItem);
			if (SUCCEEDED(hr)) {
				PWSTR pszFilePath;
				hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);
				if (SUCCEEDED(hr)) {
					_FilesName.push_back(pszFilePath);
					CoTaskMemFree(pszFilePath);
				}
				pItem->Release();
			}
		}
	}
	pItems->Release();
	pFileDialog->Release();
}

Vec2 LoadMeta(const wstring& _strMetaRelativePath)
{
	Vec2 retVec = { -1,-1 };

	FILE* pFile = nullptr;

	_wfopen_s(&pFile, _strMetaRelativePath.c_str(), L"r");

	if (nullptr == pFile)
	{
		MessageBoxA(nullptr, "Meta ������ �������� �ʽ��ϴ�.", "Meta File No Exist!", MB_OK);
		return {};
	}

	// Animation �̸� �ε�

	while (true)
	{
		wchar_t szRead[256] = {};
		float tmpfloat = -1.f;

		if (EOF == fwscanf_s(pFile, L"%s", szRead, 256))
		{
			break;
		}


		if (!wcscmp(szRead, L"m_Offset:"))
		{
			while (true)
			{
				fwscanf_s(pFile, L"%s", szRead, 256);

				if (!wcscmp(szRead, L"{x:"))
				{
					fwscanf_s(pFile, L"%f", &retVec.x);

				}
				if (!wcscmp(szRead, L"y:"))
				{
					fwscanf_s(pFile, L"%s", szRead, 256);

					int length = (int)wcslen(szRead);

					// ���� �ѱ��� �߶�ߵ� 1.24} ��� �Ǿ�����
					if (length > 0) {
						szRead[length - 1] = '\0';
					}

					wchar_t* end;
					float tmp = wcstof(szRead, &end);

					if (*end == L'\0') {
						retVec.y = tmp;
					}

					return retVec;
				}

				// Ż�� ����
				if (!wcscmp(szRead, L"m_Border:"))
				{
					break;
				}
			}

		}
		// Ż�� ����
		if (!wcscmp(szRead, L"m_Border:"))
			break;

	}



	fclose(pFile);

	return retVec;
}