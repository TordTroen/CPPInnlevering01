#pragma once
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
	bool IsActive() const;
	void SetActive(bool active);
protected:
	bool _isActive;
	Transform* _transform;
	GameObject* _gameObject;
	// TODO Maybe make transform and gameobject availivlbe as a protected 
};

