#pragma once
#include "ComponentUI.h"
class ParticleSystemUI :
    public ComponentUI
{
private:
    void SetParticleTexture();

public:
    virtual void render_update() override;

public:
    ParticleSystemUI();
    ~ParticleSystemUI();
};

