#pragma once
#include <Engine/CScript.h>
class CSwingingGarbageMagnetScript :
    public CScript
{
private:
    wstring curStateName;  // 현재 상태
    wstring prevStateName; // 이전 상태 (어떤 상태로부터 넘어왔는지)

    BOSS_SWINGING_GARBAGE_MAGNET curStage; // 현재 보스 진행 스테이지

    int curDir; // 현재 방향          // R 1, L 0
    int prevDir; // 1틱 전 방향       

private:
    int HaikuColCnt; // 하이쿠한테 맞은 횟수

    int Stage1Cnt; // 1스테이지  히트 카운트
    int Stage2Cnt; // 2스테이지 히트 카운트

public:
    wstring GetCurStateName() { return curStateName; }
    wstring GetPrevStateName() { return prevStateName; }
    BOSS_SWINGING_GARBAGE_MAGNET GetCurStage() { return curStage; }
    int GetCurDir() { return curDir; }
    int GetPrevDir() { return prevDir; }

    int GetHaikuColCnt() { return HaikuColCnt; }

public:
    void SetCurStateName(wstring _stateName) { curStateName = _stateName; }
    void SetPrevStateName(wstring _stateName) { prevStateName = _stateName; }
    void SetCurStage(BOSS_SWINGING_GARBAGE_MAGNET _stage) { curStage = _stage; }
    void SetCurDir(bool _dir) { curDir = _dir; }
    void SetPrevDir(bool _dir) { prevDir = _dir; }

public:
    virtual void tick() override;
    virtual void begin() override;

    virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CSwingingGarbageMagnetScript);
public:
    CSwingingGarbageMagnetScript();
    ~CSwingingGarbageMagnetScript();
};

