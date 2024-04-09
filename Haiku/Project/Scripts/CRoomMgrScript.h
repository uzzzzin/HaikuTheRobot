#pragma once
#include <Engine/CScript.h>
class CRoomMgrScript :
    public CScript
{
private:
    bool    bChanging;
    wstring curBeforeChangeRoomName;

    map<wstring, wstring>   map_connectedRoom;

public:
    void SetChanging(bool _b, wstring _name)
    { 
        bChanging = _b;
        curBeforeChangeRoomName = _name;
    }

public:
    void Change(wstring _name);

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CRoomMgrScript);

public:
    CRoomMgrScript();
    ~CRoomMgrScript();
};

