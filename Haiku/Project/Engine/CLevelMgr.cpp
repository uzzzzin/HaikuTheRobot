#include "pch.h"
#include "CLevelMgr.h"

#include "CRenderMgr.h"
#include "CLevel.h"
#include "CLayer.h"

#include "CDevice.h"
#include "CAssetMgr.h"
#include "CCollisionMgr.h"

#include "CTaskMgr.h"


CLevelMgr::CLevelMgr()
	: m_CurLevel(nullptr)
{

}

CLevelMgr::~CLevelMgr()
{
	if (nullptr != m_CurLevel)
		delete m_CurLevel;
}

void CLevelMgr::init()
{

}

void CLevelMgr::tick()
{
	if (nullptr == m_CurLevel)
		return;

	// ���� �����ӿ� ��ϵ� ������Ʈ�� clear
	m_CurLevel->clear();

	// ������ Play ������ ��쿡�� tick() ȣ��
	if (m_CurLevel->GetState() == LEVEL_STATE::PLAY)
	{
		m_CurLevel->tick();
	}
	
	m_CurLevel->finaltick();

	// �浹 ó��
	CCollisionMgr::GetInst()->tick();

	// Render
	CRenderMgr::GetInst()->tick();
}

void CLevelMgr::ChangeLevel(CLevel* _NextLevel, LEVEL_STATE _NextLevelStartState)
{
	tTask task = {};

	task.Type = TASK_TYPE::CHANGE_LEVEL;
	task.Param_1 = (DWORD_PTR)_NextLevel;	
	task.Param_2 = (DWORD_PTR)_NextLevelStartState;

	CTaskMgr::GetInst()->AddTask(task);	
}

void CLevelMgr::ChangeLevelState(LEVEL_STATE _State)
{
	tTask task = {};

	task.Type = TASK_TYPE::CHANGE_LEVELSTATE;
	task.Param_1 = (DWORD_PTR)m_CurLevel;
	task.Param_2 = (DWORD_PTR)_State;

	CTaskMgr::GetInst()->AddTask(task);
}

void CLevelMgr::ChangeLevel_Task(CLevel* _NextLevel, LEVEL_STATE _NextLevelState)
{
	assert(!(m_CurLevel == _NextLevel));
		
	if (nullptr != m_CurLevel)
		delete m_CurLevel;

	m_CurLevel = _NextLevel;

	if (nullptr != m_CurLevel)
		m_CurLevel->ChangeState(_NextLevelState);
}
