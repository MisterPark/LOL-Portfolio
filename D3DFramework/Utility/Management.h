#pragma once

class Scene;

class Management
{
private:
	Management();
	~Management();

public:
	static Management* GetInstance();
	static void Destroy();



public:
	std::map<std::wstring, Scene*> sceneMap;
};

