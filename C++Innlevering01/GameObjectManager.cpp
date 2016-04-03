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

std::shared_ptr<GameObject> GameObjectManager::CreateObject()
{
	std::shared_ptr<GameObject> obj(new GameObject());
	_allGameObjects.emplace_back(obj);
	return obj;
}

std::shared_ptr<GameObject> GameObjectManager::CreateObject(std::string tag)
{
	std::shared_ptr<GameObject> obj = CreateObject();
	obj->SetTag(tag);
	return obj;
}

std::shared_ptr<GameObject> GameObjectManager::CreateObject(std::vector<std::shared_ptr<Component>> components, std::string tag)
{
	std::shared_ptr<GameObject> obj = CreateObject(tag);
	for (auto it : components)
	{
		obj->AddComponent(it);
	}
	return obj;
}

std::shared_ptr<GameObject> GameObjectManager::FindGameObjectByTag(std::string tag)
{
	for (auto it : _allGameObjects)
	{
		if (it->CompareTag(tag))
		{
			return it;
		}
	}
	return nullptr;
}
