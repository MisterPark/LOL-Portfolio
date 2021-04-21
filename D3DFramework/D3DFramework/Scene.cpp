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

	auto& objTable = objectTable;
	constexpr int layerCount = MaxOfEnum<Layer>();
	for (int i = 0; i < layerCount; i++)
	{
		auto& objList = objTable[i];
		auto iter = objList.begin();
		auto end = objList.end();
		for (; iter != end;)
		{
			target = *iter;

			if (target->IsRemove())
			{
				target->SetRemove(false);
				iter = objList.erase(iter);
				continue;
			}
			else if (target->IsDestroy() && target->dontDestroy == false)
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

	for (auto& changeObj : changeList)
	{
		objectTable[(int)changeObj.origin].remove(changeObj.obj);
		objectTable[(int)changeObj.change].push_back(changeObj.obj);
	}
	changeList.clear();
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
	_obj->SetRemove(true);
}

void Engine::Scene::ChangeLayer(GameObject* _obj, Layer _origin, Layer _change)
{
	ChangeLayerNode node;
	node.obj = _obj;
	node.origin = _origin;
	node.change = _change;

	changeList.push_back(node);
}
