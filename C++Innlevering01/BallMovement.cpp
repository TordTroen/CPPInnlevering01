#include "BallMovement.h"
#include <iostream>
#include <math.h>
#include "Transform.h"
#include "GameObject.h"
#include "Collider.h"
#include "Tags.h"
#include "SDLWrapper.h"
#include "GameManager.h"
#include "InputManager.h"

BallMovement::BallMovement(Vector2D startVector, float speed)
{
	_speed = speed;
	_movement = startVector.Normalized();
}

BallMovement::~BallMovement()
{
}

void BallMovement::Update()
{
	if (GameManager::GetInstance().GetGameState() == InGame)
	{
		GetTransform()->Translate(_movement * _speed);
	}
	//GetTransform()->SetPosition(InputManager::GetInstance().GetMousePosition());
}

void BallMovement::OnCollisionEnter(const std::shared_ptr<Collider> other)
{
	std::string tag = other->GetGameObject()->GetTag();
	if (tag == Tags::Paddle && _movement.Y > 0)
	{
		Vector2D paddle = other->GetTransform()->GetCenter();
		Vector2D ball = GetTransform()->GetCenter();
		//SDLWrapper::GetInstance().CreateRect(Color(100, 100, 10), Rect(paddle.X - 5, paddle.Y - 5, 10, 10));
		//SDLWrapper::GetInstance().CreateRect(Color(0, 255, 10), Rect(ball.X - 5, ball.Y - 5, 10, 10));
		
		//Vector2D dif = (paddle - ball);
		float dist = (paddle - ball).GetLength();
		dist = dist / (paddle - other->GetTransform()->_position).GetLength();
		if (ball.X < paddle.X)
		{
			dist *= -1;
		}
		_movement.X = dist;
		if (_movement.Y > 0)
		{
			_movement.Y *= -1;
		}
		// TODO Make sure movement always has the same length
		_movement = _movement.Normalized();
	}
	else
	{
		// Third times the charm...
		// "algorithm" borrowed from: http://gamedev.stackexchange.com/a/95848
		Vector2D ball = GetTransform()->GetCenter();
		Vector2D brick = other->GetTransform()->GetCenter();
		float ax = ball.X;
		float ay = ball.Y;
		float bx = brick.X;
		float by = brick.Y;
		float bw = other->GetTransform()->_size.X / 2;
		float bh = other->GetTransform()->_size.Y / 2;

		float dx = abs(ax - bx) - bw;
		float dy = abs(ay - by) - bh;

		// TODO Can add some extra to _movement if one of the components are 0 to prevent sticking to wall??
		if (dx > dy) // Hit something on the left/right
		{
			_movement.X *= -1;
		}
		else // Hit something on the top/bottom
		{
			_movement.Y *= -1;
		}

		//Vector2D dif = (GetTransform()->_position - other->GetTransform()->_position);
		//dif = dif.Normalized();
		//Vector2D norm = Vector2D(0, 1);
		//norm = norm.Normalized();
		//float a = acos((dif * norm));
		//a = a * 180 / M_PI;

		////std::cout << "a: " << a;

		//if (a >= 315 || a <= 45)
		//{
		//	std::cout << "Right" << std::endl;
		//	_movement.X *= -1;
		//}
		//else if (a >= 45 && a <= 135)
		//{
		//	std::cout << "Down" << std::endl;
		//	_movement.Y *= -1;
		//}
		//else if (a >= 135 && a <= 225)
		//{
		//	std::cout << "Left" << std::endl;
		//	_movement.X *= -1;
		//}
		//else if (a >= 225 && a <= 315)
		//{
		//	std::cout << "Up" << std::endl;
		//	_movement.Y *= -1;
		//}

		//Vector2D absVel = Vector2D(_movement.X * _movement.X, _movement.Y * _movement.Y);
		//std::cout << "Vel[" << absVel.X << ", " << absVel.Y << "]: ";
		//if (absVel.X > absVel.Y) // Right
		//{
		//	_movement.X *= -1;
		//	std::cout << "right" << std::endl;
		//}
		//else if (absVel.X < absVel.Y) // Left
		//{
		//	_movement.X *= -1;
		//	std::cout << "left" << std::endl;
		//}
		//else if (absVel.Y > absVel.X) // Top
		//{
		//	_movement.Y *= -1;
		//	std::cout << "top" << std::endl;
		//}
		//else if (absVel.Y < absVel.X) // Bottom
		//{
		//	_movement.Y *= -1;
		//	std::cout << "bottom" << std::endl;
		//}
		//int a = 0;
	}
//	else if (tag == Tags::WallLeft || tag == Tags::WallRight)
//	{
//		_movement.X *= -1;
//	}
//	else if (tag == Tags::WallTop || tag == Tags::WallBottom)
//	{
//		_movement.Y *= -1;
//	}
}
