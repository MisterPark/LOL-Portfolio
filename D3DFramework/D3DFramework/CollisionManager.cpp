#include "stdafx.h"
#include "CollisionManager.h"
#include "Collider.h"

using namespace PKH;

PKH::CollisionManager* pCollisionManager = nullptr;

PKH::CollisionManager::CollisionManager()
{
}

PKH::CollisionManager::~CollisionManager()
{
	Release();
}

void PKH::CollisionManager::Release()
{
	int layerCount = MaxOfEnum<Layer>();
	for (int i = 0; i < layerCount; ++i)
	{
		objectList[i].clear();
	}
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
	if (pCollisionManager)
	{
		delete pCollisionManager;
		pCollisionManager = nullptr;
	}
	
}

void PKH::CollisionManager::Update()
{
	int layerCount = MaxOfEnum<Layer>();
	for (int i = 0; i < layerCount; i++)
	{
		for (int j = i; j < layerCount; j++)
		{
			CollisionCheck((Layer)i, (Layer)j);
		}
	}
}


void PKH::CollisionManager::CollisionCheck(Layer srcType, Layer dstType)
{
	for (auto& srcElem : objectList[(int)srcType])
	{
		for (auto& dstElem : objectList[(int)dstType])
		{
			if (IsCollided(srcElem, dstElem))
			{
				srcElem->OnCollisionEnter(dstElem);
				dstElem->OnCollisionEnter(srcElem);
			}
		}
	}
}

void PKH::CollisionManager::RegisterObject(Layer colType, Collider* _pObj)
{
	if (FindObject(colType, _pObj))
	{
		return;
	}

	pCollisionManager->objectList[(int)colType].push_back(_pObj);
}

void PKH::CollisionManager::DisregisterObject(Collider* obj)
{
	int layerCount = MaxOfEnum<Layer>();
	for (int i = 0; i < layerCount; ++i)
	{
		auto iter = find_if(objectList[i].begin(), objectList[i].end(), [obj](Collider* elem)
		{
			return elem == obj;
		});

		if (objectList[i].end() != iter) objectList[i].erase(iter);
	}
}

void PKH::CollisionManager::DisregisterObject(Layer colType, Collider* _pObj)
{
	if (_pObj == nullptr) return;

	auto iter = pCollisionManager->objectList[(int)colType].begin();
	auto end = pCollisionManager->objectList[(int)colType].end();

	for (; iter != end; ++iter)
	{
		if ((*iter) != _pObj) continue;

		pCollisionManager->objectList[(int)colType].erase(iter);
		return;
	}
}

bool PKH::CollisionManager::FindObject(Layer colType, Collider* _pObj)
{
	if (_pObj == nullptr) return false;
	for (auto iter : pCollisionManager->objectList[(int)colType])
	{
		if (iter != _pObj) continue;

		return true;
	}
	return false;
}

bool PKH::CollisionManager::IsCollided(Collider* _target, Collider* _other)
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
