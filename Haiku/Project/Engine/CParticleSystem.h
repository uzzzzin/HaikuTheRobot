#pragma once
#include "CRenderComponent.h"

#include "CParticleUpdate.h"

class CStructuredBuffer;

class CParticleSystem :
    public CRenderComponent
{
private:
    CStructuredBuffer*      m_ParticleBuffer;
    UINT                    m_MaxParticleCount;

    tParticleModule         m_Module;
    CStructuredBuffer*      m_ParticleModuleBuffer;

    CStructuredBuffer*      m_SpawnCountBuffer;

    Ptr<CParticleUpdate>    m_CSParticleUpdate;

    Ptr<CTexture>           m_ParticleTex;

    float                   m_Time;

public:
    tParticleModule GetParticleModule() { return m_Module; }

public:
    void SetParticleModule(tParticleModule _module) { m_Module = _module; }
    void SetParticleTexture(wstring _path) 
    { 
        m_ParticleTex = CAssetMgr::GetInst()->Load<CTexture>(_path,_path);
    }

public:
    virtual void UpdateData() override;
    virtual void finaltick() override;
    virtual void render() override;

    virtual void SaveToFile(FILE* _File) override;
    virtual void LoadFromFile(FILE* _File) override;
    CLONE(CParticleSystem);
public:
    CParticleSystem();
    CParticleSystem(const CParticleSystem& _OriginParticle);
    ~CParticleSystem();
};

