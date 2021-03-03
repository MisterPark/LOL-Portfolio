#pragma once

namespace Engine
{
	class Scene
	{
	public:
		virtual ~Scene();
		virtual void OnLoaded() = 0;
		virtual void OnUnloaded() = 0;

		virtual void Update();
		virtual void PostUpdate();

		template<class T>
		GameObject* CreateObject(Layer layer = Layer::Default);
		bool		DeleteObject(GameObject* _target);
		void		DeleteAllObject();
		void		DestroyAll();
		template<class T>
		GameObject* FindObject();

		void		AddObject(GameObject* _obj, Layer _layer = Layer::Default);
		void		RemoveObject(GameObject* _obj);

		template<typename _Layer>
		GameObject* GetNearestObject(GameObject _self, _Layer _layer);
		template<typename _Layer, typename... _Layers>
		GameObject* GetNearestObject(GameObject _self, _Layer _layer, _Layers... _layers);


	protected:
		list<GameObject*> objectTable[MaxOfEnum<Layer>()];
	};



	template<class T>
	inline GameObject* Scene::CreateObject(Layer layer)
	{
		T* pObj = new T();
		GameObject* obj = dynamic_cast<GameObject*>(pObj);
		if (obj == nullptr)
		{
			return nullptr;
		}

		if (obj->SetLayer(layer) == false)
		{
			objectTable[(int)layer].push_back(obj);
		}

		return obj;
	}

	template<class T>
	inline GameObject* Scene::FindObject()
	{
		constexpr int layerCount = MaxOfEnum<Layer>();
		for (int i = 0; i < layerCount; i++)
		{
			auto& objectList = objectTable[i];
			for (auto& iter : objectList)
			{
				if (dynamic_cast<T*>(iter) == nullptr) continue;
				return iter;
			}
		}
		return nullptr;
	}

	template<typename _Layer>
	inline GameObject* Scene::GetNearestObject(GameObject _self, _Layer _layer)
	{
		float min = FLT_MAX;
		GameObject* minObj = nullptr;

		int layer = (int)_layer;
		auto& objectList = objectTable[layer];
		for (auto& iter : objectList)
		{
			Vector3 to = _self.transform->position - iter->transform->position;
			float dist = to.Length();
			if (dist < min)
			{
				min = dist;
				minObj = iter;
			}
		}

		return minObj;
	}

	template<typename _Layer, typename ..._Layers>
	inline GameObject* Scene::GetNearestObject(GameObject _self, _Layer _layer, _Layers ..._layers)
	{
		float min = FLT_MAX;
		GameObject* minObj = nullptr;

		int layer = (int)_layer;
		auto& objectList = objectTable[layer];
		for (auto& iter : objectList)
		{
			Vector3 to = _self.transform->position - iter->transform->position;
			float dist = to.Length();
			if (dist < min)
			{
				min = dist;
				minObj = iter;
			}
		}

		float min2 = FLT_MAX;
		GameObject* minObj2 = GetNearestObject(_layers...);
		if (minObj2 != nullptr)
		{
			Vector3 to2 = _self.transform->position - minObj2->transform->position;
			min2 = to2.Length();
		}

		if (min2 < min)
		{
			min = min2;
			minObj = minObj2;
		}

		return minObj;
	}

}