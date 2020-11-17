#include "stdafx.h"
#include "CollisionManager.h"

using namespace PKH;

PKH::CollisionManager* pCollisionManager = nullptr;

PKH::CollisionManager::CollisionManager()
{
}

PKH::CollisionManager::~CollisionManager()
{
	Release();
}

PKH::CollisionManager* CollisionManager::GetInstance()
{
	if (pCollisionManager == nullptr)
	{
		pCollisionManager = new CollisionManager;
	}

	return pCollisionManager;
}

void PKH::CollisionManager::Destroy()
{
	delete pCollisionManager;
}

void PKH::CollisionManager::Update()
{
	ObjectDeadCheck();
	CollisionCheck(COLTYPE::PLAYER_ATTACK, COLTYPE::ENEMY);
	CollisionCheck(COLTYPE::PLAYER, COLTYPE::TRIGGERBOX);
	CollisionCheck(COLTYPE::PLAYER, COLTYPE::COIN);
	CollisionCheck(COLTYPE::PLAYER, COLTYPE::ITEM);
	CollisionCheck(COLTYPE::PLAYER, COLTYPE::COL_NPC);
	CollisionCheck(COLTYPE::PLAYER_MULTI_ATTACK, COLTYPE::ENEMY);
	CollisionCheck(COLTYPE::ENEMY_ATTACK, COLTYPE::PLAYER);
	CollisionCheck(COLTYPE::ENEMY_MULTI_ATTACK, COLTYPE::PLAYER);
}

void PKH::CollisionManager::ObjectDeadCheck()
{
	for (int i = 0; i < COLTYPE::END; ++i)
	{
		auto iter = objectList[i].begin();
		auto iterEnd = objectList[i].end();

		for (;iter != iterEnd;)
		{
			if ((*iter)->IsDead())
			{
				iter = objectList[i].erase(iter);
			}
			else ++iter;
		}
	}
}

void PKH::CollisionManager::CollisionCheck(COLTYPE srcType, COLTYPE dstType)
{
	for (auto& srcElem : objectList[srcType])
	{
		for (auto& dstElem : objectList[dstType])
		{
			if (IsCollided(srcElem, dstElem))
			{
				if (!srcElem->IsInCollideList(dstElem))
				{
					srcElem->OnCollision(dstElem);
					dstElem->OnCollision(srcElem);
				}
			}
		}
	}
}

void PKH::CollisionManager::Release()
{
	for (int i = 0; i < COLTYPE::END; ++i) objectList[i].clear();
}

void PKH::CollisionManager::RegisterObject(COLTYPE colType, GameObject * _pObj)
{
	if (FindObject(colType, _pObj))
	{
		return;
	}

	pCollisionManager->objectList[colType].push_back(_pObj);
}

void PKH::CollisionManager::DisregisterObject(GameObject * obj)
{
	for (int i = 0; i < COLTYPE::END; ++i)
	{
		auto iter = find_if(objectList[i].begin(), objectList[i].end(), [obj](GameObject* elem)
		{
			return elem == obj;
		});

		if (objectList[i].end() != iter) objectList[i].erase(iter);
	}
}

void PKH::CollisionManager::DisregisterObject(COLTYPE colType, GameObject * _pObj)
{
	if (_pObj == nullptr) return;

	auto iter = pCollisionManager->objectList[colType].begin();
	auto end = pCollisionManager->objectList[colType].end();

	for (; iter != end; ++iter)
	{
		if ((*iter) != _pObj) continue;

		pCollisionManager->objectList[colType].erase(iter);
		return;
	}
}

bool PKH::CollisionManager::FindObject(COLTYPE colType, GameObject * _pObj)
{
	if (_pObj == nullptr) return false;
	for (auto iter : pCollisionManager->objectList[colType])
	{
		if (iter != _pObj) continue;

		return true;
	}
	return false;
}

bool PKH::CollisionManager::IsCollided(GameObject* _target, GameObject* _other)
{
	// 거리계산
	float dist = Vector3::Distance(_target->transform->position, _other->transform->position);
	// 반지름 = 반지름 * (스케일합/3)
	float radius1 = ((_target->transform->scale.x + _target->transform->scale.y + _target->transform->scale.z) / 3.f);
	float radius2 = ((_other->transform->scale.x + _other->transform->scale.y + _other->transform->scale.z) / 3.f);
	
	// 거리가 반지름의 합보다 작으면 충돌
	if (dist < (radius1+radius2))
	{
		return true;
	}


	return false;
}
