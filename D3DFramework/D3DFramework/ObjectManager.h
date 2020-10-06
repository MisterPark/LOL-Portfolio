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
		T* pObj = new T;
		if (dynamic_cast<GameObject*>(pObj) == nullptr)
		{
			return nullptr;
		}
		objectList.push_back((GameObject*)pObj);

		return pObj;
	}

}

