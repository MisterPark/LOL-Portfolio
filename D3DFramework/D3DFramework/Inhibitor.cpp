#include "stdafx.h"
#include "Inhibitor.h"
#include "SphereCollider.h"
#include "DeferredStaticMeshRenderer.h"
#include "TurretFloatingBar.h"
#include "MinionSpawner.h"
#include "TestScene.h"
#include "AnnouncerPanel.h"
#include "KillCalloutPanel.h"

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

void Inhibitor::OnDeathBegin(Unit* _lastAttacker)
{
	if (_lastAttacker == nullptr) return;

	TestScene* scene = (TestScene*)SceneManager::GetCurrentScene();
	Unit* unit = scene->unitMap[(int)UnitID::Champ0];
	if (unit->team != this->team)
	{
		AnnouncerPanel::GetInstance()->AddAnnouncer(L"이제 적이 슈퍼미니언을 생성합니다", Team::BLUE, L"적의억제기를파괴했습니다.wav");
	}
	else
	{
		AnnouncerPanel::GetInstance()->AddAnnouncer(L"이제 슈퍼 미니언이 생성됩니다", Team::RED, L"억제기가파괴되었습니다.wav");
	}

	Team color = (team == Team::BLUE) ? Team::RED : Team::BLUE;
	KillCalloutPanel::GetInstance()->AddKillCallout(_lastAttacker->faceSquareTexkey, faceSquareTexkey, color);
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

	
}

void Inhibitor::OnRespawn()
{
	Building::OnRespawn();

	TestScene* scene = dynamic_cast<TestScene*>(SceneManager::GetCurrentScene());
	if (scene != nullptr)
	{
		Unit* player = scene->unitMap.find((int)UnitID::Champ0)->second;
		if (player->team == team)
		{
			PlaySoundAccordingCameraPosition(L"억제기가재생성되었습니다.wav", SoundChannel::PLAYER);
		}
		else
		{
			PlaySoundAccordingCameraPosition(L"적의억제기가재생성되었습니다.wav", SoundChannel::PLAYER);
		}

	}
	
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
