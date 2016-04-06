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

void BallMovement::OnCollisionEnter(const Collider* const other)
{
	bool levelStart   = true;
	bool paddleHit	  = false;
	bool bottomHit    = false;
	int  allBricksHit = 0;
	int  bricksHit	  = 0;
	int  lifeLost     = 0;

	std::string tag = other->GetGameObject()->GetTag();
	if (tag == Tags::WallBottom) {
		bottomHit = true;
		lifeLost--;
	}

	else if (tag == Tags::Paddle) {
		bricksHit = 0;
		paddleHit = true;
	}

	else if (tag == Tags::Brick) {
		allBricksHit++;
		bricksHit++;
	}


	if (tag == Tags::Paddle && _movement.Y > 0)
	{
		Vector2D paddle = other->GetTransform()->GetCenter();
		Vector2D ball = GetTransform()->GetCenter();
		//SDLWrapper::GetInstance().CreateRect(Color(100, 100, 10), Rect(paddle.X - 5, paddle.Y - 5, 10, 10));
		//SDLWrapper::GetInstance().CreateRect(Color(0, 255, 10), Rect(ball.X - 5, ball.Y - 5, 10, 10));
		
		//Vector2D dif = (paddle - ball);
		float dist = (paddle - ball).GetLength();
		dist = dist / (paddle - other->GetTransform()->GetPosition()).GetLength();
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
		// Bounce based on which side we hit. (NOTE: Untested on non-rectangular shapes)
		// "algorithm" borrowed from: http://gamedev.stackexchange.com/a/95848
		Vector2D ball = GetTransform()->GetCenter();
		Vector2D brick = other->GetTransform()->GetCenter();
		float ax = ball.X;
		float ay = ball.Y;
		float bx = brick.X;
		float by = brick.Y;
		float bw = other->GetTransform()->GetSize().X / 2;
		float bh = other->GetTransform()->GetSize().Y / 2;

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
	} 
}
