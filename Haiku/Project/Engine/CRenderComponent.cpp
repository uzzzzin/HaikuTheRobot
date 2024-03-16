#include "pch.h"
#include "CRenderComponent.h"

#include "CLevelMgr.h"
#include "CLevel.h"


CRenderComponent::CRenderComponent(COMPONENT_TYPE _Type)
	: CComponent(_Type)
{
}

CRenderComponent::CRenderComponent(const CRenderComponent& _OriginRenderCom)
	: CComponent(_OriginRenderCom)
	, m_Mesh(_OriginRenderCom.m_Mesh)
	, m_SharedMtrl(_OriginRenderCom.m_SharedMtrl)	
{
	// ���� ������Ʈ�� ���������� �����ϰ� �ְ�, ���� ��������� ���������� �ƴѰ��
	if (_OriginRenderCom.m_SharedMtrl != _OriginRenderCom.m_CurMtrl)
	{
		assert(_OriginRenderCom.m_DynamicMtrl.Get());

		// ���� ���� ������Ʈ�� ������ ���������� �����Ѵ�.
		GetDynamicMaterial();

		// ���� ����������Ʈ�� �������� ���� ���� ������ ���������� �����Ѵ�.
		*m_DynamicMtrl.Get() = *_OriginRenderCom.m_DynamicMtrl.Get();
	}
	else
	{
		m_CurMtrl = m_SharedMtrl;
	}
}

CRenderComponent::~CRenderComponent()
{

}

void CRenderComponent::SetMaterial(Ptr<CMaterial> _Mtrl)
{
	// ������ ����Ǹ� ������ ���纻 �޾Ƶ� DynamicMaterial �� �����Ѵ�.
	m_CurMtrl = m_SharedMtrl = _Mtrl;
	m_DynamicMtrl = nullptr;
}


Ptr<CMaterial> CRenderComponent::GetDynamicMaterial()
{
	CLevel* pCurLevel = CLevelMgr::GetInst()->GetCurrentLevel();
	if (pCurLevel->GetState() != LEVEL_STATE::PLAY)
		return nullptr;

	// �̹� ���������� �����ϰ� ������ �װ� �ش�.
	if (nullptr != m_DynamicMtrl)
		return m_DynamicMtrl;

	// ���������� �ִٸ�
	if (nullptr != m_SharedMtrl)
	{
		// ���������� �����ؼ� ���������� ����� �װ� ���� ��������� �����Ѵ�.
		m_CurMtrl = m_DynamicMtrl = m_SharedMtrl->Clone();		
		return m_DynamicMtrl;
	}

	return nullptr;
}

void CRenderComponent::RestoreMaterial()
{
	m_CurMtrl = m_SharedMtrl;	
}


void CRenderComponent::SaveToFile(FILE* _File)
{
	SaveAssetRef(m_Mesh, _File);
	SaveAssetRef(m_SharedMtrl, _File);	
}

void CRenderComponent::LoadFromFile(FILE* _File)
{
	LoadAssetRef(m_Mesh, _File);
	LoadAssetRef(m_SharedMtrl, _File);
	
	SetMaterial(m_SharedMtrl);	
}