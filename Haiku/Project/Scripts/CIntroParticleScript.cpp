#include "pch.h"
#include "CIntroParticleScript.h"

#include <Engine/CParticleSystem.h>

CIntroParticleScript::CIntroParticleScript()
	: CScript(INTROPARTICLESCRIPT)
{
}

CIntroParticleScript::~CIntroParticleScript()
{
}


void CIntroParticleScript::begin()
{
	tParticleModule Intro = {};
	//GetOwner()->ParticleSystem()->SetParticleModule(Intro);
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
