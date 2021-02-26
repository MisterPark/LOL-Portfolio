#include "stdafx.h"
#include "CollisionManager.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "SphereCollider.h"

using namespace Engine;

Engine::CollisionManager* pCollisionManager = nullptr;

Engine::CollisionManager::CollisionManager()
{
}

Engine::CollisionManager::~CollisionManager()
{
	Release();
}

void Engine::CollisionManager::Release()
{
	int layerCount = MaxOfEnum<Layer>();
	for (int i = 0; i < layerCount; ++i)
	{
		objectList[i].clear();
	}
}

Engine::CollisionManager* CollisionManager::GetInstance()
{
	if (pCollisionManager == nullptr)
	{
		pCollisionManager = new CollisionManager;
	}

	return pCollisionManager;
}

void Engine::CollisionManager::Destroy()
{
	if (pCollisionManager)
	{
		delete pCollisionManager;
		pCollisionManager = nullptr;
	}
	
}

void Engine::CollisionManager::Update()
{
	// TODO : CollisionManager 과부하가 너무 심해서 일단 주석
	//int layerCount = MaxOfEnum<Layer>();
	//for (int i = 0; i < layerCount; i++)
	//{
	//	for (int j = i; j < layerCount; j++)
	//	{
	//		CollisionCheck((Layer)i, (Layer)j);
	//	}
	//} 
	CollisionCheck(Layer::Building, Layer::Unit);
	CollisionCheck(Layer::Unit, Layer::Unit);
}


void Engine::CollisionManager::CollisionCheck(Layer srcType, Layer dstType)
{
	for (auto& srcElem : objectList[(int)srcType])
	{
		for (auto& dstElem : objectList[(int)dstType])
		{
			if (srcElem == dstElem)continue;
			if (srcElem->enable == false) continue;
			if (dstElem->enable == false) continue;
			if (IsCollided(srcElem, dstElem))
			{
				srcElem->OnCollisionEnter(dstElem);
				dstElem->OnCollisionEnter(srcElem);
			}
		}
	}
}

void Engine::CollisionManager::RegisterObject(Layer colType, Collider* _pObj)
{
	if (FindObject(colType, _pObj))
	{
		return;
	}

	pCollisionManager->objectList[(int)colType].push_back(_pObj);
}

void Engine::CollisionManager::DisregisterObject(Collider* obj)
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

void Engine::CollisionManager::DisregisterObject(Layer colType, Collider* _pObj)
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

bool Engine::CollisionManager::FindObject(Layer colType, Collider* _pObj)
{
	if (_pObj == nullptr) return false;
	for (auto iter : pCollisionManager->objectList[(int)colType])
	{
		if (iter != _pObj) continue;

		return true;
	}
	return false;
}

bool Engine::CollisionManager::IsCollided(Collider* src, Collider* dst)
{
	// TODO : 이거 각자의 콜라이더에서 상대 콜라이더 타입에 따른 충돌처리로 변경해야함
	// 콜라이더 타입 판별
	BoxCollider* srcBox = nullptr;
	SphereCollider* srcSphere = nullptr;
	switch (src->type)
	{
	case ColliderType::Box:
		srcBox = dynamic_cast<BoxCollider*>(src);
		if (srcBox == nullptr) return false;
		break;
	case ColliderType::Sphere:
		srcSphere = dynamic_cast<SphereCollider*>(src);
		if (srcSphere == nullptr) return false;
		break;
	default:
		return false;
	}

	BoxCollider* destBox = nullptr;
	SphereCollider* destSphere = nullptr;
	switch (dst->type)
	{
	case ColliderType::Box:
		destBox = dynamic_cast<BoxCollider*>(dst);
		if (destBox == nullptr) return false;
		break;
	case ColliderType::Sphere:
		destSphere = dynamic_cast<SphereCollider*>(dst);
		if (destSphere == nullptr) return false;
		break;
	default:
		return false;
	}

	if (src->type == ColliderType::Sphere && dst->type == ColliderType::Sphere)
	{
		return CheckSphereCollision(srcSphere, destSphere);
	}
	else if (src->type == ColliderType::Box && dst->type == ColliderType::Box)
	{
		return CheckAABBCollision(srcBox, destBox);
	}


	return false;
}

bool Engine::CollisionManager::CheckSphereCollision(SphereCollider* src, SphereCollider* dest)
{
	// 거리 계산
	Vector3 srcWorldPos = src->GetWorldPosition();
	Vector3 destWorldPos = dest->GetWorldPosition();
	float distance = Vector3::Distance(srcWorldPos, destWorldPos);
	float radiusSum = src->GetRadius() + dest->GetRadius();

	// 거리가 반지름합보다 크면 충돌X
	if (distance > radiusSum) return false;

	return true;
}

bool Engine::CollisionManager::CheckAABBCollision(BoxCollider* src, BoxCollider* dest)
{
	// 거리 계산
	Vector3 srcWorldPos = src->GetWorldPosition();
	Vector3 destWorldPos = dest->GetWorldPosition();
	
	Vector3 srcMin, srcMax, dstMin, dstMax;
	float min, max;
	
	srcMin = Vector3(srcWorldPos.x - (src->size.x * 0.5f)
					,srcWorldPos.y - (src->size.y * 0.5f)
					,srcWorldPos.z - (src->size.z * 0.5f));
	srcMax = Vector3(srcWorldPos.x + (src->size.x * 0.5f)
					,srcWorldPos.y + (src->size.y * 0.5f)
					,srcWorldPos.z + (src->size.z * 0.5f));
	dstMin = Vector3(destWorldPos.x - (dest->size.x * 0.5f)
					,destWorldPos.y - (dest->size.y * 0.5f)
					,destWorldPos.z - (dest->size.z * 0.5f));
	dstMax = Vector3(destWorldPos.x + (dest->size.x * 0.5f)
					,destWorldPos.y + (dest->size.y * 0.5f)
					,destWorldPos.z + (dest->size.z * 0.5f));

	// x축
	min = max(dstMin.x, srcMin.x);
	max = min(dstMax.x, srcMax.x);

	if (max < min) return false;

	// y축
	min = max(dstMin.y, srcMin.y);
	max = min(dstMax.y, srcMax.y);

	if (max < min) return false;

	// z축
	min = max(dstMin.z, srcMin.z);
	max = min(dstMax.z, srcMax.z);

	if (max < min) return false;
	

	return true;
}

bool Engine::CollisionManager::CheckOBBCollision(BoxCollider* src, BoxCollider* dest)
{
	// 거리 계산
	Vector3 srcWorldPos = src->GetWorldPosition();
	Vector3 destWorldPos = dest->GetWorldPosition();
	float distance = Vector3::Distance(srcWorldPos, destWorldPos);


	return false;
}
