#pragma once
#include <Engine/CState.h>
class CTireDieState :
    public CState
{
private:
    float duration;
    float accTime;

    Vec3 diePos;
public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CTireDieState();
    ~CTireDieState();
};

