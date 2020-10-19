#include "stdafx.h"
#include "Plane.h"

PKH::Plane::Plane()
{
	this->vertexCount = 4;
	this->triangleCount = 2;

	D2DRenderManager::GetDevice()->CreateVertexBuffer(
		vertexCount * sizeof(VertexUV),
		D3DUSAGE_WRITEONLY,
		VertexColor::FVF,
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

	VertexColor* vertices;
	vb->Lock(0, 0, (void**)&vertices, 0);

	vertices[0] = VertexColor(-1.f, 0.f, -1.f, D3DCOLOR_XRGB(255, 255, 255));
	vertices[1] = VertexColor(-1.f, 0.f, 1.f, D3DCOLOR_XRGB(255, 255, 255));
	vertices[2] = VertexColor(1.f, 0.f, 1.f, D3DCOLOR_XRGB(255, 255, 255));
	vertices[3] = VertexColor(1.f, 0.f, -1.f, D3DCOLOR_XRGB(255, 255, 255));
	vb->Unlock();

	WORD* indices = nullptr;
	triangles->Lock(0, 0, (void**)&indices, 0);
	indices[0] = 0; indices[1] = 1; indices[2] = 3;
	indices[3] = 1; indices[4] = 2; indices[5] = 3;
	triangles->Unlock();
}

PKH::Plane::~Plane()
{
}
