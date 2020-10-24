#include "stdafx.h"
#include "Rectangle.h"
#include "Color.h"

PKH::Rectangle::Rectangle()
{
	this->vertexCount = 4;
	this->triangleCount = 2;

	D2DRenderManager::GetDevice()->CreateVertexBuffer(
		vertexCount * sizeof(VertexUV),
		D3DUSAGE_WRITEONLY,
		VertexUV::FVF,
		D3DPOOL_MANAGED,
		&vb,
		0);

	D2DRenderManager::GetDevice()->CreateIndexBuffer(
		triangleCount * 3 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&triangles,
		0);

	VertexUV* vertices;
	vb->Lock(0, 0, (void**)&vertices, 0);

	vertices[0] = VertexUV(-1.f, -1.f, 0.f,0,1);
	vertices[1] = VertexUV(-1.f, 1.f, 0.f,0,0);
	vertices[2] = VertexUV(1.f, 1.f, 0.f, 1,0);
	vertices[3] = VertexUV(1.f, -1.f, 0.f, 1,1);
	vb->Unlock();

	WORD* indices = nullptr;
	triangles->Lock(0, 0, (void**)&indices, 0);
	indices[0] = 0; indices[1] = 1; indices[2] = 3;
	indices[3] = 1; indices[4] = 2; indices[5] = 3;
	triangles->Unlock();


}

PKH::Rectangle::~Rectangle()
{
	
}

void PKH::Rectangle::Update()
{
}

void PKH::Rectangle::Render()
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

		device->SetStreamSource(0, vb, 0, sizeof(VertexUV));
		device->SetFVF(VertexUV::FVF);
		device->SetIndices(triangles);

		device->SetTransform(D3DTS_WORLD, &transform->world);

		D2DRenderManager::GetDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		D2DRenderManager::GetDevice()->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		D2DRenderManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);

		//device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, triangleCount);
		device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, triangleCount);
	}
}

IComponent* PKH::Rectangle::Clone()
{
	return new Rectangle(*this);
}
