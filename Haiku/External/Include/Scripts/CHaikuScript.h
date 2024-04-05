#pragma once

#include "Engine\CScript.h"
class CHaikuScript :
    public CScript
{
private:
    int stamina; // 피통
    int power; // 그 요상한 기력

private:
    int curDir; // 현재 방향          // R 0, L 1
    int prevDir; // 1틱 전 방향        // true = L. false = R

    wstring curStateName;  // 현재 상태
    wstring prevStateName; // 이전 상태 (어떤 상태로부터 넘어왔는지)

    wstring colPlatformName;

    COLLISION_DIR prevColDir; // 1틱 전이 충돌상태였을 때 1틱 전 충돌 방향 

    int collisionCnt;

    vector<CGameObject*> m_Ground;
    int  m_OverlapGround;

    bool bGeneralAttackSeed;

public:
    int GetCurDir() { return curDir; }
    int GetPrevDir() { return prevDir; }

    wstring GetCurStateName() { return curStateName;  }
    wstring GetPrevStateName() { return prevStateName; }

    wstring GetColPlatformName() { return colPlatformName; }

    COLLISION_DIR GetPrevColDir() { return prevColDir; }

    void AddOverlapGround(CGameObject* _pObejct);
    void SubOverlapGround(CGameObject* _pObejct);

    int GetOverlapGround() { return m_OverlapGround; }

    int GetCollisionCnt() { return collisionCnt; }

    bool GetGeneralAttackSeed() { return bGeneralAttackSeed; }

public:
    void SetCurDir(bool _dir) { curDir = _dir; }
    void SetPrevDir(bool _dir) { prevDir = _dir; }
    void SetCurStateName(wstring _stateName) { curStateName = _stateName; }
    void SetPrevStateName(wstring _stateName) { prevStateName = _stateName; }

    void ChangeGeneralAttackSeed()
    {
        if (bGeneralAttackSeed) { bGeneralAttackSeed = false; }
        else { bGeneralAttackSeed = false; }
    }

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CHaikuScript);
public:
    CHaikuScript();
    ~CHaikuScript();
};
