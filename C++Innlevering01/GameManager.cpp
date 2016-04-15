#include "GameManager.h"
#include "PlayerController.h"
#include "Tags.h"
#include "GameObjectManager.h"
#include <iostream>

float GameManager::GetCenterXPosition(float width) const
{
	return windowWidth / 2 - width / 2;
}

float GameManager::GetCenterYPosition(float height) const
{
	return windowHeight / 2 - height / 2;
}
