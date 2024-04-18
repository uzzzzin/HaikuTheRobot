#pragma once
#include <Engine\CState.h>
class CHaikuIntroState :
    public CState
{
private:
    float accTime;
    float duration;

    float virusAccTime;
    float virusDuration;
   
    bool bShake;
public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CHaikuIntroState();
    ~CHaikuIntroState();
};

