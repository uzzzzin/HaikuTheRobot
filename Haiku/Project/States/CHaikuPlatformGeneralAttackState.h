#pragma once
#include <Engine\CState.h>
class CHaikuPlatformGeneralAttackState :
    public CState
{

private:
    float duration;
    float accTime; // ���� ���� �ִ� �÷��� �ð�

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CHaikuPlatformGeneralAttackState();
    ~CHaikuPlatformGeneralAttackState();
};

