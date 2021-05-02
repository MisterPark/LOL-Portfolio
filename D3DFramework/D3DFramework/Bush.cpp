#include "stdafx.h"
#include "Bush.h"
#include "SphereCollider.h"

Bush::Bush()
{
	transform->scale = { 0.014f, 0.014f, 0.014f, };
	transform->eulerAngles.y = D3DXToRadian(180.f);
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"bush");
	AddComponent(L"DynamicMesh", dmesh);

	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);

	Animation* anim = (Animation*)AddComponent<Animation>(L"Animation");
	anim->AttachToDynamicMesh(dmesh);

	SphereCollider* collider = (SphereCollider*)AddComponent<SphereCollider>(L"SphereCollider");
	collider->SetRadius(0.5f);
	collider->center = { 0.f,1.f,0.f };
}

Bush::~Bush()
{
}

void Bush::Initialize()
{
}

void Bush::Release()
{
}

void Bush::Update()
{
	GameObject::Update();
}
