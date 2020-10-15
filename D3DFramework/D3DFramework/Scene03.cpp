#include "stdafx.h"
#include "Scene03.h"
#include "Scene4.h"
#include "Player03.h"
#include "Monster03.h"
#include "Dust03.h"
#include "CollisionManager03.h"
#include "Triangle.h"
#include "Rectangle.h"
#include "Cube.h"

void Scene03::OnLoaded()
{
	Player03* p = (Player03*)ObjectManager::GetInstance()->CreateObject<Player03>();
	

}

void Scene03::OnUnloaded()
{
	ObjectManager::DestroyAll();
}

void Scene03::Update()
{

	/*CollisionManager03::GetInstance()->IsCollided(CollisionManager03::MONSTER_BULLET, CollisionManager03::PLAYER);*/

	GameObject* player = ObjectManager::GetInstance()->FindObject<Player03>();
	if (player != nullptr)
	{
		tick += TimeManager::DeltaTime();
		fdust += 2.f * TimeManager::DeltaTime();
		//GameObject* dust = ObjectManager::GetInstance()->FindObject<Dust03>();
		//if (fdust > 1.f)
		//{
		//	Dust03* p = (Dust03*)ObjectManager::GetInstance()->CreateObject<Dust03>();
		//	p->SetPosition(Vector3{ -3.f,3.f,5.f });
		//	p->AddComponent<PKH::Triangle>(L"Mesh");
		//	

		//	p = (Dust03*)ObjectManager::GetInstance()->CreateObject<Dust03>();
		//	p->SetPosition(Vector3{ 3.f,3.f,6.f });
		//	p->AddComponent<PKH::Triangle>(L"Mesh");

		//	p = (Dust03*)ObjectManager::GetInstance()->CreateObject<Dust03>();
		//	p->SetPosition(Vector3{ -3.f,-3.f,7.f });
		//	p->AddComponent<PKH::Triangle>(L"Mesh");


		//	p = (Dust03*)ObjectManager::GetInstance()->CreateObject<Dust03>();
		//	p->SetPosition(Vector3{ 3.f,-3.f,8.f });
		//	p->AddComponent<PKH::Triangle>(L"Mesh");
		//	fdust = 0;
		//}
	}
	//playercheck
	if (InputManager::GetKey(VK_RETURN))
	{
		GameObject* player = ObjectManager::GetInstance()->FindObject<Player03>();
		if (player == nullptr)
		{
			Player03* p = (Player03*)ObjectManager::GetInstance()->CreateObject<Player03>();
			p->transform->position = { 0.f,-2.5f,0.f };
		}
		
	}
	
	//if (MonsterMakeCount == 0)
	//{//test
	////bosstype
	//	Monster03* m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
	//	m->SetPosition(Vector3{ 0.f,5.f,11.f });
	//	m->BossType = true;
	//	m->transform->scale = { 10.f,10.f,10.f };
	//	MonsterMakeCount++;
	//}
	////////////////////////////////////////


	//monster check
	GameObject* monstercheck = ObjectManager::GetInstance()->FindObject<Monster03>();
	if (!monstercheck)
	{
		// xtype

		//Monster03* m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		//m->SetPosition(Vector3{ -10.f,0.f,5.f });
		//m->xType = true;
		//m->AddComponent<PKH::Cube>(L"Mesh");

		//m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		//m->SetPosition(Vector3{ -10.f,5.f,5.f });
		//m->xType = true;
		//m->AddComponent<PKH::Cube>(L"Mesh");

		//m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		//m->SetPosition(Vector3{ -10.f,-5.f,5.f });
		//m->xType = true;
		//m->AddComponent<PKH::Cube>(L"Mesh");
	}


	//»ý¼º
	if (tick > 2.f && MonsterMakeCount==0)
	{
		Monster03* m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ -10.f,0.f,5.f });
		m->xType = true;

		m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ -10.f,5.f,5.f });
		m->xType = true;

		m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ -10.f,-5.f,5.f });
		m->xType = true;
		MonsterMakeCount++;
	}

	if (tick > 6.f && MonsterMakeCount == 1)
	{

		//ytype
		Monster03* m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ -5.f,10.f,5.f });
		m->yType = true;
		m->yTypex = -5.f;

		m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ -2.f,-10.f,5.f });
		m->yType = true;
		m->yTypex = -2.f;

		m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ 2.f,10.f,5.f });
		m->yType = true;
		m->yTypex = 2.f;

		m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ 5.f,-10.f,5.f });
		m->yType = true;
		m->yTypex = 5.f;
		MonsterMakeCount++;
	}

	if (tick > 10.f && MonsterMakeCount == 2)
	{
		//ztype

		Monster03*  m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ -6.f,0.f,8.f });
		
		m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ -3.f,0.f,8.f });
		
		m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ -0.f,0.f,8.f });
		
		m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ 3.f,0.f,8.f });
		
		m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ 6.f,0.f,8.f });
		MonsterMakeCount++;
	}


	if (tick > 15.f && MonsterMakeCount == 3)
	{
		//xtype

		Monster03* m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ -10.f,0.f,5.f });
		m->xType = true;
		
		m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ -10.f,5.f,5.f });
		m->xType = true;

		m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ -10.f,-5.f,5.f });
		m->xType = true;
		
		//ytype

		m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ 2.f,10.f,5.f });
		m->yType = true;
		m->yTypex = 2.f;

		m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ -2.f,-10.f,5.f });
		m->yType = true;
		m->yTypex = -2.f;

		m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ 5.f,10.f,5.f });
		m->yType = true;
		m->yTypex = 5.f;
		
		//ztype

		m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ -6.f,5.f,8.f });

		m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ -3.f,-5.f,8.f });

		m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ -0.f,0.f,8.f });

		m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ 3.f,-5.f,8.f });

		m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ 6.f,5.f,8.f });
		MonsterMakeCount++;
	}

	if (!monstercheck && MonsterMakeCount == 4)
	{
		tick = 10;
		MonsterMakeCount = 3;
		++BossmakeCount;
	}

	if (BossmakeCount > 1)
	{
		//bosstype
		Monster03* m = (Monster03*)ObjectManager::GetInstance()->CreateObject<Monster03>();
		m->SetPosition(Vector3{ 0.f,5.f,11.f });
		m->BossType = true;
		m->transform->scale = { 10.f,10.f,10.f };

		BossmakeCount = 0;
		MonsterMakeCount = 10;
		
	}
	if (player != nullptr)
	{
		if (dynamic_cast<Player03*>(player)->SceneChange == 1)
		{
			GameEnd = true;
		}
	}

	if (GameEnd)
	{
		EndCount += TimeManager::DeltaTime();
		if (EndCount > 5)
		{
			SceneManager::LoadScene<Scene4>();
		}
	}



}

