#pragma once
#include "CustomMesh.h"

namespace Engine
{
	class Plane : public CustomMesh
	{
	public:
		explicit Plane(GameObject* owner);
		explicit Plane(const Plane& rhs);
		virtual ~Plane();


		// CustomMesh을(를) 통해 상속됨
		virtual void CreateCustomMesh() override;


		// CustomMesh을(를) 통해 상속됨
		virtual Engine::IComponent* Clone() override;

	};
}


