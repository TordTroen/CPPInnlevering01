#include "GameObjectManager.h"
#include <algorithm>

GameObjectManager::~GameObjectManager()
{
}

void GameObjectManager::Update()
{
	for (int i = 0; i < allGameObjects.size(); i++)
	{
		if (allGameObjects[i] != NULL)
		{
			allGameObjects[i]->Update();
		}
	}
}

GameObject* GameObjectManager::CreateObject()
{
	GameObject* obj = new GameObject();
	allGameObjects.emplace_back(obj);
	return obj;
}

GameObject* GameObjectManager::CreateObject(std::string tag)
{
	GameObject* obj = CreateObject();
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

void GameObjectManager::DeleteGameObject(GameObject** go)
{
	if (*go == NULL) return;

	allGameObjects.erase(
		std::remove_if( // Selectively remove elements in the second vector...
			allGameObjects.begin(),
			allGameObjects.end(),
			[&](std::unique_ptr<GameObject> const& p)
			{   // This predicate checks whether the element is contained
				// in the second vector of pointers to be removed...
				return *go == p.get();
			}), allGameObjects.end());
	*go = NULL;
}

GameObject* GameObjectManager::FindGameObjectByTag(std::string tag)
{
	for (auto const& it : allGameObjects)
	{
		if (it->CompareTag(tag))
		{
			return it.get();
		}
	}
	std::cout << "WARNING: Couldn't find a GameObject with the tag '" <<
		tag.c_str() << "'" << std::endl;
	return nullptr;
}
