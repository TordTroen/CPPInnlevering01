#include "GameManager.h"
#include <algorithm>
#include <iostream>
#include "GameObject.h"
#include "Tags.h"

//GameManager::GameManager()
//{
//	SetGameState(GameState::MainMenu);
//}

float GameManager::GetCenterXPosition(float width) const
{
	return windowWidth / 2 - width / 2;
}

float GameManager::GetCenterYPosition(float height) const
{
	return windowHeight / 2 - height / 2;
}

void GameManager::Update()
{
	for (int i = 0; i < allGameObjects.size(); i++)
	{
		if (allGameObjects[i] != NULL)
		{
			allGameObjects[i]->Update();
		}
	}
}

GameObject* GameManager::CreateObject()
{
	GameObject* obj = new GameObject(this);
	allGameObjects.emplace_back(obj);
	return obj;
}

GameObject* GameManager::CreateObject(std::string tag)
{
	GameObject* obj = CreateObject();
	obj->SetTag(tag);
	return obj;
}

GameObject* GameManager::CreateObject(std::vector<Component*> components, std::string tag)
{
	GameObject* obj = CreateObject(tag);
	for (auto it : components)
	{
		obj->AddComponent(it);
	}
	return obj;
}

void GameManager::DeleteGameObject(GameObject** go)
{
	if (*go == NULL) return;

	// Snippet from: http://stackoverflow.com/a/15125722/5853590
	// This erases the given gameobject pointer from the allGameObjects vector
	allGameObjects.erase(
		std::remove_if(
			allGameObjects.begin(),
			allGameObjects.end(),
			[&](std::unique_ptr<GameObject> const& p) { return *go == p.get(); }), // The predicate that checks if the given pointer is in the vector
		allGameObjects.end());

	// Null out the reference
	*go = NULL;
}

GameObject* GameManager::FindGameObjectByTag(std::string tag)
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