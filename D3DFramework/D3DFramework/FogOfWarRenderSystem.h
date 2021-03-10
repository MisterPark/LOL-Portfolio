#pragma once
namespace Engine
{
	class FogOfWarRenderSystem
	{
	public:
		struct FogSight
		{
			float radius1;
			float radius2;
			Vector3 position;
		};
		static void Initialize();
		static void Destory();
		static void Begin();
		static void End();
		static void GetMapSpace(Matrix* out);
		static void AddSight(FogSight const& fogSight);
		static void GetDepthBuffer(IDirect3DSurface9** surface);
		static bool IsInSight(Vector3 const& pos);
	};
}