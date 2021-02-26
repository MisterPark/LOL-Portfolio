#pragma once
#include <d3dx9math.h>

namespace Engine
{
	class Quaternion : public D3DXQUATERNION
	{
	public:
		Quaternion();
		Quaternion(const FLOAT* r);
		Quaternion(FLOAT fx, FLOAT fy, FLOAT fz, FLOAT fw);
		Quaternion(const D3DXQUATERNION& r);
		~Quaternion();

		static Vector3 ToEulerAngles(const Quaternion& _quat);

	};


}
