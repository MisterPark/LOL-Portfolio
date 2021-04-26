#include "stdafx.h"
#include "TrailMesh.h"

TrailMesh::TrailMesh(GameObject* owner)
    :CustomMesh(owner)
{
    CreateCustomMesh();
}

TrailMesh::TrailMesh(const TrailMesh& rhs)
    :CustomMesh(rhs)
{
    CreateCustomMesh();
}

TrailMesh::~TrailMesh()
{
}

void TrailMesh::Update()
{
	float dt = Time::DeltaTime();
	tick += dt;
	if (tick > delay)
	{
		tick = 0.f;

		
	}

	int halfCount = vertexCount / 2;
	Vertex* vertices;
	vertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	for (int i = halfCount - 1; i > 0; i--)
	{
		vertices[i * 2].pos = vertices[(i - 1) * 2].pos;
		vertices[i * 2 + 1].pos = vertices[(i - 1) * 2 + 1].pos;
	}

	vertices[0].pos = end;
	vertices[1].pos = start;

	vertexBuffer->Unlock();
	
	//if (posQ.size() > 0)
	//{
	//	auto& posPair = posQ.front();
	//	
	//	posPair.first
	//}

}

IComponent* TrailMesh::Clone()
{
    return nullptr;
}

void TrailMesh::CreateCustomMesh()
{
	this->vertexCount = 40;
	this->vertexSize = sizeof(Vertex);
	this->triangleCount = 38;

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

	int halfCount = vertexCount / 2;
	for (int i = 0; i < halfCount; i++)
	{
		vertices[i*2] = Vertex(Vector3(1.f / halfCount * i, 1.f, 0.f), 0xFFFFFFFF, 1.f / halfCount * i, 0.f);
		vertices[i*2+1] = Vertex(Vector3(1.f / halfCount * i, 0.f, 0.f), 0xFFFFFFFF, 1.f / halfCount * i, 1.f);
	}

	for (UINT i = 0; i < vertexCount; i++)
	{
		pVertices[i] = vertices[i].pos;
	}

	vertexBuffer->Unlock();

	WORD* indices = nullptr;
	triangles->Lock(0, 0, (void**)&indices, 0);

	for (int i = 0; i < triangleCount; i++)
	{
		WORD index = ((i / 2) + 1) * 2;
		WORD index2= (i % 2) ? index + 1 : index - 1;
		indices[i * 3] = i;
		indices[i * 3 + 1] = index;
		indices[i * 3 + 2] = index2;
	}

	int indexCount = triangleCount * 3;
	for (int i = 0; i < indexCount; i++)
	{
		pIndices[0] = indices[i];
	}

	triangles->Unlock();
}

void TrailMesh::SetTrailPos(const Vector3& start, const Vector3 end)
{
	this->start = start;
	this->end = end;
}
