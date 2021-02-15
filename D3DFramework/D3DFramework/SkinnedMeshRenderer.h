#pragma once
#include"Renderer.h"
#include"DynamicMesh.h"
#include"RenderSystem.h"
#include<vector>
namespace KST
{

	class SkinnedMeshRenderer :
		public Renderer
	{
	public:
		static KST::RendererType constexpr RenderingType = KST::RendererType::Forward;
	public:
		SkinnedMeshRenderer(PKH::GameObject* owner);
		virtual void Render();
		PKH::IComponent* Clone() { return nullptr; }
		void SetMesh(DynamicMesh* mesh);
	private:
		DynamicMesh* mesh;
	};
}