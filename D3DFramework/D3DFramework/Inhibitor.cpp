#include "stdafx.h"
#include "Inhibitor.h"
#include "SphereCollider.h"
#include "DeferredStaticMeshRenderer.h"
#include "TurretFloatingBar.h"
#include "MinionSpawner.h"
#include "TestScene.h"

Inhibitor::Inhibitor()
{
	transform->position = { 0,0,0 };
	transform->scale = { 0.00018f, 0.00018f, 0.00018f, };
	spawnDelay = 300.f;
	bar->SetOffset(Vector3(0, 2.5f, 0));

	StaticMesh* mesh = RenderManager::CloneStaticMesh(L"sruap_orderinhibitor");
	AddComponent(L"StaticMesh", mesh);

	collider->SetRadius(1.5f);
	Engine::DeferredStaticMeshRenderer* renderer =
		(Engine::DeferredStaticMeshRenderer*)AddComponent<Engine::DeferredStaticMeshRenderer>(L"renderer");
	renderer->SetMesh(mesh);
	SetSpawnFlag(true);

	// 스탯
	stat->SetBaseValue(StatType::MaxHealth, 620.f);
	stat->SetBaseValue(StatType::Health, 620.f);
	stat->SetBaseValue(StatType::HealthRegen, 8.f);
}

Inhibitor::~Inhibitor()
{
	bar = nullptr;
}

void Inhibitor::SetTeam(Team _team)
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

void Inhibitor::Die()
{
	Unit::Die();
	SetSpawnFlag(true);
	if(unitID == (int)UnitID::InhibitorBlueBot)
		MinionSpawner::SetMinionPhase(SpawnLane::BlueBot, PhaseType::SMMMCCC);
	else if (unitID == (int)UnitID::InhibitorBlueMid)
		MinionSpawner::SetMinionPhase(SpawnLane::BlueMid, PhaseType::SMMMCCC);
	else if (unitID == (int)UnitID::InhibitorBlueTop)
		MinionSpawner::SetMinionPhase(SpawnLane::BlueTop, PhaseType::SMMMCCC);
	else if (unitID == (int)UnitID::InhibitorRedBot)
		MinionSpawner::SetMinionPhase(SpawnLane::RedBot, PhaseType::SMMMCCC);
	else if (unitID == (int)UnitID::InhibitorRedMid)
		MinionSpawner::SetMinionPhase(SpawnLane::RedMid, PhaseType::SMMMCCC);
	else if (unitID == (int)UnitID::InhibitorRedBot)
		MinionSpawner::SetMinionPhase(SpawnLane::RedBot, PhaseType::SMMMCCC);

	if (team == Team::BLUE) {
		PhaseType botPhase = MinionSpawner::GetSpawnPhase(SpawnLane::BlueBot);
		PhaseType midPhase = MinionSpawner::GetSpawnPhase(SpawnLane::BlueMid);
		PhaseType topPhase = MinionSpawner::GetSpawnPhase(SpawnLane::BlueTop);
		if (botPhase == PhaseType::SMMMCCC && midPhase == PhaseType::SMMMCCC && topPhase == PhaseType::SMMMCCC) {
			MinionSpawner::SetMinionPhase(SpawnLane::BlueBot, PhaseType::SSMMMCCC);
			MinionSpawner::SetMinionPhase(SpawnLane::BlueMid, PhaseType::SSMMMCCC);
			MinionSpawner::SetMinionPhase(SpawnLane::BlueTop, PhaseType::SSMMMCCC);
		}
	}
	else if (team == Team::RED) {
		PhaseType botPhase = MinionSpawner::GetSpawnPhase(SpawnLane::RedBot);
		PhaseType midPhase = MinionSpawner::GetSpawnPhase(SpawnLane::RedMid);
		PhaseType topPhase = MinionSpawner::GetSpawnPhase(SpawnLane::RedTop);
		if (botPhase == PhaseType::SMMMCCC && midPhase == PhaseType::SMMMCCC && topPhase == PhaseType::SMMMCCC) {
			MinionSpawner::SetMinionPhase(SpawnLane::RedBot, PhaseType::SSMMMCCC);
			MinionSpawner::SetMinionPhase(SpawnLane::RedMid, PhaseType::SSMMMCCC);
			MinionSpawner::SetMinionPhase(SpawnLane::RedTop, PhaseType::SSMMMCCC);
		}
	}

	TestScene* scene = dynamic_cast<TestScene*>(SceneManager::GetCurrentScene());
	if (scene != nullptr)
	{
		Unit* player = scene->unitMap.find((int)UnitID::Champ0)->second;
		if (player->team == team)
			SoundManager::GetInstance()->PlayOverlapSound(L"억제기가파괴되었습니다.wav", SoundChannel::PLAYER);
		else
			SoundManager::GetInstance()->PlayOverlapSound(L"적의억제기를파괴했습니다.wav", SoundChannel::PLAYER);
	}
	
}

