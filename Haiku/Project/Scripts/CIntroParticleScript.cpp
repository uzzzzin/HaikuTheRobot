#include "pch.h"
#include "CIntroParticleScript.h"

#include <Engine/CLevelMgr.h>
#include <Engine/CLevel.h>

#include "CCamEventScript.h"

#include <Engine/CParticleSystem.h>

#include <States/CHaikuStartState.h>

CIntroParticleScript::CIntroParticleScript()
	: CScript(INTROPARTICLESCRIPT)
	, m_PModule()
	, accTime(0)
{
}

CIntroParticleScript::~CIntroParticleScript()
{
}


void CIntroParticleScript::begin()
{
	//GetStateDuration();

	CGameObject* Haiku = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"Haiku");
	CHaikuStartState* pState = (CHaikuStartState*)Haiku->StateMachine()->GetDynamicFSM()->FindState(L"Start");//->GetStateDuration();
	duration = pState->GetStateDuration();

	m_PModule = GetOwner()->ParticleSystem()->GetParticleModule();
	originSpawnMaxScale = m_PModule.vSpawnMaxScale;

	CGameObject* MainCam = CLevelMgr::GetInst()->GetCurrentLevel()->FindObjectByName(L"MainCamera");
	MainCam->GetScript<CCamEventScript>()->Shake(duration, 2);
}

void CIntroParticleScript::tick()
{
	if (accTime < duration)
	{
		float fRatio = accTime / duration;
		float fValue = 1 - fRatio;
		m_PModule.vSpawnMaxScale = originSpawnMaxScale * fValue;
	}
	else
	{
		m_PModule.arrModuleCheck[(UINT)PARTICLE_MODULE::SPAWN] = 0;

	}

	GetOwner()->ParticleSystem()->SetParticleModule(m_PModule);
	accTime += DT;
}

void CIntroParticleScript::SaveToFile(FILE* _File)
{
}

void CIntroParticleScript::LoadFromFile(FILE* _File)
{
}
