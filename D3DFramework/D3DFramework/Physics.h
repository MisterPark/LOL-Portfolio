#pragma once

namespace PKH
{
	class Collider;

	struct Ray
	{
		Ray() {  };
		Ray(Vector3 origin, Vector3 direction)
		{
			this->origin = origin;
			this->direction = direction;
		}

		Vector3 GetPoint(float distance)
		{
			Vector3 result = origin + (direction * distance);
			return result;
		}

		Vector3 origin;
		Vector3 direction;
	};

	struct RaycastHit
	{
		// 광선의 시작지점부터 충돌된 지점과의 거리.
		float distance;
		// 광선이 충돌체에 맞은 월드공간의 충돌 지점.
		Vector3 point;
		// 광선에 맞은 충돌체.
		Collider* collider = nullptr;

	};

	class Physics
	{
	public:
		static bool Raycast(Ray ray, RaycastHit* outHit, float maxDistance = INFINITY, int layerMask = 0xFFFFFFFF);
		static bool Raycast(Vector3 origin, Vector3 direction, float maxDistance = INFINITY, int layerMask = 0xFFFFFFFF);
		
	
	};

}

