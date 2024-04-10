#pragma once
#include <Engine\CScript.h>

enum class CAM_EFFECT
{
    FADE_IN,
    FADE_OUT,
    SHAKE
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

    bool                m_EventExecute; // �̺�Ʈ�� ����������

    CGameObject*        m_Directional_Light; // ���̵��ξƿ� �����Ҷ�..
    Vec4                m_Origin_Ambient;

    float               m_CurEventAccTime;



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

