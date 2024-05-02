#pragma once
#include <Engine/CState.h>

class CTrashBallDropState :
    public CState
{
private:
    float platform;
    float velocity;
    
    Vec3 prevPos;

    float acceleration;

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CTrashBallDropState();
    ~CTrashBallDropState();
};

