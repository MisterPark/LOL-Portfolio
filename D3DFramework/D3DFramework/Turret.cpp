#include "stdafx.h"
#include "Turret.h"
#include "SphereCollider.h"
#include "TurretFloatingBar.h"

Turret::Turret()
{
	transform->position = { 0,0,0 };
	transform->scale = { 0.00015f, 0.00015f, 0.00015f, };
	
	StaticMesh* mesh = RenderManager::CloneStaticMesh(L"turret_order");
	AddComponent(L"StaticMesh", mesh);

	collider->SetRadius(0.6f);

	bar = (TurretFloatingBar*)ObjectManager::GetInstance()->CreateObject<TurretFloatingBar>(Layer::UI);
	bar->SetTarget(this);

}

Turret::~Turret()
{
	bar = nullptr;
}

void Turret::SetTeam(Team _team)
{
	Unit::SetTeam(_team);
	
	if (_team == Team::BLUE)
	{
		bar->SetTextureHP(L"bar_float (5)");
	}
	else
	{
		bar->SetTextureHP(L"bar_float (2)");
	}
}
