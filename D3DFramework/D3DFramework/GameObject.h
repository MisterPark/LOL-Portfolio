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
		virtual void Render() = 0;
		virtual void Die();
		virtual void OnCollision(GameObject* target);

		void Move(Vector3 _target);

		template<class T>
		IComponent* AddComponent(const wstring& _key);

		IComponent* GetComponent(const wstring& _key);

	public:
		Transform* transform = nullptr;

		float moveSpeed = 1.f;
		bool isDead = false;
		bool isVisible = true;
		bool isEnable = true;

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


