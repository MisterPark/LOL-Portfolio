#pragma once
#include "IComponent.h"
#include <typeinfo>
namespace Engine
{
	enum class RendererType :int;
	class Renderer;

	
	class Renderer : public IComponent
	{
	protected:
		Renderer(Engine::GameObject* owner, RendererType rendererType);
	public:
		~Renderer();
		virtual void Render() PURE;
		void SetShadowState(bool use);
		bool IsShadowState();
	protected:
		void AttachToRenderSystem(std::type_info const& infos);
		void DettachToRenderSystem(std::type_info const& infos);
	public:
		RendererType rendererType;
	private:
		bool attached;
		bool shadow;
	};
}