#pragma once
#include "UI.h"

#include <Engine/CTexture.h>
#include <Engine/CAnim.h>

// Animation2D Tool
// - 아틀라스 이미지 텍스쳐 불러오기.
// - 텍스쳐를 통해 애니메이션을 만들거나 수정.
// - 만든 애니메이션의 세이브, 로드 진행.

class Animation2DTool :
    public UI
{

public:

    Ptr<CTexture> curAtlasTex;
    Ptr<CTexture> curFrameTex;

    float realWidth;
    float realHeight;

    int atlasDiv;

    int gridWidthCnt;
    int gridHeightCnt;

    bool setGrid;
    bool setClickedRect;

    vector<ImVec2> addRectPos;
    vector<tAnimFrm> animFrms;


public:
    void SaveAnimation2D();
    void LoadAnimation2D();

public:
    virtual void tick() override;
    virtual void render_update() override;

public:
    Animation2DTool();
    ~Animation2DTool();
};

