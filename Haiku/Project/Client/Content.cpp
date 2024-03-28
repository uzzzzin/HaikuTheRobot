#include "pch.h"
#include "Content.h"

#include <Engine/CAssetMgr.h>
#include <Engine/CTaskMgr.h>

#include "CImGuiMgr.h"
#include "Inspector.h"
#include "TreeUI.h"

Content::Content()
	: UI("Content", "##Content")
{
	// ContentUI �ڽ����� Tree �� ����
	m_Tree = new TreeUI("ContentTree");
	m_Tree->ShowRootNode(false);
	AddChildUI(m_Tree);
	
	// AssetMgr �� ���»��¸� Ʈ���� �����Ѵ�.
	ResetContent();

	// Ʈ���� Delegate �� ����Ѵ�.
	m_Tree->AddSelectDelegate(this, (Delegate_1)&Content::SelectAsset);

	// ������ ������ �ִ� ������ �ε��Ѵ�.
	ReloadContent();
}

Content::~Content()
{
}

void Content::render_update()
{
	if (CTaskMgr::GetInst()->GetAssetEvent())
	{
		ResetContent();
	}
}




void Content::ResetContent()
{
	// Tree Clear
	m_Tree->ClearNode();

	// ��Ʈ��� �߰�
	TreeNode* RootNode = m_Tree->AddTreeNode(nullptr, "Root", 0);

	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		TreeNode* CategoryNode = m_Tree->AddTreeNode(RootNode, ASSET_TYPE_STRING[i], 0);
		CategoryNode->SetFrame(true);

		const map<wstring, Ptr<CAsset>>& mapAsset = CAssetMgr::GetInst()->GetAssets((ASSET_TYPE)i);
		
		for (const auto& pair : mapAsset)
		{
			m_Tree->AddTreeNode(CategoryNode
				, string(pair.first.begin(), pair.first.end())
				, (DWORD_PTR)pair.second.Get());
		}
	}
}

void Content::SelectAsset(DWORD_PTR _Node)
{
	TreeNode* pNode = (TreeNode*)_Node;

	if (nullptr == pNode)
		return;
	
	Ptr<CAsset> pAsset = (CAsset*)pNode->GetData();
	if (nullptr == pAsset)
		return;

	// ������ ������ Inspector ���� �˷��ش�.
	Inspector* pInspector = (Inspector*)CImGuiMgr::GetInst()->FindUI("##Inspector");
	pInspector->SetTargetAsset(pAsset);
}


void Content::ReloadContent()
{
	// Content ������ �ִ� ��� ���� ���ϸ�(�����)�� ã�Ƴ���.
	wstring strContentPath = CPathMgr::GetContentPath();
	FindFileName(strContentPath);

	// ã�� �����̸����� ���µ��� �ε�
	for (size_t i = 0; i < m_vecAssetFileName.size(); ++i)
	{
		ASSET_TYPE Type = GetAssetTypeByExt(m_vecAssetFileName[i]);

		switch (Type)
		{
		case ASSET_TYPE::END:
		default:
			continue;
			break;
		case ASSET_TYPE::MESH:
			CAssetMgr::GetInst()->Load<CMesh>(m_vecAssetFileName[i], m_vecAssetFileName[i]);
			break;
		case ASSET_TYPE::MESHDATA:
			//CAssetMgr::GetInst()->Load<CMeshData>(m_vecAssetFileName[i], m_vecAssetFileName[i]);
			break;
		case ASSET_TYPE::PREFAB:
			CAssetMgr::GetInst()->Load<CPrefab>(m_vecAssetFileName[i], m_vecAssetFileName[i]);
			break;
		case ASSET_TYPE::TEXTURE:
			CAssetMgr::GetInst()->Load<CTexture>(m_vecAssetFileName[i], m_vecAssetFileName[i]);
			break;
		case ASSET_TYPE::MATERIAL:
			CAssetMgr::GetInst()->Load<CMaterial>(m_vecAssetFileName[i], m_vecAssetFileName[i]);
			break;
		case ASSET_TYPE::SOUND:
			CAssetMgr::GetInst()->Load<CSound>(m_vecAssetFileName[i], m_vecAssetFileName[i]);
			break;
		case ASSET_TYPE::FSM:
			CAssetMgr::GetInst()->Load<CFSM>(m_vecAssetFileName[i], m_vecAssetFileName[i]);
		}		
	}

	// ������ ������ ������, AssetMgr ������ �޸� ���� 
	for (UINT i = 0; i < (UINT)ASSET_TYPE::END; ++i)
	{
		const map<wstring, Ptr<CAsset>>& mapAsset = CAssetMgr::GetInst()->GetAssets((ASSET_TYPE)i);

		for (const auto& pair : mapAsset)
		{
			// ���� ������ ��� continue 
			// ���� ������ ���Ϸκ��� �ε��� ������ �ƴ϶�, ���α׷� ���� ���� ������� ���µ��̱� ����
			if (pair.second->IsEngineAsset())
				continue;

			// �޸𸮿� �ε��� ������ ����������, content ���� ������ ������ ���
			// ���� �ε��Ǿ��ִ� ���µ� �������Ѽ� sync �� �����.
			wstring strFilePath = strContentPath + pair.second->GetRelativePath();			
			if (!exists(strFilePath))
			{
				MessageBox(nullptr, L"���������� �����Ǿ����ϴ�.", L"Asset ��ũ", MB_OK);

				if (1 < pair.second->GetRefCount())
				{
					int value = MessageBox(nullptr, L"Asset �� �����ǰ� �ֽ��ϴ�.\n���� �����Ͻðڽ��ϱ�?", L"Asset ��ũ", MB_YESNO);
					if (value == IDCANCEL)
						continue;
				}

				// ���� �Ŵ������� �ش� ������ �����Ѵ�.
				tTask task = {};
				task.Type = TASK_TYPE::DELETE_ASSET;
				task.Param_1 = (DWORD_PTR)i;
				task.Param_2 = (DWORD_PTR)pair.second.Get();
				CTaskMgr::GetInst()->AddTask(task);
			}
		}
	}


	ResetContent();
}


