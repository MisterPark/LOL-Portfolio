#include "stdafx.h"
#include "MinionSpawner.h"
#include "AllMinion.h"
#include "MinionAI.h"

MinionSpawner* self = nullptr;

MinionSpawner::MinionSpawner()
{
	// 미니언 페이즈 세팅
	phase[(int)PhaseType::MMMCCC].push_back(MinionType::Melee);
	phase[(int)PhaseType::MMMCCC].push_back(MinionType::Melee);
	phase[(int)PhaseType::MMMCCC].push_back(MinionType::Melee);
	phase[(int)PhaseType::MMMCCC].push_back(MinionType::Caster);
	phase[(int)PhaseType::MMMCCC].push_back(MinionType::Caster);
	phase[(int)PhaseType::MMMCCC].push_back(MinionType::Caster);

	phase[(int)PhaseType::MMMSCCC].push_back(MinionType::Melee);
	phase[(int)PhaseType::MMMSCCC].push_back(MinionType::Melee);
	phase[(int)PhaseType::MMMSCCC].push_back(MinionType::Melee);
	phase[(int)PhaseType::MMMSCCC].push_back(MinionType::Siege);
	phase[(int)PhaseType::MMMSCCC].push_back(MinionType::Caster);
	phase[(int)PhaseType::MMMSCCC].push_back(MinionType::Caster);
	phase[(int)PhaseType::MMMSCCC].push_back(MinionType::Caster);

	phase[(int)PhaseType::SMMMCCC].push_back(MinionType::Super);
	phase[(int)PhaseType::SMMMCCC].push_back(MinionType::Melee);
	phase[(int)PhaseType::SMMMCCC].push_back(MinionType::Melee);
	phase[(int)PhaseType::SMMMCCC].push_back(MinionType::Melee);
	phase[(int)PhaseType::SMMMCCC].push_back(MinionType::Caster);
	phase[(int)PhaseType::SMMMCCC].push_back(MinionType::Caster);
	phase[(int)PhaseType::SMMMCCC].push_back(MinionType::Caster);

	phase[(int)PhaseType::SSMMMCCC].push_back(MinionType::Super);
	phase[(int)PhaseType::SSMMMCCC].push_back(MinionType::Super);
	phase[(int)PhaseType::SSMMMCCC].push_back(MinionType::Melee);
	phase[(int)PhaseType::SSMMMCCC].push_back(MinionType::Melee);
	phase[(int)PhaseType::SSMMMCCC].push_back(MinionType::Melee);
	phase[(int)PhaseType::SSMMMCCC].push_back(MinionType::Caster);
	phase[(int)PhaseType::SSMMMCCC].push_back(MinionType::Caster);
	phase[(int)PhaseType::SSMMMCCC].push_back(MinionType::Caster);

	// 미니언 스폰 포지션 세팅
	spawnPosition[(int)SpawnLane::BlueTop] = { 29.47f,68.04f,41.74f };
	spawnPosition[(int)SpawnLane::BlueMid] = { 30.64f,68.04f,37.51f };
	spawnPosition[(int)SpawnLane::BlueBot] = { 35.00f,68.04f,35.55f };
	spawnPosition[(int)SpawnLane::RedTop] = { -43.05f,68.01f,-29.62f };
	spawnPosition[(int)SpawnLane::RedMid] = { -36.94f,68.01f,-30.35f };
	spawnPosition[(int)SpawnLane::RedBot] = { -36.68f,68.01f,-36.45f };

	// 웨이포인트 세팅
	wayPoints[(int)SpawnLane::BlueTop].push_back(Vector3(-30.88f, 67.71f, 40.80f));
	wayPoints[(int)SpawnLane::BlueTop].push_back(Vector3(-42.32f, 67.71f, 28.58f));
	wayPoints[(int)SpawnLane::BlueTop].push_back(Vector3(-42.87f, 68.01f, -36.16f));

	wayPoints[(int)SpawnLane::BlueMid].push_back(Vector3(-3.49f, 67.72f, 3.92f));
	wayPoints[(int)SpawnLane::BlueMid].push_back(Vector3(-42.87f, 68.01f, -36.16f));

	wayPoints[(int)SpawnLane::BlueBot].push_back(Vector3(34.58f, 67.71f, -23.79f));
	wayPoints[(int)SpawnLane::BlueBot].push_back(Vector3(23.98f, 67.71f, -34.88f));
	wayPoints[(int)SpawnLane::BlueBot].push_back(Vector3(-42.87f, 68.01f, -36.16f));

	wayPoints[(int)SpawnLane::RedTop].push_back(Vector3(-42.32f, 67.71f, 28.58f));
	wayPoints[(int)SpawnLane::RedTop].push_back(Vector3(-30.88f, 67.71f, 40.80f));
	wayPoints[(int)SpawnLane::RedTop].push_back(Vector3(36.59f, 68.05f, 42.96f));

	wayPoints[(int)SpawnLane::RedMid].push_back(Vector3(-3.49f, 67.72f, 3.92f));
	wayPoints[(int)SpawnLane::RedMid].push_back(Vector3(36.59f, 68.05f, 42.96f));

	wayPoints[(int)SpawnLane::RedBot].push_back(Vector3(23.98f, 67.71f, -34.88f));
	wayPoints[(int)SpawnLane::RedBot].push_back(Vector3(34.58f, 67.71f, -23.79f));
	wayPoints[(int)SpawnLane::RedBot].push_back(Vector3(36.59f, 68.05f, 42.96f));
}

