#pragma once
#include <Engine\CState.h>
class CHaikuPlatformGeneralAttackState :
    public CState
{

private:
    float duration;
    float accTime; // 현재 누적 애님 플레이 시간

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CHaikuPlatformGeneralAttackState();
    ~CHaikuPlatformGeneralAttackState();
};

