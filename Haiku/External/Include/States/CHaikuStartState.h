#pragma once
#include <Engine\CState.h>
class CHaikuStartState :
    public CState
{
    bool bStart;
public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CHaikuStartState();
    ~CHaikuStartState();
};
