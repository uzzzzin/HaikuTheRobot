#pragma once
#include <Engine/CState.h>
class CNuttyIdleState :
    public CState
{
    float       NuttyMoveRange;
    float       NuttyDetectRange;
    float       NuttySpeed;

    //int         NuttyCurDir; // R 0, L 1

    Vec3        NuttyOriginPos;

    float        NuttyMoveLeftPos;
    float        NuttyMoveRightPos;

    float        NuttyDetectLeftPos;
    float        NuttyDetectRightPos;

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CNuttyIdleState();
    ~CNuttyIdleState();
};

