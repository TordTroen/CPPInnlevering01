#pragma once
#include <vector>
#include "Component.h"
#include "Transform.h"

class GameObject
{
public:
	GameObject();
	~GameObject();
	void Update();
	// TODO Use templates i stedet
	Component* AddComponent(Component* comp);
	Component* GetComponent(std::string comp);
	Transform* GetTransform() const;
	/*template <typename T>
	inline void AddComponent(T *comp)
	{
		_components.emplace_back(comp);
	}
	template <typename T>
	inline T GetComponent(T *comp)
	{
		for (auto i : _components)
		{
			
		}
		return NULL;
	}*/
private:
	std::vector<Component*> _components;
	Transform* _transform;
};
