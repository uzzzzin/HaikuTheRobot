#include "pch.h"
#include "CMesh.h"

#include "CDevice.h"

CMesh::CMesh(bool _Engine)
	: CAsset(ASSET_TYPE::MESH, _Engine)
	, m_VtxCount(0)
	, m_VtxSysMem(nullptr)
	, m_IdxSysMem(nullptr)
{
}

CMesh::~CMesh()
{
	if (nullptr != m_VtxSysMem)
		delete m_VtxSysMem;

	if (nullptr != m_IdxSysMem)
		delete m_IdxSysMem;
}

int CMesh::Create(void* _Vtx, UINT _VtxCount, void* _Idx, UINT _IdxCount)
{
	m_VtxCount = _VtxCount;
	m_IdxCount = _IdxCount;

	// ���ؽ� ���� ����
	m_VBDesc = {};

	m_VBDesc.ByteWidth = sizeof(Vtx) * _VtxCount;
	m_VBDesc.StructureByteStride = sizeof(Vtx);
	m_VBDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	// ���ۿ� ������ ���� ����
	m_VBDesc.CPUAccessFlags = 0;
	m_VBDesc.Usage = D3D11_USAGE_DEFAULT;

	// g_Vtx �迭�� �����͸� �ʱ� �����ͷ� ����
	D3D11_SUBRESOURCE_DATA tSubData = {};
	tSubData.pSysMem = _Vtx;

	// ���ؽ� ���� ����
	if (FAILED(DEVICE->CreateBuffer(&m_VBDesc, &tSubData, m_VB.GetAddressOf())))
	{
		MessageBox(nullptr, L"���ؽ� ���� ���� ����", L"����", MB_OK);
		return E_FAIL;
	}

	// �ε��� ���� ����
	m_IBDesc = {};

	m_IBDesc.ByteWidth = sizeof(UINT) * _IdxCount;
	m_IBDesc.StructureByteStride = sizeof(UINT);
	m_IBDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;

	// ���ۿ� ������ ���� �Ұ���
	m_IBDesc.CPUAccessFlags = 0;
	m_IBDesc.Usage = D3D11_USAGE_DEFAULT;

	// g_Idx �迭�� �����͸� �ʱ� �����ͷ� ����
	tSubData = {};
	tSubData.pSysMem = _Idx;

	// �ε��� ���� ����
	if (FAILED(DEVICE->CreateBuffer(&m_IBDesc, &tSubData, m_IB.GetAddressOf())))
	{
		MessageBox(nullptr, L"�ε��� ���� ���� ����", L"����", MB_OK);
		return E_FAIL;
	}

	// ���� �������� �� �ε��� ������ �����Ҵ��� �����ٰ� ������ѵΰ� ����
	m_VtxSysMem = new Vtx[m_VtxCount];
	m_IdxSysMem = new UINT[m_IdxCount];
	
	memcpy(m_VtxSysMem, _Vtx, sizeof(Vtx) * m_VtxCount);
	memcpy(m_IdxSysMem, _Idx, sizeof(UINT) * m_IdxCount);

	return 0;
}

void CMesh::UpdateData()
{
	UINT iStride = sizeof(Vtx);
	UINT iOffset = 0;

	CONTEXT->IASetVertexBuffers(0, 1, m_VB.GetAddressOf(), &iStride, &iOffset);
	CONTEXT->IASetIndexBuffer(m_IB.Get(), DXGI_FORMAT_R32_UINT, 0);
}

void CMesh::render()
{
	UpdateData();

	CONTEXT->DrawIndexed(m_IdxCount, 0, 0);
}

void CMesh::render_asparticle(UINT _ParticleCount)
{
	UpdateData();

	CONTEXT->DrawIndexedInstanced(m_IdxCount, _ParticleCount, 0, 0, 0);
}
