#include "stdafx.h"
#include "Nexus.h"
#include "SphereCollider.h"
#include "DeferredStaticMeshRenderer.h"
#include "TurretFloatingBar.h"
#include "EndofgamePanel.h"

Nexus::Nexus()
{
	transform->position = { 0,0,0 };
	transform->scale = { 0.00015f, 0.00015f, 0.00015f, };

	StaticMesh* mesh = RenderManager::CloneStaticMesh(L"sruap_ordernexus");

	bar->SetOffset(Vector3(0, 2.5f, 0));
	
	AddComponent(L"StaticMesh", mesh);

	collider->SetRadius(2.6f);
	Engine::DeferredStaticMeshRenderer* renderer =
		(Engine::DeferredStaticMeshRenderer*)AddComponent<Engine::DeferredStaticMeshRenderer>(L"renderer");
	renderer->SetMesh(mesh);

	// 스탯
	stat->SetBaseValue(StatType::MaxHealth, 220.f);
	stat->SetBaseValue(StatType::Health, 220.f);
	stat->SetBaseValue(StatType::HealthRegen, 8.f);
}

Nexus::~Nexus()
{

}

void Nexus::Die()
{
	Building::Die();

	Unit::StopAll();
	UI::HideAllUI();

	Cursor::Show();

	if (team == Team::RED)
	{
		EndofgamePanel::GetInstance()->ShowVictory();
	}
	else
	{
		EndofgamePanel::GetInstance()->ShowDefeat();
	}
	SoundManager::GetInstance()->PlayOverlapSound(L"NexusDie0.ogg", SoundChannel::EFFECT);
}

void Nexus::OnDamaged(Unit* target, Skill* targetSkill, float* damage)
{
	bool invinCheck = false;

	for (auto& building : frontBuildingList)
	{
		if (!building->IsDead()) {
			invinCheck = true;
			break;
		}
	}
	
	if (invinCheck)
		*damage = 0.f;
}

void Nexus::SetTeam(Team _team)
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
