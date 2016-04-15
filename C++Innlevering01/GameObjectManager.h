#pragma once
#include "GameObject.h"
#include <memory>
class Vector2D;

class GameObjectManager
{
public:
	~GameObjectManager();
	void Update();
	GameObject* CreateObject();
	GameObject* CreateObject(std::string tag);
	GameObject* CreateObject(std::vector<Component*> components, std::string tag = NULL);
	void DeleteGameObject(GameObject* go);
	/* Returns a reference to the first GameObject found with the specified tag. */
	GameObject* FindGameObjectByTag(std::string tag);
private:
	std::vector<std::unique_ptr<GameObject>> allGameObjects;

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
