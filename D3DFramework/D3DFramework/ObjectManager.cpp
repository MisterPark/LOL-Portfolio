#include "stdafx.h"
#include "ObjectManager.h"
#include "SkyBox.h"
#include "Cursor.h"
#include "Inventory.h"
#include "PlayerInfoPanel.h"

using namespace PKH;

PKH::ObjectManager* pObjectManager = nullptr;
int lastUid = 0;

PKH::ObjectManager::ObjectManager()
{
	Cursor::GetInstance();
	Inventory::GetInstance();
}

PKH::ObjectManager::~ObjectManager()
{
	
	Release();
	Cursor::Destroy();
	Inventory::Destroy();
}

ObjectManager * PKH::ObjectManager::GetInstance()
{
	if (pObjectManager == nullptr)
	{
		pObjectManager = new ObjectManager;
	}
	return pObjectManager;
}

void PKH::ObjectManager::Destroy()
{
	delete pObjectManager;
	pObjectManager = nullptr;
}

void PKH::ObjectManager::Release()
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


bool PKH::ObjectManager::DeleteObject(GameObject * _target)
{
	auto& objList = pObjectManager->objectTable[(int)_target->GetLayer()];
	
	auto target = find(objList.begin(), objList.end(), _target);
	if (target != objList.end())
	{
		_target->Destroy();
		return true;
	}
	return false;
}

void PKH::ObjectManager::DestroyAll()
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

void PKH::ObjectManager::AddObject(GameObject* _obj, Layer _layer)
{
	pObjectManager->objectTable[(int)_layer].push_back(_obj);
}

void PKH::ObjectManager::RemoveObject(GameObject* _obj)
{
	pObjectManager->objectTable[(int)_obj->GetLayer()].remove(_obj);
}



void PKH::ObjectManager::Update()
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

	Cursor::GetInstance()->Update();
	Inventory::Update();
}

void PKH::ObjectManager::PostUpdate()
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

void PKH::ObjectManager::PreRender()
{

}

void PKH::ObjectManager::Render()
{

	pObjectManager->renderList.clear();

	Vector3 camPos = Camera::main->GetPosition();
	
	auto objTable = pObjectManager->objectTable;
	int layerCount = (int)Layer::UI;
	int ground = (int)Layer::Ground;
	for (int i = 0; i < layerCount; i++)
	{
		auto& objList = objTable[i];
		if (i <= ground)
		{
			for (auto& iter : objList)
			{
				if (iter->isVisible == false)continue;
				pObjectManager->renderList.push_back(iter);
			}
		}
		else
		{
			for (auto& iter : objList)
			{
				if (iter->isVisible == false)continue;
				if (!Frustum::Intersect(&iter->transform->position, 1.f)) continue;
				pObjectManager->renderList.push_back(iter);
			}
		}
		
	}
	// z값으로 정렬
	pObjectManager->renderList.sort(CompareZ);
	// 오브젝트 렌더링
	for (auto& obj : pObjectManager->renderList)
	{
		obj->Render();
	}
	
	auto uiList = pObjectManager->objectTable[(int)Layer::UI];
	for (auto& iter : uiList)
	{
		if (iter->isVisible == false) continue;
		iter->Render();
	}

	auto hudList = pObjectManager->objectTable[(int)Layer::HUD];
	for (auto& iter : hudList)
	{
		if (iter->isVisible == false) continue;
		iter->Render();
	}
	
	// 디버그용
	//TimeManager::RenderFPS();
}

void PKH::ObjectManager::PostRender()
{ 
	
	if (pObjectManager->isVisibleCollider)
	{
		auto objTable = pObjectManager->objectTable;
		int layerCount = MaxOfEnum<Layer>();
		for (int i = 0; i < layerCount; i++)
		{
			auto& objList = objTable[i];
			for (auto& iter : objList)
			{
				iter->PostRender();
			}
		}
	}
	
	//Inventory::Render();
	Cursor::GetInstance()->Render();
}

bool PKH::ObjectManager::CompareY(GameObject* a, GameObject* b)
{
	return a->transform->position.y < b->transform->position.y;
}

bool PKH::ObjectManager::CompareZ(GameObject* a, GameObject* b)
{
	return a->transform->zOrder > b->transform->zOrder;
}

bool PKH::ObjectManager::IsVisibleCollider()
{
	return pObjectManager->isVisibleCollider;
}

void PKH::ObjectManager::SetVisibleCollider(bool _isVisible)
{
	pObjectManager->isVisibleCollider = _isVisible;
}
