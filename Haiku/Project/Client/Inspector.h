#pragma once
#include "UI.h"

// GameObject 정보
//  - 컴포넌트
//  - 스크립트

// Asset 정보
//  - 각 에셋의 정보

#include <Engine/CGameObject.h>
#include <Engine/CAsset.h>

class ComponentUI;
class ScriptUI;
class AssetUI;
class ObjectController;

class Inspector :
    public UI
{
private:
    CGameObject*        m_TargetObject;
    Ptr<CAsset>         m_TargetAsset;

    ComponentUI*        m_arrComUI[(UINT)COMPONENT_TYPE::END];
    vector<ScriptUI*>   m_vecScriptUI;

    AssetUI*            m_arrAssetUI[(UINT)ASSET_TYPE::END];

    ObjectController*   m_ObjController;

public:
    virtual void tick() override;
    virtual void render_update() override;

public:
    void SetTargetObject(CGameObject* _Object);
    void SetTargetAsset(Ptr<CAsset> _Asset);

    CGameObject* GetTargetObject() { return m_TargetObject; }

    ObjectController* GetObjController() { return m_ObjController; }

    void DrawLayerUI();

private:
    void CreateChildUI();
    void CreateComponentUI();
    void CreateAssetUI();
    void ResizeScriptUI(UINT _Size);

public:
    Inspector();
    ~Inspector();
};

