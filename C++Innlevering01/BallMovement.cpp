#include "BallMovement.h"
#include "Transform.h"
#include "GameObject.h"
#include "Collider.h"
#include <iostream>

BallMovement::BallMovement()
{
	movement = Vector2D(3.5, 1);
}

BallMovement::~BallMovement()
{
}

void BallMovement::Update()
{
	GetTransform()->Translate(movement);
}

void BallMovement::OnCollisionEnter(Collider * other)
{
	std::string tag = other->GetGameObject()->GetTag();
	if (tag == "LeftWall" || tag == "RightWall")
	{
		movement.X *= -1;
	}
	else if (tag == "TopWall" || tag == "BottomWall")
	{
		movement.Y *= -1;
	}
}
