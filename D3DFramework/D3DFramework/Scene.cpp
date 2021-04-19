#include "stdafx.h"
#include "Scene.h"

Engine::Scene::~Scene()
{
	DeleteAllObject();
}

void Engine::Scene::PreUpdate()
{
	auto objTable = objectTable;
	constexpr int layerCount = MaxOfEnum<Layer>();
	for (int i = 0; i < layerCount; i++)
	{
		auto& objList = objTable[i];
		for (auto& iter : objList)
		{
			//if (!iter->enable) continue;
			iter->PreUpdate();
		}
	}
}

void Engine::Scene::Update()
{
	auto objTable = objectTable;
	constexpr int layerCount = MaxOfEnum<Layer>();
	for (int i = 0; i < layerCount; i++)
	{
		auto& objList = objTable[i];
		for (auto& iter : objList)
		{
			//if (!iter->enable) continue;
			iter->Update();
		}
	}
}

void Engine::Scene::PostUpdate()
{
	GameObject* target = nullptr;

	auto objTable = objectTable;
	constexpr int layerCount = MaxOfEnum<Layer>();
	for (int i = 0; i < layerCount; i++)
	{
		auto& objList = objTable[i];
		auto iter = objList.begin();
		auto end = objList.end();
		for (; iter != end;)
		{
			target = *iter;


			if (target->IsDestroy() && target->dontDestroy == false)
			{
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

bool Engine::Scene::DeleteObject(GameObject* _target)
{
	if (_target == nullptr) return false;
	auto& objList = objectTable[(int)_target->GetLayer()];

	auto target = find(objList.begin(), objList.end(), _target);
	if (target != objList.end())
	{
		_target->Destroy();
		return true;
	}
	return false;
}

void Engine::Scene::DeleteAllObject()
{
	auto objTable = objectTable;
	constexpr int layerCount = MaxOfEnum<Layer>();
	for (int i = 0; i < layerCount; i++)
	{
		auto& objList = objTable[i];

		for (auto& iter : objList)
		{
			delete iter;
		}

		objList.clear();
	}

	
}

void Engine::Scene::DestroyAll()
{
	auto objTable = objectTable;
	constexpr int layerCount = MaxOfEnum<Layer>();
	for (int i = 0; i < layerCount; i++)
	{
		auto& objList = objTable[i];

		for (auto& iter : objList)
		{
			iter->Destroy();
		}
	}
}

void Engine::Scene::AddObject(GameObject* _obj, Layer _layer)
{
	objectTable[(int)_layer].push_back(_obj);
}

void Engine::Scene::RemoveObject(GameObject* _obj)
{
	objectTable[(int)_obj->GetLayer()].remove(_obj);
}
