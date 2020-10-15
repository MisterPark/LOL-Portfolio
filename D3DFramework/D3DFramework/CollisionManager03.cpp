#include "stdafx.h"
#include "CollisionManager03.h"
#include <algorithm>

using namespace PKH;

PKH::CollisionManager03* pCollisionManager03 = nullptr;

PKH::CollisionManager03::CollisionManager03()
{
}

PKH::CollisionManager03::~CollisionManager03()
{
	
}

PKH::CollisionManager03* CollisionManager03::GetInstance()
{
	if (pCollisionManager03 == nullptr)
	{
		pCollisionManager03 = new CollisionManager03;
	}

	return pCollisionManager03;
}

void PKH::CollisionManager03::Destroy()
{
	delete pCollisionManager03;
}

void PKH::CollisionManager03::CollisionSphere(GameObject* rDstObj, GameObject* rSrcObj)
{
	if (CheckSphere(rDstObj, rSrcObj)) {
		rDstObj->OnCollision(rSrcObj);
		rSrcObj->OnCollision(rDstObj);
	}

}

bool PKH::CollisionManager03::CheckSphere(GameObject* rDstObj, GameObject* rSrcObj)
{
	float fRadiusSum = static_cast<float>((rDstObj->transform->scale.x) + (rSrcObj->transform->scale.x));
	float fX = rDstObj->transform->position.x - rSrcObj->transform->position.x;
	float fY = rDstObj->transform->position.y - rSrcObj->transform->position.y;
	float fZ = rDstObj->transform->position.z - rSrcObj->transform->position.z;
	float fDist = sqrtf(fX * fX + fY * fY + fZ * fZ);
	return fDist < fRadiusSum;
}

void PKH::CollisionManager03::Update()
{

	// Ãæµ¹
	for (auto src : pCollisionManager03->objectList)
	{
		for (auto dest : pCollisionManager03->objectList)
		{
			if (src == dest) continue;

			if (CollisionManager03::IsCollided(src, dest))
			{
				src->OnCollision(dest);
			}
		}
	}



}

void PKH::CollisionManager03::RegisterObject(GameObject* _pObj)
{
	if (FindObject(_pObj))
	{
		return;
	}

	pCollisionManager03->objectList.push_back(_pObj);
}

void PKH::CollisionManager03::RegisterObject(OBJ03 _eobj, GameObject* _pObj)
{
	
	if (nullptr == _pObj) return;

	auto iter = find_if(pCollisionManager03->objList[_eobj].begin(), pCollisionManager03->objList[_eobj].end(),
		[_pObj](GameObject* elem)
		{
			return elem == _pObj;
		}
	);

	if (pCollisionManager03->objList[_eobj].end() == iter) return;

	pCollisionManager03->objList[_eobj].erase(iter);
}

void PKH::CollisionManager03::DisregisterObject(GameObject* _pObj)
{
	//if (FindObject(_pObj))
	//{
	//	//pCollisionManager03->objectList.remove(_pObj);
	//}
	if (_pObj == nullptr) return;

	auto iter = pCollisionManager03->objectList.begin();
	auto end = pCollisionManager03->objectList.end();

	for (; iter != end; ++iter)
	{
		if ((*iter) != _pObj) continue;

		pCollisionManager03->objectList.erase(iter);
		return;
	}
}

bool PKH::CollisionManager03::FindObject(GameObject* _pObj)
{
	if (_pObj == nullptr) return false;
	for (auto iter : pCollisionManager03->objectList)
	{
		if (iter != _pObj) continue;

		return true;
	}
	return false;
}

bool PKH::CollisionManager03::IsCollided(GameObject* _target, GameObject* _other)
{
	return false;
}
