#include "GameManager.h"
#include "Tags.h"
#include "GameObjectManager.h"
#include <iostream>

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
