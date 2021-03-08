#include "stdafx.h"
#include "CustomMesh.h"

using namespace Engine;

Engine::CustomMesh::CustomMesh(GameObject* owner)
	:Mesh(owner)
{
	// 머테리얼
	ZeroMemory(&material, sizeof(D3DMATERIAL9));


	material.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	material.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	material.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
	material.Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 1.f);
	material.Power = 0.f;

	type = MeshType::CUSTOM_MESH;
}

Engine::CustomMesh::CustomMesh(const CustomMesh& rhs)
	:Mesh(rhs)
{
	
}

CustomMesh::~CustomMesh()
{
	vertexBuffer->Release();
	triangles->Release();
	Safe_Delete_Array(&pVertices);
	Safe_Delete_Array(&pIndices);
}

void Engine::CustomMesh::RenderSubset(int index)
{
	device->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));
	device->SetFVF(Vertex::FVF);
	device->SetIndices(triangles);
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, triangleCount);
}

IDirect3DTexture9* Engine::CustomMesh::GetSubsetTexture(int index)
{
	Texture* texture = RenderManager::GetTexture(textureKey);
	if (texture == nullptr) return nullptr;

	return texture->pTexture;
}


IDirect3DVertexBuffer9 * Engine::CustomMesh::GetVertexBuffer()
{
	return vertexBuffer;
}

Vector3* Engine::CustomMesh::GetVertices()
{
	return pVertices;
}

DWORD* Engine::CustomMesh::GetIndices()
{
	return pIndices;
}

ULONG Engine::CustomMesh::GetVertexCount()
{
	return this->vertexCount;
}

ULONG Engine::CustomMesh::GetVertexSize()
{
	return this->vertexSize;
}

ULONG Engine::CustomMesh::GetFaceCount()
{
	return this->triangleCount;
}

void Engine::CustomMesh::SetColor(D3DCOLOR color)
{
	Vertex* vertices;
	vertexBuffer->Lock(0, 0, (void**)&vertices, 0);
	for (UINT i = 0; i < vertexCount; i++)
	{
		vertices[i].color = color;
	}
	
	vertexBuffer->Unlock();
}

void Engine::CustomMesh::SetTexture(const wstring& id)
{
	textureKey = id;
}

void Engine::CustomMesh::SetVertexPos(UINT index, const Vector3& pos)
{
	Vertex* vertices;
	vertexBuffer->Lock(0, 0, (void**)&vertices, 0);
	vertices[index].pos.x = pos.x;
	vertices[index].pos.y = pos.y;
	vertices[index].pos.z = pos.z;
	vertexBuffer->Unlock();
}

void Engine::CustomMesh::SetUV(UINT index, float u, float v)
{
	Vertex* vertices;
	vertexBuffer->Lock(0, 0, (void**)&vertices, 0);
	vertices[index].u = u;
	vertices[index].v = v;
	vertexBuffer->Unlock();
}

void Engine::CustomMesh::SetBlendMode(BlendMode _mode)
{
	this->blendMode = _mode;
}

void Engine::CustomMesh::SetCullMode(CullMode _mode)
{
	cullMode = _mode;
}

void Engine::CustomMesh::SetZReadMode(ZReadMode _mode)
{
	zReadMode = _mode;
}

void Engine::CustomMesh::SetZWriteMode(ZWriteMode _mode)
{
	zWriteMode = _mode;
}

void Engine::CustomMesh::SetLightMode(LightMode _mode)
{
	lightMode = _mode;
}


