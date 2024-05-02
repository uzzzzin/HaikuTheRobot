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

    Vec3 prevPos;
    float spawnDistance; // 일정 y값이 되면 tb 생성

    bool bSpawnNextTB;

public:
    virtual void Enter() override;
    virtual void finaltick() override;
    virtual void Exit() override;

public:
    CTrashBallSpawnState();
    ~CTrashBallSpawnState();
};

