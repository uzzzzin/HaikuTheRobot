#include "pch.h"
#include "MovementUI.h"

MovementUI::MovementUI()
	: ComponentUI("Movement", "##Movement", COMPONENT_TYPE::MOVEMENT)
{
	SetSize(ImVec2(0.f, 100.f));
	SetComopnentTitle("Movement");
}

MovementUI::~MovementUI()
{
}

void MovementUI::render_update()
{
	if (nullptr == GetTargetObject())
		return;

	ComponentUI::render_update();
}
