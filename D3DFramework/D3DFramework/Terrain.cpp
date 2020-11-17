#include "stdafx.h"
#include "Terrain.h"

PKH::Terrain::Terrain()
	: width(dfTERRAIN_WIDTH), height(dfTERRAIN_WIDTH)
{
	this->vertexCount = width * height;
	this->triangleCount = (width-1) * (height-1) * 2;

	RenderManager::LockDevice();
	RenderManager::GetDevice()->CreateVertexBuffer(
		vertexCount * sizeof(Vertex),
		D3DUSAGE_WRITEONLY,
		Vertex::FVF,
		D3DPOOL_MANAGED,
		&vertexBuffer,
		0);

	RenderManager::GetDevice()->CreateIndexBuffer(
		triangleCount * 3 * sizeof(INDEX16),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&triangles,
		0);
	RenderManager::UnlockDevice();

	// 높이맵 로드
	vertexInfo = new Vector3[width * height];

	Vertex* vertices;
	int index = 0;
	vertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	
	for (int i = 0; i < height;i++)
	{
		float v = i/ float(height - 1);

		for (int j = 0; j < width; j++)
		{
			index = i * width + j;
			float u = j / float(width - 1);
			
			vertices[index] = Vertex(Vector3(j, 0.f, i), D3DCOLOR_XRGB(255,255,255),u*30,v*30);
			vertexInfo[index].x = j;	
			vertexInfo[index].y = 0.f;
			vertexInfo[index].z = i;

		}
	}
	
	vertexBuffer->Unlock();
	//int count = 0;
	//WORD* indices = nullptr;
	//triangles->Lock(0, 0, (void**)&indices, 0);

	//for (int i = 0; i < height-1; i++)
	//{
	//	for (int j = 0; j < width-1; j++)
	//	{
	//		int index = i * width + j;
	//		indices[count] = i * width + j;
	//		indices[count+1] = (i+1) * width + j;
	//		indices[count+2] = i * width + j + 1;

	//		indices[count+3] = i * width + j + 1;
	//		indices[count+4] = (i + 1) * width + j;
	//		indices[count+5] = (i + 1) * width + j + 1;

	//		count += 6;
	//	}
	//}
	//
	//
	//triangles->Unlock();

	SetNormalVector();
}

PKH::Terrain::~Terrain()
{
	if (vertexInfo)
	{
		delete[] vertexInfo;
		vertexInfo = nullptr;
	}
	
		
}

void PKH::Terrain::Update()
{
}

IComponent* PKH::Terrain::Clone()
{
    return nullptr;
}

void PKH::Terrain::LoadHeightMap(const string& filePath)
{
	BITMAPFILEHEADER fileHeader;
	BITMAPINFOHEADER infoHeader;
	FileManager::SetDirectory(filePath.c_str());
	FileManager::OpenFile("rb");
	FileManager::ReadFile(&fileHeader, sizeof(fileHeader), 1);
	FileManager::ReadFile(&infoHeader, sizeof(infoHeader), 1);

	FileManager::Seek(fileHeader.bfOffBits, SEEK_SET);

	int byteCount = infoHeader.biBitCount / 8;

	int imgSize = infoHeader.biWidth * infoHeader.biHeight * byteCount;
	unsigned char* buffer = new unsigned char[imgSize];
	FileManager::ReadFile(buffer, imgSize, 1);

	FileManager::CloseFile();


	Vertex* vertices;
	int k = 0;
	int h = 0;
	int index = 0;
	vertexBuffer->Lock(0, 0, (void**)&vertices, 0);


	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			index = i * width + j;
			h = buffer[k] / 10.f;
			vertices[index].pos.y = h;
			vertexInfo[index].y = h;
			k += byteCount;
		}
	}


	vertexBuffer->Unlock();

	delete[] buffer;

	SetNormalVector();
}

bool PKH::Terrain::GetYFromPoint(float* _outY, float _x, float _z)
{
	if (_outY == nullptr)return false;
	if (_x < 0)return false;
	if (_z < 0)return false;
	if (_x >= width-1)return false;
	if (_z >= height-1)return false;

	int x = (int)_x;
	int z = (int)_z;
	float fx = _x - x;
	float fz = _z - z;
	float fx2 = 1.f - fx;
	float fz2 = 1.f - fz;

	Vector3 points[3];
	float len = sqrtf(fx * fx + fz * fz); // 좌표 대각선 길이
	float len2 = sqrtf(fx2 * fx2 + fz2 * fz2); // 대각선길이의 반
	if (len < len2) // 왼쪽 아래 삼각
	{
		points[0] = vertexInfo[z * width + x]; // 0,0
		points[1] = vertexInfo[(z + 1) * width + x]; //1,0
		points[2] = vertexInfo[z * width + (x + 1)]; //0,1
	}
	else // 오른쪽 위 삼각
	{
		points[0] = vertexInfo[(z + 1) * width + (x + 1)]; //1,1
		points[1] = vertexInfo[z * width + (x + 1)]; // 0,1
		points[2] = vertexInfo[(z + 1) * width + x]; // 1,0
	}

	Vector3 dir1 = points[1] - points[0];
	Vector3 dir2 = points[2] - points[0];
	Vector3 normal = Vector3::Cross(dir1, dir2).Normalized();

	// ax + by + cz + d = 0

	// d = -ax -by -cz;
	float d = -normal.x * points[0].x - normal.y * points[0].y - normal.z * points[0].z;
	// by = -ax-cz-d
	// y = (-ax-cz-d)/b
	*_outY = (-normal.x * _x - normal.z * _z - d)/normal.y;



	return true;
}

void PKH::Terrain::SetNormalVector()
{
	Vertex* vertices;
	int index = 0;
	vertexBuffer->Lock(0, 0, (void**)&vertices, 0);

	int count = 0;
	INDEX16* indices = nullptr;
	triangles->Lock(0, 0, (void**)&indices, 0);

	for (unsigned long i = 0; i < height - 1; ++i)
	{
		for (unsigned long j = 0; j < width - 1; ++j)
		{
			index = i * width + j;

			// 오른쪽 위
			indices[count]._0 = index + width;
			indices[count]._1 = index + width + 1;
			indices[count]._2 = index + 1;

			Vector3	vDest, vSour, vNormal;

			vDest = vertices[indices[count]._1].pos - vertices[indices[count]._0].pos;
			vSour = vertices[indices[count]._2].pos - vertices[indices[count]._1].pos;

			D3DXVec3Cross(&vNormal, &vDest, &vSour);
			vertices[indices[count]._0].normal += vNormal;
			vertices[indices[count]._1].normal += vNormal;
			vertices[indices[count]._2].normal += vNormal;
			++count;

			// 왼쪽 아래
			indices[count]._0 = index + width;
			indices[count]._1 = index + 1;
			indices[count]._2 = index;

			vDest = vertices[indices[count]._1].pos - vertices[indices[count]._0].pos;
			vSour = vertices[indices[count]._2].pos - vertices[indices[count]._1].pos;

			D3DXVec3Cross(&vNormal, &vDest, &vSour);
			vertices[indices[count]._0].normal += vNormal;
			vertices[indices[count]._1].normal += vNormal;
			vertices[indices[count]._2].normal += vNormal;
			++count;
		}
	}
	for (unsigned long i = 0; i < vertexCount; ++i)
		D3DXVec3Normalize(&vertices[i].normal, &vertices[i].normal);


	triangles->Unlock();
	vertexBuffer->Unlock();
}
