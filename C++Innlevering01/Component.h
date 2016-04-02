#pragma once
#include <iostream>
class Collider;
class Transform;
class GameObject;

class Component
{
public:
	Component();
	virtual ~Component();
	void Init(GameObject* gameObject);
	virtual void Update();
	virtual void OnCollisionEnter(const Collider* other);
	virtual void OnCollisionExit(const Collider* other);
	bool IsActive() const;
	void SetActive(bool active);
	Transform* GetTransform() const { return _transform; }
	GameObject* GetGameObject() const { return _gameObject; }
protected:
	virtual void Awake();
	//virtual void Start();
	virtual void OnSetActive(); // TODO Make abstract??
private:
	bool _isActive;
	Transform* _transform;
	GameObject* _gameObject;
};

