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
#include "Time.h"
#include "Player.h"
#include "GUIManager.h"


BallMovement::BallMovement(Vector2D startVector, Rect startRect, float speed)
	: startMovement(startVector.Normalized()), startRect(startRect), speed(speed)
{
}

BallMovement::~BallMovement()
{

}

void BallMovement::Awake()
{
	paddleObject = gameManager->FindGameObjectByTag(Tags::Paddle);
	player = paddleObject->GetComponent<Player>();
	Reset();
}

void BallMovement::Update()
{
	if (gameManager->GetGameState() == GameState::InGame)
	{
		if (InputManager::GetInstance().GetKeyDown(SDL_SCANCODE_SPACE) && !canMove){
			Reset();
			canMove = true;
			GUIManager::GetInstance().SetInstructionsActive(false);
		}
		if (canMove) {
			GetTransform()->Translate(movement * speed * Time::DeltaTime());
		}
		else
		{
			PositionAbovePaddle();
		}
	}
}

void BallMovement::OnCollisionEnter(const Collider* const other)
{
	std::string tag = other->GetGameObject()->GetTag();
	
	if (tag == Tags::Paddle && movement.Y > 0)
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
		movement.X = dist;
		if (movement.Y > 0)
		{
			movement.Y *= -1;
		}
		// TODO Make sure movement always has the same length
		movement = movement.Normalized();
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
			movement.X *= -1;
		}
		else // Hit something on the top/bottom
		{
			movement.Y *= -1;
		}
	} 

	if (tag == Tags::WallBottom) {
		player->SetLifeLeft(player->GetLifeLeft() - 1);
		levelStart = true;
		stuffHit = 0;

		// Only reset the ball if we have lives left
		if (player->GetLifeLeft() > 0)
		{
			Reset();
		}
	}
	else if (tag == Tags::WallLeft ||
		tag == Tags::WallRight ||
		tag == Tags::WallTop) {
		stuffHit++;
	}
	else if (tag == Tags::Brick) {
		paddleHit = false;
		player->SetBricksHit(player->GetBricksHit() + 1);
		levelStart = false;
	}
	else if (tag == Tags::Paddle) {
		if (stuffHit == 0) {
			player->SetBricksMissed(player->GetBricksMissed() - 1);
		}
		stuffHit = 0;
		paddleHit = false;
		levelStart = false;
	}
}

void BallMovement::Reset()
{
	canMove = false;
	PositionAbovePaddle();
	movement = startMovement;
	GetGameObject()->SetActive(true);
}

void BallMovement::PositionAbovePaddle()
{
	GetTransform()->SetPosition(paddleObject->GetTransform()->GetCenter() - Vector2D(0, 50));
}
