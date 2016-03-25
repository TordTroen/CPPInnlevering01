#include "GameObjectManager.h"

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

GameObject* GameObjectManager::CreateObject(std::vector<Component*> components)
{
	GameObject* obj = CreateObject();
	for (auto it : components)
	{
		obj->AddComponent(it);
	}
	return obj;
}
