#include "stdafx.h"
#include "DynamicMesh.h"

PKH::DynamicMesh::DynamicMesh(GameObject* owner)
	:Mesh(owner)
{
}

PKH::DynamicMesh::DynamicMesh(const DynamicMesh& rhs)
	:Mesh(rhs)
{
}

PKH::DynamicMesh::~DynamicMesh()
{
}

IComponent * PKH::DynamicMesh::Clone()
{
	return new DynamicMesh(*this);
}
