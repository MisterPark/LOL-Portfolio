#pragma once
#include "IComponent.h"
#include "IRenderComponent.h"
enum class RenderGroupID :int;
namespace PKH
{
	enum class MeshType
	{
		NONE,
		STATIC_MESH,
		DYNAMIC_MESH,
		TERRAIN_MESH,
		NAV_MESH,
		CUSTOM_MESH,
	};

	class Mesh : public RenderComponent
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

		virtual void Render() PURE;

	public:
		MeshType type = MeshType::NONE;
	protected:
		bool isClone;
		LPDIRECT3DDEVICE9 device = nullptr;
	};
}


