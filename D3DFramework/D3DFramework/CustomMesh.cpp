#include "stdafx.h"
#include "CustomMesh.h"

using namespace Engine;

Engine::CustomMesh::CustomMesh(GameObject* owner)
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

Engine::CustomMesh::CustomMesh(const CustomMesh& rhs)
	:Mesh(rhs)
{
	vertexBuffer = rhs.vertexBuffer;
	triangles = rhs.triangles;
	vertexCount = rhs.vertexCount;
	vertexSize = rhs.vertexSize;
	triangleCount = rhs.triangleCount;

	pVertices = new Vector3[vertexCount];
	memcpy(pVertices, rhs.pVertices, sizeof(Vector3) * vertexCount);
	pIndices = new DWORD[triangleCount * 3];
	memcpy(pIndices, rhs.pIndices, sizeof(DWORD) * triangleCount * 3);

	textureKey = rhs.textureKey;

	vertexBuffer->AddRef();
	triangles->AddRef();
}

CustomMesh::~CustomMesh()
{
	Safe_Release(&vertexBuffer);
	Safe_Release(&triangles);
	Safe_Delete_Array(&pVertices);
	Safe_Delete_Array(&pIndices);
}

void Engine::CustomMesh::RenderSubset(int index)
{
	device->SetStreamSource(0, vertexBuffer, 0, sizeof(Vertex));
	device->SetFVF(Vertex::FVF);
	device->SetIndices(triangles);
	device->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, vertexCount, 0, triangleCount);
}

IDirect3DTexture9* Engine::CustomMesh::GetSubsetTexture(int index)
{
	Texture* texture = RenderManager::GetTexture(textureKey);
	if (texture == nullptr) return nullptr;

	return texture->pTexture;
}

void Engine::CustomMesh::SetSubsetTexture(const wstring& _textureKey)
{
	this->textureKey = _textureKey;
}

Engine::IComponent* Engine::CustomMesh::Clone()
{
	return new CustomMesh(*this);
}

HRESULT Engine::CustomMesh::LoadMesh(const WCHAR* pFilePath, const WCHAR* pFileName)
{
	WCHAR		szFullPath[MAX_PATH] = L"";

	lstrcpy(szFullPath, pFilePath);
	lstrcat(szFullPath, pFileName);

	wstring ext;
	wstring fileName = pFileName;
	int len = fileName.length();
	int dotPos = fileName.find_last_of('.') + 1;
	ext = fileName.substr(dotPos);

	if (ext == L"x" || ext == L"X")
	{
		return LoadMeshX(pFilePath, pFileName);
	}
	else if (ext == L"obj" || ext == L"OBJ")
	{
		return LoadMeshOBJ(pFilePath, pFileName);
	}

	return E_FAIL;
}

HRESULT Engine::CustomMesh::LoadMeshX(const WCHAR* pFilePath, const WCHAR* pFileName)
{
	return E_NOTIMPL;
}

