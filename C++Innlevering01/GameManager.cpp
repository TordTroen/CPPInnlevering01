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

void GameManager::Init(GameState startState)
{
	GameObject* paddleObj = GameObjectManager::GetInstance().FindGameObjectByTag(Tags::Paddle);
	if (paddleObj == NULL)
	{
		std::cout << "Couldn't find the paddle GameObject!" << std::endl;
	}
	else
	{
		playerController = paddleObj->GetComponent<PlayerController>();
	}
}
