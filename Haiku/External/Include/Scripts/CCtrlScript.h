#pragma once
#include <Engine\CScript.h>

class CCtrlScript :
    public CScript
{
public:
    vector<CGameObject*> AllObjects;

private:
    // µð¹ö±ë ²°´Ù Å°´Â
    bool curCtrlColliderDebug;
    bool prevCtrlColliderDebug;
public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CCtrlScript);

public:
    CCtrlScript();
    ~CCtrlScript();
};

