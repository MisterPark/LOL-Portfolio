#pragma once
#include "Renderer.h"
#include "UIRenderer.h"
#include "Mesh.h"
#include "UI.h"
#include <d3dx9.h>
namespace Engine
{
	class MinimapRenderer :
		public UIRenderer
	{
	public:
		explicit MinimapRenderer(GameObject* owner);
		// Renderer을(를) 통해 상속됨
		virtual IComponent* Clone() override;
		virtual void Render() override;
	};
}
