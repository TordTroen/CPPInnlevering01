#pragma once
#include <memory>
#include "Component.h"
#include "Vector2D.h"
#include "Rect.h"
class Collider;

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
	Vector2D m_movement;
	Vector2D startMovement;
	Rect startRect;
	float m_speed;
	bool m_levelStart = true;
	bool m_paddleHit = true;
	bool m_canMove = true;
	int  m_stuffHit = 0;
};

