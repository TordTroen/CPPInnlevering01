#include "BoxCollider.h"
#include "Transform.h"

BoxCollider::BoxCollider(bool isStatic)
	: Collider(isStatic)
{
}

BoxCollider::~BoxCollider()
{
}

bool BoxCollider::Intersects(Collider* other)
{
	return GetTransform()->GetRect().Intersects(other->GetTransform()->GetRect());
}