void Inhibitor::UpdateSpawn()
{
	float dt = Time::DeltaTime();
	if (spawnFlag)
	{
		spawnTick += dt;
		if (spawnTick > spawnDelay)
		{
			if (isDead) {
				TestScene* scene = dynamic_cast<TestScene*>(SceneManager::GetCurrentScene());
				if (scene != nullptr)
				{
					Unit* player = scene->unitMap.find((int)UnitID::Champ0)->second;
					if (player->team == team)
						SoundManager::GetInstance()->PlayOverlapSound(L"억제기가재생성되었습니다.wav", SoundChannel::PLAYER);
					else
						SoundManager::GetInstance()->PlayOverlapSound(L"적의억제기가재생성되었습니다.wav", SoundChannel::PLAYER);
				}
			}
			spawnFlag = false;
			spawnTick = 0.f;
			attackTarget = nullptr;
			lastAttacker = nullptr;
			collider->enable = true;
			float maxHP = stat->GetValue(StatType::MaxHealth);
			stat->SetBaseValue(StatType::Health, maxHP);
			transform->position = spawnPosition;
			isDead = false;
			anim->Resume();
			Show();
			OnRespawn();

			if (team == Team::BLUE) {
				PhaseType botPhase = MinionSpawner::GetSpawnPhase(SpawnLane::BlueBot);
				if (botPhase == PhaseType::SSMMMCCC) {
					MinionSpawner::SetMinionPhase(SpawnLane::BlueBot, PhaseType::SMMMCCC);
					MinionSpawner::SetMinionPhase(SpawnLane::BlueMid, PhaseType::SMMMCCC);
					MinionSpawner::SetMinionPhase(SpawnLane::BlueTop, PhaseType::SMMMCCC);
				}
			}
			else if (team == Team::RED) {
				PhaseType botPhase = MinionSpawner::GetSpawnPhase(SpawnLane::RedBot);
				if (botPhase == PhaseType::SSMMMCCC) {
					MinionSpawner::SetMinionPhase(SpawnLane::RedBot, PhaseType::SMMMCCC);
					MinionSpawner::SetMinionPhase(SpawnLane::RedMid, PhaseType::SMMMCCC);
					MinionSpawner::SetMinionPhase(SpawnLane::RedTop, PhaseType::SMMMCCC);
				}
			}

			if (unitID == (int)UnitID::InhibitorBlueBot)
				MinionSpawner::SetMinionPhase(SpawnLane::BlueBot, PhaseType::MMMCCC);
			else if (unitID == (int)UnitID::InhibitorBlueMid)
				MinionSpawner::SetMinionPhase(SpawnLane::BlueMid, PhaseType::MMMCCC);
			else if (unitID == (int)UnitID::InhibitorBlueTop)
				MinionSpawner::SetMinionPhase(SpawnLane::BlueTop, PhaseType::MMMCCC);
			else if (unitID == (int)UnitID::InhibitorRedBot)
				MinionSpawner::SetMinionPhase(SpawnLane::RedBot, PhaseType::MMMCCC);
			else if (unitID == (int)UnitID::InhibitorRedMid)
				MinionSpawner::SetMinionPhase(SpawnLane::RedMid, PhaseType::MMMCCC);
			else if (unitID == (int)UnitID::InhibitorRedBot)
				MinionSpawner::SetMinionPhase(SpawnLane::RedBot, PhaseType::MMMCCC);

		}
	}
}
