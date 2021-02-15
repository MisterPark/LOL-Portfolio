#include "stdafx.h"
#include "Mesh.h"

PKH::Mesh::Mesh(GameObject* owner)
	:IComponent(owner)
	,isClone(false)
{
	device = RenderManager::GetDevice();
	type = MeshType::NONE;
}

PKH::Mesh::Mesh(const Mesh& rhs)
	:IComponent(rhs)
	,isClone(true)
	,type(rhs.type)
{
	device = RenderManager::GetDevice();
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
