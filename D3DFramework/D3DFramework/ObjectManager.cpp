#include "stdafx.h"
#include "ObjectManager.h"

using namespace PKH;

PKH::ObjectManager* pObjectManager = nullptr;
int lastUid = 0;

PKH::ObjectManager::ObjectManager()
{
}

PKH::ObjectManager::~ObjectManager()
{
}

ObjectManager * PKH::ObjectManager::GetInstance()
{
	if (pObjectManager == nullptr)
	{
		pObjectManager = new ObjectManager;
	}
	return pObjectManager;
}



bool PKH::ObjectManager::DeleteObject(GameObject * _target)
{
	auto& objList = pObjectManager->objectList;
	
	auto target = find(objList.begin(), objList.end(), _target);
	if (target != objList.end())
	{
		_target->Die();
		return true;
	}
	return false;
}

void PKH::ObjectManager::DestroyAll()
{
	auto& objList = pObjectManager->objectList;

	for (auto& iter : objList)
	{
		iter->Die();
	}
}

void PKH::ObjectManager::Destroy()
{
	delete pObjectManager;
	pObjectManager = nullptr;
}

void PKH::ObjectManager::Update()
{
	
	auto& objList = pObjectManager->objectList;
	for (auto& iter : objList)
	{
		if (!iter->isEnable) continue;
		iter->Update();
	}
}

void PKH::ObjectManager::PostUpdate()
{
	GameObject* target = nullptr;

	auto& objList = pObjectManager->objectList;
	auto iter = objList.begin();
	auto end = objList.end();
	for (; iter != end;)
	{
		target = *iter;
		if (target->isDead)
		{
			iter = objList.erase(iter);

			/*		if (dynamic_cast<Character*>(target) != nullptr)
					{
						CollisionManager::DisregisterObject(target);
					}*/

			delete target;
		}
		else
		{
			++iter;
		}
	}

	
	
	
}

void PKH::ObjectManager::PreRender()
{

}

void PKH::ObjectManager::Render()
{
	pObjectManager->renderList.clear();

	Vector3 camPos = Camera::GetPosition();
	
	auto& objList = pObjectManager->objectList;
	for (auto& iter : objList)
	{
		if (!iter->isVisible)continue;
		if (iter->transform.position.x < camPos.x - dfCLIENT_WIDTH / 2) continue;
		if (iter->transform.position.y < camPos.y - dfCLIENT_HEIGHT / 2) continue;
		if (iter->transform.position.x > camPos.x + dfCLIENT_WIDTH + dfCLIENT_WIDTH / 2) continue;
		if (iter->transform.position.y > camPos.y + dfCLIENT_HEIGHT + dfCLIENT_HEIGHT / 2) continue;


		pObjectManager->renderList.push_back(iter);
	}

	// y값으로 정렬
	pObjectManager->renderList.sort(Compare);
	// 오브젝트 렌더링
	for (auto& obj : pObjectManager->renderList)
	{
		obj->Render();
	}
	

	// 디버그용
	//TimeManager::RenderFPS();
}

void PKH::ObjectManager::PostRender()
{
}

bool PKH::ObjectManager::Compare(GameObject* a, GameObject* b)
{
	return a->transform.position.y < b->transform.position.y;
}

bool PKH::ObjectManager::IsVisibleCollider()
{
	return pObjectManager->isVisibleCollider;
}

void PKH::ObjectManager::SetVisibleCollider(bool _isVisible)
{
	pObjectManager->isVisibleCollider = _isVisible;
}
