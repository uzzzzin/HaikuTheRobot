#pragma once
#include <Engine/CScript.h>
class CSwingingGarbageMagnetScript :
    public CScript
{
private:
    wstring curStateName;  // ���� ����
    wstring prevStateName; // ���� ���� (� ���·κ��� �Ѿ�Դ���)

public:
    wstring GetCurStateName() { return curStateName; }
    wstring GetPrevStateName() { return prevStateName; }

public:
    void SetCurStateName(wstring _stateName) { curStateName = _stateName; }
    void SetPrevStateName(wstring _stateName) { prevStateName = _stateName; }

public:
    virtual void tick() override;
    virtual void begin() override;

    //virtual void BeginOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    //virtual void Overlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);
    //virtual void EndOverlap(CCollider2D* _Collider, CGameObject* _OtherObj, CCollider2D* _OtherCollider);

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CSwingingGarbageMagnetScript);
public:
    CSwingingGarbageMagnetScript();
    ~CSwingingGarbageMagnetScript();
};

