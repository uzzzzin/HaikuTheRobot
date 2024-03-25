#pragma once
#include "UI.h"

#include <Engine\CMaterial.h>
#include <Engine\CTexture.h>
#include <Engine/CGraphicsShader.h>

class MtrlEditorUI :
    public UI
{
private:
    Ptr<CMaterial>              m_TargetMtrl;
    
    string                      m_MtrlPath;
    string                      m_ShaderName;

    // ��Į�� �Ķ����
    int                         m_IntArr[4];
    float                       m_FloatArr[4];
    Vec2                        m_V2Arr[4];
    float                       m_V4Arr[4][4];

    // �Ķ���� ��ũ����
    string                      m_INT_Desc[4];
    string                      m_FLOAT_Desc[4];
    string                      m_V2_Desc[4];
    string                      m_V4_Desc[4];
    string                      m_TEX_Desc[6];

    // Tex Path
    string                      m_TEX_PATH[6];

    // UI ���� ��
    int                         m_DescSize;
    int                         m_InputSize;

public:
    virtual void render_update() override;

private:
    void Save();
    void Load();
    void Create();
    void Reset();

public:
    MtrlEditorUI();
    ~MtrlEditorUI();
};

