#pragma once
#include <string>

class Component
{
public:
	Component(std::string id);
	virtual ~Component();
	virtual void Awake();
	virtual void Start();
	virtual void Update();
	bool IsActive() const { return _isActive; }
	void SetActive(bool active) { _isActive = active; }
	std::string GetID() const { return _id; }
protected:
	std::string _id;
	bool _isActive;
};

