#include "PaddleMovement.h"
#include "Vector2D.h"
#include "InputManager.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Time.h"

PaddleMovement::PaddleMovement(Rect startRect, float speed)
	: startRect(startRect), paddleSpeed(speed)
{
}

PaddleMovement::~PaddleMovement()
{
}

void PaddleMovement::Awake()
{
	Reset();
}

void PaddleMovement::Update()
{
	float x = InputManager::GetInstance().GetAxis(SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT);
	Vector2D velocity = Vector2D(x, 0);
	GetTransform()->Translate(velocity * paddleSpeed * Time::DeltaTime(), true);
}

void PaddleMovement::Reset()
{
	GetTransform()->SetRect(startRect);
	GetGameObject()->SetActive(true);
}
