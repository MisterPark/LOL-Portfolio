#include "stdafx.h"
#include "Pointing.h"
#include "Animation.h"

Pointing::Pointing()
{
	transform->scale = { 0.08f,0.08f, 0.08f };
	transform->position.y = -0.1f;
	DynamicMesh* dmesh = RenderManager::CloneDynamicMesh(L"pointing");
	AddComponent(L"DynamicMesh", dmesh);
	Engine::SkinnedMeshRenderer* renderer = new Engine::SkinnedMeshRenderer(this);
	renderer->SetMesh(dmesh);
	AddComponent(L"renderer", renderer);
	Animation* anim = (Animation*)AddComponent<Animation>(L"Animation");
	anim->AttachToDynamicMesh(dmesh);
	anim->SetSpeed(0, 1.5f);
}

Pointing::~Pointing()
{
}

void Pointing::Initialize()
{
}

void Pointing::Release()
{
}

void Pointing::Update()
{
	Animation* anim = (Animation*)GetComponent(L"Animation");
	if (anim->IsFrameEnd())
	{
		anim->Stop();
	}
	GameObject::Update();
	
}

void Pointing::Show()
{
	Animation* anim = (Animation*)GetComponent(L"Animation");
	anim->Reset();
	anim->Resume();
	GameObject::Show();
}
