#pragma once
#include "Scene.h"

class LoadingChampScreen;

class TestLoadingScene :
    public Scene
{
    // Scene을(를) 통해 상속됨
    virtual void OnLoaded() override;
    virtual void OnUnloaded() override;
    virtual void Update() override;

    void LoadResources();

    void LoadStaticMeshAsync(const wstring& filePath);
    void LoadDynamicMeshAsync(const wstring& filePath);
    void LoadNavMeshAsync(const wstring& filePath);
    void LoadTerrainMeshAsync(const wstring& filePath);
    void LoadCustomMeshAsync(const wstring& filePath);

    static void Count();

    void CreateChampPanel(int borderW, int borderH, int padding);
    void SetChampPanel();
    void SetSpell();

    LoadingChampScreen* screens[10] = {};
};

