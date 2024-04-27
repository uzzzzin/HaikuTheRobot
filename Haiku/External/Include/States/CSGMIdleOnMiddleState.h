#pragma once
#include <Engine/CState.h>

class CSGMIdleOnMiddleState :
    public CState
{
private:
    float accTime;
    float duration;
public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CSGMIdleOnMiddleState();
    ~CSGMIdleOnMiddleState();
};

