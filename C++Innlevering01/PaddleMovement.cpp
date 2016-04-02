#include "PaddleMovement.h"
#include "Vector2D.h"
#include "InputManager.h"
#include "Transform.h"

PaddleMovement::PaddleMovement()
{
}


PaddleMovement::~PaddleMovement()
{
}

void PaddleMovement::Update()
{
	float x = InputManager::GetInstance().GetAxis(SDL_SCANCODE_RIGHT, SDL_SCANCODE_LEFT);
	Vector2D velocity = Vector2D(x, 0);
	GetTransform()->Translate(velocity, true);
}
