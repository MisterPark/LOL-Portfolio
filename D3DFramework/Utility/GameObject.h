#pragma once

class Component;

class GameObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;

	virtual void Update() = 0;

	template<class T>
	void AddComponent(const wstring& _key);
	template<class T>
	T GetComponent(const std::wstring& _name);

public:
	
	map<wstring, Component*> components;
};

template<class T>
inline void GameObject::AddComponent(const wstring & _key)
{
	T* comp = new T();
	comp->componentName = _key;
	comp->gameObject = this;
	components[_key] = comp;
}

template<class T>
inline T GameObject::GetComponent(const std::wstring & _name)
{
	return components[_name];
}
