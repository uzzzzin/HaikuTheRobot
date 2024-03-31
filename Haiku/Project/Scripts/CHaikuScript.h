#pragma once
#include "Engine\CScript.h"
class CHaikuScript :
    public CScript
{
private:
    int stamina; // ����
    int power; // �� ����� ���

private:
    bool curDir; // ���� ����           // true = L. false = R
    bool prevDir; // 1ƽ �� ����        // true = L. false = R

    wstring curStateName;  // ���� ����
    wstring prevStateName; // ���� ���� (� ���·κ��� �Ѿ�Դ���)

    wstring colPlatformName;

public:
    bool GetCurDir() { return curDir; }
    bool GetPrevDir() { return prevDir; }
    wstring GetCurStateName() { return curStateName;  }
    wstring GetPrevStateName() { return prevStateName; }
    wstring GetColPlatformName() { return colPlatformName; }

public:
    void SetCurDir(bool _dir) { curDir = _dir; }
    void SetPrevDir(bool _dir) { prevDir = _dir; }
    void SetCurStateName(wstring _stateName) { curStateName = _stateName; }
    void SetPrevStateName(wstring _stateName) { prevStateName = _stateName; }

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

