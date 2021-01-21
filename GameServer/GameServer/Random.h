#pragma once

namespace PKH
{
	class Random
	{
	public:

		static void InitState();
		static void InitState(int seed);
		static int Value(int numOfCases);
		static int Range(int min, int max);
		static float Range(float min, float max);
	};
}


