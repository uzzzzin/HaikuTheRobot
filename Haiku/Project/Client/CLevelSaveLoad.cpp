#include "pch.h"
#include "CLevelSaveLoad.h"

#include <Engine/CPathMgr.h>
#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>
#include <Engine/CLayer.h>
#include <Engine/CGameObject.h>
#include <Engine/components.h>
#include <Engine/CAssetMgr.h>

#include <Scripts/CScriptMgr.h>
#include <Engine/CScript.h>


void CLevelSaveLoad::SaveLevel(CLevel* _Level, const wstring& _strLevelPath)
{
	assert(_Level);
	assert(LEVEL_STATE::STOP == _Level->GetState() || LEVEL_STATE::NONE == _Level->GetState());

	// Level �� ������ ���
	wstring strLevelPath = CPathMgr::GetContentPath();
	strLevelPath += _strLevelPath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strLevelPath.c_str(), L"wb");

	// ������ �̸�
	SaveWString(_Level->GetName(), pFile);

	// ������ ���̾� ����
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		SaveLayer(_Level->GetLayer(i), pFile);
	}

	fclose(pFile);
}

void CLevelSaveLoad::SaveLayer(CLayer* _Layer, FILE* _File)
{
	// Layer �� �̸� ����
	SaveWString(_Layer->GetName(), _File);

	// Layer �� �����ϰ� �ִ� GameObject ���� ����
	const vector<CGameObject*>& vecObject = _Layer->GetParentObjects();

	size_t ObjCount = vecObject.size();
	fwrite(&ObjCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < vecObject.size(); ++i)
	{
		SaveGameObject(vecObject[i], _File);
	}	
}

void CLevelSaveLoad::SaveGameObject(CGameObject* _Obj, FILE* _File)
{
	// GameObject �� �̸��� ����
	SaveWString(_Obj->GetName(), _File);
	
	// ������Ʈ ������ ����
	UINT i = 0;
	for ( ; i < (UINT)COMPONENT_TYPE::END; ++i)
	{
		CComponent* pCom = _Obj->GetComponent((COMPONENT_TYPE)i);
		if (nullptr == pCom)
			continue;

		// ������Ʈ Ÿ�� ���� ����
		fwrite(&i, sizeof(UINT), 1, _File);

		// �ش� ������Ʈ�� ������ ������ ����
		pCom->SaveToFile(_File);
	}
	fwrite(&i, sizeof(UINT), 1, _File);

	// ��ũ��Ʈ ���� ����
	const vector<CScript*>& vecScripts = _Obj->GetScripts();
	size_t ScriptCount = vecScripts.size();

	// ��ũ��Ʈ ���� ����
	fwrite(&ScriptCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < vecScripts.size(); ++i)
	{
		SaveWString(CScriptMgr::GetScriptName(vecScripts[i]), _File);
		vecScripts[i]->SaveToFile(_File);
	}

	// �ڽ� ������Ʈ�� ������ �ڽ� ������Ʈ ���� ����
	const vector<CGameObject*>& vecChild = _Obj->GetChild();
	size_t childcount = vecChild.size();
	fwrite(&childcount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < childcount; ++i)
	{
		SaveGameObject(vecChild[i], _File);
	}
}

CLevel* CLevelSaveLoad::LoadLevel(const wstring& _strLevelPath)
{
	CLevel* pLevel = nullptr;

	// Level �� �ҷ��� ���
	wstring strLevelPath = CPathMgr::GetContentPath();
	strLevelPath += _strLevelPath;

	if (!exists(strLevelPath))
	{
		MessageBox(nullptr, L"���� ��ΰ� �ùٸ��� �ʰų�, ������ ����", L"���� �ε� ����", MB_OK);
		return nullptr;
	}

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strLevelPath.c_str(), L"rb");
			

	// ������ �̸��� �д´�.
	pLevel = new CLevel;
	wstring strLevelName;
	LoadWString(strLevelName, pFile);
	pLevel->SetName(strLevelName);

	// Layer �ε�
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		LoadLayer(pLevel->GetLayer(i), pFile);		
	}

	fclose(pFile);

	return pLevel;
}

void CLevelSaveLoad::LoadLayer(CLayer* _Layer, FILE* _File)
{
	// Layer �� �̸� ����
	wstring strLayerName;
	LoadWString(strLayerName, _File);
	_Layer->SetName(strLayerName);


	// Layer �� �����ϴ� GameObject ���� �ҷ��´�.
	size_t ObjCount = 0;
	fread(&ObjCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < ObjCount; ++i)
	{
		CGameObject* pObject = LoadGameObject(_File);
		_Layer->AddObject(pObject, false);
	}
}

CGameObject* CLevelSaveLoad::LoadGameObject(FILE* _File)
{
	CGameObject* pObject = new CGameObject;
	
	// GameObject �� �̸��� �ε�
	wstring strName;
	LoadWString(strName, _File);
	pObject->SetName(strName);

	// ������Ʈ ������ �ҷ�����
	COMPONENT_TYPE type = COMPONENT_TYPE::END;
	while(true)
	{
		fread(&type, sizeof(UINT), 1, _File);
		if (COMPONENT_TYPE::END == type)
			break;

		CComponent* pComponent = nullptr;

		switch (type)
		{
		case COMPONENT_TYPE::TRANSFORM:
			pComponent = new CTransform;
			break;
		case COMPONENT_TYPE::COLLIDER2D:
			pComponent = new CCollider2D;
			break;				
		case COMPONENT_TYPE::ANIMATOR2D:
			pComponent = new CAnimator2D;
			break;		
		case COMPONENT_TYPE::LIGHT2D:
			pComponent = new CLight2D;
			break;		
		case COMPONENT_TYPE::CAMERA:
			pComponent = new CCamera;
			break;
		case COMPONENT_TYPE::STATEMACHINE:
			pComponent = new CStateMachine;
			break;
		case COMPONENT_TYPE::MESHRENDER:
			pComponent = new CMeshRender;
			break;
		case COMPONENT_TYPE::TILEMAP:
			pComponent = new CTileMap;
			break;
		case COMPONENT_TYPE::PARTICLESYSTEM:
			pComponent = new CParticleSystem;
			break;
		default:
			assert(nullptr);
			break;
		}

		// �ش� ������Ʈ�� ������ �����͸� �ε�
		pObject->AddComponent(pComponent);
		pComponent->LoadFromFile(_File);
	}

	// ��ũ��Ʈ ���� �б�
	size_t ScriptCount = 0;
	fread(&ScriptCount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < ScriptCount; ++i)
	{
		wstring strScriptName;
		LoadWString(strScriptName, _File);		

		CScript* pScript = CScriptMgr::GetScript(strScriptName);
		pObject->AddComponent(pScript);
		pScript->LoadFromFile(_File);
	}

	// �ڽ� ������Ʈ�� ������ �ڽ� ������Ʈ ���� ����	
	size_t childcount = 0;
	fread(&childcount, sizeof(size_t), 1, _File);

	for (size_t i = 0; i < childcount; ++i)
	{
		pObject->AddChild(LoadGameObject(_File));
	}

	return pObject;
}
