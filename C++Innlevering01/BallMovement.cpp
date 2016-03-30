#include "BallMovement.h"
#include "Transform.h"
#include "GameObject.h"
#include "Collider.h"
#include "Tags.h"
#include "SDLWrapper.h"
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
	if (tag == Tags::Paddle)
	{
		Vector2D paddle = other->GetTransform()->GetCenter();
		Vector2D ball = GetTransform()->GetCenter();
		SDLWrapper::GetInstance().CreateRect(Color(100, 100, 10), Rect(paddle.X - 5, paddle.Y - 5, 10, 10));
		SDLWrapper::GetInstance().CreateRect(Color(0, 255, 10), Rect(ball.X - 5, ball.Y - 5, 10, 10));
		
		//Vector2D dif = (paddle - ball);
		float dist = (paddle - ball).GetLength();
		dist = dist / (paddle - other->GetTransform()->_position).GetLength();
		if (ball.X < paddle.X)
		{
			dist *= -1;
		}
		_movement.X = dist;
		if (_movement.Y > 0)
			_movement.Y *= -1;
		// TODO Normalize movement?
	}
	else if (tag == Tags::WallLeft || tag == Tags::WallRight)
	{
		_movement.X *= -1;
	}
	else if (tag == Tags::WallTop || tag == Tags::WallBottom)
	{
		_movement.Y *= -1;
	}
}
