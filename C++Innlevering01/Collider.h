#pragma once
#include "Component.h"

class Collider :
	public Component
{
public:
	Collider();
	~Collider();
	void OnCollisionEnter(Collider* other);
	void OnCollisionExit(Collider* other);
	virtual bool Intersects(Collider* other) = 0;
	bool isColliding;
protected:
	void Awake() override;
};

