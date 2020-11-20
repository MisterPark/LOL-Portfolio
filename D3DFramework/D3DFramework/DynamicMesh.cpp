#include "stdafx.h"
#include "DynamicMesh.h"

IComponent * PKH::DynamicMesh::Clone()
{
	return new DynamicMesh(*this);
}
