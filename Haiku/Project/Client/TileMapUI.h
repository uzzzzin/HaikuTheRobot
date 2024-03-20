#pragma once
#include "ComponentUI.h"

class TileMapUI :
    public ComponentUI
{
public:

    bool bStartBtn;

    Ptr<CTexture> m_curAtlasTex;

    float realWidth; // m_curAtlasTex->GetWidth();
    float realHeight; // m_curAtlasTex->GetHeight();

    int gridWidthCnt;
    int gridHeightCnt;

    bool bSetGrid;

    // tilemap°Íµé
    int m_faceX;
    int m_faceY;

public:
    Ptr<CTexture> SetImageForMakeAnim();

    virtual void render_update() override;

public:
    TileMapUI();
    ~TileMapUI();
};

