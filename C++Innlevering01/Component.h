#pragma once
class Collider;
class Transform;
class GameObject;

class Component
{
public:
	Component();
	virtual ~Component();
	void Init(GameObject* gameObject);
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	virtual void OnCollisionEnter(Collider* other);
	virtual void OnCollisionExit(Collider* other);
	bool IsActive() const;
	void SetActive(bool active);
	Transform* GetTransform() const { return _transform; }
	GameObject* GetGameObject() const { return _gameObject; }
protected:
	bool _isActive;
	Transform* _transform;
	GameObject* _gameObject;
	virtual void OnSetActive() { } // TODO Make abstract??
	// TODO Maybe make transform and gameobject availivlbe as a protected 
};

