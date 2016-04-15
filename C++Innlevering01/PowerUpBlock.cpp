#include "PowerUpBlock.h"
#include "Vector2D.h"
#include "InputManager.h"
#include "GameManager.h"
#include "GameObject.h"
#include "Transform.h"
#include "Time.h"


PowerUpBlock::PowerUpBlock(Vector2D start, float speed)
	: starting(start), speedBox(speed)
{
}


PowerUpBlock::~PowerUpBlock()
{
}

void PowerUpBlock::Update()
{
	Vector2D velocity = Vector2D(0, 0.5);
	GetTransform()->Translate(velocity * speedBox * Time::DeltaTime(), true);
}