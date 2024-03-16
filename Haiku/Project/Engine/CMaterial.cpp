#include "pch.h"
#include "CMaterial.h"

#include "CGraphicsShader.h"

#include "CDevice.h"
#include "CConstBuffer.h"
#include "CTexture.h"

#include "CPathMgr.h"

#include "Ptr.h"

CMaterial::CMaterial(bool _bEngine)
	: CAsset(ASSET_TYPE::MATERIAL, _bEngine)
	, m_Const{}
{
}

CMaterial::~CMaterial()
{
}


void CMaterial::UpdateData()
{	
	if (nullptr == m_pShader.Get())
		return;
	
	// ����� ���̴� ���ε�
	m_pShader->UpdateData();	

	// Texture Update(Register Binding)
	for (UINT i = 0; i < (UINT)TEX_PARAM::END; ++i)
	{
		if (nullptr != m_arrTex[i].Get())
		{
			m_arrTex[i]->UpdateData(i);
			m_Const.bTex[i] = 1;
		}
		else
		{
			CTexture::Clear(i);
			m_Const.bTex[i] = 0;
		}
	}

	// ��� ������ ������Ʈ
	static CConstBuffer* pCB = CDevice::GetInst()->GetConstBuffer(CB_TYPE::MATERIAL_CONST);
	pCB->SetData(&m_Const);
	pCB->UpdateData();	
}

void CMaterial::SetTexParam(TEX_PARAM _Param, Ptr<CTexture>_pTex)
{
	m_arrTex[(UINT)_Param] = _pTex;
}

void* CMaterial::GetScalarParam(SCALAR_PARAM _ParamType)
{
	switch (_ParamType)
	{
	case SCALAR_PARAM::INT_0:
	case SCALAR_PARAM::INT_1:
	case SCALAR_PARAM::INT_2:
	case SCALAR_PARAM::INT_3:
	{
		int idx = (UINT)_ParamType - (UINT)SCALAR_PARAM::INT_0;
		return m_Const.iArr + idx;
	}
		break;
	case SCALAR_PARAM::FLOAT_0:
	case SCALAR_PARAM::FLOAT_1:
	case SCALAR_PARAM::FLOAT_2:
	case SCALAR_PARAM::FLOAT_3:
	{
		int idx = (UINT)_ParamType - (UINT)SCALAR_PARAM::FLOAT_0;
		return m_Const.fArr + idx;
	}
		break;
	case SCALAR_PARAM::VEC2_0:
	case SCALAR_PARAM::VEC2_1:
	case SCALAR_PARAM::VEC2_2:
	case SCALAR_PARAM::VEC2_3:
	{
		int idx = (UINT)_ParamType - (UINT)SCALAR_PARAM::VEC2_0;
		return m_Const.v2Arr + idx;
	}	
		break;
	case SCALAR_PARAM::VEC4_0:
	case SCALAR_PARAM::VEC4_1:
	case SCALAR_PARAM::VEC4_2:
	case SCALAR_PARAM::VEC4_3:
	{
		int idx = (UINT)_ParamType - (UINT)SCALAR_PARAM::VEC4_0;
		return m_Const.v4Arr + idx;
	}
		break;
	case SCALAR_PARAM::MAT_0:
	case SCALAR_PARAM::MAT_1:
	case SCALAR_PARAM::MAT_2:
	case SCALAR_PARAM::MAT_3:
	{
		int idx = (UINT)_ParamType - (UINT)SCALAR_PARAM::MAT_0;
		return m_Const.matArr + idx;
	}
		break;
	}

	return nullptr;
}

int CMaterial::Save(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetContentPath();
	strFilePath += _strRelativePath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"wb");

	if (nullptr == pFile)
		return E_FAIL;

	// ���� ����� ����
	fwrite(&m_Const, sizeof(tMtrlConst), 1, pFile);	


	// ������ �����ϴ� �ؽ��� ������ ����	
	for (UINT i = 0; i < (UINT)TEX_PARAM::END; ++i)
	{
		SaveAssetRef<CTexture>(m_arrTex[i], pFile);
	}

	// ������ �����ϴ� ���̴� ������ ����
	SaveAssetRef<CGraphicsShader>(m_pShader, pFile);

	return 0;
}

int CMaterial::Load(const wstring& _strFilePath)
{
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, _strFilePath.c_str(), L"rb");

	if (nullptr == pFile)
		return E_FAIL;

	// ���� ����� ����
	fread(&m_Const, sizeof(tMtrlConst), 1, pFile);


	// ������ �����ϴ� �ؽ��� ������ �ε�
	for (UINT i = 0; i < (UINT)TEX_PARAM::END; ++i)
	{
		LoadAssetRef<CTexture>(m_arrTex[i], pFile);
	}

	// ������ �����ϴ� ���̴� ������ ����
	LoadAssetRef<CGraphicsShader>(m_pShader, pFile);

	return 0;
}