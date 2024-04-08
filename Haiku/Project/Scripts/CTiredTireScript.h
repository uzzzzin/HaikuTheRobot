#pragma once
#include <Engine/CScript.h>
class CTiredTireScript :
    public CScript
{
private :
    vector<CGameObject*> m_Ground;
    int  m_OverlapGround;

    int life; // 2

public:
    void AddOverlapGround(CGameObject* _pObejct);
    void SubOverlapGround(CGameObject* _pObejct);

    int GetOverlapGround() { return m_OverlapGround; }

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CTiredTireScript);


public:
    CTiredTireScript();
    ~CTiredTireScript();
};

