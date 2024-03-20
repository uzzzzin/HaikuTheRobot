#include "pch.h"
#include "TileMapUI.h"

#include <Engine/CAssetMgr.h>


TileMapUI::TileMapUI()
	: ComponentUI("TileMap", "##TileMap", COMPONENT_TYPE::TILEMAP)
{
	SetSize(ImVec2(0.f, 100.f));
	SetComopnentTitle("TileMap");
}

TileMapUI::~TileMapUI()
{
}

void TileMapUI::render_update()
{
	if (nullptr == GetTargetObject())
		return;

	ComponentUI::render_update();
}