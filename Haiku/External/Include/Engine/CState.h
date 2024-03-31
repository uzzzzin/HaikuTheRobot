#pragma once
#include "CEntity.h"

class CFSM;
class CStateMachine;

class CState :
    public CEntity
{
private:
    CFSM*       m_FSM;
    const UINT        m_StateType;

    wstring     curStateName;



public:
    virtual void finaltick() = 0;
    virtual void Enter() = 0;
    virtual void Exit() = 0;

protected:
    void* GetBlackboardData(const wstring& _strKey);
    CFSM* GetFSM() { return m_FSM; }

    void ChangeState(const wstring& _strStateName);

public:
    UINT GetStateType() { return m_StateType; }
    virtual void SaveToFile(FILE* _File) {}
    virtual void LoadFromFile(FILE* _File) {}

public:
    //wstring GetCurStateName()
    //{
    //    return curStateName;
    //}

    //void SetCurStateName(const wstring& _strStateName);

    CGameObject* GetOwnerObj();



public:
    CLONE_DISABLE(CState);

    CState(UINT StateType);
    ~CState();

    friend class CFSM;
};
