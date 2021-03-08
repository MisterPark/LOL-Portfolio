#pragma once

#include "Scene.h"

namespace Engine
{
	class SceneManager
	{
	private:
		SceneManager();
		~SceneManager();
		static void LoadScene(Scene* pScene);
	public:
		static SceneManager* GetInstance();
		static void Destroy();
		static void PreUpdate();
		static void Update();
		static void PostUpdate();
		//매개 인자가 없는 씬 생성자 호출
		template<typename SceneT>
		static void LoadScene();
		template<typename SceneT, typename ...ArgT>
		static void LoadScene(ArgT&& ...args);

		static Scene* GetCurrentScene();
	private:
		Scene* pCurrentScene = nullptr;
		Scene* pReadyScene = nullptr;
	};

	template<typename SceneT>
	inline void SceneManager::LoadScene()
	{
		LoadScene(static_cast<Scene*>(new SceneT{}));
	}

	template<typename SceneT, typename ...ArgT>
	inline void SceneManager::LoadScene(ArgT&& ...args)
	{
		LoadScene(static_cast<Scene*>(new SceneT{ std::forward<ArgT>(args) ... }));
	}

}
