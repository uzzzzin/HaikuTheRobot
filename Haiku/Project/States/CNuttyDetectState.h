#pragma once
#include <Engine/CState.h>
class CNuttyDetectState :
    public CState
{
private:
    float duration;
    float accTime;

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CNuttyDetectState();
    ~CNuttyDetectState();
};

