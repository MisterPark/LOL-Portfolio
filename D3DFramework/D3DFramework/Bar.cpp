#include "stdafx.h"
#include "Bar.h"

Bar::Bar()
	:UI()
{

}

Bar::Bar(const std::wstring& _tag, const Vector2& pos)
	:UI(_tag,pos)
{

}

Bar::~Bar()
{
}

float Bar::GetRatio()
{
	return this->ratio;
}

void Bar::SetRatio(float _ratio)
{
	this->ratio = _ratio;
}