MinionSpawner::~MinionSpawner()
{
}

MinionSpawner* MinionSpawner::GetInstance()
{
    if (self == nullptr)
    {
        self = new MinionSpawner();
    }
    return self;
}

void MinionSpawner::Destroy()
{
    if (self)
    {
        delete self;
        self = nullptr;
    }
}

void MinionSpawner::Update()
{
	if (self->spawnFlag)
	{
		self->spawnTick += Time::DeltaTime();

		if (self->spawnTick >= self->spawnDelay)
		{
			self->spawnTick = 0.f;

			int laneCount = MaxOfEnum<SpawnLane>();
			for (int i = 0; i < laneCount; i++)
			{
				Team team = (i < (int)SpawnLane::RedTop) ? Team::BLUE : Team::RED;
			
				PhaseType phaseType = self->spawnPhase[i];
				int phaseSize = self->phase[(int)phaseType].size();
				if (phaseSize <= self->spawnCount) continue;
				MinionType type = self->phase[(int)phaseType][self->spawnCount];
				self->CreateMinion(type, team, (SpawnLane)i);
			}
			self->spawnCount++;
		}

		if (self->spawnCount >= 10)
		{
			self->spawnFlag = false;
			self->spawnCount = 0;
		}
	}

	if (self->firstSpawn)
	{
		self->waveTick += Time::DeltaTime();

		if (self->waveTick >= self->waveDelay)
		{
			self->waveTick = 0.f;
			Spawn();
		}
	}
}

void MinionSpawner::Spawn()
{
	self->spawnFlag = true;
	self->firstSpawn = true;
}

Minion* MinionSpawner::CreateMinion(MinionType _type, Team _team, SpawnLane _spawnLane)
{
	Minion* minion = nullptr;

	// 미니언 생성
	switch (_type)
	{
	case MinionType::Caster:
		switch (_team)
		{
		case Team::BLUE:
			minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<OrderMinionCaster>(Layer::Unit);
			break;
		case Team::RED:
			minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<ChaosMinionCaster>(Layer::Unit);
			break;
		default:
			break;
		}
		break;
	case MinionType::Melee:
		switch (_team)
		{
		case Team::BLUE:
			minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<OrderMinionMelee>(Layer::Unit);
			break;
		case Team::RED:
			minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<ChaosMinionMelee>(Layer::Unit);
			break;
		default:
			break;
		}
		break;
	case MinionType::Siege:
		switch (_team)
		{
		case Team::BLUE:
			minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<OrderMinionSiege>(Layer::Unit);
			break;
		case Team::RED:
			minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<ChaosMinionSiege>(Layer::Unit);
			break;
		default:
			break;
		}
		break;
	case MinionType::Super:
		switch (_team)
		{
		case Team::BLUE:
			minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<OrderMinionSuper>(Layer::Unit);
			break;
		case Team::RED:
			minion = (Minion*)SceneManager::GetCurrentScene()->CreateObject<ChaosMinionSuper>(Layer::Unit);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	if (minion == nullptr) return minion;
	self->minionAllocCount--;

	// 스폰 위치
	minion->transform->position = self->spawnPosition[(int)_spawnLane];
	// 팀 세팅
	minion->SetTeam(_team);
	// 웨이포인트 세팅
	minion->ai->nextPoint = self->wayPoints[(int)_spawnLane][0];
	int pathCount = self->wayPoints[(int)_spawnLane].size();
	for (int i = 1; i < pathCount; i++)
	{
		minion->ai->wayPoint.push_back(self->wayPoints[(int)_spawnLane][i]);
	}

	minion->Show();
	return minion;
}

void MinionSpawner::SetMinionPhase(SpawnLane _spawnLane, PhaseType _phaseType)
{
	GetInstance();

	self->spawnPhase[(int)_spawnLane] = _phaseType;
}

PhaseType MinionSpawner::GetSpawnPhase(SpawnLane _spawnLane)
{
	return self->spawnPhase[(int)_spawnLane];
}

void MinionSpawner::IncreaseCount()
{
	self->minionAllocCount++;
}
