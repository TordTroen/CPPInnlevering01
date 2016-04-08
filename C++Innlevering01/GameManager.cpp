#include "GameManager.h"
#include "PlayerController.h"
#include "Tags.h"
#include "GameObjectManager.h"
#include <iostream>
float GameManager::GetCenterXPosition(float width) const
{
	return windowWidth / 2 - width / 2;
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

void GameManager::OnGameStateChanged()
{
	switch (gameState)
	{
	case GameState::MainMenu:
		break;
	case GameState::Paused:
		break;
	case GameState::InGame:
		// TODO move this to the function that is called when pressing playbutton
		//playerController->Start();
		break;
	case GameState::Exit:
		break;
	default:
		break;
	}
}
