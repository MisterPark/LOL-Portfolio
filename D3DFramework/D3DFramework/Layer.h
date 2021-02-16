#pragma once

enum class Layer
{
	Default,
	Node,
	Ground,
	Wall,
	Bush,
	Indicator,
	Unit,
	Building,
	Effect,
	UI,
	END
};


class LayerMask
{
public:
	template<typename _Layer> 
	static int GetMask(_Layer layer)
	{
		int val = (int)layer;
		val = (int)pow(2, val);
		return val;
	}

	template <typename _Layer, typename... _Layers>
	static int GetMask(_Layer layer, _Layers... layers)
	{
		int sum = 0;
		int val = (int)layer;
		val = (int)pow(2, val);

		sum = sum | val;
		sum = sum | GetMask(layers...);

		return sum;
	}

public:
	int value = 0;
};
