#pragma once
#include <Engine\CState.h>
class CHaikuDashState :
    public CState
{
private:
    float duration; // 얼마동안 대시가 진행되어야 하는지
    float accTime; // 현재 누적 대시 시간

    float dashLength; // 대시 거리
    float dashSpeed; // 대시 스피드

    Vec3 afterDashPos; // 대시 후 지정될 포지션

public:
    void DashSet();

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CHaikuDashState();
    ~CHaikuDashState();
};

