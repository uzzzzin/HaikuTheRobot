#pragma once
#include <Engine\CState.h>
class CHaikuStartState :
    public CState
{
    float accTime;
    float duration;

public:
    float GetStateDuration() { return duration; }
public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CHaikuStartState();
    ~CHaikuStartState();
};
