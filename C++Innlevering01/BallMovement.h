#pragma once
#include "Component.h"
#include "Vector2D.h"
class Collider;

class BallMovement :
	public Component
{
public:
	BallMovement();
	~BallMovement();
	void Update() override;
	void OnCollisionEnter(Collider* other) override;
private:
	Vector2D movement;
};

