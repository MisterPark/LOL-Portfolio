#pragma once
class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	virtual void Render() = 0;
	
	IDirect3DVertexBuffer9* vb = nullptr;
	IDirect3DIndexBuffer9* triangles = nullptr;
};

