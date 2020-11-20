#pragma once
#include "Mesh.h"

namespace PKH
{
	class DynamicMesh :
		public Mesh
	{
		// Mesh을(를) 통해 상속됨
		virtual IComponent * Clone() override;
	};
}


