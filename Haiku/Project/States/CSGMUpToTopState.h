#pragma once
#include <Engine/CState.h>
class CSGMUpToTopState :
    public CState
{
private:

    float accTime;
    float duration;

    Vec3 prevColOffset;
    Vec3 prevColScale;

    Vec3 wantColOffset;
    Vec3 wantColScale;

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CSGMUpToTopState();
    ~CSGMUpToTopState();
};

