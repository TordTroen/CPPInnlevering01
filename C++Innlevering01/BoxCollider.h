#pragma once
#include "Collider.h"

class BoxCollider :
	public Collider
{
public:
	BoxCollider();
	~BoxCollider();
	//void OnCollision(BoxCollider* other);
	bool Intersects(Collider* other) override;
};

