#include "stdafx.h"
#include "FloatingHPBar.h"

FloatingHPBar::FloatingHPBar()
{
	offset = { -0.2f,2.1f,-0.5f };

	mesh = (PKH::Rectangle*)AddComponent<PKH::Rectangle>(L"Mesh");
	mesh->SetTexture(L"bar_float (5)");
	mesh->SetBlendMode(BlendMode::ALPHA_TEST);

	Texture* tex = RenderManager::GetTexture(L"bar_float (5)");
	int w = tex->GetSpriteWidth();
	int h = tex->GetSpriteHeight();
	float scaleX = 0.8f;
	float scaleY = (float)h / w;
	transform->scale = { scaleX, scaleX *scaleY,1 };
}

FloatingHPBar::~FloatingHPBar()
{
	target = nullptr;
	mesh = nullptr;
}

void FloatingHPBar::Initialize()
{
}

void FloatingHPBar::Release()
{
}

void FloatingHPBar::Update()
{
	if (target->IsDead())
	{
		target = nullptr;
	}

	if (target != nullptr)
	{
		transform->position = target->transform->position + offset;
	}


	GameObject::Update();

	Billboard();
}

void FloatingHPBar::Render()
{
	Matrix ortho = Camera::main->GetOrthogonalMatrix();
	Matrix perspective = Camera::main->GetPerspectiveMatrix();

	RenderManager::GetDevice()->SetTransform(D3DTS_PROJECTION, &ortho);

	//RenderManager::DrawUI(textureKey, *transform, 0);
	Vector3 originCamPos = Camera::main->transform->position;
	Vector3 originCamLook = Camera::main->transform->look;

	Camera::main->transform->position = Vector3(0, 0, -1);
	Camera::main->transform->look = Vector3(0, 0, 1);

	GameObject::Render();

	Camera::main->transform->position = originCamPos;
	Camera::main->transform->look = originCamLook;


	RenderManager::GetDevice()->SetTransform(D3DTS_PROJECTION, &perspective);

}

void FloatingHPBar::SetTarget(GameObject * target)
{
	this->target = target;
}
