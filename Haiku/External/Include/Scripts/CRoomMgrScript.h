#pragma once
#include <Engine/CScript.h>

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

class CRoomMgrScript :
    public CScript
{
private:
    bool    bChanging;
    wstring curBeforeChangeRoomName;

    wstring curRoomName;

    map<wstring, wstring>   map_connectedRoom;

public:
    void SetChanging(bool _b, wstring _name)
    { 
        bChanging = _b;
        curBeforeChangeRoomName = _name;
    }

public:
    CGameObject* GetCurRoom() { return CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(curRoomName);}
    //wstring GetCurRoomName() { return curRoomName; }

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

