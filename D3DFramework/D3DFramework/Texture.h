#pragma once

namespace Engine
{
	typedef DWORD TextureID;

	enum class TextureType
	{
		DEFAULT,
		CUBE,
	};
	
	class Texture
	{
	public:
		Texture();
		~Texture();

		int GetSpriteWidth()const;
		int GetSpriteHeight()const;

		LPDIRECT3DTEXTURE9 pTexture = nullptr;
		D3DXIMAGE_INFO imageInfo;
		DWORD rowCount = 1;
		DWORD colCount = 1;
		TextureID id = 0;
	};


}
