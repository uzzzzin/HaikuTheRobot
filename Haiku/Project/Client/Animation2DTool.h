#pragma once
#include "UI.h"

#include <Engine/CTexture.h>
#include <Engine/CAnim.h>

// Animation2D Tool
// - ��Ʋ�� �̹��� �ؽ��� �ҷ�����.
// - �ؽ��ĸ� ���� �ִϸ��̼��� ����ų� ����.
// - ���� �ִϸ��̼��� ���̺�, �ε� ����.

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

