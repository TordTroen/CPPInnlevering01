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
	Transform* GetTransform() const;
	template <class T>
	inline T* GetComp()
	{
		for (auto it : _components)
		{
			T* t = static_cast<T*>(it);
			if (it != NULL)
			{
				return t;
			}
		}
		return NULL;
	}
private:
	std::vector<Component*> _components;
	Transform* _transform;
};
