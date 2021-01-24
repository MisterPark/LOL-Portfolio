#pragma once
#include "GameObject.h"

namespace PKH
{
	class Transform;

	class IComponent
	{
	public:
		explicit IComponent(GameObject* owner);
		explicit IComponent(const IComponent& rhs);
		virtual ~IComponent();

		virtual void Update();
		virtual void PostUpdate();

		virtual IComponent* Clone() = 0;


	public:
		GameObject* gameObject = nullptr;
		Transform* transform = nullptr;
		bool visible = true;
		bool enable = true;
	};


}
