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

	// 충돌
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
