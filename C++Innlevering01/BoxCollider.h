#pragma once
#include "Collider.h"

class BoxCollider :
	public Collider
{
public:
	BoxCollider(bool isStatic = true);
	~BoxCollider();
	bool Intersects(Collider* other) override;
};

