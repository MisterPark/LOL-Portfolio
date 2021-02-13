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
