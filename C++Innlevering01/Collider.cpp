#include "Collider.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Tags.h"

Collider::Collider(bool isStaticCollider)
	: isColliding(false)
{
	isStaticCollider = isStaticCollider;
}


Collider::~Collider()
{
}

void Collider::OnCollisionEnterEvent(const Collider* const other)
{
	SetIsColliding(true);
	GetGameObject()->SendCollisionEnter(other);
}

void Collider::OnCollisionExitEvent(const Collider* const other)
{
	SetIsColliding(false);
}

//bool Collider::Intersects(Collider * other)
//{
//	return false;
//}

void Collider::Awake()
{
	// TODO Find a better way to do the collision
	CollisionManager::AddCollider(this, isStaticCollider);
}

