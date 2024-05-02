#pragma once
#include <Engine\CScript.h>

class CBoss1RoomScript :
    public CScript
{
private:
    bool bIntroDoor;

    bool bCameraLock;

    int  curTrashBallCnt;

public:
    bool GetCameraLock() { return bCameraLock; }
    int  GetCurTrashBallCnt() { return curTrashBallCnt; }

public:
    void SetCameraLock(bool _lock) { bCameraLock = _lock; }
    void MinusCurTrashBallCnt() { --curTrashBallCnt; }
    void PlusCurTrashBallCnt() { ++curTrashBallCnt; }

public:
    virtual void tick() override;
    virtual void begin() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CBoss1RoomScript);
public:
    CBoss1RoomScript();
    ~CBoss1RoomScript();
};

