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
		virtual IComponent* Clone()		PURE;
		virtual Vector3* GetVertices()	PURE;
		virtual DWORD* GetIndices()		PURE;
		virtual ULONG GetVertexCount()	PURE;
		virtual ULONG GetVertexSize()	PURE;
		virtual ULONG GetFaceCount()	PURE;

	protected:
		bool isClone;
		LPDIRECT3DDEVICE9 device = nullptr;
	};
}


