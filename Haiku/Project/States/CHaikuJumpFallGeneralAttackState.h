#pragma once
#include <Engine/CState.h>
class CHaikuJumpFallGeneralAttackState :
    public CState
{
    float duration;
    float accTime; // ���� ���� �ð�
public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CHaikuJumpFallGeneralAttackState();
    ~CHaikuJumpFallGeneralAttackState();
};

