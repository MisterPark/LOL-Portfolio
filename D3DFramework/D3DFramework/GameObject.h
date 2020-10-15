#pragma once


using namespace PKH;


namespace PKH
{
	class IComponent;


	class GameObject
	{
	public:
		GameObject();
		virtual ~GameObject();


		virtual void Update() = 0;
		virtual void Render();
		virtual void Die();
		virtual void OnCollision(GameObject* target);
		virtual void PostRender() {};

		// 방향으로 이동
		// 내부에서 정규화 해줌.
		void Move(Vector3 _direction);
		// 위치로 이동
		void MoveToTarget(Vector3 _target);
		// 타겟 따라가기
		void FollowTarget(const GameObject* _target);
		void FollowTarget(const Transform& _targetTransform);
		void FollowTarget(const Vector3& _targetPos);
		// 타겟 오브젝트 방향으로 회전
		void FaceTarget(const GameObject* _target);
		void FaceTarget(const Transform& _targetTransform);
		void FaceTarget(const Vector3& _targetPos);


		void SetPosition(Vector3 _vPos);

		template<class T>
		IComponent* AddComponent(const wstring& _key);

		IComponent* GetComponent(const wstring& _key);
		Transform* GetTransform() { return transform; } //수정


	public:
		Transform* transform = nullptr;

		float moveSpeed = 1.f;
		bool isDead = false;
		bool isVisible = true;
		bool isEnable = true;
		bool isAlliance = true;

		map<wstring, PKH::IComponent*> components;

		
	};
	template<class T>
	inline IComponent* GameObject::AddComponent(const wstring & _key)
	{
		T* comp = new T;
		if (dynamic_cast<IComponent*>(comp) == nullptr)
		{
			delete comp;
			return nullptr;
		}

		comp->gameObject = this;
		components[_key] = comp;

		return comp;
	}
}


