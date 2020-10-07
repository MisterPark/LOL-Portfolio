#pragma once
#include "IComponent.h"

namespace PKH
{
	class Mesh : public PKH::IComponent
	{
	public:
		Mesh();
		virtual ~Mesh();

		virtual void Update() {};
		virtual void Render();

		IDirect3DVertexBuffer9* vb = nullptr;
		IDirect3DIndexBuffer9* triangles = nullptr;
		UINT vertexCount;
		UINT triangleCount;


		// IComponent을(를) 통해 상속됨
		virtual PKH::IComponent * Clone() override;
	};
}


