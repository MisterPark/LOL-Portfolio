#pragma once
#include "Renderer.h"

namespace KST
{
	class UIRenderer :
		public Renderer
	{
	public:
		explicit UIRenderer(GameObject* owner);
		// Renderer을(를) 통해 상속됨
		virtual IComponent* Clone() override;
		virtual void Render() override;

		void SetMesh(PKH::Mesh* mesh);

		void BringToTop();
	public:
		int zOrder = 0;
	protected:
		PKH::Mesh* mesh = nullptr;
		PKH::UI* ui = nullptr;
		
	private:
		static int uniqueZIndex;
	};


}
