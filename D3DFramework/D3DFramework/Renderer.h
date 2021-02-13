#pragma once
#include<d3dx9.h>
class Renderer
{
public:
	virtual ~Renderer() = default;
	virtual HRESULT GetEffect(const wchar_t* id, ID3DXEffect** effect) = 0;
};