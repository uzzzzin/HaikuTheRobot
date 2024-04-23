#pragma once
#include <Engine\CScript.h>

class CTraceCameraScript :
    public CScript
{
private:
    CGameObject* Target;

    float TargetPosX;
    float TargetPosY;
    float TargetPosZ;

    Vec3 FixedPos; // Ÿ���� nullptr �� ���� ��� ������ ���� ���� // ī�޶��� ���� ����.. !

public:
    void SetTraceTarget(CGameObject* _target) { Target = _target; }
    void SetFixedPos(Vec3 _FixedPos) { FixedPos = _FixedPos; }

public:
    CGameObject* GetTraceTarget() { return Target; }

public:
    virtual void tick() override;
    virtual void begin() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CTraceCameraScript);
public:
    CTraceCameraScript();
    ~CTraceCameraScript();
};

