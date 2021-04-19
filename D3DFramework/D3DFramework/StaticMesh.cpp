#include "stdafx.h"
#include "StaticMesh.h"
Engine::StaticMesh::StaticMesh(GameObject* owner)
	:Mesh(owner)
{
	type = MeshType::STATIC_MESH;
}

Engine::StaticMesh::StaticMesh(const StaticMesh& rhs)
	: Mesh(rhs)
	, pAdjacency(rhs.pAdjacency)
	, pSubset(rhs.pSubset)
	, pMesh(rhs.pMesh)
	, pOriginMesh(rhs.pOriginMesh)
	, pMaterial(rhs.pMaterial)
	, subsetCount(rhs.subsetCount)
	, vertexCount(rhs.vertexCount)
	, vertexSize(rhs.vertexSize)
	, triangleCount(rhs.triangleCount)
	, pVertices(rhs.pVertices)
	, pIndices(rhs.pIndices)
	, fvf(rhs.fvf)
{
	ppTextures = new LPDIRECT3DTEXTURE9[rhs.subsetCount];

	for (ULONG i = 0; i < rhs.subsetCount; ++i)
	{
		ppTextures[i] = rhs.ppTextures[i];
		Safe_AddRef(&ppTextures[i]);
	}

	Safe_AddRef(&pMesh);
	Safe_AddRef(&pOriginMesh);
	Safe_AddRef(&pAdjacency);
	Safe_AddRef(&pSubset);
}

Engine::StaticMesh::~StaticMesh()
{
	for (ULONG i = 0; i < subsetCount; ++i)
		Safe_Release(&ppTextures[i]);

	Safe_Delete_Array(&ppTextures);
	ppTextures = nullptr;

	if (isClone == false)
	{
		Safe_Delete_Array(&pVertices);
		Safe_Delete_Array(&pIndices);
	}
	
	Safe_Release(&pSubset);
	Safe_Release(&pAdjacency);
	Safe_Release(&pOriginMesh);
	Safe_Release(&pMesh);

	pOriginMesh = nullptr;
	pMesh = nullptr;
}

IComponent* Engine::StaticMesh::Clone()
{
	return new StaticMesh(*this);
}


int Engine::StaticMesh::GetSubsetCount()
{
	return static_cast<int>(subsetCount);
}

IDirect3DTexture9* Engine::StaticMesh::GetSubsetTexture(int index)
{
	return ppTextures[index];
}

void Engine::StaticMesh::SetSubsetTexture(int index, const wstring& textureKey)
{
	if (index < 0) return;
	if (index >= subsetCount) return;

	Texture* texture = RenderManager::GetTexture(textureKey);
	if (texture == nullptr)
	{
		MessageBox(NULL, L"로드되지 않은 텍스쳐", L"Error", MB_OK);
		return;
	}
	ppTextures[index] = texture->pTexture;
}

HRESULT Engine::StaticMesh::LoadMesh(const WCHAR* pFilePath, const WCHAR* pFileName)
{
	WCHAR		szFullPath[MAX_PATH] = L"";

	lstrcpy(szFullPath, pFilePath);
	lstrcat(szFullPath, pFileName);

	wstring ext;
	wstring fileName = pFileName;
	int len = fileName.length();
	int dotPos = fileName.find_last_of('.') + 1;
	ext = fileName.substr(dotPos);
	
	if (ext== L"x" || ext == L"X")
	{
		return LoadMeshX(pFilePath, pFileName);
	}
	else if (ext == L"obj" || ext == L"OBJ")
	{
		return LoadMeshOBJ(pFilePath, pFileName);
	}

	return E_FAIL;
}

