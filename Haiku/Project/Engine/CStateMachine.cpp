#include "pch.h"
#include "CStateMachine.h"

CStateMachine::CStateMachine()
	: CComponent(COMPONENT_TYPE::STATEMACHINE)
{
}

CStateMachine::~CStateMachine()
{
}


void CStateMachine::begin()
{
	// ���� FSM ������ Instance �� �����صд�.
	if (m_FSM.Get())
	{
		m_FSM_Inst = m_FSM->GetFSMIstance();
		m_FSM_Inst->SetStateMachine(this);
	}
}

void CStateMachine::finaltick()
{
	if(m_FSM_Inst.Get())
		m_FSM_Inst->finaltick();
}

void CStateMachine::SetFSM(Ptr<CFSM> _FSM)
{
	m_FSM = _FSM;
	m_FSM_Inst = nullptr;
}

void CStateMachine::AddBlackboardData(const wstring& _strKey, BB_DATA _Type, void* _pData)
{
	m_Blackboard.AddBlackboardData(_strKey, _Type, _pData);
}

void* CStateMachine::GetBlackboardData(const wstring& _strKey)
{
	return m_Blackboard.GetBlackboardData(_strKey);
}

void CStateMachine::SaveToFile(FILE* _File)
{
	SaveAssetRef(m_FSM, _File);	
}

void CStateMachine::LoadFromFile(FILE* _File)
{
	LoadAssetRef(m_FSM, _File);
}

Ptr<CFSM> CStateMachine::GetDynamicFSM()
{
	if (nullptr == m_FSM)
		return nullptr;

	if (!m_FSM_Inst.Get())
	{
		m_FSM_Inst = m_FSM->GetFSMIstance();
	}

	return m_FSM_Inst;
}

