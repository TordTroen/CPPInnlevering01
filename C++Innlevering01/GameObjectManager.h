#pragma once
#include "GameObject.h"
class GameObjectManager
{
public:
	GameObjectManager();
	~GameObjectManager();
	void Update();
	GameObject* CreateObject();
private:
	std::vector<GameObject*> _allGameObjects;
};

