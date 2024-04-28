#pragma once
#include <Engine/CState.h>

class CSGMUpToMiddleState :
    public CState
{
    float accTime;
    float duration;

    int introCnt;

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CSGMUpToMiddleState();
    ~CSGMUpToMiddleState();
};


