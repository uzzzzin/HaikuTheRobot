#include "pch.h"
#include "CLevel.h"

#include "CLayer.h"
#include "CGameObject.h"

#include "CTimeMgr.h"
#include "CRenderMgr.h"

CLevel::CLevel()
	: m_arrLayer{}
	, m_State(LEVEL_STATE::NONE)
{
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i] = new CLayer;
		m_arrLayer[i]->m_iLayerIdx = i;
	}
}

CLevel::CLevel(const CLevel& _OriginLevel)
	: CEntity(_OriginLevel)
	, m_arrLayer{}
{
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i] = _OriginLevel.m_arrLayer[i]->Clone();
	}
}

CLevel::~CLevel()
{
	Delete_Array(m_arrLayer);
}

void CLevel::begin()
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->begin();
	}
}

void CLevel::tick()
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->tick();
	}
}

void CLevel::finaltick()
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->finaltick();
	}
}

void CLevel::AddObject(CGameObject* _Object, int _LayerIdx, bool _bChildMove)
{
	m_arrLayer[_LayerIdx]->AddObject(_Object, _bChildMove);
}

void CLevel::AddObject(CGameObject* _Object, const wstring& _strLayerName, bool _bChildMove)
{
	CLayer* pLayer = GetLayer(_strLayerName);
	if (nullptr == pLayer)
		return;

	pLayer->AddObject(_Object, _bChildMove);
}

CLayer* CLevel::GetLayer(const wstring& _strLayerName)
{
	for (int i = 0; i < LAYER_MAX; ++i)
	{
		if (_strLayerName == m_arrLayer[i]->GetName())
		{
			return m_arrLayer[i];
		}
	}
	return nullptr;
}

CGameObject* CLevel::FindObjectByName(const wstring& _strName)
{
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		const vector<CGameObject*>& vecParent = m_arrLayer[i]->GetParentObjects();

		for (size_t j = 0; j < vecParent.size(); ++j)
		{
			list<CGameObject*> queue;
			queue.push_back(vecParent[j]);

			// ���̾ �ԷµǴ� ������Ʈ ����, �� �ؿ� �޸� �ڽĵ���� ��� Ȯ��
			while (!queue.empty())
			{
				CGameObject* pObject = queue.front();
				queue.pop_front();
				
				const vector<CGameObject*>& vecChild = pObject->GetChild();
				for (size_t k = 0; k < vecChild.size(); ++k)
				{
					queue.push_back(vecChild[k]);
				}

				if (_strName == pObject->GetName())
				{
					return pObject;
				}
			}
		}
	}
	
	return nullptr;
}

void CLevel::FindObjectsByName(const wstring& _strName, vector<CGameObject*>& _vecObj)
{
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		const vector<CGameObject*>& vecParent = m_arrLayer[i]->GetParentObjects();

		for (size_t j = 0; j < vecParent.size(); ++j)
		{
			list<CGameObject*> queue;
			queue.push_back(vecParent[j]);

			// ���̾ �ԷµǴ� ������Ʈ ����, �� �ؿ� �޸� �ڽĵ���� ��� Ȯ��
			while (!queue.empty())
			{
				CGameObject* pObject = queue.front();
				queue.pop_front();

				const vector<CGameObject*>& vecChild = pObject->GetChild();
				for (size_t k = 0; k < vecChild.size(); ++k)
				{
					queue.push_back(vecChild[k]);
				}

				if (_strName == pObject->GetName())
				{
					_vecObj.push_back(pObject);
				}
			}
		}
	}
}

void CLevel::clear()
{
	for (UINT i = 0; i < LAYER_MAX; ++i)
	{
		m_arrLayer[i]->m_vecObjects.clear();
	}
}

//void CLevel::ChangeState(LEVEL_STATE _NextState)
//{
//	if (m_State == _NextState)
//		return;
//
//	// ���� -> �÷���
//	if ((LEVEL_STATE::STOP == m_State || LEVEL_STATE::PAUSE == m_State || LEVEL_STATE::NONE == m_State)
//		&& LEVEL_STATE::PLAY == _NextState)
//	{
//		CTimeMgr::GetInst()->LockDeltaTime(false);
//
//		// ���� ī�޶� ���
//		CRenderMgr::GetInst()->ActiveEditorMode(false);
//
//		// None, Stop -> Play
//		if (LEVEL_STATE::STOP == m_State || LEVEL_STATE::NONE == m_State)
//		{
//
//			begin();
//		}
//		// ���� ������Ʈ ����
//		m_State = _NextState;
//	}
//
//	// �÷��� -> ���� or �Ͻ�����
//	else if ( (LEVEL_STATE::PLAY == m_State || LEVEL_STATE::NONE == m_State) &&
//		(LEVEL_STATE::STOP == _NextState || LEVEL_STATE::PAUSE == _NextState || LEVEL_STATE::NONE == _NextState))
//	{
//		// ���� ������Ʈ ����
//		m_State = _NextState;
//
//		CTimeMgr::GetInst()->LockDeltaTime(true);
//
//		// ������ ī�޶� ���
//		CRenderMgr::GetInst()->ActiveEditorMode(true);
//	}
//}

void CLevel::ChangeState(LEVEL_STATE _NextState)
{
	if (m_State == _NextState)
		return;

	// case: ������ -> ���� (���� -> �÷���)
	if ((m_State == LEVEL_STATE::STOP || m_State == LEVEL_STATE::PAUSE || m_State == LEVEL_STATE::NONE)
		&& _NextState == LEVEL_STATE::PLAY)
	{
		CTimeMgr::GetInst()->LockDeltaTime(false);
		CRenderMgr::GetInst()->ActiveEditorMode(false); // ���� ī�޶�

		if (LEVEL_STATE::STOP == m_State || LEVEL_STATE::NONE == m_State)
		{
			m_State = _NextState;
			begin();
		}
	}

	// case: ���� -> ������ (�÷��� -> ����)
	else if ((m_State == LEVEL_STATE::PLAY ||  m_State == LEVEL_STATE::NONE) &&
		(_NextState == LEVEL_STATE::STOP || _NextState == LEVEL_STATE::PAUSE  || _NextState == LEVEL_STATE::NONE))
	{
		CTimeMgr::GetInst()->LockDeltaTime(true);
		CRenderMgr::GetInst()->ActiveEditorMode(true); // ������ ī�޶�
	}

	m_State = _NextState;
}