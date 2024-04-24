#pragma once
#include <Engine/CScript.h>

class CMainCameraScript :
    public CScript
{
private:
    MAIN_CAMERA_TYPE camType;

    CGameObject* Target;

    float TargetPosX;
    float TargetPosY;
    float TargetPosZ;

    Vec3 FixedPos;

public:
    MAIN_CAMERA_TYPE GetCamType() { return camType; }
    CGameObject* GetTraceTarget() { return Target; }
    Vec3 TargetPosXYX() { return Vec3(TargetPosX, TargetPosY, TargetPosZ); }

public:
    void SetCamType(MAIN_CAMERA_TYPE _type) { camType = _type; }
    void SetTraceTarget(CGameObject* _target) { Target = _target; }
    void SetTargetPosY(float _y) { TargetPosZ = _y; }
    void SetTargetPosZ(float _z) { TargetPosZ = _z; }
    void SetFixedPos(Vec3 _FixedPos) { FixedPos = _FixedPos; }

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CMainCameraScript);

public:
    CMainCameraScript();
    ~CMainCameraScript();
};
