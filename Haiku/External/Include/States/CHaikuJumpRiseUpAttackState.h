#pragma once
#include <Engine/CState.h>
class CHaikuJumpRiseUpAttackState :
    public CState
{
    float duration;
    float accTime; // ���� ���� ��� �ð�

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CHaikuJumpRiseUpAttackState();
    ~CHaikuJumpRiseUpAttackState();
};
