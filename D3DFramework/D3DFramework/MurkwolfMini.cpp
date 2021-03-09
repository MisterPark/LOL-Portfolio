#include "stdafx.h"
#include "MurkwolfMini.h"

MurkwolfMini::MurkwolfMini()
{
	transform->scale = { 0.013f, 0.013f, 0.013f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"sru_murkwolfmini_left");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	anim->SetLoop((int)State::IDLE1, true);
}

MurkwolfMini::~MurkwolfMini()
{
}
