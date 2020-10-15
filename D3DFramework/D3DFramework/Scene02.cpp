#include "stdafx.h"
#include "Scene02.h"
#include "Player02.h"
#include "Enemy02.h"
#include "Boss02.h"
#include "MyCollisionManager.h"
#include "Scene03.h"

void Scene02::OnLoaded()
{
	MyCollisionManager::GetInstance();

	Cursor::GetInstance()->isVisible = false;

	myPlayer = new Player02;
	ObjectManager::AddObject(myPlayer);
	MyCollisionManager::GetInstance()->RegisterObject(MyCollisionManager::PLAYER, myPlayer);
}

void Scene02::OnUnloaded()
{
	MyCollisionManager::DestroyInstance();
	ObjectManager::DestroyAll();
}

void Scene02::Update()
{
	if (IsEndScene())
	{
		endCount += TimeManager::DeltaTime();

		if (endCount >= 3.f) SceneManager::LoadScene<Scene03>();
	}

	else
	{
		SpawnByTime();

		MyCollisionManager::GetInstance()->Collide(MyCollisionManager::ENEMY, MyCollisionManager::PLAYER_BULLET);
		MyCollisionManager::GetInstance()->Collide2(MyCollisionManager::BOSS, MyCollisionManager::PLAYER_BULLET);
		MyCollisionManager::GetInstance()->Collide2(MyCollisionManager::PLAYER, MyCollisionManager::ENEMY);
		MyCollisionManager::GetInstance()->Collide2(MyCollisionManager::PLAYER, MyCollisionManager::ENEMY_BULLET);
		MyCollisionManager::GetInstance()->CullingBullet(MyCollisionManager::ENEMY_BULLET);
		MyCollisionManager::GetInstance()->CullingBullet(MyCollisionManager::PLAYER_BULLET);
		MyCollisionManager::GetInstance()->CullingEnemy();
	}
}

bool Scene02::IsEndScene()
{
	if (myPlayer->isDead) return true;

	if (isBossSpawn && myBoss->isDead) return true;

	return false;
}

void Scene02::SpawnByTime()
{
	if (!isBossSpawn)
	{
		playTime += TimeManager::DeltaTime();
		spawnTime += TimeManager::DeltaTime();
		spawnTime2 += TimeManager::DeltaTime();

		if (30.f < playTime)
		{
			float xPos, yPos, zPos;

			SpawnEnemy01({ 0.f, 5.f, 0.f });
			SpawnEnemy02({ 0.f, 2.f, 5.f });

			yPos = Random::Range(5.f, 8.f);
			SpawnEnemy01({ -1.5f, yPos, 0.f });

			yPos = Random::Range(5.f, 8.f);
			SpawnEnemy01({ 1.5f, yPos, 0.f });

			xPos = Random::Range(-2.5f, -1.f);
			yPos = Random::Range(1.5f, 2.5f);
			zPos = Random::Range(3.f, 8.f);
			SpawnEnemy02({ xPos, yPos, zPos });

			xPos = Random::Range(1.f, 2.5f);
			yPos = Random::Range(1.5f, 2.5f);
			zPos = Random::Range(3.f, 8.f);
			SpawnEnemy02({ xPos, yPos, zPos });

			SpawnBoss({ 0.f, 2.5f, 0.f });
		}

		if (4.f < spawnTime)
		{
			++spawnType;

			float xPos, yPos, zPos;

			if (spawnType % 2)
			{
				xPos = Random::Range(-1.5f, 0.f);
				SpawnEnemy01({ xPos, 5.f, 0.f });

				xPos = Random::Range(0.f, 1.5f);
				SpawnEnemy01({ xPos, 5.f, 0.f });
			}
			else
			{
				SpawnEnemy01({ 0.f, 5.f, 0.f });

				xPos = Random::Range(1.5f, 2.5f);
				yPos = Random::Range(5.f, 8.f);
				SpawnEnemy01({ xPos, yPos, 0.f });

				xPos = Random::Range(-2.5f, -1.5f);
				yPos = Random::Range(5.f, 8.f);
				SpawnEnemy01({ xPos, yPos, 0.f });
			}

			spawnTime = 0.f;
		}
		
		if (8.f < spawnTime2)
		{
			++spawnType2;

			float xPos, yPos, zPos;

			if (spawnType2 % 2)
			{
				xPos = Random::Range(-2.5f, -1.f);
				yPos = Random::Range(-1.f, 2.f);
				zPos = Random::Range(4.f, 6.f);

				SpawnEnemy02({ xPos, yPos, zPos });

				xPos = Random::Range(1.f, 2.5f);
				yPos = Random::Range(-1.f, 2.f);
				zPos = Random::Range(4.f, 6.f);

				SpawnEnemy02({ xPos, yPos, zPos });
			}
			else
			{
				SpawnEnemy02({ 0.f, 1.5f, 7.f });

				xPos = Random::Range(-2.5f, -1.f);
				yPos = Random::Range(-1.f, 2.f);
				zPos = Random::Range(4.f, 6.f);
				SpawnEnemy02({ xPos, yPos, zPos });

				xPos = Random::Range(1.f, 2.5f);
				yPos = Random::Range(-1.f, 2.f);
				zPos = Random::Range(4.f, 6.f);
				SpawnEnemy02({ xPos, yPos, zPos });
			}

			spawnTime2 = 0.f;
		}

	}
}

void Scene02::SpawnEnemy01(Vector3 pos, Vector3 look)
{
	Enemy02* enemy = new Enemy02(pos, look);
	ObjectManager::AddObject(enemy);
	MyCollisionManager::GetInstance()->RegisterObject(MyCollisionManager::ENEMY, enemy);
}

void Scene02::SpawnEnemy02(Vector3 pos, Vector3 look)
{
	Enemy02* enemy = new Enemy02(pos, look, 2, myPlayer);
	ObjectManager::AddObject(enemy);
	MyCollisionManager::GetInstance()->RegisterObject(MyCollisionManager::ENEMY, enemy);
}

void Scene02::SpawnBoss(Vector3 pos, Vector3 look)
{
	if (!isBossSpawn)
	{
		myBoss = new Boss02(pos, look, myPlayer);
		ObjectManager::AddObject(myBoss);
		MyCollisionManager::GetInstance()->RegisterObject(MyCollisionManager::BOSS, myBoss);

		isBossSpawn = true;
	}
}
