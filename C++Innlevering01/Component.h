#pragma once

class Component
{
public:
	Component();
	virtual ~Component();
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	inline bool IsActive() const;
	inline void SetActive(bool active);
protected:
	bool _isActive;
private:
	// TODO Maybe make transform and gameobject availivlbe as a protected 
};

