#pragma once
#include "UI.h"

class EditorCamUI :
    public UI
{
    class CCamera* m_EditorCam;

public:
    virtual void render_update() override;

public:
    EditorCamUI();
    ~EditorCamUI();
};

