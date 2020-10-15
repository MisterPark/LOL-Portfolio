#include "stdafx.h"
#include "Triangle02.h"

PKH::Triangle02::Triangle02()
{
}

Triangle02::Triangle02(D3DCOLOR color)
{
	this->vertexCount = 3;
	this->triangleCount = 2;

	D2DRenderManager::GetDevice()->CreateVertexBuffer(
		vertexCount * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&vb,
		0);

	D2DRenderManager::GetDevice()->CreateIndexBuffer(
		triangleCount * 3 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&triangles,
		0);

	Vertex* vertices;
	vb->Lock(0, 0, (void**)&vertices, 0);

	vertices[0] = Vertex(-0.1f, -0.1f, 0.f, color);
	vertices[1] = Vertex(0.f, 0.1f, 0.f, color);
	vertices[2] = Vertex(0.1f, -0.1f, 0.f, color);
	vb->Unlock();

	WORD* indices = nullptr;
	triangles->Lock(0, 0, (void**)&indices, 0);
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 2; indices[4] = 1; indices[5] = 0;
	triangles->Unlock();


}

Triangle02::~Triangle02()
{
}

void Triangle02::Update()
{
}

PKH::IComponent * PKH::Triangle02::Clone()
{
	return new Triangle02(*this);
}
