#pragma once
#include <memory>
#include "Component.h"
#include "Vector2D.h"
#include "Rect.h"
#include "PaddleMovement.h"
class Collider;
class Player;

class BallMovement :
	public Component
{
public:
	BallMovement(Vector2D startVector, Rect startRect, float speed);
	~BallMovement();
	void Awake() override;
	void Update() override;
	void OnCollisionEnter(const Collider* const other) override;
	void Reset();
private:
	void PositionAbovePaddle();
	Vector2D movement;
	Vector2D startMovement;
	GameObject* paddleObject;
	Player* player;
	Rect startRect;
	float speed;
	bool levelStart = true;
	bool paddleHit = true;
	bool canMove = true;
	int  stuffHit = 0;
};

