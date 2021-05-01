#pragma once
#include "Layer.h"
#include "EventSystem.h"

using namespace Engine;

enum class Team
{
	NEUTRAL, BLUE, RED, END
};

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
		virtual void PreUpdate();
		virtual void Update() = 0;
		virtual void PostUpdate();
		virtual void Destroy();
		
		virtual void UpdateEvent() {};

		virtual void OnCollisionEnter(Collider* target);
		// 이벤트 리스너
		virtual void OnHover();
		virtual void OnLeave();

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
		IComponent* RemoveComponent(IComponent* _target);
		IComponent* RemoveComponent(const wstring& _key);

		void DeleteComponent(IComponent* _target);
		void DeleteComponent(const wstring& _key);

		bool IsDestroy();
		bool IsRemove();
		void SetRemove(bool _remove);

		// getter
		IComponent* GetComponent(const wstring& _key);
		template<class T>
		T* GetComponent();
		Transform* GetTransform() const { return transform; } // 수정
		Layer GetLayer() { return this->layer; }
		bool IsVisible();
		bool IsHover();
		bool IsLeave();
		// setter
		bool SetLayer(Layer _layer);
		void SetParent(GameObject* _parent);
		void SetPosition(Vector3 _vPos);
		virtual void Show();
		virtual void Show(bool _visible);
		virtual void Hide();

		// child
		template<class T>
		T* AddChild(const wstring& _tag, T* _child);
		GameObject* RemoveChild(const wstring& _tag);
		template<class T>
		T* RemoveChild(T* _child);
		template<class T>
		T* CreateChild(const wstring& _key);
		void DeleteChild(const wstring& _tag);
		
		//event관련하여
		void AddWeak(Engine::EventBase* evt);
		void OnEventDelete(Engine::EventBase* evt);

		void Freeze();
	public:
		wstring name;
		wstring tag;
		Transform* transform = nullptr;
		
		bool visible = true;
		bool enable = true;
		bool dontDestroy = false;

		GameObject* parent = nullptr;
		map<wstring, GameObject*> children;

		map<wstring, Engine::IComponent*> components;
		std::set<Engine::EventBase*> events;

		Event<MouseEventArg> Hover;
		Event<MouseEventArg> Leave;
	protected:
		bool destroyFlag = false;
		bool removeFlag = false;
	protected:
		// 이벤트 관련 
		bool isHover = false;
		bool isLeave = true;
	private:
		Layer layer = Layer::Default;
		map<wstring, int> childKeyCount;
	public:
		static list<GameObject*> gameObjects;
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
	inline T* GameObject::GetComponent()
	{
		for (auto& iter : components)
		{
			T* com = dynamic_cast<T*>(iter.second);
			if (com)
			{
				return com;
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
	inline T* GameObject::RemoveChild(T* _child)
	{
		for (auto child : children)
		{
			if (child.second == _child) {
				children.erase(child.first);
				return dynamic_cast<T*>(child.second);
			}
		}

		return nullptr;
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

		child->tag = appliedTag;
		children.emplace(child->tag, child);
		child->SetParent(this);
		return dynamic_cast<T*>(child);
	}
}


