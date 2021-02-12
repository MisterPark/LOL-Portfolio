#include "stdafx.h"
#include "CustomMesh.h"

using namespace PKH;

PKH::CustomMesh::CustomMesh(GameObject* owner)
	:Mesh(owner)
{
	// 머테리얼
	ZeroMemory(&material, sizeof(D3DMATERIAL9));


	material.Diffuse = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	material.Specular = D3DXCOLOR(1.f, 1.f, 1.f, 1.f);
	material.Ambient = D3DXCOLOR(0.5f, 0.5f, 0.5f, 0.5f);
	material.Emissive = D3DXCOLOR(0.f, 0.f, 0.f, 1.f);
	material.Power = 0.f;

	type = MeshType::CUSTOM_MESH;
}

PKH::CustomMesh::CustomMesh(const CustomMesh& rhs)
	:Mesh(rhs)
{
	
}

CustomMesh::~CustomMesh()
{
	vertexBuffer->Release();
	triangles->Release();
	Safe_Delete_Array(&pVertices);
	Safe_Delete_Array(&pIndices);
}

void PKH::CustomMesh::Render()
{
	if (gameObject == nullptr)return;
	
	Transform* transform = (Transform*)gameObject->GetComponent(L"Transform");

	LPDIRECT3DDEVICE9 device = RenderManager::GetDevice();
	RenderManager::LockDevice();
	if (device)
	{
		Texture* texture = RenderManager::GetTexture(textureKey);
		if (texture != nullptr)
		{
			device->SetTexture(0, texture->pTexture);
		}
		else
		{
			device->SetTexture(0, 0);
		}

		device->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));
		device->SetFVF(Vertex::FVF);
		device->SetIndices(triangles);


		device->SetTransform(D3DTS_WORLD, &transform->world);

		// Z Read 모드
		switch (zReadMode)
		{
		case PKH::ZReadMode::ON:
			device->SetRenderState(D3DRS_ZENABLE, TRUE);
			break;
		case PKH::ZReadMode::OFF:
			device->SetRenderState(D3DRS_ZENABLE, FALSE);
			break;
		default:
			break;
		}

		// Z Write 모드
		switch (zWriteMode)
		{
		case PKH::ZWriteMode::ON:
			device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
			break;
		case PKH::ZWriteMode::OFF:
			device->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);
			break;
		default:
			break;
		}

		// 블렌드 모드
		switch (blendMode)
		{
		case PKH::BlendMode::NONE:
			break;
		case PKH::BlendMode::ALPHA_BLEND:
			device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

			device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
			device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
			break;
		case PKH::BlendMode::ALPHA_TEST:
			device->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);

			device->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
			device->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
			device->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
			break;
		default:
			break;
		}
		
		switch (cullMode)
		{
		case PKH::CullMode::NONE:
			device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
			break;
		case PKH::CullMode::CW:
			device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
			break;
		case PKH::CullMode::CCW:
			device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
			break;
		default:
			break;
		}
		

		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		//device->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

		switch (lightMode)
		{
		case LightMode::ON:
			device->SetRenderState(D3DRS_LIGHTING, true);
			device->SetRenderState(D3DRS_NORMALIZENORMALS, TRUE);
			device->SetMaterial(&material);
			break;
		case LightMode::OFF:
			device->SetRenderState(D3DRS_LIGHTING, false);
			break;
		default:
			break;
		}
		
		// 렌더
		device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, triangleCount);

		device->SetRenderState(D3DRS_LIGHTING, false);
	
		device->SetTexture(0, NULL);

		switch (blendMode)
		{
		case PKH::BlendMode::NONE:
			break;
		case PKH::BlendMode::ALPHA_BLEND:
			device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			break;
		case PKH::BlendMode::ALPHA_TEST:
			device->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
			device->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
			break;
		default:
			break;
		}
		device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
		device->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		device->SetRenderState(D3DRS_ZENABLE, TRUE);
		device->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
		
	
	}
	RenderManager::UnlockDevice();
}


IDirect3DVertexBuffer9 * PKH::CustomMesh::GetVertexBuffer()
{
	return vertexBuffer;
}

Vector3* PKH::CustomMesh::GetVertices()
{
	return pVertices;
}

DWORD* PKH::CustomMesh::GetIndices()
{
	return pIndices;
}

ULONG PKH::CustomMesh::GetVertexCount()
{
	return this->vertexCount;
}

ULONG PKH::CustomMesh::GetVertexSize()
{
	return this->vertexSize;
}

ULONG PKH::CustomMesh::GetFaceCount()
{
	return this->triangleCount;
}

void PKH::CustomMesh::SetColor(D3DCOLOR color)
{
	Vertex* vertices;
	vertexBuffer->Lock(0, 0, (void**)&vertices, 0);
	for (UINT i = 0; i < vertexCount; i++)
	{
		vertices[i].color = color;
	}
	
	vertexBuffer->Unlock();
}

void PKH::CustomMesh::SetTexture(const wstring& id)
{
	textureKey = id;
}

void PKH::CustomMesh::SetVertexPos(UINT index, const Vector3& pos)
{
	Vertex* vertices;
	vertexBuffer->Lock(0, 0, (void**)&vertices, 0);
	vertices[index].pos.x = pos.x;
	vertices[index].pos.y = pos.y;
	vertices[index].pos.z = pos.z;
	vertexBuffer->Unlock();
}

void PKH::CustomMesh::SetUV(UINT index, float u, float v)
{
	Vertex* vertices;
	vertexBuffer->Lock(0, 0, (void**)&vertices, 0);
	vertices[index].u = u;
	vertices[index].v = v;
	vertexBuffer->Unlock();
}

void PKH::CustomMesh::SetBlendMode(BlendMode _mode)
{
	this->blendMode = _mode;
}

void PKH::CustomMesh::SetCullMode(CullMode _mode)
{
	cullMode = _mode;
}

void PKH::CustomMesh::SetZReadMode(ZReadMode _mode)
{
	zReadMode = _mode;
}

void PKH::CustomMesh::SetZWriteMode(ZWriteMode _mode)
{
	zWriteMode = _mode;
}

void PKH::CustomMesh::SetLightMode(LightMode _mode)
{
	lightMode = _mode;
}


