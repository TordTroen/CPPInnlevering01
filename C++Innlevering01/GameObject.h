#pragma once
#include <vector>
#include "Component.h"

class Transform;

class GameObject
{
public:
	GameObject();
	~GameObject();
	void Update();
	Component* AddComponent(Component* comp);
	void AddComponents(std::vector<Component*> components);
	Transform* GetTransform() const;
	template <class T>
	inline T* GetComponent()
	{
		for (auto it : _components)
		{
			T* t = static_cast<T*>(it);
			if (t != NULL)
			{
				return dynamic_cast<T*>(it);
				//return t;
			}
		}
		return NULL;
	}
	template <class T>
	inline T* GetComp()
	{
		for (auto it : _components)
		{
			T* t = static_cast<T*>(it);
			if (t != NULL)
			{
				return dynamic_cast<T*>(it);
				//return it;
			}
		}
		return NULL;
	}
	void SetTag(std::string tag);
	std::string GetTag() const { return _tag; }
	bool CompareTag(std::string otherTag) const { return (_tag == otherTag); }
	void SendCollisionEnter(Collider* other);
	void SendCollisionExit(Collider* other);
	void SetActive(bool active);
	bool IsActive() const { return _isActive; }
private:
	std::string _tag;
	std::vector<Component*> _components;
	Transform* _transform;
	bool _isActive;
};
