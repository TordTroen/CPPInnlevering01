#pragma once
#include "Component.h"
#include <memory>
class Collider :
	public Component
{
public:
	Collider(bool isStaticCollider = true);
	~Collider();
	void OnCollisionEnterEvent(std::shared_ptr<Collider> other);
	void OnCollisionExitEvent(std::shared_ptr<Collider> other);
	virtual bool Intersects(std::shared_ptr<Collider> other) = 0;
	void SetIsColliding(bool isColliding) { _isColliding = isColliding; }
	bool IsColliding() const { return _isColliding; }
protected:
	void Awake() override;
private:
	bool _isStaticCollider;
	bool _isColliding;
};

