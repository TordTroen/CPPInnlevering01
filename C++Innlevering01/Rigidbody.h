#pragma once
#include "Component.h"
#include "Vector2D.h"

class Rigidbody :
	public Component
{
public:
	Rigidbody();
	~Rigidbody();
	void Update() override;
	void AddForce(Vector2D force);
	void SetVelocity(Vector2D newVel);
	Vector2D GetVelocity() const;
private:
	Vector2D _velocity;
};
