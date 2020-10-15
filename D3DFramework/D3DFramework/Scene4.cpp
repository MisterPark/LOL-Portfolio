#include "stdafx.h"
#include "Scene4.h"
#include "Player4.h"
#include "Monster4.h"
#include "Boss4.h"
#include "Cube.h"
#include "CollisionManager4.h"
#include "Random_Manager4.h"
#include "QuakeManager4.h"


void Scene4::OnLoaded()
{
	SceneStartTime = 0.f;
	MonsterRegenTime1 = 0.f;
	MonsterRegenTime2 = 0.f;
	BossGen = false;
	Player4* p = (Player4*)ObjectManager::GetInstance()->CreateObject<Player4>();
	CollisionManager4::GetInstance()->RegisterObject(CollisionManager4::PLAYER, p);
	Cube* Comp = dynamic_cast<Cube*>(p->AddComponent<PKH::Cube>(L"Mesh"));
	Comp->SetColor(D3DCOLOR_XRGB(103, 153, 255));
	Random_Manager::Get_Instance()->Ready_Random();
	QuakeManager4::GetInstance();
	//Monster4* m = (Monster4*)ObjectManager::GetInstance()->CreateObject<Monster4>();
	//m->AddComponent<PKH::Cube>(L"Mesh");

}

void Scene4::OnUnloaded()
{
	ObjectManager::DestroyAll();
	CollisionManager4::Destroy();
	QuakeManager4::Destroy();
	Random_Manager::Destroy_Instance();
}

void Scene4::Update()
{
	SceneStartTime += TimeManager::DeltaTime();
	MonsterRegenTime1 += TimeManager::DeltaTime();
	MonsterRegenTime2 += TimeManager::DeltaTime();
	LARGE_INTEGER AccCount, PerCount;
	QueryPerformanceFrequency(&PerCount);
	PerCount.QuadPart *= 0.1f;
	QueryPerformanceCounter(&AccCount);
	if (MonsterRegenTime1 > 1.5f && !BossGen) {
		MonsterRegenTime1 = 0.f;
		GameObject* g = ObjectManager::GetInstance()->CreateObject<Monster4>();
		Monster4* m = dynamic_cast<Monster4*>(g);
		CollisionManager4::GetInstance()->RegisterObject(CollisionManager4::MONSTER, g);
		Cube* Comp = dynamic_cast<Cube*>(m->AddComponent<PKH::Cube>(L"Mesh"));
		int RandomNumber = Random_Manager::Random4() % 3;
		if(RandomNumber == 0)
			Comp->SetColor(D3DCOLOR_XRGB(103, 153, 255));
		else if (RandomNumber == 1)
			Comp->SetColor(D3DCOLOR_XRGB(241, 95, 95));
		else
			Comp->SetColor(D3DCOLOR_XRGB(134, 229, 127));
		m->SetPosZ(RandomNumber);
		//Monster4* m = (Monster4*)ObjectManager::GetInstance()->FindObject<Monster4>();
		m->SetCode(3);
		m->Ready();
	}
	if (MonsterRegenTime2 > 3.f) {
		MonsterRegenTime2 = 0.f;
		GameObject* g = ObjectManager::GetInstance()->CreateObject<Monster4>();
		Monster4* m = dynamic_cast<Monster4*>(g);
		CollisionManager4::GetInstance()->RegisterObject(CollisionManager4::MONSTER, g);
		Cube* Comp = dynamic_cast<Cube*>(m->AddComponent<PKH::Cube>(L"Mesh"));
		Comp->SetColor(D3DCOLOR_XRGB(103, 153, 255));
		//Monster4* m = (Monster4*)ObjectManager::GetInstance()->FindObject<Monster4>();
		m->SetCode(2);
		m->Ready();
	}
	if (!BossGen && SceneStartTime >= 50.f) {
		BossGen = true;
		GameObject* g = ObjectManager::GetInstance()->CreateObject<Boss4>();
		Boss4* b = dynamic_cast<Boss4*>(g);
		CollisionManager4::GetInstance()->RegisterObject(CollisionManager4::BOSS, g);
		b->Ready();
	}
	CollisionManager4::GetInstance()->Update();
	QuakeManager4::Update();
}
