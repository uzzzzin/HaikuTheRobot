#pragma once
#include <Engine\CState.h>
class CHaikuDashState :
    public CState
{
public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CHaikuDashState();
    ~CHaikuDashState();
};

