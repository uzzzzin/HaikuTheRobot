#include "pch.h"
#include "PrefabUI.h"

#include <Engine/CPrefab.h>

PrefabUI::PrefabUI()
	: AssetUI("Prefab", "##Prefab", ASSET_TYPE::PREFAB)
{
}

PrefabUI::~PrefabUI()
{
}

void PrefabUI::render_update()
{

	AssetUI::render_update();

	//Ptr<CPrefab> pPrefab = (CPrefab*)GetAsset().Get();

	/*ImGui::Text("Proto GameObject Name : ");
	ImGui::SameLine();
	ImGui::InputText("##ProtoName", (char*)pPrefab->GetName().c_str(), pPrefab->GetName().length(), ImGuiInputTextFlags_ReadOnly);

	*/

}