#include "stdafx.h"
#include "Mesh.h"

Engine::Mesh::Mesh(GameObject* owner)
	:IComponent(owner)
	,isClone(false)
{
	device = RenderManager::GetDevice();
	type = MeshType::NONE;
}

Engine::Mesh::Mesh(const Mesh& rhs)
	:IComponent(rhs)
	,isClone(true)
	,type(rhs.type)
{
	device = RenderManager::GetDevice();
}

Engine::Mesh::~Mesh()
{
}

int Engine::Mesh::GetSubsetCount()
{
	return 1;
}

void Engine::Mesh::RenderSubset(int index)
{

}

IDirect3DTexture9* Engine::Mesh::GetSubsetTexture(int index)
{
	return nullptr;
}
