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

GameObject* GameObjectManager::CreateObject(std::string tag)
{
	GameObject *obj = CreateObject();
	obj->SetTag(tag);
	return obj;
}

GameObject* GameObjectManager::CreateObject(std::vector<Component*> components, std::string tag)
{
	GameObject* obj = CreateObject(tag);
	for (auto it : components)
	{
		obj->AddComponent(it);
	}
	return obj;
}
