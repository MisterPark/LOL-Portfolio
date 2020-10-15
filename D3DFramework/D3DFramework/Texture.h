#pragma once

namespace PKH
{
	enum class TextureKey
	{
		NONE,
		SKY_U,
		SKY_D,
		SKY_L,
		SKY_R,
		SKY_F,
		SKY_B,
		CURSOR_TARGET,
		LOCK_ON,

	};

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
	};


}
