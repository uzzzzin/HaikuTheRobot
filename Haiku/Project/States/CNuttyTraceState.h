#pragma once
#include <Engine/CState.h>
class CNuttyTraceState :
    public CState
{
private:
    float NuttyDetectRange;

    float NuttyDetectLeftPos;
    float NuttyDetectRightPos;

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CNuttyTraceState();
    ~CNuttyTraceState();
};

