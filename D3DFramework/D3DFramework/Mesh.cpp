#include "stdafx.h"
#include "Mesh.h"

using namespace PKH;

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
}

void PKH::Mesh::Render()
{
	if (gameObject == nullptr)return;

	Transform* transform = (Transform*)gameObject->GetComponent(L"Transform");

	LPDIRECT3DDEVICE9 device = D2DRenderManager::GetDevice();
	if (device)
	{
		device->SetStreamSource(0, vb, 0, sizeof(Vertex));
		device->SetIndices(triangles);
		device->SetFVF(Vertex::FVF);

		Matrix world, trans, rotX, rotY, rotZ, scale;
		D3DXMatrixScaling(&scale, transform->scale.x, transform->scale.y, transform->scale.z);
		D3DXMatrixRotationX(&rotX, transform->rotation.x);
		D3DXMatrixRotationY(&rotY, transform->rotation.y);
		D3DXMatrixRotationZ(&rotZ, transform->rotation.z);
		D3DXMatrixTranslation(&trans, transform->position.x, transform->position.y, transform->position.z);

		world = scale * rotX * rotY * rotZ * trans;

		device->SetTransform(D3DTS_WORLD, &world);


		D2DRenderManager::GetDevice()->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		D2DRenderManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
		//device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
		device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, triangleCount);
	}
}

PKH::IComponent * PKH::Mesh::Clone()
{
	return new Mesh(*this);
}
