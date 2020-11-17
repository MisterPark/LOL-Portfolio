#pragma once
#include "IComponent.h"

namespace PKH
{
	class Mesh : public IComponent
	{
	public:
		Mesh();
		Mesh(const Mesh& rhs);
		virtual ~Mesh();


	public:
		virtual IComponent* Clone() = 0;

	protected:
		bool isClone;
	};
}


