#pragma once
#include <Engine/CState.h>
class CTireIdleState :
    public CState
{
public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CTireIdleState();
    ~CTireIdleState();
};

