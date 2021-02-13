#include "stdafx.h"
#include "RazorbeakMini.h"

RazorbeakMini::RazorbeakMini()
{
	transform->scale = { 0.011f, 0.011f, 0.011f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"sru_razorbeakmini");
	AddComponent(L"DynamicMesh", dmesh);
	dmesh->renderGroupID = RenderGroupID::Deferred;
	GameRenderer::Register(dmesh);
	anim->AttachToDynamicMesh(dmesh);

	anim->SetLoop((int)UnitState::IDLE1, true);
}

RazorbeakMini::~RazorbeakMini()
{
}
