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

    // tilemap�͵�
    int m_faceX;
    int m_faceY;

    float TileRenderSizeX;
    float TileRenderSizeY;

    Vec2 TileRenderSize;

    // �ȷ�Ʈ �귯��
    int curBrushIdxCol; // x
    int curBrushIdxRow; // y

    // �귯���� ��ĥ �� �غ� �Ϸ�Ǿ��ٴ�
    bool bReady; // bReadyToColor

public:
    Ptr<CTexture> SetImageForMakeAnim();

    Vec3 ToRelativePos(Vec3 _curWindowPos);

    virtual void render_update() override;

public:
    TileMapUI();
    ~TileMapUI();
};

