#pragma once
#include <Engine/CState.h>

class CSGMYumOnTopState :
    public CState
{
private:
    float accTime;
    float duration;
public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CSGMYumOnTopState();
    ~CSGMYumOnTopState();
};

