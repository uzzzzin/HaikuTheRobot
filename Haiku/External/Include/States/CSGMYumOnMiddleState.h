#pragma once
#include <Engine/CState.h>

class CSGMYumOnMiddleState :
    public CState
{
    float accTime;
    float duration;

    bool bIntroParticle; // true : ��Ʈ�� ��ƼŬ ���, false : ��� �� �ϰ� �Ϲ����� �߰��ȳ�

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CSGMYumOnMiddleState();
    ~CSGMYumOnMiddleState();
};
