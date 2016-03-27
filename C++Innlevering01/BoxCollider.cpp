#include "BoxCollider.h"
#include "Transform.h"
#include <iostream>

BoxCollider::BoxCollider()
{
}

BoxCollider::~BoxCollider()
{
}

//void BoxCollider::OnCollision(BoxCollider* other)
//{
//	std::cout << "Collided" << std::endl;
//}

bool BoxCollider::Intersects(Collider* other)
{
	//return false;
	return _transform->GetRect().Intersects(other->GetTransform()->GetRect());
}
