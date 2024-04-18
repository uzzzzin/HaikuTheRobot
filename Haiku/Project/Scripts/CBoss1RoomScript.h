#pragma once
#include <Engine\CScript.h>

class CBoss1RoomScript :
    public CScript
{
private:
    bool bIntroDoor;

public:
    virtual void tick() override;
    virtual void begin() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CBoss1RoomScript);
public:
    CBoss1RoomScript();
    ~CBoss1RoomScript();
};

