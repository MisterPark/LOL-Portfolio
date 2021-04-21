#include "stdafx.h"
#include "Effect_Garen_R.h"

Effect_Garen_R::Effect_Garen_R()
{
	GetComponent(L"Mesh")->visible = false;
	GetComponent(L"renderer")->visible = false;

	transform->scale = { 0.01f, 0.01f, 0.01f };
	//transform->eulerAngles.x = D3DXToRadian(180.f);

	CustomMesh* mesh = RenderManager::CloneCustomMesh(L"garen_base_r_sword_plane");
	AddComponent(L"CustomMesh", mesh);

	ForwardRenderer* renderer = new ForwardRenderer{ this, L"./forward.fx" };
	renderer->SetMesh(mesh);
	renderer->SetDiffuseTextureParam("g_diffuseTexture");
	AddComponent(L"renderer2", renderer);

	mesh->SetSubsetTexture(L"garen_base_r_sword_plane");
}

Effect_Garen_R::~Effect_Garen_R()
{
}

void Effect_Garen_R::PostUpdate()
{
	StickToTarget();
	GameObject::PostUpdate();
}

void Effect_Garen_R::Update()
{
	GameObject::Update();
	
	//auto sword = dynamic_cast<CustomMesh*>(GetComponent(L"CustomMesh"));
	//transform->position.y -= 0.1f;
	// 1.098 시전
	// 1.266 0.1초 꽂힘
	// 1.665 0.8초까지 바닥에 안보일 정도로 박힘
	// 1.888 0.8초 검 나타남
	// 1.932 0.9초 사라지는 효과
	// 2.500 1.4초 사라짐
}
