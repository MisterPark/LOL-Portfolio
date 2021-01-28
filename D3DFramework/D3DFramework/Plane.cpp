#include "stdafx.h"
#include "Plane.h"

PKH::Plane::Plane(GameObject* owner)
	:CustomMesh(owner)
{
	CreateCustomMesh();
}

PKH::Plane::Plane(const Plane& rhs)
	:CustomMesh(rhs)
{
	CreateCustomMesh();
}

PKH::Plane::~Plane()
{
}

void PKH::Plane::CreateCustomMesh()
{
	this->vertexCount = 4;
	this->vertexSize = sizeof(Vertex);
	this->triangleCount = 2;

	RenderManager::LockDevice();
	RenderManager::GetDevice()->CreateVertexBuffer(
		vertexCount * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
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

	pVertices = new Vector3[vertexCount];
	pIndices = new DWORD[triangleCount * 3];

	Vertex* vertices;
	vertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	vertices[0] = Vertex(Vector3(-1.f, 0.f, -1.f), 0xFFFFFFFF, 0, 1);
	vertices[1] = Vertex(Vector3(-1.f, 0.f, 1.f), 0xFFFFFFFF, 0, 0);
	vertices[2] = Vertex(Vector3(1.f, 0.f, 1.f), 0xFFFFFFFF, 1, 0);
	vertices[3] = Vertex(Vector3(1.f, 0.f, -1.f), 0xFFFFFFFF, 1, 1);

	for (int i = 0; i < vertexCount; i++)
	{
		pVertices[i] = vertices[i].pos;
	}

	vertexBuffer->Unlock();

	WORD* indices = nullptr;
	triangles->Lock(0, 0, (void**)&indices, 0);
	indices[0] = 0; indices[1] = 1; indices[2] = 3;
	indices[3] = 1; indices[4] = 2; indices[5] = 3;

	int indexCount = triangleCount * 3;
	for (int i = 0; i < indexCount; i++)
	{
		pIndices[0] = indices[i];
	}

	triangles->Unlock();
}

PKH::IComponent* PKH::Plane::Clone()
{
	return new Plane(*this);
}
