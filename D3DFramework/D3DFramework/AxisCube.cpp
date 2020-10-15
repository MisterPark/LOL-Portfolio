#include "stdafx.h"
#include "AxisCube.h"

PKH::AxisCube::AxisCube()
{
	this->vertexCount = 8;
	this->triangleCount = 12;


	D2DRenderManager::GetDevice()->CreateVertexBuffer(
		vertexCount * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
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

	Vertex* vertices;
	vb->Lock(0, 0, (void**)&vertices, 0);
	
	vertices[0] = Vertex(-0.1f, -0.1f, -0.1f, D3DCOLOR_XRGB(255, 0, 0));
	vertices[1] = Vertex(-0.1f, 0.3f, -0.1f, D3DCOLOR_XRGB(0, 255, 0));
	vertices[2] = Vertex(0.1f, 0.3f, -0.1f, D3DCOLOR_XRGB(0, 0, 255));
	vertices[3] = Vertex(0.1f, -0.1f, -0.1f, D3DCOLOR_XRGB(255, 0, 255));

	vertices[4] = Vertex(-0.1f, -0.1f, 0.1f, D3DCOLOR_XRGB(255, 0, 0));
	vertices[5] = Vertex(-0.1f, 0.3f, 0.1f, D3DCOLOR_XRGB(0, 255, 0));
	vertices[6] = Vertex(0.1f, 0.3f, 0.1f, D3DCOLOR_XRGB(0, 0, 255));
	vertices[7] = Vertex(0.1f, -0.1f, 0.1f, D3DCOLOR_XRGB(255, 0, 255));
	vb->Unlock();

	WORD* indices = nullptr;
	triangles->Lock(0, 0, (void**)&indices, 0);
	// 전
	indices[0] = 0; indices[1] = 1; indices[2] = 3;
	indices[3] = 1; indices[4] = 2; indices[5] = 3;
	// 후
	indices[6] = 7; indices[7] = 6; indices[8] = 4;
	indices[9] = 6; indices[10] = 5; indices[11] = 4;
	// 좌
	indices[12] = 4; indices[13] = 5; indices[14] = 0;
	indices[15] = 5; indices[16] = 1; indices[17] = 0;
	// 우
	indices[18] = 3; indices[19] = 2; indices[20] = 7;
	indices[21] = 2; indices[22] = 6; indices[23] = 7;
	// 상
	indices[24] = 1; indices[25] = 5; indices[26] = 2;
	indices[27] = 5; indices[28] = 6; indices[29] = 2;
	// 하
	indices[30] = 4; indices[31] = 0; indices[32] = 7;
	indices[33] = 0; indices[34] = 3; indices[35] = 7;
	triangles->Unlock();
}

PKH::AxisCube::~AxisCube()
{
}

void PKH::AxisCube::Update()
{
}

void PKH::AxisCube::Render(Vector3 _pos, Vector3 _axis)
{
	LPDIRECT3DDEVICE9 device = D2DRenderManager::GetDevice();
	if (device)
	{
		device->SetStreamSource(0, vb, 0, sizeof(Vertex));
		device->SetFVF(Vertex::FVF);
		device->SetIndices(triangles);

		Matrix world, matTrans, rotX, rotY, rotZ;
		D3DXMatrixRotationX(&rotX, _axis.x);
		D3DXMatrixRotationY(&rotY, _axis.y);
		D3DXMatrixRotationZ(&rotZ, _axis.z);
		D3DXMatrixTranslation(&matTrans, _pos.x, _pos.y, _pos.z);

		world = rotX * rotY * rotZ * matTrans;

		device->SetTransform(D3DTS_WORLD, &world);

		D2DRenderManager::GetDevice()->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		D2DRenderManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);

		//device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, triangleCount);
		device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, triangleCount);
	}
}

IComponent* PKH::AxisCube::Clone()
{
	return new AxisCube(*this);
}
