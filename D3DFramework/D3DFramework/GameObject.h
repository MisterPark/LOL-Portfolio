#pragma once
#include "Layer.h"

using namespace Engine;


namespace Engine
{
	class IComponent;
	class Transform;
	class Collider;

	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();
		
		virtual void Initialize() = 0;
		virtual void Release() = 0;
		virtual void Update() = 0;
		virtual void PostUpdate();

		virtual void Destroy();

		virtual void OnCollisionEnter(Collider* target);

		// 방향으로 이동
		// 내부에서 정규화 해줌.
		void Move(Vector3 _direction);
		void Move(Vector3 _direction, float _speed);
		// 위치로 이동
		void MoveToTarget(Vector3 _target);
		void MoveToTarget(Vector3 _target, float _speed);
		// 타겟 따라가기
		void FollowTarget(const GameObject* _target);
		void FollowTarget(const Transform& _targetTransform);
		void FollowTarget(const Vector3& _targetPos);
		// 타겟 오브젝트 방향으로 회전
		void FaceTarget(const GameObject* _target);
		void FaceTarget(const Transform& _targetTransform);
		void FaceTarget(const Vector3& _targetPos);
		// 빌보드
		// GameObject::Update() 호출 후에 호출
		void Billboard();
		void BillboardYaw();

		template<class T>
		IComponent* AddComponent(const wstring& _key);
		IComponent* AddComponent(const wstring& _key, IComponent* _component);
		void ReleaseComponents();
		void RemoveComponent(IComponent* _target);
		void RemoveComponent(const wstring& _key);

		bool IsDestroy();


		// getter
		IComponent* GetComponent(const wstring& _key);
		template<class T>
		IComponent* GetComponent();
		Transform* GetTransform() const { return transform; } // 수정
		Layer GetLayer() { return this->layer; }

		// setter
		bool SetLayer(Layer _layer);
		void SetParent(GameObject* _parent);
		void SetPosition(Vector3 _vPos);
		void Show();
		void Hide();

		template<class T>
		T* AddChild(const wstring& _tag, T* _child);
		template<class T>
		T* CreateChild(const wstring& _key);
		//event관련하여
		void AddWeak(Engine::EventBase* evt);
		void OnEventDelete(Engine::EventBase* evt);
	public:
		wstring name;
		wstring tag;
		Transform* transform = nullptr;
		
		bool isVisible = true;
		bool isEnable = true;
		bool dontDestroy = false;

		GameObject* parent = nullptr;
		map<wstring, GameObject*> children;

		map<wstring, Engine::IComponent*> components;
		std::set<Engine::EventBase*> events;
	protected:
		bool destroyFlag = false;
	private:
		Layer layer = Layer::Default;
		map<wstring, int> childKeyCount;
	};

	template<class T>
	inline IComponent* GameObject::AddComponent(const wstring & _key)
	{
		T* comp = new T(this);
		if (dynamic_cast<IComponent*>(comp) == nullptr)
		{
			delete comp;
			return nullptr;
		}

		comp->gameObject = this;
		comp->transform = this->transform;
		components[_key] = comp;

		return comp;
	}
	template<class T>
	inline IComponent* GameObject::GetComponent()
	{
		for (auto& iter : components)
		{
			if (dynamic_cast<T*>(iter.second))
			{
				return iter.second;
			}
		}
		return nullptr;
	}
	template<class T>
	inline T* GameObject::AddChild(const wstring& _tag, T* _child)
	{
		if (_child == nullptr) return nullptr;

		wstring appliedTag = _tag.c_str();
		int count = 0;

		auto findIter = childKeyCount.find(_tag);
		if (findIter != childKeyCount.end())
		{
			count = ++findIter->second;
		}
		else
		{
			childKeyCount.emplace(_tag, count);
		}

		if (count != 0)
		{
			WCHAR digit[16] = {};
			swprintf_s(digit, L"%d", count);
			appliedTag += digit;
		}

		_child->tag = appliedTag;
		children.emplace(_child->tag, _child);
		_child->SetParent(this);
		return _child;
	}
	template<class T>
	inline T* GameObject::CreateChild(const wstring& _tag)
	{
		GameObject* child = new T();

		wstring appliedTag = _tag.c_str();
		int count = 0;

		auto findIter = childKeyCount.find(_tag);
		if (findIter != childKeyCount.end())
		{
			count = findIter->second++;
		}
		else
		{
			childKeyCount.emplace(_tag, count);
		}

		if (count != 0)
		{
			WCHAR digit[16] = {};
			swprintf_s(digit, L"%d", count);
			appliedTag += digit;
		}

		child->tag = appliedTag;
		children.emplace(child->tag, child);
		child->SetParent(this);
		return child;
	}
}