HRESULT Engine::CustomMesh::LoadMeshOBJ(const WCHAR* pFilePath, const WCHAR* pFileName)
{
	WCHAR		szFullPath[MAX_PATH] = L"";

	lstrcpy(szFullPath, pFilePath);
	lstrcat(szFullPath, pFileName);

	auto device = RenderManager::GetDevice();

	DWORD numFaces = 0;
	DWORD numVertices = 0;
	FILE* pFile = nullptr;
	if (_wfopen_s(&pFile, szFullPath, L"rt") != 0)
	{
		MessageBox(NULL, L"OBJ파일 열기 실패", L"Error", MB_OK);
		return E_FAIL;
	}

	fseek(pFile, 0, SEEK_END);
	int fileLen = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	char* buffer = new char[fileLen + 1];
	memset(buffer, 0, fileLen + 1);
	fread_s(buffer, fileLen, fileLen, 1, pFile);
	fclose(pFile);

	int index = 0;
	string token;

	vector<Vector3> pos;
	vector<Vector2> texCoords;
	vector<Vertex> vtxs;
	vector<DWORD> indices;

	string line;
	string oldLine;
	int lineCount = 0;
	int lineLen = 0;
	int lineIndex = 0;
	int vertexIndex = 0;
	int texIndex = 0;
	int faceIndex = 0;
	int vtxIndex = 0;
	while (true)
	{
		if (index >= fileLen) break;
		if (buffer[index] == '\0') break;

		// 라인 읽기
		oldLine = line;
		line.clear();
		while (true)
		{
			if (index >= fileLen) break;
			if (buffer[index] == '\n') break;
			if (buffer[index] == '\0') break;
			if (buffer[index] == '\r') break;

			line += buffer[index];
			index++;
		}
		index++;

		if (line.size() == 0) break;

		lineIndex = 0;
		lineLen = line.length();
		// 토큰 읽기
		token.clear();
		for (; lineIndex < lineLen; lineIndex++)
		{
			if (line[lineIndex] == ' ') break;
			token += line[lineIndex];
		}
		lineIndex++;
		lineCount++;

		if (token == "v")
		{
			pos.push_back(Vector3());
			string v;
			int elemCount = 0;
			for (; elemCount < 3; elemCount++)
			{
				v.clear();
				for (; lineIndex < lineLen; lineIndex++)
				{
					if (line[lineIndex] == ' ') break;
					v += line[lineIndex];
				}
				lineIndex++;

				if (elemCount == 0)
				{
					pos[vertexIndex].x = atof(v.c_str());
				}
				else if (elemCount == 1)
				{
					pos[vertexIndex].y = atof(v.c_str());
				}
				else if (elemCount == 2)
				{
					pos[vertexIndex].z = atof(v.c_str());
				}
			}

			vertexIndex++;
		}
		else if (token == "vt")
		{
			texCoords.push_back(Vector2());
			string vt;
			int elemCount = 0;
			for (; elemCount < 2; elemCount++)
			{
				vt.clear();
				for (; lineIndex < lineLen; lineIndex++)
				{
					if (line[lineIndex] == ' ') break;
					vt += line[lineIndex];
				}
				lineIndex++;

				if (elemCount == 0)
				{
					texCoords[texIndex].x = atof(vt.c_str());
				}
				else if (elemCount == 1)
				{
					texCoords[texIndex].y = atof(vt.c_str());
				}
			}

			texIndex++;

		}
		else if (token == "f")
		{
			string f, v, vt, vn;
			int elemCount = 0;
			for (; elemCount < 3; elemCount++)
			{
				f.clear();
				v.clear();
				vt.clear();
				vn.clear();

				for (; lineIndex < lineLen; lineIndex++)
				{
					if (line[lineIndex] == ' ') break;
					f += line[lineIndex];
				}
				lineIndex++;

				int fIndex = 0;
				int fLen = f.length();
				int fElemCount = 0;
				for (; fElemCount < 3; fElemCount++)
				{
					for (; fIndex < fLen; fIndex++)
					{
						if (f[fIndex] == '/') break;

						if (fElemCount == 0)
						{
							v += f[fIndex];
						}
						else if (fElemCount == 1)
						{
							vt += f[fIndex];
						}
						else if (fElemCount == 2)
						{
							vn += f[fIndex];
						}
					}
					fIndex++;



				}

				int vIndex = atoi(v.c_str());
				int vtIndex = atoi(vt.c_str());
				vtxs.push_back(Vertex(pos[vIndex - 1], D3DCOLOR_ARGB(255, 255, 255, 255), texCoords[vtIndex - 1].x, texCoords[vtIndex - 1].y));
				indices.push_back(vtxIndex);
				vtxIndex++;
				numVertices++;
			}

			faceIndex++;
			numFaces++;
		}

	}

	delete[] buffer;


	int vtxCount = vtxs.size();
	vertexCount = vtxCount;
	vertexSize = sizeof(Vertex);
	triangleCount = numFaces;
	pVertices = new Vector3[vertexCount];
	pIndices = new DWORD[triangleCount * 3];
	for (int i = 0; i < vtxCount; i++)
	{
		pVertices[i] = vtxs[i].pos;
	}

	int idxCount = numFaces * 3;
	for (int i = 0; i < idxCount; i++)
	{
		pIndices[i] = indices[i];
	}

	RenderManager::GetDevice()->CreateVertexBuffer(
		vertexCount* vertexSize,
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&vertexBuffer,
		0);

	RenderManager::GetDevice()->CreateIndexBuffer(
		triangleCount * 3 * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&triangles,
		0);

	Vertex* vertices;
	vertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	for (int i = 0; i < vtxCount; i++)
	{
		vertices[i] = vtxs[i];
	}

	vertexBuffer->Unlock();

	WORD* indices2 = nullptr;
	triangles->Lock(0, 0, (void**)&indices2, 0);

	for (int i = 0; i < idxCount; i++)
	{
		indices2[i] = (WORD)indices[i];
	}

	triangles->Unlock();

	return S_OK;
}


IDirect3DVertexBuffer9 * Engine::CustomMesh::GetVertexBuffer()
{
	return vertexBuffer;
}

Vector3* Engine::CustomMesh::GetVertices()
{
	return pVertices;
}

DWORD* Engine::CustomMesh::GetIndices()
{
	return pIndices;
}

ULONG Engine::CustomMesh::GetVertexCount()
{
	return this->vertexCount;
}

ULONG Engine::CustomMesh::GetVertexSize()
{
	return this->vertexSize;
}

ULONG Engine::CustomMesh::GetFaceCount()
{
	return this->triangleCount;
}

void Engine::CustomMesh::SetColor(D3DCOLOR color)
{
	Vertex* vertices;
	vertexBuffer->Lock(0, 0, (void**)&vertices, 0);
	for (UINT i = 0; i < vertexCount; i++)
	{
		vertices[i].color = color;
	}
	
	vertexBuffer->Unlock();
}

void Engine::CustomMesh::SetTexture(const wstring& id)
{
	textureKey = id;
}

void Engine::CustomMesh::SetVertexPos(UINT index, const Vector3& pos)
{
	Vertex* vertices;
	vertexBuffer->Lock(0, 0, (void**)&vertices, 0);
	vertices[index].pos.x = pos.x;
	vertices[index].pos.y = pos.y;
	vertices[index].pos.z = pos.z;
	vertexBuffer->Unlock();
}

void Engine::CustomMesh::SetUV(UINT index, float u, float v)
{
	Vertex* vertices;
	vertexBuffer->Lock(0, 0, (void**)&vertices, 0);
	vertices[index].u = u;
	vertices[index].v = v;
	vertexBuffer->Unlock();
}

void Engine::CustomMesh::SetBlendMode(BlendMode _mode)
{
	this->blendMode = _mode;
}

void Engine::CustomMesh::SetCullMode(CullMode _mode)
{
	cullMode = _mode;
}

void Engine::CustomMesh::SetZReadMode(ZReadMode _mode)
{
	zReadMode = _mode;
}

void Engine::CustomMesh::SetZWriteMode(ZWriteMode _mode)
{
	zWriteMode = _mode;
}

void Engine::CustomMesh::SetLightMode(LightMode _mode)
{
	lightMode = _mode;
}


