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
#include "GameObjectManager.h"
#include "Time.h"
#include "Player.h"


BallMovement::BallMovement(Vector2D startVector, Rect startRect, float speed)
	: startMovement(startVector.Normalized()), startRect(startRect), m_speed(speed)
{
}

BallMovement::~BallMovement()
{
}

void BallMovement::Awake()
{
	Reset();
}

void BallMovement::Update()
{
	
	if (GameManager::GetInstance().GetGameState() == InGame)
	{
		GetTransform()->Translate(m_movement * m_speed * Time::DeltaTime());
	}
}

void BallMovement::OnCollisionEnter(const Collider* const other)
{

	std::string tag			= other->GetGameObject()->GetTag();
	GameObject* paddleObj	= GameObjectManager::GetInstance().FindGameObjectByTag(Tags::Paddle);
	Player * player			= paddleObj->GetComponent<Player>();

	if (tag == Tags::WallBottom) {
		player->SetLifeLeft(player->GetLifeLeft() - 1);
		m_levelStart = true;
		m_stuffHit = 0;
	}

	else if (tag == Tags::WallLeft  ||
			 tag == Tags::WallRight ||
			 tag == Tags::WallTop   ){
			 m_stuffHit++;
	}

	else if (tag == Tags::Brick) {
		m_paddleHit = false;
		player->SetBricksHit(player->GetBricksHit() + 1);
		m_levelStart = false;
	}

	else if (tag == Tags::Paddle) {
		if (m_stuffHit == 0) {
			player->SetBricksMissed(player->GetBricksMissed() - 1);
		}
		m_stuffHit = 0;
		m_paddleHit = false;
		m_levelStart = false;
	}
	

	if (tag == Tags::Paddle && m_movement.Y > 0)
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
		m_movement.X = dist;
		if (m_movement.Y > 0)
		{
			m_movement.Y *= -1;
		}
		// TODO Make sure movement always has the same length
		m_movement = m_movement.Normalized();
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
			m_movement.X *= -1;
		}
		else // Hit something on the top/bottom
		{
			m_movement.Y *= -1;
		}
	} 
}

void BallMovement::Reset()
{
	GetTransform()->SetRect(startRect);
	m_movement = startMovement;
	GetGameObject()->SetActive(true);
}
