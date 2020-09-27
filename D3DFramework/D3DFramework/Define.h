#pragma once

#define dfCLIENT_WIDTH 800
#define dfCLIENT_HEIGHT 600

template <typename T>
constexpr int MaxOfEnum()
{
	return (int)T::END;
}