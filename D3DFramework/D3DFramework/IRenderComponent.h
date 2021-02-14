#pragma once
#include "IComponent.h"
#include <combaseapi.h>
enum class RenderGroupID :int;
class RenderComponent : public PKH::IComponent
{
protected:
	RenderComponent(GameObject* owner) :IComponent(owner) {}
public:
	virtual void Render() PURE;
	RenderGroupID renderGroupID;
};
class GameObjectRenderComponent : public RenderComponent
{
public:
	GameObjectRenderComponent(GameObject* owner) :RenderComponent(owner) {}
	void Render()
	{ 
		if (this->gameObject != nullptr)
		{
			this->gameObject->Render();
		}
	}
	IComponent* Clone()
	{
		return nullptr;
	}
};

class UIRenderComponent : public RenderComponent
{
public:
	UIRenderComponent(GameObject* owner) :RenderComponent(owner) {}
	void Render();
	IComponent* Clone()
	{
		return nullptr;
	}
};