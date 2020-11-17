#pragma once

namespace PKH
{
	enum class TextureKey
	{
		NONE,
		GRASS,
		UI_CURSOR,
		UI_BUTTON,
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
