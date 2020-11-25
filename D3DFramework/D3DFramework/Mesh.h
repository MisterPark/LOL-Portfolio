#pragma once
#include "IComponent.h"

namespace PKH
{
	class Mesh : public IComponent
	{
	public:
		explicit Mesh(GameObject* owner);
		explicit Mesh(const Mesh& rhs);
		virtual ~Mesh();


	public:
		virtual IComponent* Clone() = 0;

	protected:
		bool isClone;
		LPDIRECT3DDEVICE9 device = nullptr;
	};
}


