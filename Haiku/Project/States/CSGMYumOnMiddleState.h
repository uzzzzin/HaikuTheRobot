#pragma once
#include <Engine/CState.h>

class CSGMYumOnMiddleState :
    public CState
{
    float accTime;
    float duration;

    bool bIntroParticle; // true : 인트로 파티클 재생, false : 재생 안 하고 일반적인 중간냠냠

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CSGMYumOnMiddleState();
    ~CSGMYumOnMiddleState();
};
