#include "stdafx.h"
#include "Triangle.h"

Triangle::Triangle()
{
	D2DRenderManager::GetDevice()->CreateVertexBuffer(
		3 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&vb,
		0);

	Vertex* vertices;
	vb->Lock(0, 0, (void**)&vertices, 0);

	vertices[0] = Vertex(-1.0f, -1.0f, 1.0f, D3DCOLOR_XRGB(255, 0, 0));
	vertices[1] = Vertex(0.0f, 1.0f, 1.0f, D3DCOLOR_XRGB(0, 255, 0));
	vertices[2] = Vertex(1.0f, -1.0f, 1.0f, D3DCOLOR_XRGB(0, 0, 255));

	vb->Unlock();



	// Åõ¿µ
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f,
		(float)dfCLIENT_WIDTH / dfCLIENT_HEIGHT * 0.75f,
		1.0f,
		1000.f);

	D2DRenderManager::GetDevice()->SetTransform(D3DTS_PROJECTION, &proj);
	D2DRenderManager::GetDevice()->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
	D2DRenderManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);

}

Triangle::~Triangle()
{
}

void Triangle::Render()
{

	LPDIRECT3DDEVICE9 device = D2DRenderManager::GetDevice();
	if (device)
	{
		device->SetStreamSource(0, vb, 0, sizeof(Vertex));
		device->SetFVF(Vertex::FVF);
		device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
	}
}
