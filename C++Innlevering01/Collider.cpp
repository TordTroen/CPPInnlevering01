#include "Collider.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Tags.h"

Collider::Collider(bool isStaticCollider)
	: _isColliding(false)
{
	_isStaticCollider = isStaticCollider;
}


Collider::~Collider()
{
}

void Collider::OnCollisionEnterEvent(std::shared_ptr<Collider> other)
{
	SetIsColliding(true);
	GetGameObject()->SendCollisionEnter(other);
}

void Collider::OnCollisionExitEvent(std::shared_ptr<Collider> other)
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
	CollisionManager::AddCollider(std::shared_ptr<Collider>(this), _isStaticCollider);
}

