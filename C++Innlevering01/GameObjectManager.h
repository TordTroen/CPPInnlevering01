#pragma once
#include "GameObject.h"

class Vector2D;

class GameObjectManager
{
public:
	~GameObjectManager();
	void Update();
	GameObject* CreateObject();
	GameObject* CreateObject(std::string tag);
	GameObject* CreateObject(std::vector<Component*> components, std::string tag = NULL);
private:
	std::vector<GameObject*> _allGameObjects;

// Singleton stuff
public:
	static GameObjectManager& GetInstance()
	{
		static GameObjectManager instance;
		return instance;
	}
private:
	GameObjectManager() {};
	GameObjectManager(GameObjectManager const&);
	void operator=(GameObjectManager const&);
};
