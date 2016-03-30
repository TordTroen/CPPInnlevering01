#pragma once
#include "Component.h"

class Collider :
	public Component
{
public:
	Collider();
	~Collider();
	void OnCollisionEnterEvent(Collider* other);
	void OnCollisionExitEvent(Collider* other);
	virtual bool Intersects(Collider* other);
	bool isColliding;
protected:
	void Awake() override;
};

