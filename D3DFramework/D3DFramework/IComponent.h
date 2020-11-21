#pragma once


namespace PKH
{
	class GameObject;
	class Transform;

	class IComponent
	{
	public:
		IComponent();
		IComponent(const IComponent& rhs);
		virtual ~IComponent();

		virtual void Update();

		virtual IComponent* Clone() = 0;


	public:
		GameObject* gameObject = nullptr;
		Transform* transform = nullptr;
	};


}
