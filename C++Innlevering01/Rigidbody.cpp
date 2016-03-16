#include "Rigidbody.h"
#include "Vector2D.h"
#include "Transform.h"
#include "GameManager.h"

Rigidbody::Rigidbody()
{
}


Rigidbody::~Rigidbody()
{
}

void Rigidbody::Update()
{
	// TODO Add gravity force here multiplied by deltaTime
	//_velocity.Y -= 9.81;
	AddForce(Vector2D(0, GameManager::GetInstance().GetGravity()));

	// Eulers method
	_transform->SetPosition(_transform->_position + _velocity);
}

void Rigidbody::AddForce(Vector2D force)
{
	_velocity = _velocity + force;
}

void Rigidbody::SetVelocity(Vector2D newVel)
{
	_velocity = newVel;
}

Vector2D Rigidbody::GetVelocity() const
{
	return _velocity;
}