void Content::FindFileName(const wstring& _Directory)
{
	// ���� Ž�� ��� ����
	WIN32_FIND_DATA FIND_DATA = {};
	
	// Ž���� �õ��� ���͸� ��� + ã�� ���� Ÿ�� ����
	wstring strDirectory = _Directory + L"*.*";

	// Ž�� �ڵ� ����
	HANDLE hFindHandle = FindFirstFile(strDirectory.c_str(), &FIND_DATA);

	if (INVALID_HANDLE_VALUE == hFindHandle)		
		return;
		
	// Ž�� �ڵ��� �̿��ؼ�, ������ ���� ������ Ž��, ���̻� ������ false ��ȯ
	while (FindNextFile(hFindHandle, &FIND_DATA))
	{	
		// ã�� ������ Directory Ÿ������ Ȯ��
		if (FIND_DATA.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			// .. �̸��� ������ �θ������� ���� ���
			if (!wcscmp(L"..", FIND_DATA.cFileName))
				continue;

			// ����Լ��� ���� �������� �ִ� �����̸��� Ž��
			FindFileName(_Directory + FIND_DATA.cFileName + L"\\");
		}
		else
		{
			// ���� Ÿ���� ���, ���͸����� �ٿ��� ���� ��θ� �����, ����θ� �����ؼ� m_vecAssetFileName �� ����
			wstring strRelativePath = CPathMgr::GetRelativePath(_Directory + FIND_DATA.cFileName);
			m_vecAssetFileName.push_back(strRelativePath);
		}
	}

	FindClose(hFindHandle);
}

ASSET_TYPE Content::GetAssetTypeByExt(const path& _relativePath)
{
	if (_relativePath.extension() == L".mesh")
		return ASSET_TYPE::MESH;
	if (_relativePath.extension() == L".mtrl")
		return ASSET_TYPE::MATERIAL;
	if (_relativePath.extension() == L".mdat")
		return ASSET_TYPE::MESHDATA;
	if (_relativePath.extension() == L".pref")
		return ASSET_TYPE::PREFAB;

	if (_relativePath.extension() == L".png" 
		|| _relativePath.extension() == L".bmp"
		|| _relativePath.extension() == L".jpg"
		|| _relativePath.extension() == L".jpeg"
		|| _relativePath.extension() == L".dds"
		|| _relativePath.extension() == L".tga")
		return ASSET_TYPE::TEXTURE;

	if (_relativePath.extension() == L".wav"
		|| _relativePath.extension() == L".mp3"
		|| _relativePath.extension() == L".ogg")
		return ASSET_TYPE::SOUND;

	if (_relativePath.extension() == L".mesh")
		return ASSET_TYPE::MESH;
	if (_relativePath.extension() == L".mesh")
		return ASSET_TYPE::MESH;

	if (_relativePath.extension() == L".fsm")
		return ASSET_TYPE::FSM;


	return ASSET_TYPE::END;
}
