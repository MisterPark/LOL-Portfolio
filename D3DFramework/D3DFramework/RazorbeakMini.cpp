#include "stdafx.h"
#include "RazorbeakMini.h"

RazorbeakMini::RazorbeakMini()
{
	transform->scale = { 0.011f, 0.011f, 0.011f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"sru_razorbeakmini");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);

	KST::SkinnedMeshRenderer* renderer = new KST::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	anim->SetLoop((int)UnitState::IDLE1, true);
}

RazorbeakMini::~RazorbeakMini()
{
}
