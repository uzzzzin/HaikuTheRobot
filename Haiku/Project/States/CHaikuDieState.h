#pragma once
#include <Engine\CState.h>
class CHaikuDieState :
    public CState
{
public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CHaikuDieState();
    ~CHaikuDieState();
};

