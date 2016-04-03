#include "GameManager.h"
#include "PlayerController.h"
#include "Tags.h"
#include "GameObjectManager.h"

float GameManager::GetCenterXPosition(float width) const
{
	return _windowWidth / 2 - width / 2;
}

void GameManager::OnGameStateChanged()
{
	std::shared_ptr<GameObject> paddleObj = NULL;;
	std::shared_ptr<PlayerController> pc = NULL;
	switch (_gameState)
	{
	case MainMenu:
		break;
	case Paused:
		break;
	case InGame:
		// TODO move this to the function that is called when pressing playbutton
		//GameObject* playerObj = GameObjectManager::GetInstance().FindGameObjectByTag(Tags::Paddle);
		//_playerController = playerObj->GetComponent<PlayerController>();
		paddleObj = GameObjectManager::GetInstance().FindGameObjectByTag(Tags::Paddle);
		pc = paddleObj->GetComponent<PlayerController>();
		//playerController->Start();
		break;
	case Exit:
		break;
	default:
		break;
	}
}