HRESULT Engine::StaticMesh::LoadMeshX(const WCHAR* pFilePath, const WCHAR* pFileName)
{
	WCHAR		szFullPath[MAX_PATH] = L"";

	lstrcpy(szFullPath, pFilePath);
	lstrcat(szFullPath, pFileName);

	auto device = RenderManager::GetDevice();

	//==============================
	// X파일 메쉬 로드
	//==============================
	if (FAILED(D3DXLoadMeshFromXW(szFullPath, D3DXMESH_MANAGED, device,
		&pAdjacency, &pSubset, NULL, &subsetCount, &pOriginMesh)))
	{
		return E_FAIL;
	}

	//==============================
	// FVF & 노말 세팅
	//==============================
	fvf = pOriginMesh->GetFVF();	// 메쉬가 지닌 정점 FVF정보를 얻어오는 함수

	if (!(fvf & D3DFVF_NORMAL))
	{
		// 노말 값이 없는 경우
		pOriginMesh->CloneMeshFVF(pOriginMesh->GetOptions(), fvf |= D3DFVF_NORMAL, device, &pMesh);
		// 노말계산
		D3DXComputeNormals(pMesh, (ULONG*)pAdjacency->GetBufferPointer());
	}
	else
	{
		pOriginMesh->CloneMeshFVF(pOriginMesh->GetOptions(), fvf, device, &pMesh);
	}


	//==============================
	// 버텍스들의 포지션 정보 저장
	//==============================
	void* pVertex = nullptr;

	vertexCount = pMesh->GetNumVertices();	// 메쉬가 지닌 정점의 개수를 반환
	pVertices = new Vector3[vertexCount];

	pMesh->LockVertexBuffer(0, &pVertex);

	// 정점 정보 중 position의 위치 찾기
	D3DVERTEXELEMENT9			Decl[MAX_FVF_DECL_SIZE];
	ZeroMemory(Decl, sizeof(D3DVERTEXELEMENT9) * MAX_FVF_DECL_SIZE);

	pMesh->GetDeclaration(Decl);

	UCHAR byOffset = 0;

	for (ULONG i = 0; i < MAX_FVF_DECL_SIZE; ++i)
	{
		if (Decl[i].Usage == D3DDECLUSAGE_POSITION)
		{
			byOffset = (UCHAR)Decl[i].Offset;
			break;
		}
	}
	// FVF 정보를 토대로 정점의 크기를 반환하는 함수
	vertexSize = D3DXGetFVFVertexSize(fvf);
	// 버텍스의 포지션정보만 저장
	for (ULONG i = 0; i < vertexCount; ++i)
	{
		pVertices[i] = *((Vector3*)(((UCHAR*)pVertex) + (i * vertexSize + byOffset)));
	}

	pMesh->UnlockVertexBuffer();

	//==============================
	// 인덱스 정보 저장
	//==============================

	this->triangleCount = pMesh->GetNumFaces();
	int indexCount = triangleCount * 3;
	pIndices = new DWORD[indexCount];

	// 인덱스 버퍼 세팅
	LPDIRECT3DINDEXBUFFER9 pIB;
	pMesh->GetIndexBuffer(&pIB);

	D3DINDEXBUFFER_DESC desc;
	pIB->GetDesc(&desc);
	D3DFORMAT format = desc.Format;
	UINT indexSize = 2; // INDEX16
	if (format == D3DFORMAT::D3DFMT_INDEX16)
	{
		WORD* dummyIndices = nullptr;
		pMesh->LockIndexBuffer(0, (void**)&dummyIndices);
		for (int i = 0; i < indexCount; i++)
		{
			WORD idx = dummyIndices[i];
			pIndices[i] = idx;
		}
		pMesh->UnlockIndexBuffer();
	}
	else
	{
		DWORD* dummyIndices = nullptr;
		pMesh->LockIndexBuffer(0, (void**)&dummyIndices);
		for (int i = 0; i < indexCount; i++)
		{
			DWORD idx = dummyIndices[i];
			pIndices[i] = idx;
		}
		pMesh->UnlockIndexBuffer();
	}



	//==============================
	// 머티리얼 & 텍스처 정보 저장
	//==============================
	// 메쉬가 지닌 재질 정보 중 첫 번째 주소를 반환하여 저장
	pMaterial = (D3DXMATERIAL*)pSubset->GetBufferPointer();

	ppTextures = new LPDIRECT3DTEXTURE9[subsetCount];

	for (ULONG i = 0; i < subsetCount; ++i)
	{
		WCHAR	szFileName[256] = L"";

		lstrcpy(szFullPath, pFilePath);

		MultiByteToWideChar(CP_ACP,
			0,
			pMaterial[i].pTextureFilename,
			strlen(pMaterial[i].pTextureFilename),
			szFileName,
			256);

		lstrcat(szFullPath, szFileName);

		HRESULT res = E_FAIL;
		res = D3DXCreateTextureFromFile(device, szFullPath, &ppTextures[i]);
		if (res != S_OK)
		{
			return E_FAIL;
		}

	}

	return S_OK;
}

