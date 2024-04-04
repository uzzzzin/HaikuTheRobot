#pragma once
#include <Engine\CState.h>
class CHaikuRepairState :
    public CState
{
private:
    float duration; 
    float accTime; // 현재 누적 대시 시간

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CHaikuRepairState();
    ~CHaikuRepairState();

};

