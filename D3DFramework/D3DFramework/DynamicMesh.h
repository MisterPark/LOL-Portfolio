#pragma once
#include "Mesh.h"

namespace PKH
{
	class DynamicMesh :
		public Mesh
	{
	public:
		explicit DynamicMesh(GameObject* owner);
		explicit DynamicMesh(const DynamicMesh& rhs);
		virtual ~DynamicMesh();
		// Mesh을(를) 통해 상속됨
		virtual IComponent * Clone() override;
	};
}


