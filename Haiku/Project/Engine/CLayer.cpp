#include "pch.h"
#include "CLayer.h"

#include "CGameObject.h"
#include "CGC.h"


CLayer::CLayer()
	: m_iLayerIdx(-1)
{

}

CLayer::CLayer(const CLayer& _OriginLayer)
	: CEntity(_OriginLayer)
	, m_iLayerIdx(_OriginLayer.m_iLayerIdx)
{
	for (size_t i = 0; i < _OriginLayer.m_vecParent.size(); ++i)
	{
		AddObject(_OriginLayer.m_vecParent[i]->Clone(), false);
	}
}

CLayer::~CLayer()
{
	Delete_Vec(m_vecParent);	
}



void CLayer::begin()
{
	for (size_t i = 0; i < m_vecParent.size(); ++i)
	{
		m_vecParent[i]->begin();
	}
}

void CLayer::tick()
{
	for (size_t i = 0; i < m_vecParent.size(); ++i)
	{
		m_vecParent[i]->tick();
	}
}

void CLayer::finaltick()
{
	vector<CGameObject*>::iterator iter = m_vecParent.begin();

	for (; iter != m_vecParent.end(); )
	{
		(*iter)->finaltick();

		if ((*iter)->IsDead())
		{
			CGC::GetInst()->Add(*iter);
			iter = m_vecParent.erase(iter);
		}
		else
		{
			++iter;
		}
	}
}

void CLayer::AddObject(CGameObject* _Object, bool _bMove)
{
	// _bMove : true  - ���̾ �ԷµǴ� Object�� �ڽ��� �ִ� ���, �ڽı��� ��� �ش� ���̾�� �Ѿ�´�.
	// _bMove : false - ���̾ �ԷµǴ� Object�� �ڽ��� �ش� ���̾�� ���� �Ѿ���� �ʴ´�. �� �ڽĿ�����Ʈ�� ���̾� �Ҽ��� ���� ���(-1)���� ���� �����Ѵ�.      AssortRock

	// �ֻ��� �θ� ������Ʈ����.
	if (nullptr == _Object->GetParent())
	{
		// �ٸ� ���̾� �Ҽ��̾���
		if (-1 != _Object->m_iLayerIdx)
		{
			// ���� ���̾��� Parent ���Ϳ��� ���ŵǾ�� �Ѵ�.
			_Object->DisconnectWithLayer();
		}

		// �ֻ��� �θ� ������Ʈ�� m_vecParent ���� ����Ű���� �Ѵ�.
		m_vecParent.push_back(_Object);
	}
	
	// ������Ʈ�� ���̾� �Ҽ��� ���� ���̾�� ����
	// �ڽ� ������Ʈ���� ���̾� �Ҽ��� ����	
	list<CGameObject*> queue;
	queue.push_back(_Object);
	
	// ���̾ �ԷµǴ� ������Ʈ ����, �� �ؿ� �޸� �ڽĵ���� ��� Ȯ��
	while (!queue.empty())
	{
		CGameObject* pObject = queue.front();
		queue.pop_front();

		for (size_t i = 0; i < pObject->m_vecChild.size(); ++i)
		{
			queue.push_back(pObject->m_vecChild[i]);
		}		

		// ���� �Է� ������Ʈ�� ������ �ش� ���̾� �Ҽ����� ����
		if(pObject == _Object)
			pObject->m_iLayerIdx = m_iLayerIdx;
		else
		{
			// �ڽ� ������Ʈ���� _bMove �� true �� ���, �θ� ���� �ش� ���̾�Ҽ����� ����
			if(_bMove)
				pObject->m_iLayerIdx = m_iLayerIdx;
			// _bMove �� false ��쿡��, �ڽ� ������Ʈ�� ���̾�Ҽ��� ���ٸ� �θ� ���� ����
			else if(-1 == pObject->m_iLayerIdx)
				pObject->m_iLayerIdx = m_iLayerIdx;
		}
	}
}

void CLayer::DetachGameObject(CGameObject* _Object)
{
	assert(!(-1 == _Object->m_iLayerIdx || _Object->m_iLayerIdx != m_iLayerIdx));
	
	// �θ� ������Ʈ�� �ִ� ���
	if (nullptr != _Object->GetParent())
	{
		_Object->m_iLayerIdx = -1;
	}

	// �ֻ��� �θ� ������Ʈ�� ���
	else
	{
		vector<CGameObject*>::iterator iter = m_vecParent.begin();
		for (; iter != m_vecParent.end(); ++iter)
		{
			if (*iter == _Object)
			{
				m_vecParent.erase(iter);
				_Object->m_iLayerIdx = -1;
				return;
			}			
		}
	}

	assert(nullptr);
}
