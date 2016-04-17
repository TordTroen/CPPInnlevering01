#pragma once
#include <memory>
#include <vector>
#include "Component.h"
class Transform;

class GameObject
{
public:
	GameObject(GameManager* gameManager);
	~GameObject();
	void Update();
	Component* AddComponent(Component* const comp);
	void AddComponents(std::vector<Component*> components);
	Transform* GetTransform() const;

	/* Returns the first Component of the specified type on this GameObject. Returns NULL if the component doensn't exist on this GameObject. */
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
		std::cout << "WARNING: Couldn't find the component " << typeid(T).name() << " on this GameObject" << std::endl;
		return NULL;
	}
	void SetTag(std::string tag);
	std::string GetTag() const { return _tag; }
	bool CompareTag(std::string otherTag) const { return (_tag == otherTag); }

	/* Send the OnCollisionXXX event to all the attached components when this GameObject recieves it. */
	void SendCollisionEnter(const Collider* const other);
	void SendCollisionExit(const Collider* const other);

	void SetActive(bool active);
	bool IsActive() const { return _isActive; }
private:
	std::string _tag;
	std::vector<std::unique_ptr<Component>> _components;
	Transform* _transform;
	bool _isActive;
	GameManager* gameManager;
};
