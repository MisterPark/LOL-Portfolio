#pragma once

namespace PKH
{
	class Vertex
	{
	public:
		Vertex(float _x, float _y, float _z, D3DCOLOR _color);

		float x;
		float y;
		float z;
		D3DCOLOR color;

		static const DWORD FVF; //플렉서블 버텍스 포멧 = 자유자재 버텍스 형태 = 커스텀 버텍스
	};
	

	class VertexUV
	{
	public:
		VertexUV(float _x, float _y, float _z, float _u, float _v);

		float x;
		float y;
		float z;
		float u;
		float v;

		static const DWORD FVF; 
	};

}
