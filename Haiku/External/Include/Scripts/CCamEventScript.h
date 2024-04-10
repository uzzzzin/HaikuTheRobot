#pragma once
#include <Engine\CScript.h>

enum class CAM_EFFECT
{
    FADE_IN,
    FADE_OUT,
    SHAKE,
    NONE
};

struct FCamEvent
{
    CAM_EFFECT	Type;
    float		Duration;
    int		    ShakingSize;
};

class CCamEventScript :
    public CScript
{
private:
    list<FCamEvent>		m_EventList;
    CAM_EFFECT          m_CurEvent; // 현재 카메라 상태

    bool                m_EventExecute; // 이벤트가 수행중인지

    // FadeIn, Out
    CGameObject*        m_Directional_Light;
    Vec4                m_Origin_Ambient;

    // Shake
    Vec3                m_Origin_MainCamPos;

    float               m_CurEventAccTime;

public:
    CAM_EFFECT GetCurCamEffect() { return m_CurEvent; }

private:
    void FadeIn_Imp(FCamEvent _event);
    void FadeOut_Imp(FCamEvent _event);
    void Shake_Imp(FCamEvent _event);

public:
    void FadeIn(float _time);
    void FadeOut(float _time);
    void Shake(float _time, int _size);

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CCamEventScript);


public:
    CCamEventScript();
    ~CCamEventScript();
};

