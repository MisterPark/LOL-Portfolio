#include "stdafx.h"
#include "Mesh.h"

using namespace PKH;

Mesh::Mesh()
{

}

Mesh::~Mesh()
{
	vb->Release();
	triangles->Release();
}

void PKH::Mesh::Render()
{
	if (gameObject == nullptr)return;

	Transform* transform = (Transform*)gameObject->GetComponent(L"Transform");

	LPDIRECT3DDEVICE9 device = D2DRenderManager::GetDevice();
	if (device)
	{
		Texture* texture = D2DRenderManager::GetTexture(textureKey);
		if (texture != nullptr)
		{
			device->SetTexture(0, texture->pTexture);
		}

		device->SetStreamSource(0, vb, 0, sizeof(VertexColor));
		device->SetFVF(VertexColor::FVF);
		device->SetIndices(triangles);

		Matrix world, matTrans, matScale, matRot;//, rotX, rotY, rotZ
		D3DXMatrixScaling(&matScale, transform->scale.x, transform->scale.y, transform->scale.z);
		//D3DXMatrixRotationX(&rotX, transform->eulerAngles.x);
		//D3DXMatrixRotationY(&rotY, transform->eulerAngles.y);
		//D3DXMatrixRotationZ(&rotZ, transform->eulerAngles.z);
		D3DXMatrixRotationQuaternion(&matRot, &transform->rotation);
		D3DXMatrixTranslation(&matTrans, transform->position.x, transform->position.y, transform->position.z);
		
		//world = matScale * rotX * rotY * rotZ * matTrans;
		world = matScale * matRot * matTrans;

		device->SetTransform(D3DTS_WORLD, &world);

		D2DRenderManager::GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		D2DRenderManager::GetDevice()->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		D2DRenderManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);

		//device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, triangleCount);
		device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, triangleCount);
	}
}

PKH::IComponent * PKH::Mesh::Clone()
{
	return new Mesh(*this);
}

UINT PKH::Mesh::GetVertexCount()
{
	return this->vertexCount;
}

void PKH::Mesh::SetColor(D3DCOLOR color)
{
	VertexColor* vertices;
	vb->Lock(0, 0, (void**)&vertices, 0);
	for (int i = 0; i < vertexCount; i++)
	{
		vertices[i].color = color;
	}
	
	vb->Unlock();
}

void PKH::Mesh::SetTexture(PKH::TextureKey key)
{
	Texture* tx = D2DRenderManager::GetTexture(key);
	if (tx == nullptr) return;

	textureKey = key;
}

void PKH::Mesh::SetVertexPos(UINT index, const Vector3& pos)
{
	VertexUV* vertices;
	vb->Lock(0, 0, (void**)&vertices, 0);
	vertices[index].x = pos.x;
	vertices[index].y = pos.y;
	vertices[index].z = pos.z;
	vb->Unlock();
}

void PKH::Mesh::SetUV(UINT index, float u, float v)
{
	VertexUV* vertices;
	vb->Lock(0, 0, (void**)&vertices, 0);
	vertices[index].u = u;
	vertices[index].v = v;
	vb->Unlock();
}
