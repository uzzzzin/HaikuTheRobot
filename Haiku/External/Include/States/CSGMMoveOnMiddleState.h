#pragma once
#include <Engine/CState.h>
class CSGMMoveOnMiddleState :
    public CState
{

private:
    float accTime;
    float duration;

    Vec3 prevColOffset;
    Vec3 prevColScale;
    //float prevColRotZ;

    Vec3 wantColOffsetL;
    Vec3 wantColScaleL;
    //float wantColRotZL;

    Vec3 wantColOffsetR;
    Vec3 wantColScaleR;
    //float wantColRotZR;

    Vec3 prevPos;

    float WallL;
    float WallR;

    float speed;

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CSGMMoveOnMiddleState();
    ~CSGMMoveOnMiddleState();
};

