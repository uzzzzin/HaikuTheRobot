#pragma once
#include <Engine/CScript.h>
class CNuttyScript :
    public CScript
{
private:
    float       m_MoveRange;
    float       m_DetectRange;
    float       m_Speed;

    int         m_CurDir; // R 0, L 1

    Vec3        m_OriginPos;

    CGameObject*  m_Target;

public:
    int GetCurDir() { return m_CurDir; }
    Vec3 GetOriginPos() { return m_OriginPos; }
    float GetMoveRange() { return m_MoveRange; }
    float GetDetectRange() { return m_DetectRange; }
    float GetSpeed() { return m_Speed; }
    CGameObject* GetTarget() { return m_Target; }

public:
    void SetCurDir(int _dir) { m_CurDir = _dir; }

public:
    virtual void begin() override;
    virtual void tick() override;


    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CNuttyScript);
public:
    CNuttyScript();
    ~CNuttyScript();
};

