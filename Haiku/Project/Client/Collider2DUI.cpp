#include "pch.h"
#include "Collider2DUI.h"

#include <Engine/CCollider2D.h>

Collider2DUI::Collider2DUI()
	: ComponentUI("Collider2D", "##Collider2D", COMPONENT_TYPE::COLLIDER2D)
{
	SetSize(ImVec2(0.f, 180.f));
	SetComopnentTitle("Collider2D");
}

Collider2DUI::~Collider2DUI()
{
}

void Collider2DUI::render_update()
{
	if (nullptr == GetTargetObject())
		return;

	ComponentUI::render_update();

	Vec3 vOffset = GetTargetObject()->Collider2D()->GetOffset();
	Vec3 vScale = GetTargetObject()->Collider2D()->GetScale();
	float fRotation = GetTargetObject()->Collider2D()->GetRotationZ();
	fRotation = fRotation / XM_PI * 100.f;
	bool bAbsolute = GetTargetObject()->Collider2D()->IsAbsolute();

	Vec3 FinalPos = GetTargetObject()->Collider2D()->GetFinalPos();

	ImGui::Text("Offset"); 
	ImGui::SameLine();  
	ImGui::DragFloat3("##vOffset", vOffset);

	ImGui::Text("Scale   ");
	ImGui::SameLine();
	ImGui::DragFloat3("##vScale", vScale);

	ImGui::Text("Rotation(Z)");
	ImGui::SameLine();
	ImGui::DragFloat("##RotationZ", &fRotation);

	ImGui::Text("Absolute");
	ImGui::SameLine();
	ImGui::Checkbox("Absolute", &bAbsolute);

	GetTargetObject()->Collider2D()->SetOffset(vOffset);
	GetTargetObject()->Collider2D()->SetScale(vScale);
	fRotation = (fRotation / 100.f) * XM_PI;
	GetTargetObject()->Collider2D()->SetRotationZ(fRotation);
	GetTargetObject()->Collider2D()->SetAbsolute(bAbsolute);

	ImGui::Text("FinalPos");
	ImGui::SameLine();
	ImGui::InputFloat3("##TextureWidth", FinalPos, 0, ImGuiInputTextFlags_ReadOnly);






}