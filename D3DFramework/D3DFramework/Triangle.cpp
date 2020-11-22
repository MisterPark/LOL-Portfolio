#include "stdafx.h"
#include "Triangle.h"

PKH::Triangle::Triangle(GameObject* owner)
	:CustomMesh(owner)
{
	CreateCustomMesh();
}

PKH::Triangle::Triangle(const Triangle& rhs)
	:CustomMesh(rhs)
{
	CreateCustomMesh();
}

Triangle::~Triangle()
{
}

void PKH::Triangle::CreateCustomMesh()
{
	this->vertexCount = 3;
	this->triangleCount = 2;

	RenderManager::LockDevice();
	RenderManager::GetDevice()->CreateVertexBuffer(
		vertexCount * sizeof(VertexColor),
		D3DUSAGE_WRITEONLY,
		VertexColor::FVF,
		D3DPOOL_MANAGED,
		&vertexBuffer,
		0);

	RenderManager::GetDevice()->CreateIndexBuffer(
		triangleCount * 3 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&triangles,
		0);
	RenderManager::UnlockDevice();

	VertexColor* vertices;
	vertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	vertices[0] = VertexColor(-0.1f, -0.1f, 0.f, D3DCOLOR_XRGB(0, 255, 0));
	vertices[1] = VertexColor(0.f, 0.1f, 0.f, D3DCOLOR_XRGB(255, 0, 0));
	vertices[2] = VertexColor(0.1f, -0.1f, 0.f, D3DCOLOR_XRGB(0, 255, 0));
	vertexBuffer->Unlock();

	WORD* indices = nullptr;
	triangles->Lock(0, 0, (void**)&indices, 0);
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 2; indices[4] = 1; indices[5] = 0;
	triangles->Unlock();
}

void Triangle::Update()
{
}

PKH::IComponent * PKH::Triangle::Clone()
{
	return new Triangle(*this);
}

