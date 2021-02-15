#include "stdafx.h"
#include "Mesh.h"

PKH::Mesh::Mesh(GameObject* owner)
	:RenderComponent(owner)
	,isClone(false)
{
	type = MeshType::NONE;
}

PKH::Mesh::Mesh(const Mesh& rhs)
	:RenderComponent(rhs)
	,isClone(true)
	,type(rhs.type)
{
}

PKH::Mesh::~Mesh()
{
}

int PKH::Mesh::GetSubsetCount()
{
	return 1;
}

void PKH::Mesh::RenderSubset(int index)
{
}

IDirect3DTexture9* PKH::Mesh::GetSubsetTexture(int index)
{
	return nullptr;
}
