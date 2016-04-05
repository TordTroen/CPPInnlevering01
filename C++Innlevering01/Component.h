#pragma once
#include <iostream>
#include <memory>
class Collider;
class Transform;
class GameObject;

class Component
{
public:
	Component();
	virtual ~Component();
	/* Initializes this component. */
	void Init(std::shared_ptr<GameObject> gameObject);
	/* Called once per frame. Override to do stuff over time.*/
	virtual void Update();
	/* Called when this objects hits another (when both objects have colliders). */
	virtual void OnCollisionEnter(const std::shared_ptr<Collider> other);
	/* Called when this objects stops hitting another(when both objects have colliders). */
	virtual void OnCollisionExit(const std::shared_ptr<Collider> other);
	/* Returns the active state of this component. Update() won't be called when IsActive() is false. */
	bool IsActive() const;
	/* Set the active state of this component. Update() won't be called when the active state is false. */
	void SetActive(bool active);
	/* Returns the Transform component of the GameObject this component is attached to. */
	std::shared_ptr<Transform> GetTransform() const { return _transform; }
	/* Returns the GameObject this component is attached to. */
	std::shared_ptr<GameObject> GetGameObject() const { return _gameObject; }
protected:
	/* Called after the object is contructed. Override to do initialization stuff after the object is created. */
	virtual void Awake();
	/* Called when the objects IsActive() state changes. */
	virtual void OnSetActive(); // TODO Make abstract??
private:
	bool _isActive;
	std::shared_ptr<Transform> _transform;
	std::shared_ptr<GameObject> _gameObject;
};

