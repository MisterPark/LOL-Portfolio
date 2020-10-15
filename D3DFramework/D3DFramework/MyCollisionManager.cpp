#include "stdafx.h"
#include "MyCollisionManager.h"
#include "GameObject.h"
#include "Bullet02.h"
#include "Enemy02.h"
#include <algorithm>

MyCollisionManager* MyCollisionManager::instance = nullptr;

using namespace PKH;

MyCollisionManager::MyCollisionManager()
{
}

MyCollisionManager::~MyCollisionManager()
{
	Release();
}

MyCollisionManager * MyCollisionManager::GetInstance()
{
	if (nullptr == instance) instance = new MyCollisionManager;

	return instance;
}

void MyCollisionManager::DestroyInstance()
{
	delete instance;
	instance = nullptr;
}

void MyCollisionManager::RegisterObject(OBJTAG tag, GameObject * obj)
{
	if (nullptr == obj) return;
	objList[tag].emplace_back(obj);
}

void MyCollisionManager::UnListObject(OBJTAG tag, GameObject * obj)
{
	if (nullptr == obj) return;

	auto iter =  find_if(objList[tag].begin(),objList[tag].end(),
		[obj](GameObject* elem)
	{
		return elem == obj;
	}
	);

	if (objList[tag].end() == iter) return;

	objList[tag].erase(iter);
}

void MyCollisionManager::Collide(OBJTAG dst, OBJTAG src)
{
	auto dstIter = objList[dst].begin();

	for (; dstIter != objList[dst].end();)
	{
		bool isCollide = false;
		auto srcIter = objList[src].begin();

		for (; srcIter != objList[src].end();)
		{
			if (IsCollision((*dstIter)->transform, (*srcIter)->transform))
			{
				(*dstIter)->OnCollision(*srcIter);
				(*srcIter)->OnCollision(*dstIter);

				dstIter = objList[dst].erase(dstIter);
				srcIter = objList[src].erase(srcIter);

				isCollide = true;

				break;
			}
			++srcIter;
		}
		if(!isCollide) ++dstIter;
	}
}

void MyCollisionManager::Collide2(OBJTAG dst, OBJTAG src)
{
	auto srcIter = objList[src].begin();

	for (; srcIter != objList[src].end();)
	{
		bool isCollide = false;
		auto dstIter = objList[dst].begin();

		for (; dstIter != objList[dst].end();)
		{
			if (IsCollision((*dstIter)->transform, (*srcIter)->transform))
			{
				(*srcIter)->OnCollision(*dstIter);
				(*dstIter)->OnCollision(*srcIter);

				srcIter = objList[src].erase(srcIter);

				isCollide = true;

				break;
			}
			if(!isCollide) ++dstIter;
		}
		if (!isCollide) ++srcIter;
	}
}

void MyCollisionManager::CullingBullet(OBJTAG tag)
{
	for (auto iter = objList[tag].begin(); iter != objList[tag].end();)
	{
		Bullet02* bullet = dynamic_cast<Bullet02*>(*iter);

		if (bullet->Culling())
		{
			iter = objList[tag].erase(iter);
		}
		else ++iter;
	}
}

void MyCollisionManager::CullingEnemy()
{
	for (auto iter = objList[ENEMY].begin(); iter != objList[ENEMY].end();)
	{
		Enemy02* enemy = dynamic_cast<Enemy02*>(*iter);

		if (enemy->Culling())
		{
			iter = objList[ENEMY].erase(iter);
		}
		else ++iter;
	}
}

void MyCollisionManager::Release()
{
	for (int i = 0; i < OBJTAG::END; ++i)
	{
		objList[i].clear();
	}
	objList->clear();
}

bool MyCollisionManager::IsCollision(Transform* dst, Transform* src)
{
	Vector3 target = dst->position - src->position;

	float dstRadius = dst->scale.z * 0.1f;
	float srcRadius = src->scale.z * 0.1f;

	float distance = D3DXVec3LengthSq(&target);

	if (distance <= dstRadius + srcRadius)
		return true;

	return false;
}
