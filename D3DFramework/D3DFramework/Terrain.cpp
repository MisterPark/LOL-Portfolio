#include "stdafx.h"
#include "Terrain.h"

PKH::Terrain::Terrain()
{
	this->vertexCount = width * height;
	this->triangleCount = (width-1) * (height-1) * 2;

	D2DRenderManager::GetDevice()->CreateVertexBuffer(
		vertexCount * sizeof(VertexColor),
		D3DUSAGE_WRITEONLY,
		VertexColor::FVF,
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


	// ³ôÀÌ¸Ê ·Îµå



	VertexColor* vertices;
	vb->Lock(0, 0, (void**)&vertices, 0);

	
	for (int i = 0; i < height;i++)
	{
		for (int j = 0; j < width; j++)
		{
			vertices[i * width + j] = VertexColor(j, 0.f, i, D3DCOLOR_XRGB(j*20,i*20,0));
		}
	}
	
	
	vb->Unlock();

	int count = 0;
	WORD* indices = nullptr;
	triangles->Lock(0, 0, (void**)&indices, 0);

	for (int i = 0; i < height-1; i++)
	{
		for (int j = 0; j < width-1; j++)
		{
			int index = i * width + j;
			indices[count] = i * width + j;
			indices[count+1] = (i+1) * width + j;
			indices[count+2] = i * width + j + 1;

			indices[count+3] = i * width + j + 1;
			indices[count+4] = (i + 1) * width + j;
			indices[count+5] = (i + 1) * width + j + 1;

			count += 6;
		}
	}
	
	
	triangles->Unlock();
}

PKH::Terrain::~Terrain()
{
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


	VertexColor* vertices;
	int k = 0;
	vb->Lock(0, 0, (void**)&vertices, 0);


	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			vertices[i * width + j].y = buffer[k] / 25.f;
			k += byteCount;
		}
	}


	vb->Unlock();
}
