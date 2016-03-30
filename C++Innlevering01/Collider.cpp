#include "Collider.h"
#include "CollisionManager.h"
#include <iostream>
#include "GameObject.h"
Collider::Collider()
{
}


Collider::~Collider()
{
}

void Collider::OnCollisionEnterEvent(Collider* other)
{
	//std::cout << "ColEnter: " << _gameObject->GetTag().c_str() << " -> " << other->_gameObject->GetTag().c_str() << std::endl;
	isColliding = true;
	GetGameObject()->SendCollisionEnter(other);
}

void Collider::OnCollisionExitEvent(Collider* other)
{
	//std::cout << "ColExit: " << _gameObject->GetTag().c_str() << " -> " << other->_gameObject->GetTag().c_str() << std::endl;
	isColliding = false;
}

bool Collider::Intersects(Collider * other)
{
	return false;
}

void Collider::Awake()
{
	// TODO Find a better way to do the collision
	if (!_gameObject->CompareTag("Player"))
	{
		CollisionManager::AddCollider(this);
	}
}

