#include "pch.h"
#include "ParticleSystemUI.h"

ParticleSystemUI::ParticleSystemUI() 
	: ComponentUI("ParticleSystem", "##ParticleSystem", COMPONENT_TYPE::PARTICLESYSTEM)
{
	SetSize(ImVec2(0.f, 100.f));
	SetComopnentTitle("ParticleSystem");
}

ParticleSystemUI::~ParticleSystemUI()
{
}

void ParticleSystemUI::render_update()
{
	if (nullptr == GetTargetObject())
		return;

	ComponentUI::render_update();
}
