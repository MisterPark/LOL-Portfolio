#pragma once
#include "IComponent.h"
#include "Vector3.h"

namespace PKH
{
	class Transform : public IComponent
	{
	public:
		Transform();
		~Transform();

		virtual void Update();

		Vector3 position{ 0.f,0.f,0.f };
		Vector3 rotation{ 0.f,0.f,0.f };
		Vector3 scale{ 1.f,1.f,1.f };

		Vector3 target{ 0,1,0 };


		// IComponent을(를) 통해 상속됨
		virtual IComponent* Clone() override;

	};
}


