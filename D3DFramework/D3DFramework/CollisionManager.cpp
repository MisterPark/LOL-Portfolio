#include "stdafx.h"
#include "CollisionManager.h"

using namespace PKH;

PKH::CollisionManager* pCollisionManager = nullptr;

PKH::CollisionManager::CollisionManager()
{
}

PKH::CollisionManager::~CollisionManager()
{
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

	// Ãæµ¹
	for (auto src : pCollisionManager->objectList)
	{
		for (auto dest : pCollisionManager->objectList)
		{
			if (src == dest) continue;

			if (CollisionManager::IsCollided(src, dest))
			{
				src->OnCollision(dest);
			}
		}
	}

	

}

void PKH::CollisionManager::RegisterObject(GameObject* _pObj)
{
	if (FindObject(_pObj))
	{
		return;
	}

	pCollisionManager->objectList.push_back(_pObj);
}

void PKH::CollisionManager::DisregisterObject(GameObject* _pObj)
{
	//if (FindObject(_pObj))
	//{
	//	//pCollisionManager->objectList.remove(_pObj);
	//}
	if (_pObj == nullptr) return;

	auto iter = pCollisionManager->objectList.begin();
	auto end = pCollisionManager->objectList.end();

	for (; iter != end; ++iter)
	{
		if ((*iter) != _pObj) continue;

		pCollisionManager->objectList.erase(iter);
		return;
	}
}

bool PKH::CollisionManager::FindObject(GameObject* _pObj)
{
	if (_pObj == nullptr) return false;
	for (auto iter : pCollisionManager->objectList)
	{
		if (iter != _pObj) continue;

		return true;
	}
	return false;
}

bool PKH::CollisionManager::IsCollided(GameObject* _target, GameObject* _other)
{
	return false;
}
