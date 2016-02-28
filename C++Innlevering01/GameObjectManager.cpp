#include "GameObjectManager.h"



GameObjectManager::GameObjectManager()
{
}


GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Update()
{
	for (auto i : _allGameObjects)
	{
		i->Update();
	}
}

GameObject* GameObjectManager::CreateObject()
{
	GameObject *obj = new GameObject();
	_allGameObjects.emplace_back(obj);
	return obj;
}
