#include "PlayerController.h"
#include "GameObject.h"
#include "GameObjectManager.h"
#include "Tags.h"

PlayerController::PlayerController()
	: _ballMovement(NULL)
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
	std::cout << "Stop()" << std::endl;
	GetGameObject()->SetActive(false);
	_ballMovement->GetGameObject()->SetActive(false);
}

void PlayerController::Start()
{
	std::cout << "Start()" << std::endl;
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
	BallMovement* bm = ball->GetComponent<BallMovement>();
	_ballMovement = bm;
}
