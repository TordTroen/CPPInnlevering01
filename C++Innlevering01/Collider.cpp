#include "Collider.h"
#include "CollisionManager.h"
#include "GameObject.h"
#include "Tags.h"

Collider::Collider(bool isStaticCollider)
	: isColliding(false)
{
	this->isStaticCollider = isStaticCollider;
}

Collider::~Collider()
{
	CollisionManager::DeleteCollider(this);
	//std::cout << "Deleting component " << typeid(this).name() << std::endl;
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

void Collider::Awake()
{
	// TODO Find a better way to do the collision
	CollisionManager::AddCollider(this, isStaticCollider);
}

