#pragma once
#include <Engine\CState.h>
class CSGMNullState :
    public CState
{
public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CSGMNullState();
    ~CSGMNullState();
};

