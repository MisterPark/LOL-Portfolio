#pragma once

#include<typeinfo>
namespace Engine
{
	enum class RendererType :int
	{
		EarlyForward,
		Deferred,
		Forward,
		UI,
		END
	};
	class Renderer;
	class RenderSystem
	{
		friend class Renderer;
	public:
		static void Initialize();
		static void Destory();
		static void			AddLight(const wchar_t* name, const D3DLIGHT9& init );
		static void			RemoveLight(const wchar_t* name);
		static D3DLIGHT9*	GetLight(const wchar_t* name);
		static int			GetLightCount();
		static void			GetLights(D3DLIGHT9* buffer, int count);
		static wstring const& GetLightName(int index);
		static void			EnableShadow(const wchar_t* lightName);
		static void			DisableShadow(const wchar_t* lightName);
		static void			Render();
		static bool			GetShadowMap(const wchar_t* lightName, RenderTarget** renderTarget, IDirect3DSurface9** depthBuffer, Matrix* proj);
		static long			GetUniqueID();
	private:
		static void SetupShadowMap();
		static void RednerEarlyForward();
		static void RednerDeferred();
		static void RenderForward();
		static void RenderUI();
		static void RenderLigting();
		static void RenderCombine();
		static void Add(Renderer*);
		static void Remove(Renderer*);

	};
	extern wchar_t const* const RENDER_TARGET_ALBEDO;
	extern wchar_t const* const RENDER_TARGET_NORMAL;
	extern wchar_t const* const RENDER_TARGET_SHARPNESS;
	extern wchar_t const* const LIGHT_SPECULAR;
	extern wchar_t const* const LIGHT_DIFFUSE;
	extern wchar_t const* const RENDER_TARGET_RIMLIGHT_COLOR;
}
using RenderSystem = Engine::RenderSystem;