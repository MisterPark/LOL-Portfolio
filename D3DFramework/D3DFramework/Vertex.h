﻿#pragma once

namespace Engine
{
	class Vertex
	{
	public:
		Vertex(Vector3 _pos, D3DCOLOR _color, float _u, float _v);

		Vector3 pos;
		Vector3 normal;
		D3DCOLOR color;
		float u;
		float v;

		static const DWORD FVF;
	};
	class VertexColor
	{
	public:
		VertexColor(float _x, float _y, float _z, D3DCOLOR _color);

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
		VertexUV(Vector3 _v, Vector2 _uv);

		float x;
		float y;
		float z;
		float u;
		float v;

		static const DWORD FVF; 
	};

	typedef	struct tagIndex16
	{
		unsigned short	_0, _1, _2;

	}INDEX16;

	typedef	struct tagIndex32
	{
		unsigned long	_0, _1, _2;

	}INDEX32;
}
