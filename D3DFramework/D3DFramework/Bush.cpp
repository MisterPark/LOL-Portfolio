﻿#include "stdafx.h"
#include "Bush.h"
Bush::Bush()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"bush");
	AddComponent(L"DynamicMesh", dmesh);
	anim->AttachToDynamicMesh(dmesh);
	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);
}

Bush::~Bush()
{
}
