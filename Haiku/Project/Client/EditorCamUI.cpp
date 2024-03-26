#include "pch.h"
#include "EditorCamUI.h"
#include "CGameObjectEx.h"

#include <Engine/CCamera.h>
#include <Engine/CRenderMgr.h>


EditorCamUI::EditorCamUI()
	: UI("EditorCamUI", "##EditorCam")
{
	m_EditorCam = CRenderMgr::GetInst()->GetEditorCam()->Camera();
}

EditorCamUI::~EditorCamUI()
{
}

void EditorCamUI::render_update()
{
	Vec3 vPos = m_EditorCam->Transform()->GetRelativePos();
	ImGui::Text("Position"); ImGui::SameLine();  ImGui::DragFloat3("##Position", vPos);
	m_EditorCam->Transform()->SetRelativePos(vPos);

	float fScale = m_EditorCam->GetScale();
	ImGui::Text("Scale"); ImGui::SameLine();  ImGui::InputFloat("##Scale", &fScale);
	if (fScale != 0.f)
	{
		m_EditorCam->SetScale(fScale);
	}

}