#include "stdafx.h"
#include "RazorbeakMini.h"

RazorbeakMini::RazorbeakMini()
{
	transform->scale = { 0.011f, 0.011f, 0.011f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"sru_razorbeakmini");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	anim->SetLoop((int)State::IDLE1, true);
}

RazorbeakMini::~RazorbeakMini()
{
}
