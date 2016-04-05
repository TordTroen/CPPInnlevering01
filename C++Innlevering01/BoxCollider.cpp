#include "BoxCollider.h"
#include "Transform.h"

BoxCollider::BoxCollider(bool isStatic)
	: Collider(isStatic)
{
}

BoxCollider::~BoxCollider()
{
}

bool BoxCollider::Intersects(const Collider* const other)
{
	return GetTransform()->GetRect().Intersects(other->GetTransform()->GetRect());
}
