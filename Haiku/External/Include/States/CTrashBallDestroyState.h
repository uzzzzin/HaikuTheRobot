#pragma once
#include <Engine/CState.h>

class CTrashBallDestroyState :
    public CState
{
public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CTrashBallDestroyState();
    ~CTrashBallDestroyState();
};

