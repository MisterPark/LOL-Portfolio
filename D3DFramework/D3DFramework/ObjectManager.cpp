#include "stdafx.h"
#include "ObjectManager.h"
#include "SkyBox.h"
#include "Cursor.h"
#include "PlayerInfoPanel.h"

using namespace Engine;

Engine::ObjectManager* pObjectManager = nullptr;
int lastUid = 0;

Engine::ObjectManager::ObjectManager()
{
}

Engine::ObjectManager::~ObjectManager()
{
	Release();
}

ObjectManager * Engine::ObjectManager::GetInstance()
{
	if (pObjectManager == nullptr)
	{
		pObjectManager = new ObjectManager;
	}
	return pObjectManager;
}

void Engine::ObjectManager::Destroy()
{
	delete pObjectManager;
	pObjectManager = nullptr;
}

void Engine::ObjectManager::Release()
{
	auto objTable = pObjectManager->objectTable;
	int layerCount = MaxOfEnum<Layer>();
	for (int i = 0; i < layerCount; i++)
	{
		auto& objList = objTable[i];

		auto iter = objList.begin();
		auto end = objList.end();
		for (; iter != end; ++iter)
		{
			delete (*iter);
			*iter = nullptr;
		}
		objList.clear();
	}
	
}


bool Engine::ObjectManager::DeleteObject(GameObject * _target)
{
	if (_target == nullptr) return false;
	auto& objList = pObjectManager->objectTable[(int)_target->GetLayer()];
	
	auto target = find(objList.begin(), objList.end(), _target);
	if (target != objList.end())
	{
		_target->Destroy();
		return true;
	}
	return false;
}

void Engine::ObjectManager::DestroyAll()
{
	auto objTable = pObjectManager->objectTable;
	int layerCount = MaxOfEnum<Layer>();
	for (int i = 0; i < layerCount; i++)
	{
		auto& objList = objTable[i];

		for (auto& iter : objList)
		{
			iter->Destroy();
		}
	}
}

void Engine::ObjectManager::AddObject(GameObject* _obj, Layer _layer)
{
	pObjectManager->objectTable[(int)_layer].push_back(_obj);
}

void Engine::ObjectManager::RemoveObject(GameObject* _obj)
{
	pObjectManager->objectTable[(int)_obj->GetLayer()].remove(_obj);
}



void Engine::ObjectManager::Update()
{
	auto objTable = pObjectManager->objectTable;
	int layerCount = MaxOfEnum<Layer>();
	for (int i = 0; i < layerCount; i++)
	{
		auto& objList = objTable[i];
		for (auto& iter : objList)
		{
			if (!iter->isEnable) continue;
			iter->Update();
		}
	}
}

void Engine::ObjectManager::PostUpdate()
{
	GameObject* target = nullptr;

	auto objTable = pObjectManager->objectTable;
	int layerCount = MaxOfEnum<Layer>();
	for (int i = 0; i < layerCount; i++)
	{
		auto& objList = objTable[i];
		auto iter = objList.begin();
		auto end = objList.end();
		for (; iter != end;)
		{
			target = *iter;


			if (target->IsDestroy())
			{
				if (target->dontDestroy)
				{

					++iter;
					continue;
				}
				iter = objList.erase(iter);
				delete target;
			}
			else
			{
				target->PostUpdate();
				++iter;
			}
		}

	}
	
	
}

bool Engine::ObjectManager::CompareY(GameObject* a, GameObject* b)
{
	return a->transform->position.y < b->transform->position.y;
}

bool Engine::ObjectManager::CompareZ(GameObject* a, GameObject* b)
{
	return a->transform->zOrder > b->transform->zOrder;
}

bool Engine::ObjectManager::IsVisibleCollider()
{
	return pObjectManager->isVisibleCollider;
}

void Engine::ObjectManager::SetVisibleCollider(bool _isVisible)
{
	pObjectManager->isVisibleCollider = _isVisible;
}
