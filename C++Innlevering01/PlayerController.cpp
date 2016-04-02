#include "PlayerController.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Tags.h"

PlayerController::PlayerController()
{
	Reset();
}


PlayerController::~PlayerController()
{
}

void PlayerController::Reset()
{
	_curLives = _startingLives;
	_score = 0;
	// Reset ball movmeent
	// reset paddle position
}

void PlayerController::Stop()
{
	GetGameObject()->SetActive(true);
	_ballMovement->GetGameObject()->SetActive(true);
}

void PlayerController::Start()
{
	GetGameObject()->SetActive(true);
	_ballMovement->GetGameObject()->SetActive(true);
	Reset();
}

void PlayerController::LoseLife()
{
	_curLives--;
	if (_curLives <= 0)
	{
		// TODO Game over
		Stop();
	}
}

void PlayerController::Awake()
{
	GameObject* ball = GameObjectManager::GetInstance().FindGameObjectByTag(Tags::Ball);
	_ballMovement = ball->GetComponent<BallMovement>();
}
