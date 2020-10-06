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

		template<class T>
		void AddComponent(const wstring& _key);

	public:
		Transform transform;
		bool isDead = false;
		bool isVisible = true;
		bool isEnable = true;

		map<wstring, PKH::IComponent*> components;
	};
	template<class T>
	inline void GameObject::AddComponent(const wstring & _key)
	{
		T* comp = new T;
		if (dynamic_cast<IComponent*>(comp) == nullptr)
		{
			delete comp;
			return;
		}

		comp->gameObject = this;
		components[_key] = comp;
	}
}


