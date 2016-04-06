#pragma once
#include <memory>
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
	void OnCollisionEnter(const Collider* const other) override;
private:
	Vector2D m_movement;
	float m_speed;
	bool m_levelStart = true;
	bool m_paddleHit = true;
	int  m_stuffHit = 0;
};

