#pragma once

template <typename T>
constexpr int MaxOfEnum()
{
	return (int)T::END;
}

static int GetPokemonGeneration(Pokemon number)
{
	int num = (int)number;
	if (num > (int)Pokemon::Celebi)
	{
		return 3;
	}
	else if (num > (int)Pokemon::Mew)
	{
		return 2;
	}
	else
	{
		return 1;
	}
}