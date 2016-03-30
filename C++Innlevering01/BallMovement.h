#pragma once
#include "Component.h"
#include "Vector2D.h"

class Collider;

class BallMovement :
	public Component
{
public:
	BallMovement(Vector2D startVector, float speed);
	~BallMovement();
	void Update() override;
	void OnCollisionEnter(const Collider* other) override;
private:
	Vector2D _movement;
	float _speed;
};

