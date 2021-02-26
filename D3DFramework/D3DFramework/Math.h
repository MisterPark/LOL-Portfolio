#pragma once

namespace Engine
{
	class Math
	{
		template<typename T>
		static T Clamp(T value, T min, T max);
	};


	template<typename T>
	inline T Math::Clamp(T value, T min, T max)
	{
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}

}
