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
	void Init(std::shared_ptr<GameObject> gameObject);
	virtual void Update();
	virtual void OnCollisionEnter(const std::shared_ptr<Collider> other);
	virtual void OnCollisionExit(const std::shared_ptr<Collider> other);
	bool IsActive() const;
	void SetActive(bool active);
	std::shared_ptr<Transform> GetTransform() const { return _transform; }
	std::shared_ptr<GameObject> GetGameObject() const { return _gameObject; }
protected:
	virtual void Awake();
	//virtual void Start();
	virtual void OnSetActive(); // TODO Make abstract??
private:
	bool _isActive;
	std::shared_ptr<Transform> _transform;
	std::shared_ptr<GameObject> _gameObject;
};

