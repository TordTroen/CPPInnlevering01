#pragma once
#include "GameObject.h"
#include <memory>
class Vector2D;

class GameObjectManager
{
public:
	~GameObjectManager();
	void Update();
	std::shared_ptr<GameObject> CreateObject();
	std::shared_ptr<GameObject> CreateObject(std::string tag);
	std::shared_ptr<GameObject> CreateObject(std::vector<std::shared_ptr<Component>> components, std::string tag = NULL);
	/* Returns a reference to the first GameObject found with the specified tag. */
	std::shared_ptr<GameObject> FindGameObjectByTag(std::string tag);
private:
	std::vector<std::shared_ptr<GameObject>> _allGameObjects;

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
