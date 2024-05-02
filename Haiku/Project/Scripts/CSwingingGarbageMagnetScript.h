#pragma once
#include <Engine/CScript.h>
class CSwingingGarbageMagnetScript :
    public CScript
{
private:
    wstring curStateName;  // ���� ����
    wstring prevStateName; // ���� ���� (� ���·κ��� �Ѿ�Դ���)

    BOSS_SWINGING_GARBAGE_MAGNET curStage; // ���� ���� ���� ��������

    int curDir; // ���� ����          // R 1, L 0
    int prevDir; // 1ƽ �� ����       

private:
    int HaikuColCnt; // ���������� ���� Ƚ��

    int Stage1Cnt; // 1��������  ��Ʈ ī��Ʈ
    int Stage2Cnt; // 2�������� ��Ʈ ī��Ʈ

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

