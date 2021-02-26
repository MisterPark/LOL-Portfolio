#pragma once
#include <d3dx9math.h>

namespace Engine
{
	class Color
	{
	public:

		Color();
		Color(D3DCOLOR d3dcolor);
		Color(FLOAT r, FLOAT g, FLOAT b, FLOAT a);



	public:
		D3DCOLOR value = 0;


		static const Color RedMonster;
		static const Color Green;
		static const Color White;
		static const Color Black;
		static const Color Gray;
		static const Color BlueMonster;
	};
	
}
