#include "GameObjectManager.h"



GameObjectManager::GameObjectManager(int screenWidth, int screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;
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

//ScreenLocation GameObjectManager::GetObjectLocation(Vector2D pos)
//{
//	if (pos.X < 0)
//	{
//		return SCREEN_Left;
//	}
//	else if (pos.X > _screenWidth)
//	{
//		return SCREEN_Right;
//	}
//	else if (pos.Y < 0)
//	{
//		return SCREEN_Top;
//	}
//	else if (pos.Y > _screenHeight)
//	{
//		return SCREEN_Bottom;
//	}
//	return SCREEN_Inside;
//}
