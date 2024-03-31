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

