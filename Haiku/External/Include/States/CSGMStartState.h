#pragma once
#include <Engine/CState.h>

class CSGMStartState :
    public CState
{
    float accTime;
    float duration;

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CSGMStartState();
    ~CSGMStartState();
};

