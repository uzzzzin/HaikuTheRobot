#pragma once
#include <Engine/CState.h>
class CHaikuJumpRiseDownAttackState :
    public CState
{
    float duration;
    float accTime; // ���� ���� ��� �ð�

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CHaikuJumpRiseDownAttackState();
    ~CHaikuJumpRiseDownAttackState();
};

