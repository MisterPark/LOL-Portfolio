#include "stdafx.h"
#include "Renderer.h"
#include "RenderSystem.h"
namespace Engine
{
	Renderer::Renderer(Engine::GameObject* owner, RendererType rendererType):
		IComponent{ owner },
		attached{ false },
		shadow{ false },
		rendererType{ rendererType }
	{
		RenderSystem::Add(this);
	}
	Renderer::~Renderer()
	{
		RenderSystem::Remove(this);
	}
	void Renderer::SetShadowState(bool use)
	{
		shadow = use;
	}

	bool Renderer::IsShadowState()
	{
		return shadow;
	}

	void Renderer::AttachToRenderSystem(std::type_info const& infos)
	{
		if (attached)
		{
			return;
		}
		RenderSystem::Add(this);
		attached = true;
	}

	void Renderer::DettachToRenderSystem(std::type_info const& infos)
	{
		if (!attached)
		{
			return;
		}
		RenderSystem::Remove(this);
	}

}
