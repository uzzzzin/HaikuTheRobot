#pragma once
#include <Engine/CScript.h>
class CRoomMgrScript :
    public CScript
{
private:
    bool    bChanging;
    wstring curBeforeChangeRoomName;

    map<wstring, wstring>   map_connectedRoom;

    Vec3 curBossRoomPos; // 보스방에 들어갔을 때, 보스룸의 포지션 값을 카메라가 고정할 값으로 지정하기 위한..

public:
    void SetChanging(bool _b, wstring _name)
    { 
        bChanging = _b;
        curBeforeChangeRoomName = _name;
    }
    
    void SetCurBossRoomPos(Vec3 _pos) { curBossRoomPos = _pos; }

public:
    Vec3 GetCurBossRoomPos() { return curBossRoomPos; }

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

