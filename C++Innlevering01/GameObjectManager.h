#pragma once
#include "GameObject.h"

//enum ScreenLocation
//{
//	SCREEN_Inside,
//	SCREEN_Left,
//	SCREEN_Right,
//	SCREEN_Top,
//	SCREEN_Bottom
//};

class GameObjectManager
{
public:
	GameObjectManager(int screenWidth, int screenHeight);
	~GameObjectManager();
	void Update();
	GameObject* CreateObject();
//	ScreenLocation GetObjectLocation(Vector2D pos);
private:
	std::vector<GameObject*> _allGameObjects;
	int _screenWidth;
	int _screenHeight;
};

