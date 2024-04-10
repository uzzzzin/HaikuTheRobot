#include "pch.h"
#include "CIntroParticleScript.h"

#include <Engine/CParticleSystem.h>

CIntroParticleScript::CIntroParticleScript()
	: CScript(INTROPARTICLESCRIPT)
	, m_PModule()
{
}

CIntroParticleScript::~CIntroParticleScript()
{
}


void CIntroParticleScript::begin()
{
	//GetOwner()->ParticleSystem()->SetParticleModule(m_PModule);
}

void CIntroParticleScript::tick()
{
}

void CIntroParticleScript::SaveToFile(FILE* _File)
{
}

void CIntroParticleScript::LoadFromFile(FILE* _File)
{
}
