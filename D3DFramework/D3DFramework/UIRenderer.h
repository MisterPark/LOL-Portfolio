#pragma once
#include "Renderer.h"

namespace Engine
{
	class UIRenderer :
		public Renderer
	{
	public:
		explicit UIRenderer(GameObject* owner);
		// Renderer을(를) 통해 상속됨
		virtual IComponent* Clone() override;
		virtual void Render() override;

		void SetMesh(Engine::Mesh* mesh);
		void SetTimerRatio(float ratio);
		void SetGradientMap(const std::wstring& _maptag, int _max, int _idx);
		void SetGradientMapIndex(int _idx);

		void BringToTop();
	public:
		int zOrder = 0;
	protected:
		Engine::Mesh* mesh = nullptr;
		Engine::UI* ui = nullptr;
		ID3DXEffect* effect = nullptr;
		Texture* timerGradientTex = nullptr;
		Texture* gradientmapTex = nullptr;
		int gradientmapMaxCnt = 0;
		int gradientmapIndex = 0;
		float timerRatio;
	private:
		static int uniqueZIndex;
	};


}
