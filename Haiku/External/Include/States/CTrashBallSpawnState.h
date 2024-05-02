#pragma once
#include <Engine/CState.h>

class CTrashBallSpawnState :
    public CState
{
private:
    float accTime;
    float duration;

    float spawnAccTime;
    float spawnTime;

    bool bSpawnNextTB;

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CTrashBallSpawnState();
    ~CTrashBallSpawnState();
};

