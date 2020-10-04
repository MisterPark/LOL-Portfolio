#pragma once

namespace PKH
{
	class Mesh
	{
	public:
		Mesh();
		virtual ~Mesh();

		virtual void Update() = 0;
		virtual void Render() = 0;

		IDirect3DVertexBuffer9* vb = nullptr;
		IDirect3DIndexBuffer9* triangles = nullptr;

		Transform transform;
	};
}


