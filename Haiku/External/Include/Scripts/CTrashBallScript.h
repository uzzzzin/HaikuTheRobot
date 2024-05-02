#pragma once
#include <Engine/CScript.h>

class CTrashBallScript :
    public CScript
{
private:
    float fRandomSpawnX;
    bool  bWillDestroy;


public:
    bool GetWillDestroy() { return bWillDestroy; }

public:
    void SetWillDestroy(bool _b) { bWillDestroy = _b; }
    float SetRandomSpawnX();
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CTrashBallScript);

public:
    CTrashBallScript();
    ~CTrashBallScript();
};

