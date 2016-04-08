#pragma once
#include <memory>
#include <vector>
#include "Component.h"
class Transform;

class GameObject
{
public:
	GameObject();
	~GameObject();
	void Update();
	Component* AddComponent(Component* const comp);
	void AddComponents(std::vector<Component*> components);
	Transform* GetTransform() const;
	template <class T>
	inline T* GetComponent()
	{
		for (auto& it : _components)
		{
			if (typeid(*it) == typeid(T))
			{
				return dynamic_cast<T*>(it.get());
			}
		}
		return NULL;
	}
	void SetTag(std::string tag);
	std::string GetTag() const { return _tag; }
	bool CompareTag(std::string otherTag) const { return (_tag == otherTag); }
	void SendCollisionEnter(const Collider* const other);
	void SendCollisionExit(const Collider* const other);
	void SetActive(bool active);
	bool IsActive() const { return _isActive; }
	void Destroy();
private:
	std::string _tag;
	std::vector<std::unique_ptr<Component>> _components;
	Transform* _transform;
	bool _isActive;
};
