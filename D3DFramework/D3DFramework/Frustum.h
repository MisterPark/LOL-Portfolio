#pragma once


namespace PKH
{
	class Frustum
	{
	private:
		Frustum();
		~Frustum();

		void Initialize();

	public:
		static Frustum* GetInstance();
		static void Destroy();

		static void Update();

		static bool Intersect(const Vector3* pWorldPos);
		static bool Intersect(const Vector3* pWorldPos, const float& radius);
		

	private:
		Vector3 point[8];
		D3DXPLANE plane[6];
	};


}