HRESULT Engine::StaticMesh::LoadMeshOBJ(const WCHAR* pFilePath, const WCHAR* pFileName)
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

	char* buffer = new char[fileLen+1];
	memset(buffer, 0, fileLen+1);
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
				vtxs.push_back(Vertex(pos[vIndex-1], D3DCOLOR_ARGB(255, 255, 255, 255), texCoords[vtIndex-1].x, texCoords[vtIndex-1].y));
				indices.push_back(vtxIndex);
				vtxIndex++;
				numVertices++;
			}

			faceIndex++;
			numFaces++;
		}

	}

	delete[] buffer;

	fvf = Vertex::FVF;
	
	HRESULT res = D3DXCreateMeshFVF(numFaces, numVertices, D3DXMESH_MANAGED, fvf, device, &pOriginMesh);

	if (res != S_OK)
	{
		int a = 0;
	}

	Vertex* pV = nullptr;
	int vtxCount = vtxs.size();
	pOriginMesh->LockVertexBuffer(0, (void**)&pV);

	for (int i = 0; i < vtxCount; i++)
	{
		pV[i] = vtxs[i];
	}

	pOriginMesh->UnlockVertexBuffer();

	WORD* pI = nullptr;
	int idxCount = numFaces * 3;
	pOriginMesh->LockIndexBuffer(0, (void**)&pI);

	for (int i = 0; i < idxCount; i++)
	{
		pI[i] = indices[i];
	}

	pOriginMesh->UnlockIndexBuffer();

	// adj 추가
	DWORD* adj = new DWORD[numFaces * 3];
	pOriginMesh->GenerateAdjacency(FLT_EPSILON, adj);

	// Attribute
	D3DXATTRIBUTERANGE* pAttributeTable = new D3DXATTRIBUTERANGE;
	memset(pAttributeTable, 0, sizeof(D3DXATTRIBUTERANGE));

	pAttributeTable[0].AttribId = 0;
	pAttributeTable[0].FaceCount = numFaces;
	pAttributeTable[0].FaceStart = 0;
	pAttributeTable[0].VertexCount = numVertices;
	pAttributeTable[0].VertexStart = 0;

	pOriginMesh->SetAttributeTable(pAttributeTable, 1);

	delete pAttributeTable;

	DWORD c;
	pOriginMesh->GetAttributeTable(0, &c);

	pOriginMesh->CloneMeshFVF(pOriginMesh->GetOptions(), fvf, device, &pMesh);
	D3DXComputeNormals(pMesh, adj);

	DWORD d;
	pMesh->GetAttributeTable(0, &d);

	delete[] adj;

	//==============================
	// 버텍스들의 포지션 정보 저장
	//==============================
	void* pVertex = nullptr;

	vertexCount = pMesh->GetNumVertices();	// 메쉬가 지닌 정점의 개수를 반환
	pVertices = new Vector3[vertexCount];

	pMesh->LockVertexBuffer(0, &pVertex);

	// 정점 정보 중 position의 위치 찾기
	D3DVERTEXELEMENT9			Decl[MAX_FVF_DECL_SIZE];
	ZeroMemory(Decl, sizeof(D3DVERTEXELEMENT9)* MAX_FVF_DECL_SIZE);

	pMesh->GetDeclaration(Decl);

	UCHAR byOffset = 0;

	for (ULONG i = 0; i < MAX_FVF_DECL_SIZE; ++i)
	{
		if (Decl[i].Usage == D3DDECLUSAGE_POSITION)
		{
			byOffset = (UCHAR)Decl[i].Offset;
			break;
		}
	}
	// FVF 정보를 토대로 정점의 크기를 반환하는 함수
	vertexSize = D3DXGetFVFVertexSize(fvf);
	// 버텍스의 포지션정보만 저장
	for (ULONG i = 0; i < vertexCount; ++i)
	{
		pVertices[i] = *((Vector3*)(((UCHAR*)pVertex) + (i * vertexSize + byOffset)));
	}

	pMesh->UnlockVertexBuffer();

	//==============================
	// 인덱스 정보 저장
	//==============================

	this->triangleCount = pMesh->GetNumFaces();
	int indexCount = triangleCount * 3;
	pIndices = new DWORD[indexCount];

	// 인덱스 버퍼 세팅
	LPDIRECT3DINDEXBUFFER9 pIB;
	pMesh->GetIndexBuffer(&pIB);

	D3DINDEXBUFFER_DESC desc;
	pIB->GetDesc(&desc);
	D3DFORMAT format = desc.Format;
	UINT indexSize = 2; // INDEX16
	if (format == D3DFORMAT::D3DFMT_INDEX16)
	{
		WORD* dummyIndices = nullptr;
		pMesh->LockIndexBuffer(0, (void**)&dummyIndices);
		for (int i = 0; i < indexCount; i++)
		{
			WORD idx = dummyIndices[i];
			pIndices[i] = idx;
		}
		pMesh->UnlockIndexBuffer();
	}
	else
	{
		DWORD* dummyIndices = nullptr;
		pMesh->LockIndexBuffer(0, (void**)&dummyIndices);
		for (int i = 0; i < indexCount; i++)
		{
			DWORD idx = dummyIndices[i];
			pIndices[i] = idx;
		}
		pMesh->UnlockIndexBuffer();
	}

	subsetCount = 1;
	ppTextures = new LPDIRECT3DTEXTURE9[subsetCount];
	ppTextures[0] = nullptr;

	

	return S_OK;
}


void Engine::StaticMesh::RenderSubset(int index)
{
	auto device = RenderManager::GetDevice();
	Vector3 worldPos = *((Vector3*)&transform->worldMatrix._41);

	// TODO : Render 반경 계산 해야할듯?
	//if (Frustum::Intersect(&worldPos, 1.f) == false) return;
	device->SetFVF(fvf);
	pMesh->DrawSubset(index);
}
