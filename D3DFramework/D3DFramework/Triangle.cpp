#include "stdafx.h"
#include "Triangle.h"

Triangle::Triangle()
{
	D2DRenderManager::GetDevice()->CreateVertexBuffer(
		4 * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&vb,
		0);

	D2DRenderManager::GetDevice()->CreateIndexBuffer(
		6 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&triangles,
		0);

	Vertex* vertices;
	vb->Lock(0, 0, (void**)&vertices, 0);

	vertices[0] = Vertex(-0.1f, -0.1f, 1.0f, D3DCOLOR_XRGB(255, 0, 0));
	vertices[1] = Vertex(-0.1f, 0.1f, 1.0f, D3DCOLOR_XRGB(0, 255, 0));
	vertices[2] = Vertex(0.1f, 0.1f, 1.0f, D3DCOLOR_XRGB(0, 0, 255));
	vertices[3] = Vertex(0.1f, -0.1f, 1.0f, D3DCOLOR_XRGB(255, 0, 255));
	vb->Unlock();

	WORD* indices = nullptr;
	triangles->Lock(0, 0, (void**)&indices, 0);
	indices[0] = 0; indices[1] = 1; indices[2] = 3;
	indices[3] = 1; indices[4] = 2; indices[5] = 3;
	triangles->Unlock();

	// Åõ¿µ
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f,
		(float)dfCLIENT_WIDTH / dfCLIENT_HEIGHT,
		1.0f,
		1000.f);

	D2DRenderManager::GetDevice()->SetTransform(D3DTS_PROJECTION, &proj);
	

}

Triangle::~Triangle()
{
}

void Triangle::Update()
{
	if (InputManager::GetKey(VK_UP))
	{
		this->transform.position.y += 1.f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey(VK_DOWN))
	{
		this->transform.position.y -= 1.f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey(VK_LEFT))
	{
		this->transform.position.x -= 1.f * TimeManager::DeltaTime();
	}
	if (InputManager::GetKey(VK_RIGHT))
	{
		this->transform.position.x += 1.f * TimeManager::DeltaTime();
	}
}

void Triangle::Render()
{

	LPDIRECT3DDEVICE9 device = D2DRenderManager::GetDevice();
	if (device)
	{
		device->SetStreamSource(0, vb, 0, sizeof(Vertex));
		device->SetIndices(triangles);
		device->SetFVF(Vertex::FVF);

		Matrix world, trans, rot, scale;
		D3DXMatrixScaling(&scale, transform.scale.x, transform.scale.y, transform.scale.z);
		D3DXMatrixRotationX(&rot, transform.rotation.x);
		D3DXMatrixRotationY(&rot, transform.rotation.y);
		D3DXMatrixRotationZ(&rot, transform.rotation.z);
		D3DXMatrixTranslation(&trans, transform.position.x, transform.position.y, transform.position.z);

		world = scale * rot * trans;

		device->SetTransform(D3DTS_WORLD, &world);


		D2DRenderManager::GetDevice()->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);
		D2DRenderManager::GetDevice()->SetRenderState(D3DRS_LIGHTING, false);
		//device->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
		device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	}
}
