#pragma once
#include "Component.h"

class Collider :
	public Component
{
public:
	Collider(bool isStaticCollider = true);
	~Collider();
	void OnCollisionEnterEvent(Collider* other);
	void OnCollisionExitEvent(Collider* other);
	virtual bool Intersects(Collider* other) = 0;
	void SetIsColliding(bool isColliding) { _isColliding = isColliding; }
	bool IsColliding() const { return _isColliding; }
protected:
	void Awake() override;
private:
	bool _isStaticCollider;
	bool _isColliding;
};

