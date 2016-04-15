#pragma once
#include "Component.h"
#include <memory>
class Collider :
	public Component
{
public:
	Collider(bool isStaticCollider = true);
	~Collider();
	void OnCollisionEnterEvent(const Collider* const other);
	void OnCollisionExitEvent(const Collider* const other);
	virtual bool Intersects(const Collider* const other) = 0;
	void SetIsColliding(bool isColliding) { this->isColliding = isColliding; }
	bool IsColliding() const { return isColliding; }
	bool IsStaticCollider() const { return isStaticCollider; }
protected:
	void Awake() override;
private:
	bool isStaticCollider;
	bool isColliding;
};

