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

	vertices[0] = Vertex(Vector3(-0.1f, -0.1f, 0.f), D3DCOLOR_XRGB(0, 255, 0),0,0);
	vertices[1] = Vertex(Vector3(0.f, 0.1f, 0.f), D3DCOLOR_XRGB(255, 0, 0),0.5f,1);
	vertices[2] = Vertex(Vector3(0.1f, -0.1f, 0.f), D3DCOLOR_XRGB(0, 255, 0),1,0);

	for (int i = 0; i < vertexCount; i++)
	{
		pVertices[i] = vertices[i].pos;
	}

	vertexBuffer->Unlock();

	WORD* indices = nullptr;
	triangles->Lock(0, 0, (void**)&indices, 0);
	indices[0] = 0; indices[1] = 1; indices[2] = 2;
	indices[3] = 2; indices[4] = 1; indices[5] = 0;

	int indexCount = triangleCount * 3;
	for (int i = 0; i < indexCount; i++)
	{
		pIndices[0] = indices[i];
	}

	triangles->Unlock();
}

void Triangle::Update()
{
}

PKH::IComponent * PKH::Triangle::Clone()
{
	return new Triangle(*this);
}

