#pragma once
#include <Engine/CScript.h>
class CIntroParticleScript :
    public CScript
{
private:
    tParticleModule m_PModule;
    float accTime;
    float duration;

    Vec4 originSpawnMaxScale;

public:
    virtual void begin() override;
    virtual void tick() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CIntroParticleScript);

public:
    CIntroParticleScript();
    ~CIntroParticleScript();
};

