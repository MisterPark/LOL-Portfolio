#include "stdafx.h"
#include "Effect4.h"
#include "Random_Manager4.h"
#include "TimeManager.h"
#include "Cube.h"

PKH::Effect4::Effect4()
{
	moveSpeed = 2.5f;
	Frame = 0.f;
	EffectCode = 0;
}

PKH::Effect4::~Effect4()
{
}

void PKH::Effect4::Ready()
{
	transform->scale = { 0.5f, 0.5f, 0.5f };
	dir.x = -0.8f + 0.1f * (Random_Manager::Random4() % 16);
	dir.y = -0.8f + 0.1f * (Random_Manager::Random4() % 16);
	Cube* Comp = dynamic_cast<Cube*>(AddComponent<PKH::Cube>(L"Mesh"));
	if (EffectCode == 2) {
		Comp->SetColor(D3DCOLOR_XRGB(204, 62, 62));
	}
	else {
		Comp->SetColor(D3DCOLOR_XRGB(Random_Manager::Random4() % 255, Random_Manager::Random4() % 255, Random_Manager::Random4() % 255));
	}
}

void PKH::Effect4::Update()
{
	Frame += TimeManager::DeltaTime();
	if (Frame > 1.f)
		isDead = true;
	transform->scale.x -= Frame * 0.01f;
	transform->scale.y -= Frame * 0.01f;
	transform->position.x += dir.x * moveSpeed * TimeManager::DeltaTime();
	transform->position.y += dir.y * moveSpeed * TimeManager::DeltaTime();
}

