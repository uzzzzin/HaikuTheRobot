#pragma once
#include "ComponentUI.h"
class ParticleSystemUI :
    public ComponentUI
{
    virtual void render_update() override;

public:
    ParticleSystemUI();
    ~ParticleSystemUI();
};

