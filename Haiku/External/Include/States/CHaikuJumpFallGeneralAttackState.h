#pragma once
#include <Engine/CState.h>
class CHaikuJumpFallGeneralAttackState :
    public CState
{
    float duration;
    float accTime; // 현재 누적 시간
public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CHaikuJumpFallGeneralAttackState();
    ~CHaikuJumpFallGeneralAttackState();
};

