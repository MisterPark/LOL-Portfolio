#pragma once
#include "Layer.h"

using namespace PKH;


namespace PKH
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

		// �������� �̵�
		// ���ο��� ����ȭ ����.
		void Move(Vector3 _direction);
		void Move(Vector3 _direction, float _speed);
		// ��ġ�� �̵�
		void MoveToTarget(Vector3 _target);
		void MoveToTarget(Vector3 _target, float _speed);
		// Ÿ�� ���󰡱�
		void FollowTarget(const GameObject* _target);
		void FollowTarget(const Transform& _targetTransform);
		void FollowTarget(const Vector3& _targetPos);
		// Ÿ�� ������Ʈ �������� ȸ��
		void FaceTarget(const GameObject* _target);
		void FaceTarget(const Transform& _targetTransform);
		void FaceTarget(const Vector3& _targetPos);
		// �����
		// GameObject::Update() ȣ�� �Ŀ� ȣ��
		void Billboard();
		void BillboardYaw();


		void SetPosition(Vector3 _vPos);

		template<class T>
		IComponent* AddComponent(const wstring& _key);
		IComponent* AddComponent(const wstring& _key, IComponent* _component);
		void ReleaseComponents();
		void RemoveComponent(IComponent* _target);
		void RemoveComponent(const wstring& _key);


		// getter
		IComponent* GetComponent(const wstring& _key);
		template<class T>
		IComponent* GetComponent();
		Transform* GetTransform() const { return transform; } //����
		Layer GetLayer() { return this->layer; }

		bool IsDestroy();
		
		// setter
		bool SetLayer(Layer _layer);
		
	public:
		wstring name;
		Transform* transform = nullptr;
		
		bool isVisible = true;
		bool isEnable = true;
		bool dontDestroy = false;

		GameObject* parent = nullptr;
		map<wstring, GameObject*> children;

		map<wstring, PKH::IComponent*> components;
	protected:
		bool destroyFlag = false;
	private:
		Layer layer = Layer::Default;
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
}


