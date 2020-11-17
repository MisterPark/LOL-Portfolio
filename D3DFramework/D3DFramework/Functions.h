#pragma once

template <typename T>
constexpr int MaxOfEnum()
{
	return (int)T::END;
}