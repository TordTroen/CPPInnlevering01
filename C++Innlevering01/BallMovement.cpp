#include "BallMovement.h"
#include "Transform.h"
#include "GameObject.h"
#include "Collider.h"
#include <iostream>

BallMovement::BallMovement(Vector2D startVector, float speed)
{
	_speed = speed;
	_movement = startVector;
}

BallMovement::~BallMovement()
{
}

void BallMovement::Update()
{
	GetTransform()->Translate(_movement * _speed);
}

void BallMovement::OnCollisionEnter(const Collider * other)
{
	std::string tag = other->GetGameObject()->GetTag();
	if (tag == "LeftWall" || tag == "RightWall")
	{
		_movement.X *= -1;
	}
	else if (tag == "TopWall" || tag == "BottomWall")
	{
		_movement.Y *= -1;
	}
}
