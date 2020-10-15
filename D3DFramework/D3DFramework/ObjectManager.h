#pragma once
#include "GameObject.h"

using namespace std;

namespace PKH
{
	class ObjectManager
	{
	private:
		ObjectManager();
		~ObjectManager();
	public:
		static ObjectManager* GetInstance();

		template<class T>
		GameObject* CreateObject();

		static bool DeleteObject(GameObject* _target);
		static void DestroyAll();

		template<class T>
		GameObject* FindObject();

		template<class T>
		void FindObjectList(list<GameObject*>& outList);

		static void AddObject(GameObject* _obj);

		static void Destroy();
		static void Update();
		static void PostUpdate();
		static void PreRender();
		static void Render();
		static void PostRender();

		static bool Compare(GameObject* a, GameObject* b);

		static bool IsVisibleCollider();
		static void SetVisibleCollider(bool _isVisible);

	private:

		list<GameObject*> objectList;
		list<GameObject*> renderList;
		bool isVisibleCollider = false;
	};


	template<class T>
	inline GameObject * ObjectManager::CreateObject()
	{
		T* pObj = new T();
		if (dynamic_cast<GameObject*>(pObj) == nullptr)
		{
			return nullptr;
		}
		objectList.push_back((GameObject*)pObj);

		return pObj;
	}

	template<class T>
	inline GameObject* ObjectManager::FindObject()
	{
		for (auto& iter : objectList)
		{
			if (dynamic_cast<T*>(iter) == nullptr) continue;

			return iter;
		}
		
		return nullptr;
	}

	template<class T>
	inline void ObjectManager::FindObjectList(list<GameObject*>& outList)
	{
		for (auto& iter : objectList)
		{
			if (dynamic_cast<T*>(iter) == nullptr) continue;

			outList.push_back(iter);
		}
	}

}

