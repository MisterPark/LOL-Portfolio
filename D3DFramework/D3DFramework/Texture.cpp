#include "stdafx.h"
#include "Texture.h"

using namespace PKH;

PKH::Texture::Texture()
{
	memset(&imageInfo, 0, sizeof(D3DXIMAGE_INFO));
}

PKH::Texture::~Texture()
{
}

int PKH::Texture::GetSpriteWidth()const
{
	//if (this == nullptr) return 0;
	return imageInfo.Width / colCount;
}

int PKH::Texture::GetSpriteHeight()const
{
	if (this == nullptr) return 0;
	return imageInfo.Height / rowCount;
}
