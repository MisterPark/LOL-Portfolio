#include "stdafx.h"
#include "Texture.h"

using namespace Engine;

Engine::Texture::Texture()
{
	memset(&imageInfo, 0, sizeof(D3DXIMAGE_INFO));
}

Engine::Texture::~Texture()
{
}

int Engine::Texture::GetSpriteWidth()const
{
	//if (this == nullptr) return 0;
	return imageInfo.Width / colCount;
}

int Engine::Texture::GetSpriteHeight()const
{
	if (this == nullptr) return 0;
	return imageInfo.Height / rowCount;
}
