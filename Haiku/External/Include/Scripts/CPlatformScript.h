#pragma once
#include "Engine\CScript.h"
class CPlatformScript :
    public CScript
{
private:
    COLLISION_DIR curColDir;
public:
    COLLISION_DIR GetCurColDir() { return curColDir; }
    COLLISION_DIR DetectCollision(Vec3 PlatformPos, float PlatformWidth, float PlatformHeight, Vec3 ObjPos, float ObjWidth, float ObjHeight);

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CPlatformScript);
public:
    CPlatformScript();
    ~CPlatformScript();
};



