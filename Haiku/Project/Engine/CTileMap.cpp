#include "pch.h"
#include "CTileMap.h"

#include "CStructuredBuffer.h"

#include "CAssetMgr.h"
#include "CMesh.h"

#include "CTransform.h"

CTileMap::CTileMap()
	: CRenderComponent(COMPONENT_TYPE::TILEMAP)
	, m_FaceX(2)
	, m_FaceY(2)
	, m_vTileRenderSize(Vec2(128.f, 128.f))	
	, m_TileInfoBuffer(nullptr)
{
	SetMesh(CAssetMgr::GetInst()->FindAsset<CMesh>(L"RectMesh"));
	SetMaterial(CAssetMgr::GetInst()->FindAsset<CMaterial>(L"TileMapMtrl"));

	m_TileInfoBuffer = new CStructuredBuffer;

	SetFace(m_FaceX, m_FaceY);
}

CTileMap::CTileMap(const CTileMap& _OriginTileMap)
	: CRenderComponent(_OriginTileMap)
	, m_FaceX(_OriginTileMap.m_FaceX)
	, m_FaceY(_OriginTileMap.m_FaceY)
	, m_vTileRenderSize(_OriginTileMap.m_vTileRenderSize)	
	, m_TileAtlas(_OriginTileMap.m_TileAtlas)
	, m_vTilePixelSize(_OriginTileMap.m_vTilePixelSize)
	, m_vSliceSizeUV(_OriginTileMap.m_vSliceSizeUV)
	, m_MaxCol(_OriginTileMap.m_MaxCol)
	, m_MaxRow(_OriginTileMap.m_MaxRow)
	, m_vecTileInfo(_OriginTileMap.m_vecTileInfo)
	, m_TileInfoBuffer(nullptr)
{
	if (nullptr != _OriginTileMap.m_TileInfoBuffer)
	{
		m_TileInfoBuffer = _OriginTileMap.m_TileInfoBuffer->Clone();
	}	
}

CTileMap::~CTileMap()
{
	if (nullptr != m_TileInfoBuffer)
		delete m_TileInfoBuffer;
}

void CTileMap::finaltick()
{
	// (Ÿ�� ���� * Ÿ�� ������) �� ����� ����ó���Ѵ�.
	Vec3 vTileMapSize = Vec3(m_FaceX * m_vTileRenderSize.x, m_FaceY * m_vTileRenderSize.y, 1.f);
	Transform()->SetRelativeScale(vTileMapSize);
}

void CTileMap::render()
{	
	// ������ ��Ʋ�� �ؽ��� ����.
	GetMaterial()->SetTexParam(TEX_PARAM::TEX_0, m_TileAtlas);
	
	// Ÿ���� ���� ���� ����
	GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_0, m_FaceX);
	GetMaterial()->SetScalarParam(SCALAR_PARAM::INT_1, m_FaceY);
		
	// ��Ʋ�� �̹������� Ÿ�� 1���� �ڸ��� ������(UV ����)
	GetMaterial()->SetScalarParam(SCALAR_PARAM::VEC2_0, m_vSliceSizeUV);

	// �� Ÿ�� ������ ����ȭ ���۷� �̵�
	m_TileInfoBuffer->SetData(m_vecTileInfo.data(), m_vecTileInfo.size());

	// Ÿ�� ����ȭ ���۸� t20 �� ���ε�
	m_TileInfoBuffer->UpdateData(20);

	// ���� ������Ʈ
	GetMaterial()->UpdateData();	

	Transform()->UpdateData();

	GetMesh()->render();
}


void CTileMap::UpdateData()
{

}


void CTileMap::SetTileAtlas(Ptr<CTexture> _Atlas, Vec2 _TilePixelSize)
{
	m_TileAtlas = _Atlas;
	m_vTilePixelSize = _TilePixelSize;

	m_MaxCol = m_TileAtlas->GetWidth() / (UINT)m_vTilePixelSize.x;
	m_MaxRow = m_TileAtlas->GetHeight() / (UINT)m_vTilePixelSize.y;

	m_vSliceSizeUV = Vec2(m_vTilePixelSize.x / m_TileAtlas->GetWidth()
		, m_vTilePixelSize.y / m_TileAtlas->GetHeight());
}

void CTileMap::SetFace(UINT _FaceX, UINT _FaceY)
{
	m_FaceX = _FaceX;
	m_FaceY = _FaceY;

	vector<tTileInfo> vecTemp;
	m_vecTileInfo.swap(vecTemp);
	m_vecTileInfo.resize(_FaceX * _FaceY);

	m_TileInfoBuffer->Create(sizeof(tTileInfo), _FaceX * _FaceY, SB_TYPE::READ_ONLY, true);
}

void CTileMap::SetTileIndex(UINT _Row, UINT _Col, UINT _ImgIdx)
{
	if (nullptr == m_TileAtlas)
		return;

	UINT idx = _Row* m_FaceX + _Col;

	// �������� Ÿ�� ����
	UINT iRow = _ImgIdx / m_MaxCol;
	UINT iCol = _ImgIdx % m_MaxCol;

	m_vecTileInfo[idx].vLeftTopUV = Vec2((iCol * m_vTilePixelSize.x) / m_TileAtlas->GetWidth()
								  , (iRow * m_vTilePixelSize.y) / m_TileAtlas->GetHeight());

	m_vecTileInfo[idx].bRender = 1;
}





void CTileMap::SaveToFile(FILE* _File)
{
	// TileMap ���� ����
	fwrite(&m_FaceX, sizeof(UINT), 1, _File);
	fwrite(&m_FaceY, sizeof(UINT), 1, _File);
	fwrite(&m_vTileRenderSize, sizeof(Vec2), 1, _File);
	fwrite(&m_vTileRenderSize, sizeof(Vec2), 1, _File);

	SaveAssetRef(m_TileAtlas, _File);

	fwrite(&m_vTilePixelSize, sizeof(Vec2), 1, _File);
	fwrite(&m_vSliceSizeUV, sizeof(Vec2), 1, _File);

	fwrite(&m_MaxCol, sizeof(UINT), 1, _File);
	fwrite(&m_MaxRow, sizeof(UINT), 1, _File);
	
	size_t InfoCount = m_vecTileInfo.size();
	fwrite(&InfoCount, sizeof(size_t), 1, _File);
	fwrite(m_vecTileInfo.data(), sizeof(tTileInfo), InfoCount, _File);
}

void CTileMap::LoadFromFile(FILE* _File)
{
	// TileMap ���� ����
	fread(&m_FaceX, sizeof(UINT), 1, _File);
	fread(&m_FaceY, sizeof(UINT), 1, _File);
	fread(&m_vTileRenderSize, sizeof(Vec2), 1, _File);
	fread(&m_vTileRenderSize, sizeof(Vec2), 1, _File);

	LoadAssetRef(m_TileAtlas, _File);

	fread(&m_vTilePixelSize, sizeof(Vec2), 1, _File);
	fread(&m_vSliceSizeUV, sizeof(Vec2), 1, _File);

	fread(&m_MaxCol, sizeof(UINT), 1, _File);
	fread(&m_MaxRow, sizeof(UINT), 1, _File);

	size_t InfoCount = 0;
	fread(&InfoCount, sizeof(size_t), 1, _File);
	m_vecTileInfo.reserve(InfoCount);
	fread(m_vecTileInfo.data(), sizeof(tTileInfo), InfoCount, _File);
}