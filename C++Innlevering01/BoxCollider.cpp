#include "BoxCollider.h"
#include "Transform.h"
#include "CollisionManager.h"

BoxCollider::BoxCollider(bool isStatic)
	: Collider(isStatic)
{
}

BoxCollider::~BoxCollider()
{
	CollisionManager::DeleteCollider(this);
	std::cout << "Deleting component " << typeid(this).name() << std::endl;
}

bool BoxCollider::Intersects(const Collider* const other)
{
	return GetTransform()->GetRect().Intersects(other->GetTransform()->GetRect());
}
